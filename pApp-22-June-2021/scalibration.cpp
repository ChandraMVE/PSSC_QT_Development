#include "scalibration.h"
#include "ui_scalibration.h"

sCalibration::sCalibration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sCalibration)
{
    ui->setupUi(this);

    QListView *view1 = new QListView(ui->cbTCalibMethod);
    view1->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbTCalibMethod->setView(view1);

    QListView *view2 = new QListView(ui->cbPCSelectorValve);
    view2->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbPCSelectorValve->setView(view2);

    QListView *view3 = new QListView(ui->cbPCTFirst);
    view3->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbPCTFirst->setView(view3);

    QListView *view4 = new QListView(ui->cbPCTFinal);
    view4->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbPCTFinal->setView(view4);

    connect(ui->leTCTemperature, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->leTCTemperature, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));

    connect(ui->leTCTLow, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->leTCTLow, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));

    connect(ui->leTCTHigh, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->leTCTHigh, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));

    connect(ui->leTCTOffset, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->leTCTOffset, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));

    connect(ui->lePCTemperature, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->lePCTemperature, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));

    connect(ui->lePCPLow, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->lePCPLow, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));

    connect(ui->lePCPHigh, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->lePCPHigh, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));

    ui->lePrHidden->hide();

    cParasChanged = false;

    ui->grOffset->hide();

    cWidgetPressure = ui->tabPressure;
    cStringPressure = ui->twCalibration->tabText(1);

    cWidgetPrLinear = ui->tabPrLinear;
    cStringPrLinear = ui->twCalibration->tabText(2);

    cWidgetPrLinearzation = ui->tabPrLinerzation;
    cStringPrLinearzation = ui->twCalibration->tabText(3);

    ui->twCalibration->removeTab(2);
    ui->twCalibration->removeTab(2);
    ui->twCalibration->removeTab(2); //naveen

    ui->twCalibration->setCurrentIndex(0);

    ui->tvPressure->setColumnWidth(0, 119);
    ui->tvPressure->setColumnWidth(1, 142);
    ui->tvPressure->setColumnWidth(2, 142);
    ui->tvPressure->setColumnWidth(3, 142);
    ui->tvPressure->setColumnWidth(4, 142);

    setDefaults();
    cParasChanged = false;
    cEnSwitch = true;

    QDoubleValidator* tempValidator = new QDoubleValidator(RANGE_CALIB_TEMPERATURE_MIN, RANGE_CALIB_TEMPERATURE_MAX, RANGE_CALIB_TEMPERATURE_DECIMAL_PLACES);
    tempValidator->setNotation(QDoubleValidator::StandardNotation);

    QDoubleValidator* tempOffsetValidator = new QDoubleValidator(RANGE_CALIB_TEMPERATURE_OFFSET_MIN, RANGE_CALIB_TEMPERATURE_OFFSET_MAX, RANGE_CALIB_TEMPERATURE_DECIMAL_PLACES);
    tempOffsetValidator->setNotation(QDoubleValidator::StandardNotation);

    ui->leTCTemperature->setValidator(tempValidator);
    ui->leTCTLow->setValidator(tempValidator);
    ui->leTCTHigh->setValidator(tempValidator);

    ui->leTCTOffset->setValidator(tempOffsetValidator);

    ui->lePCTemperature->setValidator(tempValidator);

    QDoubleValidator* prValidator = new QDoubleValidator(RANGE_CALIB_PRESSURE_MIN, RANGE_CALIB_PRESSURE_MAX, RANGE_CALIB_PRESSURE_DECIMAL_PLACES);
    prValidator->setNotation(QDoubleValidator::StandardNotation);

    ui->lePCPLow->setValidator(prValidator);
    ui->lePCPHigh->setValidator(prValidator);

    QDoubleValidator* prcorrValidator = new QDoubleValidator(RANGE_CALIB_PRESSURE_CORRECTION_MIN, RANGE_CALIB_PRESSURE_CORRECTION_MAX, RANGE_CALIB_PRESSURE_CORRECTION_DECIMAL_PLACES);
    prcorrValidator->setNotation(QDoubleValidator::StandardNotation);

    ui->lePrHidden->setValidator(prcorrValidator);

    cStage = 0;
    cTemperatureCount = 0;
    cPressureCount = 0;

    cPrAutoCalibIndex = 0;

    cPrevTab = -1;


    initAvg();
}

sCalibration::~sCalibration()
{
    delete ui;
}

void sCalibration::Show()
{
    ui->cbPCTFirst->setCurrentIndex(0);
    ui->cbPCTFinal->setCurrentIndex(17);

    ui->twCalibration->removeTab(1);
    ui->twCalibration->insertTab(1, cWidgetPressure, cStringPressure);

    ui->twCalibration->setCurrentIndex(0);
    cPrevTab = 0;

    showTemperatureCalib();
    showPressureCalib();

    setAutoCalibrationStatus("");
    setAutoCalibrationSubStatus("");

    ui->tvLivePrTable->clearContents();
    ui->tvLivePrTable->model()->removeRows(0, ui->tvLivePrTable->rowCount());
    ui->tvLivePrTable->hide();

    ui->tvPressure->clearContents();
    ui->tvPressure->model()->removeRows(0, ui->tvPressure->rowCount());

    cHide = false;

    setWaitACKStatus(true);
    emit sendCommand(cProtocol.sendMeasuringStart(1, 0), this);

    this->show();
}

