#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(parent);

#ifdef Q_OS_WIN32

    //view->setGeometry(0,0,600,800);
    view->setGeometry(0,0,768,1024);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

#else
   view->setGeometry(0,0,768,1024);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
#endif

    QGraphicsProxyWidget *proxy = scene->addWidget(this);
    view->setScene(scene);
    view->show();

#ifdef Q_OS_WIN32

#else
   view->rotate(90);
#endif

   /*
    * Language Setting
    */

   QString path = QApplication::applicationDirPath();

   qDebug()<<"Path Checking: "<<path;

   path.append("/languages/");

   switch(setLanguage())
   {
       case 0: break;

       case 1: if(translatorLa.load(path + "/pApp_la.qm"))
               {
                   qDebug()<<"successfully load pApp_la file.";
                   qApp->installTranslator(&translatorLa);
               }
               break;

       case 2: if(translatorDe.load(path + "/pApp_de.qm"))
               {
                   qDebug()<<"successfully load pApp_de file.";
                   qApp->installTranslator(&translatorDe);
               }
               break;

       case 3: if(translatorFr.load(path + "/pApp_fr.qm"))
               {
                   qDebug()<<"successfully load pApp_fr file.";
                   qApp->installTranslator(&translatorFr);
               }
               break;
   }


    ui->setupUi(this);

    ui->wCalibrationSetup->IsLanguage = setLanguage();
    setLists();
    setMeasuring();

    ui->wCheckPass->resize(768, 876+92-10);
    ui->wCheckPass->move(0, 180-92+20);
    ui->wCheckPass->hide();

    connect(ui->wCheckPass, SIGNAL(SendData(QString, QString, int, int)), this, SLOT(onPassDataReceived(QString, QString, int, int)));
    connect(ui->wCheckPass, SIGNAL(showKeypad(QObject*,int,bool)), this, SLOT(onShowKeypad(QObject*,int,bool)));
    connect(ui->wCheckPass, SIGNAL(Confirmed(int, bool, int)), this, SLOT(onConfirmed(int, bool, int)));

   ui->wError->resize(768, 876+92-10);
    ui->wError->move(0, 180-92+20);
    ui->wError->hide();

    connect(ui->wError, SIGNAL(SendData(QString, QString, int, int)), this, SLOT(onPassDataReceived(QString, QString, int, int)));
    connect(ui->wError, SIGNAL(showKeypad(QObject*,int,bool)), this, SLOT(onShowKeypad(QObject*,int,bool)));
    connect(ui->wError, SIGNAL(Confirmed(int, bool, int)), this, SLOT(onConfirmed(int, bool, int)));

    ui->wMenuBar->resize(768, 86);
    ui->wMenuBar->move(0,92);

    ui->wMeasuring1->resize(768, 876);
    ui->wMeasuring1->move(0, 180);
    ui->wMeasuring1->setMethods(qslMethods);
    ui->wMeasuring1->readOperatorsFile();
    ui->wMeasuring1->readSampleIdsFile();
    ui->wMeasuring1->Show();

    ui->wMeasuring2->resize(768, 876);
    ui->wMeasuring2->move(0, 180);
    ui->wMeasuring2->hide();

    ui->wCleaning->resize(768, 876);
    ui->wCleaning->move(0, 180);
    ui->wCleaning->hide();

    ui->wMemory->resize(768, 876+92-10);
    ui->wMemory->move(0, 180-92+10);
    ui->wMemory->hide();

    QString errlist;

    if(!ui->wMemory->readFile())
    {
        errlist.append("Memory Setup");
        ui->wMemory->saveFile();
    }

    ui->wMemory->readTests();

    ui->wUserSetup->resize(768, 876+92-10);
    ui->wUserSetup->move(0, 180-92+10);
    ui->wUserSetup->hide();

    if(!ui->wUserSetup->readFile())
    {
        errlist.append("User Setup");
        ui->wUserSetup->saveFile();
    }

    ui->wGeneralSetup->resize(768, 876+92-10);
    ui->wGeneralSetup->move(0, 180-92+10);
    ui->wGeneralSetup->hide();
    ui->wGeneralSetup->setDateFormat(qslDateFormat);
    ui->wGeneralSetup->setTimeFormat(qslTimeFormat);
    ui->wGeneralSetup->setLanguage(qslLanguage);
    ui->wGeneralSetup->setPressureScale(qslPressureScale);
    ui->wGeneralSetup->setTemperatureScale(qsTemperatureScaleFull);

    ui->wGeneralSetup->setEmulation(qslEmulation);
    ui->wGeneralSetup->setBaudRate(qslBaudRate);
    ui->wGeneralSetup->setParity(qslParity);
    ui->wGeneralSetup->setFlow(qslFlow);

    ui->wGeneralSetup->setStopBits(qslStopBits);
    ui->wGeneralSetup->setDataBits(qslDataBits);

    ui->wGeneralSetup->setPageSize(qslPageSize);
    ui->wGeneralSetup->setReportFormat(qslReportFormat);

    if(!ui->wGeneralSetup->readFile())
    {
        if(errlist.isEmpty()) errlist.append("General Setup");
        else errlist.append(", General Setup");
        ui->wGeneralSetup->saveFile();
    }

    ui->wMethodSetup->resize(768, 876+92-10);
    ui->wMethodSetup->move(0, 180-92+10);
    ui->wMethodSetup->setMethods(qslMethods);
    ui->wMethodSetup->setD5191(qslFormulaD5191);
    ui->wMethodSetup->setD6378(qslFormulaD6378);
    ui->wMethodSetup->setFree1(qslFormulaFree1);
    ui->wMethodSetup->setFree2(qslFormulaFree2);
    ui->wMethodSetup->setFree3(qslFormulaFree3);
    ui->wMethodSetup->setFree4(qslFormulaFree4);
    ui->wMethodSetup->hide();

    if(!ui->wMethodSetup->readFile())
    {
        if(errlist.isEmpty()) errlist.append("Method Setup");
        else errlist.append(", Method Setup");
        ui->wMethodSetup->saveFile();
    }

    ui->wServiceSetup->resize(768, 876+92-10);
    ui->wServiceSetup->move(0, 180-92+10);
    ui->wServiceSetup->hide();

    if(!ui->wServiceSetup->readFile())
    {
        if(errlist.isEmpty()) errlist.append("Service Setup");
        else errlist.append(", Service Setup");
        ui->wServiceSetup->saveFile();
    }


    ui->wServiceSetup->readErrorLogFile();

    ui->wCalibrationSetup->resize(768, 876+92-10);
    ui->wCalibrationSetup->move(0, 180-92+10);
    ui->wCalibrationSetup->hide();
    if(!ui->wCalibrationSetup->readFile())
    {
        if(errlist.isEmpty()) errlist.append("Calibration Setup");
        else errlist.append(", Calibration Setup");
        ui->wCalibrationSetup->saveFile();
    }

    ui->listSetupMenu->hide();

    ui->wKeypad->resize(768, 1024);
    ui->wKeypad->move(0, 0);
    ui->wKeypad->hide();

    ui->wFileSelect->resize(768, 1024);
    ui->wFileSelect->move(0, 0);
    ui->wFileSelect->hide();

    connect(ui->wMenuBar, SIGNAL(MenuClicked(int)), this, SLOT(onMenuClicked(int)));

    connect(ui->wFileSelect, SIGNAL(FileSelected(QString)), this, SLOT(onFileSelected(QString)));

    connect(ui->wMeasuring1, SIGNAL(showKeypad(QObject*,int,bool)), this, SLOT(onShowKeypad(QObject*,int,bool)));
    connect(ui->wMeasuring1, SIGNAL(showMsgBox(QString, QString)), this, SLOT(onShowMsgBox(QString, QString)));
    connect(ui->wGeneralSetup, SIGNAL(showKeypad(QObject*,int,bool)), this, SLOT(onShowKeypad(QObject*,int,bool)));

    connect(ui->wMethodSetup, SIGNAL(showMsgBox(QString, QString)), this, SLOT(onShowMsgBox(QString, QString)));
    connect(ui->wMethodSetup, SIGNAL(showKeypad(QObject*,int,bool)), this, SLOT(onShowKeypad(QObject*,int,bool)));

    connect(ui->wServiceSetup, SIGNAL(showKeypad(QObject*,int,bool)), this, SLOT(onShowKeypad(QObject*,int,bool)));
    connect(ui->wCalibrationSetup, SIGNAL(showKeypad(QObject*,int,bool)), this, SLOT(onShowKeypad(QObject*,int,bool)));

    connect(ui->wMemory, SIGNAL(getConfirmation(int, int)), this, SLOT(onGetConfirmation(int, int)));
    connect(ui->wMemory, SIGNAL(showMsgBox(QString, QString)), this, SLOT(onShowMsgBox(QString, QString)));
    connect(ui->wMemory, SIGNAL(showStatusBox(QString,QString, bool)), this, SLOT(onShowStatusBox(QString, QString, bool)));

    connect(ui->wUserSetup, SIGNAL(getConfirmation(int, int)), this, SLOT(onGetConfirmation(int, int)));
    connect(ui->wUserSetup, SIGNAL(showMsgBox(QString, QString)), this, SLOT(onShowMsgBox(QString, QString)));
    connect(ui->wGeneralSetup, SIGNAL(getConfirmation(int, int)), this, SLOT(onGetConfirmation(int, int)));
    connect(ui->wGeneralSetup, SIGNAL(showMsgBox(QString, QString)), this, SLOT(onShowMsgBox(QString, QString)));

    connect(ui->wMethodSetup, SIGNAL(getConfirmation(int, int)), this, SLOT(onGetConfirmation(int, int)));
    connect(ui->wServiceSetup, SIGNAL(getConfirmation(int, int)), this, SLOT(onGetConfirmation(int, int)));
    connect(ui->wCalibrationSetup, SIGNAL(getConfirmation(int, int)), this, SLOT(onGetConfirmation(int, int)));

    connect(ui->wServiceSetup, SIGNAL(getPass()), this, SLOT(onGetPass()));
    connect(ui->wCleaning, SIGNAL(showHome(bool)), this, SLOT(onShowHome(bool)));
    connect(ui->wMemory, SIGNAL(showHome(bool)), this, SLOT(onShowHome(bool)));
    connect(ui->wUserSetup, SIGNAL(showHome(bool)), this, SLOT(onShowHome(bool)));
    connect(ui->wGeneralSetup, SIGNAL(showHome(bool)), this, SLOT(onShowHome(bool)));
    connect(ui->wMethodSetup, SIGNAL(showHome(bool)), this, SLOT(onShowHome(bool)));
    connect(ui->wCalibrationSetup, SIGNAL(showHome(bool)), this, SLOT(onShowHome(bool)));

    connect(ui->wServiceSetup, SIGNAL(showHome(bool)), this, SLOT(onShowHome(bool)));
    connect(ui->wServiceSetup, SIGNAL(showFileSelect()), this, SLOT(onShowFileSelect()));
    connect(ui->wServiceSetup, SIGNAL(showMsgBox(QString, QString)), this, SLOT(onShowMsgBox(QString, QString)));
    connect(ui->wServiceSetup, SIGNAL(showStatusBox(QString, QString, bool)), this, SLOT(onShowStatusBox(QString, QString, bool)));

   

    connect(ui->wMeasuring1, SIGNAL(runClicked(int, bool)), this, SLOT(onRunClicked(int, bool)));
    connect(ui->wMeasuring1, SIGNAL(saveResult(double, double, double, QString, QString, double, double, double, double, double, double, double)), this, SLOT(onSaveResult(double, double, double, QString, QString, double, double, double, double, double, double, double)));

    connect(ui->wCleaning, SIGNAL(runClicked(int, bool)), this, SLOT(onRunClicked(int, bool)));
    connect(ui->wServiceSetup, SIGNAL(runClicked(int, bool)), this, SLOT(onRunClicked(int, bool)));

    //connect(ui->wUserSetup, SIGNAL(sendCommand(QString)), this, SLOT(onSendCommand(QString)));
    connect(ui->wUserSetup, SIGNAL(sendCommand(QString, sAccessWidget *)), this, SLOT(onSendCommand(QString, sAccessWidget *)));
    //connect(ui->wServiceSetup, SIGNAL(sendCommand(QString)), this, SLOT(onSendCommand(QString)));
    connect(ui->wServiceSetup, SIGNAL(sendCommand(QString, sAccessWidget *)), this, SLOT(onSendCommand(QString, sAccessWidget *)));


    //connect(ui->wCalibrationSetup, SIGNAL(sendCommand(QString)), this, SLOT(onSendCommand(QString)));
    connect(ui->wCalibrationSetup, SIGNAL(sendCommand(QString, sAccessWidget *)), this, SLOT(onSendCommand(QString, sAccessWidget *)));
    connect(ui->wCalibrationSetup, SIGNAL(runClicked(int, bool)), this, SLOT(onRunClicked(int, bool)));
    connect(ui->wCalibrationSetup, SIGNAL(showMsgBox(QString, QString)), this, SLOT(onShowMsgBox(QString, QString)));
    //connect(ui->wCalibrationSetup, SIGNAL(showStatusBox(QString,QString, bool)), this, SLOT(onShowStatusBox(QString, QString, bool)));
    connect(ui->wCalibrationSetup, SIGNAL(updateMainWindow(void)), this, SLOT(onUpdateMainWindow(void)));

    cWidget = ui->wMeasuring1;
    cAccessWidget = ui->wMeasuring1;

    ui->wMenuBar->setSelectedMenu(M_MEASURING);
    cMenu = M_MEASURING;

    cValvePosition = -1;
    cPistonPosition = -1;
    cRawATemperature = -1;
    cRawCTemperature = -1;
    cRawCPressure = -1;
    cStepperSpeed = -1;

    cParasUpdated = false; //true;
    cDiagErrorHandle = false;

    cPrCount = 0;

    cFrameReceived = 0;
    cFrameErrorShown = false;
    cFrameTimeOut = 0;

    cFrameError = false;
    dcount = 0;
    cStage = 0;
    cStageTimeOut = 0;
 
    cErrorPos = 0;
    cPrevUCError = 0;
    cCurrentUCError = 0;
    cTimeOutError = 0;
    cStrringErrorCount = 0;

    cTest = new TestStruct();

    cCRFlag = false;
    cCRTimeout = CONTINUOUS_RUN_TIMEOUT;

   
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleErrorSerial(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readSerial()));

    cDateTime = QDateTime::currentDateTime().addSecs(ui->wUserSetup->getGMTSeconds()); 

    ui->lblDate->setText(cDateTime.toString(qslShowDateFormat.at(ui->wGeneralSetup->general_setup.date_format)));
    ui->lblTime->setText(cDateTime.toString(qslShowTimeFormat.at(ui->wGeneralSetup->general_setup.time_format)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onLoad()
{
    this->show();

#ifdef Q_OS_WIN32

    cRawCTemperature = cSettings.getTemperatureCount(20);
    cValvePosition = M_VALVE_POSITION_EXHAUST;
    //cPistonPosition = 5; //0;  //14-July-2022 for testing changed to 5
    cPistonPosition = 0;  //14-July-2022 for testing changed to 5

    cIdleTimeout = 0;
    cStartTimeoutFlag = false;

    cInitDone = false;
    cInitSuccess = false;

    cStageTimeOut = 2; //3; //10;

    cFrameReceived = true;
    cFrameTimeOut = 0;
    cFrameErrorShown = false;

    startTimer(1000);
    qApp->installEventFilter(this);
    openSerial("COM26");

#else

    ui->pushButton->hide();
    ui->pushButton_2->hide();

    cIdleTimeout = 0;
    cStartTimeoutFlag = false;

    cInitDone = false;
    cInitSuccess = false;

    cStageTimeOut = 12*60; //3-Sept-2021 //240; //3; //10;

    cFrameReceived = true;
    cFrameTimeOut = 0;
    cFrameErrorShown = false;

    startTimer(1000);
    qApp->installEventFilter(this);
    openSerial("/dev/ttymxc1");

#endif

    cNAKCount = 0;

    //cACKReceived = true;
    cWaitForACK = true;
    cACKReceived = false;
    cNACKReceived = false;
    cUACKReceived = false;

    int tc = cSettings.getTemperatureCount(20); 

    //onSendCommand(cProtocol.sendMeasuring(1, tc));
    //cPCMD = cProtocol.sendMeasuring(1, tc);

    //sendPara(cProtocol.sendMeasuring(1, tc), 1, cStageTimeOut);


    sendPara(cProtocol.sendMeasuringStart(1, tc), 1, cStageTimeOut);
    QString info = (setLanguage()==0)?"Information":(setLanguage()==1)?"Información":(setLanguage()==2)?"Information":"Information";
    QString initial = (setLanguage()==0)?"Initializing...\nPlease wait...":(setLanguage()==1)?"Inicializando...\nPor favor espere...":(setLanguage()==2)?"Initialisierung wird durchgeführt...\nBitte warten...":"Initialisation...\nVeuillez patienter...";
    onShowStatusBox(info, initial, true);

}


void MainWindow::setLists()
{
    QString CheckPistonMotor;
    QString PressureLimitExceeded;
    QString DeviceTempExceeded;
    QString CheckHeatingElement;
    QString CheckValveMotor;
    QString CheckPressureSensor;
    QString CheckStirringMotor;
    QString Err;
    QString PistonMotorFault;
    QString PistonPositionFault;
    QString PressureHighFault;
    QString TECfailureFault;
    QString ValveMotorFault;
    QString ValveSwitchesFault;
    QString PressureReadingFault;
    QString StiringMotorFault;
    if(setLanguage()==0){
        CheckPistonMotor = "Check Piston Motor";
        PressureLimitExceeded = "Pressure Limit Exceeded";
        DeviceTempExceeded = "Device Temp Exceeded";
        CheckHeatingElement = "Check Heating Element";
        CheckValveMotor = "Check Valve Motor";
        CheckPressureSensor = "Check Pressure Sensor";
        CheckStirringMotor = "Check Stirring Motor";
        Err = "Error";
        PistonMotorFault = "Piston Motor Fault";
        PistonPositionFault = "Piston Position Fault";
        PressureHighFault = "Pressure High Fault";
        TECfailureFault = "TEC failure Fault";
        ValveMotorFault = "Valve Motor Fault";
        ValveSwitchesFault = "Valve Switches Fault";
        PressureReadingFault = "Pressure reading Fault";
        StiringMotorFault = "Stiring Motor Fault";
    }
    else if(setLanguage()==1){
        CheckPistonMotor = "Revisar el motor de pistón";
        PressureLimitExceeded = "Límite de presión excedido";
        DeviceTempExceeded = "Temperatura del dispositivo excedida";
        CheckHeatingElement = "Comprobar el elemento calefactor";
        CheckValveMotor = "Motor de válvula de retención";
        CheckPressureSensor = "Comprobar el sensor de presión";
        CheckStirringMotor = "Comprobar el motor de agitación";
        Err = "Error";
        PistonMotorFault = "Falla del motor de pistón";
        PistonPositionFault = "Fallo de posición del pistón";
        PressureHighFault = "Fallo de presión alta";
        TECfailureFault = "Fallo TEC Fallo";
        ValveMotorFault = "Fallo del motor de la válvula";
        ValveSwitchesFault = "Fallo de los interruptores de válvula";
        PressureReadingFault = "Fallo de lectura de presión";
        StiringMotorFault = "Fallo del motor de agitación";
    }
    else if(setLanguage()==2){
        CheckPistonMotor = "Kolbenmotor prüfen";
        PressureLimitExceeded = "Druckgrenzwert überschritten";
        DeviceTempExceeded = "Gerätetemperatur überschritten";
        CheckHeatingElement = "Heizelement prüfen";
        CheckValveMotor = "Ventilmotor prüfen";
        CheckPressureSensor = "Drucksensor prüfen";
        CheckStirringMotor = "Überprüfen Sie den Rührmotor";
        Err = "Fehler";
        PistonMotorFault = "Kolbenmotorfehler";
        PistonPositionFault = "Kolbenpositionsfehler";
        PressureHighFault = "Fehler „Druck zu hoch“";
        TECfailureFault = "TEC-Fehler Fehler";
        ValveMotorFault = "Ventilmotorfehler";
        ValveSwitchesFault = "Ventilschaltfehler";
        PressureReadingFault = "Druckmessfehler";
        StiringMotorFault = "Störung des Rührmotors";
    }
    else{
        CheckPistonMotor = "Vérifier le moteur à piston";
        PressureLimitExceeded = "Limite de pression dépassée";
        DeviceTempExceeded = "Température de l'appareil dépassée";
        CheckHeatingElement = "Vérifier l'élément chauffant";
        CheckValveMotor = "Moteur de clapet anti-retour";
        CheckPressureSensor = "Vérifier le capteur de pression";
        CheckStirringMotor = "Vérifier le moteur d'agitation";
        Err = "Erreur";
        PistonMotorFault = "Défaut du moteur à piston";
        PistonPositionFault = "Défaut de position du piston";
        PressureHighFault = "Défaut de pression élevée";
        TECfailureFault = "Défaillance TEC Défaut";
        ValveMotorFault = "Défaut du moteur de vanne";
        ValveSwitchesFault = "Défaut des interrupteurs de vanne";
        PressureReadingFault = "Défaut de lecture de pression";
        StiringMotorFault = "Défaut du moteur d'agitation";
    }
    qslUCErrors.insert(0, CheckPistonMotor);
    qslUCErrors.insert(1, CheckPistonMotor);
    qslUCErrors.insert(2, PressureLimitExceeded);
    qslUCErrors.insert(3, DeviceTempExceeded);
    qslUCErrors.insert(4, CheckHeatingElement);
    qslUCErrors.insert(5, CheckValveMotor);
    qslUCErrors.insert(6, CheckValveMotor);
    qslUCErrors.insert(7, CheckPressureSensor);
    qslUCErrors.insert(8, CheckStirringMotor);

    qslUCErrors.insert(9, Err + " 9");
    qslUCErrors.insert(10, Err + " 10");
    qslUCErrors.insert(11, Err + " 11");
    qslUCErrors.insert(12, Err + " 12");
    qslUCErrors.insert(13, Err + " 13");
    qslUCErrors.insert(14, Err + " 14");
    qslUCErrors.insert(15, Err + " 15");

    qslLogErrors.insert(0, PistonMotorFault);
    qslLogErrors.insert(1, PistonPositionFault);
    qslLogErrors.insert(2, PressureHighFault);
    qslLogErrors.insert(3, DeviceTempExceeded);
    qslLogErrors.insert(4, TECfailureFault);
    qslLogErrors.insert(5, ValveMotorFault);
    qslLogErrors.insert(6, ValveSwitchesFault);
    qslLogErrors.insert(7, PressureReadingFault);
    qslLogErrors.insert(8, StiringMotorFault);

    qslLogErrors.insert(9, Err + " 9");
    qslLogErrors.insert(10, Err + " 10");
    qslLogErrors.insert(11, Err + " 11");
    qslLogErrors.insert(12, Err + " 12");
    qslLogErrors.insert(13, Err + " 13");
    qslLogErrors.insert(14, Err + " 14");
    qslLogErrors.insert(15, Err + " 15");

    qslDateFormat.insert(0, "MM/DD/YYYY");
    qslDateFormat.insert(1, "MM/DD/YY");
    qslDateFormat.insert(2, "DD/MM/YYYY");
    qslDateFormat.insert(3, "DD/MM/YY");

    qslShowDateFormat.insert(0, "MM/dd/yyyy");
    qslShowDateFormat.insert(1, "MM/dd/yy");
    qslShowDateFormat.insert(2, "dd/MM/yyyy");
    qslShowDateFormat.insert(3, "dd/MM/yy");

    qslTimeFormat.insert(0, "12 Hour AM/PM");
    qslTimeFormat.insert(1, "24 Hours");

    qslShowTimeFormat.insert(0, "h:mm:ss AP");
    qslShowTimeFormat.insert(1, "hh:mm:ss");

    qslLanguage.insert(0, "English");
    qslLanguage.insert(1, "Spanish");
    qslLanguage.insert(2, "German");
    qslLanguage.insert(3, "French");

    qsTemperatureScaleFull.insert(0, "Celsius");
    qsTemperatureScaleFull.insert(1, "Fahrenheit");

    qslTemperatureScale.insert(0, "C");
    qslTemperatureScale.insert(1, "F");

    qslPressureScale.insert(0, "kPa");
    qslPressureScale.insert(1, "psi");
    qslPressureScale.insert(2, "hPa");
    qslPressureScale.insert(3, "ATM");

    qslPressureMultiplier.insert(0, "1");
    qslPressureMultiplier.insert(1, "0.145038");
    qslPressureMultiplier.insert(2, "10");
    qslPressureMultiplier.insert(3, "0.00986923");

    qslPressureDP.insert(0, "1");
    qslPressureDP.insert(1, "2");
    qslPressureDP.insert(2, "2");
    qslPressureDP.insert(3, "3");

    qslTemperatureDP.insert(0, "1");
    qslTemperatureDP.insert(1, "1");

    qslRinseCycles.insert(0, "1");
    qslRinseCycles.insert(1, "2");
    qslRinseCycles.insert(2, "3");
    qslRinseCycles.insert(3, "4");
    qslRinseCycles.insert(4, "5");
    qslRinseCycles.insert(5, "6");
    qslRinseCycles.insert(6, "7");
    qslRinseCycles.insert(7, "8");
    qslRinseCycles.insert(8, "9");

    qslEmulation.insert(0, "Serial");
    qslEmulation.insert(1, "USB");

    qslBaudRate.insert(0, "2400");
    qslBaudRate.insert(1, "4800");
    qslBaudRate.insert(2, "9600");
    qslBaudRate.insert(3, "19200");

    qslParity.insert(0, "None");
    qslParity.insert(1, "Odd");
    qslParity.insert(2, "Even");

    qslFlow.insert(0, "None");
    qslFlow.insert(1, "XON/XOFF");
    qslFlow.insert(2, "DTR");

    qslStopBits.insert(0, "1");
    qslStopBits.insert(1, "2");

    qslDataBits.insert(0, "7");
    qslDataBits.insert(1, "8");

    qslPageSize.insert(0, "Letter");
    qslPageSize.insert(1, "A4");

    qslReportFormat.insert(0, "Multiline");
    qslReportFormat.insert(1, "Single");

    qslMethods.insert(0, "D5191");
    qslMethods.insert(1, "D6377");
    qslMethods.insert(2, "D6378");
    qslMethods.insert(3, "D5188");
    qslMethods.insert(4, "Free 1");
    qslMethods.insert(5, "Free 2");
    qslMethods.insert(6, "Free 3");
    qslMethods.insert(7, "Free 4");

    qslFormulaD5191aConstant.insert(0, "0.965");
    qslFormulaD5191bConstant.insert(0, "0");
    qslFormulaD5191cConstant.insert(0, "3.78");

    qslFormulaD5191aConstant.insert(1, "0.956");
    qslFormulaD5191bConstant.insert(1, "0");
    qslFormulaD5191cConstant.insert(1, "2.39");

    qslFormulaD5191aConstant.insert(2, "0.972");
    qslFormulaD5191bConstant.insert(2, "0");
    qslFormulaD5191cConstant.insert(2, "4.93");

    qslFormulaD5191.insert(0, "ASTM =  0.965 x Ptot - 0.000 x Pgas – 3.78");
    qslFormulaD5191.insert(1, "EPA = 0.956 x Ptot - 0.000 x Pgas – 2.39");
    qslFormulaD5191.insert(2, "CARB = 0.972 x Ptot - 0.000 x Pgas – 4.93");

    qslFormulaD6378aConstant.insert(0, "1.0");
    qslFormulaD6378bConstant.insert(0, "1.0");
    qslFormulaD6378cConstant.insert(0, "1.005");

    qslFormulaD6378aConstant.insert(1, "1.0");
    qslFormulaD6378bConstant.insert(1, "1.0");
    qslFormulaD6378cConstant.insert(1, "0.137");

    qslFormulaD6378aConstant.insert(2, "1.0");
    qslFormulaD6378bConstant.insert(2, "1.0");
    qslFormulaD6378cConstant.insert(2, "1.575");

    qslFormulaD6378.insert(0, "ASTM =  1.000 x Ptot - 1.000 x Pgas – 1.005");
    qslFormulaD6378.insert(1, "EPA = 1.000 x Ptot - 1.000 x Pgas – 0.137");
    qslFormulaD6378.insert(2, "CARB = 1.000 x Ptot - 1.000 x Pgas – 1.575");

    qslFormulaFree1.insert(0, "Free 1 = a x Ptot – b x Pgas – c");
    qslFormulaFree2.insert(0, "Free 2 = a x Ptot – b x Pgas – c");
    qslFormulaFree3.insert(0, "Free 3 = a x Ptot – b x Pgas – c");
    qslFormulaFree4.insert(0, "Free 4 = a x Ptot – b x Pgas – c");

}

void MainWindow::changeEvent(QEvent* event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        qDebug() << "QEvent::LanguageChange";

        ui->retranslateUi(this);
    }

    QWidget::changeEvent(event);
}

bool MainWindow::eventFilter(QObject *w, QEvent *e)
{
    if(e->type() == QEvent::Wheel)
    {
        e->ignore();
        return true;
    }

    if (e->type() == QEvent::MouseButtonPress)
    {
       if(ui->listSetupMenu->isVisible())
       {
//           ui->wMenuBar->wmSetupsetSelected(true); //naveen
           if(w->objectName().contains("MainWindow"))
           {
               ui->listSetupMenu->hide();
           }
       }
//       else if(ui->wUserSetup->isVisible()){
//           ui->wMenuBar->wmSetupsetSelected(true);
//       }else if(ui->wGeneralSetup->isVisible()){
//            ui->wMenuBar->wmSetupsetSelected(true);
//       }else if(ui->wMethodSetup->isVisible()){
//            ui->wMenuBar->wmSetupsetSelected(true);
//       }else if(ui->wServiceSetup->isVisible()){
//            ui->wMenuBar->wmSetupsetSelected(true);
//       }else if(ui->wCalibrationSetup->isVisible()){
//            ui->wMenuBar->wmSetupsetSelected(true);
//       }else{
//            ui->wMenuBar->wmSetupsetSelected(false);
//       }
//       else{
//           ui->wMenuBar->wmSetupsetSelected(false); //naveen
//       }

        if(ui->wMeasuring1->isVisible())
        {
            QList<QListWidget *> alw = w->findChildren<QListWidget *>();

            if(alw.count()>0)
            {
                ui->wMeasuring1->hideLists();
            }
        }
    }

    return false;

}

int MainWindow::setLanguage()
{
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

void MainWindow::setMeasuring()
{
    ui->wMeasuring1->cgs = &ui->wGeneralSetup->general_setup;

    ui->wMeasuring1->cstdD5191 = &ui->wMethodSetup->stdD5191;
    ui->wMeasuring1->cstdD6377 = &ui->wMethodSetup->stdD6377;
    ui->wMeasuring1->cstdD6378 = &ui->wMethodSetup->stdD6378;
    ui->wMeasuring1->cstdD5188 = &ui->wMethodSetup->stdD5188;

    ui->wMeasuring1->cstdFree1 = &ui->wMethodSetup->stdFree1;
    ui->wMeasuring1->cstdFree2 = &ui->wMethodSetup->stdFree2;
    ui->wMeasuring1->cstdFree3 = &ui->wMethodSetup->stdFree3;
    ui->wMeasuring1->cstdFree4 = &ui->wMethodSetup->stdFree4;

    ui->wMeasuring1->qslD5191 = &qslFormulaD5191;
    ui->wMeasuring1->qslD6378 = &qslFormulaD6378;
    ui->wMeasuring1->qslFree1 = &qslFormulaFree1;
    ui->wMeasuring1->qslFree2 = &qslFormulaFree2;
    ui->wMeasuring1->qslFree3 = &qslFormulaFree3;
    ui->wMeasuring1->qslFree4 = &qslFormulaFree4;

    ui->wMeasuring1->qslFormulaD5191aConstant = &qslFormulaD5191aConstant;
    ui->wMeasuring1->qslFormulaD5191bConstant = &qslFormulaD5191bConstant;
    ui->wMeasuring1->qslFormulaD5191cConstant = &qslFormulaD5191cConstant;

    ui->wMeasuring1->qslFormulaD6378aConstant = &qslFormulaD6378aConstant;
    ui->wMeasuring1->qslFormulaD6378bConstant = &qslFormulaD6378bConstant;
    ui->wMeasuring1->qslFormulaD6378cConstant = &qslFormulaD6378cConstant;

    ui->wMeasuring1->qslPressureScale = &qslPressureScale;
    ui->wMeasuring1->qslTemperatureScale = &qslTemperatureScale;


    ui->wMethodSetup->qslFormulaD5191aConstant = &qslFormulaD5191aConstant;
    ui->wMethodSetup->qslFormulaD5191bConstant = &qslFormulaD5191bConstant;
    ui->wMethodSetup->qslFormulaD5191cConstant = &qslFormulaD5191cConstant;

    ui->wMethodSetup->qslFormulaD6378aConstant = &qslFormulaD6378aConstant;
    ui->wMethodSetup->qslFormulaD6378bConstant = &qslFormulaD6378bConstant;
    ui->wMethodSetup->qslFormulaD6378cConstant = &qslFormulaD6378cConstant;

    cSettings.setGeneralSetup(&ui->wGeneralSetup->general_setup);
    cSettings.setUserSetup(&ui->wUserSetup->user_setup);

    cSettings.setTemperatureCalib(&ui->wCalibrationSetup->cCalibTm);
    cSettings.setPressureCalib(&ui->wCalibrationSetup->cCalibPr);

    cSettings.qslPressureScale = &qslPressureScale;
    cSettings.qslTemperatureScale = &qslTemperatureScale;
    cSettings.qslPressureMultiplier = &qslPressureMultiplier;
    cSettings.qslPressureDP = &qslPressureDP;
    cSettings.qslTemperatureDP = &qslTemperatureDP;
    cSettings.qslShowDateFormat = &qslShowDateFormat;
    cSettings.qslShowTimeFormat = &qslShowTimeFormat;

}

void MainWindow::openSerial(QString tmp)
{
    serial->setPortName(tmp);

    if (serial->open(QIODevice::ReadWrite))
    {
        if (serial->setBaudRate(QSerialPort::Baud9600)
                && serial->setDataBits(QSerialPort::Data8)
                && serial->setParity(QSerialPort::NoParity)
                && serial->setStopBits(QSerialPort::OneStop)
                && serial->setFlowControl(QSerialPort::NoFlowControl))
        {

        }
        else
        {
            serial->close();
        }
    }

}

void MainWindow::closeSerial()
{
    if(serial->isOpen())
        serial->close();
}

void MainWindow::checkInit()
{
    if(cWaitForACK && !cACKReceived) return;
    cWaitForACK = false;

    qDebug() << "CI";

    switch(cStage)
    {
        case 1:
                //if(cACKReceived) sendPara(ui->wUserSetup->getBuzAndVol(), 2, 5);

                #ifdef Q_OS_WIN32
                    sendPara(ui->wUserSetup->getBuzAndVol(), 2, 10);
                #else
                    //sendPara(ui->wUserSetup->getBuzAndVol(), 2, 12*60);
                    sendPara(ui->wUserSetup->getBuzAndVol(), 2, 20*60);
                #endif

                break;

        case 2: //if(cACKReceived)
                cStage++;
                break;

        case 3:
                {

                    #ifdef Q_OS_WIN32
                        //cParasUpdated = true;
                        cParasUpdated = false;
                    #else
                        cParasUpdated = false;
                    #endif

                    double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                    if((cValvePosition == M_VALVE_POSITION_EXHAUST && cPistonPosition == 0) &&
                       ((ctmp >= (20 - M_INIT_TEMPERATURE_TOLERANCE ))
                       && (ctmp <= (20 + M_INIT_TEMPERATURE_TOLERANCE ))))
                    {

                        //ui->wUserSetup->sendBuzAndVol();

                        onShowMsgBox(tr("Initial"), tr("Initial test done!"));
                        cInitSuccess = true;
                        cInitDone = true;

                        qDebug() << "TMO Reset";

                        cStage = -2; //0;
                        cIdleTimeout = 0;
                        cStageTimeOut = 60*12;

                        //ui->wMeasuring1->setIdleTimer(cIdleTimeout);

                    }
                    else
                    {
                        if(!cStageTimeOut)
                        {

                            if(cValvePosition != M_VALVE_POSITION_EXHAUST)
                            {
                                cTimeOutError |= (1<<M_ERROR_VALVE_MOTOR);
                            }

                            if(cPistonPosition != 0)
                            {
                                cTimeOutError |= (1<<M_ERROR_PISTON_POSITION);
                            }

                            if((ctmp < (20 - M_INIT_TEMPERATURE_TOLERANCE))
                                || (ctmp > (20 + M_INIT_TEMPERATURE_TOLERANCE)))
                            {
                                cTimeOutError |= (1<<M_ERROR_TEMPERATURE);
                            }

                            ui->wCheckPass->hide();

                            //cStage  = 0;      //4-July-2022
                            cInitSuccess = false;
                            cInitDone = true;

                            //ui->wUserSetup->sendBuzAndVol();

                            qDebug() << "TMO Reset";
                            cStage = -1; //0;
                            cIdleTimeout = 0;
                            cStageTimeOut = 60*12;

                            //ui->wMeasuring1->setIdleTimer(cIdleTimeout);

                        }
                        else
                            cStageTimeOut--;
                    }

                }
                break;

    }

}

/*
void MainWindow::checkInit()
{
    if(cParasUpdated)
    {

#ifdef Q_OS_WIN32
       //cParasUpdated = true;
        cParasUpdated = false;
#else
        cParasUpdated = false;
#endif

        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

        if((cValvePosition == M_VALVE_POSITION_EXHAUST &&
           cPistonPosition == 0) &&
           ((ctmp >= (20 - M_INIT_TEMPERATURE_TOLERANCE ))
                                     && (ctmp <= (20 + M_INIT_TEMPERATURE_TOLERANCE ))))
        {
            ui->wUserSetup->sendBuzAndVol(); 

            onShowMsgBox(tr("Initial"), tr("Initial test done!"));
            cInitSuccess = true;
            cInitDone = true;

            qDebug() << "TMO Reset";

            cStage = -2; //0;
            cIdleTimeout = 0;
            cStageTimeOut = 60*12;

            //ui->wMeasuring1->setIdleTimer(cIdleTimeout);

        }
        else
        {
            if(!cStageTimeOut)
            {
                if(cValvePosition != M_VALVE_POSITION_EXHAUST)
                {
                    cTimeOutError |= (1<<M_ERROR_VALVE_MOTOR);
                }

                if(cPistonPosition != 0)
                {
                    cTimeOutError |= (1<<M_ERROR_PISTON_POSITION);
                }

                if((ctmp < (20 - M_INIT_TEMPERATURE_TOLERANCE))
                        || (ctmp > (20 + M_INIT_TEMPERATURE_TOLERANCE)))
                {
                    cTimeOutError |= (1<<M_ERROR_TEMPERATURE);
                }

                //cStage  = 0;      //4-July-2022
                cInitSuccess = false;
                cInitDone = true;

                ui->wUserSetup->sendBuzAndVol(); 

                qDebug() << "TMO Reset";
                cStage = -1; //0;
                cIdleTimeout = 0;
                cStageTimeOut = 60*12;

                ui->wMeasuring1->setIdleTimer(cIdleTimeout);

            }
            else cStageTimeOut--;
        }
    }
}
*/

void MainWindow::handleRinsing()
{
    switch(cStage)
    {
        case -2: {
                    cParasUpdated = false;

                    qDebug() << "TR";

                    cIdleTimeout = 0;
                    cStage = -1;

                    /* //30-July-2022

                    double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                    if((ctmp >= (20 - M_TEMPERATURE_TOLERANCE ))
                        && (ctmp <= (20 + M_TEMPERATURE_TOLERANCE)))
                    {
                            cStage = -1;
                            qDebug() << "TR -1";
                    }


                    else
                    {
                        if(!cStageTimeOut) { setError(M_ERROR_TEMPERATURE); }
                        else cStageTimeOut--;
                    }
                    */

                 }
        break;

        case -1:
                    //qDebug() << "TMO";

                    if(cIdleTimeout > M_IDLE_TIME_OUT)
                    {
                        cIdleTimeout = 0;
                        cStartTimeoutFlag = false;
                        qDebug() << "Idle 0C Send";
                        //onSendCommand();

                        sendPara(cProtocol.sendMeasuring(1, 0), 0, 0);
                        //cStage = 0;

                    }
                    else
                    {
                        //ui->wMeasuring1->setIdleTimer(cIdleTimeout);
                        cIdleTimeout++;
                    }

        break;

        case 0:
                    qDebug() << "TMO>>";

        break;

        case 2:
                {
                    cParasUpdated = false;

                    double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                    if((cValvePosition == M_VALVE_POSITION_EXHAUST) &&
                       (cPistonPosition == 0) && ((ctmp >= (20 - M_RINSING_TEMPERATURE_TOLERANCE )) && (ctmp <= (20 + M_RINSING_TEMPERATURE_TOLERANCE ))))
                    {
                        #ifdef Q_OS_WIN32
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 3, 10);
                        #else
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 3, 60);
                        #endif

			if(ui->wMeasuring1->isVisible())
                        {
                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_IN);
                            else
                            {
                                QString str = tr("Rinsing of cell: ")
                                + tr("Current Cycle:") + QString::number(cRinseCycles + 1)
                                + "/"
                                + QString::number(ui->wUserSetup->user_setup.rinse_cycle + 1);

                                ui->wMeasuring1->setStatus(str);
                            }
                        }
                    }
                    else
                    {
                        if(!cStageTimeOut)
                        {
                            if(cValvePosition != M_VALVE_POSITION_EXHAUST)
                            {
                                setError(M_ERROR_VALVE_MOTOR);
                            }

                            if(cPistonPosition != 0)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }

                            if(((ctmp < (20 - M_TEMPERATURE_TOLERANCE )) || (ctmp > (20 + M_TEMPERATURE_TOLERANCE ))))
                            {
                                setError(M_ERROR_TEMPERATURE);
                            }

                        }
                        else cStageTimeOut--;
                    }
                }

                break;

        case 3:
                {
                    cParasUpdated = false;

                    if(cValvePosition == M_VALVE_POSITION_IN)
                    {
                        sendPara(cProtocol.sendPistonPosition(250), 4, 60);

                        if(ui->wMeasuring1->isVisible())
			    if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_2_5_ML);
                    }
                    else
                    {
                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_VALVE_MOTOR);
                        }
                        else cStageTimeOut--;
                    }
                }

                break;

        case 4:
                {
                    cParasUpdated = false;

                    if((cPistonPosition <= 250+5) && (cPistonPosition >= 250-5))
                    {
                        sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST), 5, 60);

                        if(ui->wMeasuring1->isVisible())
			    if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_EXHAUST);
                    }
                    else
                    {
                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_PISTON_POSITION);
                        }
                        else cStageTimeOut--;
                    }
                }

                break;

        case 5:
                {
                    cParasUpdated = false;
                    if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                    {
                        sendPara(cProtocol.sendPistonPosition(0), 6, 60);	

                        if(ui->wMeasuring1->isVisible())
			    if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_0_ML);
                    }
                    else
                    {
                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_VALVE_MOTOR);
                        }
                        else cStageTimeOut--;
                    }
                }

                break;

        case 6:
                {
                    cParasUpdated = false;
                    if(cPistonPosition == 0)
                    {
                        cRinseCycles++;

                        if(cRinseCycles < ui->wUserSetup->user_setup.rinse_cycle + 1)
                        {
                            
			             ui->wCleaning->updateStatus(cRinseCycles + 1, ui->wUserSetup->user_setup.rinse_cycle + 1);
                            cStage = 2;
                        }
                        else
                        {
                            if(ui->wCleaning->isVisible())
                            {
                                //cStage = 0;

                                cIdleTimeout = 0;
                                qDebug() << "TMO Reset";
                                cStage = -2; //0;
                                cIdleTimeout = 0;

                                ui->wCleaning->setRunning(false); //18-Apr-2023
                                ui->wMenuBar->setSelectedMenu(M_CLEANING); //18-Apr-2023
                            }
                            
                            else
                            {
                                sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 7, 60);

                                if(ui->wMeasuring1->isVisible())
                                    if(ui->wServiceSetup->getDebug())
                                        ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_IN);
                            }
                        }
                    }
                    else
                    {
                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_PISTON_POSITION);
                        }
                        else cStageTimeOut--;
                    }
                }

                break;
    }
}

