#include "gtbutton.h"

namespace Lamp
{
    GTButton::GTButton(QWidget *parent)
        : QFrame(parent),
        iId(GTBI_Unknown)
    {
        this->iUi.setupUi(this);
        qRegisterMetaType<GTBtnId>("GTBtnId");
        this->setEnabled(false);
    }

    GTButton::~GTButton()
    {
    }

    void GTButton::initButton(
        const GTBtnId& id,
        const QString& icon
        )
    {
        this->iId = id;
        this->iUi.iconLbl->setPixmap(QPixmap(icon));
        this->setEnabled(true);
    }

    void GTButton::resetButton()
    {
        this->iId = GTBI_Unknown;
        this->iUi.iconLbl->setPixmap(QPixmap());
        this->setEnabled(false);
    }

    void GTButton::mousePressEvent(QMouseEvent* event)
    {
        this->setFrameShadow(QFrame::Sunken);
        emit this->pressed(this->iId);
    }

    void GTButton::mouseReleaseEvent(QMouseEvent* event)
    {
        this->setFrameShadow(QFrame::Raised);
        emit this->released(this->iId);
        emit this->clicked(this->iId);
    }
}
