#include "slabel.h"
#include "ui_slabel.h"

slabel::slabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::slabel)
{
    enabled = true;
    ui->setupUi(this);
}

slabel::~slabel()
{
    delete ui;
}

void slabel::setText(QString caption)
{
    ui->label->setText(caption);
}

void slabel::setEnabled(bool tmp)
{
    enabled = tmp;
}

void slabel::setSelected(bool tmp)
{
    if(tmp)
        ui->label->setStyleSheet(
        "QLabel { background-color: rgb(21, 100, 192); \
        border-width: 2px; \
        border-color: rgb(51, 204, 255);\
        border-style: solid;\
        border-radius: 10;\
        color: rgb(255, 255, 255);\
        font: 75 16pt \"Roboto Medium\"; }");
    else
        ui->label->setStyleSheet(
        "QLabel { background-color: rgb(241, 241, 241); \
        border-width: 2px; \
        border-color: rgb(21, 100, 192); \
        border-style: solid;\
        border-radius: 10;\
        color: rgb(0, 0, 0);\
        font: 75 16pt \"Roboto Medium\"; }");

}

void slabel::setRunning()
{
    enabled = false;
    ui->label->setStyleSheet("QLabel {background-color: rgb(21, 100, 192);\
    border-width: 2px;\
    border-color: rgb(51, 204, 255);\
    border-style: solid;\
    border-radius: 10;\
    color: rgb(255, 255, 255);\
    font: 75 16pt \"Roboto Medium\"; }");
}

void slabel::setFirmware(QString caption)
{
    enabled = true;

    ui->label->setText(caption);
    ui->label->resize(this->width(), this->height());
    ui->label->move(0,0);

    ui->label->setStyleSheet(
    "QLabel { background-color: rgb(241, 241, 241); \
    border-width: 0px; \
    border-color: rgb(51, 204, 255);\
    border-style: solid;\
    border-radius: 10;\
    color: rgb(193, 193, 193);\
    font: 68 14pt \"Roboto Medium\"; }");
}

void slabel::mousePressEvent(QMouseEvent *evt)
{
    if(enabled)
        emit clicked();

}