void MainWindow::writeSerial(const QByteArray &data, int len)
{
    if(serial->isOpen()) serial->write(data, len);
}

void MainWindow::readSerial(void)
{

    QByteArray data = serial->readAll();

    int count=0;

    for(count=0; count<data.length(); count++)
    {
        if(!dcount && data[count] == '#')
        {
            rdata[dcount] = '#';
            dcount++;
        }
        else if(dcount>=1 && dcount < 100)
        {

            //"#YC4096,A262144,B262144,F700,D1,H210,E1234$

            //"#YC4096,A262144,B262144,F700,D1,H210,E1234,W123$
            //"#YC4096,A262144,B262144,F700,D1,H210,E1234,Z06,W123$   //ack
            //"#YC4096,A262144,B262144,F700,D1,H210,E1234,Z21,W123$     //nack

            rdata[dcount] =  data[count];

            if(rdata[dcount] == '$')
            {

                if(rdata[1] == 'Y')
                {
                    cFrameError = false;

                    if(rdata[2] != 'C') cFrameError = true;     //4
                    if(rdata[8] != 'A') cFrameError = true;     //6
                    if(rdata[16] != 'B') cFrameError = true;    //6
                    if(rdata[24] != 'F') cFrameError = true;    //4
                    if(rdata[29] != 'D') cFrameError = true;    //1
                    if(rdata[32] != 'H') cFrameError = true;    //3
                    if(rdata[37] != 'E') cFrameError = true;    //4

                    if(rdata[43] != 'W' && rdata[43] != 'Z') cFrameError = true;
                    if(rdata[43] == 'Z' && rdata[47] != 'W') cFrameError = true;

                    if(!cFrameError)
                    {

                        int count = dcount - 4, pcount = 0;
                        unsigned char  crc = 0, crcPoly = 0x07, i;

                        while (count-- > 0)
                        {
                            crc = crc ^ rdata[pcount];

                            i = 8;

                            pcount++;

                            do
                            {
                                if (crc & 0x80) crc = crc << 1 ^ crcPoly;
                                else crc = crc << 1;

                            } while(--i);

                        }

                        rdata[7] = 0;
                        int  cVal = atoi((const char *)&rdata[3]);

                        rdata[15] = 0;
                        int  aVal = atoi((const char *)&rdata[9]);

                        rdata[23] = 0;
                        int  bVal = atoi((const char *)&rdata[17]);

                        rdata[28] = 0;
                        int  fVal = atoi((const char *)&rdata[25]);

                        rdata[31] = 0;
                        int  dVal = atoi((const char *)&rdata[30]);

                        rdata[36] = 0;
                        int  hVal = atoi((const char *)&rdata[33]);

                        rdata[42] = 0;
                        int  eVal = atoi((const char *)&rdata[38]);

                        //"#YC4096,A262144,B262144,F700,D1,H210,E1234,W123$
                        //"#YC4096,A262144,B262144,F700,D1,H210,E1234,Z06,W123$   //ack
                        //"#YC4096,A262144,B262144,F700,D1,H210,E1234,Z21,W123$     //nack

                        int zVal = 0;
                        int  crcVal = 0;

                        if(rdata[43] == 'Z')
                        {
                            rdata[46] = 0;
                            zVal = atoi((const char *)&rdata[44]);

                            rdata[51] = 0;
                            crcVal = atoi((const char *)&rdata[48]);
                        }
                        else
                        {
                            rdata[47] = 0;
                            crcVal = atoi((const char *)&rdata[44]);
                        }

                        {
                            QString str = QString::number(crc).rightJustified(3, '0')
                                  + "," + QString::number(crcVal).rightJustified(3, '0')
                                  + "," + QString::number(zVal).rightJustified(2, '0');

                            //ui->label_2->setText(str);
                        }

                        if(crc == crcVal)
                        {
                            cValvePosition = dVal;
                            cPistonPosition = fVal;
                            cRawATemperature = cVal;
                            cRawCTemperature = aVal;
                            cRawCPressure = bVal;
                            cStepperSpeed = hVal;
                            cCurrentUCError = eVal;

                            if(ui->wServiceSetup->isVisible())
                                ui->wServiceSetup->onLiveData(cValvePosition, cPistonPosition,
                                        cRawATemperature, cRawCTemperature,
                                        cRawCPressure, cStepperSpeed, cCurrentUCError);

                            else if(ui->wCalibrationSetup->isVisible())
                                ui->wCalibrationSetup->onLiveData(cValvePosition,
                                           cRawCTemperature, cRawCPressure, cCurrentUCError);

                            if(ui->wCleaning->isVisible())
                                ui->wCleaning->onLiveData(cRawCTemperature, cRawCPressure);

                            if(ui->wServiceSetup->getUSBLogEnabled())
                                ui->wServiceSetup->onLogData(cValvePosition, cPistonPosition,
                                        cRawATemperature, cRawCTemperature,
                                        cRawCPressure, cStepperSpeed, cCurrentUCError);


                            if(zVal == 6)
                            {
                                cACKReceived = true;
                                cNACKReceived = false;
                                cUACKReceived = true;
                            }

                            if(zVal == 21)
                            {
                                cACKReceived = false;
                                cNACKReceived = true;
                            }

                            cParasUpdated = true;
                            cFrameReceived = true;

                        }//crc

                    }// cFrameReceived

                }
                else if(rdata[1] == 'Z')
                {
                    if(rdata[2] == '0' && rdata[3] == '6')  //ack
                    {
                        cACKReceived = true;
                        cNACKReceived = false;
                        cUACKReceived = true;
                    }
                    else if(rdata[2] == '2' && rdata[3] == '1') //nack
                    {
                        cACKReceived = false;
                        cNACKReceived = true;
                    }
                }
                else if(rdata[1] == 'V')
                {
                    //#Vxxyyzz,<CRC>$

                    int count = dcount - 3, pcount = 0;
                    unsigned char  crc = 0, crcPoly = 0x07, i;

                    while (count-- > 0)
                    {
                        crc = crc ^ rdata[pcount];

                        i = 8;

                        pcount++;

                        do
                        {
                            if (crc & 0x80) crc = crc << 1 ^ crcPoly;
                            else crc = crc << 1;

                        } while(--i);
                    }


                    rdata[12] = 0;
                    int  cCrc = atoi((const char *)&rdata[9]);

                    rdata[8] = 0;
                    int  czz = atoi((const char *)&rdata[6]);

                    rdata[6] = 0;
                    int  cyy = atoi((const char *)&rdata[4]);

                    rdata[4] = 0;
                    int  cxx = atoi((const char *)&rdata[2]);

		    if(crc == cCrc)
                    {
                        QString str = QString::number(cxx)
                                + "." + QString::number(cyy)
                                + "." + QString::number(czz);
                        ui->wServiceSetup->setVersion(str);
                    }
                }

                dcount = 0;
            }
            else
                dcount++;
        }
        else
        {
            dcount = 0;
        }

    }
}

