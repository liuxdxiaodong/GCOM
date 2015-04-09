#include "imgproc.h"

#ifdef max
#undef max
#endif // max

#ifdef min
#undef min
#endif // min

namespace Lamp
{
    const int WIN_SIZE = 60;
    const int HALF_WIN_SIZE = WIN_SIZE / 2;

    ImgProc::ImgProc()
    {
    }

    ImgProc::~ImgProc()
    {
    }

    void ImgProc::copyEdge(
        const cv::Mat& srcStdImg,
        const cv::Mat& srcChkImg,
        cv::Mat& dstStdImg,
        cv::Mat& dstChkImg
        )
    {
        int rows = srcStdImg.rows;
        int cols = srcStdImg.cols;
        dstStdImg = cv::Mat::zeros(rows + WIN_SIZE, cols + WIN_SIZE, CV_8UC1);
        dstChkImg = cv::Mat::zeros(rows + WIN_SIZE, cols + WIN_SIZE, CV_8UC1);
        for(int y = 0; y < rows; ++y)
        {
            const uchar* srcStdPtr = srcStdImg.ptr(y);
            const uchar* srcChkPtr = srcChkImg.ptr(y);
            uchar* dstStdPtr = dstStdImg.ptr(y + HALF_WIN_SIZE);
            uchar* dstChkPtr = dstChkImg.ptr(y + HALF_WIN_SIZE);
            for(int x = 0; x < cols; ++x)
            {
                dstStdPtr[x + HALF_WIN_SIZE] = srcStdPtr[x];
                dstChkPtr[x + HALF_WIN_SIZE] = srcChkPtr[x];
            }
        }
    }

