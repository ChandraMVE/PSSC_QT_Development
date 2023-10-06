#include "smeasuring2.h"
#include "ui_smeasuring2.h"

sMeasuring2::sMeasuring2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMeasuring2)
{
    ui->setupUi(this);
    ui->frVLPr->move(20,300);
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
    ui->lblMethod->resize(471,101);
    ui->lblMethod->setText(tmp);
    ui->fr3Pr->hide();
    ui->frVLPr->hide();
    ui->lblFormula->hide();
}

void sMeasuring2::setMethodFormula(QString tmp, QString formula)
{
    ui->lblMethod->resize(471,41);
    ui->lblMethod->setText(tmp);
    ui->lblFormula->setText(formula);
    ui->lblFormula->show();
    ui->fr3Pr->hide();
    ui->frVLPr->hide();
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

    ui->lblVL->setText(vl);
    ui->lblatPr->setText(pr + " " + scale);
    ui->lblPassFail->setText(pass);
    ui->frVLPr->show();
}

void sMeasuring2::setVLTm(QString vl, QString tm, QString scale, QString pass)
{
    ui->lblVL->setText(vl);
    ui->lblatPr->setText(tm + " " + scale);
    ui->lblPassFail->setText(pass);
    ui->frVLPr->show();
}

void sMeasuring2::set3Prs(QString pabs, QString pgas, QString ptot, QString scale, QString pass)
{
    ui->lblPabs->setText(pabs);
    ui->lblPgas->setText(pgas);
    ui->lblPtot->setText(ptot);
    ui->lblScale->setText(scale);
    ui->lblPassFail->setText(pass);

    ui->fr3Pr->show();
    ui->lblScale->show();
}