void MainWindow::handleErrorSerial(QSerialPort::SerialPortError error)
{

    if (error == QSerialPort::ResourceError) 
	{
        closeSerial();
    }
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    cDateTime = cSettings.getCurrentDateTime();

    ui->lblDate->setText(cDateTime.toString(cSettings.getDateFormat()));
    ui->lblTime->setText(cDateTime.toString(cSettings.getTimeFormat()));

    //QString str = "T:" + QString::number(cStage).rightJustified(2, '0');
    //ui->label_2->setText(str);

#ifdef Q_OS_WIN32
    cFrameReceived = true;  //9-July-2022 for testing
#endif

    if(cNACKReceived)
    {
        if(cNAKCount<=2)
        {
            cNAKCount++;
            onSendCommand(cPCMD);
            cNACKReceived = false;
        }
        else if(cNAKCount == 3)
        {
            cNAKCount = 4;
            showCommError(1);
        }
    }

    if(cACKReceived)
    {
        cNAKCount = 0;
        cNACKReceived = false;

        if(cUACKReceived)
        {
            cUACKReceived = false;

            if(cAccessWidget)
            {
                if(cAccessWidget->getHideAfterACK())
                {
                    //3-May-2023 onShowHome(false);
                    cAccessWidget->hideAfterACK(false);
                }
                else cAccessWidget->setWaitACKStatus(false);
                //cAccessWidget = NULL;
            }
        }
    }

    checkCommError();

    if(!cInitDone)
    {
        checkInit();
    }
    else
    {
        if(ui->wMeasuring1->isVisible())
        {
            ui->wMeasuring1->onLiveData(cRawCTemperature, cRawCPressure);

            if(cWaitForACK)
            {
                if(cACKReceived)
                {
                    cWaitForACK = false;

                    if(ui->wMeasuring1->getMethod() == M_METHOD_D5188)
                        handleD5188();
                    else if(ui->wMeasuring1->getMethod() == M_METHOD_D6377)
                            handleD6377();
                    else
                        handleOther();
                }
            }
            else
            {
                if(ui->wMeasuring1->getMethod() == M_METHOD_D5188)
                    handleD5188();
                else if(ui->wMeasuring1->getMethod() == M_METHOD_D6377)
                        handleD6377();
                else
                    handleOther();
            }

        }
        else if(ui->wCleaning->isVisible())
        {
            ui->wCleaning->onLiveData(cRawCTemperature, cRawCPressure);

            if(cWaitForACK)
            {
                if(cACKReceived)
                {
                    cWaitForACK = false;
                    handleRinsing();
                }
            }
            else handleRinsing();
        }
        else if(ui->wServiceSetup->isVisible())
        {
            if(ui->wServiceSetup->isDiagnosticMode()) //handleDiagnostic();
            {
                if(cWaitForACK)
                {
                    if(cACKReceived)
                    {
                        cWaitForACK = false;
                        handleDiagnostic();
                    }
                }
                else handleDiagnostic();
            }
        } 
        else if(ui->wMemory->isVisible() || ui->wMethodSetup->isVisible() || ui->wGeneralSetup->isVisible())
        {
	    if(cWaitForACK)
            {
                if(cACKReceived) cWaitForACK = false;
                  
            }
        }

        if(ui->wCalibrationSetup->isVisible())
        {
            ui->wCalibrationSetup->updatePressureStatus();
        }

        if(ui->wCalibrationSetup->isLinerzationVisible())
        {
            //handleCalibration();

            if(cWaitForACK)
            {
                if(cACKReceived)
                {
                    cWaitForACK = false;
                    handleCalibration();
                }
            }
            else handleCalibration();
        }

    }

    if((cCurrentUCError || cTimeOutError) && (!ui->wError->isErrorVisible())) {
        showError();
    }
    else if(cDiagErrorHandle && (!cCurrentUCError))
    {
        cDiagErrorHandle = false;
        showError();
    }
}

