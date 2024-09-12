#include "susersetup.h"
#include "ui_susersetup.h"

sUserSetup::sUserSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sUserSetup)
{
    ui->setupUi(this);

    QListView *view1 = new QListView(ui->cbGMT);
    view1->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item::hover { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255);}\
                        QListView::item{height: 41px}");

    ui->cbGMT->setView(view1);

    QListView *view2 = new QListView(ui->cbRinseCycles);
    view2->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item::hover { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255);}\
                        QListView::item{height: 41px}");

    ui->cbRinseCycles->setView(view2);

    setDefaults();
    cParasChanged = false;
    cHide = false;
    cEnSwitch = true;
}

sUserSetup::~sUserSetup()
{
    delete ui;
}

void sUserSetup::Show()
{
    showUserSetup();
    this->show();
    cHide = false;
}

int sUserSetup::getGMTSeconds()
{
    return ((1800*user_setup.gmt)-43200);
}

void sUserSetup::sendBuzAndVol()
{
    /*QString str = "#Q" + QString::number(user_setup.error_buzzer_enable ? 1:0) +
                  "," + QString::number(user_setup.alarm_vol) +
                  "$";
    */

    QString str = cProtocol.sendBuzAndVol(user_setup.error_buzzer_enable ? 1:0, user_setup.alarm_vol);

    emit sendCommand(str,this);
}

QString sUserSetup::getBuzAndVol()
{
    QString str = cProtocol.sendBuzAndVol(user_setup.error_buzzer_enable ? 1:0, user_setup.alarm_vol);
    return str;
}

void sUserSetup::setDefaults()
{
    user_setup.alarm_vol = DEFAULT_USER_ALARM_VOL;
    user_setup.error_buzzer_enable = DEFAULT_ERROR_BUZZER_ENABLE;
    user_setup.gmt = DEFAULT_USER_GMT;
    user_setup.rinse_cycle = DEFAULT_RINSE_CYCLES;
    user_setup.auto_print = DEFAULT_AUTO_PRINT_ENABLE;

}

bool sUserSetup::readFile()
{

    QString fname = QApplication::applicationDirPath() + FN_USER_SETUP;

    QFile in(fname);

    cEnSwitch = true;

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
        cEnSwitch = true;
    }
    else
    {
        cEnSwitch = false;
        emit showMsgBox(tr("User Setup"), tr("Error Saving File!"));
    }
}

void sUserSetup::showUserSetup()
{
    ui->hsAlarmVolme->setValue(user_setup.alarm_vol);
    ui->cbEBEnable->setChecked(user_setup.error_buzzer_enable);
    ui->cbGMT->setCurrentIndex(user_setup.gmt);
    ui->cbRinseCycles->setCurrentIndex(user_setup.rinse_cycle);
    ui->cbAutoPrintEnable->setChecked(user_setup.auto_print);

    ui->pbSave->setEnabled(true);
    ui->pbExit->setEnabled(true);
}

void sUserSetup::updateUserSetup()
{
   //qDebug() << "updateUserSetup";

   // cParasChanged = false;

    if(user_setup.alarm_vol != ui->hsAlarmVolme->value()) cParasChanged = true;
    user_setup.alarm_vol = ui->hsAlarmVolme->value();

    if(user_setup.error_buzzer_enable != ui->cbEBEnable->checkState()) cParasChanged = true;
    user_setup.error_buzzer_enable = ui->cbEBEnable->checkState();

    if(user_setup.gmt != ui->cbGMT->currentIndex()) cParasChanged = true;
    user_setup.gmt = ui->cbGMT->currentIndex();

    if(user_setup.rinse_cycle != ui->cbRinseCycles->currentIndex()) cParasChanged = true;
    user_setup.rinse_cycle = ui->cbRinseCycles->currentIndex();

    if(user_setup.auto_print!= ui->cbAutoPrintEnable->checkState()) cParasChanged = true;
    user_setup.auto_print = ui->cbAutoPrintEnable->checkState();

}

void sUserSetup::setWaitACKStatus(bool tmp)
{
    ui->pbExit->setEnabled(!tmp);
}

bool sUserSetup::getWaitACKStatus()
{
    return true;
}

void sUserSetup::hideAfterACK(bool tmp)
{
    if(!tmp)
    {
        cHide = false;
        qDebug() << "this-hide user";
        //13-May-2023
        //this->hide();
    }
    else cHide = true;
}

bool sUserSetup::getHideAfterACK()
{
    return cHide;
}

bool sUserSetup::isSwitchEnabled(int tmp)
{
    updateUserSetup();

    if(cParasChanged)
    {
        cEnSwitch = false;
        emit getConfirmation(M_CONFIRM_USER, tmp);
    }
    else //13-May-2023
    {
        hideAfterACK(true);
        emit sendCommand(cProtocol.sendBuzAndVol(user_setup.error_buzzer_enable ? 1:0, user_setup.alarm_vol), this);
    }

    return cEnSwitch;
}

void sUserSetup::on_pbSave_clicked()
{
    updateUserSetup();
    saveFile();

    /* 8-July-2022
    if(cParasChanged)
    {
        cParasChanged = false;
        sendBuzAndVol();
    }
    */

}

void sUserSetup::on_pbExit_clicked()
{
    updateUserSetup();

    if(cParasChanged)
    {
        cEnSwitch = false;
        emit getConfirmation(M_CONFIRM_USER, M_MEASURING);
    }
    else //13-May-2023
    {
        hideAfterACK(true);
        emit sendCommand(cProtocol.sendBuzAndVol(user_setup.error_buzzer_enable ? 1:0, user_setup.alarm_vol), this);
    }

    if(!cParasChanged)
    {
        this->hide();
        emit showHome(false);
    }
}
