#include "smenubar.h"
#include "ui_smenubar.h"

sMenuBar::sMenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMenuBar)
{
    ui->setupUi(this);

    ui->pbMeasuring->setDown(true);
    ui->pbCleaning->setDown(true);
    ui->pbMemory->setDown(true);
    ui->pbSetup->setDown(true);

    pMenu = -1;
}

sMenuBar::~sMenuBar()
{
    delete ui;
}

void sMenuBar::setSelectedMenu(int menu)
{

    ui->pbMeasuring->setDown(false);
    ui->pbCleaning->setDown(false);
    ui->pbMemory->setDown(false);
    ui->pbSetup->setDown(false);

    ui->pbMeasuring->setEnabled(false);
    ui->pbCleaning->setEnabled(false);
    ui->pbMemory->setEnabled(false);
    ui->pbSetup->setEnabled(false);

    switch (menu) {
        case M_MEASURING:
        ui->pbMeasuring->setDown(true);

        ui->pbCleaning->setEnabled(true);
        ui->pbMemory->setEnabled(true);
        ui->pbSetup->setEnabled(true);

        break;

        case M_CLEANING:
        ui->pbCleaning->setDown(true);
        break;

        case M_MEMORY:
        ui->pbMemory->setDown(true);
        break;

        case M_SETUP:
        ui->pbSetup->setDown(true);
        break;
    }

   pMenu = menu;
}

void sMenuBar::setRunningMenu(int menu)
{

    if(menu == M_MEASURING)
    {
        ui->pbMeasuring->setDown(true);
        ui->pbCleaning->setEnabled(false);
    }
    else if(menu == M_CLEANING)
    {
        ui->pbMeasuring->setEnabled(false);
        ui->pbCleaning->setDown(true);
    }

    ui->pbMemory->setEnabled(false);
    ui->pbSetup->setEnabled(false);

    pMenu = menu;
}

void sMenuBar::on_pbMeasuring_clicked()
{
    emit MenuClicked(M_MEASURING);
}

void sMenuBar::on_pbCleaning_clicked()
{
    emit MenuClicked(M_CLEANING);
}

void sMenuBar::on_pbMemory_clicked()
{
    emit MenuClicked(M_MEMORY);
}

void sMenuBar::on_pbSetup_clicked()
{
    emit MenuClicked(M_SETUP);
}