void MainWindow::onRunClicked(int state, bool init)
{
    int tc = cSettings.getTemperatureCount(20); 

    switch(state)
    {
        case MS_TEST_RUN:

        if(cInitSuccess)
        {
            if(init)
            {
                cAutoCycles = 0;

                if(ui->wMemory->getMemoryCount() >= M_MEMORY_COUNT)
                {
                    onGetConfirmation(M_CONFIRM_MEASURE_WITHOUT_SAVING, M_MEASURING);
                    return;
                }
            }

            ui->wMeasuring1->setStatus(STRING_MEASURING_IDLE);
            ui->wMeasuring1->setRunning(true);

            ui->wMenuBar->setRunningMenu(M_MEASURING);

            if(!ui->wServiceSetup->getContinuousRunEnabled() && ui->wGeneralSetup->general_setup.auto_measuring_cycle)  
                ui->wMeasuring1->setAutoCount(cAutoCycles + 1, ui->wGeneralSetup->general_setup.auto_measuring_cycle + 1);

            cRinseCycles = 0; 
            cStrringErrorCount = 0;

            cAccessWidget = ui->wMeasuring1;
            cAccessWidget->setWaitACKStatus(true);
            //sendPara(cProtocol.sendMeasuring(0, tc), 2, 60*12);
            sendPara(cProtocol.sendMeasuringStart(0, tc), 2, 60*12);
 
        }
        else
        {
            onShowMsgBox("Information", "Initial test failed\nMeasuring can not be started!");
        }
        break;

        case MS_TEST_STOP:

            qDebug() << "TMO Reset";

            cIdleTimeout = 0;
            cStrringErrorCount = 0;

            //ui->wMeasuring1->setIdleTimer(cIdleTimeout);

            ui->wMenuBar->setSelectedMenu(M_MEASURING);
            //onSendCommand(cProtocol.sendMeasuring(0, tc));

            cAccessWidget = ui->wMeasuring1;
            cAccessWidget->setWaitACKStatus(true);
            sendPara(cProtocol.sendMeasuring(0, tc), -2, 60*12);

        break;

        case MS_RINSING_RUN:

        if(cInitSuccess)
        {
            ui->wCleaning->setRunning(true);
            ui->wMenuBar->setRunningMenu(M_CLEANING);

            cRinseCycles = 0; 
            ui->wCleaning->updateStatus(cRinseCycles + 1, ui->wUserSetup->user_setup.rinse_cycle + 1);

            cAccessWidget = ui->wCleaning;
            cAccessWidget->setWaitACKStatus(true);

            sendPara(cProtocol.sendMeasuringStart(0, tc), 2, 60*12);

        }
        else
        {
            onShowMsgBox("Information", "Initial test failed\nRinsing can not be started!");
        }

        break;

        case MS_RINSING_STOP:

            qDebug() << "TMO Reset";
            cIdleTimeout = 0;

            //ui->wMeasuring1->setIdleTimer(cIdleTimeout);

            ui->wCleaning->setRunning(false);
            ui->wMenuBar->setSelectedMenu(M_CLEANING);

            cAccessWidget = ui->wCleaning;
            cAccessWidget->setWaitACKStatus(true);
            sendPara(cProtocol.sendMeasuring(0, tc), -2, 60*12);

        break;

        case MS_DIAGNOSTIC_RUN:

            cStage = MS_DIAGNOSTIC_STAGE;
            cStrringErrorCount = 0;
            ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Started..."));

            cAccessWidget = ui->wServiceSetup;
            cAccessWidget->setWaitACKStatus(true);
            sendPara(cProtocol.sendMeasuringStart(0, tc), 25, 60*12); 

            cDiagTestSuccess = true;
            cDiagErrorHandle = false;

        break;

        case MS_DIAGNOSTIC_STOP:

            cStage = 0;
            cStrringErrorCount = 0;
            ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Stopped..."));

            cAccessWidget = ui->wServiceSetup;
            ui->wServiceSetup->setWaitACKStatus(true);
            onSendCommand(cProtocol.sendMeasuring(0, tc));

        break;

        case MS_LINEARIZATION_RUN:

        if(cInitSuccess)
        {
            if( (ui->wCalibrationSetup->getLinerizationCount() >= 17) ||
                    ( ui->wCalibrationSetup->getTFirst() == 10 &&
                      ui->wCalibrationSetup->getTFinal() >= 95 )

                    ) 
            {

                cPrTpx1 = ui->wCalibrationSetup->getTFirst();
                cPrTpx2 = ui->wCalibrationSetup->getTFinal();

                if(cPrTpx2 > cPrTpx1)
                {

                    cPrTpx3 = cPrTpx1;

                    ui->wCalibrationSetup->setPRLRunning(1);
                    ui->wCalibrationSetup->setAutoCalibrationStatus(tr("Auto Calibration Started..."));
                    ui->wCalibrationSetup->setAutoCalibrationSubStatus("");

                    cAccessWidget = ui->wCalibrationSetup;
                    cAccessWidget->setWaitACKStatus(true);
                    sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST), //closed
                                                 24, 60);

                    ui->wCalibrationSetup->setAutoCalibrationSubStatus(tr("Moving Valve to Exhaust Position"));
                }
                else
                    onShowMsgBox("Auto Calibration", "T Final should be greater than T First!");
            }
            else
                onShowMsgBox("Auto Calibration", "Perform Full Linearization First!");


        }
        else
        {
            onShowMsgBox("Information", "Initial test failed\nCalibration can not be started!");
        }

        break;

        case MS_LINEARIZATION_STOP:

            cStage = 0;
            ui->wCalibrationSetup->setPRLRunning(3);
            ui->wCalibrationSetup->setAutoCalibrationStatus(tr("Auto Calibration Stopped..."));
            ui->wCalibrationSetup->setAutoCalibrationSubStatus(tr(""));

            cAccessWidget = ui->wCalibrationSetup;
            cAccessWidget->setWaitACKStatus(true);
            onSendCommand(cProtocol.sendMeasuring(0, tc));

        break;

    }

}

void MainWindow::onGetPass()
{
    ui->wCheckPass->Show_CheckPass(M_PWD_DEBUG, false);
}

void MainWindow::onSendCommand(QString cmd)
{

    cWaitForACK = true;
    cACKReceived = false;
    cNACKReceived = false;
    cPCMD = cmd;

    QByteArray ba = cmd.toLocal8Bit();
    char *c_str2 = ba.data();
    writeSerial(&c_str2[0], ba.length());

    qDebug() << "onSendCommand:" << cmd;

    //QString str = "S:" + QString::number(cStage).rightJustified(2, '0');
    //ui->label_2->setText(str);


}

void MainWindow::onSendCommand(QString cmd, sAccessWidget *sa)
{
    cWaitForACK = true;
    cACKReceived = false;
    cNACKReceived = false;
    cPCMD = cmd;

    QByteArray ba = cmd.toLocal8Bit();
    char *c_str2 = ba.data();
    writeSerial(&c_str2[0], ba.length());

    qDebug() << "onSendCommand SA:" << cmd;

    //ui->label_2->setText("S:" + cmd);

    //QString str = "S:" + QString::number(cStage).rightJustified(2, '0');
    //ui->label_2->setText(str);


    cAccessWidget = sa;

}

