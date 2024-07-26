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
    cParaMethodVolumeChanged = false;

    ui->grOffset->hide();

    cWidgetPressure = ui->tabPressure;
    cStringPressure = ui->twCalibration->tabText(1);

    cWidgetPrLinear = ui->tabPrLinear;
    cStringPrLinear = ui->twCalibration->tabText(2);

    cWidgetPrLinearzation = ui->tabPrLinerzation;
    cStringPrLinearzation = ui->twCalibration->tabText(3);

    cWidgetMethodVolume = ui->tabMethodVolume;
    cStringMethodVolume = ui->twCalibration->tabText(5);

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
    MethodVolumeDefault();
    cParasChanged = false;
    cParaMethodVolumeChanged = false;
    cEnSwitch = true;
    D6377Vl_updated = false;

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

    D6377vl_Range = 5.0;

    ui->imageCapture->hide();

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

    qDebug()<<"IS_ADMIN_USER"<<IS_ADMIN_USER;
    if(IS_ADMIN_USER){
        ui->twCalibration->insertTab(2,cWidgetMethodVolume,cStringMethodVolume);
//        showMethodVolume();
    }else{
        ui->twCalibration->removeTab(2);
    }

    cPrevMethod = M_METHOD_D5191;
    ui->cbMethod->setCurrentIndex(M_METHOD_D5191);

    showMethodVolume();
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

void sCalibration::MethodVolumeDefault()
{
    cCalibSingleD5191.StageVolume = DEFAULT_STAGE_VOLUME;
    cCalibSingleD5191.FirstVolume = DEFAULT_THIRD_VOLUME;
    cCalibSingleD5191.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibSingleD5191.ThirdVOlume = DEFAULT_THIRD_VOLUME;
//    cCalibSingleD5191.single_expansion = DEFAULT_D5191_SINGLE_EXPAN_ENABLED;

    cCalibD5191.StageVolume = DEFAULT_STAGE_VOLUME;
    cCalibD5191.FirstVolume = DEFAULT_FIRST_VOLUME;
    cCalibD5191.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibD5191.ThirdVOlume = DEFAULT_THIRD_VOLUME;
//    cCalibD5191.single_expansion = DEFAULT_D5191_SINGLE_EXPAN_ENABLED;

    cCalibD6377.StageVolume = DEFAULT_STAGE_VOLUME;
    cCalibD6377.FirstVolume = DEFAULT_THIRD_VOLUME;
    cCalibD6377.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibD6377.ThirdVOlume = DEFAULT_THIRD_VOLUME;

    cCalibD6378.StageVolume = DEFAULT_STAGE_VOLUME;
    cCalibD6378.FirstVolume = DEFAULT_FIRST_VOLUME;
    cCalibD6378.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibD6378.ThirdVOlume = DEFAULT_THIRD_VOLUME;

    cCalibD5188.StageVolume = DEFAULT_MIN_VOLUME;
    cCalibD5188.FirstVolume = DEFAULT_MAX_VOLUME;
    cCalibD5188.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibD5188.ThirdVOlume = DEFAULT_THIRD_VOLUME;

    cCalibFree1.StageVolume = DEFAULT_STAGE_VOLUME;
    cCalibFree1.FirstVolume = DEFAULT_FIRST_VOLUME;
    cCalibFree1.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibFree1.ThirdVOlume = DEFAULT_THIRD_VOLUME;

    cCalibFree2.StageVolume = DEFAULT_STAGE_VOLUME;
    cCalibFree2.FirstVolume = DEFAULT_FIRST_VOLUME;
    cCalibFree2.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibFree2.ThirdVOlume = DEFAULT_THIRD_VOLUME;

    cCalibFree3.StageVolume = DEFAULT_STAGE_VOLUME;
    cCalibFree3.FirstVolume = DEFAULT_FIRST_VOLUME;
    cCalibFree3.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibFree3.ThirdVOlume = DEFAULT_THIRD_VOLUME;

    cCalibFree4.StageVolume = DEFAULT_STAGE_VOLUME;
    cCalibFree4.FirstVolume = DEFAULT_FIRST_VOLUME;
    cCalibFree4.SecondVolume = DEFAULT_SECOND_VOLUME;
    cCalibFree4.ThirdVOlume = DEFAULT_THIRD_VOLUME;

    qDebug()<<"cCalibD6377.StageVolume"<<cCalibD6377.StageVolume;
    qDebug()<<"cCalibD6377.FirstVolume"<<cCalibD6377.FirstVolume;
    qDebug()<<"cCalibD5188.StageVolume"<<cCalibD5188.StageVolume;
    qDebug()<<"cCalibD5188.FirstVolume"<<cCalibD5188.FirstVolume;


}

