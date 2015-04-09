/********************************************************************************
** Form generated from reading UI file 'gcom.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GCOM_H
#define UI_GCOM_H

#include <../ImageView/imageview.h>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>
#include <gcbutton.h>
#include <gtbutton.h>

QT_BEGIN_NAMESPACE

class Ui_GCOMClass
{
public:
    QAction *actQuit;
    QAction *actHelp;
    QAction *actAbout;
    QWidget *centralWidget;
    QTabWidget *viewTabFrm;
    QWidget *camTab;
    Lamp::ImageView *camView;
    Lamp::GTButton *t1Btn;
    Lamp::GTButton *t2Btn;
    Lamp::GTButton *t3Btn;
    Lamp::GTButton *t4Btn;
    Lamp::GTButton *t5Btn;
    Lamp::GTButton *t6Btn;
    Lamp::GTButton *t7Btn;
    Lamp::GTButton *t8Btn;
    Lamp::GTButton *t9Btn;
    Lamp::GTButton *t10Btn;
    Lamp::GTButton *t11Btn;
    QWidget *cadTab;
    QGraphicsView *cadView;
    QWidget *mixTab;
    QGraphicsView *mixView;
    QFrame *axisFrm;
    QLabel *xAxisLbl;
    QDoubleSpinBox *xAxisBox;
    QLabel *yAxisLbl;
    QDoubleSpinBox *yAxisBox;
    QLabel *zAxisLbl;
    QDoubleSpinBox *zAxisBox;
    QLabel *aAxisLbl;
    QDoubleSpinBox *aAxisBox;
    QLabel *bAxisLbl;
    QDoubleSpinBox *bAxisBox;
    QLabel *cAxisLbl;
    QDoubleSpinBox *cAxisBox;
    Lamp::GTButton *upBtn;
    Lamp::GTButton *leftBtn;
    Lamp::GTButton *downBtn;
    Lamp::GTButton *rightBtn;
    QPushButton *recImgBtn;
    QPushButton *runNCBtn;
    QPushButton *loadImgBtn;
    QPushButton *runEdgeBtn;
    QPushButton *runBladeBtn;
    QSpinBox *fpsBox;
    QPushButton *fpsBtn;
    Lamp::GCButton *f1Btn;
    QTreeWidget *treeWidget;
    Lamp::GCButton *f2Btn;
    Lamp::GCButton *f3Btn;
    Lamp::GCButton *f4Btn;
    Lamp::GCButton *f5Btn;
    Lamp::GCButton *f6Btn;
    Lamp::GCButton *f7Btn;
    Lamp::GCButton *f8Btn;
    Lamp::GCButton *f9Btn;
    Lamp::GCButton *f10Btn;
    Lamp::GCButton *f11Btn;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GCOMClass)
    {
        if (GCOMClass->objectName().isEmpty())
            GCOMClass->setObjectName(QString::fromUtf8("GCOMClass"));
        GCOMClass->resize(1255, 955);
        GCOMClass->setMinimumSize(QSize(1255, 955));
        GCOMClass->setMaximumSize(QSize(1255, 955));
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI"));
        GCOMClass->setFont(font);
        actQuit = new QAction(GCOMClass);
        actQuit->setObjectName(QString::fromUtf8("actQuit"));
        actHelp = new QAction(GCOMClass);
        actHelp->setObjectName(QString::fromUtf8("actHelp"));
        actAbout = new QAction(GCOMClass);
        actAbout->setObjectName(QString::fromUtf8("actAbout"));
        centralWidget = new QWidget(GCOMClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        viewTabFrm = new QTabWidget(centralWidget);
        viewTabFrm->setObjectName(QString::fromUtf8("viewTabFrm"));
        viewTabFrm->setGeometry(QRect(5, 5, 660, 575));
        camTab = new QWidget();
        camTab->setObjectName(QString::fromUtf8("camTab"));
        camView = new Lamp::ImageView(camTab);
        camView->setObjectName(QString::fromUtf8("camView"));
        camView->setGeometry(QRect(2, 2, 650, 488));
        t1Btn = new Lamp::GTButton(camTab);
        t1Btn->setObjectName(QString::fromUtf8("t1Btn"));
        t1Btn->setGeometry(QRect(5, 495, 50, 50));
        t1Btn->setFrameShape(QFrame::WinPanel);
        t1Btn->setFrameShadow(QFrame::Raised);
        t2Btn = new Lamp::GTButton(camTab);
        t2Btn->setObjectName(QString::fromUtf8("t2Btn"));
        t2Btn->setGeometry(QRect(60, 495, 50, 50));
        t2Btn->setFrameShape(QFrame::WinPanel);
        t2Btn->setFrameShadow(QFrame::Raised);
        t3Btn = new Lamp::GTButton(camTab);
        t3Btn->setObjectName(QString::fromUtf8("t3Btn"));
        t3Btn->setGeometry(QRect(115, 495, 50, 50));
        t3Btn->setFrameShape(QFrame::WinPanel);
        t3Btn->setFrameShadow(QFrame::Raised);
        t4Btn = new Lamp::GTButton(camTab);
        t4Btn->setObjectName(QString::fromUtf8("t4Btn"));
        t4Btn->setGeometry(QRect(170, 495, 50, 50));
        t4Btn->setFrameShape(QFrame::WinPanel);
        t4Btn->setFrameShadow(QFrame::Raised);
        t5Btn = new Lamp::GTButton(camTab);
        t5Btn->setObjectName(QString::fromUtf8("t5Btn"));
        t5Btn->setGeometry(QRect(225, 495, 50, 50));
        t5Btn->setFrameShape(QFrame::WinPanel);
        t5Btn->setFrameShadow(QFrame::Raised);
        t6Btn = new Lamp::GTButton(camTab);
        t6Btn->setObjectName(QString::fromUtf8("t6Btn"));
        t6Btn->setGeometry(QRect(280, 495, 50, 50));
        t6Btn->setFrameShape(QFrame::WinPanel);
        t6Btn->setFrameShadow(QFrame::Raised);
        t7Btn = new Lamp::GTButton(camTab);
        t7Btn->setObjectName(QString::fromUtf8("t7Btn"));
        t7Btn->setGeometry(QRect(335, 495, 50, 50));
        t7Btn->setFrameShape(QFrame::WinPanel);
        t7Btn->setFrameShadow(QFrame::Raised);
        t8Btn = new Lamp::GTButton(camTab);
        t8Btn->setObjectName(QString::fromUtf8("t8Btn"));
        t8Btn->setGeometry(QRect(390, 495, 50, 50));
        t8Btn->setFrameShape(QFrame::WinPanel);
        t8Btn->setFrameShadow(QFrame::Raised);
        t9Btn = new Lamp::GTButton(camTab);
        t9Btn->setObjectName(QString::fromUtf8("t9Btn"));
        t9Btn->setGeometry(QRect(445, 495, 50, 50));
        t9Btn->setFrameShape(QFrame::WinPanel);
        t9Btn->setFrameShadow(QFrame::Raised);
        t10Btn = new Lamp::GTButton(camTab);
        t10Btn->setObjectName(QString::fromUtf8("t10Btn"));
        t10Btn->setGeometry(QRect(500, 495, 50, 50));
        t10Btn->setFrameShape(QFrame::WinPanel);
        t10Btn->setFrameShadow(QFrame::Raised);
        t11Btn = new Lamp::GTButton(camTab);
        t11Btn->setObjectName(QString::fromUtf8("t11Btn"));
        t11Btn->setGeometry(QRect(555, 495, 50, 50));
        t11Btn->setFrameShape(QFrame::WinPanel);
        t11Btn->setFrameShadow(QFrame::Raised);
        viewTabFrm->addTab(camTab, QString());
        cadTab = new QWidget();
        cadTab->setObjectName(QString::fromUtf8("cadTab"));
        cadView = new QGraphicsView(cadTab);
        cadView->setObjectName(QString::fromUtf8("cadView"));
        cadView->setGeometry(QRect(2, 2, 650, 488));
        viewTabFrm->addTab(cadTab, QString());
        mixTab = new QWidget();
        mixTab->setObjectName(QString::fromUtf8("mixTab"));
        mixView = new QGraphicsView(mixTab);
        mixView->setObjectName(QString::fromUtf8("mixView"));
        mixView->setGeometry(QRect(2, 2, 650, 488));
        viewTabFrm->addTab(mixTab, QString());
        axisFrm = new QFrame(centralWidget);
        axisFrm->setObjectName(QString::fromUtf8("axisFrm"));
        axisFrm->setGeometry(QRect(5, 585, 660, 215));
        QFont font1;
        font1.setPointSize(12);
        axisFrm->setFont(font1);
        axisFrm->setFrameShape(QFrame::Box);
        axisFrm->setFrameShadow(QFrame::Sunken);
        xAxisLbl = new QLabel(axisFrm);
        xAxisLbl->setObjectName(QString::fromUtf8("xAxisLbl"));
        xAxisLbl->setGeometry(QRect(5, 5, 30, 30));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        xAxisLbl->setPalette(palette);
        xAxisLbl->setAlignment(Qt::AlignCenter);
        xAxisBox = new QDoubleSpinBox(axisFrm);
        xAxisBox->setObjectName(QString::fromUtf8("xAxisBox"));
        xAxisBox->setGeometry(QRect(40, 5, 150, 30));
        xAxisBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        xAxisBox->setDecimals(3);
        xAxisBox->setMinimum(-100000);
        xAxisBox->setMaximum(100000);
        xAxisBox->setSingleStep(0.001);
        yAxisLbl = new QLabel(axisFrm);
        yAxisLbl->setObjectName(QString::fromUtf8("yAxisLbl"));
        yAxisLbl->setGeometry(QRect(5, 75, 30, 30));
        QPalette palette1;
        QBrush brush2(QColor(0, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        yAxisLbl->setPalette(palette1);
        yAxisLbl->setAlignment(Qt::AlignCenter);
        yAxisBox = new QDoubleSpinBox(axisFrm);
        yAxisBox->setObjectName(QString::fromUtf8("yAxisBox"));
        yAxisBox->setGeometry(QRect(40, 75, 150, 30));
        yAxisBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        yAxisBox->setDecimals(3);
        yAxisBox->setMinimum(-100000);
        yAxisBox->setMaximum(100000);
        yAxisBox->setSingleStep(0.001);
        zAxisLbl = new QLabel(axisFrm);
        zAxisLbl->setObjectName(QString::fromUtf8("zAxisLbl"));
        zAxisLbl->setGeometry(QRect(5, 145, 30, 30));
        QPalette palette2;
        QBrush brush3(QColor(0, 0, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        zAxisLbl->setPalette(palette2);
        zAxisLbl->setAlignment(Qt::AlignCenter);
        zAxisBox = new QDoubleSpinBox(axisFrm);
        zAxisBox->setObjectName(QString::fromUtf8("zAxisBox"));
        zAxisBox->setGeometry(QRect(40, 145, 150, 30));
        zAxisBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        zAxisBox->setDecimals(3);
        zAxisBox->setMinimum(-100000);
        zAxisBox->setMaximum(100000);
        zAxisBox->setSingleStep(0.001);
        aAxisLbl = new QLabel(axisFrm);
        aAxisLbl->setObjectName(QString::fromUtf8("aAxisLbl"));
        aAxisLbl->setGeometry(QRect(5, 40, 30, 30));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        aAxisLbl->setPalette(palette3);
        aAxisLbl->setAlignment(Qt::AlignCenter);
        aAxisBox = new QDoubleSpinBox(axisFrm);
        aAxisBox->setObjectName(QString::fromUtf8("aAxisBox"));
        aAxisBox->setGeometry(QRect(40, 40, 150, 30));
        aAxisBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        aAxisBox->setDecimals(3);
        aAxisBox->setMinimum(-100000);
        aAxisBox->setMaximum(100000);
        aAxisBox->setSingleStep(0.001);
        bAxisLbl = new QLabel(axisFrm);
        bAxisLbl->setObjectName(QString::fromUtf8("bAxisLbl"));
        bAxisLbl->setGeometry(QRect(5, 110, 30, 30));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        bAxisLbl->setPalette(palette4);
        bAxisLbl->setAlignment(Qt::AlignCenter);
        bAxisBox = new QDoubleSpinBox(axisFrm);
        bAxisBox->setObjectName(QString::fromUtf8("bAxisBox"));
        bAxisBox->setGeometry(QRect(40, 110, 150, 30));
        bAxisBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        bAxisBox->setDecimals(3);
        bAxisBox->setMinimum(-100000);
        bAxisBox->setMaximum(100000);
        bAxisBox->setSingleStep(0.001);
        cAxisLbl = new QLabel(axisFrm);
        cAxisLbl->setObjectName(QString::fromUtf8("cAxisLbl"));
        cAxisLbl->setGeometry(QRect(5, 180, 30, 30));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        cAxisLbl->setPalette(palette5);
        cAxisLbl->setAlignment(Qt::AlignCenter);
        cAxisBox = new QDoubleSpinBox(axisFrm);
        cAxisBox->setObjectName(QString::fromUtf8("cAxisBox"));
        cAxisBox->setGeometry(QRect(40, 180, 150, 30));
        cAxisBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cAxisBox->setDecimals(3);
        cAxisBox->setMinimum(-100000);
        cAxisBox->setMaximum(100000);
        cAxisBox->setSingleStep(0.001);
        upBtn = new Lamp::GTButton(axisFrm);
        upBtn->setObjectName(QString::fromUtf8("upBtn"));
        upBtn->setGeometry(QRect(500, 15, 50, 50));
        upBtn->setFrameShape(QFrame::WinPanel);
        upBtn->setFrameShadow(QFrame::Raised);
        leftBtn = new Lamp::GTButton(axisFrm);
        leftBtn->setObjectName(QString::fromUtf8("leftBtn"));
        leftBtn->setGeometry(QRect(435, 80, 50, 50));
        leftBtn->setFrameShape(QFrame::WinPanel);
        leftBtn->setFrameShadow(QFrame::Raised);
        downBtn = new Lamp::GTButton(axisFrm);
        downBtn->setObjectName(QString::fromUtf8("downBtn"));
        downBtn->setGeometry(QRect(500, 145, 50, 50));
        downBtn->setFrameShape(QFrame::WinPanel);
        downBtn->setFrameShadow(QFrame::Raised);
        rightBtn = new Lamp::GTButton(axisFrm);
        rightBtn->setObjectName(QString::fromUtf8("rightBtn"));
        rightBtn->setGeometry(QRect(565, 80, 50, 50));
        rightBtn->setFrameShape(QFrame::WinPanel);
        rightBtn->setFrameShadow(QFrame::Raised);
        recImgBtn = new QPushButton(axisFrm);
        recImgBtn->setObjectName(QString::fromUtf8("recImgBtn"));
        recImgBtn->setGeometry(QRect(195, 40, 80, 30));
        runNCBtn = new QPushButton(axisFrm);
        runNCBtn->setObjectName(QString::fromUtf8("runNCBtn"));
        runNCBtn->setGeometry(QRect(195, 5, 80, 30));
        loadImgBtn = new QPushButton(axisFrm);
        loadImgBtn->setObjectName(QString::fromUtf8("loadImgBtn"));
        loadImgBtn->setGeometry(QRect(195, 75, 80, 30));
        runEdgeBtn = new QPushButton(axisFrm);
        runEdgeBtn->setObjectName(QString::fromUtf8("runEdgeBtn"));
        runEdgeBtn->setGeometry(QRect(195, 110, 80, 30));
        runBladeBtn = new QPushButton(axisFrm);
        runBladeBtn->setObjectName(QString::fromUtf8("runBladeBtn"));
        runBladeBtn->setGeometry(QRect(195, 145, 80, 30));
        fpsBox = new QSpinBox(axisFrm);
        fpsBox->setObjectName(QString::fromUtf8("fpsBox"));
        fpsBox->setGeometry(QRect(280, 5, 40, 30));
        fpsBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        fpsBtn = new QPushButton(axisFrm);
        fpsBtn->setObjectName(QString::fromUtf8("fpsBtn"));
        fpsBtn->setGeometry(QRect(320, 5, 40, 30));
        f1Btn = new Lamp::GCButton(centralWidget);
        f1Btn->setObjectName(QString::fromUtf8("f1Btn"));
        f1Btn->setGeometry(QRect(5, 805, 105, 105));
        f1Btn->setFrameShape(QFrame::WinPanel);
        f1Btn->setFrameShadow(QFrame::Raised);
        treeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(670, 5, 580, 795));
        f2Btn = new Lamp::GCButton(centralWidget);
        f2Btn->setObjectName(QString::fromUtf8("f2Btn"));
        f2Btn->setGeometry(QRect(115, 805, 105, 105));
        f2Btn->setFrameShape(QFrame::WinPanel);
        f2Btn->setFrameShadow(QFrame::Raised);
        f3Btn = new Lamp::GCButton(centralWidget);
        f3Btn->setObjectName(QString::fromUtf8("f3Btn"));
        f3Btn->setGeometry(QRect(225, 805, 105, 105));
        f3Btn->setFrameShape(QFrame::WinPanel);
        f3Btn->setFrameShadow(QFrame::Raised);
        f4Btn = new Lamp::GCButton(centralWidget);
        f4Btn->setObjectName(QString::fromUtf8("f4Btn"));
        f4Btn->setGeometry(QRect(335, 805, 105, 105));
        f4Btn->setFrameShape(QFrame::WinPanel);
        f4Btn->setFrameShadow(QFrame::Raised);
        f5Btn = new Lamp::GCButton(centralWidget);
        f5Btn->setObjectName(QString::fromUtf8("f5Btn"));
        f5Btn->setGeometry(QRect(445, 805, 105, 105));
        f5Btn->setFrameShape(QFrame::WinPanel);
        f5Btn->setFrameShadow(QFrame::Raised);
        f6Btn = new Lamp::GCButton(centralWidget);
        f6Btn->setObjectName(QString::fromUtf8("f6Btn"));
        f6Btn->setGeometry(QRect(555, 805, 105, 105));
        f6Btn->setFrameShape(QFrame::WinPanel);
        f6Btn->setFrameShadow(QFrame::Raised);
        f7Btn = new Lamp::GCButton(centralWidget);
        f7Btn->setObjectName(QString::fromUtf8("f7Btn"));
        f7Btn->setGeometry(QRect(665, 805, 105, 105));
        f7Btn->setFrameShape(QFrame::WinPanel);
        f7Btn->setFrameShadow(QFrame::Raised);
        f8Btn = new Lamp::GCButton(centralWidget);
        f8Btn->setObjectName(QString::fromUtf8("f8Btn"));
        f8Btn->setGeometry(QRect(775, 805, 105, 105));
        f8Btn->setFrameShape(QFrame::WinPanel);
        f8Btn->setFrameShadow(QFrame::Raised);
        f9Btn = new Lamp::GCButton(centralWidget);
        f9Btn->setObjectName(QString::fromUtf8("f9Btn"));
        f9Btn->setGeometry(QRect(885, 805, 105, 105));
        f9Btn->setFrameShape(QFrame::WinPanel);
        f9Btn->setFrameShadow(QFrame::Raised);
        f10Btn = new Lamp::GCButton(centralWidget);
        f10Btn->setObjectName(QString::fromUtf8("f10Btn"));
        f10Btn->setGeometry(QRect(995, 805, 105, 105));
        f10Btn->setFrameShape(QFrame::WinPanel);
        f10Btn->setFrameShadow(QFrame::Raised);
        f11Btn = new Lamp::GCButton(centralWidget);
        f11Btn->setObjectName(QString::fromUtf8("f11Btn"));
        f11Btn->setGeometry(QRect(1105, 805, 105, 105));
        f11Btn->setFrameShape(QFrame::WinPanel);
        f11Btn->setFrameShadow(QFrame::Raised);
        GCOMClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GCOMClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1255, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        GCOMClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(GCOMClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GCOMClass->setStatusBar(statusBar);
        QWidget::setTabOrder(viewTabFrm, camView);
        QWidget::setTabOrder(camView, cadView);
        QWidget::setTabOrder(cadView, mixView);
        QWidget::setTabOrder(mixView, xAxisBox);
        QWidget::setTabOrder(xAxisBox, aAxisBox);
        QWidget::setTabOrder(aAxisBox, yAxisBox);
        QWidget::setTabOrder(yAxisBox, bAxisBox);
        QWidget::setTabOrder(bAxisBox, zAxisBox);
        QWidget::setTabOrder(zAxisBox, cAxisBox);
        QWidget::setTabOrder(cAxisBox, treeWidget);
        QWidget::setTabOrder(treeWidget, runNCBtn);
        QWidget::setTabOrder(runNCBtn, recImgBtn);
        QWidget::setTabOrder(recImgBtn, loadImgBtn);
        QWidget::setTabOrder(loadImgBtn, runEdgeBtn);
        QWidget::setTabOrder(runEdgeBtn, runBladeBtn);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actQuit);
        menuHelp->addAction(actHelp);
        menuHelp->addAction(actAbout);

        retranslateUi(GCOMClass);

        viewTabFrm->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GCOMClass);
    } // setupUi

    void retranslateUi(QMainWindow *GCOMClass)
    {
        GCOMClass->setWindowTitle(QApplication::translate("GCOMClass", "GCOM", 0, QApplication::UnicodeUTF8));
        actQuit->setText(QApplication::translate("GCOMClass", "Quit", 0, QApplication::UnicodeUTF8));
        actHelp->setText(QApplication::translate("GCOMClass", "Help", 0, QApplication::UnicodeUTF8));
        actAbout->setText(QApplication::translate("GCOMClass", "About", 0, QApplication::UnicodeUTF8));
        viewTabFrm->setTabText(viewTabFrm->indexOf(camTab), QApplication::translate("GCOMClass", "CAM", 0, QApplication::UnicodeUTF8));
        viewTabFrm->setTabText(viewTabFrm->indexOf(cadTab), QApplication::translate("GCOMClass", "CAD", 0, QApplication::UnicodeUTF8));
        viewTabFrm->setTabText(viewTabFrm->indexOf(mixTab), QApplication::translate("GCOMClass", "MIX", 0, QApplication::UnicodeUTF8));
        xAxisLbl->setText(QApplication::translate("GCOMClass", "X", 0, QApplication::UnicodeUTF8));
        yAxisLbl->setText(QApplication::translate("GCOMClass", "Y", 0, QApplication::UnicodeUTF8));
        zAxisLbl->setText(QApplication::translate("GCOMClass", "Z", 0, QApplication::UnicodeUTF8));
        aAxisLbl->setText(QApplication::translate("GCOMClass", "A", 0, QApplication::UnicodeUTF8));
        bAxisLbl->setText(QApplication::translate("GCOMClass", "B", 0, QApplication::UnicodeUTF8));
        cAxisLbl->setText(QApplication::translate("GCOMClass", "C", 0, QApplication::UnicodeUTF8));
        recImgBtn->setText(QApplication::translate("GCOMClass", "Rec Img", 0, QApplication::UnicodeUTF8));
        runNCBtn->setText(QApplication::translate("GCOMClass", "Run NC", 0, QApplication::UnicodeUTF8));
        loadImgBtn->setText(QApplication::translate("GCOMClass", "Load Img", 0, QApplication::UnicodeUTF8));
        runEdgeBtn->setText(QApplication::translate("GCOMClass", "Run Edge", 0, QApplication::UnicodeUTF8));
        runBladeBtn->setText(QApplication::translate("GCOMClass", "Run Blade", 0, QApplication::UnicodeUTF8));
        fpsBtn->setText(QApplication::translate("GCOMClass", "FPS", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("GCOMClass", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("GCOMClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GCOMClass: public Ui_GCOMClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCOM_H