void MainWindow::sendPara(QString tmp, int stage, int timeout)
{

    //if(cACKReceived)
    {
        cWaitForACK = true;
        cACKReceived = false;
        cNACKReceived = false;
        cNAKCount = 0;

        QByteArray ba = tmp.toLocal8Bit();
        char *c_str2 = ba.data();
        writeSerial(&c_str2[0], ba.length());

        cPCMD = tmp;

        cParasUpdated = false;
        cStage = stage;
        cStageTimeOut = timeout;

        qDebug() << "sendPara:" << tmp << "cStage:" << stage << "T:" << timeout;

        //QString str = "P:" + QString::number(cStage).rightJustified(2, '0');
        //ui->label_2->setText(str);

    }

    //qDebug() << "NACK sendPara:" << cPCMD << "nPara" << tmp << "cStage:" << stage;

}



void MainWindow::startLogging()
{

}

void MainWindow::showError()
{

    if(cCurrentUCError & 0x1ff)
    {
        bool lFound=false;

        for(int i = cErrorPos; i<16; i++)
        {
            if(cCurrentUCError & ( 1<< i))
            {
                lFound = true;

        
                if(ui->wServiceSetup->isDiagnosticMode())
                {
                    //ui->wServiceSetup->addStatus(qslUCErrors.at(i) + QString::number(i));

                    ui->wServiceSetup->addStatus(qslUCErrors.at(i));

                    cDiagTestSuccess = false;
                    cDiagErrorHandle = true;

                    if(i==4) cStageTimeOut = 60;
                    //else if(i == 5 || i == 6) cStageTimeOut = 5;

                }
                else
                {
                    ui->wServiceSetup->addErrorLog(qslLogErrors.at(i), cDateTime.toString("dd/MM/yyyy hh:mm:ss"));
                    ui->wError->Show_ErrorMessage(tr("Error"), qslUCErrors.at(i));
                }

                if(i == 8)
                {
                   cStrringErrorCount++;

                   if(cStrringErrorCount >= 5)
                   {
                       cStrringErrorCount = 0;
                       if(!ui->wServiceSetup->isDiagnosticMode()) abortCurrentTask();
                   }

                }
                else
                {
                    if(!ui->wServiceSetup->isDiagnosticMode()) abortCurrentTask();
                }

                cErrorPos = i + 1;

                //qDebug() << "cStage:" << cStage
                //         << ", cACKReceived:" << cACKReceived
                //         << ", cNACKReceived:" << cNACKReceived;

                //ui->wError->SetErrorACKWait(true);

                if(!ui->wServiceSetup->isDiagnosticMode())
                {
                    cAccessWidget = ui->wError;
                    cAccessWidget->setWaitACKStatus(true);
                    onSendCommand(cProtocol.sendClearError(( 1<< i)));
                }
                else
                {
                    cAccessWidget = ui->wServiceSetup;
                    cAccessWidget->setWaitACKStatus(true);

                    if((i>=2 && i <=4) || i==7)
                    {
                        onSendCommand(cProtocol.sendAbortDiagnostic());
                        ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Failed!"));
                        ui->wServiceSetup->testDone();
                        cStage = 0;
                    }
                    else
                        onSendCommand(cProtocol.sendAckError());
                        //onSendCommand(cProtocol.sendClearError(( 1<< i)));

                }

                if(cErrorPos >=16) cErrorPos = 0;
                break;
            }
        }

        if(!lFound)
        {
            for(int i = 0; i < cErrorPos; i++)
            {
                if(cCurrentUCError & ( 1<< i))
                {
                    if(ui->wServiceSetup->isDiagnosticMode())
                    {
                        //ui->wServiceSetup->addStatus(qslUCErrors.at(i) + QString::number(i));
                        ui->wServiceSetup->addStatus(qslUCErrors.at(i));
                        cDiagTestSuccess = false;
                        cDiagErrorHandle = true;

                        if(i==4) cStageTimeOut = 60;
                        //else if(i == 5 || i == 6) cStageTimeOut = 5;

                    }
                    else
                    {
                        ui->wServiceSetup->addErrorLog(qslLogErrors.at(i), cDateTime.toString("dd/MM/yyyy hh:mm:ss"));
                        ui->wError->Show_ErrorMessage(tr("Error"), qslUCErrors.at(i));
                    }

                    if(i == 8)
                    {
                       cStrringErrorCount++;

                       if(cStrringErrorCount >= 5)
                       {
                           cStrringErrorCount = 0;
                           if(!ui->wServiceSetup->isDiagnosticMode()) abortCurrentTask();
                       }
                    }
                    else
                    {
                        if(!ui->wServiceSetup->isDiagnosticMode()) abortCurrentTask();
                    }

                    cErrorPos = i + 1;

                    //qDebug() << "cStage:" << cStage
                    //         << ", cACKReceived:" << cACKReceived
                    //         << ", cNACKReceived:" << cNACKReceived;

                    if(!ui->wServiceSetup->isDiagnosticMode())
                    {
                        cAccessWidget = ui->wError;
                        cAccessWidget->setWaitACKStatus(true);
                        onSendCommand(cProtocol.sendClearError(( 1<< i)));
                    }
                    else
                    {
                        cAccessWidget = ui->wServiceSetup;
                        cAccessWidget->setWaitACKStatus(true);

                        if((i>=2 && i <=4) || i==7)
                        {
                            onSendCommand(cProtocol.sendAbortDiagnostic());
                            ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Failed!"));
                            ui->wServiceSetup->testDone();
                            cStage = 0;
                        }
                        else
                            onSendCommand(cProtocol.sendAckError());
                            //onSendCommand(cProtocol.sendClearError(( 1<< i)));
                    }


                    if(cErrorPos >=16) cErrorPos = 0;
                    break;
                }
            }
        }

    }
    else if(cTimeOutError)
    {

        for(int i = cErrorPos; i<15; i++)
        {
            if(cTimeOutError & ( 1<< i))
            {
                QString str;

                if(!cInitSuccess) str = tr("Initial ");
                str.append(tr("TimeOut "));

                if(ui->wCalibrationSetup->isEnabled())
                    ui->wCalibrationSetup->abortCurrentProcess();

                ui->wServiceSetup->addErrorLog(str + qslLogErrors.at(i), cDateTime.toString("dd/MM/yyyy hh:mm:ss"));
                ui->wError->Show_ErrorMessage(str, qslUCErrors.at(i));

                cTimeOutError = cTimeOutError - ( 1<< i);

                cErrorPos = i + 1;
                if(cErrorPos >=15) cErrorPos = 0;
                break;
            }
        }
    }
    else
    {

/*
        qDebug() << "cStage:" << cStage
                 << ", cACKReceived:" << cACKReceived
                 << ", cNACKReceived:" << cNACKReceived;
*/

        //qDebug() << "cFrameErrorShown:" << cFrameErrorShown;

        if(!ui->wServiceSetup->isDiagnosticMode())
        {
            cAccessWidget = ui->wError;
            cAccessWidget->setWaitACKStatus(true);
        }
        else
        {
            cAccessWidget = ui->wServiceSetup;
            cAccessWidget->setWaitACKStatus(true);
        }

        onSendCommand(cProtocol.sendAckError());

        if(!ui->wServiceSetup->isDiagnosticMode()) ui->wError->hide();

        cErrorPos = 0;

        if(ui->wMeasuring1->isVisible() && (!cStrringErrorCount || cStrringErrorCount>=5))
        {
            cStrringErrorCount = 0; 

            ui->wMeasuring1->setRunning(false);
            ui->wMenuBar->setSelectedMenu(M_MEASURING);
        }

        if(ui->wCleaning->isVisible())
        {
            ui->wCleaning->setRunning(false);
            ui->wMenuBar->setSelectedMenu(M_CLEANING);
        }
    }

}

void MainWindow::abortCurrentTask()
{
    //if(ui->wCalibrationSetup->isEnabled())    //30-July-2022

    if(ui->wCalibrationSetup->isEnabled() && ui->wCalibrationSetup->isVisible())
    {
        qDebug() << "abortCurrentTask";
        //cStage = 0;
        cStage = -2; //30-July-2022
        ui->wCalibrationSetup->abortCurrentProcess();
    }
    //30-July-2022
    else cStage = -2;
}

void MainWindow::handleOther(void)
{
    if(cStage <= 6 )
    {
        handleRinsing();
    }
    else
    {

        switch(cStage)
        {

            case 7:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_IN)
                        {
                            sendPara(cProtocol.sendPistonPosition(100), 8, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_1_ML);
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_FILLING);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 8:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= 105) && (cPistonPosition >= 95))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                     9, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_CLOSE);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 9:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_CLOSED)
                        {
                            sendPara(cProtocol.sendPistonPosition(170), 10, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_1_7_ML);

                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 10:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= 170+5) && (cPistonPosition >= 170-5))
                        {
                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_FREE1: cREqTime = ui->wMethodSetup->stdFree1.tpx1;
                                                     cTmTest = ui->wMethodSetup->stdFree1.temperature;
                                break;

                                case M_METHOD_FREE2: cREqTime = ui->wMethodSetup->stdFree2.tpx1;
                                                     cTmTest = ui->wMethodSetup->stdFree2.temperature;
                                break;

                                case M_METHOD_FREE3: cREqTime = ui->wMethodSetup->stdFree3.tpx1;
                                                     cTmTest = ui->wMethodSetup->stdFree3.temperature;
                                break;

                                case M_METHOD_FREE4: cREqTime = ui->wMethodSetup->stdFree4.tpx1;
                                                     cTmTest = ui->wMethodSetup->stdFree4.temperature;
                                break;

                                default : cREqTime = 180;
                                          cTmTest = 37.80;
                                break;
                            }

                            int tc = cSettings.getTemperatureCount(cTmTest);

                            sendPara(cProtocol.sendTemperature(tc),
                                     11, cREqTime + M_EQUILIBRIUM_TIME_OUT);


                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(cTmTest));
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);

                            cEqTime = 0;
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 11:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
                        {
                            cEqTime++;

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx1= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);
                                sendPara(cProtocol.sendPistonPosition(250), 12, 60);

                                if(ui->wServiceSetup->getDebug())
                                    ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_2_5_ML);

                            }
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_FOR + QString::number(cREqTime-cEqTime) + " Sec");
                        }
                        else
                        {
                            cEqTime = 0;

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(cTmTest));
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);
                        }

                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_TEMPERATURE);
                        }
                        else cStageTimeOut--;

                    }

                    break;

            case 12:
                {
                    cParasUpdated = false;

                    if((cPistonPosition <= 250+5) && (cPistonPosition >= 250-5))
                    {
                        switch(ui->wMeasuring1->getMethod())
                        {
                            case M_METHOD_FREE1: cREqTime = ui->wMethodSetup->stdFree1.tpx2; break;
                            case M_METHOD_FREE2: cREqTime = ui->wMethodSetup->stdFree2.tpx2; break;
                            case M_METHOD_FREE3: cREqTime = ui->wMethodSetup->stdFree3.tpx2; break;
                            case M_METHOD_FREE4: cREqTime = ui->wMethodSetup->stdFree4.tpx2; break;
                            default : cREqTime = 60; break;
                        }

                        cStage = 13;
                        cStageTimeOut = cREqTime + M_EQUILIBRIUM_TIME_OUT;

                        if(ui->wServiceSetup->getDebug())
                            ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(cTmTest));
                        else
                            ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);

                        cEqTime = 0;
                    }
                    else
                    {
                        if(!cStageTimeOut)
                        {
                                setError(M_ERROR_PISTON_POSITION);
                        }
                        else cStageTimeOut--;
                    }
                }

                    break;

            case 13:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
                        {
                            cEqTime++;

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx2= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);
                                sendPara(cProtocol.sendPistonPosition(500), 14, 60);

                                if(ui->wServiceSetup->getDebug())
                                    ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_5_ML);
                            }
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_FOR + QString::number(cREqTime-cEqTime) + " Sec");
                        }
                        else
                        {
                            cEqTime = 0;

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(cTmTest));
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);
                        }

                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_TEMPERATURE);
                        }
                        else cStageTimeOut--;

                    }

                    break;

            case 14:
                    {
                        cParasUpdated = false;

                        if((cPistonPosition <= 500+5) && (cPistonPosition >= 500-5))
                        {
                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_FREE1: cREqTime = ui->wMethodSetup->stdFree1.tpx3; break;
                                case M_METHOD_FREE2: cREqTime = ui->wMethodSetup->stdFree2.tpx3; break;
                                case M_METHOD_FREE3: cREqTime = ui->wMethodSetup->stdFree3.tpx3; break;
                                case M_METHOD_FREE4: cREqTime = ui->wMethodSetup->stdFree4.tpx3; break;
                                default : cREqTime = 60; break;
                            }

                            cStage = 15;
                            cStageTimeOut = cREqTime + M_EQUILIBRIUM_TIME_OUT;
                            ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_FOR + QString::number(cREqTime) + " Sec");
                            cEqTime = 0;
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 15:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
                        {
                            cEqTime++;

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx3= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                                ui->wMeasuring1->setStatus("");

                                if(ui->wMeasuring1->getMethod() == M_METHOD_D5191)
                                    ui->wMeasuring1->showResultD5191(cPrTpx1, cPrTpx2, cPrTpx3);
                                else if(ui->wMeasuring1->getMethod() == M_METHOD_D6378)
                                    ui->wMeasuring1->showResultD6378(cPrTpx1, cPrTpx2, cPrTpx3);
                                else
                                    ui->wMeasuring1->showResultFree(cPrTpx1, cPrTpx2, cPrTpx3);

                                ui->wServiceSetup->incrementCount();

                                sendPara( cProtocol.sendTemperature(cSettings.getTemperatureCount(20)),
                                          16, 60*12);

                                if(ui->wServiceSetup->getDebug())
                                    ui->wMeasuring1->setStatus(STRING_MEASURING_COOLING + cSettings.getTemperature(20));
                                else
                                    ui->wMeasuring1->setStatus(STRING_MEASURING_COOL);

                            }
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_FOR + QString::number(cREqTime-cEqTime) + " Sec");
                        }
                        else
                        {
                            cEqTime = 0;

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(cTmTest));
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);
                        }

                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_TEMPERATURE);
                        }
                        else cStageTimeOut--;

                    }

                    break;

            case 16:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if(((ctmp >= (20 - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (20 + M_TEMPERATURE_TOLERANCE))) && cStageTimeOut <=700)
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST),
                                     17, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_EXHAUST);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                    setError(M_ERROR_TEMPERATURE);
                            }
                            else cStageTimeOut--;

                            if(cStageTimeOut == 710)
                            {
                                switch(ui->wMeasuring1->getMethod())
                                {
                                    case M_METHOD_D5191:
                                        if(ui->wMethodSetup->stdD5191.alarm_enabled)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_D6378:
                                        if(ui->wMethodSetup->stdD6378.alarm_enabled)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE1:
                                        if(ui->wMethodSetup->stdFree1.alarm_enabled)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE2:
                                        if(ui->wMethodSetup->stdFree2.alarm_enabled)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE3:
                                        if(ui->wMethodSetup->stdFree3.alarm_enabled)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE4:
                                        if(ui->wMethodSetup->stdFree4.alarm_enabled)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;
                                }
                            }

                        }
                    }

                    break;

            case 17:
                    {
                        cParasUpdated = false;

                        if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                        {
                            sendPara(cProtocol.sendPistonPosition(0), 18, 60);
                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_0_ML);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 18:
                    {
                        cParasUpdated = false;

                        if(cPistonPosition == 0)
                        {
                            //cStage = 0;
                            qDebug() << "TMO Reset";
                            cStage = -1; //0;
                            cIdleTimeout = 0;

                            if(ui->wServiceSetup->getContinuousRunEnabled())
                            {
                                ui->wMeasuring1->hideResult();
                                onRunClicked(MS_TEST_RUN, false);
                            }
                            else
                            {
                                cAutoCycles++;

                                if(cAutoCycles < ui->wGeneralSetup->general_setup.auto_measuring_cycle + 1)
                                {
                                    ui->wMeasuring1->setAutoCount(cAutoCycles + 1, ui->wGeneralSetup->general_setup.auto_measuring_cycle + 1);

                                    ui->wMeasuring1->hideResult();
                                    onRunClicked(MS_TEST_RUN, false);
                                }
                                else
                                    ui->wMeasuring1->setStatus("");
                            }
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;
        }
    }
}