//void sCalibration::MethodVolumeSetDefualt(METHOD_VOLUMES_CALIB mvc){
//    MethodVolumeCal = mvc;
//}

bool sCalibration::readFile()
{
    QString fname = QApplication::applicationDirPath() + FN_TCALIBRATION_SETUP;

    QFile in(fname);

    cEnSwitch = true;
//    MethodVolumeDefault();

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
//        MethodVolumeDefault();
        return false;
    }

}

bool sCalibration::readMethodVolumeFile()
{
    QString fname = QApplication::applicationDirPath() + FN_METHOD_VOLUME_SETUP;

    QFile in(fname);
    cEnSwitch = true;

    if(in.open(QIODevice::ReadOnly))
    {
        in.read((char *)&cCalibSingleD5191, sizeof(cCalibSingleD5191));

        in.read((char *)&cCalibD5191, sizeof(cCalibD5191));
        in.read((char *)&cCalibD6377, sizeof(cCalibD6377));
        in.read((char *)&cCalibD6378, sizeof(cCalibD6378));
        in.read((char *)&cCalibD5188, sizeof(cCalibD5188));

        in.read((char *)&cCalibFree1, sizeof(cCalibFree1));
        in.read((char *)&cCalibFree2, sizeof(cCalibFree2));
        in.read((char *)&cCalibFree3, sizeof(cCalibFree3));
        in.read((char *)&cCalibFree4, sizeof(cCalibFree4));

        in.close();

        cParaMethodVolumeChanged = false;

        return true;

    }
    else
    {
        MethodVolumeDefault();
        return false;
    }
}

bool sCalibration::saveMethodVolumeFile()
{
    QString fname = QApplication::applicationDirPath() + FN_METHOD_VOLUME_SETUP;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        out.write((char *)&cCalibSingleD5191, sizeof(cCalibSingleD5191));

        out.write((char *)&cCalibD5191, sizeof(cCalibD5191));
        out.write((char *)&cCalibD6377, sizeof(cCalibD6377));
        out.write((char *)&cCalibD6378, sizeof(cCalibD6378));
        out.write((char *)&cCalibD5188, sizeof(cCalibD5188));

        out.write((char *)&cCalibFree1, sizeof(cCalibFree1));
        out.write((char *)&cCalibFree2, sizeof(cCalibFree2));
        out.write((char *)&cCalibFree3, sizeof(cCalibFree3));
        out.write((char *)&cCalibFree4, sizeof(cCalibFree4));

        out.close();
        cParaMethodVolumeChanged = false;
        cEnSwitch = true;
        if(D6377Vl_updated){
            D6377Vl_updated = false;
        }else{
            emit showMsgBox(tr("Calibration Setup"), tr("Volume Adjustment Saved!"));
        }

    }
    else
    {
        cEnSwitch = false;
        emit showMsgBox(tr("Calibration Setup"), tr("Error Saving File!"));
    }

}


