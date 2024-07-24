#include "sfileselect.h"
#include "ui_sfileselect.h"
#include <QTime>

sFileSelect::sFileSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sFileSelect)
{
    ui->setupUi(this);

    ui->frMessage->move(40,200);
    ui->frMessage->hide();

    ui->imageCapture->hide();
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

        rootDir->setSorting(QDir::Time);

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
	{
	    ui->lwFiles->setCurrentRow(0);
            ui->frFileSelect->show();
	}
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

void sFileSelect::on_imageCapture_clicked()
{
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

        //QString filename = QApplication::applicationDirPath() + QString("/screenshot/sfileselect_%1.png").arg(timestamp);
        QString filename = QString("/run/media/sda1/screenshot/_%1_sfileselect.png").arg(timestamp);
        QWidget *widget = QApplication::activeWindow();
        QPixmap pixmap = QPixmap::grabWidget(widget);
        //    QString path = QApplication::applicationDirPath() + "/screenshot/screenshot.png";
        ui->imageCapture->setFocusPolicy(Qt::NoFocus);
        qDebug()<<"path : "<<filename;
        pixmap.save(QString(filename));
    }else{
        qDebug()<<"folder doesn't exist";
    }
}