void MainWindow::handleDiagnostic()
{

    switch(cStage)
    {
        case 25:
        {
            cParasUpdated = false;

            //cDiagTestSuccess = true;
            //cDiagErrorHandle = false;

            double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

            //QString str = QString::number(ctmp);
            //ui->wServiceSetup->addStatus(str);

            if(cDiagTestSuccess && (cValvePosition == M_VALVE_POSITION_EXHAUST) &&
               (cPistonPosition == 0) && ((ctmp >= (20 - M_TEMPERATURE_TOLERANCE )) && (ctmp <= (20 + M_TEMPERATURE_TOLERANCE ))))
            {
                ui->wServiceSetup->addStatus(tr("Valve Exhaust OK!"));
                ui->wServiceSetup->addStatus(tr("Piston Zero OK!"));
                ui->wServiceSetup->addStatus(tr("Temperature OK!"));

                ui->wServiceSetup->addStatus(tr("Pressure @20C:")
                      + cSettings.getPressureLive(cRawCTemperature, cRawCPressure));

                cPrTpx1 = cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                sendPara(cProtocol.sendPistonPosition(500), 26, 60);

            }
            else if((!cDiagTestSuccess) && (ctmp >= (20 - M_TEMPERATURE_TOLERANCE )) && (ctmp <= (20 + M_TEMPERATURE_TOLERANCE )))
            {

                if(cValvePosition == M_VALVE_POSITION_EXHAUST) ui->wServiceSetup->addStatus(tr("Valve Exhaust OK!"));
                if(cPistonPosition == 0) ui->wServiceSetup->addStatus(tr("Piston Zero OK!"));

                ui->wServiceSetup->addStatus(tr("Temperature OK!"));

                ui->wServiceSetup->addStatus(tr("Pressure @20C:")
                      + cSettings.getPressureLive(cRawCTemperature, cRawCPressure));

                cPrTpx1 = cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                sendPara(cProtocol.sendPistonPosition(500), 26, 60);

            }
            else
            //{
                if(!cStageTimeOut)
                {
                    if(cValvePosition != M_VALVE_POSITION_EXHAUST)
                    {
                        ui->wServiceSetup->addStatus(tr("Valve Motor Error!"));
                        cDiagTestSuccess = false;
                    }
                    else if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                    {
                        ui->wServiceSetup->addStatus(tr("Valve Exhaust OK!"));
                    }

                    if(cPistonPosition != 0)
                    {
                        ui->wServiceSetup->addStatus(tr("Piston Motor Error!"));
                        cDiagTestSuccess = false;
                    }
                    else if(cPistonPosition == 0)
                    {
                        ui->wServiceSetup->addStatus(tr("Piston Zero OK!"));
                    }


                    /*
                    if(((ctmp < (20 - M_TEMPERATURE_TOLERANCE )) || (ctmp > (20 + M_TEMPERATURE_TOLERANCE ))))
                    {
                        ui->wServiceSetup->addStatus(tr("Temperature Error!"));
                        cDiagTestSuccess = false;
                        ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Failed!"));
                        ui->wServiceSetup->testDone();

                        int tc = cSettings.getTemperatureCount(20);
                        onSendCommand(cProtocol.sendMeasuring(0, tc));

                        cStage = 0;

                    } else */

                    if((ctmp >= (20 - M_TEMPERATURE_TOLERANCE )) && (ctmp <= (20 + M_TEMPERATURE_TOLERANCE )))
                    {
                        ui->wServiceSetup->addStatus(tr("Temperature OK!"));

                        ui->wServiceSetup->addStatus(tr("Pressure @20C:")
                              + cSettings.getPressureLive(cRawCTemperature, cRawCPressure));

                        cPrTpx1 = cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                        sendPara(cProtocol.sendPistonPosition(500), 26, 60);

                    }
                    else
                    {
                        ui->wServiceSetup->addStatus(tr("Temperature Error!"));

                        cDiagTestSuccess = false;
                        ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Failed!"));
                        ui->wServiceSetup->testDone();

                        int tc = cSettings.getTemperatureCount(20);
                        onSendCommand(cProtocol.sendMeasuring(0, tc));

                        cStage = 0;

                    }
                }
                else cStageTimeOut--;
            //}
        }

        break;

        case 26:  

                cParasUpdated = false;

                if((cPistonPosition <= 500+M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= 500-M_PISTON_POSITION_TOLERANCE))
                {
                    ui->wServiceSetup->addStatus(tr("Piston 5ml OK!"));
                    sendPara(cProtocol.sendPistonPosition(0), 27, 60);
                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        ui->wServiceSetup->addStatus(tr("Piston Motor Error!"));
                        cDiagTestSuccess = false;
                        sendPara(cProtocol.sendPistonPosition(0), 27, 60);
                    }
                    else cStageTimeOut--;
                }

        break;

        case 27:

                cParasUpdated = false;

                if(cPistonPosition == 0 && cStageTimeOut < 5)
                {
                    ui->wServiceSetup->addStatus(tr("Piston 0ml OK!"));
                    sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                             28, 60);
                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        ui->wServiceSetup->addStatus(tr("Piston Motor Error!"));
                        cDiagTestSuccess = false;
                        sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                 28, 60);

                    }
                    else cStageTimeOut--;
                }

        break;

        case 28:

                cParasUpdated = false;

                if(cValvePosition == M_VALVE_POSITION_CLOSED)
                {
                    ui->wServiceSetup->addStatus(tr("Valve Closed OK!"));

                    sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN),
                             29, 60);
                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        ui->wServiceSetup->addStatus(tr("Valve Motor Error!"));
                        cDiagTestSuccess = false;

                        sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN),
                                 29, 60);
                    }
                    else cStageTimeOut--;
                }

        break;

        case 29:

                cParasUpdated = false;

                if(cValvePosition == M_VALVE_POSITION_IN)
                {
                    ui->wServiceSetup->addStatus(tr("Valve In OK!"));
                    sendPara(cProtocol.sendShakerSpeed(1, 60), 30, 35);
                    cStrringErrorCount = 0;
                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        ui->wServiceSetup->addStatus(tr("Valve Motor Error!"));
                        cDiagTestSuccess = false;
                        sendPara(cProtocol.sendShakerSpeed(1, 60), 30, 35);
                        cStrringErrorCount = 0;
                    }
                    else cStageTimeOut--;
                }

        break;

        case 30:

                cParasUpdated = false;
                if(!cStageTimeOut)
                {
                    cStage = 31;
                    cStageTimeOut = 25;
                }
                else cStageTimeOut--;

        break;

        case 31:

                cParasUpdated = false;

                if(cStepperSpeed == 60)
                {
                    ui->wServiceSetup->addStatus(tr("Shaker Motor 60rpm OK!"));
                    sendPara( cProtocol.sendShakerSpeed(0, 0),
                              32, 60);
                    cStrringErrorCount = 0;
                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        ui->wServiceSetup->addStatus(tr("Shaker Motor Error!"));
                        cDiagTestSuccess = false;
                        sendPara( cProtocol.sendShakerSpeed(0, 0),
                                  32, 60);
                        cStrringErrorCount = 0;
                    }
                    else cStageTimeOut--;
                }

        break;

        case 32:

                cParasUpdated = false;

                if(cStepperSpeed == 0)
                {
                    int tc = cSettings.getTemperatureCount(30);

                    ui->wServiceSetup->addStatus(tr("Shaker Motor Stopped OK!"));
                    sendPara( cProtocol.sendTemperature(tc),
                              33, 120+120); 

                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        int tc = cSettings.getTemperatureCount(30);
                        ui->wServiceSetup->addStatus(tr("Shaker Motor Error!"));
                        cDiagTestSuccess = false;
                        sendPara( cProtocol.sendTemperature(tc),
                                  33, 120+120);  
                    }
                    else cStageTimeOut--;
                }

        break;

        case 33:
                cParasUpdated = false;

                double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                if( ( ctmp >= (30 - M_TEMPERATURE_TOLERANCE ))
                    && (ctmp <= (30 + M_TEMPERATURE_TOLERANCE )))
                {
                    ui->wServiceSetup->addStatus(tr("Temperature 30C OK!"));

                    ui->wServiceSetup->addStatus(tr("Pressure @30C:")
                          + cSettings.getPressureLive(cRawCTemperature, cRawCPressure));

                    cPrTpx2 = cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                    if(cPrTpx1 != cPrTpx2)
                    {
                        ui->wServiceSetup->addStatus(tr("Pressure Test Successful"));
                    }
                    else
                        cDiagTestSuccess = false;

                    if(cDiagTestSuccess)
                        ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Successsfully Completed!"));
                    else
                        ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Failed!"));

                    ui->wServiceSetup->testDone();

		    int tc = cSettings.getTemperatureCount(20); 
		    onSendCommand(cProtocol.sendMeasuring(0, tc));

                    cStage = 0;

                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        ui->wServiceSetup->addStatus(tr("Temperature Error!"));
                        cDiagTestSuccess = false;
                        ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Failed!"));
                        ui->wServiceSetup->testDone();

			int tc = cSettings.getTemperatureCount(20); 
			onSendCommand(cProtocol.sendMeasuring(0, tc));

                        cStage = 0;
                    }
                    else cStageTimeOut--;
                }

        break;

    }

}

void MainWindow::handleCalibration()
{
    switch(cStage)
    {
        case 24:

               cParasUpdated = false;

               if((cValvePosition == M_VALVE_POSITION_EXHAUST) &&  
                  (cPistonPosition == 0))
               {
                   int tc = cSettings.getTemperatureCount(cPrTpx3);
                   sendPara(cProtocol.sendTemperature(tc), 25, 300); 
                   ui->wCalibrationSetup->setAutoCalibrationSubStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperatureCS(cPrTpx3));
               }
               else
               {
                   if(!cStageTimeOut)
                   {
                       if(cValvePosition != M_VALVE_POSITION_EXHAUST)
                       {
                           ui->wCalibrationSetup->setAutoCalibrationStatus(tr("Auto Calibration Stopped..."));
                           ui->wCalibrationSetup->setAutoCalibrationSubStatus(tr("Valve Motor Error!"));
                           ui->wCalibrationSetup->setPRLRunning(2); 
                           cStage = 0;
                       }

                       if(cPistonPosition != 0)
                       {
                           ui->wCalibrationSetup->setAutoCalibrationStatus(tr("Auto Calibration Stopped..."));
                           ui->wCalibrationSetup->setAutoCalibrationSubStatus(tr("Piston Motor Error!"));
                           ui->wCalibrationSetup->setPRLRunning(2); 
                           cStage = 0;
                       }
                   }
                   else cStageTimeOut--;
               }
        break;

        case 25:
        {
            cParasUpdated = false;

            double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

            if((ctmp >= (cPrTpx3 - M_TEMPERATURE_TOLERANCE)) &&
               (ctmp <= (cPrTpx3 + M_TEMPERATURE_TOLERANCE)))
            {
                sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST),
                                             26, 60);
                ui->wCalibrationSetup->setAutoCalibrationSubStatus(STRING_MEASURING_MOVING_VALVE_EXHAUST);
            }
            else
            {
                if(!cStageTimeOut)
                {
                    sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST),
                                                 26, 60);
                    ui->wCalibrationSetup->setAutoCalibrationSubStatus(STRING_MEASURING_MOVING_VALVE_EXHAUST);
                }
                else cStageTimeOut--;
            }
        }

        break;

        case 26:

                cParasUpdated = false;

                if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                {
                    cStage = 27;
                    cStageTimeOut = 180;
                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        ui->wCalibrationSetup->setAutoCalibrationStatus(tr("Auto Calibration Stopped..."));
                        ui->wCalibrationSetup->setAutoCalibrationSubStatus(tr("Valve Motor Error!"));
                        ui->wCalibrationSetup->setPRLRunning(2); 
                        cStage = 0;
                    }
                    else cStageTimeOut--;
                }

        break;

        case 27:
                cParasUpdated = false;

                if(!cStageTimeOut)
                {
                    ui->wCalibrationSetup->setZero(cRawCPressure, cPrTpx3);
                    sendPara(cProtocol.sendValvePosition(
                                 M_VALVE_POSITION_IN),
                                                 28, 60);
                    ui->wCalibrationSetup->setAutoCalibrationSubStatus(STRING_MEASURING_MOVING_VALVE_IN);

                }
                else cStageTimeOut--;
        break;

        case 28:
                cParasUpdated = false;

                if(cValvePosition == M_VALVE_POSITION_IN)
                {
                    cStage = 29;
                    cStageTimeOut = 30;
                }
                else
                {
                    if(!cStageTimeOut)
                    {
                        ui->wCalibrationSetup->setAutoCalibrationStatus(tr("Auto Calibration Stopped..."));
                        ui->wCalibrationSetup->setAutoCalibrationSubStatus(
                                    tr("Valve Motor Error!"));
                        ui->wCalibrationSetup->setPRLRunning(2); 
                        cStage = 0;
                    }
                    else cStageTimeOut--;
                }
        break;

        case 29:
                cParasUpdated = false;
                if(!cStageTimeOut)
                {
                    ui->wCalibrationSetup->setAmbient(cRawCPressure, cPrTpx3);

                    if(cPrTpx3 < cPrTpx2)
                    {
                        cPrTpx3 = cPrTpx3 + 5;

                        sendPara(cProtocol.sendValvePosition(
                                     M_VALVE_POSITION_EXHAUST), 
                                                     24, 60);

                        ui->wCalibrationSetup->setAutoCalibrationSubStatus(STRING_MEASURING_MOVING_VALVE_EXHAUST);

                    }
                    else
                    {
                        int tc = cSettings.getTemperatureCount(20);
                        onSendCommand(cProtocol.sendMeasuring(0, tc));

                        ui->wCalibrationSetup->setAutoCalibrationStatus(
                                    tr("Auto Calibration Done..."));

                        ui->wCalibrationSetup->setAutoCalibrationSubStatus("");

                        ui->wCalibrationSetup->setPRLRunning(0); //done
                        cStage = 0;
                    }
                }
                else cStageTimeOut--;
        break;

    }
}

void MainWindow::setError(int tmp)
{
    cTimeOutError |= (1<< tmp);

    cStage = -2; //0; //6-July-2022
    cIdleTimeout = 0;
    
    ui->wMeasuring1->setStatus("");

    int tc = cSettings.getTemperatureCount(20);
    //onSendCommand(cProtocol.sendMeasuring(0, tc));

    qDebug() << "ERROR";

    cACKReceived = true;
    cNACKReceived = false;

    sendPara(cProtocol.sendMeasuring(0, tc), -2, 60*12);

}

void MainWindow::checkCommError()
{
    if(cWaitForACK && !cACKReceived)
    {
        if(cFrameTimeOut > M_COMMUNICATION_TIME_OUT)
        {
            showCommError(2);
        }
        else
            cFrameTimeOut++;
    }
    else if(!cFrameReceived)
    {
        if(cFrameTimeOut > M_COMMUNICATION_TIME_OUT)
        {
            showCommError(3);
        }
        else
            cFrameTimeOut++;
    }
    else
    {
        cFrameReceived = false;
        cFrameTimeOut = 0;
        //sn cFrameErrorShown = false; //22-July-2022
    }
}