bool sCalibration::saveFile()
{
//    if(ui->tabMethodVolume->isVisible()){
//        return saveMethodVolumeFile();
//    }

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

void sCalibration::setMethods(const QStringList tmp)
{
    ui->cbMethod->clear();
    ui->cbMethod->insertItems(0, tmp);
}

void sCalibration::showMethodVolume(){

//    cPrevMethod = M_METHOD_D5191;
//    ui->cbMethod->setCurrentIndex(M_METHOD_D5191);

//    if(ui->cbMethod->currentIndex()==M_METHOD_D5188 || ui->cbMethod->currentIndex()==M_METHOD_D6377){
//        MethodSingleExpansion();
//    }else{
//        MethodTripleExpansion();
//    }
    if(ui->cbMethod->currentIndex()==M_METHOD_D5191) {
        if(ui->cbSingleExpEnable->checkState() == 0)
            showVolumeD5191();
        else
            showVolumeSinExpD5191();
    }
    if(ui->cbMethod->currentIndex()==M_METHOD_D6377) showVolumeD6377();
    if(ui->cbMethod->currentIndex()==M_METHOD_D6378) showVolumeD6378();
    if(ui->cbMethod->currentIndex()==M_METHOD_D5188) showVolumeD5188();
    if(ui->cbMethod->currentIndex()==M_METHOD_FREE1) showVolumeFree1();
    if(ui->cbMethod->currentIndex()==M_METHOD_FREE2) showVolumeFree2();
    if(ui->cbMethod->currentIndex()==M_METHOD_FREE3) showVolumeFree3();
    if(ui->cbMethod->currentIndex()==M_METHOD_FREE4) showVolumeFree4();

}

void sCalibration::showVolumeSinExpD5191(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibSingleD5191.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibSingleD5191.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibSingleD5191.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibSingleD5191.ThirdVOlume));
//    ui->cbSingleExpEnable->setChecked(cCalibD5191.single_expansion);

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->hide();
    ui->leVolume2->hide();
    ui->volumeSecondP->hide();
    ui->volumeSecondN->hide();

    ui->lblPara4->hide();
    ui->leVolume3->hide();
    ui->volumeThirdP->hide();
    ui->volumeThirdN->hide();

    ui->lblPara5->show();
    ui->cbSingleExpEnable->show();

}

void sCalibration::showVolumeD5191(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibD5191.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibD5191.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibD5191.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibD5191.ThirdVOlume));
//    ui->cbSingleExpEnable->setChecked(cCalibD5191.single_expansion);

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->show();
    ui->leVolume2->show();
    ui->volumeSecondP->show();
    ui->volumeSecondN->show();

    ui->lblPara4->show();
    ui->leVolume3->show();
    ui->volumeThirdP->show();
    ui->volumeThirdN->show();

    ui->lblPara5->show();
    ui->cbSingleExpEnable->show();

}

void sCalibration::showVolumeD6377(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibD6377.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibD6377.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibD6377.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibD6377.ThirdVOlume));

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->hide();
    ui->leVolume2->hide();
    ui->volumeSecondP->hide();
    ui->volumeSecondN->hide();

    ui->lblPara4->hide();
    ui->leVolume3->hide();
    ui->volumeThirdP->hide();
    ui->volumeThirdN->hide();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

}

void sCalibration::showVolumeD6378(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibD6378.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibD6378.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibD6378.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibD6378.ThirdVOlume));

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->show();
    ui->leVolume2->show();
    ui->volumeSecondP->show();
    ui->volumeSecondN->show();

    ui->lblPara4->show();
    ui->leVolume3->show();
    ui->volumeThirdP->show();
    ui->volumeThirdN->show();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

}

void sCalibration::showVolumeD5188(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibD5188.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibD5188.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibD5188.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibD5188.ThirdVOlume));

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->hide();
    ui->leVolume2->hide();
    ui->volumeSecondP->hide();
    ui->volumeSecondN->hide();

    ui->lblPara4->hide();
    ui->leVolume3->hide();
    ui->volumeThirdP->hide();
    ui->volumeThirdN->hide();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

}

void sCalibration::showVolumeFree1(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibFree1.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibFree1.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibFree1.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibFree1.ThirdVOlume));

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->show();
    ui->leVolume2->show();
    ui->volumeSecondP->show();
    ui->volumeSecondN->show();

    ui->lblPara4->show();
    ui->leVolume3->show();
    ui->volumeThirdP->show();
    ui->volumeThirdN->show();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

}

void sCalibration::showVolumeFree2(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibFree2.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibFree2.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibFree2.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibFree2.ThirdVOlume));

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->show();
    ui->leVolume2->show();
    ui->volumeSecondP->show();
    ui->volumeSecondN->show();

    ui->lblPara4->show();
    ui->leVolume3->show();
    ui->volumeThirdP->show();
    ui->volumeThirdN->show();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

}

void sCalibration::showVolumeFree3(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibFree3.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibFree3.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibFree3.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibFree3.ThirdVOlume));

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->show();
    ui->leVolume2->show();
    ui->volumeSecondP->show();
    ui->volumeSecondN->show();

    ui->lblPara4->show();
    ui->leVolume3->show();
    ui->volumeThirdP->show();
    ui->volumeThirdN->show();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

}

