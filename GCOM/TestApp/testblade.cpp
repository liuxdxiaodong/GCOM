#include "testblade.h"

namespace Lamp
{
    const std::string imgDir = "F:\\cutter\\code\\data\\sample\\";
    const std::string headName = "a1";
    const std::string oriImgName = imgDir + headName + "_ori.jpg";
    const std::string stdImgName = imgDir + headName + "_std.jpg";
    const std::string resImgName = imgDir + headName + "_res.jpg";

    int testBlade(int argc, char* argv[])
    {
        cv::Mat stand = cv::imread(stdImgName);
        cv::Mat image = cv::imread(oriImgName);
        int rows = image.rows;
        int cols = image.cols;
        cv::Size size = image.size();
        cv::Mat edge;
        // 0：正常
        // 1：蹦损
        std::vector<int> crack;
        std::vector<int> dual;
        std::vector<int> broken;
        // 窗口中心位置
        cv::Mat crackPos;
        cv::Mat dualPos;
        cv::Mat brokenPos;
        ImgProc::pcaCheck(stand, image, edge, crack, dual, broken, crackPos, dualPos, brokenPos);
        cv::Mat result = image.clone();
        for(int y = 0; y < rows; ++y)
        {
            const uchar* ePtr = edge.ptr(y);
            uchar* rPtr = result.ptr(y);
            for(int x = 0; x < cols; ++x)
            {
                if(ePtr[x] == 255)
                {
                    rPtr[x * 3 + 0] = 0;
                    rPtr[x * 3 + 1] = 0;
                    rPtr[x * 3 + 2] = 255;
                }
            }
        }
        for(size_t idx = 0; idx < crack.size(); ++idx)
        {
            if(crack[idx])
            {
                std::cout << "Crack X: " << crackPos.at<int>(idx, 0) << " Y: " << crackPos.at<int>(idx, 1) << std::endl;
                cv::circle(result, cv::Point(crackPos.at<int>(idx, 0), crackPos.at<int>(idx, 1)), 5, WHITE, 2);
            }
        }
        for(size_t idx = 0; idx < dual.size(); ++idx)
        {
            if(dual[idx])
            {
                std::cout << "Dual X: " << dualPos.at<int>(idx, 0) << " Y: " << dualPos.at<int>(idx, 1) << std::endl;
                cv::circle(result, cv::Point(dualPos.at<int>(idx, 0), dualPos.at<int>(idx, 1)), 5, BLACK, 2);
            }
        }
        for(size_t idx = 0; idx < broken.size(); ++idx)
        {
            if(broken[idx])
            {
                std::cout << "Broken X: " << brokenPos.at<int>(idx, 0) << " Y: " << brokenPos.at<int>(idx, 1) << std::endl;
                cv::circle(result, cv::Point(brokenPos.at<int>(idx, 0), brokenPos.at<int>(idx, 1)), 5, BLUE, 2);
            }
        }
        cv::imwrite(resImgName, result);
        cv::imshow("result", result);
        cv::waitKey();
        return 0;
    }
}
