#include "smeasuring2.h"
#include "ui_smeasuring2.h"
#include <QTime> //naveen
#include <QDebug> //naveen
sMeasuring2::sMeasuring2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMeasuring2)
{
    ui->setupUi(this);
//    ui->frVLPr->move(20,300);
    ui->frVLPr->hide();
}

sMeasuring2::~sMeasuring2()
{
    delete ui;
}

void sMeasuring2::setSampleId(QString tmp)
{
    ui->lblSampleId->setText(tmp);
}

void sMeasuring2::setOperator(QString tmp)
{

}

void sMeasuring2::setMethod(QString tmp)
{
    ui->lblMethod->resize(491,101);
    ui->lblMethod->setText(tmp);
    ui->fr3Pr->hide();
    ui->frVLPr->hide();
    ui->lblFormula->hide();
    ui->frShaker->hide();
}

void sMeasuring2::setMethodFormula(QString tmp, QString formula)
{
    ui->lblMethod->resize(491,41);
    ui->lblMethod->setText(tmp);
    ui->lblFormula->setText(formula);
    ui->lblFormula->show();
    ui->fr3Pr->hide();
    ui->frVLPr->hide();
    ui->frShaker->hide();
}

void sMeasuring2::setResult(QString tmp, QString scale)
{
    ui->lblResult->setText(tmp);
    ui->lblScale->setText(scale);
    ui->lblScale->show();
}

void sMeasuring2::setStatus(QString tmp) 
{
    ui->lblStatus->setText(tmp);
}

void sMeasuring2::setVLPr(QString vl, QString pr, QString scale, QString pass)
{

    ui->frVLPr->move(105,315);

    ui->lblVL->setText(vl);
    ui->lblatPr->setText(pr + " " + scale);
    if(pass == "Pass")
    {
        ui->lblPassFail->setText(pass);
        ui->lblPassFail->setStyleSheet("color: rgb(0, 225, 0); font: 75 20pt \"Roboto Medium\";");
    }else
    {
        ui->lblPassFail->setText(pass);
        ui->lblPassFail->setStyleSheet("color: rgb(255, 0, 0); font: 75 20pt \"Roboto Medium\";");
    }
    ui->frVLPr->show();
}

void sMeasuring2::setShaker(QString sh){
    ui->frVLPr->move(20,300);
    ui->lblShakerCS->setText(sh);
    ui->frShaker->move(420,320);
    ui->frShaker->show();
}

void sMeasuring2::setVLTm(QString vl, QString tm, QString scale, QString pass)
{
    ui->frVLPr->move(105,315);
    ui->lblVL->setText(vl);
    ui->lblatPr->setText(tm + " " + scale);
    if(pass == "Pass")
    {
        ui->lblPassFail->setText(pass);
        ui->lblPassFail->setStyleSheet("color: rgb(0, 225, 0); font: 75 20pt \"Roboto Medium\";");
    }else
    {
        ui->lblPassFail->setText(pass);
        ui->lblPassFail->setStyleSheet("color: rgb(255, 0, 0); font: 75 20pt \"Roboto Medium\";");
    }
    ui->frVLPr->show();
}

void sMeasuring2::set3Prs(QString pabs, QString pgas, QString ptot, QString scale, QString pass)
{
    ui->label_8->move(30,0);
    ui->lblPtot->move(30,40);

    ui->lblPabs->setText(pabs);
    ui->lblPgas->setText(pgas);
    ui->lblPtot->setText(ptot);
    ui->lblScale->setText(scale);
    if(pass == "Pass")
    {
        ui->lblPassFail->setText(pass);
        ui->lblPassFail->setStyleSheet("color: rgb(0, 225, 0); font: 75 20pt \"Roboto Medium\";");
    }else
    {
        ui->lblPassFail->setText(pass);
        ui->lblPassFail->setStyleSheet("color: rgb(255, 0, 0); font: 75 20pt \"Roboto Medium\";");
    }

    ui->lblPabs->show();
    ui->lblPgas->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->fr3Pr->show();
    ui->lblScale->show();
}

void sMeasuring2::setPtot(QString ptot, QString scale, QString pass){
    ui->lblPabs->hide();
    ui->lblPgas->hide();
    ui->label_9->hide();
    ui->label_10->hide();

    ui->lblPtot->setText(ptot);
    ui->lblScale->setText(scale);

    ui->label_8->move(200,0);
    ui->lblPtot->move(190,40);
    if(pass == "Pass")
    {
        ui->lblPassFail->setText(pass);
        ui->lblPassFail->setStyleSheet("color: rgb(0, 225, 0); font: 75 20pt \"Roboto Medium\";");
    }else
    {
        ui->lblPassFail->setText(pass);
        ui->lblPassFail->setStyleSheet("color: rgb(255, 0, 0); font: 75 20pt \"Roboto Medium\";");
    }
    ui->fr3Pr->show();
    ui->lblScale->show();
}

void sMeasuring2::setFreeShaker(QString speed){
    ui->frShaker->move(245, 430);
    ui->label_15->move(10,0);
    ui->lblShakerCS->move(160,0);
    ui->lblShakerCS->setText(speed);
    ui->frShaker->show();
}

//void sMeasuring2::on_imageCapture_clicked()
//{
//    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

//    QString filename = QApplication::applicationDirPath() + QString("/screenshot/smeasuring2_%1.png").arg(timestamp);
//    QWidget *widget = QApplication::activeWindow();
//    QPixmap pixmap = QPixmap::grabWidget(widget);
// //    QString path = QApplication::applicationDirPath() + "/screenshot/screenshot.png";
//    ui->imageCapture->setFocusPolicy(Qt::NoFocus);
//    qDebug()<<"path : "<<filename;
//    pixmap.save(QString(filename));
//}
