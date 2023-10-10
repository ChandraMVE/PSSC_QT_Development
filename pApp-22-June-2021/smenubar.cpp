#include "smenubar.h"
#include "ui_smenubar.h"

sMenuBar::sMenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMenuBar)
{
    ui->setupUi(this);
 ui->wmMeasuring->setText("Measuring");
    ui->wmMeasuring->setEnabled(true);
    ui->wmMeasuring->setSelected(false);

    ui->wmCleaning->setText("Rinsing");
    ui->wmCleaning->setEnabled(true);
    ui->wmCleaning->setSelected(false);

    ui->wmMemory->setText("Memory");
    ui->wmMemory->setEnabled(true);
    ui->wmMemory->setSelected(false);

    ui->wmSetup->setText("Setup");
    ui->wmSetup->setEnabled(true);
    ui->wmSetup->setSelected(false);

    connect(ui->wmMeasuring, SIGNAL(clicked()), this , SLOT(onMeasuringClicked()));
    connect(ui->wmCleaning, SIGNAL(clicked()), this , SLOT(onCleaningClicked()));
    connect(ui->wmMemory, SIGNAL(clicked()), this , SLOT(onMemoryClicked()));
    connect(ui->wmSetup, SIGNAL(clicked()), this , SLOT(onSetupClicked()));

    pMenu = -1;
}

sMenuBar::~sMenuBar()
{
    delete ui;
}

void sMenuBar::setSelectedMenu(int menu)
{

    ui->wmMeasuring->setEnabled(true);
    ui->wmMeasuring->setSelected(false);
    ui->wmCleaning->setEnabled(true);
    ui->wmCleaning->setSelected(false);
    ui->wmMemory->setEnabled(true);
    ui->wmMemory->setSelected(false);
    ui->wmSetup->setEnabled(true);
    ui->wmSetup->setSelected(false);

    switch (menu)
    {
        case M_MEASURING: ui->wmMeasuring->setSelected(true); break;

        case M_CLEANING: ui->wmCleaning->setSelected(true); break;

        case M_MEMORY: ui->wmMemory->setSelected(true); break;

        case M_SETUP: ui->wmSetup->setSelected(true); break;

    }

   pMenu = menu;
}

void sMenuBar::setRunningMenu(int menu)
{
 ui->wmMeasuring->setEnabled(false);
    ui->wmCleaning->setEnabled(false);
    ui->wmMemory->setEnabled(false);
    ui->wmSetup->setEnabled(false);

    switch (menu)
    {
        case M_MEASURING: ui->wmMeasuring->setRunning(); break;
        case M_CLEANING: ui->wmCleaning->setRunning(); break;
        case M_MEMORY: ui->wmMemory->setRunning(); break;
        case M_SETUP: ui->wmSetup->setRunning(); break;
    }

    pMenu = menu;
}

void sMenuBar::onMeasuringClicked()
{
    emit MenuClicked(M_MEASURING);
}

void sMenuBar::onCleaningClicked()
{
    emit MenuClicked(M_CLEANING);
}

void sMenuBar::onMemoryClicked()
{
    emit MenuClicked(M_MEMORY);
}

void sMenuBar::onSetupClicked()
{
  
}

    emit MenuClicked(M_SETUP);
}