void sCalibration::setDefaults()
{

    cCalibTm.method = CALIB_DEFAULT_TEMPERATURE_CALIB_METHOD;

    cCalibTm.tlow = CALIB_DEFAULT_TEMPERATURE_T_LOW;
    cCalibTm.thigh = CALIB_DEFAULT_TEMPERATURE_T_HIGH;

    cCalibTm.tzero = CALIB_DEFAULT_TEMPERATURE_ZERO;
    cCalibTm.toffset = CALIB_DEFAULT_TEMPERATURE_OFFSET;
    cCalibTm.tgain = CALIB_DEFAULT_TEMPERATURE_GAIN;

    cCalibTm.tlow_count = CALIB_DEFAULT_TEMPERATURE_T_LOW_COUNT;
    cCalibTm.thigh_count = CALIB_DEFAULT_TEMPERATURE_T_HIGH_COUNT;

    cTCTLow = cCalibTm.tlow;
    cTCTHigh = cCalibTm.thigh;
    cTCTLowCount = cCalibTm.tlow_count;
    cTCTHighCount = cCalibTm.thigh_count;

    cCalibTm.slope = getSlope(cCalibTm.thigh, cCalibTm.thigh_count,
                              cCalibTm.tlow, cCalibTm.tlow_count);

    cCalibTm.constant = getConstant(cCalibTm.thigh, cCalibTm.slope,
                                    cCalibTm.thigh_count);

    cCalibTm.tzero = cCalibTm.tlow;
    cCalibTm.tgain = cCalibTm.slope;


    cCalibPr.plow = CALIB_DEFAULT_PRESSURE_P_LOW;
    cCalibPr.phigh = CALIB_DEFAULT_PRESSURE_P_HIGH;

    cCalibPr.pzero = CALIB_DEFAULT_PRESSURE_ZERO;
    cCalibPr.poffset = CALIB_DEFAULT_PRESSURE_OFFSET;
    cCalibPr.pgain = CALIB_DEFAULT_PRESSURE_GAIN;

    cCalibPr.plow_count = CALIB_DEFAULT_PRESSURE_P_LOW_COUNT;
    cCalibPr.phigh_count = CALIB_DEFAULT_PRESSURE_P_HIGH_COUNT;

    cPCPLow = cCalibPr.plow;
    cPCPHigh = cCalibPr.phigh;

    cPCPLowCount = cCalibPr.plow_count;
    cPCPHighCount = cCalibPr.phigh_count;

    cCalibPr.slope20 = getSlope(cCalibPr.phigh, cCalibPr.phigh_count,
                              cCalibPr.plow, cCalibPr.plow_count);

    cCalibPr.constant20 = getConstant(cCalibPr.phigh, cCalibPr.slope20,
                                    cCalibPr.phigh_count);

    cCalibPr.pzero = cCalibPr.plow;
    cCalibPr.pgain = cCalibPr.slope20;

    cTemperatureCount = 0; 
    cPressureCount = 0; 

    cPrAutoCalibIndex = 0;

    cCalibPr.prl_index = 0;
    cCalibPr.prl_low = cCalibPr.plow;
    cCalibPr.prl_high = cCalibPr.phigh;

    for(int tmp=0; tmp<19; tmp++)
    {
        cCalibPr.prl_enabled[tmp] = 0;

        cCalibPr.prl_temperature[tmp] = 5+((tmp+1)*5);
        cCalibPr.prl_low_correction[tmp] = 0.01;
        cCalibPr.prl_high_correction[tmp] = 0.02;

        cCalibPr.prl_slope[tmp] = getSlope(cCalibPr.prl_high_correction[tmp],
                                       cCalibPr.prl_high,
                                       cCalibPr.prl_low_correction[tmp],
                                       cCalibPr.prl_low);

        cCalibPr.prl_constant[tmp] = getConstant(cCalibPr.prl_high_correction[tmp], cCalibPr.slope20,
                                                 cCalibPr.prl_high);

    }
}

bool sCalibration::readFile()
{
    QString fname = QApplication::applicationDirPath() + FN_TCALIBRATION_SETUP;

    QFile in(fname);

    cEnSwitch = true;

    if(in.open(QIODevice::ReadOnly))
    {
        in.read((char *)&cCalibTm, sizeof(cCalibTm));
        in.read((char *)&cCalibPr, sizeof(cCalibPr));
        in.close();

        cTCTLow = cCalibTm.tlow;
        cTCTHigh = cCalibTm.thigh;
        cTCTLowCount = cCalibTm.tlow_count;
        cTCTHighCount = cCalibTm.thigh_count;

        cPCPLow = cCalibPr.plow;
        cPCPHigh = cCalibPr.phigh;

        cPCPLowCount = cCalibPr.plow_count;
        cPCPHighCount = cCalibPr.phigh_count;

        cParasChanged = false;

        return true;

    }
    else
    {
        setDefaults();
        return false;
    }
}

bool sCalibration::saveFile()
{
    QString fname = QApplication::applicationDirPath() + FN_TCALIBRATION_SETUP;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {

        out.write((char *)&cCalibTm, sizeof(cCalibTm));
        out.write((char *)&cCalibPr, sizeof(cCalibPr));

        out.close();
        cParasChanged = false;
        cEnSwitch = true;
        return true;
    }
    else
    {
        cEnSwitch = false;
        emit showMsgBox(tr("Calibration Setup"), tr("Error Saving File!"));
        return false;
    }
}

void sCalibration::showTemperatureCalib()
{
    setTempTabReadOnly(false);

    if(IS_ADMIN_USER){
        QString OffsetLang = (IsLanguage==0)?"Offset":(IsLanguage==1)?"Compensar":(IsLanguage==2)?"Versatz":"Compenser";
        ui->label_12->setVisible(true);
        ui->label_12->setText(OffsetLang);
        ui->pbTCTOffset->setText(getTemperatureCS(cCalibTm.toffset));
        ui->pbTCTOffset->setVisible(true);
    }else{
        ui->label_12->setVisible(false);
        ui->pbTCTOffset->hide();
    }
    //ui->label_12->setVisible(false);
    ui->cbTCalibMethod->setCurrentIndex(cCalibTm.method);

    ui->cbTCTEnable->setChecked(CALIB_DEFAULT_TEMPERATURE_T_CONTROL_ENABLE);
    ui->leTCTemperature->setText(getTemperatureCS(CALIB_DEFAULT_TEMPERATURE_T));

    if(!cCalibTm.method) ui->cbTCTEnable->setEnabled(true);
    else ui->cbTCTEnable->setEnabled(false);

    ui->leTCTemperature->setReadOnly(!ui->cbTCTEnable->isChecked());
    ui->pbTCTSet->setEnabled(ui->cbTCTEnable->isChecked());

    ui->leTCTLow->setText(getTemperatureCS(cCalibTm.tlow));
    ui->leTCTHigh->setText(getTemperatureCS(cCalibTm.thigh));
    ui->leTCTOffset->setText(getTemperatureCS(cCalibTm.toffset));
    //ui->pbTCTOffset->setText(getTemperatureCS(cCalibTm.toffset));
    //ui->pbTCTOffset->hide();

    ui->lblTCZero->setText(getTemperatureCS(cCalibTm.tlow));
    ui->lblTCGain->setText(QString::number(cCalibTm.slope, 'f', 6));

    ui->lblTCTemperature->setText("");

    cTCTLow = cCalibTm.tlow;
    cTCTHigh = cCalibTm.thigh;
    cTCTLowCount = cCalibTm.tlow_count;
    cTCTHighCount = cCalibTm.thigh_count;

    ui->pbTCTLowSet->setText(tr("Set"));
    ui->pbTCTHighSet->setText(tr("Set"));

    ui->grOffset->hide();

}

