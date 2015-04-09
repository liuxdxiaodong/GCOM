#ifndef LAMP_GCBUTTON_H
#define LAMP_GCBUTTON_H

#include "uidef.h"
#include "ui_gcbutton.h"
#include <QtGui/QFrame>
#include <QtGui/QtEvents>

namespace Lamp
{
    class GCButton : public QFrame
    {
        Q_OBJECT

    signals:
        void pressed(GCBtnId id);
        void released(GCBtnId id);
        void clicked(GCBtnId id);

    public:
        GCButton(
            QWidget* parent = 0
            );
        ~GCButton();

    public:
        void initButton(
            const GCBtnId& id,
            const QString& icon,
            const QString& title,
            const QString& hotKey
            );
        void resetButton();

    protected:
        virtual void mousePressEvent(QMouseEvent* event);
        virtual void mouseReleaseEvent(QMouseEvent* event);

    private:
        Ui::GCButton iUi;
        bool iIsEnabled;
        GCBtnId iId;
    };
}

#endif // LAMP_GCBUTTON_H
