#include "scleaning.h"
#include "ui_scleaning.h"

sCleaning::sCleaning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sCleaning)
{
    ui->setupUi(this);

    ui->pbRun->setEnabled(true);

    cRunState = false;

}

sCleaning::~sCleaning()
{
    delete ui;
}

void sCleaning::onLiveData(int tm, int pr)
{
    if(ui->lblTemperature->isVisible()) 
    {
        QString str;
        str = cSettings.getTemperatureLiveSS(tm);
        ui->lblTemperature->setText(str);
        str = cSettings.getPressureLiveSS(tm, pr);
        ui->lblPressure->setText(str);
    }
}

void sCleaning::Show()
{
    ui->lblCountDown->hide();
    setRunning(false);
    this->show();
}

void sCleaning::setRunning(bool tmp)
{
    cRunState = tmp;

    switch(tmp)
    {
        case 0:
                ui->pbRun->setEnabled(true);
                ui->pbStop->setEnabled(false);
                ui->lblCountDown->hide();
                break;
        case 1:
                ui->pbRun->setEnabled(false);
                ui->pbStop->setEnabled(true);
                break;
    }
}

void sCleaning::updateStatus(int current, int total)
{
    QString str;
    str = tr("Current Cycle:") + QString::number(current) + "/"
            + QString::number(total);
    ui->lblCountDown->setText(str);
    ui->lblCountDown->show();
}

void sCleaning::setWaitACKStatus(bool tmp)
{
    if(!cRunState) ui->pbRun->setEnabled(!tmp);
}

bool sCleaning::getWaitACKStatus()
{
    return true;
}

void sCleaning::hideAfterACK(bool tmp)
{

}

bool sCleaning::getHideAfterACK()
{
    return false;
}

void sCleaning::on_pbRun_clicked()
{
    emit runClicked(MS_RINSING_RUN, false);
}

void sCleaning::on_pbStop_clicked()
{
    emit runClicked(MS_RINSING_STOP, false);

    // 18-Apr-2023 this->hide();
    // 18-Apr-2023 emit showHome(false);
}

void sCleaning::on_pbHome_clicked()
{
    this->hide();
    emit showHome(false);
}