void sCalibration::updateTemperatureCalib()
{

    if(cCalibTm.method != ui->cbTCalibMethod->currentIndex())
    {
        cParasChanged = true;
    }

    cCalibTm.method = ui->cbTCalibMethod->currentIndex();

    if(getTemperatureCS(cCalibTm.tlow) != ui->leTCTLow->text())
    {
        cParasChanged = true;
    }

    cCalibTm.tlow = ui->leTCTLow->text().toDouble();

    if(getTemperatureCS(cCalibTm.thigh) != ui->leTCTHigh->text())
    {
        cParasChanged = true;
    }

    cCalibTm.thigh = ui->leTCTHigh->text().toDouble();


    if(getTemperatureCS(cCalibTm.toffset) != ui->pbTCTOffset->text())
    {
        cParasChanged = true;
    }

    cCalibTm.toffset = ui->pbTCTOffset->text().toDouble();

    if(cCalibTm.tlow != cTCTLow)
    {
        cParasChanged = true;
    }
    cCalibTm.tlow = cTCTLow;

    if(cCalibTm.thigh != cTCTHigh)
    {
        cParasChanged = true;
    }

    cCalibTm.thigh = cTCTHigh;

    if(cCalibTm.tlow_count != cTCTLowCount)
    {
        cParasChanged = true;
    }

    cCalibTm.tlow_count = cTCTLowCount;

    if(cCalibTm.thigh_count != cTCTHighCount)
    {
        cParasChanged = true;
    }

    cCalibTm.thigh_count = cTCTHighCount;

    cCalibTm.slope = getSlope(cCalibTm.thigh, cCalibTm.thigh_count,
                              cCalibTm.tlow, cCalibTm.tlow_count);

    cCalibTm.constant = getConstant(cCalibTm.thigh, cCalibTm.slope,
                                    cCalibTm.thigh_count);


    ui->lblTCZero->setText(getTemperatureCS(cCalibTm.tlow));
    ui->lblTCGain->setText(QString::number(cCalibTm.slope, 'f', 6));

}

void sCalibration::showPressureCalib()
{
    setPressureTabReadOnly(false);

    ui->cbPCTEnable->setChecked(CALIB_DEFAULT_TEMPERATURE_T_CONTROL_ENABLE);
    ui->lePCTemperature->setText(getTemperatureCS(CALIB_DEFAULT_TEMPERATURE_T));

    ui->pbPCSVSet->setEnabled(true);

    ui->lePCTemperature->setReadOnly(true); 
    ui->pbPCTSet->setEnabled(ui->cbPCTEnable->isChecked());

    ui->lePCPLow->setText(getPressureCS(cCalibPr.plow));
    ui->lePCPHigh->setText(getPressureCS(cCalibPr.phigh));

    ui->lblPCZero->setText(getPressureCS(cCalibPr.plow));
    ui->lblPCGain->setText(QString::number(cCalibPr.slope20, 'f', 6));

    ui->lblPCTemperature->setText("");
    ui->lblPCPressure->setText("");

    cPCPLow = cCalibPr.plow;
    cPCPHigh = cCalibPr.phigh;

    cPCPLowCount = cCalibPr.plow_count;
    cPCPHighCount = cCalibPr.phigh_count;

    ui->pbPCPLowSet->setText(tr("Set"));
    ui->pbPCPHighSet->setText(tr("Set"));

    ui->pbPCAutoStart->setEnabled(true);
    ui->pbPCAutoStop->setEnabled(false);

}

void sCalibration::updatePressureCalib()
{
    if(ui->twCalibration->currentWidget() == cWidgetPressure)
    {
        if(getPressureCS(cCalibPr.plow) != ui->lePCPLow->text()) cParasChanged = true;
        cCalibPr.plow = ui->lePCPLow->text().toDouble();

        if(getPressureCS(cCalibPr.phigh) != ui->lePCPHigh->text()) cParasChanged = true;
        cCalibPr.phigh = ui->lePCPHigh->text().toDouble();

        if(cCalibPr.plow != cPCPLow) cParasChanged = true;
        cCalibPr.plow = cPCPLow;

        if(cCalibPr.phigh != cPCPHigh) cParasChanged = true;
        cCalibPr.phigh = cPCPHigh;

        if(cCalibPr.plow_count != cPCPLowCount) cParasChanged = true;
        cCalibPr.plow_count = cPCPLowCount;

        if(cCalibPr.phigh_count != cPCPHighCount) cParasChanged = true;
        cCalibPr.phigh_count = cPCPHighCount;

        cCalibPr.slope20 = getSlope(cCalibPr.phigh, cCalibPr.phigh_count,
                                  cCalibPr.plow, cCalibPr.plow_count);

        cCalibPr.constant20 = getConstant(cCalibPr.phigh, cCalibPr.slope20,
                                        cCalibPr.phigh_count);

        ui->lblPCZero->setText(getPressureCS(cCalibPr.plow));
        ui->lblPCGain->setText(QString::number(cCalibPr.slope20, 'f', 6));

    }

    if(ui->twCalibration->currentWidget() == cWidgetPrLinear)
    {
        int tmp = 0;

        for(tmp=0; tmp < ui->tvPressure->rowCount(); tmp++)
        {
            if(cCalibPr.prl_enabled[tmp] != 1)
            {
                cParasChanged = true;
            }
            cCalibPr.prl_enabled[tmp] = 1;

            if(cCalibPr.prl_temperature[tmp] != ui->tvPressure->item(tmp, 0)->text().toInt())
            {
                cParasChanged = true;
            }

            cCalibPr.prl_temperature[tmp] = ui->tvPressure->item(tmp, 0)->text().toInt();

            if(cCalibPr.prl_low_correction[tmp] != ui->tvPressure->item(tmp, 1)->text().toDouble())
            {
                cParasChanged = true;
            }

            cCalibPr.prl_low_correction[tmp] = ui->tvPressure->item(tmp, 1)->text().toDouble();

            if(cCalibPr.prl_high_correction[tmp] != ui->tvPressure->item(tmp, 2)->text().toDouble())
            {
                cParasChanged = true;
            }

            cCalibPr.prl_high_correction[tmp] = ui->tvPressure->item(tmp, 2)->text().toDouble();


            cCalibPr.prl_slope[tmp] = getSlope(cCalibPr.prl_high_correction[tmp],
                                           cCalibPr.prl_high,
                                           cCalibPr.prl_low_correction[tmp],
                                           cCalibPr.prl_low);

            cCalibPr.prl_constant[tmp] = getConstant(cCalibPr.prl_high_correction[tmp],
                                                     cCalibPr.prl_slope[tmp],
                                                     cCalibPr.prl_high);

        }


        if(ui->tvPressure->rowCount())
        {
            if(cCalibPr.prl_index != ui->tvPressure->rowCount()-1)
            {
                cParasChanged = true;
            }

            cCalibPr.prl_index = ui->tvPressure->rowCount()-1;
        }

        for(; tmp < 19; tmp++)
        {
            if(cCalibPr.prl_enabled[tmp] != 0)
            {
                cParasChanged = true;
            }

            cCalibPr.prl_enabled[tmp] = 0;
        }
    }
}

