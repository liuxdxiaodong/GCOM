#include "imageview.h"
#include "../CamBox/camcfg.h"
#include "../ImgProc/imgproc.h"

namespace Lamp
{
    ImageView::ImageView(
        QWidget* parent
        )
        : QGraphicsView(parent),
        iScale(0.25),
        iImgScene(NULL),
        iPixmapItem(NULL),
        iActType(AT_Unknown)
    {
        this->iUi.setupUi(this);
        this->iImgData.iOriImg = cv::Mat::zeros(CamCfg::IMAGE_HEIGHT, CamCfg::IMAGE_WIDTH, CV_8UC1);
        this->iImgData.iMdfImg = cv::Mat::zeros(CamCfg::IMAGE_HEIGHT, CamCfg::IMAGE_WIDTH, CV_8UC1);
        this->iImgData.iDspImg = cv::Mat::zeros(CamCfg::ZOOM_IMAGE_HEIGHT, CamCfg::ZOOM_IMAGE_WIDTH, CV_8UC1);
        QImage image(this->iImgData.iDspImg.data, CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT, QImage::Format_Indexed8);
        this->iImgScene = new QGraphicsScene(this);
        this->setScene(this->iImgScene);
        this->iPixmapItem = this->iImgScene->addPixmap(QPixmap::fromImage(image));
        connect(this, SIGNAL(imgRecv()), this, SLOT(updateImg()), Qt::QueuedConnection);
    }

    ImageView::~ImageView()
    {
        delete this->iImgScene;
    }

    void ImageView::zoom(
        double scale
        )
    {
        if(0 == this->iImgData.iOriImg.size().area())
        {
            return;
        }
        if(scale > 1)
        {
            this->iScale = 1;
        }
        else if(scale < 0.25)
        {
            this->iScale = 0.25;
        }
        else
        {
            this->iScale = scale;
        }
        int oriW = this->iImgData.iOriImg.cols;
        int oriH = this->iImgData.iOriImg.rows;
        int dspW = cvRound(oriW * scale);
        int dspH = cvRound(oriH * scale);
        this->iScale = scale;
        cv::resize(this->iImgData.iMdfImg, this->iImgData.iDspImg, cv::Size(dspW, dspH), 0, 0, cv::INTER_NEAREST);
        QImage image(this->iImgData.iDspImg.data, dspW, dspH, QImage::Format_Indexed8);
        this->iImgScene->setSceneRect(0, 0, dspW, dspH);
        this->iPixmapItem->setPixmap(QPixmap::fromImage(image));
    }

    void ImageView::zoomFit()
    {
        this->zoom(0.25);
    }

    void ImageView::zoomIn()
    {
        this->zoom(this->iScale * 2);
    }

    void ImageView::zoomOut()
    {
        this->zoom(this->iScale / 2);
    }

    void ImageView::recvImg(
        const cv::Mat* image
        )
    {
        CopyMemory(this->iImgData.iOriImg.data, image->data, CamCfg::IMAGE_LENGTH);
        emit this->imgRecv();
    }

