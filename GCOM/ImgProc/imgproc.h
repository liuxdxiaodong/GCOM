#ifndef LAMP_IMGPROC_H
#define LAMP_IMGPROC_H

#include "imgproc_global.h"

namespace Lamp
{
    // color
    const cv::Scalar WHITE(255, 255, 255);
    const cv::Scalar BLACK(0, 0, 0);
    const cv::Scalar RED(0, 0, 255);
    const cv::Scalar DARK_RED(0, 0, 128);
    const cv::Scalar GREEN(0, 255, 0);
    const cv::Scalar DARK_GREEN(0, 128, 0);
    //const cv::Scalar BLUE(255, 0, 0);
    const cv::Scalar BLUE(255, 128, 0);
    const cv::Scalar DARK_BLUE(128, 0, 0);
    const cv::Scalar CYAN(255, 255, 0);
    const cv::Scalar DARK_CYAN(128, 128, 0);
    const cv::Scalar MAGENTA(255, 0, 255);
    const cv::Scalar DARK_MAGENTA(128, 0, 128);
    const cv::Scalar YELLOW(0, 255, 255);
    const cv::Scalar DARK_YELLOW(0, 128, 128);
    const cv::Scalar GRAY(164, 160, 160);
    const cv::Scalar DARK_GRAY(128, 128, 128);
    const cv::Scalar LIGHT_GRAY(192, 192, 192);

    class IMGPROC_EXPORT ImgProc
    {
    private:
        ImgProc();
        ~ImgProc();

    public:
        // 找出mat中的tag并返回位置
        template<typename T>
        static void findTag(
            const cv::Mat& mat,
            T tag,
            std::vector<int>& locX,
            std::vector<int>& locY
            )
        {
            for(int y = 0; y < mat.rows; ++y)
            {
                const T* ptr = mat.ptr<T>(y);
                for(int x = 0; x < mat.cols; ++x)
                {
                    if(ptr[x] == tag)
                    {
                        locX.push_back(x);
                        locY.push_back(y);
                    }
                }
            }
        }
        // 返回一个升序排序的非重复向量
        template<typename T>
        static void unique(
            const cv::Mat& src,
            cv::Mat& dst
            )
        {
            cv::Mat tmp;
            cv::sort(src, tmp, CV_SORT_ASCENDING);
            T* ptr = (T*)tmp.data;
            T value = *ptr;
            dst.push_back<T>(value);
            for(int x = 1; x < tmp.rows; ++x)
            {
                ++ptr;
                if(*ptr != value)
                {
                    value = *ptr;
                    dst.push_back<T>(value);
                }
            }
        }
        // 填充value边界
        template<typename T>
        static void mopEdge(
            cv::Mat& img,
            T value
            )
        {
            for(int x = 0; x < img.cols; ++x)
            {
                img.at<T>(0, x) = value;
                img.at<T>(1, x) = value;
                img.at<T>(img.rows - 1, x) = value;
                img.at<T>(img.rows - 2, x) = value;
            }
            for(int y = 0; y < img.rows; ++y)
            {
                img.at<T>(y, 0) = value;
                img.at<T>(y, 1) = value;
                img.at<T>(y, img.cols - 1) = value;
                img.at<T>(y, img.cols - 2) = value;
            }
        }
        static void copyEdge(
            const cv::Mat& srcStdImg,
            const cv::Mat& srcChkImg,
            cv::Mat& dstStdImg,
            cv::Mat& dstChkImg
            );
        // L0图像平滑
        static void l0Smooth(
            const cv::Mat& src,
            cv::Mat& dst,
            double kappa = 2,
            double lambda = 0.03,
            double betaMax = 100000
            );
        static void preProc(
            const cv::Mat& stand,
            const cv::Mat& image,
            cv::Mat& stdImg,
            cv::Mat& chkImg
            );
        static void pca2D(
            const std::vector<int>& winLocX1,
            const std::vector<int>& winLocY1,
            const std::vector<int>& winLocX2,
            const std::vector<int>& winLocY2,
            int& crack,
            int& dual,
            int& broken
            );
        static void pcaCheck(
            const cv::Mat& stand,
            const cv::Mat& image,
            cv::Mat& edge,
            std::vector<int>& crack,
            std::vector<int>& dual,
            std::vector<int>& broken,
            cv::Mat& crackPos,
            cv::Mat& dualPos,
            cv::Mat& brokenPos
            );
        static void valueFocus(
            const cv::Mat& image,
            cv::Rect roi,
            int norm,
            double& focus
            );
        static void preEdge(
            const cv::Mat& src,
            cv::Mat& dst
            );
        static void extContour(
            const cv::Mat& image,
            cv::vector<cv::vector<cv::Point>>& contours,
            cv::vector<cv::Point>& globalContour
            );
        static void fitEdge(
            const cv::Size& size,
            const cv::vector<cv::Point>& globalContour,
            cv::Vec4f& line,
            cv::Mat& edgeImg
            );
        static void preBlade(
            const cv::Mat& src,
            cv::Mat& dst
            );
        static void detBlade(
            const cv::Mat& image,
            const cv::Vec4f& line,
            const int& winSize,
            std::vector<cv::Point>& brokenPos,
            std::vector<cv::Point>& dualPos,
            std::vector<cv::Point>& crackPos
            );
    };
}

#endif // LAMP_IMGPROC_H