void sCalibration::onLiveData(int cValvePosition, int cRawCTemperature, int cRawCPressure, int cCurrentUCError)
{
    cTemperatureCount = cRawCTemperature;
    cPressureCount = cRawCPressure;

    QString str;
    str = getTemperatureLive(cRawCTemperature);
    ui->lblTCTemperature->setText(str);
    ui->lblPCTemperature->setText(str);
    ui->lblPCTemperature_3->setText(str);

    str = getPressureLive(cRawCPressure);
    ui->lblPCPressure->setText(str);
    ui->lblPCPressure_2->setText(str);

    if(cValvePosition >=0 && cValvePosition <= 2)
        ui->lblSelectorValve->setText(ui->cbPCSelectorValve->itemText(cValvePosition));

}

void sCalibration::initAvg()
{
    cAvgSum = 0;
    cAvgCount = 0;
    cAvgWaitPeriod = AVG_WAIT_PERIOD;

    for(int tmp=0; tmp<AVG_BUFFER_SIZE; tmp++) cAvgBuffer[tmp] = 0;
}

int sCalibration::doAvg(int tmp)
{

    cAvgSum = cAvgSum - cAvgBuffer[cAvgCount] + tmp;

    cAvgBuffer[cAvgCount] = tmp;

    cAvgCount++;

    if(cAvgCount>=AVG_BUFFER_SIZE) cAvgCount = 0;

    return (cAvgSum / (AVG_BUFFER_SIZE));

}

int sCalibration::getAvg()
{
    return (cAvgSum / AVG_BUFFER_SIZE);
}

void sCalibration::updatePressureStatus()
{
    handleCalib();
}

void sCalibration::handleCalib()
{
    switch(cStage)
    {
        case 0: 

        break;

        case 2:

        if(cAvgWaitPeriod)
        {
            doAvg(cTemperatureCount);
            cAvgWaitPeriod--;
        }
        else
        {
            cTCTLow = ui->leTCTLow->text().toDouble();
            cTCTLowCount = getAvg();
            ui->pbTCTLowSet->setText(tr("Done"));
            cStage = 3;
        }

        break;

        case 3:
            ui->pbTCTLowSet->setText(tr("Set"));
            cStage = 0;
            setTempTabReadOnly(false);

        break;

        case 4:

        if(cAvgWaitPeriod)
        {
            doAvg(cTemperatureCount);
            cAvgWaitPeriod--;
        }
        else
        {
            cTCTHigh = ui->leTCTHigh->text().toDouble();
            cTCTHighCount = getAvg();
            ui->pbTCTHighSet->setText(tr("Done"));
            cStage = 5;
        }

        break;

        case 5:
            ui->pbTCTHighSet->setText(tr("Set"));
            cStage = 0;

            setTempTabReadOnly(false);

        break;

        case 6:

        if(cAvgWaitPeriod)
        {
            doAvg(cPressureCount);
            cAvgWaitPeriod--;
        }
        else
        {
            cPCPLow = ui->lePCPLow->text().toDouble();
            cPCPLowCount = getAvg();
            ui->pbPCPLowSet->setText(tr("Done"));
            cStage = 7;
        }

        break;

        case 7:
            ui->pbPCPLowSet->setText(tr("Set"));
            cStage = 0;
            setPressureTabReadOnly(false);
        break;

        case 8:

        if(cAvgWaitPeriod)
        {
            doAvg(cPressureCount);
            cAvgWaitPeriod--;
        }
        else
        {
            cPCPHigh = ui->lePCPHigh->text().toDouble();
            cPCPHighCount = getAvg();
            ui->pbPCPHighSet->setText(tr("Done"));
            cStage = 9;
        }

        break;

        case 9:
            ui->pbPCPHighSet->setText(tr("Set"));
            cStage = 0;
            setPressureTabReadOnly(false);

        break;

        case 10:

        break;

    }
}

void sCalibration::abortCurrentProcess()
{

    if(ui->twCalibration->currentWidget() == ui->tabTemperature)
    {
        cStage = 0;
        setTempTabReadOnly(false);
        ui->pbTCTLowSet->setText(tr("Set"));
        ui->pbTCTHighSet->setText(tr("Set"));
    }
    else if(ui->twCalibration->currentWidget() == cWidgetPressure)
    {
        cStage = 0;
        setPressureTabReadOnly(false);
        ui->pbPCPLowSet->setText(tr("Set"));
        ui->pbPCPHighSet->setText(tr("Set"));

    }
    else if(ui->twCalibration->currentWidget() == cWidgetPrLinearzation)
    {
        cStage = 0;
        setAutoCalibrationStatus(tr("Auto Calibration Stopped..."));
        setAutoCalibrationSubStatus(tr(""));
        setPRLRunning(2);
    }

}

QString sCalibration::getTemperatureCS(double tm) const
{
    return (QString::number(tm, 'f', 2));
}

QString sCalibration::getPressureCS(double pr) const
{
    return (QString::number(pr, 'f', 2));
}

int sCalibration::getTemperatureCount(double tm) 
{
    double dx, dy, sl, cc;
    dx = cTCTHigh - cTCTLow;
    dy = cTCTHighCount - cTCTLowCount;
    sl = dy/dx;
    cc = cTCTHighCount - (sl*cTCTHigh);

    double offset = ui->pbTCTOffset->text().toDouble();

    return (sl*(tm-offset)+cc); 

}

QString sCalibration::getTemperatureLive(int tm)
{
    double dx, dy, sl, cc;
    dx = cTCTHigh - cTCTLow;
    dy = cTCTHighCount - cTCTLowCount;
    sl = dx/dy;
    cc =  cTCTHigh - (sl*cTCTHighCount);

    double offset = ui->pbTCTOffset->text().toDouble();

    return (QString::number((sl*tm+cc) + offset, 'f', 2)); 

}

QString sCalibration::getPressureLive(int pr) const
{
    double dx, dy, sl, cc;
    dx = cPCPHigh - cPCPLow;
    dy = cPCPHighCount - cPCPLowCount;
    sl = dx/dy;
    cc =  cPCPHigh - (sl*cPCPHighCount);

    return (QString::number((sl*pr+cc), 'f', 2));

}

double sCalibration::getPressure20(int pr)
{
    return (cCalibPr.slope20 * pr + cCalibPr.constant20);
}

double sCalibration::getSlope(double tmh, int tmhc, double tmhl, int tmlc)
{
    double dx, dy;
    dx = tmh - tmhl;
    dy = tmhc - tmlc;
    return (dx/dy);
}

double sCalibration::getConstant(double tmh, double tmsl, int tmhc)
{
    return (tmh - (tmsl*tmhc));
}

int sCalibration::getTFirst()
{
    return ui->cbPCTFirst->currentText().toInt();
}

int sCalibration::getTFinal()
{
    return ui->cbPCTFinal->currentText().toInt();
}