void sCalibration::showVolumeFree4(){

    ui->leVolume->clear();
    ui->leVolume1->clear();
    ui->leVolume2->clear();
    ui->leVolume3->clear();

    ui->leVolume->setText(QString::number(cCalibFree4.StageVolume));
    ui->leVolume1->setText(QString::number(cCalibFree4.FirstVolume));
    ui->leVolume2->setText(QString::number(cCalibFree4.SecondVolume));
    ui->leVolume3->setText(QString::number(cCalibFree4.ThirdVOlume));

    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->show();
    ui->leVolume2->show();
    ui->volumeSecondP->show();
    ui->volumeSecondN->show();

    ui->lblPara4->show();
    ui->leVolume3->show();
    ui->volumeThirdP->show();
    ui->volumeThirdN->show();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

}

void sCalibration::updateVolumeSinExpD5191(){
    if(cCalibSingleD5191.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibSingleD5191.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibSingleD5191.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibSingleD5191.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibSingleD5191.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibSingleD5191.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibSingleD5191.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibSingleD5191.ThirdVOlume = ui->leVolume3->text().toDouble();

//    if(cCalibD5191.single_expansion != ui->cbSingleExpEnable->checkState()) cParaMethodVolumeChanged = true;
//    cCalibD5191.single_expansion = ui->cbSingleExpEnable->checkState();
}

void sCalibration::updateVolumeD5191(){
    if(cCalibD5191.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD5191.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibD5191.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD5191.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibD5191.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD5191.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibD5191.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD5191.ThirdVOlume = ui->leVolume3->text().toDouble();

//    if(cCalibD5191.single_expansion != ui->cbSingleExpEnable->checkState()) cParaMethodVolumeChanged = true;
//    cCalibD5191.single_expansion = ui->cbSingleExpEnable->checkState();
}

void sCalibration::updateVolumeD6377(){
    if(cCalibD6377.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD6377.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibD6377.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD6377.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibD6377.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD6377.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibD6377.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD6377.ThirdVOlume = ui->leVolume3->text().toDouble();

}

void sCalibration::updateVolumeD6378(){
    if(cCalibD6378.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD6378.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibD6378.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD6378.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibD6378.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD6378.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibD6378.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD6378.ThirdVOlume = ui->leVolume3->text().toDouble();
}

void sCalibration::updateVolumeD5188(){
    if(cCalibD5188.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD5188.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibD5188.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD5188.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibD5188.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD5188.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibD5188.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibD5188.ThirdVOlume = ui->leVolume3->text().toDouble();
}

void sCalibration::updateVolumeFree1(){
    if(cCalibFree1.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree1.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibFree1.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree1.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibFree1.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree1.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibFree1.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree1.ThirdVOlume = ui->leVolume3->text().toDouble();
}

void sCalibration::updateVolumeFree2(){
    if(cCalibFree2.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree2.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibFree2.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree2.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibFree2.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree2.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibFree2.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree2.ThirdVOlume = ui->leVolume3->text().toDouble();
}

void sCalibration::updateVolumeFree3(){
    if(cCalibFree3.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree3.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibFree3.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree3.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibFree3.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree3.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibFree3.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree3.ThirdVOlume = ui->leVolume3->text().toDouble();
}

void sCalibration::updateVolumeFree4(){
    if(cCalibFree4.StageVolume != ui->leVolume->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree4.StageVolume = ui->leVolume->text().toDouble();

    if(cCalibFree4.FirstVolume != ui->leVolume1->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree4.FirstVolume = ui->leVolume1->text().toDouble();

    if(cCalibFree4.SecondVolume != ui->leVolume2->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree4.SecondVolume = ui->leVolume2->text().toDouble();

    if(cCalibFree4.ThirdVOlume != ui->leVolume3->text().toDouble()) cParaMethodVolumeChanged = true;
    cCalibFree4.ThirdVOlume = ui->leVolume3->text().toDouble();
}


void sCalibration::MethodSingleExpansion(){
    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->hide();
    ui->leVolume2->hide();
    ui->volumeSecondP->hide();
    ui->volumeSecondN->hide();

    ui->lblPara4->hide();
    ui->leVolume3->hide();
    ui->volumeThirdP->hide();
    ui->volumeThirdN->hide();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();
}

void sCalibration::MethodTripleExpansion(){
    ui->lblPara1->show();
    ui->leVolume->show();
    ui->volumeStageP->show();
    ui->volumeStageN->show();

    ui->lblPara2->show();
    ui->leVolume1->show();
    ui->volumeFirstP->show();
    ui->volumeFirstN->show();

    ui->lblPara3->show();
    ui->leVolume2->show();
    ui->volumeSecondP->show();
    ui->volumeSecondN->show();

    ui->lblPara4->show();
    ui->leVolume3->show();
    ui->volumeThirdP->show();
    ui->volumeThirdN->show();

    if(ui->cbMethod->currentIndex() == M_METHOD_D5191){
        ui->lblPara5->show();
        ui->cbSingleExpEnable->show();
    }else{
        ui->lblPara5->hide();
        ui->cbSingleExpEnable->hide();
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

    if(ui->twCalibration->currentWidget() == ui->tabMethodVolume)
    {
        if(cPrevMethod == ui->cbMethod->currentIndex())
        {
            switch (cPrevMethod) {

                case M_METHOD_D5191:
                    {
                        if(ui->cbSingleExpEnable->checkState() == 0)
                            updateVolumeD5191();
                        else
                            updateVolumeSinExpD5191();
                    }
                break;
                case M_METHOD_D6377: updateVolumeD6377(); break;
                case M_METHOD_D6378: updateVolumeD6378(); break;
                case M_METHOD_D5188: updateVolumeD5188(); break;

                case M_METHOD_FREE1: updateVolumeFree1(); break;
                case M_METHOD_FREE2: updateVolumeFree2(); break;
                case M_METHOD_FREE3: updateVolumeFree3(); break;
                case M_METHOD_FREE4: updateVolumeFree4(); break;
            }
        }
        if(cParaMethodVolumeChanged)
        {
            if(saveMethodVolumeFile()){
                emit showMsgBox(tr("Calibration Setup"), tr("Volume Adjustment Saved!"));
            }
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

void sCalibration::updateVolumeCalib(){
    if(cPrevMethod == ui->cbMethod->currentIndex())
    {
        switch (cPrevMethod) {

            case M_METHOD_D5191:
                    {
                        if(ui->cbSingleExpEnable->checkState() == 0)
                            updateVolumeD5191();
                        else
                            updateVolumeSinExpD5191();
                    }
            break;
            case M_METHOD_D6377: updateVolumeD6377(); break;
            case M_METHOD_D6378: updateVolumeD6378(); break;
            case M_METHOD_D5188: updateVolumeD5188(); break;

            case M_METHOD_FREE1: updateVolumeFree1(); break;
            case M_METHOD_FREE2: updateVolumeFree2(); break;
            case M_METHOD_FREE3: updateVolumeFree3(); break;
            case M_METHOD_FREE4: updateVolumeFree4(); break;
        }
    }

    if(cParaMethodVolumeChanged){
        cParasChanged = true;
    }
}

bool sCalibration::getcParaMethodVolumeChanged(){
    return cParaMethodVolumeChanged;
}

void sCalibration::sendTemcommand(){
    if(!cParaMethodVolumeChanged)
    {
        int tc = getTemperatureCount(20);
        emit sendCommand(cProtocol.sendMeasuring(0, tc), this);
    }
}

void sCalibration::checkExit(int tmp)
{
    updateTemperatureCalib();

    updatePressureCalib();

    updateVolumeCalib();

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
    else if(ui->twCalibration->currentWidget() == cWidgetMethodVolume){
        qDebug()<<"cWidgetMethodVolume";

        if(cParasChanged){
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

    if(index==3) ui->pbSave->hide();
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

        if(cPrevTab == 2){
            if(cPrevMethod == ui->cbMethod->currentIndex())
            {
                switch (cPrevMethod) {

                    case M_METHOD_D5191:
                            {
                                if(ui->cbSingleExpEnable->checkState() == 0)
                                    updateVolumeD5191();
                                else
                                    updateVolumeSinExpD5191();
                            }
                    break;
                    case M_METHOD_D6377: updateVolumeD6377(); break;
                    case M_METHOD_D6378: updateVolumeD6378(); break;
                    case M_METHOD_D5188: updateVolumeD5188(); break;

                    case M_METHOD_FREE1: updateVolumeFree1(); break;
                    case M_METHOD_FREE2: updateVolumeFree2(); break;
                    case M_METHOD_FREE3: updateVolumeFree3(); break;
                    case M_METHOD_FREE4: updateVolumeFree4(); break;
                }
            }

            if(cParaMethodVolumeChanged){
                emit getConfirmation(M_CONFIRM_CALIBRATION_SWITCH, M_MEASURING);
            }
        }
        cPrevTab = index;

    }

    if(!index) showTemperatureCalib();
    else if(index==1)showPressureCalib();
    else if(index == 2) showMethodVolume();

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

void sCalibration::on_cbMethod_currentIndexChanged(int index)
{
    if(!isVisible()) return;

    if(cPrevMethod != index)
    {
        switch (cPrevMethod) {

            case M_METHOD_D5191:
                {
                    if(ui->cbSingleExpEnable->checkState() == 0)
                        updateVolumeD5191();
                    else
                        updateVolumeSinExpD5191();
                }
            break;

            case M_METHOD_D6377: updateVolumeD6377();
            break;
            case M_METHOD_D6378: updateVolumeD6378();
            break;
            case M_METHOD_D5188: updateVolumeD5188();
            break;

            case M_METHOD_FREE1: updateVolumeFree1();
            break;
            case M_METHOD_FREE2: updateVolumeFree2();
            break;
            case M_METHOD_FREE3: updateVolumeFree3();
            break;
            case M_METHOD_FREE4: updateVolumeFree4();
            break;
        }
    }

    if(cParaMethodVolumeChanged)
        emit getConfirmation(M_CONFIRM_CALIBRATION_SWITCH, M_MEASURING);
//        emit getConfirmation(M_CONFIRM_METHOD_SWITCH, M_MEASURING);

    cPrevMethod = index;

    switch(index)
    {
        case M_METHOD_D5191:
            {
                if(ui->cbSingleExpEnable->checkState() == 0)
                    showVolumeD5191();
                else
                    showVolumeSinExpD5191();
            }
        break;

        case M_METHOD_D6377: showVolumeD6377(); break;
        case M_METHOD_D6378: showVolumeD6378(); break;
        case M_METHOD_D5188: showVolumeD5188(); break;

        case M_METHOD_FREE1: showVolumeFree1(); break;
        case M_METHOD_FREE2: showVolumeFree2(); break;
        case M_METHOD_FREE3: showVolumeFree3(); break;
        case M_METHOD_FREE4: showVolumeFree4(); break;
    }
}

void sCalibration::on_volumeStageP_clicked()
{
    int tmp = ui->cbMethod->currentIndex();
    double currentVal;
    switch(tmp){
        case M_METHOD_D5191:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal >= 0.7) && (currentVal < 1.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6377:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal >= 0.7) && (currentVal < 1.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6378:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal >= 0.7) && (currentVal < 1.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_D5188:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal >= 0) && (currentVal < 0.55))
                {
                    currentVal += 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;

        case M_METHOD_FREE1:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal >= 0.7) && (currentVal < 1.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE2:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal >= 0.7) && (currentVal < 1.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE3:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal >= 0.7) && (currentVal < 1.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE4:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal >= 0.7) && (currentVal < 1.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
    }
}

void sCalibration::on_volumeStageN_clicked()
{
    int tmp = ui->cbMethod->currentIndex();
    double currentVal;
    switch(tmp){
        case M_METHOD_D5191:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal > 0.7) && (currentVal <= 1.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6377:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal > 0.7) && (currentVal <= 1.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6378:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal > 0.7) && (currentVal <= 1.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_D5188:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal > 0) && (currentVal <= 0.55))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;

        case M_METHOD_FREE1:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal > 0.7) && (currentVal <= 1.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE2:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal > 0.7) && (currentVal <= 1.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE3:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal > 0.7) && (currentVal <= 1.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE4:
                currentVal = ui->leVolume->text().toDouble();
                if((currentVal > 0.7) && (currentVal <= 1.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume->setText(QString::number(currentVal));
            break;
    }
}

void sCalibration::on_volumeFirstP_clicked()
{
    int tmp = ui->cbMethod->currentIndex();
    double currentVal;
    switch(tmp){
        case M_METHOD_D5191:
                currentVal = ui->leVolume1->text().toDouble();
                if(ui->cbSingleExpEnable->checkState() == 0){
                    if((currentVal >= 1.40) && (currentVal < 2.00))
                    {
                        currentVal += 0.01;
                    }
                }
                else{
                    if((currentVal >= 4.70) && (currentVal < 5.30))
                    {
                        currentVal += 0.01;
                    }
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6377:
                currentVal = ui->leVolume1->text().toDouble();
                qDebug()<<"D6377vl_Range value: "<<D6377vl_Range;
                if((currentVal >= (D6377vl_Range - 0.30)) && (currentVal < (D6377vl_Range + 0.30)))
                {
                    currentVal += 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6378:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal >= 1.40) && (currentVal < 2.00))
                {
                    currentVal += 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_D5188:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal >= 4.95) && (currentVal < 5.55))
                {
                    currentVal += 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;

        case M_METHOD_FREE1:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal >= 1.40) && (currentVal < 2.00))
                {
                    currentVal += 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE2:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal >= 1.40) && (currentVal < 2.00))
                {
                    currentVal += 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE3:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal >= 1.40) && (currentVal < 2.00))
                {
                    currentVal += 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE4:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal >= 1.40) && (currentVal < 2.00))
                {
                    currentVal += 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
    }
}

void sCalibration::on_volumeFirstN_clicked()
{
    int tmp = ui->cbMethod->currentIndex();
    double currentVal;
    switch(tmp){
        case M_METHOD_D5191:
                currentVal = ui->leVolume1->text().toDouble();
                if(ui->cbSingleExpEnable->checkState() == 0){
                    if((currentVal > 1.40) && (currentVal <= 2.00))
                    {
                        currentVal -= 0.01;
                    }
                }
                else{
                    if((currentVal > 4.70) && (currentVal <= 5.30))
                    {
                        currentVal -= 0.01;
                    }
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6377:
                currentVal = ui->leVolume1->text().toDouble();
                qDebug()<<"D6377vl_Range value: "<<D6377vl_Range;
                if((currentVal > (D6377vl_Range - 0.30)) && (currentVal <= (D6377vl_Range + 0.30)))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6378:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal > 1.40) && (currentVal <= 2.00))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_D5188:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal > 4.95) && (currentVal <= 5.55))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;

        case M_METHOD_FREE1:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal > 1.40) && (currentVal <= 2.00))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE2:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal > 1.40) && (currentVal <= 2.00))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE3:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal > 1.40) && (currentVal <= 2.00))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE4:
                currentVal = ui->leVolume1->text().toDouble();
                if((currentVal > 1.40) && (currentVal <= 2.00))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume1->setText(QString::number(currentVal));
            break;
    }
}

void sCalibration::on_volumeSecondP_clicked()
{
    int tmp = ui->cbMethod->currentIndex();
    double currentVal;
    switch(tmp){
        case M_METHOD_D5191:
                currentVal = ui->leVolume2->text().toDouble();
                if(ui->cbSingleExpEnable->checkState() == 0){
                    if((currentVal >= 2.20) && (currentVal < 2.80))
                    {
                        currentVal += 0.01;
                    }
                }
                else{
                    if((currentVal >= 0) && (currentVal < 5.35))
                    {
                        currentVal += 0.01;
                    }
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6377:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal >= 0) && (currentVal < 5.35))
                {
                    currentVal += 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6378:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal >= 2.20) && (currentVal < 2.80))
                {
                    currentVal += 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_D5188:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal >= 0) && (currentVal < 5.35))
                {
                    currentVal += 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;

        case M_METHOD_FREE1:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal >= 2.20) && (currentVal < 2.80))
                {
                    currentVal += 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE2:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal >= 2.20) && (currentVal < 2.80))
                {
                    currentVal += 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE3:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal >= 2.20) && (currentVal < 2.80))
                {
                    currentVal += 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE4:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal >= 2.20) && (currentVal < 2.80))
                {
                    currentVal += 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
    }
}

