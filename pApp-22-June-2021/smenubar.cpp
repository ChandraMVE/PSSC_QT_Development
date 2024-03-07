#include "smenubar.h"
#include "ui_smenubar.h"

#include "sgeneralsetup.h"

sMenuBar::sMenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMenuBar)
{
    ui->setupUi(this);

    QString measu = (getLanguage()==0)?"Measuring":(getLanguage()==1)?"Medición":(getLanguage()==2)?"Messung":"Mesure";
    ui->wmMeasuring->setText(measu);
    ui->wmMeasuring->setEnabled(true);
    ui->wmMeasuring->setSelected(false);

    QString rins=(getLanguage()==0)?"Rinsing":(getLanguage()==1)?"Enjuague":(getLanguage()==2)?"Spülen":"Rinçage";
    ui->wmCleaning->setText(rins);
    ui->wmCleaning->setEnabled(true);
    ui->wmCleaning->setSelected(false);

    QString mem=(getLanguage()==0)?"Memory":(getLanguage()==1)?"Memoria":(getLanguage()==2)?"Erinnerung":"Mémoire";
    ui->wmMemory->setText(mem);
    ui->wmMemory->setEnabled(true);
    ui->wmMemory->setSelected(false);

    QString setu=(getLanguage()==0)?"Setup":(getLanguage()==1)?"Preparar":(getLanguage()==2)?"Installieren":"Installer";
    ui->wmSetup->setText(setu);
    ui->wmSetup->setEnabled(true);
    ui->wmSetup->setSelected(false);

    connect(ui->wmMeasuring, SIGNAL(clicked()), this , SLOT(onMeasuringClicked()));
    connect(ui->wmCleaning, SIGNAL(clicked()), this , SLOT(onCleaningClicked()));
    connect(ui->wmMemory, SIGNAL(clicked()), this , SLOT(onMemoryClicked()));
    connect(ui->wmSetup, SIGNAL(clicked()), this , SLOT(onSetupClicked()));

    pMenu = -1;
}

int sMenuBar::getLanguage(){
    struct GENERAL_SETUP general_setup;

    QString fname = QApplication::applicationDirPath() + FN_GENERAL_SETUP;

    QFile in(fname);

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream save(&in);
        save >> general_setup;
        in.close();
        return general_setup.language;
    }
    else
    {
       return 0;
    }
}

sMenuBar::~sMenuBar()
{
    delete ui;
}

void sMenuBar::wmSetupsetSelected(bool tmp){
    if(tmp){
        ui->wmSetup->setSelected(true);
    }else{
        ui->wmSetup->setSelected(false);
    }
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
    ui->wmSetup->setSelected(false); //naveen

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
//    ui->wmSetup->setSelected(true); //naveen
    emit MenuClicked(M_SETUP);
}