    void ImageView::updateImg()
    {
        CopyMemory(this->iImgData.iMdfImg.data, this->iImgData.iOriImg.data, CamCfg::IMAGE_LENGTH);
        switch(this->iActType)
        {
        case AT_Edge:
            {
                cv::Mat preImg;
                ImgProc::preEdge(this->iImgData.iMdfImg, preImg);
                cv::vector<cv::vector<cv::Point>> contours;
                ImgProc::extContour(preImg, contours, this->iGlobalContour);
                cv::Mat edgeImg;
                cv::cvtColor(this->iImgData.iMdfImg, edgeImg, CV_GRAY2BGR);
                cv::drawContours(edgeImg, contours, -1, RED, 4);
                cv::drawContours(this->iEdgeImg, contours, -1, BLUE, 4);
                cv::resize(edgeImg, this->iImgData.iDspImg, cv::Size(CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT), 0, 0, cv::INTER_NEAREST);
                QImage image(this->iImgData.iDspImg.data, CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT, QImage::Format_RGB888);
                this->iImgScene->setSceneRect(0, 0, CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT);
                this->iPixmapItem->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
            }
            break;
        case AT_Blade:
            {
                cv::Mat preImg;
                ImgProc::preBlade(this->iImgData.iMdfImg, preImg);
                const cv::Vec4f line(-0.7150, 0.6991, 2590, 493);
                const int winSize = 64;
                std::vector<cv::Point> brokenPos;
                std::vector<cv::Point> dualPos;
                std::vector<cv::Point> crackPos;
                ImgProc::detBlade(preImg, line, winSize, brokenPos, dualPos, crackPos);
                cv::Mat bladeImg;
                cv::cvtColor(this->iImgData.iMdfImg, bladeImg, CV_GRAY2BGR);
                cv::line(bladeImg, cv::Point(2590, 493), cv::Point(1072, 1942), YELLOW, 4);
                for(std::vector<cv::Point>::const_iterator ptIter = brokenPos.begin(); ptIter != brokenPos.end(); ++ptIter)
                {
                    cv::rectangle(bladeImg, cv::Rect(ptIter->x - winSize / 2, ptIter->y - winSize / 2, winSize, winSize), BLUE, 4);
                    cv::circle(bladeImg, *ptIter, 8, BLUE, 4);
                }
                for(std::vector<cv::Point>::const_iterator ptIter = dualPos.begin(); ptIter != dualPos.end(); ++ptIter)
                {
                    cv::rectangle(bladeImg, cv::Rect(ptIter->x - winSize / 2, ptIter->y - winSize / 2, winSize, winSize), GREEN, 4);
                    cv::circle(bladeImg, *ptIter, 8, GREEN, 4);
                }
                for(std::vector<cv::Point>::const_iterator ptIter = crackPos.begin(); ptIter != crackPos.end(); ++ptIter)
                {
                    cv::rectangle(bladeImg, cv::Rect(ptIter->x - winSize / 2, ptIter->y - winSize / 2, winSize, winSize), RED, 4);
                    cv::circle(bladeImg, *ptIter, 8, RED, 4);
                }
                cv::resize(bladeImg, this->iImgData.iDspImg, cv::Size(CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT), 0, 0, cv::INTER_NEAREST);
                QImage image(this->iImgData.iDspImg.data, CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT, QImage::Format_RGB888);
                this->iImgScene->setSceneRect(0, 0, CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT);
                this->iPixmapItem->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
            }
            break;
        default:
            this->zoom(this->iScale);
            break;
        }
    }

    void ImageView::clear()
    {
        this->iImgData.iOriImg = cv::Mat::zeros(CamCfg::IMAGE_HEIGHT, CamCfg::IMAGE_WIDTH, CV_8UC1);
        this->updateImg();
    }

    ActType ImageView::getActType() const
    {
        return this->iActType;
    }

    void ImageView::setActType(ActType type)
    {
        this->iActType = type;
        switch(type)
        {
        case AT_Edge:
            {
                this->iEdgeImg = cv::Mat::zeros(CamCfg::IMAGE_HEIGHT, CamCfg::IMAGE_WIDTH, CV_8UC3);
                this->iGlobalContour.clear();
                for(int y = 0; y < CamCfg::IMAGE_HEIGHT; ++y)
                {
                    this->iGlobalContour.push_back(cv::Point(0, y));
                }
            }
            break;
        case AT_Blade:
            {
            }
            break;
        default:
            break;
        }
    }

    void ImageView::fitEdge()
    {
        cv::Vec4f line;
        ImgProc::fitEdge(cv::Size(CamCfg::IMAGE_WIDTH, CamCfg::IMAGE_HEIGHT), this->iGlobalContour, line, this->iEdgeImg);
        cv::resize(this->iEdgeImg, this->iImgData.iDspImg, cv::Size(CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT), 0, 0, cv::INTER_NEAREST);
        QImage image(this->iImgData.iDspImg.data, CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT, QImage::Format_RGB888);
        this->iImgScene->setSceneRect(0, 0, CamCfg::ZOOM_IMAGE_WIDTH, CamCfg::ZOOM_IMAGE_HEIGHT);
        this->iPixmapItem->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
    }
}
