/********************************************************************************
** Form generated from reading UI file 'imageview.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEW_H
#define UI_IMAGEVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ImageView
{
public:

    void setupUi(QGraphicsView *ImageView)
    {
        if (ImageView->objectName().isEmpty())
            ImageView->setObjectName(QString::fromUtf8("ImageView"));
        ImageView->resize(642, 514);

        retranslateUi(ImageView);

        QMetaObject::connectSlotsByName(ImageView);
    } // setupUi

    void retranslateUi(QGraphicsView *ImageView)
    {
        ImageView->setWindowTitle(QApplication::translate("ImageView", "ImageView", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageView: public Ui_ImageView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEW_H