void sCalibration::setTempTabReadOnly(bool tmp)
{
    if(tmp)
    {
        ui->cbTCalibMethod->setDisabled(true);
        ui->leTCTemperature->setReadOnly(true);
        ui->leTCTLow->setReadOnly(true);
        ui->leTCTHigh->setReadOnly(true);
        ui->leTCTOffset->setReadOnly(true);
        ui->cbTCTEnable->setDisabled(true);

        ui->pbTCTHighSet->setEnabled(false);
        ui->pbTCTLowSet->setEnabled(false);

        ui->twCalibration->setTabEnabled(1, false);
        ui->twCalibration->setTabEnabled(2, false);

        ui->pbTCTSet->setEnabled(false);
        ui->pbTCTOffset->setEnabled(false);
        ui->pbTCTOffsetSet->setEnabled(false);
        ui->pbSave->setEnabled(false);
        ui->pbExit->setEnabled(false);
    }
    else
    {
        ui->pbTCTHighSet->setEnabled(true);
        ui->pbTCTLowSet->setEnabled(true);
        ui->cbTCTEnable->setEnabled(true);
        ui->cbTCalibMethod->setEnabled(true);

        on_cbTCTEnable_clicked();
        ui->pbTCTOffset->setEnabled(true);
        ui->pbTCTOffsetSet->setEnabled(true);

        ui->leTCTLow->setReadOnly(false);
        ui->leTCTHigh->setReadOnly(false);
        ui->leTCTOffset->setReadOnly(false);

        ui->pbSave->setEnabled(true);
        ui->pbExit->setEnabled(true);

        ui->twCalibration->setTabEnabled(0, true);
        ui->twCalibration->setTabEnabled(1, true);
        ui->twCalibration->setTabEnabled(2, true);
    }
}

void sCalibration::setPressureTabReadOnly(bool tmp)
{
    if(tmp)
    {
        ui->lePCTemperature->setReadOnly(true);
        ui->lePCPLow->setReadOnly(true);
        ui->lePCPHigh->setReadOnly(true);
        ui->cbPCTEnable->setDisabled(true);
        ui->cbPCSelectorValve->setDisabled(true);

        ui->pbPCPHighSet->setEnabled(false);
        ui->pbPCPLowSet->setEnabled(false);
        ui->pbPCPCal->setEnabled(false);

        ui->twCalibration->setTabEnabled(0, false);
        ui->twCalibration->setTabEnabled(2, false);

        ui->pbPCTSet->setEnabled(false);
        ui->pbSave->setEnabled(false);
        ui->pbExit->setEnabled(false);

    }
    else
    {
        ui->lePCTemperature->setReadOnly(true); 
        ui->lePCPLow->setReadOnly(false);
        ui->lePCPHigh->setReadOnly(false);
        ui->cbPCTEnable->setDisabled(false);
        ui->cbPCSelectorValve->setEnabled(true);

        ui->pbPCPHighSet->setEnabled(true);
        ui->pbPCPLowSet->setEnabled(true);
        ui->pbPCPCal->setEnabled(true);

        ui->pbPCTSet->setEnabled(true);
        ui->pbSave->setEnabled(true);
        ui->pbExit->setEnabled(true);

        on_cbPCTEnable_clicked();

        ui->twCalibration->setTabEnabled(0, true);
        ui->twCalibration->setTabEnabled(1, true);
        ui->twCalibration->setTabEnabled(2, true);
    }
}

void sCalibration::setPRLRunning(int tmp)
{
    if(tmp==1)
    {

        for(int sp=0; sp<19 && cCalibPr.prl_enabled[sp]; sp++)
        {
            if(cCalibPr.prl_temperature[sp] == getTFirst())
            {
                cPrAutoCalibIndex = sp;
                break;
            }
        }

        ui->cbPCTFirst->setEnabled(false);
        ui->cbPCTFinal->setEnabled(false);
        ui->pbPCTableShow->setEnabled(false);

        ui->pbPCAutoStart->setEnabled(false);
        ui->pbPCAutoStop->setEnabled(true);

        ui->pbSave->setEnabled(false);
        ui->pbExit->setEnabled(false);

        ui->tvLivePrTable->clearContents();
        ui->tvLivePrTable->model()->removeRows(0, ui->tvLivePrTable->rowCount());
        ui->tvLivePrTable->show();

        cEnSwitch = false;
        qDebug() << "wCalibR:" << cEnSwitch;

        ui->twCalibration->setTabEnabled(0, false);
        ui->twCalibration->setTabEnabled(2, false);

    }
    else if(tmp==2) //error
    {
        cPrAutoCalibIndex = 0;

        readFile();

        ui->cbPCTFirst->setEnabled(true);
        ui->cbPCTFinal->setEnabled(true);
        ui->pbPCTableShow->setEnabled(true);

        ui->pbPCAutoStart->setEnabled(true);
        ui->pbPCAutoStop->setEnabled(false);

        ui->pbSave->setEnabled(true);
        ui->pbExit->setEnabled(true);
        qDebug() << "wCalibE:" << cEnSwitch;

        ui->twCalibration->setTabEnabled(0, true);
        ui->twCalibration->setTabEnabled(2, true);
    }
    else
    {
        cEnSwitch = true;

        ui->cbPCTFirst->setEnabled(true);
        ui->cbPCTFinal->setEnabled(true);
        ui->pbPCTableShow->setEnabled(true);

        ui->pbPCAutoStart->setEnabled(true);
        ui->pbPCAutoStop->setEnabled(false);

        ui->pbSave->setEnabled(true);
        ui->pbExit->setEnabled(true);

        if(!tmp) on_pbPCTableShow_clicked();

        qDebug() << "wCalib:" << cEnSwitch;

        ui->twCalibration->setTabEnabled(0, true);
        ui->twCalibration->setTabEnabled(2, true);

    }
}

bool sCalibration::isLinerzationVisible()
{
    return ui->tabPrLinerzation->isVisible();
}

void sCalibration::setAutoCalibrationStatus(QString tmp)
{
    ui->lblAutoCalibStatus->setText(tmp);
}

void sCalibration::setAutoCalibrationSubStatus(QString tmp)
{
    ui->lblAutoCalibSubStatus->setText(tmp);
}

void sCalibration::setZero(int tmp, double ctmp)
{
    cCalibPr.prl_enabled[cPrAutoCalibIndex] = 1;
    cCalibPr.prl_temperature[cPrAutoCalibIndex] = (int) ctmp; 
    cCalibPr.prl_low = cCalibPr.plow;
    cCalibPr.prl_high = cCalibPr.phigh;
    cCalibPr.prl_low_correction[cPrAutoCalibIndex] =  cCalibPr.plow - getPressure20(tmp);
}

void sCalibration::setAmbient(int tmp, double ctmp)
{
    cCalibPr.prl_temperature[cPrAutoCalibIndex] = (int) ctmp;
    cCalibPr.prl_high_correction[cPrAutoCalibIndex] = cCalibPr.phigh - getPressure20(tmp);

    setLivePrTable();

    cPrAutoCalibIndex++;
}

