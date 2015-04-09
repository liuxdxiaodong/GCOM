#include "gcbutton.h"

namespace Lamp
{
    GCButton::GCButton(
        QWidget* parent
        )
        : QFrame(parent),
        iIsEnabled(false),
        iId(GCBI_Unknown)
    {
        this->iUi.setupUi(this);
        qRegisterMetaType<GCBtnId>("GCBtnId");
        this->iUi.hotKeyLbl->setPalette(QPalette(DISABLED_COLOR));
        this->setEnabled(false);
    }

    GCButton::~GCButton()
    {
    }

    void GCButton::initButton(
        const GCBtnId& id,
        const QString& icon,
        const QString& title,
        const QString& hotKey
        )
    {
        this->iId = id;
        this->iUi.iconLbl->setPixmap(QPixmap(icon));
        this->iUi.titleLbl->setText(title);
        this->iUi.hotKeyLbl->setText(hotKey);
        this->setEnabled(true);
    }

    void GCButton::resetButton()
    {
        this->iId = GCBI_Unknown;
        this->iUi.iconLbl->setPixmap(QPixmap());
        this->iUi.titleLbl->setText(tr(""));
        this->iUi.hotKeyLbl->setText(tr(""));
        this->iIsEnabled = false;
        this->iUi.hotKeyLbl->setPalette(QPalette(DISABLED_COLOR));
        this->setEnabled(false);
    }

    void GCButton::mousePressEvent(QMouseEvent* event)
    {
        this->setFrameShadow(QFrame::Sunken);
        emit this->pressed(this->iId);
    }

    void GCButton::mouseReleaseEvent(QMouseEvent* event)
    {
        this->setFrameShadow(QFrame::Raised);
        if(this->iIsEnabled)
        {
            this->iIsEnabled = false;
            this->iUi.hotKeyLbl->setPalette(QPalette(DISABLED_COLOR));
        }
        else
        {
            this->iIsEnabled = true;
            this->iUi.hotKeyLbl->setPalette(QPalette(ENABLED_COLOR));
        }
        emit this->released(this->iId);
        emit this->clicked(this->iId);
    }
}
