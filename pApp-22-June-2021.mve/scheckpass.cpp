#include "scheckpass.h"
#include "ui_scheckpass.h"

sCheckPass::sCheckPass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sCheckPass)
{
    ui->setupUi(this);
    cShowMessageType = 0;
    cConfirmType = 0;
    cCheckPassType = 0;

    cCalls = 0;

    ui->frMessage->move(ui->frPassword->x(), ui->frPassword->y());
    ui->frMessage->hide();

    ui->frConfirm->move(ui->frPassword->x(), ui->frPassword->y());
    ui->frConfirm->hide();

    connect(ui->leUser, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->lePassword, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

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
    }

    this->show();
}

void sCheckPass::Show_ShowMessage(int cptype, int mtype)
{
    cShowMessageType = mtype;

    ui->frPassword->hide();
    ui->frConfirm->hide();
    ui->frMessage->show();

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

        case M_MEMORY_TRANSFEFRED: ui->lblMessage->setText(tr("Selected Memory Transferred!\nUSB Logging is Active\nDo not remove USB Pen Drive!")); break;
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
}

void sCheckPass::Show_Status(QString title, QString msg)
{
    cShowMessageType = 0; 

    ui->frPassword->hide();
    ui->frConfirm->hide();
    ui->frMessage->show();
    ui->pbOK->hide();
    ui->lblMCaption->setText(title);
    ui->lblMessage->setText(msg);
    this->show();
}

void sCheckPass::Show_ErrorMessage(QString title, QString msg)
{
    cShowMessageType = M_ERROR_ACKNOWLEDGE; 

    ui->frPassword->hide();
    ui->frConfirm->hide();
    ui->frMessage->show();
    ui->pbOK->show();
    ui->lblMCaption->setText(title);
    ui->lblMessage->setText(msg);
    this->show();
}

bool sCheckPass::isErrorVisible()
{
   return (cShowMessageType == M_ERROR_ACKNOWLEDGE && ui->frMessage->isVisible()) ? true : false; 
}

void sCheckPass::Show_Confirmation(int ctype)
{
    cConfirmType = ctype;
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
    emit Confirmed(cConfirmType, true);
}

void sCheckPass::on_pbNo_clicked()
{
    this->hide();
    emit Confirmed(cConfirmType, false);
}
