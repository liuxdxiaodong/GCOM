#ifndef LAMP_IMAGEVIEW_H
#define LAMP_IMAGEVIEW_H

#include "imageview_global.h"
#include "imagedef.h"
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
    class IMAGEVIEW_EXPORT ImageView : public QGraphicsView
    {
        Q_OBJECT

    signals:
        void imgRecv();

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
        void recvImg(
            const cv::Mat* image
            );
        void updateImg();

    public:
        void clear();
        ActType getActType() const;
        void setActType(ActType type);
        void fitEdge();

    private:
        Ui::ImageView iUi;
        double iScale;
        ImgData iImgData;
        QGraphicsScene* iImgScene;
        QGraphicsPixmapItem* iPixmapItem;
        ActType iActType;
        // for edge
        cv::Mat iEdgeImg;
        cv::vector<cv::Point> iGlobalContour;
    };
}

#endif // LAMP_IMAGEVIEW_H
