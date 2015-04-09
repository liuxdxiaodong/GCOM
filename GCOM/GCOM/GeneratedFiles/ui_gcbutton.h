/********************************************************************************
** Form generated from reading UI file 'gcbutton.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GCBUTTON_H
#define UI_GCBUTTON_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_GCButton
{
public:
    QLabel *hotKeyLbl;
    QLabel *iconLbl;
    QLabel *titleLbl;

    void setupUi(QFrame *GCButton)
    {
        if (GCButton->objectName().isEmpty())
            GCButton->setObjectName(QString::fromUtf8("GCButton"));
        GCButton->resize(105, 105);
        GCButton->setMinimumSize(QSize(105, 105));
        GCButton->setMaximumSize(QSize(105, 105));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        GCButton->setFont(font);
        GCButton->setFrameShape(QFrame::WinPanel);
        GCButton->setFrameShadow(QFrame::Raised);
        hotKeyLbl = new QLabel(GCButton);
        hotKeyLbl->setObjectName(QString::fromUtf8("hotKeyLbl"));
        hotKeyLbl->setGeometry(QRect(80, 80, 20, 20));
        hotKeyLbl->setAutoFillBackground(true);
        hotKeyLbl->setFrameShape(QFrame::WinPanel);
        hotKeyLbl->setFrameShadow(QFrame::Sunken);
        hotKeyLbl->setAlignment(Qt::AlignCenter);
        iconLbl = new QLabel(GCButton);
        iconLbl->setObjectName(QString::fromUtf8("iconLbl"));
        iconLbl->setGeometry(QRect(5, 5, 96, 64));
        iconLbl->setScaledContents(true);
        iconLbl->setAlignment(Qt::AlignCenter);
        titleLbl = new QLabel(GCButton);
        titleLbl->setObjectName(QString::fromUtf8("titleLbl"));
        titleLbl->setGeometry(QRect(5, 70, 75, 30));
        titleLbl->setAlignment(Qt::AlignCenter);

        retranslateUi(GCButton);

        QMetaObject::connectSlotsByName(GCButton);
    } // setupUi

    void retranslateUi(QFrame *GCButton)
    {
        GCButton->setWindowTitle(QApplication::translate("GCButton", "GCButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GCButton: public Ui_GCButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCBUTTON_H