    void ImgProc::l0Smooth(
        const cv::Mat& src,
        cv::Mat& dst,
        double kappa,
        double lambda,
        double betaMax
        )
    {
        cv::Size size = src.size();
        int length = size.area();
        cv::Mat zero = cv::Mat::zeros(size, CV_32FC1);
        // Matlab: S = im2double(I); normin1 = fft2(S);
        cv::Mat S; src.convertTo(S, CV_32FC1, 1.0 / 255, 0.0);
        cv::Mat sPlanes[2]; sPlanes[0] = S; sPlanes[1] = zero;
        cv::Mat normin1; cv::merge(sPlanes, 2, normin1); cv::dft(normin1, normin1, cv::DFT_COMPLEX_OUTPUT);
        // Matlab: fx = [1, -1], otfFx = psf2otf(fx, size);
        cv::Mat fx = zero.clone(); fx.at<float>(0, 0) = 1; fx.at<float>(0, 1) = -1;
        cv::Mat fxPlanes[2]; fxPlanes[0] = fx; fxPlanes[1] = zero;
        cv::Mat otfFx; cv::merge(fxPlanes, 2, otfFx); cv::dft(otfFx, otfFx, cv::DFT_COMPLEX_OUTPUT); fx.release();
        // Matlab: fy = [1; -1], otfFy = psf2otf(fy, size);
        cv::Mat fy = zero.clone(); fy.at<float>(0, 0) = 1; fy.at<float>(1, 0) = -1;
        cv::Mat fyPlanes[2]; fyPlanes[0] = fy; fyPlanes[1] = zero;
        cv::Mat otfFy; cv::merge(fyPlanes, 2, otfFy); cv::dft(otfFy, otfFy, cv::DFT_COMPLEX_OUTPUT); fy.release();
        // Matlab: denormin2 = abs(otfFx).^2 + abs(otfFy).^2;
        cv::Mat denFx; cv::mulSpectrums(otfFx, otfFx, denFx, cv::DFT_REAL_OUTPUT, true); otfFx.release();
        cv::Mat denFy; cv::mulSpectrums(otfFy, otfFy, denFy, cv::DFT_REAL_OUTPUT, true); otfFy.release();
        cv::Mat denormin2; cv::add(denFx, denFy, denormin2); denFx.release(); denFy.release();
        cv::Mat dv[2]; cv::split(denormin2, dv); denormin2.release();
        denormin2 = dv[0]; dv[1].release();
        // smoothing
        double beta = lambda * kappa;
        cv::Mat one = cv::Mat::ones(size, CV_32FC1);
        // kernel dx
        cv::Mat dx(1, 2, CV_32FC1); dx.at<float>(0, 0) = -1; dx.at<float>(0, 1) = 1;
        // kernel dy
        cv::Mat dy(2, 1, CV_32FC1); dy.at<float>(0, 0) = -1; dy.at<float>(1, 0) = 1;
        // h-v subproblem
        cv::Mat Sx;
        cv::Mat Sy;
        cv::Mat denormin;
        cv::Mat SxSx;
        cv::Mat SySy;
        cv::Mat sum;
        double tmp = 0;
        float* ptrX = NULL;
        float* ptrY = NULL;
        float* ptrS = NULL;
        // S subproblem
        cv::Mat Sxx;
        cv::Mat Syy;
        cv::Mat nv2[2]; nv2[0] = zero.clone(); nv2[1] = zero.clone();
        cv::Mat normin2;
        cv::Mat nv[2];
        cv::Mat normin;
        cv::Mat fsv[2];
        cv::Mat FS;
        while(beta < betaMax)
        {
            cv::add(one, denormin2 * beta, denormin);
            // h-v subproblem
            // Matlab: h = [diff(S,1,2), S(:,1,:) - S(:,end,:)];
            // Matlab: v = [diff(S,1,1); S(1,:,:) - S(end,:,:)];
            cv::filter2D(S, Sx, CV_32FC1, dx, cv::Point(0, 0), 0.0, cv::BORDER_REFLECT);
            cv::filter2D(S, Sy, CV_32FC1, dy, cv::Point(0, 0), 0.0, cv::BORDER_REFLECT);
            // Matlab: t = (h.^2+v.^2)<lambda/beta;
            cv::multiply(Sx, Sx, SxSx);
            cv::multiply(Sy, Sy, SySy);
            cv::add(SxSx, SySy, sum);
            tmp = lambda / beta;
            ptrX = (float*)Sx.data;
            ptrY = (float*)Sy.data;
            ptrS = (float*)sum.data;
            for(int idx = 0; idx < length; ++idx)
            {
                if(*(ptrS++) < tmp)
                {
                    *(ptrX++) = 0;
                    *(ptrY++) = 0;
                }
                else
                {
                    ++ptrX;
                    ++ptrY;
                }
            }
            // S subproblem
            // Matlab: dh = [h(:,end,:) - h(:, 1,:), -diff(h,1,2)];
            // Matlab: dv = [v(end,:,:) - v(1, :,:); -diff(v,1,1)];
            cv::filter2D(Sx, Sxx, CV_32FC1, -dx, cv::Point(1, 0));
            cv::filter2D(Sy, Syy, CV_32FC1, -dy, cv::Point(0, 1));
            cv::add(Sxx, Syy, sum);
            // Matlab: FS = (normin1 + beta*fft2(normin2))./denormin;
            nv2[0] = sum;
            cv::merge(nv2, 2, normin2);
            cv::dft(normin2, normin2, cv::DFT_COMPLEX_OUTPUT);
            cv::add(normin1, normin2 * beta, normin);
            cv::split(normin, nv);
            cv::divide(nv[0], denormin, fsv[0]);
            cv::divide(nv[1], denormin, fsv[1]);
            cv::merge(fsv, 2, FS);
            // Matlab: S = real(ifft2(FS));
            cv::idft(FS, S, cv::DFT_SCALE | cv::DFT_REAL_OUTPUT);
            beta *= kappa;
        }
        S.convertTo(dst, CV_8UC1, 255, 0.0);
    }