void sCalibration::setLivePrTable()
{
    int row = ui->tvLivePrTable->rowCount();

    ui->tvLivePrTable->insertRow(row);
    ui->tvLivePrTable->setRowHeight(0, 31);

    QString str = QString::number(cCalibPr.prl_temperature[cPrAutoCalibIndex]);

    ui->tvLivePrTable->setItem(row, 0, new QTableWidgetItem(str));
    ui->tvLivePrTable->item(row, 0)->setTextAlignment(Qt::AlignRight);

    str = QString::number(cCalibPr.prl_low_correction[cPrAutoCalibIndex], 'f', 2);
    ui->tvLivePrTable->setItem(row, 1, new QTableWidgetItem(str));
    ui->tvLivePrTable->item(row, 1)->setTextAlignment(Qt::AlignRight);

    str = QString::number(cCalibPr.prl_high_correction[cPrAutoCalibIndex], 'f', 2);
    ui->tvLivePrTable->setItem(row, 2, new QTableWidgetItem(str));
    ui->tvLivePrTable->item(row, 2)->setTextAlignment(Qt::AlignRight);

    str = QString::number(cCalibPr.prl_low - cCalibPr.prl_low_correction[cPrAutoCalibIndex], 'f', 1);

    ui->tvLivePrTable->setItem(row, 3, new QTableWidgetItem(str));
    ui->tvLivePrTable->item(row, 3)->setTextAlignment(Qt::AlignRight);

    str = QString::number(cCalibPr.prl_high - cCalibPr.prl_high_correction[cPrAutoCalibIndex], 'f', 1);

    ui->tvLivePrTable->setItem(row, 4, new QTableWidgetItem(str));
    ui->tvLivePrTable->item(row, 4)->setTextAlignment(Qt::AlignRight);

}

int sCalibration::getLinerizationCount()
{
    for(int tmp=18; tmp>=0; tmp--)
    {
        if(cCalibPr.prl_enabled[tmp]) return tmp+1;
    }

    return 0;
}

void sCalibration::setWaitACKStatus(bool tmp)
{

    qDebug() << "Calib setWaitACKStatus:" << tmp;

    if(ui->twCalibration->currentWidget() == ui->tabTemperature)
    {

        if(tmp)
        {
            ui->cbTCTEnable->setEnabled(false);
            ui->pbTCTSet->setEnabled(false);
            ui->twCalibration->setTabEnabled(1, false);
            ui->twCalibration->setTabEnabled(2, false);
            ui->pbExit->setEnabled(false);
        }
        else
        {
            ui->cbTCTEnable->setEnabled(true);
            ui->pbTCTSet->setEnabled(ui->cbTCTEnable->isChecked());

            if(cEnSwitch)
            {
                ui->twCalibration->setTabEnabled(1, true);
                ui->twCalibration->setTabEnabled(2, true);
            }
            ui->pbExit->setEnabled(true);
        }

        //qDebug() << "tabTemperature";

    }
    else if(ui->twCalibration->currentWidget() == cWidgetPressure)
    {
        if(tmp)
        {
            ui->cbPCTEnable->setEnabled(false);
            ui->pbPCTSet->setEnabled(false);
            ui->pbPCSVSet->setEnabled(false);
            ui->twCalibration->setTabEnabled(0, false);
            ui->twCalibration->setTabEnabled(2, false);
            ui->pbPCPCal->setEnabled(false);
            ui->pbExit->setEnabled(false);
        }
        else
        {
            ui->cbPCTEnable->setEnabled(true);
            ui->pbPCTSet->setEnabled(ui->cbPCTEnable->isChecked());
            ui->pbPCSVSet->setEnabled(true);
            if(cEnSwitch)
            {
                ui->twCalibration->setTabEnabled(0, true);
                ui->twCalibration->setTabEnabled(2, true);
            }
            ui->pbPCPCal->setEnabled(true);
            ui->pbExit->setEnabled(true);
        }

        //qDebug() << "cWidgetPressure";
    }
    else if(ui->twCalibration->currentWidget() == cWidgetPrLinearzation)
    {
        if(tmp)
        {
            //ui->pbPCAutoStart->setEnabled(false);
            //ui->pbPCAutoStop->setEnabled(false);

            ui->twCalibration->setTabEnabled(0, false);
            ui->twCalibration->setTabEnabled(2, false);
            ui->pbExit->setEnabled(false);
        }
        else
        {
            //ui->pbPCAutoStart->setEnabled(true);
            //ui->pbPCAutoStop->setEnabled(true);
            if(cEnSwitch)
            {
                ui->twCalibration->setTabEnabled(0, true);
                ui->twCalibration->setTabEnabled(2, true);
            }
            ui->pbExit->setEnabled(true);
        }

        //qDebug() << "cWidgetPrLinearzation";
    }
    /*
    else if(ui->twCalibration->currentWidget() == cWidgetPrLinear)
    {
        qDebug() << "cWidgetPrLinear";
    }
    */
}

bool sCalibration::getWaitACKStatus()
{
    return true;
}

void sCalibration::hideAfterACK(bool tmp)
{
    qDebug() << "hideAfterACK:" << tmp;

    if(!tmp)
    {
        cHide = false;
        //3-May-2023 this->hide();
    }
    else cHide = true;
}

bool sCalibration::getHideAfterACK()
{
    return cHide;
}

bool sCalibration::isSwitchEnabled(int tmp)
{
    if(cStage) return false;    //13-May-2023

    checkExit(tmp);
    return cEnSwitch;
}

void sCalibration::onShowKeypad(int tmp)
{
    emit showKeypad(QObject::sender(), KAYPAD_NUMERIC, false);
}

void sCalibration::on_pbSave_clicked()
{
    updateTemperatureCalib();
    updatePressureCalib();

    if(saveFile())
    {
        if(ui->twCalibration->currentWidget() == ui->tabTemperature)
        {
            emit showMsgBox(tr("Calibration Setup"), tr("Temperature Calibration Saved!"));
        }
        else if(ui->twCalibration->currentWidget() == cWidgetPressure)
        {
            emit showMsgBox(tr("Calibration Setup"), tr("Pressure Calibration Saved!"));
        }
        else if(ui->twCalibration->currentWidget() == cWidgetPrLinear)
        {
            emit showMsgBox(tr("Calibration Setup"), tr("Linear Table Saved!"));
        }
    }

    if(ui->twCalibration->currentWidget() == cWidgetPrLinearzation)
    {
        ui->twCalibration->setEnabled(false); 
        ui->twCalibration->removeTab(1);
        ui->twCalibration->insertTab(1, cWidgetPressure, cStringPressure);
        ui->twCalibration->setEnabled(true);
        ui->twCalibration->setCurrentIndex(1);

        ui->pbSave->show();
        ui->pbExit->setText(tr("Home"));
    }

}

