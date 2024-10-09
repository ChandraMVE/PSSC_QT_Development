#include "smethodsetup.h"
#include "ui_smethodsetup.h"

sMethodSetup::sMethodSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMethodSetup)
{
    ui->setupUi(this);
    ui->gbConstants->hide();

    QListView *view1 = new QListView(ui->cbMethod);
    view1->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item::hover { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255);}\
                        QListView::item{height: 41px}");

    ui->cbMethod->setView(view1);


    QListView *view2 = new QListView(ui->cbFormula);
    view2->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item::hover { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255);}\
                        QListView::item{height: 41px}");

    ui->cbFormula->setView(view2);

    cWidgetFormula = ui->tabFormula;
    cStringFormula = ui->twMethodSetup->tabText(0);

    cWidgetStdParas = ui->tabParameters;
    cStringStdParas = ui->twMethodSetup->tabText(1);

    cWidgetFreeParas = ui->tabFreeParas;
    cStringFreeParas = ui->twMethodSetup->tabText(2);

    cWidgetPassFail = ui->tabPassFail;
    cStringPassFail = ui->twMethodSetup->tabText(3);

    ui->twMethodSetup->clear();

    connect(ui->leConst1, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leConst1, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leConst2, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leConst2, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leConst3, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leConst3, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leInjectPara6, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leInjectPara6, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->lePara1, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->lePara1, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->lePara2, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->lePara2, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->lePara3, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->lePara3, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->lePara4, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->lePara4, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leInjectTemp, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leInjectTemp, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leTestTemp, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leTestTemp, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leTPx1, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leTPx1, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leTPx2, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leTPx2, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leTPx3, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leTPx3, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leVLRatio, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leVLRatio, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->cbShakerValue, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->cbShakerValue, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->lePRPFrom, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->lePRPFrom, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->lePRPTo, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->lePRPTo, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    dvaConst = new QDoubleValidator(METHOD_CONSTANT_MIN, METHOD_CONSTANT_MAX, METHOD_CONSTANT_DP, ui->leConst1);
    dvaConst->setNotation(QDoubleValidator::StandardNotation);
    ui->leConst1->setValidator(dvaConst);

    dvbConst = new QDoubleValidator(METHOD_CONSTANT_MIN, METHOD_CONSTANT_MAX, METHOD_CONSTANT_DP, ui->leConst2);
    dvbConst->setNotation(QDoubleValidator::StandardNotation);
    ui->leConst2->setValidator(dvbConst);

    dvcConst = new QDoubleValidator(METHOD_CONSTANT_MIN, METHOD_CONSTANT_MAX, METHOD_CONSTANT_DP, ui->leConst3);
    dvcConst->setNotation(QDoubleValidator::StandardNotation);
    ui->leConst3->setValidator(dvcConst);

    dvInjectPara6 = new QDoubleValidator(-999.0, 999.0, 3, ui->leInjectPara6);
    dvInjectPara6->setNotation(QDoubleValidator::StandardNotation);
    ui->leInjectPara6->setValidator(dvInjectPara6);

    dvPara1 = new QDoubleValidator(-999.0, 999.0, 3, ui->lePara1);
    dvPara1->setNotation(QDoubleValidator::StandardNotation);
    ui->lePara1->setValidator(dvPara1);

    dvPara2 = new QDoubleValidator(-999.0, 999.0, 3, ui->lePara2);
    dvPara2->setNotation(QDoubleValidator::StandardNotation);
    ui->lePara2->setValidator(dvPara2);

    dvPara3 = new QDoubleValidator(-999.0, 999.0, 3, ui->lePara3);
    dvPara3->setNotation(QDoubleValidator::StandardNotation);
    ui->lePara3->setValidator(dvPara3);

    dvPara4 = new QDoubleValidator(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP, ui->lePara4);
    dvPara4->setNotation(QDoubleValidator::StandardNotation);
    ui->lePara4->setValidator(dvPara4);

    dvInjectTemperature = new QDoubleValidator(METHOD_TEMPERATURE_MIN, METHOD_TEMPERATURE_MAX, METHOD_TEMPERATURE_DP, ui->leInjectTemp);
    dvInjectTemperature->setNotation(QDoubleValidator::StandardNotation);
    ui->leInjectTemp->setValidator(dvInjectTemperature);

    dvTestTemperature = new QDoubleValidator(METHOD_TEMPERATURE_MIN, METHOD_TEMPERATURE_MAX, METHOD_TEMPERATURE_DP, ui->leTestTemp);
    dvTestTemperature->setNotation(QDoubleValidator::StandardNotation);
    ui->leTestTemp->setValidator(dvTestTemperature);

    dvTPx1 = new QDoubleValidator(METHOD_TPX_MIN, METHOD_TPX_MAX, METHOD_TPX_DP, ui->leTPx1);
    dvTPx1->setNotation(QDoubleValidator::StandardNotation);
    ui->leTPx1->setValidator(dvTPx1);

    dvTPx2 = new QDoubleValidator(METHOD_TPX_MIN, METHOD_TPX_MAX, METHOD_TPX_DP, ui->leTPx2);
    dvTPx2->setNotation(QDoubleValidator::StandardNotation);
    ui->leTPx2->setValidator(dvTPx2);

    dvTPx3 = new QDoubleValidator(METHOD_TPX_MIN, METHOD_TPX_MAX, METHOD_TPX_DP, ui->leTPx3);
    dvTPx3->setNotation(QDoubleValidator::StandardNotation);
    ui->leTPx3->setValidator(dvTPx3);

    dvVLRatio = new QDoubleValidator(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX, METHOD_VLRATIO_DP, ui->leVLRatio);
    dvVLRatio->setNotation(QDoubleValidator::StandardNotation);
    ui->leVLRatio->setValidator(dvVLRatio);

    dvShaker = new QDoubleValidator(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP, ui->cbShakerValue);
    dvShaker->setNotation(QDoubleValidator::StandardNotation);
    ui->cbShakerValue->setValidator(dvShaker);

    dvFrom = new QDoubleValidator(-999.0, 999.0, 2, ui->lePRPFrom);
    dvFrom->setNotation(QDoubleValidator::StandardNotation);
    ui->lePRPFrom->setValidator(dvFrom);

    dvTo = new QDoubleValidator(-999.0, 999.0, 2, ui->lePRPTo);
    dvTo->setNotation(QDoubleValidator::StandardNotation);
    ui->lePRPTo->setValidator(dvTo);

    setDefaults();
    cPrevMethod = 0;
    cParasChanged = false;
    cEnSwitch = true;
    exitClicked = false;
    MethodSetUpFilesSaved = false;

    ui->imageCapture->hide();

}

sMethodSetup::~sMethodSetup()
{
    delete ui;
}

void sMethodSetup::setMethods(const QStringList tmp)
{
    ui->cbMethod->clear();
    ui->cbMethod->insertItems(0, tmp);
}

void sMethodSetup::setD5191(const QStringList tmp)
{
    qslD5191 = tmp;
}

void sMethodSetup::setD6378(const QStringList tmp)
{
    qslD6378 = tmp;
}

void sMethodSetup::setEN_13016_1(const QStringList tmp)
{
    qslEN_13016_1 = tmp;
}

void sMethodSetup::setEN_13016_2(const QStringList tmp)
{
    qslEN_13016_2 = tmp;
}

void sMethodSetup::setGB_T_8017(const QStringList tmp)
{
    qslGB_T_8017 = tmp;
}

void sMethodSetup::setIP_394(const QStringList tmp)
{
    qslIP_394 = tmp;
}

void sMethodSetup::setIP_409(const QStringList tmp)
{
    qslIP_409 = tmp;
}

void sMethodSetup::setJIS_K2258_2(const QStringList tmp)
{
    qslJIS_K2258_2 = tmp;
}

void sMethodSetup::setSH_T_0769(const QStringList tmp)
{
    qslSH_T_0769 = tmp;
}

void sMethodSetup::setSH_T_0794(const QStringList tmp)
{
    qslSH_T_0794 = tmp;
}

void sMethodSetup::setSN_T_2932(const QStringList tmp)
{
    qslSN_T_2932 = tmp;
}


void sMethodSetup::setFree1(const QStringList tmp)
{
    qslFree1 = tmp;
}

void sMethodSetup::setFree2(const QStringList tmp)
{
    qslFree2 = tmp;
}

void sMethodSetup::setFree3(const QStringList tmp)
{
    qslFree3 = tmp;
}

void sMethodSetup::setFree4(const QStringList tmp)
{
    qslFree4 = tmp;
}

void sMethodSetup::Show()
{
    cPrevMethod = M_METHOD_NEW_D5191;
    ui->cbMethod->setCurrentIndex(M_METHOD_NEW_D5191);
    showD5191();
    this->show();
}