void sCalibration::on_volumeSecondN_clicked()
{
    int tmp = ui->cbMethod->currentIndex();
    double currentVal;
    switch(tmp){
        case M_METHOD_D5191:
                currentVal = ui->leVolume2->text().toDouble();
                if(ui->cbSingleExpEnable->checkState() == 0){
                    if((currentVal > 2.20) && (currentVal <= 2.80))
                    {
                        currentVal -= 0.01;
                    }
                }
                else{
                    if((currentVal > 0) && (currentVal <= 5.35))
                    {
                        currentVal -= 0.01;
                    }
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6377:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal > 0) && (currentVal <= 5.35))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6378:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal > 2.20) && (currentVal <= 2.80))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_D5188:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal > 0) && (currentVal <= 5.35))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;

        case M_METHOD_FREE1:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal > 2.20) && (currentVal <= 2.80))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE2:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal > 2.20) && (currentVal <= 2.80))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE3:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal > 2.20) && (currentVal <= 2.80))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE4:
                currentVal = ui->leVolume2->text().toDouble();
                if((currentVal > 2.20) && (currentVal <= 2.80))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume2->setText(QString::number(currentVal));
            break;
    }
}

void sCalibration::on_volumeThirdP_clicked()
{
    int tmp = ui->cbMethod->currentIndex();
    double currentVal;
    switch(tmp){
        case M_METHOD_D5191:
                currentVal = ui->leVolume3->text().toDouble();
                if(ui->cbSingleExpEnable->checkState() == 0){
                    if((currentVal >= 4.70) && (currentVal < 5.30))
                    {
                        currentVal += 0.01;
                    }
                }
                else{
                    if((currentVal >= 0) && (currentVal < 5.35))
                    {
                        currentVal += 0.01;
                    }
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6377:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal >= 0) && (currentVal < 5.35))
                {
                    currentVal += 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6378:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal >= 4.7) && (currentVal < 5.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_D5188:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal >= 0) && (currentVal < 5.35))
                {
                    currentVal += 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;

        case M_METHOD_FREE1:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal >= 4.7) && (currentVal < 5.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE2:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal >= 4.7) && (currentVal < 5.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE3:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal >= 4.7) && (currentVal < 5.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE4:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal >= 4.7) && (currentVal < 5.30))
                {
                    currentVal += 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
    }
}