    void ImgProc::preProc(
        const cv::Mat& stand,
        const cv::Mat& image,
        cv::Mat& stdImg,
        cv::Mat& chkImg
        )
    {
        // stand
        cv::Mat grayImg;
        cv::Mat diff = image - stand;
        cv::cvtColor(diff, grayImg, CV_BGR2GRAY);
        cv::threshold(grayImg, stdImg, 8, 255, cv::THRESH_BINARY);
        ImgProc::mopEdge<uchar>(stdImg, 0);
        //cv::imshow("stand", stdImg);
        //cv::waitKey();
        // image
        cv::cvtColor(image, grayImg, CV_BGR2GRAY);
        cv::Mat smthImg;
        ImgProc::l0Smooth(grayImg, smthImg);
        double minVal = 0;
        double maxVal = 0;
        cv::minMaxLoc(smthImg, &minVal, &maxVal);
        smthImg.convertTo(smthImg, CV_32FC1);
        cv::Mat normImg = (smthImg - cv::Mat::ones(smthImg.size(), CV_32FC1) * minVal) / float(maxVal - minVal) * 255.0f;
        normImg.convertTo(normImg, CV_8UC1);
        cv::Mat binImg;
        //double threshold = cv::threshold(grayImg, binImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        //cv::Canny(grayImg, edgeImg, threshold * 0.4, threshold);
        double threshold = cv::threshold(normImg, binImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        cv::Canny(normImg, chkImg, threshold * 0.4, threshold);
        ImgProc::mopEdge<uchar>(chkImg, 0);
        //cv::imshow("check", chkImg);
        //cv::waitKey();
    }

    void ImgProc::pca2D(
        const std::vector<int>& winLocX1,
        const std::vector<int>& winLocY1,
        const std::vector<int>& winLocX2,
        const std::vector<int>& winLocY2,
        int& crack,
        int& dual,
        int& broken
        )
    {
        crack = 0;
        dual = 0;
        broken = 0;
        // 准线归一化
        cv::Mat X1_c(winLocX1.size(), 1, CV_32SC1);
        cv::Mat Y1_c(winLocY1.size(), 1, CV_32SC1);
        CopyMemory(X1_c.data, winLocX1.data(), sizeof(int) * winLocX1.size());
        CopyMemory(Y1_c.data, winLocY1.data(), sizeof(int) * winLocY1.size());
        X1_c.convertTo(X1_c, CV_32FC1);
        Y1_c.convertTo(Y1_c, CV_32FC1);
        // 曲线归一化
        cv::Mat X2_c(winLocX2.size(), 1, CV_32SC1);
        cv::Mat Y2_c(winLocY2.size(), 1, CV_32SC1);
        CopyMemory(X2_c.data, winLocX2.data(), sizeof(int) * winLocX2.size());
        CopyMemory(Y2_c.data, winLocY2.data(), sizeof(int) * winLocY2.size());
        X2_c.convertTo(X2_c, CV_32FC1);
        Y2_c.convertTo(Y2_c, CV_32FC1);
        // 主方向
        std::vector<cv::Point> winLoc1;
        std::vector<int>::const_iterator xIter = winLocX1.begin();
        std::vector<int>::const_iterator yIter = winLocY1.begin();
        for(size_t idx = 0; idx < winLocX1.size(); ++idx)
        {
            winLoc1.push_back(cv::Point(*xIter, *yIter));
            ++xIter;
            ++yIter;
        }
        cv::Vec4f line;
        cv::fitLine(winLoc1, line, CV_DIST_L2, 0, 0.01f, 0.01f);
        float theta = atan(line[1] / line[0]);
        float cosa = cos(theta);
        float sina = sin(theta);
        cv::Mat offset1 = cv::Mat::ones(X1_c.rows, 1, CV_32FC1) * HALF_WIN_SIZE;
        cv::Mat offset2 = cv::Mat::ones(X2_c.rows, 1, CV_32FC1) * HALF_WIN_SIZE;
        cv::Mat rotX1_in = (X1_c - offset1) * cosa + (Y1_c - offset1) * sina + offset1;
        cv::Mat rotY1_in = -(X1_c - offset1) * sina + (Y1_c - offset1) * cosa + offset1;
        cv::Mat rotX2_in = (X2_c - offset2) * cosa + (Y2_c - offset2) * sina + offset2;
        cv::Mat rotY2_in = -(X2_c - offset2) * sina + (Y2_c - offset2) * cosa + offset2;
        cv::Mat rotX1;
        cv::Mat rotX2;
        rotX1_in.convertTo(rotX1, CV_32SC1);
        rotX2_in.convertTo(rotX2, CV_32SC1);
        cv::Mat comIdx(0, 1, CV_32SC1);
        ImgProc::unique<int>(rotX1, comIdx); // 唯一化每个待检测曲线的横坐标
        int comNum = comIdx.rows;
        cv::Mat dualX2(0, 1, CV_32SC1);
        ImgProc::unique<int>(rotX2, dualX2);
        cv::Mat dualDis(0, 1, CV_32SC1);
        for(int i = 0; i < dualX2.rows; ++i)
        {
            std::vector<int> coorX;
            std::vector<int> coorY;
            ImgProc::findTag<int>(rotX2, dualX2.at<int>(i), coorX, coorY);
            cv::Mat dualY2(0, 1, CV_32SC1);
            for(size_t j = 0; j < coorX.size(); ++j)
            {
                dualY2.push_back<int>(rotX2.at<int>(j));
            }
            double minVal = 0;
            double maxVal = 0;
            cv::minMaxLoc(dualY2, &minVal, &maxVal);
            dualDis.push_back<int>((int)abs(maxVal - minVal));
        }
        if(dualDis.empty())
        {
            crack = 1;
        }
        else
        {
            cv::Mat mask = (dualDis >= 2);
            mask.convertTo(mask, CV_32SC1);
            int dualIdx = cvRound(cv::norm(mask, cv::NORM_L1) / 255);
            if(dualIdx >= (0.55 * dualX2.rows))
            {
                dual = 1;
            }
        }
        // 崩损检测
        std::vector<float> index;
        for(int i = 0; i < comNum; ++i)
        {
            std::vector<int> locX1;
            std::vector<int> locY1;
            std::vector<int> locX2;
            std::vector<int> locY2;
            ImgProc::findTag<int>(rotX1, comIdx.at<int>(i), locX1, locY1);
            ImgProc::findTag<int>(rotX2, comIdx.at<int>(i), locX2, locY2);
            if(locX2.empty())
            {
                continue;
            }
            float sum1 = 0.0f;
            std::vector<float> y1_col;
            for(std::vector<int>::const_iterator xIter = locX1.begin(); xIter != locX1.end(); ++xIter)
            {
                y1_col.push_back(rotY1_in.at<float>(*xIter));
                sum1 += rotY1_in.at<float>(*xIter);
            }
            float mean1 = sum1 / y1_col.size();
            float sum2 = 0.0f;
            std::vector<float> y2_col;
            for(std::vector<int>::const_iterator xIter = locX2.begin(); xIter != locX2.end(); ++xIter)
            {
                y2_col.push_back(rotY2_in.at<float>(*xIter));
                sum2 += rotY2_in.at<float>(*xIter);
            }
            float mean2 = sum2 / y2_col.size();
            index.push_back(abs(mean1 - mean2));
        }
        std::vector<float> mask;
        for(std::vector<float>::const_iterator iter = index.begin(); iter != index.end(); ++iter)
        {
            if(*iter > 5)
            {
                mask.push_back(*iter);
            }
        }
        if(!mask.empty())
        {
            broken = 1;
        }
    }

    void ImgProc::pcaCheck(
        const cv::Mat& stand,
        const cv::Mat& image,
        cv::Mat& edge,
        std::vector<int>& crack,
        std::vector<int>& dual,
        std::vector<int>& broken,
        cv::Mat& crackPos,
        cv::Mat& dualPos,
        cv::Mat& brokenPos
        )
    {
        cv::Mat stdImg; // 给定的准线
        cv::Mat chkImg; // 检测的曲线
        ImgProc::preProc(stand, image, stdImg, chkImg);
        edge = chkImg.clone();
        // 把检测图像的边缘扩大HALF_WIN_SIZE
        cv::Mat newStdImg; // 新准线
        cv::Mat newChkImg; // 新曲线
        ImgProc::copyEdge(stdImg, chkImg, newStdImg, newChkImg);

        int size = cv::countNonZero(newStdImg);
        std::vector<int> locX;
        std::vector<int> locY;
        ImgProc::findTag<uchar>(newStdImg, 255, locX, locY);

        int sizeCor = int((double)size / HALF_WIN_SIZE) + 1;
        crackPos = cv::Mat::zeros(sizeCor, 2, CV_32SC1);
        dualPos = cv::Mat::zeros(sizeCor, 2, CV_32SC1);
        brokenPos = cv::Mat::zeros(sizeCor, 2, CV_32SC1);

        cv::Mat stdWin = cv::Mat::zeros(WIN_SIZE + 1, WIN_SIZE + 1, CV_32SC1);
        cv::Mat chkWin = cv::Mat::zeros(WIN_SIZE + 1, WIN_SIZE + 1, CV_32SC1);
        for(int index = 0; index < size; index += HALF_WIN_SIZE)
        {
            cv::Rect roi(locX[index] - HALF_WIN_SIZE, locY[index] - HALF_WIN_SIZE, WIN_SIZE + 1, WIN_SIZE + 1);
            //cv::Mat stdSkeleton = cv::Mat::zeros(newStdImg.size(), CV_8UC1);
            //cv::rectangle(stdSkeleton, roi, cv::Scalar(255));
            //cv::max(stdSkeleton, newStdImg, stdSkeleton);
            //cv::Mat chkSkeleton = cv::Mat::zeros(newChkImg.size(), CV_8UC1);
            //cv::rectangle(chkSkeleton, roi, cv::Scalar(255));
            //cv::max(chkSkeleton, newChkImg, chkSkeleton);
            //cv::imshow("std", stdSkeleton);
            //cv::imshow("chk", chkSkeleton);
            // 检测出窗口内的边缘
            stdWin = newStdImg(roi).clone();
            chkWin = newChkImg(roi).clone();
            std::vector<int> winLocX1;
            std::vector<int> winLocY1;
            ImgProc::findTag<uchar>(stdWin, 255, winLocX1, winLocY1);
            std::vector<int> winLocX2;
            std::vector<int> winLocY2;
            ImgProc::findTag<uchar>(chkWin, 255, winLocX2, winLocY2);
            int crackTmp = false;
            int dualTmp = false;
            int brokenTmp = false;
            ImgProc::pca2D(winLocX1, winLocY1, winLocX2, winLocY2, crackTmp, dualTmp, brokenTmp);
            crackPos.at<int>(index / HALF_WIN_SIZE, 0) = locX[index] - HALF_WIN_SIZE;
            crackPos.at<int>(index / HALF_WIN_SIZE, 1) = locY[index] - HALF_WIN_SIZE;
            dualPos.at<int>(index / HALF_WIN_SIZE, 0) = locX[index] - HALF_WIN_SIZE;
            dualPos.at<int>(index / HALF_WIN_SIZE, 1) = locY[index] - HALF_WIN_SIZE;
            brokenPos.at<int>(index / HALF_WIN_SIZE, 0) = locX[index] - HALF_WIN_SIZE;
            brokenPos.at<int>(index / HALF_WIN_SIZE, 1) = locY[index] - HALF_WIN_SIZE;
            crack.push_back(crackTmp);
            dual.push_back(dualTmp);
            broken.push_back(brokenTmp);
        }
    }

    void ImgProc::valueFocus(
        const cv::Mat& image,
        cv::Rect roi,
        int norm,
        double& focus
        )
    {
        cv::Mat roiImg = image(roi).clone();

        cv::Mat dstXImg;
        cv::Mat dstYImg;
        cv::Sobel(roiImg, dstXImg, CV_32F, 1, 0, 3);
        cv::Sobel(roiImg, dstYImg, CV_32F, 0, 1, 3);

        cv::Mat G;
        if(1 == norm)
        {
            G = abs(dstXImg) + abs(dstYImg);
            cv::minMaxIdx(G, NULL, &focus);
        }
        else if(2 == norm)
        {
            G = dstXImg.mul(dstXImg) + dstYImg.mul(dstYImg);
            cv::Scalar mean;
            cv::Scalar stddev;
            cv::meanStdDev(G, mean, stddev);
            focus = stddev[0];
        }
    }

    void ImgProc::preEdge(
        const cv::Mat& src,
        cv::Mat& dst
        )
    {
        cv::blur(src, dst, cv::Size(3, 3));
    }

    void ImgProc::extContour(
        const cv::Mat& image,
        cv::vector<cv::vector<cv::Point>>& contours,
        cv::vector<cv::Point>& globalContour
        )
    {
        cv::Mat binImg;
        double thresh = cv::threshold(image, binImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        cv::Mat edgeImg;
        cv::Canny(binImg, edgeImg, thresh, 255, 3);
        // single contours
        cv::vector<cv::Vec4i> hierarchy;
        cv::findContours(edgeImg, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
        // update global contours
        for(std::vector<cv::vector<cv::Point>>::const_iterator conIter = contours.begin(); conIter != contours.end(); ++conIter)
        {
            for(cv::vector<cv::Point>::const_iterator ptIter = conIter->begin(); ptIter != conIter->end(); ++ptIter)
            {
                if(ptIter->x > globalContour[ptIter->y].x)
                {
                    globalContour[ptIter->y].x = ptIter->x;
                }
            }
        }
    }

    void ImgProc::fitEdge(
        const cv::Size& size,
        const cv::vector<cv::Point>& globalContour,
        cv::Vec4f& line,
        cv::Mat& edgeImg
        )
    {
        // deal with outliers
        const cv::Point2f P1(1974, 0);
        const cv::Point2f P2(1588, 1944);
        const float k = (P2.y - P1.y) / (P2.x - P1.x);
        const float b = P1.y - k * P1.x;
        const double tolPixel = 10;
        int indexFit = 0;
        int countFit = 0;
        cv::vector<cv::Point> globalContourFit;
        for(std::vector<cv::Point>::const_iterator ptIter = globalContour.begin(); ptIter != globalContour.end(); ++ptIter)
        {
            //if(abs((k * ptIter->x - ptIter->y + b) / sqrt(k * k + 1)) < tolPixel)
            {
                globalContourFit.push_back(*ptIter);
            }
        }
        cv::fitLine(globalContourFit, line, CV_DIST_L2, 0, 0.01, 0.01);
        cv::Point p1;
        cv::Point p2;
        float t = float(size.width + size.height);
        p1.x = cvRound(line[2] - line[0] * t);
        p1.y = cvRound(line[3] - line[1] * t);
        p2.x = cvRound(line[2] + line[0] * t);
        p2.y = cvRound(line[3] + line[1] * t);
        cv::line(edgeImg, P1, P2, RED, 4);
        cv::line(edgeImg, p1, p2, GREEN, 4);
    }

    void ImgProc::preBlade(
        const cv::Mat& src,
        cv::Mat& dst
        )
    {
        // smooth the img to remove noise
        cv::GaussianBlur(src, dst, cv::Size(9, 9), 1.5, 2);
    }

    void ImgProc::detBlade(
        const cv::Mat& image,
        const cv::Vec4f& line,
        const int& winSize,
        std::vector<cv::Point>& brokenPos,
        std::vector<cv::Point>& dualPos,
        std::vector<cv::Point>& crackPos
        )
    {
        cv::Point2d direct(line[0], line[1]); direct *= 1.0 / cv::norm(direct);
        cv::Point2d point(line[2], line[3]);
        // binarize the image, "canny" from bw image can reduce a lot of noises
        cv::Mat binImg;
        double thresh = cv::threshold(image, binImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        // get the edge map from the bw image
        cv::Mat edge;
        cv::Canny(binImg, edge, thresh, 0.4 * thresh, 3);
        size_t rows = image.rows;
        size_t cols = image.cols;
        // track_path is the path for searching-windows
        std::vector<cv::Point> trackPath;
        cv::Point2f start;
        cv::Point2f end;
        //start.x = (line[0]/line[1]) * (0.0 - line[3]) + line[2];
        //start.y = 0.0;
        //end.x = (line[0]/line[1]) * (rows - line[3]) + line[2];
        //end.y = rows;
        start.x = 2520;
        start.y = 560;
        end.x = 1145;
        end.y = 1871;
        // this loop is to find the tracking path of the standard image
        cv::Point2f center;
        int steps = cv::norm(end - start) / winSize / 2;
        for(int step = 0; step < steps; ++step)
        {
            float t = (float)step / steps;
            center = start * (1 - t) + end * t;
            trackPath.push_back(cv::Point(cvRound(center.x), cvRound(center.y)));
        }
        // handle error when the track_path is empty
        if(trackPath.empty())
        {
            return;
        }
        for(std::vector<cv::Point>::const_iterator iter = trackPath.begin(); iter != trackPath.end(); ++iter)
        {
            cv::Mat disVec(0, 1, CV_64FC1);
            std::vector<cv::Point> poPts;
            std::vector<cv::Point> nePts;
            for(int y = iter->y - winSize / 2; y < iter->y + winSize / 2; ++y)
            {
                if((y < 0) || (y >= rows))
                {
                    continue;
                }
                const uchar* ptr = binImg.ptr(y);
                for(int x = iter->x - winSize / 2; x < iter->x + winSize / 2; ++x)
                {
                    if((x < 0) || (x >= cols))
                    {
                        continue;
                    }
                    if(ptr[x] > 0)
                    {
                        cv::Point2d vec = cv::Point2d(x, y) - point;
                        vec = vec - direct * vec.dot(direct);
                        double dis = cv::norm(vec);
                        disVec.push_back<double>(dis);
                        if(vec.y > 0)
                        {
                            poPts.push_back(cv::Point(x, y));
                        }
                        else 
                        {
                            nePts.push_back(cv::Point(x, y));
                        }
                    }
                }
            }
            // detect broken area by standard variance, empirically set the threshold to 8.0
            cv::Mat mean;
            cv::Mat stddev;
            if(disVec.rows > 0)
            {
                // broken area detection
                cv::meanStdDev(disVec, mean, stddev);
                if((stddev.at<double>(0) >= 8) && (mean.at<double>(0) >= 30))
                {
                    brokenPos.push_back(cv::Point(iter->x, iter->y));
                }
                // dual area detection
                int dualNum = 0;
                if((poPts.size() > 0) && (nePts.size() > 0) && (disVec.rows > 0))
                {
                    for(std::vector<cv::Point>::const_iterator poIter = poPts.begin(); poIter != poPts.end(); ++poIter)
                    {
                        for(std::vector<cv::Point>::const_iterator neIter = nePts.begin(); neIter != nePts.end(); ++neIter)
                        {
                            cv::Point2d vec;
                            vec.x = poIter->x - neIter->x;
                            vec.y = poIter->y - neIter->y;
                            vec *= 1.0 / cv::norm(vec);
                            if(abs(vec.dot(direct)) < 0.12)
                            {
                                ++dualNum;
                            }
                        }
                    }
                    if(dualNum > winSize)
                    {
                        dualPos.push_back(cv::Point(iter->x, iter->y));
                    }
                }
                // crack area detection
                if(disVec.rows <= winSize / 2)
                {
                    crackPos.push_back(cv::Point(iter->x, iter->y));
                }
            }
        }
    }
}