void sMethodSetup::setDefaults()
{
    stdD5191.formula = DEFAULT_D5191_FORMULA;
    stdD5191.temperature = DEFAULT_D5191_TEMPERATURE;
    stdD5191.time = DEFAULT_D5191_TIME;
    stdD5191.vl_ratio = DEFAULT_D5191_VL_RATIO;
    stdD5191.single_expansion = DEFAULT_D5191_SINGLE_EXPAN_ENABLED;
    stdD5191.passfail_enabled = DEFAULT_D5191_PASS_FAIL_ENABLED;
    stdD5191.from = DEFAULT_D5191_FROM;
    stdD5191.to = DEFAULT_D5191_TO;

    stdEN_13016_1.formula = DEFAULT_D5191_FORMULA;
    stdEN_13016_1.temperature = DEFAULT_D5191_TEMPERATURE;
    stdEN_13016_1.time = DEFAULT_D5191_TIME;
    stdEN_13016_1.vl_ratio = DEFAULT_D5191_VL_RATIO;
    stdEN_13016_1.single_expansion = DEFAULT_D5191_SINGLE_EXPAN_ENABLED;
    stdEN_13016_1.passfail_enabled = DEFAULT_D5191_PASS_FAIL_ENABLED;
    stdEN_13016_1.from = DEFAULT_D5191_FROM;
    stdEN_13016_1.to = DEFAULT_D5191_TO;

    stdGB_T_8017.formula = DEFAULT_D5191_FORMULA;
    stdGB_T_8017.temperature = DEFAULT_D5191_TEMPERATURE;
    stdGB_T_8017.time = DEFAULT_D5191_TIME;
    stdGB_T_8017.vl_ratio = DEFAULT_D5191_VL_RATIO;
    stdGB_T_8017.single_expansion = DEFAULT_D5191_SINGLE_EXPAN_ENABLED;
    stdGB_T_8017.passfail_enabled = DEFAULT_D5191_PASS_FAIL_ENABLED;
    stdGB_T_8017.from = DEFAULT_D5191_FROM;
    stdGB_T_8017.to = DEFAULT_D5191_TO;

    stdIP_394.formula = DEFAULT_D5191_FORMULA;
    stdIP_394.temperature = DEFAULT_D5191_TEMPERATURE;
    stdIP_394.time = DEFAULT_D5191_TIME;
    stdIP_394.vl_ratio = DEFAULT_D5191_VL_RATIO;
    stdIP_394.single_expansion = DEFAULT_D5191_SINGLE_EXPAN_ENABLED;
    stdIP_394.passfail_enabled = DEFAULT_D5191_PASS_FAIL_ENABLED;
    stdIP_394.from = DEFAULT_D5191_FROM;
    stdIP_394.to = DEFAULT_D5191_TO;

    stdSH_T_0794.formula = DEFAULT_D5191_FORMULA;
    stdSH_T_0794.temperature = DEFAULT_D5191_TEMPERATURE;
    stdSH_T_0794.time = DEFAULT_D5191_TIME;
    stdSH_T_0794.vl_ratio = DEFAULT_D5191_VL_RATIO;
    stdSH_T_0794.single_expansion = DEFAULT_D5191_SINGLE_EXPAN_ENABLED;
    stdSH_T_0794.passfail_enabled = DEFAULT_D5191_PASS_FAIL_ENABLED;
    stdSH_T_0794.from = DEFAULT_D5191_FROM;
    stdSH_T_0794.to = DEFAULT_D5191_TO;

    stdD6377.InjectTemp = DEFAULT_D6377_INJECT_TMP;
    stdD6377.temperature = DEFAULT_D6377_TEMPERATURE;
    stdD6377.time = DEFAULT_D6377_TIME;
    stdD6377.vl_ratio = DEFAULT_D6377_VL_RATIO;
    stdD6377.shaker_speed = DEFAULT_D5188_SHAKER_SPEED * (60);
    stdD6377.passfail_enabled = DEFAULT_D6377_PASS_FAIL_ENABLED;
    stdD6377.from = DEFAULT_D6377_FROM;
    stdD6377.to = DEFAULT_D6377_TO;

    stdIP_481.InjectTemp = DEFAULT_D6377_INJECT_TMP;
    stdIP_481.temperature = DEFAULT_D6377_TEMPERATURE;
    stdIP_481.time = DEFAULT_D6377_TIME;
    stdIP_481.vl_ratio = DEFAULT_D6377_VL_RATIO;
    stdIP_481.shaker_speed = DEFAULT_D5188_SHAKER_SPEED * (60);
    stdIP_481.passfail_enabled = DEFAULT_D6377_PASS_FAIL_ENABLED;
    stdIP_481.from = DEFAULT_D6377_FROM;
    stdIP_481.to = DEFAULT_D6377_TO;

    stdD6378.formula = DEFAULT_D6378_FORMULA;
    stdD6378.temperature = DEFAULT_D6378_TEMPERATURE;
    stdD6378.time = DEFAULT_D6378_TIME;
    stdD6378.vl_ratio = DEFAULT_D6378_VL_RATIO;
    stdD6378.passfail_enabled = DEFAULT_D6378_PASS_FAIL_ENABLED;
    stdD6378.from = DEFAULT_D6378_FROM;
    stdD6378.to = DEFAULT_D6378_TO;

    stdEN_13016_2.formula = DEFAULT_D6378_FORMULA;
    stdEN_13016_2.temperature = DEFAULT_D6378_TEMPERATURE;
    stdEN_13016_2.time = DEFAULT_D6378_TIME;
    stdEN_13016_2.vl_ratio = DEFAULT_D6378_VL_RATIO;
    stdEN_13016_2.passfail_enabled = DEFAULT_D6378_PASS_FAIL_ENABLED;
    stdEN_13016_2.from = DEFAULT_D6378_FROM;
    stdEN_13016_2.to = DEFAULT_D6378_TO;

    stdIP409.formula = DEFAULT_D6378_FORMULA;
    stdIP409.temperature = DEFAULT_D6378_TEMPERATURE;
    stdIP409.time = DEFAULT_D6378_TIME;
    stdIP409.vl_ratio = DEFAULT_D6378_VL_RATIO;
    stdIP409.passfail_enabled = DEFAULT_D6378_PASS_FAIL_ENABLED;
    stdIP409.from = DEFAULT_D6378_FROM;
    stdIP409.to = DEFAULT_D6378_TO;

    stdJIS_K2258_2.formula = DEFAULT_D6378_FORMULA;
    stdJIS_K2258_2.temperature = DEFAULT_D6378_TEMPERATURE;
    stdJIS_K2258_2.time = DEFAULT_D6378_TIME;
    stdJIS_K2258_2.vl_ratio = DEFAULT_D6378_VL_RATIO;
    stdJIS_K2258_2.passfail_enabled = DEFAULT_D6378_PASS_FAIL_ENABLED;
    stdJIS_K2258_2.from = DEFAULT_D6378_FROM;
    stdJIS_K2258_2.to = DEFAULT_D6378_TO;

    stdSH_T_0769.formula = DEFAULT_D6378_FORMULA;
    stdSH_T_0769.temperature = DEFAULT_D6378_TEMPERATURE;
    stdSH_T_0769.time = DEFAULT_D6378_TIME;
    stdSH_T_0769.vl_ratio = DEFAULT_D6378_VL_RATIO;
    stdSH_T_0769.passfail_enabled = DEFAULT_D6378_PASS_FAIL_ENABLED;
    stdSH_T_0769.from = DEFAULT_D6378_FROM;
    stdSH_T_0769.to = DEFAULT_D6378_TO;

    stdSN_T_2932.formula = DEFAULT_D6378_FORMULA;
    stdSN_T_2932.temperature = DEFAULT_D6378_TEMPERATURE;
    stdSN_T_2932.time = DEFAULT_D6378_TIME;
    stdSN_T_2932.vl_ratio = DEFAULT_D6378_VL_RATIO;
    stdSN_T_2932.passfail_enabled = DEFAULT_D6378_PASS_FAIL_ENABLED;
    stdSN_T_2932.from = DEFAULT_D6378_FROM;
    stdSN_T_2932.to = DEFAULT_D6378_TO;

    stdD5188.pressure = DEFAULT_D5188_PRESSURE;
    stdD5188.vl_ratio = DEFAULT_D5188_VL_RATIO;
    stdD5188.shaker_speed = DEFAULT_D5188_SHAKER_SPEED * (60);
    stdD5188.passfail_enabled = DEFAULT_D5188_PASS_FAIL_ENABLED;
//    stdD5188.alarm_enabled = DEFAULT_D5188_ALARM_ENABLED;
    stdD5188.from = DEFAULT_D5188_FROM;
    stdD5188.to = DEFAULT_D5188_TO;

    stdFree1.aconstant = DEFAULT_FREE_A_CONSTANT;
    stdFree1.bconstant = DEFAULT_FREE_B_CONSTANT;
    stdFree1.cconstant = DEFAULT_FREE_C_CONSTANT;
    stdFree1.InjectTemp = DEFAULT_FREE_INJECT_TMP;
    stdFree1.temperature = DEFAULT_FREE_TEMPERATURE;
    stdFree1.tpx1 = DEFAULT_FREE_TPX1;
    stdFree1.tpx2 = DEFAULT_FREE_TPX2;
    stdFree1.tpx3 = DEFAULT_FREE_TPX3;
    stdFree1.vl_ratio = DEFAULT_FREE_VLRATIO;
    stdFree1.shaker_speed = DEFAULT_FREE_SHAKER_SPEED * (60);
    stdFree1.shaker_disabled = DEFAULT_FREE_SHAKER_DISABLE;
    stdFree1.passfail_enabled = DEFAULT_FREE_PASS_FAIL_ENABLED;
//    stdFree1.alarm_enabled = DEFAULT_FREE_ALARM_ENABLED;
    stdFree1.from = DEFAULT_FREE_FROM;
    stdFree1.to = DEFAULT_FREE_TO;

    stdFree2.aconstant = DEFAULT_FREE_A_CONSTANT;
    stdFree2.bconstant = DEFAULT_FREE_B_CONSTANT;
    stdFree2.cconstant = DEFAULT_FREE_C_CONSTANT;
    stdFree2.InjectTemp = DEFAULT_FREE_INJECT_TMP;
    stdFree2.temperature = DEFAULT_FREE_TEMPERATURE;
    stdFree2.tpx1 = DEFAULT_FREE_TPX1;
    stdFree2.tpx2 = DEFAULT_FREE_TPX2;
    stdFree2.tpx3 = DEFAULT_FREE_TPX3;
    stdFree2.vl_ratio = DEFAULT_FREE_VLRATIO;
    stdFree2.shaker_speed = DEFAULT_FREE_SHAKER_SPEED * (60);
    stdFree2.shaker_disabled = DEFAULT_FREE_SHAKER_DISABLE;
    stdFree2.passfail_enabled = DEFAULT_FREE_PASS_FAIL_ENABLED;
//    stdFree2.alarm_enabled = DEFAULT_FREE_ALARM_ENABLED;
    stdFree2.from = DEFAULT_FREE_FROM;
    stdFree2.to = DEFAULT_FREE_TO;

    stdFree3.aconstant = DEFAULT_FREE_A_CONSTANT;
    stdFree3.bconstant = DEFAULT_FREE_B_CONSTANT;
    stdFree3.cconstant = DEFAULT_FREE_C_CONSTANT;
    stdFree3.InjectTemp = DEFAULT_FREE_INJECT_TMP;
    stdFree3.temperature = DEFAULT_FREE_TEMPERATURE;
    stdFree3.tpx1 = DEFAULT_FREE_TPX1;
    stdFree3.tpx2 = DEFAULT_FREE_TPX2;
    stdFree3.tpx3 = DEFAULT_FREE_TPX3;
    stdFree3.vl_ratio = DEFAULT_FREE_VLRATIO;
    stdFree3.shaker_speed = DEFAULT_FREE_SHAKER_SPEED * (60);
    stdFree3.shaker_disabled = DEFAULT_FREE_SHAKER_DISABLE;
    stdFree3.passfail_enabled = DEFAULT_FREE_PASS_FAIL_ENABLED;
//    stdFree3.alarm_enabled = DEFAULT_FREE_ALARM_ENABLED;
    stdFree3.from = DEFAULT_FREE_FROM;
    stdFree3.to = DEFAULT_FREE_TO;

    stdFree4.aconstant = DEFAULT_FREE_A_CONSTANT;
    stdFree4.bconstant = DEFAULT_FREE_B_CONSTANT;
    stdFree4.cconstant = DEFAULT_FREE_C_CONSTANT;
    stdFree4.InjectTemp = DEFAULT_FREE_INJECT_TMP;
    stdFree4.temperature = DEFAULT_FREE_TEMPERATURE;
    stdFree4.tpx1 = DEFAULT_FREE_TPX1;
    stdFree4.tpx2 = DEFAULT_FREE_TPX2;
    stdFree4.tpx3 = DEFAULT_FREE_TPX3;
    stdFree4.vl_ratio = DEFAULT_FREE_VLRATIO;
    stdFree4.shaker_speed = DEFAULT_FREE_SHAKER_SPEED * (60);
    stdFree4.shaker_disabled = DEFAULT_FREE_SHAKER_DISABLE;
    stdFree4.passfail_enabled = DEFAULT_FREE_PASS_FAIL_ENABLED;
//    stdFree4.alarm_enabled = DEFAULT_FREE_ALARM_ENABLED;
    stdFree4.from = DEFAULT_FREE_FROM;
    stdFree4.to = DEFAULT_FREE_TO;

    cParasChanged = true;
}