void MainWindow::showCommError(int tmp)
{
    if(!cFrameErrorShown) //sn 8-July-2022 && (!ui->wError->isVisible()))
    {
        if(cAccessWidget)
        {
            if(cAccessWidget->getHideAfterACK())
            {
                //3-May-2023 onShowHome(false);
                cAccessWidget->hideAfterACK(false);
            }
            else cAccessWidget->setWaitACKStatus(false);

            //cAccessWidget = NULL;
        }

        QString CommunicationError = (setLanguage()==0)?"Communication Error":(setLanguage()==1)?"Error de comunicación":(setLanguage()==2)?"Kommunikationsfehler":"Erreur de communication";
        QString str = CommunicationError + " (" + QString::number(tmp) + ")!";

        QString Err = (setLanguage()==0)?"Error":(setLanguage()==1)?"Error":(setLanguage()==2)?"Fehler":"Erreur";
        ui->wError->Show_ErrorMessage(Err, str);

        cStage = 0;
        cFrameErrorShown = true;
        cWaitForACK = false;

        if(!cInitDone)
        {
            cInitSuccess = false;
            cInitDone = true;

            ui->wCheckPass->hide();

            qDebug() << "TMO Reset";
            cStage = -1; //0;
            cIdleTimeout = 0;
            cStageTimeOut = 60*12;

            //ui->wMeasuring1->setIdleTimer(cIdleTimeout);

        }
        else if(ui->wMeasuring1->isVisible())
        {
            ui->wMeasuring1->setRunning(false);
            ui->wMenuBar->setSelectedMenu(M_MEASURING);
        }
        else if(ui->wCleaning->isVisible())
        {
            ui->wCleaning->setRunning(false);
            ui->wMenuBar->setSelectedMenu(M_CLEANING);
        }
        else if(ui->wCalibrationSetup->isVisible())
        {
            ui->wCalibrationSetup->abortCurrentProcess();
        }
        else if(ui->wServiceSetup->isVisible() && ui->wServiceSetup->isDiagnosticMode())
        {
            cDiagTestSuccess = false;
            ui->wServiceSetup->addStatus(tr("Communication Error!"));
            ui->wServiceSetup->addStatus(tr("Diagnostic Cycle Failed!"));
            ui->wServiceSetup->testDone();
        }
    }
}

void MainWindow::handleD5188(void)
{

    if( cStage <= 6 )
    {
        handleRinsing();
    }
    else
    {
        switch(cStage)
        {
            case 7:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_IN)
                        {
                            sendPara(cProtocol.sendPistonPosition(25), 8, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_0_25_ML);
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_FILLING);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                  setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 8:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= 25+5) && (cPistonPosition >= 25-5))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                     9, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_CLOSE);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 9:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_CLOSED)
                        {
                            sendPara(cProtocol.sendPistonPosition(525), 10, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_5_25_ML);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                 setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 10:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= 525+5) && (cPistonPosition >= 525-5))
                        {
                            sendPara(cProtocol.sendShakerSpeed(1, ui->wMethodSetup->stdD5188.shaker_speed), 11, 60);
                            cStrringErrorCount = 0;
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 11:
                {
                    cParasUpdated = false;

                    if(1)
                    {
                        //NNNNN

                        cPrCount = cSettings.getPressureCount(101.3);
                        //cPrTpx1 = cSettings.getTemperatureCelsius(cRawCTemperature);

                        sendPara(cProtocol.sendPressure(cPrCount), 12, 60*30);

                        if(ui->wServiceSetup->getDebug())
                            ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_PRESSURE_STABILIZE + cSettings.getPressure(101.3));
                        else
                            ui->wMeasuring1->setStatus(STRING_MEASURING_PRESSURE_STABILIZING);


                        cREqTime = 0;
                        cEqTime = 0;
                    }
                    else
                    {
                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_SHAKER_MOTOR);
                        }
                        else cStageTimeOut--;
                    }
                }

                break;

            case 12:
                {
                    cParasUpdated = false;

                    double dtpr1 = cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                    if((cRawCPressure >= cPrCount-50) && (cRawCPressure <= cPrCount+50))
                    {
                        if(dtpr1 < (101.3 - 0.3))
                        {
                            cPrCount = cRawCPressure+50;
                            onSendCommand(cProtocol.sendPressure(cPrCount));
                            cREqTime = 0;
                            cEqTime = 0;
                        }
                        else if(dtpr1 > (101.3 + 0.3))
                        {
                            cPrCount = cRawCPressure-50;
                            onSendCommand(cProtocol.sendPressure(cPrCount));
                            cREqTime = 0;
                            cEqTime = 0;
                        }
                    }
                    else
                    {
                        cREqTime = 0;
                        cEqTime = 0;
                    }

                    cEqTime++;

                    if(cEqTime >= 60)
                    {
                        cEqTime = 0;

                        if( (dtpr1 >= (101.3 - 0.3 )) && (dtpr1 <= (101.3 + 0.3)))
                        {
                            cREqTime++;

                            if(cREqTime >=3)
                            {
                                ui->wMeasuring1->setStatus("");

                                ui->wMeasuring1->showResultD5188(cSettings.getTemperatureCelsius(cRawCTemperature));
                                ui->wServiceSetup->incrementCount();
                                sendPara(cProtocol.sendShakerSpeed(0, 0), 13, 60);
                                cStrringErrorCount = 0;
                            }

                        }
                        else
                        {
                            cREqTime = 0;
                        }
                    }

                    if(!cStageTimeOut)
                    {
                        setError(M_ERROR_PRESSURE_SENSOR);
                    }
                    else cStageTimeOut--;

                }

                break;

            case 13:
                    {
                        cParasUpdated = false;

                        if((cStepperSpeed == 0) && (cStageTimeOut <=56))
                        {
                            sendPara( cProtocol.sendTemperature(cSettings.getTemperatureCount(20)),
                                      14, 60*18); //180+300);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_COOLING + cSettings.getTemperature(20));
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_COOL);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_SHAKER_MOTOR);
                            }
                            else cStageTimeOut--;

                            if(ui->wMethodSetup->stdD5188.alarm_enabled && cStageTimeOut == 58)
                                onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                        }
                    }

                    break;

            case 14:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if((ctmp >= (20 - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (20 + M_TEMPERATURE_TOLERANCE )))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST),
                                     15, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_EXHAUST);

                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_TEMPERATURE);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 15:
                    {
                        cParasUpdated = false;

                        if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                        {
                            sendPara(cProtocol.sendPistonPosition(0), 16, 60);
                            ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_0_ML);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 16:
                    {
                        cParasUpdated = false;

                        if(cPistonPosition == 0)
                        {
                            //cStage = 0;

                            qDebug() << "TMO Reset";
                            cStage = -1; //0;
                            cIdleTimeout = 0;

                            if(ui->wServiceSetup->getContinuousRunEnabled())
                            {
                                ui->wMeasuring1->hideResult();
                                onRunClicked(MS_TEST_RUN, false);
                            }
                            else
                            {
                                cAutoCycles++;

                                if(cAutoCycles < ui->wGeneralSetup->general_setup.auto_measuring_cycle + 1)
                                {
                                    ui->wMeasuring1->setAutoCount(cAutoCycles + 1, ui->wGeneralSetup->general_setup.auto_measuring_cycle + 1);
                                    ui->wMeasuring1->hideResult();
                                    onRunClicked(MS_TEST_RUN, false);
                                }
                                else
                                    ui->wMeasuring1->setStatus("");
                            }
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;
        }
    }
}

void MainWindow::handleD6377(void)
{

    if( cStage <= 6 )
    {
        handleRinsing();
    }
    else
    {
        switch(cStage)
        {
            case 7:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_IN)
                        {
                            sendPara(cProtocol.sendPistonPosition(100), 8, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_1_ML);
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_FILLING);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 8:
                    {
                        cParasUpdated = false;

                        if((cPistonPosition <= 100+M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= 100-M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                     9, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_CLOSE);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 9:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_CLOSED)
                        {
                            int vl = (ui->wMethodSetup->stdD6377.vl_ratio * 100) + 100;
                            sendPara(cProtocol.sendPistonPosition(vl), 10, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON + QString::number(vl/100, 'f', 2) + " ml");

                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 10:
                    {
                        cParasUpdated = false;

                        int cvl = (ui->wMethodSetup->stdD6377.vl_ratio * 100) + 100;

                        if((cPistonPosition <= cvl + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cvl - M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendShakerSpeed(1, ui->wMethodSetup->stdD6377.shaker_speed), 11, 60);
                            cStrringErrorCount = 0;
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 11:
                    {
                        cParasUpdated = false;

                        if(1)
                        {
                            cREqTime = ui->wMethodSetup->stdD6377.time;

                            int tc = cSettings.getTemperatureCount(37.8);

                            sendPara(cProtocol.sendTemperature(tc),
                                     12, cREqTime + M_EQUILIBRIUM_TIME_OUT);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(37.8));
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);

                            cEqTime = 0;
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_SHAKER_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 12:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( (ctmp >= (37.8 - M_TEMPERATURE_TOLERANCE))
                            && (ctmp <= (37.8 + M_TEMPERATURE_TOLERANCE)))
                        {
                            cEqTime++;

                            if(cEqTime >= cREqTime)
                            {
                                cStage = 13;
                                cEqTime = 0;
                                cREqTime = 0;
                                cStageTimeOut = cREqTime + M_EQUILIBRIUM_TIME_OUT;

                            }
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_FOR + QString::number(cREqTime-cEqTime) + " Sec");
                        }
                        else
                        {
                            cEqTime = 0;

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(37.8));
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);
                        }

                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_TEMPERATURE);
                        }
                        else cStageTimeOut--;

                    }

                    break;

            case 13:
                    {
                        cParasUpdated = false;

                        cEqTime++;

                        if(cEqTime >=60)
                        {
                            cEqTime = 0;

                            ui->wMeasuring1->setStatus("");

                            ui->wMeasuring1->showResultD6377(cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure));
                            ui->wServiceSetup->incrementCount();

                            sendPara(cProtocol.sendShakerSpeed( 0, 0), 14, 60);
                            cStrringErrorCount = 0;
                        }
                        else
                            ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_FOR + QString::number(60-cEqTime) + " Sec");

                        if(!cStageTimeOut)
                        {
                            setError(M_ERROR_TEMPERATURE);
                        }
                        else cStageTimeOut--;

                    }

                    break;

            case 14:
                    {
                        cParasUpdated = false;

                        if((cStepperSpeed == 0) && (cStageTimeOut <=56))
                        {

                           sendPara( cProtocol.sendTemperature(cSettings.getTemperatureCount(20)),
                                     15, 60*12); //180+180);

                           if(ui->wServiceSetup->getDebug())
                               ui->wMeasuring1->setStatus(STRING_MEASURING_COOLING + cSettings.getTemperature(20));
                           else
                               ui->wMeasuring1->setStatus(STRING_MEASURING_COOL);

                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_SHAKER_MOTOR);
                            }
                            else cStageTimeOut--;

                            if(ui->wMethodSetup->stdD6377.alarm_enabled && cStageTimeOut == 58)
                                onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                        }
                    }

                    break;

            case 15:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if((ctmp >= (20 - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (20 + M_TEMPERATURE_TOLERANCE )))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST),
                                     16, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_VALVE_EXHAUST);

                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_TEMPERATURE);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 16:
                    {
                        cParasUpdated = false;

                        if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                        {
                            sendPara(cProtocol.sendPistonPosition(0), 17, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_0_ML);
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_VALVE_MOTOR);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;

            case 17:
                    {
                        cParasUpdated = false;

                        if(cPistonPosition == 0)
                        {
                            //cStage = 0;

                            qDebug() << "TMO Reset";
                            cStage = -1; //0;
                            cIdleTimeout = 0;

                            if(ui->wServiceSetup->getContinuousRunEnabled())
                            {
                                ui->wMeasuring1->hideResult();
                                onRunClicked(MS_TEST_RUN, false);
                            }
                            else
                            {
                                cAutoCycles++;

                                if(cAutoCycles < ui->wGeneralSetup->general_setup.auto_measuring_cycle + 1)
                                {
                                    ui->wMeasuring1->setAutoCount(cAutoCycles + 1, ui->wGeneralSetup->general_setup.auto_measuring_cycle + 1);
                                    ui->wMeasuring1->hideResult();
                                    onRunClicked(MS_TEST_RUN, false);
                                }
                                else
                                    ui->wMeasuring1->setStatus("");
                            }
                        }
                        else
                        {
                            if(!cStageTimeOut)
                            {
                                setError(M_ERROR_PISTON_POSITION);
                            }
                            else cStageTimeOut--;
                        }

                    }

                    break;
        }
    }
}

bool MainWindow::onSaveResult(double p_tot, double p_gas, double p_abs,
                              QString method, QString formula,
                              double aconst, double bconst, double cconst,
                              double result,
                              double ttime, double vlratio,
                              double para_measured)
{

    QString noperator = ui->wMeasuring1->getOperator();
    QString sampleID = ui->wMeasuring1->getSampleId();

    cTest->sel = 0;
    cTest->noperator = noperator;
    cTest->sample_id = sampleID;
    cTest->datetime = cDateTime.toString(STORAGE_DATETIME_FORMAT);
    cTest->p_tot = p_tot;
    cTest->p_gas = p_gas;
    cTest->p_abs = p_abs;
    cTest->method = method;
    cTest->formula = formula;
    cTest->aconst = aconst;
    cTest->bconst = bconst;
    cTest->cconst = cconst;
    cTest->ttime = ttime;
    cTest->vlratio = vlratio;
    cTest->result = result;
    cTest->para_measured = para_measured;

    if(ui->wMemory->getMemoryCount() < M_MEMORY_COUNT)
    {


        if(ui->wMemory->saveResult( noperator, sampleID,
                                 cDateTime.toString(STORAGE_DATETIME_FORMAT),
                                 p_tot, p_gas, p_abs,
                                 method, formula,
                                 aconst, bconst, cconst,
                                 result,
                                 ttime,
                                 vlratio,
                                 para_measured))
        {
            if(ui->wUserSetup->user_setup.auto_print) ui->wMemory->printResult(cTest);
        }

    }
    else
    {
       ui->wCheckPass->Show_MessageWithAck("Measuring!", "Test Results not saved!");
    }




    return true;
}

void MainWindow::onMenuClicked(int menu)
{

   //18-Apr-2023 if(!ui->wMeasuring1->isVisible() && menu != M_MEASURING) return;
    if(ui->wCheckPass->isVisible() || ui->wError->isVisible()) return;

    switch (cMenu) {

        case M_MEASURING:
            if(ui->wMemory->isVisible()) ui->wMemory->hide();
        break;

        case M_CLEANING:
            if(ui->wMemory->isVisible()) ui->wMemory->hide();
        break;

        case M_MEMORY:
            if(ui->wMemory->isVisible() && !ui->wMemory->isSwitchEnabled(menu)) return;
        break;

        case M_SETUP:

            if(ui->wMemory->isVisible()) ui->wMemory->hide();

            if(ui->wUserSetup->isVisible() && !ui->wUserSetup->isSwitchEnabled(menu)) return;
            if(ui->wGeneralSetup->isVisible() && !ui->wGeneralSetup->isSwitchEnabled(menu)) return;
            if(ui->wMethodSetup->isVisible() && !ui->wMethodSetup->isSwitchEnabled(menu)) return;
            if(ui->wServiceSetup->isVisible() && !ui->wServiceSetup->isSwitchEnabled(menu)) return;
            if(ui->wCalibrationSetup->isVisible() && !ui->wCalibrationSetup->isSwitchEnabled(menu)) return;

        break;
    }

    if(menu != M_SETUP)
    {
      if(cInitSuccess && cWidget) cWidget->hide();
    }

    if(menu <= M_MEMORY)
    {
        ui->wMenuBar->move(0,92);
        ui->fTitle->show();
        ui->listSetupMenu->hide();
    }

    if(cMenu < M_MEMORY) ui->listSetupMenu->move(558,60+120);
    else if(cMenu == M_MEMORY) ui->listSetupMenu->move(558,60+40);
    else ui->listSetupMenu->move(558,60);

    switch (menu) {

    case M_MEASURING:
         ui->wMeasuring1->Show();
         ui->wMenuBar->setSelectedMenu(menu);

//--------------- 8-May-2023 added below
         //if(cWaitForACK)
         {
            cAccessWidget = ui->wMeasuring1;
            cAccessWidget->setWaitACKStatus(cWaitForACK);
         }
//--------------------

         if( cWidget == ui->wMeasuring1 || cWidget == ui->wCleaning ||
             cWidget == ui->wUserSetup || cWidget == ui->wServiceSetup ||
             cWidget == ui->wCalibrationSetup)
         {
             qDebug() << "TMO Reset";
             cStage = -2; //0;
             cIdleTimeout = 0;
             cStageTimeOut = 60*12;
         }

         cMenu = menu;
         cWidget = ui->wMeasuring1;
         break;

    case M_CLEANING:
         ui->wCleaning->Show();
         ui->wMenuBar->setSelectedMenu(menu);
         //--------------- 8-May-2023 added below
          //if(cWaitForACK)
          {
             cAccessWidget = ui->wCleaning;
             cAccessWidget->setWaitACKStatus(cWaitForACK);
          }
         //--------------------

         cMenu = menu;
         cWidget = ui->wCleaning;
         break;

    case M_MEMORY:

        if(cWidget) cWidget->hide();
        ui->fTitle->hide();
        ui->wMenuBar->move(0, 10);

         ui->wMemory->Show();
         ui->wMenuBar->setSelectedMenu(menu); //18-Apr-2023
         cMenu = menu;
         cWidget = ui->wMemory;
         break;

    case M_SETUP:
         ui->listSetupMenu->clearSelection();
         ui->listSetupMenu->show();
         ui->wMenuBar->setSelectedMenu(cMenu);
         break;
    }
}

