#include "sqleextend.h"

sQLEExtend::sQLEExtend(QWidget *parent) :
    QLineEdit(parent)
{
    this->setContextMenuPolicy(Qt::NoContextMenu);

    cTimer = new QTimer(this);
    cKeydown = 0;
    connect(cTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
}

sQLEExtend::~sQLEExtend()
{

}

void sQLEExtend::mousePressEvent(QMouseEvent *event)
{
    if(!this->isReadOnly())
    {
        cTimer->start(2000);
        cKeydown = 1;
    }

    QLineEdit::mousePressEvent(event);
    emit click();
}

void sQLEExtend::mouseReleaseEvent(QMouseEvent *event)
{
    if(!this->isReadOnly())
    {
        cKeydown = 0;
        if(cTimer->isActive()) cTimer->stop();
    }

    QLineEdit::mousePressEvent(event);

}

void sQLEExtend::onTimeOut()
{
    cTimer->stop();
    if(cKeydown) emit showKeypad(1);
}