bool sMethodSetup::readFile()
{
    QString fname = QApplication::applicationDirPath() + FN_METHOD_SETUP;

    QFile in(fname);
    cEnSwitch = true;

    if(in.open(QIODevice::ReadOnly))
    {

        in.read((char *)&stdD5191, sizeof(stdD5191));
        in.read((char *)&stdD6377, sizeof(stdD6377));
        in.read((char *)&stdD6378, sizeof(stdD6378));
        in.read((char *)&stdD5188, sizeof(stdD5188));

        in.read((char *)&stdFree1, sizeof(stdFree1));
        in.read((char *)&stdFree2, sizeof(stdFree2));
        in.read((char *)&stdFree3, sizeof(stdFree3));
        in.read((char *)&stdFree4, sizeof(stdFree3));

        in.read((char *)&stdEN_13016_1, sizeof(stdEN_13016_1));
        in.read((char *)&stdEN_13016_2, sizeof(stdEN_13016_2));
        in.read((char *)&stdGB_T_8017, sizeof(stdGB_T_8017));
        in.read((char *)&stdIP_394, sizeof(stdIP_394));
        in.read((char *)&stdIP409, sizeof(stdIP409));
        in.read((char *)&stdIP_481, sizeof(stdIP_481));
        in.read((char *)&stdJIS_K2258_2, sizeof(stdJIS_K2258_2));
        in.read((char *)&stdSH_T_0769, sizeof(stdSH_T_0769));
        in.read((char *)&stdSH_T_0794, sizeof(stdSH_T_0794));
        in.read((char *)&stdSN_T_2932, sizeof(stdSN_T_2932));

        in.close();

        cParasChanged = false;

        return true;

    }
    else
    {
        setDefaults();
        return false;
    }
}

void sMethodSetup::saveFile()
{
    QString fname = QApplication::applicationDirPath() + FN_METHOD_SETUP;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {

        out.write((char *)&stdD5191, sizeof(stdD5191));
        out.write((char *)&stdD6377, sizeof(stdD6377));
        out.write((char *)&stdD6378, sizeof(stdD6378));
        out.write((char *)&stdD5188, sizeof(stdD5188));

        out.write((char *)&stdFree1, sizeof(stdFree1));
        out.write((char *)&stdFree2, sizeof(stdFree2));
        out.write((char *)&stdFree3, sizeof(stdFree3));
        out.write((char *)&stdFree4, sizeof(stdFree4));

        out.write((char *)&stdEN_13016_1, sizeof(stdEN_13016_1));
        out.write((char *)&stdEN_13016_2, sizeof(stdEN_13016_2));
        out.write((char *)&stdGB_T_8017, sizeof(stdGB_T_8017));
        out.write((char *)&stdIP_394, sizeof(stdIP_394));
        out.write((char *)&stdIP409, sizeof(stdIP409));
        out.write((char *)&stdIP_481, sizeof(stdIP_481));
        out.write((char *)&stdJIS_K2258_2, sizeof(stdJIS_K2258_2));
        out.write((char *)&stdSH_T_0769, sizeof(stdSH_T_0769));
        out.write((char *)&stdSH_T_0794, sizeof(stdSH_T_0794));
        out.write((char *)&stdSN_T_2932, sizeof(stdSN_T_2932));

        out.close();
        cParasChanged = false;
        cEnSwitch = true;
        MethodSetUpFilesSaved = true;
        emit showMsgBox(tr("Method Setup"), tr("Method Changes Saved!"));
    }
    else
    {
        cEnSwitch = false;
        MethodSetUpFilesSaved = false;
        emit showMsgBox(tr("Method Setup"), tr("Error Saving File!"));
    }

}

void sMethodSetup::showD5191()
{
    ui->cbFormula->clear();

    {

        qslD5191.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaD5191aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaD5191bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaD5191cConstant->at(0).toDouble());

        qslD5191.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaD5191aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaD5191bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaD5191cConstant->at(1).toDouble());

        qslD5191.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaD5191aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaD5191bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaD5191cConstant->at(2).toDouble());

        qslD5191.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslD5191);
    ui->cbFormula->setCurrentIndex(stdD5191.formula);

    ui->gbConstants->hide();
    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdD5191.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);
    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdD5191.time));
    ui->lePara2->move(310,90);

    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdD5191.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);
    ui->lePara3->show();
    ui->lblPara3->show();

    ui->cbSingleExpEnable->setChecked(stdD5191.single_expansion);
    ui->cbSingleExpEnable->move(445, 230);
    ui->lblPara5->move(20,230);

    ui->cbSingleExpEnable->show();
    ui->lblPara5->show();

    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();
    ui->frPara1->resize(660,350);
    ui->lblPara4->hide();
    ui->lePara4->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdD5191.from));

    dvTo->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdD5191.to));

    ui->cbEnable->setChecked(stdD5191.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdD5191.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showD6377()
{
    ui->gbConstants->hide();
    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Measuring Temp."));
    ui->lblPara1->move(20,90);

    dvInjectPara6->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                            cSettings.getTemperatureMS(stdD6377.temperature).toDouble(),
                            METHOD_TEMPERATURE_DP);
    ui->leInjectPara6->setText(cSettings.getTemperatureMS(stdD6377.InjectTemp));
    ui->lblPara1_2->move(20,20);
    ui->leInjectPara6->move(310,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdD6377.temperature));
    ui->lePara1->move(310,90);

    ui->lePara1->setReadOnly(false); 
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,160);
    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdD6377.time));
    ui->lePara2->move(310,160);

    ui->lePara2->setReadOnly(false);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,230);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdD6377.vl_ratio));
    ui->lePara3->move(310,230);
    ui->lePara3->setReadOnly(false);

    ui->lePara3->show();
    ui->lblPara3->show();
    ui->frPara1->resize(660,420);
    
    qDebug()<<"stdD6377.shaker_speed: "<<stdD6377.shaker_speed;
    double D6377ShakerSpeed = (double)(stdD6377.shaker_speed/(60.0));
    qDebug()<<"D6377ShakerSpeed: "<<D6377ShakerSpeed;
    dvPara4->setRange(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP);
    ui->lePara4->setText(cSettings.getShakerSpeed(D6377ShakerSpeed));

    ui->lblPara4->show();
    ui->lePara4->show();

    ui->lblPara1_2->show();
    ui->leInjectPara6->show();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D6377_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6377_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdD6377.from));

    dvTo->setRange(cSettings.getPressureMS(D6377_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6377_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdD6377.to));

    ui->cbEnable->setChecked(stdD6377.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdD6377.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showD6378()
{
    ui->gbConstants->hide();
    ui->cbFormula->clear();

    {

        qslD6378.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaD6378aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaD6378bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaD6378cConstant->at(0).toDouble());

        qslD6378.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaD6378aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaD6378bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaD6378cConstant->at(1).toDouble());

        qslD6378.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaD6378aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaD6378bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaD6378cConstant->at(2).toDouble());

        qslD6378.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslD6378);
    ui->cbFormula->setCurrentIndex(stdD6378.formula);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdD6378.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);

    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdD6378.time));
    ui->lePara2->move(310,90);
    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdD6378.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);

    ui->lblPara3->show();
    ui->lePara3->show();

    ui->frPara1->resize(660,250);
    ui->lblPara4->hide();
    ui->lePara4->hide();
    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();
    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdD6378.from));

    dvTo->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdD6378.to));

    ui->cbEnable->setChecked(stdD6378.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdD6378.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showEN_13016_1(){
    ui->cbFormula->clear();

    {

        qslEN_13016_1.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaEN_13016_1aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaEN_13016_1bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaEN_13016_1cConstant->at(0).toDouble());

        qslEN_13016_1.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaEN_13016_1aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaEN_13016_1bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaEN_13016_1cConstant->at(1).toDouble());

        qslEN_13016_1.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaEN_13016_1aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaEN_13016_1bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaEN_13016_1cConstant->at(2).toDouble());

        qslEN_13016_1.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslEN_13016_1);
    ui->cbFormula->setCurrentIndex(stdEN_13016_1.formula);

    ui->gbConstants->hide();
    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdEN_13016_1.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);
    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdEN_13016_1.time));
    ui->lePara2->move(310,90);

    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdEN_13016_1.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);
    ui->lePara3->show();
    ui->lblPara3->show();

    ui->cbSingleExpEnable->setChecked(stdEN_13016_1.single_expansion);
    ui->cbSingleExpEnable->move(445, 230);
    ui->lblPara5->move(20,230);

    ui->cbSingleExpEnable->show();
    ui->lblPara5->show();

    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();
    ui->frPara1->resize(660,350);
    ui->lblPara4->hide();
    ui->lePara4->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdEN_13016_1.from));

    dvTo->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdEN_13016_1.to));

    ui->cbEnable->setChecked(stdEN_13016_1.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdEN_13016_1.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());
}

void sMethodSetup::showEN_13016_2(){
    ui->gbConstants->hide();
    ui->cbFormula->clear();

    {

        qslEN_13016_2.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaEN_13016_2aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaEN_13016_2bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaEN_13016_2cConstant->at(0).toDouble());

        qslEN_13016_2.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaEN_13016_2aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaEN_13016_2bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaEN_13016_2cConstant->at(1).toDouble());

        qslEN_13016_2.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaEN_13016_2aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaEN_13016_2bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaEN_13016_2cConstant->at(2).toDouble());

        qslEN_13016_2.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslEN_13016_2);
    ui->cbFormula->setCurrentIndex(stdEN_13016_2.formula);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdEN_13016_2.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);

    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdEN_13016_2.time));
    ui->lePara2->move(310,90);
    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdEN_13016_2.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);

    ui->lblPara3->show();
    ui->lePara3->show();

    ui->frPara1->resize(660,250);
    ui->lblPara4->hide();
    ui->lePara4->hide();
    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();
    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdEN_13016_2.from));

    dvTo->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdEN_13016_2.to));

    ui->cbEnable->setChecked(stdEN_13016_2.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdEN_13016_2.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showGB_T_8017(){
    ui->cbFormula->clear();

    {

        qslGB_T_8017.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaGB_T_8017aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaGB_T_8017bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaGB_T_8017cConstant->at(0).toDouble());

        qslGB_T_8017.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaGB_T_8017aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaGB_T_8017bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaGB_T_8017cConstant->at(1).toDouble());

        qslGB_T_8017.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaGB_T_8017aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaGB_T_8017bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaGB_T_8017cConstant->at(2).toDouble());

        qslGB_T_8017.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslGB_T_8017);
    ui->cbFormula->setCurrentIndex(stdGB_T_8017.formula);

    ui->gbConstants->hide();
    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdGB_T_8017.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);
    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdGB_T_8017.time));
    ui->lePara2->move(310,90);

    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdGB_T_8017.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);
    ui->lePara3->show();
    ui->lblPara3->show();

    ui->cbSingleExpEnable->setChecked(stdGB_T_8017.single_expansion);
    ui->cbSingleExpEnable->move(445, 230);
    ui->lblPara5->move(20,230);

    ui->cbSingleExpEnable->show();
    ui->lblPara5->show();

    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();
    ui->frPara1->resize(660,350);
    ui->lblPara4->hide();
    ui->lePara4->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdGB_T_8017.from));

    dvTo->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdGB_T_8017.to));

    ui->cbEnable->setChecked(stdGB_T_8017.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdGB_T_8017.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());
}