void sCalibration::on_volumeThirdN_clicked()
{
    int tmp = ui->cbMethod->currentIndex();
    double currentVal;
    switch(tmp){
        case M_METHOD_D5191:
                currentVal = ui->leVolume3->text().toDouble();
                if(ui->cbSingleExpEnable->checkState() == 0){
                    if((currentVal > 4.70) && (currentVal <= 5.35))
                    {
                        currentVal -= 0.01;
                    }
                }
                else{
                    if((currentVal > 0) && (currentVal <= 5.35))
                    {
                        currentVal -= 0.01;
                    }
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6377:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal > 0) && (currentVal <= 5.35))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_D6378:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal > 4.70) && (currentVal <= 5.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_D5188:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal > 0) && (currentVal <= 5.35))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;

        case M_METHOD_FREE1:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal > 4.70) && (currentVal <= 5.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE2:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal > 4.70) && (currentVal <= 5.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE3:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal > 4.70) && (currentVal <= 5.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
        case M_METHOD_FREE4:
                currentVal = ui->leVolume3->text().toDouble();
                if((currentVal > 4.70) && (currentVal <= 5.30))
                {
                    currentVal -= 0.01;
                }
                ui->leVolume3->setText(QString::number(currentVal));
            break;
    }
}

void sCalibration::on_cbSingleExpEnable_clicked()
{
    if(ui->cbSingleExpEnable->checkState() == 0)
    {
        updateVolumeSinExpD5191();

        if(cParaMethodVolumeChanged)
            emit getConfirmation(M_CONFIRM_CALIBRATION_SWITCH, M_MEASURING);

        showVolumeD5191();
    }else{
        updateVolumeD5191();

        if(cParaMethodVolumeChanged)
            emit getConfirmation(M_CONFIRM_CALIBRATION_SWITCH, M_MEASURING);

        showVolumeSinExpD5191();
    }
}

void sCalibration::on_D6377_Vl_ration(double vl, bool init){
    if(init){
        cCalibD6377.StageVolume = DEFAULT_STAGE_VOLUME;
        cCalibD6377.FirstVolume = (vl/100);
        D6377vl_Range = (vl/100);
        qDebug()<<"D6377vl_Range: "<<D6377vl_Range;
    }else{
        cCalibD6377.FirstVolume = (vl/100);
        D6377vl_Range = (vl/100);
        qDebug()<<"D6377vl_Range: "<<D6377vl_Range;
    }
    D6377Vl_updated = true;
    saveMethodVolumeFile();
}

void sCalibration::updateD6377Range(double D6377Range){
    D6377vl_Range = (D6377Range/100);
}