void sCalibration::checkExit(int tmp)
{
    updateTemperatureCalib();

    updatePressureCalib();

    if(ui->pbExit->text() == tr("Back"))
    {
        {
            if(ui->twCalibration->currentWidget() == cWidgetPrLinearzation)
            {
               qDebug() << "cWidgetPrLinearzation";

               if(cEnSwitch)
               {
                    ui->twCalibration->setEnabled(false);
                    ui->twCalibration->removeTab(1);
                    ui->twCalibration->insertTab(1, cWidgetPressure, cStringPressure);
                    ui->twCalibration->setEnabled(true);
                    ui->twCalibration->setCurrentIndex(1);

                    ui->pbSave->show();
                    ui->pbExit->setText(tr("Home"));

                    ui->twCalibration->setTabEnabled(0, true);
                    ui->twCalibration->setTabEnabled(1, true);
                    ui->twCalibration->setTabEnabled(2, true);
               }

            }
            else if(ui->twCalibration->currentWidget() == cWidgetPrLinear)
            {
                qDebug() << "cWidgetPrLinear";

                if(!cParasChanged)
                {
                    ui->twCalibration->setEnabled(false);
                    ui->twCalibration->removeTab(1);
                    ui->twCalibration->insertTab(1, cWidgetPrLinearzation, cStringPrLinearzation);
                    ui->twCalibration->setCurrentIndex(1);
                    ui->twCalibration->setEnabled(true);

                    ui->twCalibration->setTabEnabled(0, false);
                    ui->twCalibration->setTabEnabled(2, false);

                    ui->pbSave->hide();
                    ui->pbExit->setText(tr("Back"));
                }
                else
                {
                    cEnSwitch = false;
                    emit getConfirmation(M_CONFIRM_CALIBRATION, tmp);
                }
            }

            setWaitACKStatus(false);
        }

    }
    else //Exit
    {
        if(cParasChanged)
        {
            cEnSwitch = false;
            emit getConfirmation(M_CONFIRM_CALIBRATION, tmp);
        }

        if(!cParasChanged)
        {
            hideAfterACK(true);
            int tc = getTemperatureCount(20);
            emit sendCommand(cProtocol.sendMeasuring(0, tc), this);
        }


        if(!cParasChanged)
        {


            this->hide();
            emit showHome(false);
        }

    }
}

void sCalibration::on_pbExit_clicked()
{

    checkExit(M_MEASURING);

    /*
    if(ui->pbExit->text() != tr("Back"))

    if(!cParasChanged)
    {
        this->hide();
        emit showHome(false);
    }
    */
}

void sCalibration::on_pbPCPCal_clicked()
{
    ui->twCalibration->setEnabled(false); 
    ui->twCalibration->removeTab(1);
    ui->twCalibration->insertTab(1, cWidgetPrLinearzation, cStringPrLinearzation);
    ui->twCalibration->setEnabled(true); 
    ui->twCalibration->setCurrentIndex(1);


    ui->twCalibration->setTabEnabled(0, false);
    ui->twCalibration->setTabEnabled(2, false);

    ui->pbSave->hide();
    ui->pbExit->setText(tr("Back"));
}

void sCalibration::on_pbTCTOffset_clicked()
{
    if(ui->grOffset->isVisible())
        ui->grOffset->setVisible(false);
    else
        ui->grOffset->setVisible(true);
}

void sCalibration::on_tvPressure_cellClicked(int row, int column)
{

    if(column >=1 && column <=2)
    {
        QString str = ui->tvPressure->item(row, column)->text();

        ui->lePrHidden->setText(str);
        emit showKeypad(ui->lePrHidden, KAYPAD_NUMERIC, false);
    }
}

void sCalibration::on_lePrHidden_editingFinished()
{
    ui->tvPressure->currentItem()->setText(ui->lePrHidden->text());
}

void sCalibration::on_pbTCTOffsetSet_clicked()
{
    ui->pbTCTOffset->setText(ui->leTCTOffset->text());
    ui->grOffset->hide();
}

void sCalibration::on_pbTCTHighSet_clicked()
{
    if(ui->leTCTHigh->hasAcceptableInput())
    {

        ui->pbTCTHighSet->setText(tr("Wait"));
        setTempTabReadOnly(true);
        initAvg();
        cStage = 4;
    }
}

void sCalibration::on_pbTCTLowSet_clicked()
{
    if(ui->leTCTLow->hasAcceptableInput())
    {
        ui->pbTCTLowSet->setText(tr("Wait"));
        setTempTabReadOnly(true);
        initAvg();
        cStage = 2;
    }
}

void sCalibration::on_pbPCPHighSet_clicked()
{
    if(ui->lePCPHigh->hasAcceptableInput())
    {
        ui->pbPCPHighSet->setText(tr("Wait"));
        setPressureTabReadOnly(true);
        ui->twCalibration->setTabEnabled(0, false);
        ui->twCalibration->setTabEnabled(2, false);

        initAvg();
        cStage = 8;
    }
}

void sCalibration::on_pbPCPLowSet_clicked()
{
    if(ui->lePCPLow->hasAcceptableInput())
    {

        ui->pbPCPLowSet->setText(tr("Wait"));
        setPressureTabReadOnly(true);
        ui->twCalibration->setTabEnabled(0, false);
        ui->twCalibration->setTabEnabled(2, false);

        initAvg();
        cStage = 6;
    }
}

void sCalibration::on_pbTCTSet_clicked()
{
    if(ui->leTCTemperature->hasAcceptableInput())
    {
        double tm = ui->leTCTemperature->text().toDouble();
        int tmp = getTemperatureCount(tm);

        setWaitACKStatus(true);
        emit sendCommand(cProtocol.sendTemperature(tmp), this);
    }
}

void sCalibration::on_cbTCTEnable_clicked()
{
    ui->leTCTemperature->setReadOnly(!ui->cbTCTEnable->isChecked());
    ui->pbTCTSet->setEnabled(ui->cbTCTEnable->isChecked());
    ui->cbTCalibMethod->setEnabled(!ui->cbTCTEnable->isChecked());

    if(!ui->cbTCTEnable->isChecked())
    {
        setWaitACKStatus(true);
        emit sendCommand(cProtocol.sendMeasuringStart(1, 0), this);
    }
}

void sCalibration::on_cbTCalibMethod_currentIndexChanged(int index)
{
    if(!index) ui->cbTCTEnable->setEnabled(true);
    else ui->cbTCTEnable->setEnabled(false);
}

void sCalibration::ontextChanged(QString tmp)
{
    QLineEdit *tle = qobject_cast<QLineEdit *>(QObject::sender());

    if(tle)
    {
        if(!tle->hasAcceptableInput())
        {
            tle->setProperty("error", true);
            tle->style()->polish(tle);

            if(ui->twCalibration->currentIndex() != 0)
                ui->twCalibration->setTabEnabled(0, false);

            if(ui->twCalibration->currentIndex() != 1)
                ui->twCalibration->setTabEnabled(1, false);

            if(ui->twCalibration->currentIndex() != 2)
                ui->twCalibration->setTabEnabled(2, false);

            ui->pbPCPCal->setEnabled(false);

        }
        else
        {
            tle->setProperty("error", false);
            tle->style()->polish(tle);

            ui->twCalibration->setTabEnabled(0, true);
            ui->twCalibration->setTabEnabled(1, true);
            ui->twCalibration->setTabEnabled(2, true);

            ui->pbPCPCal->setEnabled(true);

        }
    }
}