void MainWindow::on_listSetupMenu_itemClicked(QListWidgetItem *item)
{

    if(item->text()==tr("User"))
    {
        if(cWidget) cWidget->hide();
        ui->fTitle->hide();
        ui->wMenuBar->move(0, 10);

        ui->wUserSetup->Show();
        cMenu = M_SETUP;
        cWidget = ui->wUserSetup;
        ui->wMenuBar->setSelectedMenu(cMenu);
    }
    else if(item->text()==tr("General"))
    {
        ui->wCheckPass->Show_CheckPass(M_PWD_GENERAL, false);
    }
    else if(item->text()==tr("Method"))
    {
        ui->wCheckPass->Show_CheckPass(M_PWD_METHOD, false);
    }
    else if(item->text()==tr("Service"))
    {
        ui->wCheckPass->Show_CheckPass(M_PWD_SERVICE, false);
    }
    else if(item->text()==tr("Calibration"))
    {
        ui->wCheckPass->Show_CheckPass(M_PWD_CALIBRATION, false);
    }

    ui->listSetupMenu->hide();
}

void MainWindow::onPassDataReceived(QString rUser, QString rPwd, int rAction, int rMenu)
{

    if(rAction==MS_TYPE_CHECK_DATA)
    {
        if(rMenu >= M_PWD_SERVICE && rMenu<=M_PWD_CALIBRATION)
        {

            if((!QString::compare(rUser, "admin", Qt::CaseSensitive) &&
                !QString::compare(rPwd, ui->wGeneralSetup->general_setup.admin_password, Qt::CaseSensitive)) ||
               (!QString::compare(rUser, "service", Qt::CaseSensitive) &&
                !QString::compare(rPwd, ui->wGeneralSetup->general_setup.service_password, Qt::CaseSensitive)) ||
               (!QString::compare(rUser, "pssc", Qt::CaseSensitive) &&
                !QString::compare(rPwd, "p", Qt::CaseSensitive)))
            {
                ui->wCheckPass->hide();

                switch(rMenu)
                {

                    case M_PWD_SERVICE: if(cWidget) cWidget->hide();
                                        ui->wServiceSetup->Show();
                                        cMenu = M_SETUP;
                                        cWidget = ui->wServiceSetup;
                                        break;

                    case M_PWD_CALIBRATION:  if(cWidget) cWidget->hide();
                                            if(rUser == "admin") {
                                                ui->wCalibrationSetup->IS_ADMIN_USER=1;
                                            }
                                            else {
                                                ui->wCalibrationSetup->IS_ADMIN_USER=0;
                                            }
                                            ui->wCalibrationSetup->Show();
                                            cMenu = M_SETUP;
                                            cWidget = ui->wCalibrationSetup;
                                            break;
                }

                ui->fTitle->hide();
                ui->wMenuBar->move(0, 10);
                ui->wMenuBar->setSelectedMenu(cMenu);
            }
            else if(!QString::compare(rUser, "admin", Qt::CaseSensitive))
                ui->wCheckPass->Show_ShowMessage(rMenu, M_USER_WRONG);
            else
                ui->wCheckPass->Show_ShowMessage(rMenu, M_PWD_WRONG);

        }
        else if(rMenu==M_PWD_GENERAL &&
           ((!QString::compare(rUser, "admin", Qt::CaseSensitive) &&
            !QString::compare(rPwd, ui->wGeneralSetup->general_setup.admin_password, Qt::CaseSensitive)) ||
           (!QString::compare(rUser, "service", Qt::CaseSensitive) &&
            !QString::compare(rPwd, ui->wGeneralSetup->general_setup.service_password, Qt::CaseSensitive)) ||
           (!QString::compare(rUser, "pssc", Qt::CaseSensitive) &&
            !QString::compare(rPwd, "p", Qt::CaseSensitive))))

        {
            ui->wCheckPass->hide();

            if(cWidget) cWidget->hide();
            ui->wGeneralSetup->Show(rUser);
            cMenu = M_SETUP;
            cWidget = ui->wGeneralSetup;

            ui->fTitle->hide();
            ui->wMenuBar->move(0, 10);
            ui->wMenuBar->setSelectedMenu(cMenu);
        }
        else if(rMenu==M_PWD_METHOD &&
                ((!QString::compare(rUser, "admin", Qt::CaseSensitive) &&
                 !QString::compare(rPwd, ui->wGeneralSetup->general_setup.admin_password, Qt::CaseSensitive)) ||
                (!QString::compare(rUser, "service", Qt::CaseSensitive) &&
                 !QString::compare(rPwd, ui->wGeneralSetup->general_setup.service_password, Qt::CaseSensitive)) ||
                (!QString::compare(rUser, "pssc", Qt::CaseSensitive) &&
                 !QString::compare(rPwd, "p", Qt::CaseSensitive))))
        {
            ui->wCheckPass->hide();

            if(cWidget) cWidget->hide();
            ui->wMethodSetup->Show();
            cMenu = M_SETUP;
            cWidget = ui->wMethodSetup;

            ui->fTitle->hide();
            ui->wMenuBar->move(0, 10);
            ui->wMenuBar->setSelectedMenu(cMenu);

        }
        else if(rMenu==M_PWD_DEBUG &&
                ((!QString::compare(rUser, "admin", Qt::CaseSensitive) &&
                 !QString::compare(rPwd, ui->wGeneralSetup->general_setup.admin_password, Qt::CaseSensitive)) ||
                (!QString::compare(rUser, "service", Qt::CaseSensitive) &&
                 !QString::compare(rPwd, ui->wGeneralSetup->general_setup.service_password, Qt::CaseSensitive)) ||
                (!QString::compare(rUser, "pssc", Qt::CaseSensitive) &&
                 !QString::compare(rPwd, "p", Qt::CaseSensitive))))
        {
            ui->wCheckPass->hide();
            ui->wServiceSetup->setDebug();

        }
        else
        {
            ui->wCheckPass->Show_ShowMessage(rMenu, M_PWD_WRONG);
        }
    }

    if(rAction==MS_TYPE_CANCEL)
    {
        ui->wCheckPass->hide();
        ui->wMenuBar->setSelectedMenu(cMenu);
    }

    if(rAction==MS_TYPE_AGAIN)
    {
        switch(rMenu)
        {
            case M_PWD_GENERAL: ui->wCheckPass->Show_CheckPass(M_PWD_GENERAL, true); break;
            case M_PWD_METHOD: ui->wCheckPass->Show_CheckPass(M_PWD_METHOD, true); break;
            case M_PWD_SERVICE: ui->wCheckPass->Show_CheckPass(M_PWD_SERVICE, true); break;
            case M_PWD_CALIBRATION: ui->wCheckPass->Show_CheckPass(M_PWD_CALIBRATION, true); break;
            case M_PWD_DEBUG: ui->wCheckPass->Show_CheckPass(M_PWD_DEBUG, true); break;
        }
    }

    if(rAction== M_ERROR_ACKNOWLEDGE)
    {
        if(cFrameErrorShown)
        {
            cFrameReceived = false;
            cFrameTimeOut = 0;
            cFrameErrorShown = false;
            ui->wError->hide();

            qDebug() << "ERR-hide";

            cAccessWidget->setWaitACKStatus(true);
            onSendCommand(cProtocol.sendMeasuring(1, 0));

        }
        else
        {
            showError();
        }

        if(!cInitDone)
        {
            cInitSuccess = false;
            cInitDone = true;

            ui->wCheckPass->hide();

            qDebug() << "TMO Reset";
            cStage = -1; //0;
            cIdleTimeout = 0;
            //ui->wMeasuring1->setIdleTimer(cIdleTimeout);
        }
    }

    if(rAction == M_MESSAGE_ACKNOWLEDGE)
    {
        ui->wCheckPass->hide();

        if(ui->wUserSetup->user_setup.auto_print)
        {
            ui->wMemory->printResult(cTest);
        }
    }

}

void MainWindow::onShowKeypad(QObject *tobj, int tmp, bool zero)
{
    ui->wKeypad->ShowKeypad(tobj, tmp, zero);
}

void MainWindow::onShowHome(bool tmp)
{
    //qDebug() << "onShowHome:" << tmp;
    onMenuClicked(M_MEASURING);
}

void MainWindow::onFileSelected(QString fs)
{
    ui->wServiceSetup->setFileSelected(fs);
}

void MainWindow::onUpdateMainWindow()
{
    this->hide();
    this->show();
}

void MainWindow::onShowFileSelect(void)
{
    ui->wFileSelect->Show();
}

void MainWindow::onGetConfirmation(int tmp, int tmp1)
{
    ui->wCheckPass->Show_Confirmation(tmp, tmp1);
}

void MainWindow::onShowMsgBox(QString title, QString msg)
{
    ui->wCheckPass->Show_Message(title, msg);
}

void MainWindow::onShowStatusBox(QString title, QString msg, bool show)
{
    ui->wCheckPass->Show_Status(title, msg, show);
}

void MainWindow::onConfirmed(int ctype, bool tmp, int cmenu)
{
    switch(ctype)
    {
        case M_CONFIRM_MEASURING_STOP:
            if(tmp) ui->wCheckPass->Show_ShowMessage(ctype, M_MEMORY_TRANSFEFRED);
        break;

        case M_CONFIRM_MEASURE_WITHOUT_SAVING:
            if(tmp) onRunClicked(MS_TEST_RUN, false);
        break;

        case M_CONFIRM_RINSING_STOP:

        break;

        case M_CONFIRM_USER:

            if(tmp)
            {
               ui->wUserSetup->readFile();
               ui->wUserSetup->hide();
               //onShowHome(false);
               onMenuClicked(cmenu);
            }
            else
            {
               //2-May-2023 ui->wUserSetup->saveFile();

               //ui->wUserSetup->hideAfterACK(true);
               //ui->wUserSetup->sendBuzAndVol();
            }

        break;

        case M_CONFIRM_GENERAL:

             if(tmp)
             {
                ui->wGeneralSetup->readFile();
                //2-May-2023 added below
                ui->wGeneralSetup->hide();
                //onShowHome(false);
                onMenuClicked(cmenu);
             }
             else
             {
                //2-May-2023 ui->wGeneralSetup->saveFile();
             }

        break;

        case M_CONFIRM_GENERAL_SWITCH:

             if(tmp) ui->wGeneralSetup->saveFile();
             else ui->wGeneralSetup->readFile();

        break;

        case M_CONFIRM_METHOD:
            if(tmp)
            {
               ui->wMethodSetup->readFile();
               //2-May-2023 added below
               ui->wMethodSetup->hide();
               //onShowHome(false);
               onMenuClicked(cmenu);
            }
            else
            {
               //ui->wMethodSetup->saveFile();
//                onShowHome(false); //naveen
            }
        break;

        case M_CONFIRM_METHOD_SWITCH:

             if(tmp)
             {
                ui->wMethodSetup->saveFile();
             }
             else
             {
                ui->wMethodSetup->readFile();
             }
        break;

        case M_CONFIRM_SERVICE:
            if(tmp)
            {
               ui->wServiceSetup->readFile();
               //2-May-2023 added below
               ui->wServiceSetup->hide();
               //onShowHome(false);
               onMenuClicked(cmenu);
            }
            else
            {
               //ui->wServiceSetup->saveFile();
            }
        break;
        case M_CONFIRM_SERVICE_SWITCH:

             if(tmp)
             {
                ui->wServiceSetup->saveFile();
             }
             else
             {
                ui->wServiceSetup->readFile();
             }
        break;

        case M_CONFIRM_CALIBRATION:

             if(tmp)
             {
                ui->wCalibrationSetup->readFile();
                //2-May-2023 added below
                ui->wCalibrationSetup->hide();
                //onShowHome(false);
                onMenuClicked(cmenu);
             }
             else
             {
                //ui->wCalibrationSetup->saveFile();
             }
        break;

        case M_CONFIRM_CALIBRATION_SWITCH:

             qDebug() << "M_CONFIRM_CALIBRATION_SWITCH:" << tmp;

             if(tmp)
             {
                ui->wCalibrationSetup->saveFile();
             }
             else
             {
                ui->wCalibrationSetup->readFile();
             }
        break;

        case M_CONFIRM_TRANSFER:

            if(tmp)
            {

#ifndef Q_OS_WIN32
                if(!cSettings.checkFolderExists(FF_USB))
                {
                    ui->wCheckPass->Show_ShowMessage(ctype, M_MEMORY_TRANSFER_NO_USB);
                }
                else

#endif

                {
                    QString fname, fdate, ftime;
                    fdate = ui->lblDate->text();
                    ftime = ui->lblTime->text();

                    fdate.replace(QString("/"), QString("_"));
                    ftime.replace(":", "_");

                    fname =  fdate + " " + ftime + " " +
                            ui->wGeneralSetup->general_setup.unit_id
                            + ".csv";

                    if(ui->wMemory->transferTests(fname)){
                        onShowMsgBox(tr("Memory Transfer"),tr("Selected Memory Transferred!"));
                    }
                    else{
                        onShowMsgBox(tr("Memory Transfer"),tr("Error Transferring Memory!"));
                    }
                }
            }

        break;

        case M_CONFIRM_DELETE:
            if(tmp)
            {
                if(ui->wMemory->deleteTests())
                    ui->wCheckPass->Show_ShowMessage(ctype, M_MEMORY_DELETED);
                else
                    ui->wCheckPass->Show_ShowMessage(ctype, M_MEMORY_DELETE_ERROR);
            }
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    cACKReceived = false;
    cNACKReceived = true;
}

void MainWindow::on_pushButton_2_clicked()
{
    cACKReceived = true;
    cNACKReceived = false;
    cUACKReceived = true;

/*
    if(cAccessWidget)
    {
        if(cAccessWidget->getHideAfterACK())
        {
            onShowHome(false);
            cAccessWidget->hideAfterACK(false);
        }
        else cAccessWidget->setWaitACKStatus(false);

        //cAccessWidget = NULL;
    }
*/

}

void MainWindow::on_pushButton_3_clicked()
{
    cParasUpdated = true;
}

void MainWindow::on_pushButton_4_clicked()
{
    if(cCurrentUCError) cCurrentUCError = 0;
    else cCurrentUCError = 1;
}
