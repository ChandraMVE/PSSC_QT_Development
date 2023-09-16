#include "susersetup.h"
#include "ui_susersetup.h"

sUserSetup::sUserSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sUserSetup)
{
    ui->setupUi(this);
    setDefaults();
    cParasChanged = false;
}

sUserSetup::~sUserSetup()
{
    delete ui;
}

void sUserSetup::Show()
{
    showUserSetup();
    this->show();
}

int sUserSetup::getGMTSeconds()
{
    return ((1800*user_setup.gmt)-43200);
}

void sUserSetup::sendBuzAndVol()
{

    QString str = "#Q" + QString::number(user_setup.error_buzzer_enable ? 1:0) +
                  "," + QString::number(user_setup.alarm_vol) +
                  "$";

    emit sendCommand(str);
}

void sUserSetup::setDefaults()
{
    user_setup.alarm_vol = DEFAULT_USER_ALARM_VOL;
    user_setup.error_buzzer_enable = DEFAULT_ERROR_BUZZER_ENABLE;
    user_setup.gmt = DEFAULT_USER_GMT;
    user_setup.rinse_cycle = DEFAULT_RINSE_CYCLES;
}

bool sUserSetup::readFile()
{

    QString fname = QApplication::applicationDirPath() + FN_USER_SETUP;

    QFile in(fname);

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream save(&in);
        save >> user_setup;
        in.close();

        cParasChanged = false;
        return true;

    }
    else
    {
        setDefaults();
        cParasChanged = true;
        return false;
    }
}

void sUserSetup::saveFile()
{
    QString fname = QApplication::applicationDirPath() + FN_USER_SETUP;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);
        save << user_setup;
        out.close();
        cParasChanged = false;
    }
    else
    {
        emit showMsgBox(tr("User Setup"), tr("Error Saving File!"));
    }
}

void sUserSetup::showUserSetup()
{
    ui->hsAlarmVolme->setValue(user_setup.alarm_vol);
    ui->cbEBEnable->setChecked(user_setup.error_buzzer_enable);
    ui->cbGMT->setCurrentIndex(user_setup.gmt);
    ui->cbRinseCycles->setCurrentIndex(user_setup.rinse_cycle);
}

void sUserSetup::updateUserSetup()
{
    cParasChanged = false;

    if(user_setup.alarm_vol != ui->hsAlarmVolme->value()) cParasChanged = true;
    user_setup.alarm_vol = ui->hsAlarmVolme->value();

    if(user_setup.error_buzzer_enable != ui->cbEBEnable->checkState()) cParasChanged = true;
    user_setup.error_buzzer_enable = ui->cbEBEnable->checkState();

    if(user_setup.gmt != ui->cbGMT->currentIndex()) cParasChanged = true;
    user_setup.gmt = ui->cbGMT->currentIndex();

    if(user_setup.rinse_cycle != ui->cbRinseCycles->currentIndex()) cParasChanged = true;
    user_setup.rinse_cycle = ui->cbRinseCycles->currentIndex();

}

void sUserSetup::on_pbSave_clicked()
{
    updateUserSetup();
    saveFile();

    if(cParasChanged)
    {
        cParasChanged = false;
        sendBuzAndVol();
    }

}

void sUserSetup::on_pbExit_clicked()
{
    updateUserSetup();

    if(cParasChanged)
    {
        emit getConfirmation(M_CONFIRM_USER);
    }

    this->hide();
    emit showHome(false);
}