void sMethodSetup::showIP_394(){
    ui->cbFormula->clear();

    {

        qslIP_394.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaIP_394aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaIP_394bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaIP_394cConstant->at(0).toDouble());

        qslIP_394.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaIP_394aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaIP_394bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaIP_394cConstant->at(1).toDouble());

        qslIP_394.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaIP_394aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaIP_394bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaIP_394cConstant->at(2).toDouble());

        qslIP_394.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslIP_394);
    ui->cbFormula->setCurrentIndex(stdIP_394.formula);

    ui->gbConstants->hide();
    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdIP_394.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);
    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdIP_394.time));
    ui->lePara2->move(310,90);

    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdIP_394.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);
    ui->lePara3->show();
    ui->lblPara3->show();

    ui->cbSingleExpEnable->setChecked(stdIP_394.single_expansion);
    ui->cbSingleExpEnable->move(445, 230);
    ui->lblPara5->move(20,230);

    ui->cbSingleExpEnable->show();
    ui->lblPara5->show();

    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();
    ui->frPara1->resize(660,350);
    ui->lblPara4->hide();
    ui->lePara4->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdIP_394.from));

    dvTo->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdIP_394.to));

    ui->cbEnable->setChecked(stdIP_394.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdIP_394.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());
}

void sMethodSetup::showIP_409(){
    ui->gbConstants->hide();
    ui->cbFormula->clear();

    {

        qslIP_409.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaIP_409aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaIP_409bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaIP_409cConstant->at(0).toDouble());

        qslIP_409.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaIP_409aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaIP_409bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaIP_409cConstant->at(1).toDouble());

        qslIP_409.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaIP_409aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaIP_409bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaIP_409cConstant->at(2).toDouble());

        qslIP_409.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslIP_409);
    ui->cbFormula->setCurrentIndex(stdIP409.formula);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdIP409.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);

    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdIP409.time));
    ui->lePara2->move(310,90);
    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdIP409.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);

    ui->lblPara3->show();
    ui->lePara3->show();

    ui->frPara1->resize(660,250);
    ui->lblPara4->hide();
    ui->lePara4->hide();
    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();
    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdIP409.from));

    dvTo->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdIP409.to));

    ui->cbEnable->setChecked(stdIP409.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdIP409.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showIP_481(){
    ui->gbConstants->hide();
    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Measuring Temp."));
    ui->lblPara1->move(20,90);

    dvInjectPara6->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                            cSettings.getTemperatureMS(stdIP_481.temperature).toDouble(),
                            METHOD_TEMPERATURE_DP);
    ui->leInjectPara6->setText(cSettings.getTemperatureMS(stdIP_481.InjectTemp));
    ui->lblPara1_2->move(20,20);
    ui->leInjectPara6->move(310,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdIP_481.temperature));
    ui->lePara1->move(310,90);

    ui->lePara1->setReadOnly(false);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,160);
    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdIP_481.time));
    ui->lePara2->move(310,160);

    ui->lePara2->setReadOnly(false);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,230);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdIP_481.vl_ratio));
    ui->lePara3->move(310,230);
    ui->lePara3->setReadOnly(false);

    ui->lePara3->show();
    ui->lblPara3->show();
    ui->frPara1->resize(660,420);

    qDebug()<<"stdIP_481.shaker_speed: "<<stdIP_481.shaker_speed;
    double D6377ShakerSpeed = (double)(stdIP_481.shaker_speed/(60.0));
    qDebug()<<"stdIP_481 ShakerSpeed: "<<D6377ShakerSpeed;
    dvPara4->setRange(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP);
    ui->lePara4->setText(cSettings.getShakerSpeed(D6377ShakerSpeed));

    ui->lblPara4->show();
    ui->lePara4->show();

    ui->lblPara1_2->show();
    ui->leInjectPara6->show();

    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D6377_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6377_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdIP_481.from));

    dvTo->setRange(cSettings.getPressureMS(D6377_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6377_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdIP_481.to));

    ui->cbEnable->setChecked(stdIP_481.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdIP_481.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showJIS_K2258_2(){
    ui->gbConstants->hide();
    ui->cbFormula->clear();

    {

        qslJIS_K2258_2.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaJIS_K2258_2aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaJIS_K2258_2bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaJIS_K2258_2cConstant->at(0).toDouble());

        qslJIS_K2258_2.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaJIS_K2258_2aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaJIS_K2258_2bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaJIS_K2258_2cConstant->at(1).toDouble());

        qslJIS_K2258_2.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaJIS_K2258_2aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaJIS_K2258_2bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaJIS_K2258_2cConstant->at(2).toDouble());

        qslJIS_K2258_2.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslJIS_K2258_2);
    ui->cbFormula->setCurrentIndex(stdJIS_K2258_2.formula);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdJIS_K2258_2.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);

    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdJIS_K2258_2.time));
    ui->lePara2->move(310,90);
    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdJIS_K2258_2.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);

    ui->lblPara3->show();
    ui->lePara3->show();

    ui->frPara1->resize(660,250);
    ui->lblPara4->hide();
    ui->lePara4->hide();
    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();
    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdJIS_K2258_2.from));

    dvTo->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdJIS_K2258_2.to));

    ui->cbEnable->setChecked(stdJIS_K2258_2.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdJIS_K2258_2.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showSH_T_0769(){
    ui->gbConstants->hide();
    ui->cbFormula->clear();

    {

        qslSH_T_0769.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaSH_T_0769aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaSH_T_0769bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaSH_T_0769cConstant->at(0).toDouble());

        qslSH_T_0769.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaSH_T_0769aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaSH_T_0769bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaSH_T_0769cConstant->at(1).toDouble());

        qslSH_T_0769.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaSH_T_0769aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaSH_T_0769bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaSH_T_0769cConstant->at(2).toDouble());

        qslSH_T_0769.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslSH_T_0769);
    ui->cbFormula->setCurrentIndex(stdSH_T_0769.formula);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdSH_T_0769.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);

    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdSH_T_0769.time));
    ui->lePara2->move(310,90);
    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdSH_T_0769.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);

    ui->lblPara3->show();
    ui->lePara3->show();

    ui->frPara1->resize(660,250);
    ui->lblPara4->hide();
    ui->lePara4->hide();
    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();
    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdSH_T_0769.from));

    dvTo->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdSH_T_0769.to));

    ui->cbEnable->setChecked(stdSH_T_0769.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdSH_T_0769.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showSH_T_0794(){
    ui->cbFormula->clear();

    {

        qslSH_T_0794.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaSH_T_0794aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaSH_T_0794bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaSH_T_0794cConstant->at(0).toDouble());

        qslSH_T_0794.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaSH_T_0794aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaSH_T_0794bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaSH_T_0794cConstant->at(1).toDouble());

        qslSH_T_0794.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaSH_T_0794aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaSH_T_0794bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaSH_T_0794cConstant->at(2).toDouble());

        qslSH_T_0794.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslSH_T_0794);
    ui->cbFormula->setCurrentIndex(stdSH_T_0794.formula);

    ui->gbConstants->hide();
    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdSH_T_0794.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);
    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdSH_T_0794.time));
    ui->lePara2->move(310,90);

    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdSH_T_0794.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);
    ui->lePara3->show();
    ui->lblPara3->show();

    ui->cbSingleExpEnable->setChecked(stdSH_T_0794.single_expansion);
    ui->cbSingleExpEnable->move(445, 230);
    ui->lblPara5->move(20,230);

    ui->cbSingleExpEnable->show();
    ui->lblPara5->show();

    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();
    ui->frPara1->resize(660,350);
    ui->lblPara4->hide();
    ui->lePara4->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdSH_T_0794.from));

    dvTo->setRange(cSettings.getPressureMS(D5191_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D5191_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdSH_T_0794.to));

    ui->cbEnable->setChecked(stdSH_T_0794.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdSH_T_0794.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());
}

