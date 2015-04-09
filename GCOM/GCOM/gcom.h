#ifndef LAMP_GCOM_H
#define LAMP_GCOM_H

#include "../ImageView/imagedef.h"
#include "uidef.h"
#include "ui_gcom.h"
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QMutex>
#include <QtCore/QSettings>
#include <QtCore/QStringList>
#include <QtCore/QTextStream>
#include <QtCore/QTimer>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QFileDialog>
#include <QtGui/QMainWindow>
#include <QtGui/QMessageBox>
#include <QtGui/QtEvents>

namespace Lamp
{
    class CamBox;
    class ComPort;
    class NCEngine;

    class GCOM : public QMainWindow
    {
        Q_OBJECT

    signals:
        void imgRecv();

    public:
        GCOM(
            QWidget* parent = 0,
            Qt::WFlags flags = 0
            );
        ~GCOM();

    public slots:
        void recvImg(
            const cv::Mat* image
            );
        void updateImg();
        void gtClicked(GTBtnId id);
        void gcClicked(GCBtnId id);
        void quit();
        void help();
        void about();
        void xAxis(double value);
        void aAxis(double value);
        void yAxis(double value);
        void bAxis(double value);
        void zAxis(double value);
        void cAxis(double value);
        void runNC();
        void recImg();
        void loadImg();
        void runEdge();
        void runBlade();
        void runImg();
        void changeFPS();

    private:
        void openCom();
        void closeCom();
        void openCam();
        void closeCam();
        void openNC();
        void closeNC();
        void initToolBtn();
        void resetTooBtn();
        void initAxisBtn();
        void initCtrlBtn();
        void resetCtrlBtn();
        void swtichToMain();
        void swtichToSelectCutter();
        void swtichToMeasureCutter();
        void swtichToSwitchWindow();
        void swtichToOperateCAD();
        void loadImg(
            const QString& dirName
            );

    private:
        Ui::GCOMClass iUi;
        ComPort* iComPort;
        ULONG iIdMap[2];
        CamBox* iCamBox;
        ImgData iImgData;
        NCEngine* iNCEngine;
        bool iRecImg;
        int iImgIdx;
        QTimer iImgTimer;
        std::vector<cv::Mat> iImgs;
    };
}

#endif // LAMP_GCOM_H
