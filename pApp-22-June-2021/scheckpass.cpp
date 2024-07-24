#include "scheckpass.h"
#include "ui_scheckpass.h"
#include <QTime>//naveen
#include <QDir> //naveen

sCheckPass::sCheckPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sCheckPass)
{
    ui->setupUi(this);
    cShowMessageType = 0;
    cConfirmType = 0;
    cConfirmMenu = 0;
    cCheckPassType = 0;

    cCalls = 0;

    ui->frMessage->move(ui->frPassword->x(), ui->frPassword->y());
    ui->frMessage->hide();

    ui->frConfirm->move(ui->frPassword->x(), ui->frPassword->y());
    ui->frConfirm->hide();

    connect(ui->leUser, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->lePassword, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    ui->imageCapture->hide();
}

sCheckPass::~sCheckPass()
{
    delete ui;
}

void sCheckPass::Show_CheckPass(int cptype, bool again)
{
    cCheckPassType = cptype;

    ui->frMessage->hide();
    ui->frConfirm->hide();
    ui->frPassword->show();


    switch(cptype)
    {
        case M_PWD_GENERAL: ui->lblCaption->setText(tr("General Setup Password"));
        if(!again) ui->leUser->setText("admin");
        ui->lePassword->setText("");
        ui->lePassword->setFocus();
        break;

        case M_PWD_METHOD: ui->lblCaption->setText(tr("Method Setup Password"));

        if(!again) ui->leUser->setText("admin"); 
        ui->lePassword->setText("");
        ui->lePassword->setFocus();
        break;

        case M_PWD_SERVICE: ui->lblCaption->setText(tr("Service Password"));
        if(!again) ui->leUser->setText("service");
        ui->lePassword->setText("");
        ui->lePassword->setFocus();
        break;

        case M_PWD_CALIBRATION: ui->lblCaption->setText(tr("Calibration Password"));
        if(!again) ui->leUser->setText("service");
        ui->lePassword->setText("");
        ui->lePassword->setFocus();
        break;

        case M_PWD_DEBUG: ui->lblCaption->setText(tr("Debug Message Password"));
        if(!again) ui->leUser->setText("pssc");
        ui->lePassword->setText("");
        ui->lePassword->setFocus();
        break;

    }

    this->show();
}

void sCheckPass::Show_ShowMessage(int cptype, int mtype)
{
    cShowMessageType = mtype;

    ui->frPassword->hide();
    ui->frConfirm->hide();
    ui->frMessage->show();
    ui->pbOK->show();

    switch(cptype)
    {
        case M_PWD_GENERAL:
        ui->lblMCaption->setText(tr("General Setup Password!"));
        break;

        case M_PWD_METHOD:
        ui->lblMCaption->setText(tr("Method Setup Password!"));
        break;

        case M_PWD_SERVICE:
        ui->lblMCaption->setText(tr("Service Password!"));
        break;

        case M_PWD_CALIBRATION:
        ui->lblMCaption->setText(tr("Calibration Password!"));
        break;

        case M_PWD_DEBUG:
        ui->lblMCaption->setText(tr(" Debug Message Password!"));
        break;

        case M_MEMORY_DELETE:
        ui->lblMCaption->setText(tr("Memory Delete"));
        break;

        case M_MEMORY_TRANSFER:
        ui->lblMCaption->setText(tr("Memory Transfer"));
        break;

        case M_MEMORY_PRINT:
        ui->lblMCaption->setText(tr("Memory Print"));
        break;

    }

    switch(mtype)
    {
        case M_PWD_WRONG: ui->lblMessage->setText(tr("Wrong Password!\nEnter valid password & try again!")); break;
        case M_USER_WRONG: ui->lblMessage->setText(tr("Wrong User!\nEnter valid user & try again!")); break;

        case M_MEMORY_DELETED: ui->lblMessage->setText(tr("Selected Memory Deleted!")); break;
        case M_MEMORY_DELETE_ERROR: ui->lblMessage->setText(tr("Error Deleting Memory!")); break;

        //case M_MEMORY_TRANSFEFRED: ui->lblMessage->setText(tr("Selected Memory Transferred!\nUSB Logging is Active\nDo not remove USB Pen Drive!")); break;
        case M_MEMORY_TRANSFEFRED: ui->lblMessage->setText(tr("Selected Memory Transferred!")); break;
        case M_MEMORY_TRANSFER_ERROR: ui->lblMessage->setText(tr("Error Transferring Memory!")); break;
        case M_MEMORY_TRANSFER_NO_USB: ui->lblMessage->setText(tr("No USB Pen Drive Found!\nReconnect USB Pen Drive & try again!")); break;

        case M_CONFIRM_NDELETE: ui->lblMessage->setText(tr("Select  tests/columns!")); break;
        case M_CONFIRM_NTRANSFER: ui->lblMessage->setText(tr("Select  tests/columns!")); break;
        case M_NPRINT: ui->lblMessage->setText(tr("Select  tests/columns!")); break;
    }

    this->show();
}

void sCheckPass::Show_Message(QString title, QString msg)
{
    cShowMessageType = 0; 

    ui->frPassword->hide();
    ui->frConfirm->hide();
    ui->frMessage->show();
    ui->pbOK->show();
    ui->lblMCaption->setText(title);
    ui->lblMessage->setText(msg);
    this->show();

    qDebug() << "Show_Message:" << title << ", msg:" << msg;
}

void sCheckPass::Show_MessageWithAck(QString title, QString msg)
{
    cShowMessageType = M_MESSAGE_ACKNOWLEDGE;

    ui->frPassword->hide();
    ui->frConfirm->hide();
    ui->frMessage->show();
    ui->pbOK->show();
    ui->lblMCaption->setText(title);
    ui->lblMessage->setText(msg);
    this->show();

    qDebug() << "Show_MessageAck:" << title << ", msg:" << msg;
}


void sCheckPass::Show_Status(QString title, QString msg, bool show)
{
    cShowMessageType = 0; 

    if(show)
    {
        ui->frPassword->hide();
        ui->frConfirm->hide();
        ui->frMessage->show();
        ui->pbOK->hide();
        ui->lblMCaption->setText(title);
        ui->lblMessage->setText(msg);
        this->show();
    }
    else
        this->hide();
}

void sCheckPass::Show_ErrorMessage(QString title, QString msg)
{
    cShowMessageType = M_ERROR_ACKNOWLEDGE; 

    ui->frPassword->hide();
    ui->frConfirm->hide();
    ui->frMessage->show();
    ui->pbOK->show();
    ui->pbOK->setEnabled(true); //8-July-2022
    ui->lblMCaption->setText(title);
    ui->lblMessage->setText(msg);
    this->show();
}

void sCheckPass::setWaitACKStatus(bool tmp)
{
    ui->pbOK->setEnabled(!tmp);
}

bool sCheckPass::getWaitACKStatus()
{
    return true;
}

void sCheckPass::hideAfterACK(bool tmp)
{

}

bool sCheckPass::getHideAfterACK()
{
    return false;
}

bool sCheckPass::isErrorVisible()
{
   return (cShowMessageType == M_ERROR_ACKNOWLEDGE && ui->frMessage->isVisible()) ? true : false; 
}

void sCheckPass::Show_Confirmation(int ctype, int cmenu)
{

    qDebug() << "Show_Confirmation:" << ctype;

    cConfirmType = ctype;
    cConfirmMenu = cmenu;

    ui->frPassword->hide();
    ui->frMessage->hide();
    ui->frConfirm->show();

    switch(ctype)
    {
        case M_CONFIRM_MEASURING_STOP:
        ui->lblCCaption->setText(tr("Measuring!"));
        ui->lblCMessage->setText(tr("Do you want to Stop Test?"));
        break;

        case M_CONFIRM_MEASURE_WITHOUT_SAVING:
        ui->lblCCaption->setText(tr("Measuring!"));
        ui->lblCMessage->setText(tr("Memory Full!\nPerform Test without saving?"));
        break;

        case M_CONFIRM_RINSING_STOP:
        ui->lblCCaption->setText(tr("Rinsing!"));
        ui->lblCMessage->setText(tr("Do you want to Stop Rinsing?"));
        break;

        case M_CONFIRM_USER:
        ui->lblCCaption->setText(tr("User Setup!"));
        ui->lblCMessage->setText(tr("Do you want to Leave without saving?"));
        break;

        case M_CONFIRM_GENERAL:
        ui->lblCCaption->setText(tr("General Setup!"));
        ui->lblCMessage->setText(tr("Do you want to Leave without saving?"));
        break;

        case M_CONFIRM_GENERAL_SWITCH:
        ui->lblCCaption->setText(tr("General Setup!"));
        ui->lblCMessage->setText(tr("Save before switch?"));
        break;

        case M_CONFIRM_METHOD:
        ui->lblCCaption->setText(tr("Method Setup!"));
        ui->lblCMessage->setText(tr("Do you want to Exit without saving?"));
        break;

        case M_CONFIRM_METHOD_SWITCH:
        ui->lblCCaption->setText(tr("Method Setup!"));
        ui->lblCMessage->setText(tr("Save before switch?"));
        break;

        case M_CONFIRM_SERVICE:
        ui->lblCCaption->setText(tr("Service Setup!"));
        ui->lblCMessage->setText(tr("Do you want to Exit without saving?"));
        break;

        case M_CONFIRM_SERVICE_SWITCH:
        ui->lblCCaption->setText(tr("Service Setup!"));
        ui->lblCMessage->setText(tr("Save before switch?"));
        break;

        case M_CONFIRM_CALIBRATION:
        ui->lblCCaption->setText(tr("Calibration Setup!"));
        ui->lblCMessage->setText(tr("Do you want to Exit without saving?"));
        break;

        case M_CONFIRM_CALIBRATION_SWITCH:
        ui->lblCCaption->setText(tr("Calibration Setup!"));
        ui->lblCMessage->setText(tr("Save before switch?"));
        break;

        case M_CONFIRM_TRANSFER:
        ui->lblCCaption->setText(tr("Memory Transfer!"));
        ui->lblCMessage->setText(tr("Do you want to transfer!"));
        break;

        case M_CONFIRM_DELETE:
        ui->lblCCaption->setText(tr("Memory Delete!"));
        ui->lblCMessage->setText(tr("Do you want to delete!"));
        break;
    }

    this->show();
}

void sCheckPass::onShowKeypad(int tmp)
{
    emit showKeypad(QObject::sender(), KAYPAD_ALPHA_NUMERIC, false);
}

void sCheckPass::on_pbConfirm_clicked()
{
    ui->lePassword->setFocus();
    emit SendData(ui->leUser->text(), ui->lePassword->text(), MS_TYPE_CHECK_DATA, cCheckPassType);
}

void sCheckPass::on_pbOK_clicked()
{

    if(cShowMessageType == M_PWD_WRONG)
    {
        emit SendData("", "", MS_TYPE_AGAIN, cCheckPassType);
    }
    else if(cShowMessageType == M_ERROR_ACKNOWLEDGE)
    {
        emit SendData("", "", M_ERROR_ACKNOWLEDGE, M_ERROR_ACKNOWLEDGE);
    }
    else if(cShowMessageType == M_MESSAGE_ACKNOWLEDGE)
    {
        emit SendData("", "", M_MESSAGE_ACKNOWLEDGE, M_MESSAGE_ACKNOWLEDGE);
    }
    else
        this->hide();

}

void sCheckPass::on_pbCan_clicked()
{
   emit SendData("", "", MS_TYPE_CANCEL, cCheckPassType);
}

void sCheckPass::on_pbYes_clicked()
{
    this->hide();
    emit Confirmed(cConfirmType, true, cConfirmMenu);
}

void sCheckPass::on_pbNo_clicked()
{
    this->hide();
    emit Confirmed(cConfirmType, false, cConfirmMenu);
}

void sCheckPass::on_imageCapture_clicked()
{
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

        //QString filename = QApplication::applicationDirPath() + QString("/screenshot/scheckpass_%1.png").arg(timestamp);
        QString filename = QString("/run/media/sda1/screenshot/_%1_scheckpass.png").arg(timestamp);
        QWidget *widget = QApplication::activeWindow();
        QPixmap pixmap = QPixmap::grabWidget(widget);
        //    QString path = QApplication::applicationDirPath() + "/screenshot/screenshot.png";
        ui->imageCapture->setFocusPolicy(Qt::NoFocus);
        qDebug()<<"path : "<<filename;
        pixmap.save(QString(filename));
//        Show_ErrorMessage("Screenshot","Screenshot saved!");
    }else{
        qDebug()<<"folder doesn't exist";
//        Show_ErrorMessage("Screenshot","USB Not Found!");
    }
}