void sMethodSetup::showSN_T_2932(){
    ui->gbConstants->hide();
    ui->cbFormula->clear();

    {

        qslSN_T_2932.clear();

        QString str = "ASTM = " +
           cSettings.getFormulaConstantsAB(qslFormulaSN_T_2932aConstant->at(0).toDouble()) +
           " x Ptot - " +
           cSettings.getFormulaConstantsAB(qslFormulaSN_T_2932bConstant->at(0).toDouble()) +
           " x Pgas - " +
           cSettings.getPressureNMS(qslFormulaSN_T_2932cConstant->at(0).toDouble());

        qslSN_T_2932.insert(0, str);

        str = "EPA = " +
                   cSettings.getFormulaConstantsAB(qslFormulaSN_T_2932aConstant->at(1).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaSN_T_2932bConstant->at(1).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaSN_T_2932cConstant->at(1).toDouble());

        qslSN_T_2932.insert(1, str);

        str = "CARB = " +
                   cSettings.getFormulaConstantsAB(qslFormulaSN_T_2932aConstant->at(2).toDouble()) +
                   " x Ptot - " +
                   cSettings.getFormulaConstantsAB(qslFormulaSN_T_2932bConstant->at(2).toDouble()) +
                   " x Pgas - " +
                   cSettings.getPressureNMS(qslFormulaSN_T_2932cConstant->at(2).toDouble());

        qslSN_T_2932.insert(2, str);

    }

    ui->cbFormula->insertItems(0, qslSN_T_2932);
    ui->cbFormula->setCurrentIndex(stdSN_T_2932.formula);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Temperature"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                      cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                      METHOD_TEMPERATURE_DP);

    ui->lePara1->setText(cSettings.getTemperatureMS(stdSN_T_2932.temperature));
    ui->lePara1->move(310,20);

    ui->lePara1->setReadOnly(true);
    ui->lblPara2->setText(tr("Time"));
    ui->lblPara2->move(20,90);

    dvPara2->setRange(METHOD_TIME_MIN, METHOD_TIME_MAX,
                      METHOD_TIME_DP);
    ui->lePara2->setText(cSettings.getTestTime(stdSN_T_2932.time));
    ui->lePara2->move(310,90);
    ui->lePara2->setReadOnly(true);
    ui->lblPara3->setText(tr("V/L Ratio"));
    ui->lblPara3->move(20,160);

    dvPara3->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lePara3->setText(cSettings.getVLRatio(stdSN_T_2932.vl_ratio));
    ui->lePara3->move(310,160);
    ui->lePara3->setReadOnly(true);

    ui->lblPara3->show();
    ui->lePara3->show();

    ui->frPara1->resize(660,250);
    ui->lblPara4->hide();
    ui->lePara4->hide();
    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();
    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdSN_T_2932.from));

    dvTo->setRange(cSettings.getPressureMS(D6378_METHOD_FROM).toDouble(),
                     cSettings.getPressureMS(D6378_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdSN_T_2932.to));

    ui->cbEnable->setChecked(stdSN_T_2932.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdSN_T_2932.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showD5188()
{
    ui->gbConstants->hide();
    ui->lblPara1_2->hide();
    ui->leInjectPara6->hide();
    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetStdParas, cStringStdParas);
    ui->twMethodSetup->insertTab(1, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    ui->lblPara1->setText(tr("Pressure"));
    ui->lblPara1->move(20,20);

    dvPara1->setRange(cSettings.getPressureMS(METHOD_PRESSURE_MIN).toDouble(),
                      cSettings.getPressureMS(METHOD_PRESSURE_MAX).toDouble(),
                      cSettings.getPressureDPMS());

    ui->lePara1->setText(cSettings.getPressureMS(stdD5188.pressure));

    ui->lePara1->setReadOnly(true);
    ui->lePara1->move(310,20);

    dvPara2->setRange(METHOD_VLRATIO_MIN, METHOD_VLRATIO_MAX,
                      METHOD_VLRATIO_DP);

    ui->lblPara2->setText(tr("V/L Ratio"));
    ui->lblPara2->move(20,90);
    ui->lePara2->setText(cSettings.getVLRatio(stdD5188.vl_ratio));
    ui->lePara2->setReadOnly(true);
    ui->lePara2->move(310,90);

    ui->lePara3->setReadOnly(false);
    ui->lePara3->move(310,160);
    ui->lblPara3->setText(tr("Shaker Speed"));
    ui->lblPara3->move(20,160);

    double D5188ShakerSpeed = (double)(stdD5188.shaker_speed/60.0);
    dvPara3->setRange(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP);
    ui->lePara3->setText(cSettings.getShakerSpeed(D5188ShakerSpeed));

    ui->lblPara3->show();
    ui->lePara3->show();

    ui->frPara1->resize(660,250);
    ui->lblPara4->hide();
    ui->lePara4->hide();
    ui->lblPara5->hide();
    ui->cbSingleExpEnable->hide();

    ui->gbRange->setTitle(tr("\"Pass\" Range T"));

    dvFrom->setRange(cSettings.getTemperatureMS(D5188_METHOD_FROM).toDouble(),
                     cSettings.getTemperatureMS(D5188_METHOD_TO).toDouble(),
                     METHOD_TEMPERATURE_DP);

    ui->lePRPFrom->setText(cSettings.getTemperatureMS(stdD5188.from));

    dvTo->setRange(cSettings.getTemperatureMS(D5188_METHOD_FROM).toDouble(),
                     cSettings.getTemperatureMS(D5188_METHOD_TO).toDouble(),
                     METHOD_TEMPERATURE_DP);

    ui->lePRPTo->setText(cSettings.getTemperatureMS(stdD5188.to));

    ui->cbEnable->setChecked(stdD5188.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdD5188.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showFree1()
{
    ui->gbConstants->show();
    ui->cbFormula->clear();
     ui->cbFormula->insertItems(0, qslFree1);


    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetFreeParas, cStringFreeParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    dvInjectTemperature->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                                  cSettings.getTemperatureMS(stdFree1.temperature).toDouble(),
                                  METHOD_TEMPERATURE_DP);
    ui->leInjectTemp->setText(cSettings.getTemperatureMS(stdFree1.InjectTemp));

    dvTestTemperature->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                                cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                                METHOD_TEMPERATURE_DP);

    ui->leTestTemp->setText(cSettings.getTemperatureMS(stdFree1.temperature));
    ui->leConst1->setText(cSettings.getFormulaConstantsAB(stdFree1.aconstant));
    ui->leConst2->setText(cSettings.getFormulaConstantsAB(stdFree1.bconstant));

    dvcConst->setRange(cSettings.getPressureMS(METHOD_PRESSURE_MIN).toDouble(),
                      cSettings.getPressureMS(METHOD_PRESSURE_MAX).toDouble(),
                      METHOD_CONSTANT_DP);

    ui->leConst3->setText(cSettings.getPressureNaMS(stdFree1.cconstant));

    ui->leTPx1->setText(cSettings.getTestTime(stdFree1.tpx1));
    ui->leTPx2->setText(cSettings.getTestTime(stdFree1.tpx2));
    ui->leTPx3->setText(cSettings.getTestTime(stdFree1.tpx3));
    ui->leVLRatio->setText(cSettings.getVLRatio(stdFree1.vl_ratio));

    ui->cbShakerDisable->setChecked(stdFree1.shaker_disabled);
    double Free1ShakerSpeed = (double)(stdFree1.shaker_speed/60.0);
    dvShaker->setRange(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP);
    ui->cbShakerValue->setText(cSettings.getShakerSpeed(Free1ShakerSpeed));
    ui->cbShakerValue->setReadOnly(!ui->cbShakerDisable->isChecked());

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(FREE_METHOD_FROM).toDouble(),
                      cSettings.getPressureMS(FREE_METHOD_TO).toDouble(),
                      cSettings.getPressureDPMS());

    ui->lePRPFrom->setText(cSettings.getPressureMS(stdFree1.from));

    dvTo->setRange(cSettings.getPressureMS(FREE_METHOD_FROM).toDouble(),
                      cSettings.getPressureMS(FREE_METHOD_TO).toDouble(),
                      cSettings.getPressureDPMS());

    ui->lePRPTo->setText(cSettings.getPressureMS(stdFree1.to));

    ui->cbEnable->setChecked(stdFree1.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdFree1.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showFree2()
{
    ui->gbConstants->show();
    ui->cbFormula->clear();
    ui->cbFormula->insertItems(0, qslFree2);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetFreeParas, cStringFreeParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    dvInjectTemperature->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                                  cSettings.getTemperatureMS(stdFree2.temperature).toDouble(),
                                  METHOD_TEMPERATURE_DP);
    ui->leInjectTemp->setText(cSettings.getTemperatureMS(stdFree2.InjectTemp));

    dvTestTemperature->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                                cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                                METHOD_TEMPERATURE_DP);

    ui->leTestTemp->setText(cSettings.getTemperatureMS(stdFree2.temperature));
    ui->leConst1->setText(cSettings.getFormulaConstantsAB(stdFree2.aconstant));
    ui->leConst2->setText(cSettings.getFormulaConstantsAB(stdFree2.bconstant));

    dvcConst->setRange(cSettings.getPressureMS(METHOD_PRESSURE_MIN).toDouble(),
                      cSettings.getPressureMS(METHOD_PRESSURE_MAX).toDouble(),
                      METHOD_CONSTANT_DP);

    ui->leConst3->setText(cSettings.getPressureNaMS(stdFree2.cconstant));

    ui->leTPx1->setText(cSettings.getTestTime(stdFree2.tpx1));
    ui->leTPx2->setText(cSettings.getTestTime(stdFree2.tpx2));
    ui->leTPx3->setText(cSettings.getTestTime(stdFree2.tpx3));
    ui->leVLRatio->setText(cSettings.getVLRatio(stdFree2.vl_ratio));

    ui->cbShakerDisable->setChecked(stdFree2.shaker_disabled);
    double Free2ShakerSpeed = (double)(stdFree2.shaker_speed/(60.0));
    dvShaker->setRange(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP);
    ui->cbShakerValue->setText(cSettings.getShakerSpeed(Free2ShakerSpeed));
    ui->cbShakerValue->setReadOnly(!ui->cbShakerDisable->isChecked());

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(FREE_METHOD_FROM).toDouble(),
                      cSettings.getPressureMS(FREE_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());
    ui->lePRPFrom->setText(cSettings.getPressureMS(stdFree2.from));

    dvTo->setRange(cSettings.getPressureMS(FREE_METHOD_FROM).toDouble(),
                      cSettings.getPressureMS(FREE_METHOD_TO).toDouble(),
                      cSettings.getPressureDPMS());
    ui->lePRPTo->setText(cSettings.getPressureMS(stdFree2.to));

    ui->cbEnable->setChecked(stdFree2.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdFree2.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());
}

void sMethodSetup::showFree3()
{
    ui->gbConstants->show();

    ui->cbFormula->clear();
    ui->cbFormula->insertItems(0, qslFree3);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetFreeParas, cStringFreeParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    dvInjectTemperature->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                                  cSettings.getTemperatureMS(stdFree3.temperature).toDouble(),
                                  METHOD_TEMPERATURE_DP);
    ui->leInjectTemp->setText(cSettings.getTemperatureMS(stdFree3.InjectTemp));

    dvTestTemperature->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                                cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                                METHOD_TEMPERATURE_DP);

    ui->leTestTemp->setText(cSettings.getTemperatureMS(stdFree3.temperature));
    ui->leConst1->setText(cSettings.getFormulaConstantsAB(stdFree3.aconstant));
    ui->leConst2->setText(cSettings.getFormulaConstantsAB(stdFree3.bconstant));

    dvcConst->setRange(cSettings.getPressureMS(METHOD_PRESSURE_MIN).toDouble(),
                      cSettings.getPressureMS(METHOD_PRESSURE_MAX).toDouble(),
                      METHOD_CONSTANT_DP);

    ui->leConst3->setText(cSettings.getPressureNaMS(stdFree3.cconstant));

    ui->leTPx1->setText(cSettings.getTestTime(stdFree3.tpx1));
    ui->leTPx2->setText(cSettings.getTestTime(stdFree3.tpx2));
    ui->leTPx3->setText(cSettings.getTestTime(stdFree3.tpx3));
    ui->leVLRatio->setText(cSettings.getVLRatio(stdFree3.vl_ratio));

    ui->cbShakerDisable->setChecked(stdFree3.shaker_disabled);
    double Free3ShakerSpeed = (double)(stdFree3.shaker_speed/60.0);
    dvShaker->setRange(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP);
    ui->cbShakerValue->setText(cSettings.getShakerSpeed(Free3ShakerSpeed));
    ui->cbShakerValue->setReadOnly(!ui->cbShakerDisable->isChecked());

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(FREE_METHOD_FROM).toDouble(),
                      cSettings.getPressureMS(FREE_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());
    ui->lePRPFrom->setText(cSettings.getPressureMS(stdFree3.from));

    dvTo->setRange(cSettings.getPressureMS(FREE_METHOD_FROM).toDouble(),
                      cSettings.getPressureMS(FREE_METHOD_TO).toDouble(),
                   cSettings.getPressureDPMS());
    ui->lePRPTo->setText(cSettings.getPressureMS(stdFree3.to));

    ui->cbEnable->setChecked(stdFree3.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdFree3.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::showFree4()
{
    ui->gbConstants->show();

    ui->cbFormula->clear();
    ui->cbFormula->insertItems(0, qslFree4);

    ui->twMethodSetup->clear();
    ui->twMethodSetup->insertTab(0, cWidgetFormula, cStringFormula);
    ui->twMethodSetup->insertTab(1, cWidgetFreeParas, cStringFreeParas);
    ui->twMethodSetup->insertTab(2, cWidgetPassFail, cStringPassFail);
    ui->twMethodSetup->setCurrentIndex(0);

    dvInjectTemperature->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                                  cSettings.getTemperatureMS(stdFree4.temperature).toDouble(),
                                  METHOD_TEMPERATURE_DP);
    ui->leInjectTemp->setText(cSettings.getTemperatureMS(stdFree4.InjectTemp));

    dvTestTemperature->setRange(cSettings.getTemperatureMS(METHOD_TEMPERATURE_MIN).toDouble(),
                                cSettings.getTemperatureMS(METHOD_TEMPERATURE_MAX).toDouble(),
                                METHOD_TEMPERATURE_DP);

    ui->leTestTemp->setText(cSettings.getTemperatureMS(stdFree4.temperature));
    ui->leConst1->setText(cSettings.getFormulaConstantsAB(stdFree4.aconstant));
    ui->leConst2->setText(cSettings.getFormulaConstantsAB(stdFree4.bconstant));

    dvcConst->setRange(cSettings.getPressureMS(METHOD_PRESSURE_MIN).toDouble(),
                      cSettings.getPressureMS(METHOD_PRESSURE_MAX).toDouble(),
                      METHOD_CONSTANT_DP);

    ui->leConst3->setText(cSettings.getPressureNaMS(stdFree4.cconstant));

    ui->leTPx1->setText(cSettings.getTestTime(stdFree4.tpx1));
    ui->leTPx2->setText(cSettings.getTestTime(stdFree4.tpx2));
    ui->leTPx3->setText(cSettings.getTestTime(stdFree4.tpx3));
    ui->leVLRatio->setText(cSettings.getVLRatio(stdFree4.vl_ratio));

    ui->cbShakerDisable->setChecked(stdFree4.shaker_disabled);
    double Free4ShakerSpeed = (double)(stdFree4.shaker_speed/60.0);
    dvShaker->setRange(METHOD_SHAKER_SPEED_MIN, METHOD_SHAKER_SPEED_MAX, METHOD_SHAKER_SPEED_DP);
    ui->cbShakerValue->setText(cSettings.getShakerSpeed(Free4ShakerSpeed));
    ui->cbShakerValue->setReadOnly(!ui->cbShakerDisable->isChecked());

    ui->gbRange->setTitle(tr("\"Pass\" Range P"));

    dvFrom->setRange(cSettings.getPressureMS(FREE_METHOD_FROM).toDouble(),
                      cSettings.getPressureMS(FREE_METHOD_TO).toDouble(),
                     cSettings.getPressureDPMS());
    ui->lePRPFrom->setText(cSettings.getPressureMS(stdFree4.from));

    dvTo->setRange(cSettings.getPressureMS(FREE_METHOD_FROM).toDouble(),
                      cSettings.getPressureMS(FREE_METHOD_TO).toDouble(),
                   cSettings.getPressureDPMS());
    ui->lePRPTo->setText(cSettings.getPressureMS(stdFree4.to));

    ui->cbEnable->setChecked(stdFree4.passfail_enabled);
//    ui->cbAlarmEnable->setChecked(stdFree4.alarm_enabled);

    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());

}

