#ifndef LAMP_GTBUTTON_H
#define LAMP_GTBUTTON_H

#include "uidef.h"
#include "ui_gtbutton.h"
#include <QtGui/QFrame>
#include <QtGui/QtEvents>

namespace Lamp
{
    class GTButton : public QFrame
    {
        Q_OBJECT

    signals:
        void pressed(GTBtnId id);
        void released(GTBtnId id);
        void clicked(GTBtnId id);

    public:
        GTButton(
            QWidget* parent = 0
            );
        ~GTButton();

    public:
        void initButton(
            const GTBtnId& id,
            const QString& icon
            );
        void resetButton();

    protected:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);

    private:
        Ui::GTButton iUi;
        GTBtnId iId;
    };
}

#endif // LAMP_GTBUTTON_H
