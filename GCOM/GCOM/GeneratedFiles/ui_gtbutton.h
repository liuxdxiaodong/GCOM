/********************************************************************************
** Form generated from reading UI file 'gtbutton.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GTBUTTON_H
#define UI_GTBUTTON_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_GTButton
{
public:
    QLabel *iconLbl;

    void setupUi(QFrame *GTButton)
    {
        if (GTButton->objectName().isEmpty())
            GTButton->setObjectName(QString::fromUtf8("GTButton"));
        GTButton->resize(100, 100);
        GTButton->setFrameShape(QFrame::WinPanel);
        GTButton->setFrameShadow(QFrame::Raised);
        iconLbl = new QLabel(GTButton);
        iconLbl->setObjectName(QString::fromUtf8("iconLbl"));
        iconLbl->setGeometry(QRect(1, 1, 48, 48));
        iconLbl->setScaledContents(true);
        iconLbl->setAlignment(Qt::AlignCenter);

        retranslateUi(GTButton);

        QMetaObject::connectSlotsByName(GTButton);
    } // setupUi

    void retranslateUi(QFrame *GTButton)
    {
        GTButton->setWindowTitle(QApplication::translate("GTButton", "GTButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GTButton: public Ui_GTButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GTBUTTON_H