void sMethodSetup::updateD5191()
{

    if(stdD5191.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdD5191.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdD5191.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble()){
//        cParasChanged = true;
//    }
//    stdD5191.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdD5191.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5191.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdD5191.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5191.time = ui->lePara2->text().toDouble();

    if(stdD5191.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5191.vl_ratio = ui->lePara3->text().toDouble();

    if(stdD5191.single_expansion != ui->cbSingleExpEnable->checkState())
    {
        cParasChanged = true;
    }
    stdD5191.single_expansion = ui->cbSingleExpEnable->checkState();

    if(stdD5191.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdD5191.passfail_enabled = ui->cbEnable->checkState();

//    if(stdD5191.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdD5191.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdD5191.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5191.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdD5191.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5191.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateD6377()
{

    if( cSettings.getTemperatureMS(stdD6377.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6377.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdD6377.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6377.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdD6377.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6377.time = ui->lePara2->text().toDouble();

    if(stdD6377.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6377.vl_ratio = ui->lePara3->text().toDouble();
    emit D6377_VlRatio(((stdD6377.vl_ratio * 100)+100));

//    if(stdD6377.shaker_speed != ui->lePara4->text().toInt())
    if((double)(stdD6377.shaker_speed) != (ui->lePara4->text().toDouble()*(60.0)))
    {
        cParasChanged = true;
    }
//    stdD6377.shaker_speed = ui->lePara4->text().toInt();
    stdD6377.shaker_speed = (ui->lePara4->text().toDouble()*(60.0));

    if(stdD6377.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdD6377.passfail_enabled = ui->cbEnable->checkState();

//    if(stdD6377.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdD6377.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdD6377.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6377.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdD6377.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6377.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateD6378()
{

    if(stdD6378.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdD6378.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdD6378.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble())
//    {
//        cParasChanged = true;
//    }
//    stdD6378.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdD6378.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6378.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdD6378.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6378.time = ui->lePara2->text().toDouble();

    if(stdD6378.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6378.vl_ratio = ui->lePara3->text().toDouble();

    if(stdD6378.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdD6378.passfail_enabled = ui->cbEnable->checkState();

//    if(stdD6378.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdD6378.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdD6378.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6378.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdD6378.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD6378.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateEN_13016_1(){
    if(stdEN_13016_1.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdEN_13016_1.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdEN_13016_1.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble()){
//        cParasChanged = true;
//    }
//    stdEN_13016_1.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdEN_13016_1.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_1.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdEN_13016_1.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_1.time = ui->lePara2->text().toDouble();

    if(stdEN_13016_1.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_1.vl_ratio = ui->lePara3->text().toDouble();

    if(stdEN_13016_1.single_expansion != ui->cbSingleExpEnable->checkState())
    {
        cParasChanged = true;
    }
    stdEN_13016_1.single_expansion = ui->cbSingleExpEnable->checkState();

    if(stdEN_13016_1.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdEN_13016_1.passfail_enabled = ui->cbEnable->checkState();

//    if(stdEN_13016_1.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdEN_13016_1.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdEN_13016_1.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_1.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdEN_13016_1.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_1.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateEN_13016_2(){
    if(stdEN_13016_2.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdEN_13016_2.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdEN_13016_2.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble())
//    {
//        cParasChanged = true;
//    }
//    stdEN_13016_2.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdEN_13016_2.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_2.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdEN_13016_2.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_2.time = ui->lePara2->text().toDouble();

    if(stdEN_13016_2.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_2.vl_ratio = ui->lePara3->text().toDouble();

    if(stdEN_13016_2.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdEN_13016_2.passfail_enabled = ui->cbEnable->checkState();

//    if(stdEN_13016_2.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdEN_13016_2.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdEN_13016_2.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_2.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdEN_13016_2.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdEN_13016_2.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateGB_T_8017(){
    if(stdGB_T_8017.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdGB_T_8017.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdGB_T_8017.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble()){
//        cParasChanged = true;
//    }
//    stdGB_T_8017.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdGB_T_8017.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdGB_T_8017.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdGB_T_8017.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdGB_T_8017.time = ui->lePara2->text().toDouble();

    if(stdGB_T_8017.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdGB_T_8017.vl_ratio = ui->lePara3->text().toDouble();

    if(stdGB_T_8017.single_expansion != ui->cbSingleExpEnable->checkState())
    {
        cParasChanged = true;
    }
    stdGB_T_8017.single_expansion = ui->cbSingleExpEnable->checkState();

    if(stdGB_T_8017.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdGB_T_8017.passfail_enabled = ui->cbEnable->checkState();

//    if(stdGB_T_8017.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdGB_T_8017.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdGB_T_8017.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdGB_T_8017.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdGB_T_8017.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdGB_T_8017.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateIP_394(){
    if(stdIP_394.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdIP_394.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdIP_394.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble()){
//        cParasChanged = true;
//    }
//    stdIP_394.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdIP_394.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_394.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdIP_394.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_394.time = ui->lePara2->text().toDouble();

    if(stdIP_394.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_394.vl_ratio = ui->lePara3->text().toDouble();

    if(stdIP_394.single_expansion != ui->cbSingleExpEnable->checkState())
    {
        cParasChanged = true;
    }
    stdIP_394.single_expansion = ui->cbSingleExpEnable->checkState();

    if(stdIP_394.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdIP_394.passfail_enabled = ui->cbEnable->checkState();

//    if(stdIP_394.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdIP_394.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdIP_394.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_394.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdIP_394.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_394.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateIP_409(){
    if(stdIP409.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdIP409.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdIP409.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble())
//    {
//        cParasChanged = true;
//    }
//    stdIP409.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdIP409.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP409.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdIP409.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP409.time = ui->lePara2->text().toDouble();

    if(stdIP409.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP409.vl_ratio = ui->lePara3->text().toDouble();

    if(stdIP409.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdIP409.passfail_enabled = ui->cbEnable->checkState();

//    if(stdIP409.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdIP409.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdIP409.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP409.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdIP409.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP409.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateIP_481(){
    if( cSettings.getTemperatureMS(stdIP_481.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_481.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdIP_481.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_481.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdIP_481.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_481.time = ui->lePara2->text().toDouble();

    if(stdIP_481.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_481.vl_ratio = ui->lePara3->text().toDouble();
    emit IP_481_VlRatio(((stdIP_481.vl_ratio * 100)+100));

//    if(stdIP_481.shaker_speed != ui->lePara4->text().toInt())
    if((double)(stdIP_481.shaker_speed) != (ui->lePara4->text().toDouble()*(60.0)))
    {
        cParasChanged = true;
    }
//    stdIP_481.shaker_speed = ui->lePara4->text().toInt();
    stdIP_481.shaker_speed = (ui->lePara4->text().toDouble()*(60.0));

    if(stdIP_481.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdIP_481.passfail_enabled = ui->cbEnable->checkState();

//    if(stdIP_481.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdIP_481.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdIP_481.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_481.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdIP_481.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdIP_481.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateJIS_K2258_2(){
    if(stdJIS_K2258_2.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdJIS_K2258_2.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdJIS_K2258_2.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble())
//    {
//        cParasChanged = true;
//    }
//    stdJIS_K2258_2.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdJIS_K2258_2.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdJIS_K2258_2.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdJIS_K2258_2.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdJIS_K2258_2.time = ui->lePara2->text().toDouble();

    if(stdJIS_K2258_2.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdJIS_K2258_2.vl_ratio = ui->lePara3->text().toDouble();

    if(stdJIS_K2258_2.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdJIS_K2258_2.passfail_enabled = ui->cbEnable->checkState();

//    if(stdJIS_K2258_2.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdJIS_K2258_2.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdJIS_K2258_2.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdJIS_K2258_2.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdJIS_K2258_2.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdJIS_K2258_2.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateSH_T_0769(){
    if(stdSH_T_0769.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdSH_T_0769.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdSH_T_0769.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble())
//    {
//        cParasChanged = true;
//    }
//    stdSH_T_0769.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdSH_T_0769.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0769.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdSH_T_0769.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0769.time = ui->lePara2->text().toDouble();

    if(stdSH_T_0769.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0769.vl_ratio = ui->lePara3->text().toDouble();

    if(stdSH_T_0769.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdSH_T_0769.passfail_enabled = ui->cbEnable->checkState();

//    if(stdSH_T_0769.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdSH_T_0769.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdSH_T_0769.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0769.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdSH_T_0769.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0769.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateSH_T_0794(){
    if(stdSH_T_0794.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdSH_T_0794.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdSH_T_0794.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble()){
//        cParasChanged = true;
//    }
//    stdSH_T_0794.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdSH_T_0794.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0794.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdSH_T_0794.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0794.time = ui->lePara2->text().toDouble();

    if(stdSH_T_0794.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0794.vl_ratio = ui->lePara3->text().toDouble();

    if(stdSH_T_0794.single_expansion != ui->cbSingleExpEnable->checkState())
    {
        cParasChanged = true;
    }
    stdSH_T_0794.single_expansion = ui->cbSingleExpEnable->checkState();

    if(stdSH_T_0794.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdSH_T_0794.passfail_enabled = ui->cbEnable->checkState();

//    if(stdSH_T_0794.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdSH_T_0794.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdSH_T_0794.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0794.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdSH_T_0794.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSH_T_0794.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateSN_T_2932(){
    if(stdSN_T_2932.formula != ui->cbFormula->currentIndex())
    {
        cParasChanged = true;
    }
    stdSN_T_2932.formula = ui->cbFormula->currentIndex();

//    if( cSettings.getTemperatureMS(stdSN_T_2932.InjectTemp).toDouble() != ui->leInjectPara6->text().toDouble())
//    {
//        cParasChanged = true;
//    }
//    stdSN_T_2932.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectPara6->text().toDouble());

    if( cSettings.getTemperatureMS(stdSN_T_2932.temperature).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSN_T_2932.temperature = cSettings.getTemperatureCelsiusMS(ui->lePara1->text().toDouble());

    if(stdSN_T_2932.time != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSN_T_2932.time = ui->lePara2->text().toDouble();

    if(stdSN_T_2932.vl_ratio != ui->lePara3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSN_T_2932.vl_ratio = ui->lePara3->text().toDouble();

    if(stdSN_T_2932.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdSN_T_2932.passfail_enabled = ui->cbEnable->checkState();

//    if(stdSN_T_2932.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdSN_T_2932.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdSN_T_2932.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSN_T_2932.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdSN_T_2932.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdSN_T_2932.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateD5188()
{
    if( cSettings.getPressureMS(stdD5188.pressure).toDouble() != ui->lePara1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5188.pressure = cSettings.getPressurekPaMS(ui->lePara1->text().toDouble());

    if(stdD5188.vl_ratio != ui->lePara2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5188.vl_ratio = ui->lePara2->text().toDouble();

    if((double)(stdD5188.shaker_speed) != (ui->lePara3->text().toDouble() * (60)))
    {
        cParasChanged = true;
    }
    stdD5188.shaker_speed = (ui->lePara3->text().toDouble()*(60.0));

    if(stdD5188.passfail_enabled != ui->cbEnable->checkState())
    {
         cParasChanged = true;
    }
    stdD5188.passfail_enabled = ui->cbEnable->checkState();

//    if(stdD5188.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdD5188.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getTemperatureMS(stdD5188.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5188.from = cSettings.getTemperatureCelsiusMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getTemperatureMS(stdD5188.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdD5188.to = cSettings.getTemperatureCelsiusMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateFree1()
{

    if( cSettings.getTemperatureMS(stdFree1.InjectTemp).toDouble() != ui->leInjectTemp->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectTemp->text().toDouble());

    if( cSettings.getTemperatureMS(stdFree1.temperature).toDouble() != ui->leTestTemp->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.temperature = cSettings.getTemperatureCelsiusMS(ui->leTestTemp->text().toDouble());

    if(stdFree1.aconstant != ui->leConst1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.aconstant = ui->leConst1->text().toDouble();

    if(stdFree1.bconstant != ui->leConst2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.bconstant = ui->leConst2->text().toDouble();

    if(stdFree1.cconstant != ui->leConst3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.cconstant = ui->leConst3->text().toDouble();

    if(stdFree1.tpx1 != ui->leTPx1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.tpx1 = ui->leTPx1->text().toDouble();

    if(stdFree1.tpx2 != ui->leTPx2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.tpx2 = ui->leTPx2->text().toDouble();

    if(stdFree1.tpx3 != ui->leTPx3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.tpx3 = ui->leTPx3->text().toDouble();

    if(stdFree1.vl_ratio != ui->leVLRatio->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.vl_ratio = ui->leVLRatio->text().toDouble();

    if(stdFree1.shaker_disabled != ui->cbShakerDisable->checkState())
    {
        cParasChanged = true;
    }
    stdFree1.shaker_disabled = ui->cbShakerDisable->checkState();
    qDebug()<<"stdFree1.shaker_disabled from updateFree1: "<<stdFree1.shaker_disabled;

    if((double)(stdFree1.shaker_speed) != (ui->cbShakerValue->text().toDouble() * (60))){
        cParasChanged = true;
    }
    stdFree1.shaker_speed = (ui->cbShakerValue->text().toDouble() * (60));

    if(stdFree1.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdFree1.passfail_enabled = ui->cbEnable->checkState();

//    if(stdFree1.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdFree1.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdFree1.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdFree1.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree1.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());
}

void sMethodSetup::updateFree2()
{
    if( cSettings.getTemperatureMS(stdFree2.InjectTemp).toDouble() != ui->leInjectTemp->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectTemp->text().toDouble());

    if( cSettings.getTemperatureMS(stdFree2.temperature).toDouble() != ui->leTestTemp->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.temperature = cSettings.getTemperatureCelsiusMS(ui->leTestTemp->text().toDouble());

    if(stdFree2.aconstant != ui->leConst1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.aconstant = ui->leConst1->text().toDouble();

    if(stdFree2.bconstant != ui->leConst2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.bconstant = ui->leConst2->text().toDouble();

    if(stdFree2.cconstant != ui->leConst3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.cconstant = ui->leConst3->text().toDouble();

    if(stdFree2.tpx1 != ui->leTPx1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.tpx1 = ui->leTPx1->text().toDouble();

    if(stdFree2.tpx2 != ui->leTPx2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.tpx2 = ui->leTPx2->text().toDouble();

    if(stdFree2.tpx3 != ui->leTPx3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.tpx3 = ui->leTPx3->text().toDouble();

    if(stdFree2.vl_ratio != ui->leVLRatio->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.vl_ratio = ui->leVLRatio->text().toDouble();

    if(stdFree2.shaker_disabled != ui->cbShakerDisable->checkState())
    {
        cParasChanged = true;
    }
    stdFree2.shaker_disabled = ui->cbShakerDisable->checkState();

    if((double)(stdFree2.shaker_speed) != (ui->cbShakerValue->text().toDouble() * 60))
    {
        cParasChanged = true;
    }
    stdFree2.shaker_speed = ui->cbShakerValue->text().toDouble() * 60;

    if(stdFree2.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdFree2.passfail_enabled = ui->cbEnable->checkState();

//    if(stdFree2.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdFree2.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdFree2.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdFree2.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree2.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());

}

void sMethodSetup::updateFree3()
{
    if( cSettings.getTemperatureMS(stdFree3.InjectTemp).toDouble() != ui->leInjectTemp->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectTemp->text().toDouble());

    if(cSettings.getTemperatureMS(stdFree3.temperature).toDouble() != ui->leTestTemp->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.temperature = cSettings.getTemperatureCelsiusMS(ui->leTestTemp->text().toDouble());

    if(stdFree3.aconstant != ui->leConst1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.aconstant = ui->leConst1->text().toDouble();

    if(stdFree3.bconstant != ui->leConst2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.bconstant = ui->leConst2->text().toDouble();

    if(stdFree3.cconstant != ui->leConst3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.cconstant = ui->leConst3->text().toDouble();

    if(stdFree3.tpx1 != ui->leTPx1->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.tpx1 = ui->leTPx1->text().toDouble();

    if(stdFree3.tpx2 != ui->leTPx2->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.tpx2 = ui->leTPx2->text().toDouble();

    if(stdFree3.tpx3 != ui->leTPx3->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.tpx3 = ui->leTPx3->text().toDouble();

    if(stdFree3.vl_ratio != ui->leVLRatio->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.vl_ratio = ui->leVLRatio->text().toDouble();

    if(stdFree3.shaker_disabled != ui->cbShakerDisable->checkState())
    {
        cParasChanged = true;
    }
    stdFree3.shaker_disabled = ui->cbShakerDisable->checkState();

    if((double)(stdFree3.shaker_speed) != (ui->cbShakerValue->text().toDouble() * 60))
    {
        cParasChanged = true;
    }
    stdFree3.shaker_speed = (ui->cbShakerValue->text().toDouble() * 60);

    if(stdFree3.passfail_enabled != ui->cbEnable->checkState())
    {
        cParasChanged = true;
    }
    stdFree3.passfail_enabled = ui->cbEnable->checkState();

//    if(stdFree3.alarm_enabled != ui->cbAlarmEnable->checkState())
//    {
//        cParasChanged = true;
//    }
//    stdFree3.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdFree3.from).toDouble() != ui->lePRPFrom->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdFree3.to).toDouble() != ui->lePRPTo->text().toDouble())
    {
        cParasChanged = true;
    }
    stdFree3.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());
}

void sMethodSetup::updateFree4()
{
    if( cSettings.getTemperatureMS(stdFree4.InjectTemp).toDouble() != ui->leInjectTemp->text().toDouble()) cParasChanged = true;
    stdFree4.InjectTemp = cSettings.getTemperatureCelsiusMS(ui->leInjectTemp->text().toDouble());

    if(cSettings.getTemperatureMS(stdFree4.temperature).toDouble() != ui->leTestTemp->text().toDouble()) cParasChanged = true;
    stdFree4.temperature = cSettings.getTemperatureCelsiusMS(ui->leTestTemp->text().toDouble());

    if(stdFree4.aconstant != ui->leConst1->text().toDouble()) cParasChanged = true;
    stdFree4.aconstant = ui->leConst1->text().toDouble();

    if(stdFree4.bconstant != ui->leConst2->text().toDouble()) cParasChanged = true;
    stdFree4.bconstant = ui->leConst2->text().toDouble();

    if(stdFree4.cconstant != ui->leConst3->text().toDouble()) cParasChanged = true;
    stdFree4.cconstant = ui->leConst3->text().toDouble();

    if(stdFree4.tpx1 != ui->leTPx1->text().toDouble()) cParasChanged = true;
    stdFree4.tpx1 = ui->leTPx1->text().toDouble();

    if(stdFree4.tpx2 != ui->leTPx2->text().toDouble()) cParasChanged = true;
    stdFree4.tpx2 = ui->leTPx2->text().toDouble();

    if(stdFree4.tpx3 != ui->leTPx3->text().toDouble()) cParasChanged = true;
    stdFree4.tpx3 = ui->leTPx3->text().toDouble();

    if(stdFree4.vl_ratio != ui->leVLRatio->text().toDouble()) cParasChanged = true;
    stdFree4.vl_ratio = ui->leVLRatio->text().toDouble();

    if(stdFree4.shaker_disabled != ui->cbShakerDisable->checkState()) cParasChanged = true;
    stdFree4.shaker_disabled = ui->cbShakerDisable->checkState();

    if((double)(stdFree4.shaker_speed) != (ui->cbShakerValue->text().toDouble() * 60)) cParasChanged = true;
    stdFree4.shaker_speed = (ui->cbShakerValue->text().toDouble() * 60);

    if(stdFree4.passfail_enabled != ui->cbEnable->checkState()) cParasChanged = true;
    stdFree4.passfail_enabled = ui->cbEnable->checkState();

//    if(stdFree4.alarm_enabled != ui->cbAlarmEnable->checkState()) cParasChanged = true;
//    stdFree4.alarm_enabled = ui->cbAlarmEnable->checkState();

    if(cSettings.getPressureMS(stdFree4.from).toDouble() != ui->lePRPFrom->text().toDouble()) cParasChanged = true;
    stdFree4.from = cSettings.getPressurekPaMS(ui->lePRPFrom->text().toDouble());

    if(cSettings.getPressureMS(stdFree4.to).toDouble() != ui->lePRPTo->text().toDouble()) cParasChanged = true;
    stdFree4.to = cSettings.getPressurekPaMS(ui->lePRPTo->text().toDouble());
}

bool sMethodSetup::isSwitchEnabled(int tmp)
{
    checkExit(tmp);
    return cEnSwitch;
}

void sMethodSetup::checkExit(int tmp)
{
    if(cPrevMethod == ui->cbMethod->currentIndex())
    {
        switch (cPrevMethod) {

            case M_METHOD_NEW_D5191: updateD5191(); break;
            case M_METHOD_NEW_D6377: updateD6377(); break;
            case M_METHOD_NEW_D6378: updateD6378(); break;
            case M_METHOD_NEW_D5188: updateD5188(); break;

            case M_METHOD_EN_13016_1: updateEN_13016_1(); break;
            case M_METHOD_EN_13016_2: updateEN_13016_2(); break;
            case M_METHOD_GB_T_8017: updateGB_T_8017(); break;
            case M_METHOD_IP_394: updateIP_394(); break;
            case M_METHOD_IP_409: updateIP_409(); break;
            case M_METHOD_IP_481: updateIP_481(); break;
            case M_METHOD_JIS_K2258_2: updateJIS_K2258_2(); break;
            case M_METHOD_SH_T_0769: updateSH_T_0769(); break;
            case M_METHOD_SH_T_0794: updateSH_T_0794(); break;
            case M_METHOD_SN_T_2932: updateSN_T_2932(); break;

            case M_METHOD_NEW_FREE1: updateFree1(); break;
            case M_METHOD_NEW_FREE2: updateFree2(); break;
            case M_METHOD_NEW_FREE3: updateFree3(); break;
            case M_METHOD_NEW_FREE4: updateFree4(); break;
        }
    }

    if(cParasChanged)
    {
        cEnSwitch = false;
        emit getConfirmation(M_CONFIRM_METHOD, tmp);
    }
    else if(exitClicked)
    {
        exitClicked = false;
        this->hide();
        emit showHome(false);
    }
    else{

    }
}

void sMethodSetup::on_cbMethod_currentIndexChanged(int index)
{
    if(!isVisible()) return; 
    
    if(cPrevMethod != index)
    {
        switch (cPrevMethod) {

        case M_METHOD_NEW_D5191: updateD5191();
            break;
            case M_METHOD_NEW_D6377: updateD6377();
            break;
            case M_METHOD_NEW_D6378: updateD6378();
            break;
        case M_METHOD_NEW_D5188: updateD5188();
            break;
        case M_METHOD_EN_13016_1: updateEN_13016_1();
            break;
        case M_METHOD_EN_13016_2: updateEN_13016_2();
            break;
        case M_METHOD_GB_T_8017: updateGB_T_8017();
            break;
        case M_METHOD_IP_394: updateIP_394();
            break;
        case M_METHOD_IP_409: updateIP_409();
            break;
        case M_METHOD_IP_481: updateIP_481();
            break;
        case M_METHOD_JIS_K2258_2: updateJIS_K2258_2();
            break;
        case M_METHOD_SH_T_0769: updateSH_T_0769();
            break;
        case M_METHOD_SH_T_0794: updateSH_T_0794();
            break;
        case M_METHOD_SN_T_2932: updateSN_T_2932();
            break;

            case M_METHOD_NEW_FREE1: updateFree1();
            break;
            case M_METHOD_NEW_FREE2: updateFree2();
            break;
            case M_METHOD_NEW_FREE3: updateFree3();
            break;
            case M_METHOD_NEW_FREE4: updateFree4();
            break;
        }
    }

    if(cParasChanged)
        emit getConfirmation(M_CONFIRM_METHOD_SWITCH, M_MEASURING);

    cPrevMethod = index;

    switch(index)
    {
        case M_METHOD_NEW_D5191: showD5191(); break;
        case M_METHOD_NEW_D6377: showD6377(); break;
        case M_METHOD_NEW_D6378: showD6378(); break;
        case M_METHOD_NEW_D5188: showD5188(); break;
        case M_METHOD_EN_13016_1: showEN_13016_1(); break;
        case M_METHOD_EN_13016_2: showEN_13016_2(); break;
        case M_METHOD_GB_T_8017: showGB_T_8017(); break;
        case M_METHOD_IP_394: showIP_394(); break;
        case M_METHOD_IP_409: showIP_409(); break;
        case M_METHOD_IP_481: showIP_481(); break;
        case M_METHOD_JIS_K2258_2: showJIS_K2258_2(); break;
        case M_METHOD_SH_T_0769: showSH_T_0769(); break;
        case M_METHOD_SH_T_0794: showSH_T_0794(); break;
        case M_METHOD_SN_T_2932: showSN_T_2932(); break;

        case M_METHOD_NEW_FREE1: showFree1(); break;
        case M_METHOD_NEW_FREE2: showFree2(); break;
        case M_METHOD_NEW_FREE3: showFree3(); break;
        case M_METHOD_NEW_FREE4: showFree4(); break;
    }
}

void sMethodSetup::on_cbEnable_clicked()
{
    ui->lePRPFrom->setReadOnly(!ui->cbEnable->isChecked());
    ui->lePRPTo->setReadOnly(!ui->cbEnable->isChecked());
//    ui->cbAlarmEnable->setEnabled(ui->cbEnable->isChecked());
 }

void sMethodSetup::onShowKeypad(int tmp)
{
   emit showKeypad(QObject::sender(), KAYPAD_NUMERIC, false);
}

void sMethodSetup::ontextChanged(QString tmp)
{

    QLineEdit *tle = qobject_cast<QLineEdit *>(QObject::sender());

    if(tle)
    {
        if(!tle->hasAcceptableInput())
        {
            tle->setProperty("error", true);
            tle->style()->polish(tle);

            if(ui->twMethodSetup->currentIndex() != 0)
                ui->twMethodSetup->setTabEnabled(0, false);

            if(ui->twMethodSetup->currentIndex() != 1)
                ui->twMethodSetup->setTabEnabled(1, false);

            if(ui->twMethodSetup->currentIndex() != 2)
                ui->twMethodSetup->setTabEnabled(2, false);

            ui->cbMethod->setEnabled(false);

            ui->pbSave->setEnabled(false);

        }
        else
        {
            tle->setProperty("error", false);
            tle->style()->polish(tle);

            ui->twMethodSetup->setTabEnabled(0, true);
            ui->twMethodSetup->setTabEnabled(1, true);
            ui->twMethodSetup->setTabEnabled(2, true);

            ui->cbMethod->setEnabled(true);
            ui->cbEnable->setEnabled(true);

            ui->pbSave->setEnabled(true);

            if(ui->frPassFail->isVisible())
            {
                double from = ui->lePRPFrom->text().toDouble();
                double to = ui->lePRPTo->text().toDouble();

                if(from > to)
                {
                    tle->setProperty("error", true);
                    tle->style()->polish(tle);

                    if(ui->twMethodSetup->currentIndex() != 0)
                        ui->twMethodSetup->setTabEnabled(0, false);

                    if(ui->twMethodSetup->currentIndex() != 1)
                        ui->twMethodSetup->setTabEnabled(1, false);

                    if(ui->twMethodSetup->currentIndex() != 2)
                        ui->twMethodSetup->setTabEnabled(2, false);

                    ui->cbMethod->setEnabled(false);
                    ui->cbEnable->setEnabled(false);
                    ui->pbSave->setEnabled(false);
                }
            }
        }
    }

}

void sMethodSetup::on_pbSave_clicked()
{
    if(cPrevMethod == ui->cbMethod->currentIndex())
    {
        switch (cPrevMethod) {

            case M_METHOD_NEW_D5191: updateD5191(); break;
            case M_METHOD_NEW_D6377: updateD6377(); break;
            case M_METHOD_NEW_D6378: updateD6378(); break;
            case M_METHOD_NEW_D5188: updateD5188(); break;

            case M_METHOD_EN_13016_1: updateEN_13016_1(); break;
            case M_METHOD_EN_13016_2: updateEN_13016_2(); break;
            case M_METHOD_GB_T_8017: updateGB_T_8017(); break;
            case M_METHOD_IP_394: updateIP_394(); break;
            case M_METHOD_IP_409: updateIP_409(); break;
            case M_METHOD_IP_481: updateIP_481(); break;
            case M_METHOD_JIS_K2258_2: updateJIS_K2258_2(); break;
            case M_METHOD_SH_T_0769: updateSH_T_0769(); break;
            case M_METHOD_SH_T_0794: updateSH_T_0794(); break;
            case M_METHOD_SN_T_2932: updateSN_T_2932(); break;

            case M_METHOD_NEW_FREE1: updateFree1(); break;
            case M_METHOD_NEW_FREE2: updateFree2(); break;
            case M_METHOD_NEW_FREE3: updateFree3(); break;
            case M_METHOD_NEW_FREE4: updateFree4(); break;
        }
    }

    saveFile();
}

void sMethodSetup::on_pbExit_clicked()
{
    qDebug()<< __FILE__ << __LINE__ <<"cParasChanged: "<<cParasChanged;
    exitClicked = true;
    checkExit(M_MEASURING);
}

void sMethodSetup::on_imageCapture_clicked()
{
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

        //QString filename = QApplication::applicationDirPath() + QString("/screenshot/smethodsetup_%1.png").arg(timestamp);
        QString filename = QString("/run/media/sda1/screenshot/_%1_smethodsetup.png").arg(timestamp);
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

void sMethodSetup::on_cbShakerDisable_clicked()
{
    qDebug()<<"ui->cbShakerDisable->isChecked() "<<ui->cbShakerDisable->isChecked();
    qDebug()<<"stdFree1.shaker_disabled: "<<stdFree1.shaker_disabled;
    ui->cbShakerValue->setReadOnly(!ui->cbShakerDisable->isChecked());
}
