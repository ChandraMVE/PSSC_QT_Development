#include "sfileselect.h"
#include "ui_sfileselect.h"

sFileSelect::sFileSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sFileSelect)
{
    ui->setupUi(this);

    ui->frMessage->move(40,200);
    ui->frMessage->hide();
}

sFileSelect::~sFileSelect()
{
    delete ui;
}

void sFileSelect::Show()
{
    ui->frFileSelect->hide();
    ui->frMessage->hide();

    QDir* rootDir = new QDir(FF_FIRMWARE_FOLDER);

    if(rootDir->exists())
    {
        rootDir->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);

        rootDir->setSorting(QDir::Name);

        QFileInfoList filesList = rootDir->entryInfoList();

        ui->lwFiles->clear();

        foreach(QFileInfo fileInfo, filesList)
        {
            ui->lwFiles->addItem(fileInfo.fileName());
        }

        if(!ui->lwFiles->count())
        {
            ui->lblMessage->setText(tr("Firmware Files not found!"));
            ui->frMessage->show();
        }
        else
            ui->frFileSelect->show();
    }
    else
    {
        ui->lblMessage->setText(tr("No USB Pen Drive Found!\nReconnect USB Pen Drive & try again!"));
        ui->frMessage->show();
    }

    this->show();
}

void sFileSelect::on_pbSelected_clicked()
{
    emit FileSelected(ui->lwFiles->currentItem()->text());
    ui->lwFiles->clear();
    this->hide();
}

void sFileSelect::on_pbCancel_clicked()
{
    emit FileSelected("---");
    ui->lwFiles->clear();
    this->hide();
}

void sFileSelect::on_pbOK_clicked()
{
    emit FileSelected("---");
    this->hide();
}
