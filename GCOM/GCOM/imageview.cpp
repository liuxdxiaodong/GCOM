#include "imageview.h"
#include "../CamBox/camcfg.h"

namespace Lamp
{
    ImageView::ImageView(
        QWidget* parent
        )
        : QGraphicsView(parent),
        iScale(1),
        iImgScene(NULL),
        iPixmapItem(NULL)
    {
        this->iUi.setupUi(this);
        this->iImgScene = new QGraphicsScene(this);
        this->setScene(this->iImgScene);
        this->iPixmapItem = this->iImgScene->addPixmap(QPixmap());
    }

    ImageView::~ImageView()
    {
        delete this->iImgScene;
    }

    void ImageView::zoom(
        double scale
        )
    {
        this->iImgMutex.lock();
        if(scale > 8)
        {
            this->iScale = 8;
        }
        else if(scale < 0.125)
        {
            this->iScale = 0.125;
        }
        else
        {
            this->iScale = scale;
        }
        int width = cvRound(CamCfg::IMAGE_WIDTH * this->iScale);
        int height = cvRound(CamCfg::IMAGE_HEIGHT * this->iScale);
        cv::resize(*this->iOriImgRef, this->iMdfImg, cv::Size(width, height), 0, 0, cv::INTER_NEAREST);
        this->iDspImg = QImage(this->iMdfImg.data, width, height, QImage::Format_Indexed8);
        this->iImgScene->setSceneRect(this->iDspImg.rect());
        this->iPixmapItem->setPixmap(QPixmap::fromImage(this->iDspImg));
        this->iImgMutex.unlock();
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

    void ImageView::updateImage(const cv::Mat* image)
    {
        this->iImgMutex.lock();
        this->iOriImgRef = image;
        int width = cvRound(CamCfg::IMAGE_WIDTH * this->iScale);
        int height = cvRound(CamCfg::IMAGE_HEIGHT * this->iScale);
        cv::resize(*this->iOriImgRef, this->iMdfImg, cv::Size(width, height), 0, 0, cv::INTER_NEAREST);
        this->iDspImg = QImage(this->iMdfImg.data, width, height, QImage::Format_Indexed8);
        this->iImgScene->setSceneRect(this->iDspImg.rect());
        this->iPixmapItem->setPixmap(QPixmap::fromImage(this->iDspImg));
        this->iImgMutex.unlock();
    }
}
