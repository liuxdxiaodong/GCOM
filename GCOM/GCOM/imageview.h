#ifndef LAMP_IMAGEVIEW_H
#define LAMP_IMAGEVIEW_H

#include "uidef.h"
#include "ui_imageview.h"
#include <QtCore/QMutex>
#include <QtGui/QGraphicsPixmapItem>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QtEvents>

namespace Lamp
{
    class ImageView : public QGraphicsView
    {
        Q_OBJECT

    public:
        ImageView(
            QWidget* parent = 0
            );
        ~ImageView();

    public slots:
        void zoom(
            double scale
            );
        void zoomFit();
        void zoomIn();
        void zoomOut();

    public:
        void updateImage(const cv::Mat* image);

    private:
        Ui::ImageView iUi;
        QMutex iImgMutex;
        double iScale;
        const cv::Mat* iOriImgRef;
        cv::Mat iMdfImg;
        QImage iDspImg;
        QGraphicsScene* iImgScene;
        QGraphicsPixmapItem* iPixmapItem;
    };
}

#endif // LAMP_IMAGEVIEW_H