void sCalibration::on_cbPCTEnable_clicked()
{
    ui->lePCTemperature->setReadOnly(true); 
    ui->pbPCTSet->setEnabled(ui->cbPCTEnable->isChecked());

    if(!ui->cbPCTEnable->isChecked())
    {
        setWaitACKStatus(true);
        emit sendCommand(cProtocol.sendMeasuringStart(1, 0), this);
    }
}

void sCalibration::on_pbPCTSet_clicked()
{
    if(ui->lePCTemperature->hasAcceptableInput())
    {
        double tm = ui->lePCTemperature->text().toDouble();

        setWaitACKStatus(true);
        int tmp = getTemperatureCount(tm);
        emit sendCommand(cProtocol.sendTemperature(tmp), this);

    }
}

void sCalibration::on_pbTouchCalibrate_clicked()
{
    QProcess process;
    //process.start("/usr/bin/ts_calibrate -r 1");
    process.start("/usr/bin/ts_calibrate");
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    QString err = process.readAllStandardError();

    emit updateMainWindow();

}

void sCalibration::on_twCalibration_currentChanged(int index)
{
    bool sc = false;

    if(!isVisible()) return;

    if(index==2) ui->pbSave->hide();
    else ui->pbSave->show();

    if(ui->twCalibration->isEnabled() && (index < 2)  &&
       ui->twCalibration->currentWidget() != cWidgetPrLinear)
    {
        sc = true;
        //emit sendCommand(cProtocol.sendMeasuring(1, 0));
        emit sendCommand(cProtocol.sendMeasuringStart(1, 0), this);
    }

    if(cPrevTab!=index)
    {
        if(!cPrevTab)
        {
            updateTemperatureCalib();

            if(cParasChanged)
            {
                emit getConfirmation(M_CONFIRM_CALIBRATION_SWITCH, M_MEASURING);
            }
        }
        else
        {
            updatePressureCalib();

            if(cParasChanged)
            {
                emit getConfirmation(M_CONFIRM_CALIBRATION_SWITCH, M_MEASURING);
            }
        }

        cPrevTab = index;

    }

    if(!index) showTemperatureCalib();
    else if(index==1)showPressureCalib();

    if(sc) setWaitACKStatus(true);

}

void sCalibration::on_pbPCAutoStart_clicked()
{
     emit runClicked(MS_LINEARIZATION_RUN, false);
}

void sCalibration::on_pbPCAutoStop_clicked()
{
    emit runClicked(MS_LINEARIZATION_STOP, false);
}

void sCalibration::on_cbPCSelectorValve_currentIndexChanged(int index)
{
    if(!ui->tabPressure->isVisible()) return;

    //emit sendCommand(cProtocol.sendValvePosition(ui->cbPCSelectorValve->currentIndex()));
}

void sCalibration::on_pbPCTableShow_clicked()
{
    ui->pbSave->show();

    ui->lblAutoCalibStatus->setText("");
    ui->lblAutoCalibSubStatus->setText("");

    ui->tvLivePrTable->clearContents();
    ui->tvLivePrTable->model()->removeRows(0, ui->tvLivePrTable->rowCount());
    ui->tvLivePrTable->hide();

    ui->twCalibration->setEnabled(false);
    ui->twCalibration->removeTab(1);
    ui->twCalibration->insertTab(1, cWidgetPrLinear, cStringPrLinear);

    ui->twCalibration->setEnabled(true);

    ui->twCalibration->setCurrentIndex(1);

    ui->twCalibration->setTabEnabled(0, false);
    ui->twCalibration->setTabEnabled(2, false);

    ui->tvPressure->clearContents();
    ui->tvPressure->model()->removeRows(0, ui->tvPressure->rowCount());

    for(int tmp=18; tmp>=0; tmp--)
    {
        if(cCalibPr.prl_enabled[tmp])
        {
            ui->tvPressure->insertRow(0);
            ui->tvPressure->setRowHeight(0, 31);

            QString str = QString::number(cCalibPr.prl_temperature[tmp]);

            ui->tvPressure->setItem(0, 0, new QTableWidgetItem(str));
            ui->tvPressure->item(0, 0)->setTextAlignment(Qt::AlignRight);

            str = QString::number(cCalibPr.prl_low_correction[tmp], 'f', 2);
            ui->tvPressure->setItem(0, 1, new QTableWidgetItem(str));
            ui->tvPressure->item(0, 1)->setTextAlignment(Qt::AlignRight);

            str = QString::number(cCalibPr.prl_high_correction[tmp], 'f', 2);
            ui->tvPressure->setItem(0, 2, new QTableWidgetItem(str));
            ui->tvPressure->item(0, 2)->setTextAlignment(Qt::AlignRight);

            str = QString::number(cCalibPr.prl_low - cCalibPr.prl_low_correction[tmp], 'f', 1);
            ui->tvPressure->setItem(0, 3, new QTableWidgetItem(str));
            ui->tvPressure->item(0, 3)->setTextAlignment(Qt::AlignRight);

            str = QString::number(cCalibPr.prl_high - cCalibPr.prl_high_correction[tmp], 'f', 1);
            ui->tvPressure->setItem(0, 4, new QTableWidgetItem(str));
            ui->tvPressure->item(0, 4)->setTextAlignment(Qt::AlignRight);
        }
    }
}

void sCalibration::on_pbPCSVSet_clicked()
{
    setWaitACKStatus(true);
    emit sendCommand(cProtocol.sendValvePosition(ui->cbPCSelectorValve->currentIndex()), this);
}

void sCalibration::on_imageCapture_clicked()
{
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

        //QString filename = QApplication::applicationDirPath() + QString("/screenshot/scalibration_%1.png").arg(timestamp);
        QString filename = QString("/run/media/sda1/screenshot/_%1_scalibration.png").arg(timestamp);
        QWidget *widget = QApplication::activeWindow();
        QPixmap pixmap = QPixmap::grabWidget(widget);
        //    QString path = QApplication::applicationDirPath() + "/screenshot/screenshot.png";
        ui->imageCapture->setFocusPolicy(Qt::NoFocus);
        qDebug()<<"path : "<<filename;
        pixmap.save(QString(filename));
//        emit showMsgBox("Screenshot","Screenshot saved!");
    }else{
        qDebug()<<"folder doesn't exist";
//        emit showMsgBox("Screenshot","USB Not Found!");
    }
}
