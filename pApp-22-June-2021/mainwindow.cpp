#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTimer>

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
//   view->setGeometry(0,0,780,1034);
    view->setGeometry(0,0,768,1024);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFrameStyle(QFrame::NoFrame);
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
//   if (qgetenv("QT_FONT_DPI").isEmpty()) {
//       qputenv("QT_FONT_DPI", "96");
//   }
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

//    lastMousePos = QCursor::pos();
//    setMouseTracking(true);

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

    ui->wMenuBar->resize(768, 96);
    ui->wMenuBar->move(0,92);

    ui->wMeasuring1->resize(768, 876);
    ui->wMeasuring1->move(0, 189);
    ui->wMeasuring1->setMethods(qslMethods);
    ui->wMeasuring1->readOperatorsFile();
    ui->wMeasuring1->readSampleIdsFile();
    ui->wMeasuring1->Show();
    ui->imageCapture->resize(167,41);
    ui->imageCapture->move(20,889);
    ui->imageCapture->show();

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
    }else{
        readSaveLogFile(MEMORY_FILES, true);
    }

    ui->wMemory->readTests();

    ui->wUserSetup->resize(768, 876+92-10);
    ui->wUserSetup->move(0, 180-92+10);
    ui->wUserSetup->hide();

    if(!ui->wUserSetup->readFile())
    {
        errlist.append("User Setup");
        ui->wUserSetup->saveFile();
        QString str = " UserSetUp file is not present and values setted to default ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(USER_SETUP_FILES, false);
    }else{
        QString str = " UserSetUp file is read successfully from mainwindow ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(USER_SETUP_FILES, true);
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
        QString str = " General Setup is not present and values setted to default ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(GENERAL_SETUP_FILES, false);
    }else{
        QString str = " General Setup is read successfully from mainwindow ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(GENERAL_SETUP_FILES, true);
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

    ui->wCalibrationSetup->setMethods(qslMethods);

    if(!ui->wMethodSetup->readFile())
    {
        if(errlist.isEmpty()) errlist.append("Method Setup");
        else errlist.append(", Method Setup");
        ui->wMethodSetup->saveFile();
        QString str = " Method Setup is not present and values setted to default ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(METHOD_SETUP_FILES, false);
    }else{
        QString str = " Method Setup is read successfully from mainwindow ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(METHOD_SETUP_FILES, true);
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
        QString str = " Calibration Setup is not present and values setted to default ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(CALIBRATION_SETUP_FILES, false);
    }else{
        QString str = " Calibration Setup is read successfully from mainwindow ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(CALIBRATION_SETUP_FILES, true);
    }

    if(!ui->wCalibrationSetup->readMethodVolumeFile()){
        if(errlist.isEmpty()) errlist.append("Calibration Setup");
        else errlist.append(", Method Calibration Setup");
        qDebug()<<"Method Adjust file";
        ui->wCalibrationSetup->saveMethodVolumeFile();
        ui->wCalibrationSetup->on_D6377_Vl_ration(((ui->wMethodSetup->stdD6377.vl_ratio * 100)+100), true);
        ui->wCalibrationSetup->updateD6377Range(((ui->wMethodSetup->stdD6377.vl_ratio * 100)+100));
        QString str = " Method Calibration Setup is not present and values setted to default ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(VOLUME_ADJUSTMENT_FILES, false);
    }else{
        QString str = " Method Calibration Setup is read successfully from mainwindow ";
        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
        readSaveLogFile(VOLUME_ADJUSTMENT_FILES, true);
    }
//    qDebug()<<"value of from mainwindow constructor (ui->wCalibrationSetup->cCalibD6377.FirstVolume): "<<(ui->wCalibrationSetup->cCalibD6377.FirstVolume);

    ui->wCalibrationSetup->updateD6377Range(((ui->wMethodSetup->stdD6377.vl_ratio * 100)+100));

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
    connect(ui->wMethodSetup, SIGNAL(D6377_VlRatio(double)), this, SLOT(onD6377VlRatio(double)));
//    connect(ui->wMethodSetup, SIGNAL(methodVolumesDefault(METHOD_VOLUMES)), this, SLOT(onMethodVolumesDefault(METHOD_VOLUMES_Main)));
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

    cDateTime = QDateTime::currentDateTime().addSecs(ui->wGeneralSetup->getGMTSeconds());

    ui->lblDate->setText(cDateTime.toString(qslShowDateFormat.at(ui->wGeneralSetup->general_setup.date_format)));
    ui->lblTime->setText(cDateTime.toString(qslShowTimeFormat.at(ui->wGeneralSetup->general_setup.time_format)));
    ui->wCleaning->hide();
    rinsing = false;

    connect(ui->imageCapture, &QPushButton::clicked, this, &MainWindow::on_imageCapture_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint currentMousePos = event->globalPos();

    // Calculate the movement direction
    QPoint delta = currentMousePos - lastMousePos;

    QPoint newCursorPos = QCursor::pos();

    if (delta.y() < 0)  // Mouse moved up
        newCursorPos.setX(newCursorPos.x() - 1);  // Move left
    if (delta.x() > 0)  // Mouse moved right
        newCursorPos.setY(newCursorPos.y() - 1);  // Move up
    if (delta.y() > 0)  // Mouse moved down
        newCursorPos.setX(newCursorPos.x() + 1);  // Move right
    if (delta.x() < 0)  // Mouse moved left
        newCursorPos.setY(newCursorPos.y() + 1);  // Move down

    // Update the cursor position
    QCursor::setPos(newCursorPos);

    // Update last mouse position
    lastMousePos = currentMousePos;
}*/

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
           if(w->objectName().contains("MainWindow"))
           {
               ui->listSetupMenu->hide();
           }
       }

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

void MainWindow::readSaveLogFile(int tmp, bool readSuccessfully){
    QString str;
    switch(tmp){
    case MEMORY_FILES:{
            if(readSuccessfully){
//                str =
            }else{

            }

        }
        break;

    case USER_SETUP_FILES:{
            if(readSuccessfully){
                str =" user_setup.alarm_buzzer_enable: "+ QString::number(ui->wUserSetup->user_setup.alarm_buzzer_enable) + \
                        ", user_setup.alarm_vol: " + QString::number(ui->wUserSetup->user_setup.alarm_vol) + \
                        ", \n\t\t\t user_setup.error_buzzer_enable: " + QString::number(ui->wUserSetup->user_setup.error_buzzer_enable) + \
                        ", user_setup.rinse_cycle: " + QString::number(ui->wUserSetup->user_setup.rinse_cycle) + \
                        ", user_setup.auto_print: " + QString::number(ui->wUserSetup->user_setup.auto_print) + \
                        "\"\n";
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }
            }else{
                str =" user_setup.alarm_buzzer_enable: "+ QString::number(ui->wUserSetup->user_setup.alarm_buzzer_enable) + \
                        ", user_setup.alarm_vol: " + QString::number(ui->wUserSetup->user_setup.alarm_vol) + \
                        ", \n\t\t\t user_setup.error_buzzer_enable: " + QString::number(ui->wUserSetup->user_setup.error_buzzer_enable) + \
                        ", user_setup.rinse_cycle: " + QString::number(ui->wUserSetup->user_setup.rinse_cycle) + \
                        ", user_setup.auto_print: " + QString::number(ui->wUserSetup->user_setup.auto_print) + \
                        "\"\n";
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }
            }
        }
        break;

    case GENERAL_SETUP_FILES:{
            if(readSuccessfully){
                str =" 1- \"" + ui->wGeneralSetup->general_setup.admin_password + \
                        "\", 2- \"" + QString::number(ui->wGeneralSetup->general_setup.auto_measuring_cycle) + \
                        "\", 3- \"" + QString::number(ui->wGeneralSetup->general_setup.baud) + \
                        "\", 4- \"" + ui->wGeneralSetup->general_setup.company + \
                        "\", 5- \"" + QString::number(ui->wGeneralSetup->general_setup.data_bits) + \
                        "\", 6- \"" + QString::number(ui->wGeneralSetup->general_setup.date_format) + \
                        "\", 7- \"" + QString::number(ui->wGeneralSetup->general_setup.emulation) + \
                        "\", 8- \"" + QString::number(ui->wGeneralSetup->general_setup.flow) + \
                        "\", 9- \"" + QString::number(ui->wGeneralSetup->general_setup.gmt) + \
                        "\", 10- \"" + ui->wGeneralSetup->general_setup.ip_address + \
                        "\", 11- \"" + ui->wGeneralSetup->general_setup.ip_dns + \
                        "\", 12- \"" + ui->wGeneralSetup->general_setup.ip_gateway + \
                        "\",  \n\t\t\t 13- \"" + ui->wGeneralSetup->general_setup.ip_mask + \
                        "\", 14- \"" + QString::number(ui->wGeneralSetup->general_setup.language) + \
                        "\", 15- \"" + ui->wGeneralSetup->general_setup.location + \
                        "\", 16- \"" + QString::number(ui->wGeneralSetup->general_setup.network_enable) + \
                        "\", 17- \"" + ui->wGeneralSetup->general_setup.network_name + \
                        "\", 18- \"" + QString::number(ui->wGeneralSetup->general_setup.page_size) + \
                        "\", 19- \"" + QString::number(ui->wGeneralSetup->general_setup.parity) + \
                        "\", 20- \"" + QString::number(ui->wGeneralSetup->general_setup.pressure_scale) + \
                        "\", 21- \"" + QString::number(ui->wGeneralSetup->general_setup.report_format) + \
                        "\", 22- \"" + ui->wGeneralSetup->general_setup.service_password + \
                        "\", 23- \"" + QString::number(ui->wGeneralSetup->general_setup.stop_bits) + \
                        "\", 24-\" " + QString::number(ui->wGeneralSetup->general_setup.temperature_scale) + \
                        "\", 25- \"" + QString::number(ui->wGeneralSetup->general_setup.time_format) + \
                        "\", 26- \"" + ui->wGeneralSetup->general_setup.unit_id + \
                        "\"\n";
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }
            }else{
                str =" 1- \"" + ui->wGeneralSetup->general_setup.admin_password + \
                        "\", 2- \"" + QString::number(ui->wGeneralSetup->general_setup.auto_measuring_cycle) + \
                        "\", 3- \"" + QString::number(ui->wGeneralSetup->general_setup.baud) + \
                        "\", 4- \"" + ui->wGeneralSetup->general_setup.company + \
                        "\", 5- \"" + QString::number(ui->wGeneralSetup->general_setup.data_bits) + \
                        "\", 6- \"" + QString::number(ui->wGeneralSetup->general_setup.date_format) + \
                        "\", 7- \"" + QString::number(ui->wGeneralSetup->general_setup.emulation) + \
                        "\", 8- \"" + QString::number(ui->wGeneralSetup->general_setup.flow) + \
                        "\", 9- \"" + QString::number(ui->wGeneralSetup->general_setup.gmt) + \
                        "\", 10- \"" + ui->wGeneralSetup->general_setup.ip_address + \
                        "\", 11- \"" + ui->wGeneralSetup->general_setup.ip_dns + \
                        "\", 12- \"" + ui->wGeneralSetup->general_setup.ip_gateway + \
                        "\",  \n\t\t\t 13- \"" + ui->wGeneralSetup->general_setup.ip_mask + \
                        "\", 14- \"" + QString::number(ui->wGeneralSetup->general_setup.language) + \
                        "\", 15- \"" + ui->wGeneralSetup->general_setup.location + \
                        "\", 16- \"" + QString::number(ui->wGeneralSetup->general_setup.network_enable) + \
                        "\", 17- \"" + ui->wGeneralSetup->general_setup.network_name + \
                        "\", 18- \"" + QString::number(ui->wGeneralSetup->general_setup.page_size) + \
                        "\", 19- \"" + QString::number(ui->wGeneralSetup->general_setup.parity) + \
                        "\", 20- \"" + QString::number(ui->wGeneralSetup->general_setup.pressure_scale) + \
                        "\", 21- \"" + QString::number(ui->wGeneralSetup->general_setup.report_format) + \
                        "\", 22- \"" + ui->wGeneralSetup->general_setup.service_password + \
                        "\", 23- \"" + QString::number(ui->wGeneralSetup->general_setup.stop_bits) + \
                        "\", 24-\" " + QString::number(ui->wGeneralSetup->general_setup.temperature_scale) + \
                        "\", 25- \"" + QString::number(ui->wGeneralSetup->general_setup.time_format) + \
                        "\", 26- \"" + ui->wGeneralSetup->general_setup.unit_id + \
                        "\"\n";
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }
            }
        }
        break;

    case METHOD_SETUP_FILES:{
            if(readSuccessfully){
                str = " D5188.from - \"" + QString::number(ui->wMethodSetup->stdD5188.from) + \
                        "\", D5188.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdD5188.passfail_enabled) + \
                        "\", D5188.pressure - \"" + QString::number(ui->wMethodSetup->stdD5188.pressure) + \
                        "\", D5188.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdD5188.shaker_speed) + \
                        "\", D5188.to - \"" + QString::number(ui->wMethodSetup->stdD5188.to) + \
                        "\", D5188.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdD5188.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " D5191.aconstant - \"" + QString::number(ui->wMethodSetup->stdD5191.aconstant) + \
                        "\", D5191.bconstant - \"" + QString::number(ui->wMethodSetup->stdD5191.bconstant) + \
                        "\", D5191.cconstant - \"" + QString::number(ui->wMethodSetup->stdD5191.cconstant) + \
                        "\", D5191.formula - \"" + QString::number(ui->wMethodSetup->stdD5191.formula) + \
                        "\", D5191.from - \"" + QString::number(ui->wMethodSetup->stdD5191.from) + \
                        "\", D5191.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdD5191.passfail_enabled) + \
                        "\", \n\t\t\t D5191.single_expansion - \"" + QString::number(ui->wMethodSetup->stdD5191.single_expansion) + \
                        "\", D5191.temperature - \"" + QString::number(ui->wMethodSetup->stdD5191.temperature) + \
                        "\", D5191.time - \"" + QString::number(ui->wMethodSetup->stdD5191.time) + \
                        "\", D5191.to - \"" + QString::number(ui->wMethodSetup->stdD5191.to) + \
                        "\", D5191.vl_ratio- \"" + QString::number(ui->wMethodSetup->stdD5191.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " D6377.from - \"" + QString::number(ui->wMethodSetup->stdD6377.from) + \
                        "\", D6377.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdD6377.InjectTemp) + \
                        "\", D6377.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdD6377.passfail_enabled) + \
                        "\", D6377.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdD6377.shaker_speed) + \
                        "\", D6377.temperature - \"" + QString::number(ui->wMethodSetup->stdD6377.temperature) + \
                        "\", \n\t\t\t D6377.time - \"" + QString::number(ui->wMethodSetup->stdD6377.time) + \
                        "\", D6377.to - \"" + QString::number(ui->wMethodSetup->stdD6377.to) + \
                        "\", D6377.vl_ratio- \"" + QString::number(ui->wMethodSetup->stdD6377.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " D6378.aconstant - \"" + QString::number(ui->wMethodSetup->stdD6378.aconstant) + \
                        "\", D6378.bconstant - \"" + QString::number(ui->wMethodSetup->stdD6378.bconstant) + \
                        "\", D6378.cconstant - \"" + QString::number(ui->wMethodSetup->stdD6378.cconstant) + \
                        "\", D6378.formula - \"" + QString::number(ui->wMethodSetup->stdD6378.formula) + \
                        "\", D6378.from - \"" + QString::number(ui->wMethodSetup->stdD6378.from) + \
                        "\", D6378.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdD6378.passfail_enabled) + \
                        "\", \n\t\t\t D6378.temperature - \"" + QString::number(ui->wMethodSetup->stdD6378.temperature) + \
                        "\", D6378.time - \"" + QString::number(ui->wMethodSetup->stdD6378.time) + \
                        "\", D6378.to - \"" + QString::number(ui->wMethodSetup->stdD6378.to) + \
                        "\", D6378.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdD6378.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " Free1.aconstant - \"" + QString::number(ui->wMethodSetup->stdFree1.aconstant) + \
                        "\", Free1.bconstant - \"" + QString::number(ui->wMethodSetup->stdFree1.bconstant) + \
                        "\", Free1.cconstant - \"" + QString::number(ui->wMethodSetup->stdFree1.cconstant) + \
                        "\", Free1.from - \"" + QString::number(ui->wMethodSetup->stdFree1.from) + \
                        "\", Free1.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdFree1.InjectTemp) + \
                        "\", Free1.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdFree1.passfail_enabled) + \
                        "\", Free1.shaker_disabled - \"" + QString::number(ui->wMethodSetup->stdFree1.shaker_disabled) + \
                        "\", \n\t\t\t Free1.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdFree1.shaker_speed) + \
                        "\", Free1.temperature - \"" + QString::number(ui->wMethodSetup->stdFree1.temperature) + \
                        "\", Free1.to - \"" + QString::number(ui->wMethodSetup->stdFree1.to) + \
                        "\", Free1.tpx1 - \"" + QString::number(ui->wMethodSetup->stdFree1.tpx1) + \
                        "\", Free1.tpx2 - \"" + QString::number(ui->wMethodSetup->stdFree1.tpx2) + \
                        "\", Free1.tpx3- \"" + QString::number(ui->wMethodSetup->stdFree1.tpx3) + \
                        "\", Free1.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdFree1.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " Free2.aconstant - \"" + QString::number(ui->wMethodSetup->stdFree2.aconstant) + \
                        "\", Free2.bconstant - \"" + QString::number(ui->wMethodSetup->stdFree2.bconstant) + \
                        "\", Free2.cconstant - \"" + QString::number(ui->wMethodSetup->stdFree2.cconstant) + \
                        "\", Free2.from - \"" + QString::number(ui->wMethodSetup->stdFree2.from) + \
                        "\", Free2.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdFree2.InjectTemp) + \
                        "\", Free2.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdFree2.passfail_enabled) + \
                        "\", Free2.shaker_disabled - \"" + QString::number(ui->wMethodSetup->stdFree2.shaker_disabled) + \
                        "\", \n\t\t\t Free2.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdFree2.shaker_speed) + \
                        "\", Free2.temperature - \"" + QString::number(ui->wMethodSetup->stdFree2.temperature) + \
                        "\", Free2.to - \"" + QString::number(ui->wMethodSetup->stdFree2.to) + \
                        "\", Free2.tpx1 - \"" + QString::number(ui->wMethodSetup->stdFree2.tpx1) + \
                        "\", Free2.tpx2 - \"" + QString::number(ui->wMethodSetup->stdFree2.tpx2) + \
                        "\", Free2.tpx3 - \"" + QString::number(ui->wMethodSetup->stdFree2.tpx3) + \
                        "\", Free2.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdFree2.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " Free3.aconstant - \"" + QString::number(ui->wMethodSetup->stdFree3.aconstant) + \
                        "\", Free3.bconstant - \"" + QString::number(ui->wMethodSetup->stdFree3.bconstant) + \
                        "\", Free3.cconstant - \"" + QString::number(ui->wMethodSetup->stdFree3.cconstant) + \
                        "\", Free3.from - \"" + QString::number(ui->wMethodSetup->stdFree3.from) + \
                        "\", Free3.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdFree3.InjectTemp) + \
                        "\", Free3.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdFree3.passfail_enabled) + \
                        "\", Free3.shaker_disabled - \"" + QString::number(ui->wMethodSetup->stdFree3.shaker_disabled) + \
                        "\", \n\t\t\t Free3.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdFree3.shaker_speed) + \
                        "\", Free3.temperature - \"" + QString::number(ui->wMethodSetup->stdFree3.temperature) + \
                        "\", Free3.to - \"" + QString::number(ui->wMethodSetup->stdFree3.to) + \
                        "\", Free3.tpx1 - \"" + QString::number(ui->wMethodSetup->stdFree3.tpx1) + \
                        "\", Free3.tpx2 - \"" + QString::number(ui->wMethodSetup->stdFree3.tpx2) + \
                        "\", Free3.tpx3 - \"" + QString::number(ui->wMethodSetup->stdFree3.tpx3) + \
                        "\", Free3.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdFree3.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " Free4.aconstant - \"" + QString::number(ui->wMethodSetup->stdFree4.aconstant) + \
                        "\", Free4.bconstant - \"" + QString::number(ui->wMethodSetup->stdFree4.bconstant) + \
                        "\", Free4.cconstant - \"" + QString::number(ui->wMethodSetup->stdFree4.cconstant) + \
                        "\", Free4.from - \"" + QString::number(ui->wMethodSetup->stdFree4.from) + \
                        "\", Free4.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdFree4.InjectTemp) + \
                        "\", Free4.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdFree4.passfail_enabled) + \
                        "\", Free4.shaker_disabled - \"" + QString::number(ui->wMethodSetup->stdFree4.shaker_disabled) + \
                        "\", \n\t\t\t Free4.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdFree4.shaker_speed) + \
                        "\", Free4.temperature - \"" + QString::number(ui->wMethodSetup->stdFree4.temperature) + \
                        "\", Free4.to - \"" + QString::number(ui->wMethodSetup->stdFree4.to) + \
                        "\", Free4.tpx1 - \"" + QString::number(ui->wMethodSetup->stdFree4.tpx1) + \
                        "\", Free4.tpx2 - \"" + QString::number(ui->wMethodSetup->stdFree4.tpx2) + \
                        "\", Free4.tpx3 - \"" + QString::number(ui->wMethodSetup->stdFree4.tpx3) + \
                        "\", Free4.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdFree4.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

            }else{

                str = " D5188.from - \"" + QString::number(ui->wMethodSetup->stdD5188.from) + \
                        "\", D5188.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdD5188.passfail_enabled) + \
                        "\", D5188.pressure - \"" + QString::number(ui->wMethodSetup->stdD5188.pressure) + \
                        "\", D5188.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdD5188.shaker_speed) + \
                        "\", D5188.to - \"" + QString::number(ui->wMethodSetup->stdD5188.to) + \
                        "\", D5188.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdD5188.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " D5191.aconstant - \"" + QString::number(ui->wMethodSetup->stdD5191.aconstant) + \
                        "\", D5191.bconstant - \"" + QString::number(ui->wMethodSetup->stdD5191.bconstant) + \
                        "\", D5191.cconstant - \"" + QString::number(ui->wMethodSetup->stdD5191.cconstant) + \
                        "\", D5191.formula - \"" + QString::number(ui->wMethodSetup->stdD5191.formula) + \
                        "\", D5191.from - \"" + QString::number(ui->wMethodSetup->stdD5191.from) + \
                        "\", D5191.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdD5191.passfail_enabled) + \
                        "\", \n\t\t\t D5191.single_expansion - \"" + QString::number(ui->wMethodSetup->stdD5191.single_expansion) + \
                        "\", D5191.temperature - \"" + QString::number(ui->wMethodSetup->stdD5191.temperature) + \
                        "\", D5191.time - \"" + QString::number(ui->wMethodSetup->stdD5191.time) + \
                        "\", D5191.to - \"" + QString::number(ui->wMethodSetup->stdD5191.to) + \
                        "\", D5191.vl_ratio- \"" + QString::number(ui->wMethodSetup->stdD5191.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " D6377.from - \"" + QString::number(ui->wMethodSetup->stdD6377.from) + \
                        "\", D6377.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdD6377.InjectTemp) + \
                        "\", D6377.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdD6377.passfail_enabled) + \
                        "\", D6377.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdD6377.shaker_speed) + \
                        "\", D6377.temperature - \"" + QString::number(ui->wMethodSetup->stdD6377.temperature) + \
                        "\", \n\t\t\t D6377.time - \"" + QString::number(ui->wMethodSetup->stdD6377.time) + \
                        "\", D6377.to - \"" + QString::number(ui->wMethodSetup->stdD6377.to) + \
                        "\", D6377.vl_ratio- \"" + QString::number(ui->wMethodSetup->stdD6377.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " D6378.aconstant - \"" + QString::number(ui->wMethodSetup->stdD6378.aconstant) + \
                        "\", D6378.bconstant - \"" + QString::number(ui->wMethodSetup->stdD6378.bconstant) + \
                        "\", D6378.cconstant - \"" + QString::number(ui->wMethodSetup->stdD6378.cconstant) + \
                        "\", D6378.formula - \"" + QString::number(ui->wMethodSetup->stdD6378.formula) + \
                        "\", D6378.from - \"" + QString::number(ui->wMethodSetup->stdD6378.from) + \
                        "\", D6378.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdD6378.passfail_enabled) + \
                        "\", \n\t\t\t D6378.temperature - \"" + QString::number(ui->wMethodSetup->stdD6378.temperature) + \
                        "\", D6378.time - \"" + QString::number(ui->wMethodSetup->stdD6378.time) + \
                        "\", D6378.to - \"" + QString::number(ui->wMethodSetup->stdD6378.to) + \
                        "\", D6378.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdD6378.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " Free1.aconstant - \"" + QString::number(ui->wMethodSetup->stdFree1.aconstant) + \
                        "\", Free1.bconstant - \"" + QString::number(ui->wMethodSetup->stdFree1.bconstant) + \
                        "\", Free1.cconstant - \"" + QString::number(ui->wMethodSetup->stdFree1.cconstant) + \
                        "\", Free1.from - \"" + QString::number(ui->wMethodSetup->stdFree1.from) + \
                        "\", Free1.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdFree1.InjectTemp) + \
                        "\", Free1.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdFree1.passfail_enabled) + \
                        "\", Free1.shaker_disabled - \"" + QString::number(ui->wMethodSetup->stdFree1.shaker_disabled) + \
                        "\", \n\t\t\t Free1.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdFree1.shaker_speed) + \
                        "\", Free1.temperature - \"" + QString::number(ui->wMethodSetup->stdFree1.temperature) + \
                        "\", Free1.to - \"" + QString::number(ui->wMethodSetup->stdFree1.to) + \
                        "\", Free1.tpx1 - \"" + QString::number(ui->wMethodSetup->stdFree1.tpx1) + \
                        "\", Free1.tpx2 - \"" + QString::number(ui->wMethodSetup->stdFree1.tpx2) + \
                        "\", Free1.tpx3- \"" + QString::number(ui->wMethodSetup->stdFree1.tpx3) + \
                        "\", Free1.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdFree1.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " Free2.aconstant - \"" + QString::number(ui->wMethodSetup->stdFree2.aconstant) + \
                        "\", Free2.bconstant - \"" + QString::number(ui->wMethodSetup->stdFree2.bconstant) + \
                        "\", Free2.cconstant - \"" + QString::number(ui->wMethodSetup->stdFree2.cconstant) + \
                        "\", Free2.from - \"" + QString::number(ui->wMethodSetup->stdFree2.from) + \
                        "\", Free2.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdFree2.InjectTemp) + \
                        "\", Free2.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdFree2.passfail_enabled) + \
                        "\", Free2.shaker_disabled - \"" + QString::number(ui->wMethodSetup->stdFree2.shaker_disabled) + \
                        "\", \n\t\t\t Free2.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdFree2.shaker_speed) + \
                        "\", Free2.temperature - \"" + QString::number(ui->wMethodSetup->stdFree2.temperature) + \
                        "\", Free2.to - \"" + QString::number(ui->wMethodSetup->stdFree2.to) + \
                        "\", Free2.tpx1 - \"" + QString::number(ui->wMethodSetup->stdFree2.tpx1) + \
                        "\", Free2.tpx2 - \"" + QString::number(ui->wMethodSetup->stdFree2.tpx2) + \
                        "\", Free2.tpx3 - \"" + QString::number(ui->wMethodSetup->stdFree2.tpx3) + \
                        "\", Free2.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdFree2.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " Free3.aconstant - \"" + QString::number(ui->wMethodSetup->stdFree3.aconstant) + \
                        "\", Free3.bconstant - \"" + QString::number(ui->wMethodSetup->stdFree3.bconstant) + \
                        "\", Free3.cconstant - \"" + QString::number(ui->wMethodSetup->stdFree3.cconstant) + \
                        "\", Free3.from - \"" + QString::number(ui->wMethodSetup->stdFree3.from) + \
                        "\", Free3.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdFree3.InjectTemp) + \
                        "\", Free3.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdFree3.passfail_enabled) + \
                        "\", Free3.shaker_disabled - \"" + QString::number(ui->wMethodSetup->stdFree3.shaker_disabled) + \
                        "\", \n\t\t\t Free3.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdFree3.shaker_speed) + \
                        "\", Free3.temperature - \"" + QString::number(ui->wMethodSetup->stdFree3.temperature) + \
                        "\", Free3.to - \"" + QString::number(ui->wMethodSetup->stdFree3.to) + \
                        "\", Free3.tpx1 - \"" + QString::number(ui->wMethodSetup->stdFree3.tpx1) + \
                        "\", Free3.tpx2 - \"" + QString::number(ui->wMethodSetup->stdFree3.tpx2) + \
                        "\", Free3.tpx3 - \"" + QString::number(ui->wMethodSetup->stdFree3.tpx3) + \
                        "\", Free3.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdFree3.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " Free4.aconstant - \"" + QString::number(ui->wMethodSetup->stdFree4.aconstant) + \
                        "\", Free4.bconstant - \"" + QString::number(ui->wMethodSetup->stdFree4.bconstant) + \
                        "\", Free4.cconstant - \"" + QString::number(ui->wMethodSetup->stdFree4.cconstant) + \
                        "\", Free4.from - \"" + QString::number(ui->wMethodSetup->stdFree4.from) + \
                        "\", Free4.InjectTemp - \"" + QString::number(ui->wMethodSetup->stdFree4.InjectTemp) + \
                        "\", Free4.passfail_enabled - \"" + QString::number(ui->wMethodSetup->stdFree4.passfail_enabled) + \
                        "\", Free4.shaker_disabled - \"" + QString::number(ui->wMethodSetup->stdFree4.shaker_disabled) + \
                        "\", \n\t\t\t Free4.shaker_speed - \"" + QString::number(ui->wMethodSetup->stdFree4.shaker_speed) + \
                        "\", Free4.temperature - \"" + QString::number(ui->wMethodSetup->stdFree4.temperature) + \
                        "\", Free4.to - \"" + QString::number(ui->wMethodSetup->stdFree4.to) + \
                        "\", Free4.tpx1 - \"" + QString::number(ui->wMethodSetup->stdFree4.tpx1) + \
                        "\", Free4.tpx2 - \"" + QString::number(ui->wMethodSetup->stdFree4.tpx2) + \
                        "\", Free4.tpx3 - \"" + QString::number(ui->wMethodSetup->stdFree4.tpx3) + \
                        "\", Free4.vl_ratio - \"" + QString::number(ui->wMethodSetup->stdFree4.vl_ratio) + \
                        "\"\n";

                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }
            }
        }
        break;

    case CALIBRATION_SETUP_FILES:{
            if(readSuccessfully){
                str = " CalibTm.constant: " + QString::number(ui->wCalibrationSetup->cCalibTm.constant) + \
                        " CalibTm.method: " + QString::number(ui->wCalibrationSetup->cCalibTm.method) + \
                        " CalibTm.slope: " + QString::number(ui->wCalibrationSetup->cCalibTm.slope) + \
                        " CalibTm.tgain: " + QString::number(ui->wCalibrationSetup->cCalibTm.tgain) + \
                        " CalibTm.thigh: " + QString::number(ui->wCalibrationSetup->cCalibTm.thigh) + \
                        " CalibTm.thigh_count: " + QString::number(ui->wCalibrationSetup->cCalibTm.thigh_count) + \
                        " \n\t\t\t CalibTm.tlow: " + QString::number(ui->wCalibrationSetup->cCalibTm.tlow) + \
                        " CalibTm.tlow_count: " + QString::number(ui->wCalibrationSetup->cCalibTm.tlow_count) + \
                        " CalibTm.toffset: " + QString::number(ui->wCalibrationSetup->cCalibTm.toffset) + \
                        " CalibTm.tzero: " + QString::number(ui->wCalibrationSetup->cCalibTm.tzero);
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " CalibPr.constant20: " + QString::number(ui->wCalibrationSetup->cCalibPr.constant20) + \
                        " CalibPr.pgain: " + QString::number(ui->wCalibrationSetup->cCalibPr.pgain) + \
                        " CalibPr.phigh: " + QString::number(ui->wCalibrationSetup->cCalibPr.phigh) + \
                        " CalibPr.phigh_count: " + QString::number(ui->wCalibrationSetup->cCalibPr.phigh_count) + \
                        " CalibPr.plow: " + QString::number(ui->wCalibrationSetup->cCalibPr.plow) + \
                        " CalibPr.plow_count: " + QString::number(ui->wCalibrationSetup->cCalibPr.plow_count) + \
                        " \n\t\t\t CalibPr.poffset: " + QString::number(ui->wCalibrationSetup->cCalibPr.poffset) + \
                        " CalibPr.prl_high: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_high) + \
                        " CalibPr.prl_index: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_index) + \
                        " CalibPr.prl_low: " +QString::number( ui->wCalibrationSetup->cCalibPr.prl_low) + \
                        " CalibPr.pzero: " + QString::number(ui->wCalibrationSetup->cCalibPr.pzero) + \
                        " CalibPr.slope20: " + QString::number(ui->wCalibrationSetup->cCalibPr.slope20);
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = "";
                for(int i=0;i<19;i++){
                    str += " \n\t\t\t CalibPr.prl_enabled[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_enabled[i]) + \
                           " CalibPr.prl_temperature[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_temperature[i]) + \
                           " CalibPr.prl_low_correction[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_low_correction[i]) + \
                           " CalibPr.prl_high_correction[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_high_correction[i]) + \
                            " CalibPr.prl_slope[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_slope[i]) + \
                            " CalibPr.prl_constant[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_constant[i]);
                }
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

            }else{
                str = " CalibTm.constant: " + QString::number(ui->wCalibrationSetup->cCalibTm.constant) + \
                        " CalibTm.method: " + QString::number(ui->wCalibrationSetup->cCalibTm.method) + \
                        " CalibTm.slope: " + QString::number(ui->wCalibrationSetup->cCalibTm.slope) + \
                        " CalibTm.tgain: " + QString::number(ui->wCalibrationSetup->cCalibTm.tgain) + \
                        " CalibTm.thigh: " + QString::number(ui->wCalibrationSetup->cCalibTm.thigh) + \
                        " CalibTm.thigh_count: " + QString::number(ui->wCalibrationSetup->cCalibTm.thigh_count) + \
                        " \n\t\t\t CalibTm.tlow: " + QString::number(ui->wCalibrationSetup->cCalibTm.tlow) + \
                        " CalibTm.tlow_count: " + QString::number(ui->wCalibrationSetup->cCalibTm.tlow_count) + \
                        " CalibTm.toffset: " + QString::number(ui->wCalibrationSetup->cCalibTm.toffset) + \
                        " CalibTm.tzero: " + QString::number(ui->wCalibrationSetup->cCalibTm.tzero);
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = " CalibPr.constant20: " + QString::number(ui->wCalibrationSetup->cCalibPr.constant20) + \
                        " CalibPr.pgain: " + QString::number(ui->wCalibrationSetup->cCalibPr.pgain) + \
                        " CalibPr.phigh: " + QString::number(ui->wCalibrationSetup->cCalibPr.phigh) + \
                        " CalibPr.phigh_count: " + QString::number(ui->wCalibrationSetup->cCalibPr.phigh_count) + \
                        " CalibPr.plow: " + QString::number(ui->wCalibrationSetup->cCalibPr.plow) + \
                        " CalibPr.plow_count: " + QString::number(ui->wCalibrationSetup->cCalibPr.plow_count) + \
                        " \n\t\t\t CalibPr.poffset: " + QString::number(ui->wCalibrationSetup->cCalibPr.poffset) + \
                        " CalibPr.prl_high: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_high) + \
                        " CalibPr.prl_index: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_index) + \
                        " CalibPr.prl_low: " +QString::number( ui->wCalibrationSetup->cCalibPr.prl_low) + \
                        " CalibPr.pzero: " + QString::number(ui->wCalibrationSetup->cCalibPr.pzero) + \
                        " CalibPr.slope20: " + QString::number(ui->wCalibrationSetup->cCalibPr.slope20);
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }

                str = "";
                for(int i=0;i<19;i++){
                    str += " \n\t\t\t CalibPr.prl_enabled[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_enabled[i]) + \
                           " CalibPr.prl_temperature[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_temperature[i]) + \
                           " CalibPr.prl_low_correction[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_low_correction[i]) + \
                           " CalibPr.prl_high_correction[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_high_correction[i]) + \
                            " CalibPr.prl_slope[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_slope[i]) + \
                            " CalibPr.prl_constant[" + QString::number(i) + "]: " + QString::number(ui->wCalibrationSetup->cCalibPr.prl_constant[i]);
                }
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }


            }
        }
        break;

    case VOLUME_ADJUSTMENT_FILES:{
            if(readSuccessfully){
                str = " D5188.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5188.StageVolume) + \
                        " D5188.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5188.FirstVolume) + \
                        " \n\t\t\t D5191.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5191.StageVolume) + \
                        " D5191.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5191.FirstVolume) + \
                        " D5191.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5191.SecondVolume)  + \
                        " D5191.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibD5191.ThirdVOlume) + \
                        " \n\t\t\t SingleD5191.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibSingleD5191.StageVolume) + \
                        " SingleD5191.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibSingleD5191.FirstVolume) + \
                        " \n\t\t\t D6377.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6377.StageVolume) + \
                        " D6377.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6377.FirstVolume) + \
                        " \n\t\t\t D6378.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6378.StageVolume) + \
                        " D6378.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6378.FirstVolume) + \
                        " D6378.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6378.SecondVolume) + \
                        " D6378.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibD6378.ThirdVOlume) + \
                        " \n\t\t\t Free1.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree1.StageVolume) + \
                        " Free1.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree1.FirstVolume) + \
                        " Free1.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree1.SecondVolume) + \
                        " Free1.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibFree1.ThirdVOlume) + \
                        " \n\t\t\t Free2.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree2.StageVolume) + \
                        " Free2.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree2.FirstVolume) + \
                        " Free2.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree2.SecondVolume) + \
                        " Free2.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibFree2.ThirdVOlume) + \
                        " \n\t\t\t Free3.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree3.StageVolume) + \
                        " Free3.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree3.FirstVolume) + \
                        " Free3.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree3.SecondVolume) + \
                        " Free3.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibFree3.ThirdVOlume) + \
                        " \n\t\t\t Free4.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree4.StageVolume) + \
                        " Free4.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree4.FirstVolume) + \
                        " Free4.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree4.SecondVolume) + \
                        " Free4.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibFree4.ThirdVOlume);
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }
            }else{
                str = " D5188.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5188.StageVolume) + \
                        " D5188.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5188.FirstVolume) + \
                        " \n\t\t\t D5191.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5191.StageVolume) + \
                        " D5191.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5191.FirstVolume) + \
                        " D5191.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibD5191.SecondVolume)  + \
                        " D5191.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibD5191.ThirdVOlume) + \
                        " \n\t\t\t SingleD5191.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibSingleD5191.StageVolume) + \
                        " SingleD5191.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibSingleD5191.FirstVolume) + \
                        " \n\t\t\t D6377.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6377.StageVolume) + \
                        " D6377.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6377.FirstVolume) + \
                        " \n\t\t\t D6378.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6378.StageVolume) + \
                        " D6378.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6378.FirstVolume) + \
                        " D6378.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibD6378.SecondVolume) + \
                        " D6378.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibD6378.ThirdVOlume) + \
                        " \n\t\t\t Free1.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree1.StageVolume) + \
                        " Free1.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree1.FirstVolume) + \
                        " Free1.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree1.SecondVolume) + \
                        " Free1.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibFree1.ThirdVOlume) + \
                        " \n\t\t\t Free2.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree2.StageVolume) + \
                        " Free2.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree2.FirstVolume) + \
                        " Free2.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree2.SecondVolume) + \
                        " Free2.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibFree2.ThirdVOlume) + \
                        " \n\t\t\t Free3.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree3.StageVolume) + \
                        " Free3.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree3.FirstVolume) + \
                        " Free3.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree3.SecondVolume) + \
                        " Free3.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibFree3.ThirdVOlume) + \
                        " \n\t\t\t Free4.StageVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree4.StageVolume) + \
                        " Free4.FirstVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree4.FirstVolume) + \
                        " Free4.SecondVolume: " + QString::number(ui->wCalibrationSetup->cCalibFree4.SecondVolume) + \
                        " Free4.ThirdVOlume: " + QString::number(ui->wCalibrationSetup->cCalibFree4.ThirdVOlume);
                if(ui->wServiceSetup->logPathEnabled())
                    ui->wServiceSetup->commandLog(str);
                else if(ui->wServiceSetup->internalLogData())
                {
                    qDebug()<<"First Time";
                    ui->wServiceSetup->commandLog(str);
                }
            }
        }
        break;
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
    ui->wMeasuring1->onLiveData(cRawCTemperature, cRawCPressure);

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
                        sendPara(cProtocol.sendPistonPosition(100), 4, 60);
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
                            ui->wServiceSetup->sInitDone = false;

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

    case 4:
            {
                double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                if((cValvePosition == M_VALVE_POSITION_EXHAUST && cPistonPosition == 100) &&
                   ((ctmp >= (20 - M_INIT_TEMPERATURE_TOLERANCE ))
                   && (ctmp <= (20 + M_INIT_TEMPERATURE_TOLERANCE ))))
                {
                    sendPara(cProtocol.sendPistonPosition(0), 5, 60);
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
                        ui->wServiceSetup->sInitDone = false;

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

        case 5:
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
//                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable){
//                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
//                        }

                        if(ui->wServiceSetup->getUSBLogEnabled()){
                            if(ui->wServiceSetup->USBNotFound){
                                onShowMsgBox(tr("Initial"), tr("Initialization is Successful\nUSB not found, USB Log is disabled"));
                                ui->wServiceSetup->sInitDone = false;
                                ui->wServiceSetup->USBNotFound = false;
                                ui->wServiceSetup->resetDataLog();
                            }else{
                                onShowStatusBox(tr("Initial"), tr("Initialization is successful"),true);
                                QEventLoop delay;
                                QTimer::singleShot(3000,&delay,&QEventLoop::quit);
                                delay.exec();
                                onShowStatusBox(tr("Initial"), tr("Initialization is successful"),false);
                                ui->wServiceSetup->sInitDone = false;
                                ui->wServiceSetup->USBNotFound = false;
                            }
                        }
                        else
                        {
                            onShowStatusBox(tr("Initial"), tr("Initialization is successful"),true);
                            QEventLoop delay;
                            QTimer::singleShot(1000,&delay,&QEventLoop::quit);
                            delay.exec();
                            onShowStatusBox(tr("Initial"), tr("Initialization is successful"),false);
                        }
                        cInitSuccess = true;
                        cInitDone = true;
                        ui->wServiceSetup->sInitDone = false;

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
                            ui->wServiceSetup->sInitDone = false;

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
                        int tc = cSettings.getTemperatureCount(20);

                        sendPara(cProtocol.sendTemperature(tc),
                                 3, 120);

                        if(ui->wMeasuring1->isVisible())
                        {
                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);
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

                    double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                    if((ctmp >= (20 - 0.25 )) && (ctmp <= (20 + 0.25 )))
                    {
                        #ifdef Q_OS_WIN32
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 4, 10);
                        #else
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 4, 60);
                        #endif
                            if(ui->wMeasuring1->isVisible()){
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

        case 4:
                {
                    cParasUpdated = false;

                    if(cValvePosition == M_VALVE_POSITION_IN)
                    {
                        sendPara(cProtocol.sendPistonPosition(250), 5, 60);

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

        case 5:
                {
                    cParasUpdated = false;

                    if((cPistonPosition <= 250+5) && (cPistonPosition >= 250-5))
                    {
                        sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST), 6, 60);

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

        case 6:
                {
                    cParasUpdated = false;
                    if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                    {
                        sendPara(cProtocol.sendPistonPosition(0), 7, 60);

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

        case 7:
                {
                    cParasUpdated = false;
                    if(cPistonPosition == 0)
                    {
                        cRinseCycles++;

                        if(cRinseCycles < ui->wUserSetup->user_setup.rinse_cycle + 1)
                        {
                            
			             ui->wCleaning->updateStatus(cRinseCycles + 1, ui->wUserSetup->user_setup.rinse_cycle + 1);
                            cStage = 3;
                        }
                        else
                        {
//                            if(ui->wCleaning->isVisible())
                            if(rinsing)
                            {
                                //cStage = 0;

                                cIdleTimeout = 0;
                                qDebug() << "TMO Reset";
                                cStage = -2; //0;
                                cIdleTimeout = 0;
                                rinsing = false;

                                int tc = cSettings.getTemperatureCount(20);

                                ui->wMeasuring1->setRunning(false);
//                                ui->wCleaning->setRunning(false); //18-Apr-2023
                                ui->wMenuBar->setSelectedMenu(M_MEASURING); //18-Apr-2023

                                sendPara(cProtocol.sendMeasuring(0, tc), -2, 60*12);
                            }
                            
                            else
                            {
                                sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 8, 60);

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

void MainWindow::handleInjectRinsing()
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

                    switch(ui->wMeasuring1->getMethod())
                    {
                        case M_METHOD_D6377: cTmTest = ui->wMethodSetup->stdD6377.InjectTemp;
                        break;

                        case M_METHOD_FREE1: cTmTest = ui->wMethodSetup->stdFree1.InjectTemp;
                        break;

                        case M_METHOD_FREE2: cTmTest = ui->wMethodSetup->stdFree2.InjectTemp;
                        break;

                        case M_METHOD_FREE3: cTmTest = ui->wMethodSetup->stdFree3.InjectTemp;
                        break;

                        case M_METHOD_FREE4: cTmTest = ui->wMethodSetup->stdFree4.InjectTemp;
                        break;

                        default : cTmTest = 20.0;
                        break;
                    }

                    if((cValvePosition == M_VALVE_POSITION_EXHAUST) &&
                       (cPistonPosition == 0) && ((ctmp >= (cTmTest - M_RINSING_TEMPERATURE_TOLERANCE )) && (ctmp <= (cTmTest + M_RINSING_TEMPERATURE_TOLERANCE ))))
                    {
                        int tc = cSettings.getTemperatureCount(cTmTest);

                        sendPara(cProtocol.sendTemperature(tc),
                                 3, 120);

                        if(ui->wMeasuring1->isVisible())
                        {
                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);
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

                    double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                    if((ctmp >= (cTmTest - 0.25 )) && (ctmp <= (cTmTest + 0.25 )))
                    {
                        #ifdef Q_OS_WIN32
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 4, 10);
                        #else
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 4, 60);
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

                            if(((ctmp < (cTmTest - M_TEMPERATURE_TOLERANCE )) || (ctmp > (cTmTest + M_TEMPERATURE_TOLERANCE ))))
                            {
                                setError(M_ERROR_TEMPERATURE);
                            }

                        }
                        else cStageTimeOut--;
                    }
                }

                break;

        case 4:
                {
                    cParasUpdated = false;

                    if(cValvePosition == M_VALVE_POSITION_IN)
                    {
                        sendPara(cProtocol.sendPistonPosition(250), 5, 60);

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

        case 5:
                {
                    cParasUpdated = false;

                    if((cPistonPosition <= 250+5) && (cPistonPosition >= 250-5))
                    {
                        sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST), 6, 60);

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

        case 6:
                {
                    cParasUpdated = false;
                    if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                    {
                        sendPara(cProtocol.sendPistonPosition(0), 7, 60);

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

        case 7:
                {
                    cParasUpdated = false;
                    if(cPistonPosition == 0)
                    {
                        cRinseCycles++;

                        if(cRinseCycles < ui->wUserSetup->user_setup.rinse_cycle + 1)
                        {

                         ui->wCleaning->updateStatus(cRinseCycles + 1, ui->wUserSetup->user_setup.rinse_cycle + 1);
                            cStage = 3;
                        }
                        else
                        {
//                            if(ui->wCleaning->isVisible())
                            if(rinsing)
                            {
                                //cStage = 0;

                                cIdleTimeout = 0;
                                qDebug() << "TMO Reset";
                                cStage = -2; //0;
                                cIdleTimeout = 0;
                                rinsing = false;

                                switch(ui->wMeasuring1->getMethod())
                                {
                                    case M_METHOD_D6377: cTmTest = ui->wMethodSetup->stdD6377.InjectTemp;
                                    break;

                                    case M_METHOD_FREE1: cTmTest = ui->wMethodSetup->stdFree1.InjectTemp;
                                    break;

                                    case M_METHOD_FREE2: cTmTest = ui->wMethodSetup->stdFree2.InjectTemp;
                                    break;

                                    case M_METHOD_FREE3: cTmTest = ui->wMethodSetup->stdFree3.InjectTemp;
                                    break;

                                    case M_METHOD_FREE4: cTmTest = ui->wMethodSetup->stdFree4.InjectTemp;
                                    break;

                                    default : cTmTest = 20.0;
                                    break;
                                }

                                int tc = cSettings.getTemperatureCount(cTmTest);

                                ui->wMeasuring1->setRunning(false);
//                                ui->wCleaning->setRunning(false); //18-Apr-2023
                                ui->wMenuBar->setSelectedMenu(M_MEASURING); //18-Apr-2023
                                sendPara(cProtocol.sendMeasuring(0, tc), -2, 60*12);
                            }

                            else
                            {
                                sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_IN), 8, 60);

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

//                            qDebug()<<"Piston Position: "<<cPistonPosition;
//                            qDebug()<<"Stepper Speed: "<<cStepperSpeed;
                            ui->wMeasuring1->onLiveData(cRawCTemperature, cRawCPressure);
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

//                            ui->wServiceSetup->onInternalLogData(cValvePosition, cPistonPosition,
//                                                                 cRawATemperature, cRawCTemperature,
//                                                                 cRawCPressure, cStepperSpeed, cCurrentUCError);
                            QString str = " Tm:" + cSettings.getTemperatureLive(cRawCTemperature)
                                          + ", Pr:" + cSettings.getPressureLiveSS(cRawCTemperature, cRawCPressure)
                                          + ", Valve:" + QString::number(cValvePosition)
                                          + ", PP:" + QString::number(cPistonPosition/100.0, 'f', 2)
                                          + ", SS:" + QString::number(cStepperSpeed)
                                          + ", ADC T: " + QString::number(cRawCTemperature)
                                          + ", ADC P: " + QString::number(cRawCPressure);
                            QString logMethod;
                            QString currentTab;

                            if(ui->wMeasuring1->isVisible())
                            {
                                currentTab = "Measuring Tab ";
                                switch(ui->wMeasuring1->getMethod())
                                {
                                case M_METHOD_D5191: logMethod = "D5191 ";
                                    break;

                                case M_METHOD_D6377: logMethod = "D6377 ";
                                    break;

                                case M_METHOD_D6378: logMethod = "D6378 ";
                                    break;

                                case M_METHOD_D5188: logMethod = "D5188 ";
                                    break;

                                case M_METHOD_FREE1: logMethod = "Free1 ";
                                    break;

                                case M_METHOD_FREE2: logMethod = "Free2 ";
                                    break;

                                case M_METHOD_FREE3: logMethod = "Free3 ";
                                    break;

                                case M_METHOD_FREE4: logMethod = "Free4 ";
                                    break;

                                default: logMethod = " ";
                                    break;
                                }
                            }
                            else if(ui->wUserSetup->isVisible()){
                                if(ui->wUserSetup->UserSetUpFilesSaved){
                                    QString tmpstr = " USER setup file is saved ";

                                    if(ui->wServiceSetup->logPathEnabled())
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    else if(ui->wServiceSetup->internalLogData())
                                    {
                                        qDebug()<<"First Time";
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    }

                                    ui->wUserSetup->UserSetUpFilesSaved = false;
                                    readSaveLogFile(USER_SETUP_FILES, false);
                                }
                                logMethod = "";
                                currentTab = "User Tab ";
                            }else if(ui->wMemory->isVisible()){
                                logMethod = "";
                                currentTab = "Memory Tab ";
                            }else if(ui->wGeneralSetup->isVisible()){
                                if(ui->wGeneralSetup->GeneralSetUpFilesSaved){
                                    QString tmpstr = " GENERAL setup file is saved ";

                                    if(ui->wServiceSetup->logPathEnabled())
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    else if(ui->wServiceSetup->internalLogData())
                                    {
                                        qDebug()<<"First Time";
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    }
                                    ui->wGeneralSetup->GeneralSetUpFilesSaved = false;
                                    readSaveLogFile(GENERAL_SETUP_FILES, false);
                                }
                                logMethod = "";
                                currentTab = "General SetUp Tab ";
                            }else if(ui->wMethodSetup->isVisible()){
                                if(ui->wMethodSetup->MethodSetUpFilesSaved){
                                    QString tmpstr = " METHOD setup file is saved ";

                                    if(ui->wServiceSetup->logPathEnabled())
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    else if(ui->wServiceSetup->internalLogData())
                                    {
                                        qDebug()<<"First Time";
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    }

                                    ui->wMethodSetup->MethodSetUpFilesSaved = false;
                                    readSaveLogFile(METHOD_SETUP_FILES, false);
                                }
                                logMethod = "";
                                currentTab = "Method SetUp Tab ";
                            }else if(ui->wServiceSetup->isVisible()){
                                if(ui->wServiceSetup->ServiceSetUpFilesSaved){
                                    QString tmpstr = " SERVICE setup file is saved ";

                                    if(ui->wServiceSetup->logPathEnabled())
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    else if(ui->wServiceSetup->internalLogData())
                                    {
                                        qDebug()<<"First Time";
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    }

                                    ui->wServiceSetup->ServiceSetUpFilesSaved = false;
                                    readSaveLogFile(SERVICE_SETUP_FILES, false);
                                }
                                logMethod = "";
                                currentTab = "Service Tab ";
                            }else if(ui->wCalibrationSetup->isVisible()){
                                if(ui->wCalibrationSetup->CalibSetUpFilesSaved)
                                {
                                    QString tmpstr = " CALIBRATION setup file is saved ";

                                    if(ui->wServiceSetup->logPathEnabled())
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    else if(ui->wServiceSetup->internalLogData())
                                    {
                                        qDebug()<<"First Time";
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    }
                                    if(ui->wCalibrationSetup->CalibSetUpFilesSaved){
                                        ui->wCalibrationSetup->CalibSetUpFilesSaved = false;
                                        readSaveLogFile(CALIBRATION_SETUP_FILES, false);
                                    }
                                } else if(ui->wCalibrationSetup->VolumeCalibSetUpFilesSaved){
                                    QString tmpstr = " METHOD CALIBRATION setup file is saved ";

                                    if(ui->wServiceSetup->logPathEnabled())
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    else if(ui->wServiceSetup->internalLogData())
                                    {
                                        qDebug()<<"First Time";
                                        ui->wServiceSetup->commandLog(tmpstr);
                                    }
                                    if(ui->wCalibrationSetup->VolumeCalibSetUpFilesSaved){
                                        ui->wCalibrationSetup->VolumeCalibSetUpFilesSaved = false;
                                        readSaveLogFile(VOLUME_ADJUSTMENT_FILES, false);
                                    }
                                }
                                logMethod = "";
                                currentTab = " Calibration Tab ";
                            }else {
                                logMethod = "";
                                currentTab = "";
                            }
                            if(ui->wServiceSetup->logPathEnabled())
                                ui->wServiceSetup->commandLog(currentTab + logMethod + str);
                            else if(ui->wServiceSetup->internalLogData())
                            {
                                qDebug()<<"First Time";
                                ui->wServiceSetup->commandLog(str);
                            }


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

                        QString str = "cACKReceived: "+ QString::number(cACKReceived) + " cNACKReceived: " + QString::number(cNACKReceived) + " cUACKReceived: "+ QString::number(cUACKReceived);

                        if(ui->wServiceSetup->logPathEnabled())
                            ui->wServiceSetup->commandLog(str);
                        else if(ui->wServiceSetup->internalLogData())
                        {
                            qDebug()<<"First Time";
                            ui->wServiceSetup->commandLog(str);
                        }
                    }
                    else if(rdata[2] == '2' && rdata[3] == '1') //nack
                    {
                        cACKReceived = false;
                        cNACKReceived = true;

                        QString str = "cACKReceived: "+ QString::number(cACKReceived) + " cNACKReceived: " + QString::number(cNACKReceived);

                        if(ui->wServiceSetup->logPathEnabled())
                            ui->wServiceSetup->commandLog(str);
                        else if(ui->wServiceSetup->internalLogData())
                        {
                            qDebug()<<"First Time";
                            ui->wServiceSetup->commandLog(str);
                        }
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
                        qDebug()<<"MCU Version from MCU:"<<str;
                        ui->wServiceSetup->setVersion(str);

                        QString Vstr = ui->wServiceSetup->FWVersion() + "MCU Version from MCU: "+ str;
                        if(ui->wServiceSetup->logPathEnabled())
                            ui->wServiceSetup->commandLog(Vstr);
                        else if(ui->wServiceSetup->internalLogData())
                        {
                            qDebug()<<"First Time";
                            ui->wServiceSetup->commandLog(Vstr);
                        }
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
    /*cDateTime = QDateTime::currentDateTime().addSecs(ui->wGeneralSetup->getGMTSeconds());

    ui->lblDate->setText(cDateTime.toString(qslShowDateFormat.at(ui->wGeneralSetup->general_setup.date_format)));
    ui->lblTime->setText(cDateTime.toString(qslShowTimeFormat.at(ui->wGeneralSetup->general_setup.time_format)));*/

    if(ui->wGeneralSetup->getTabDateTimeVisible())
    {
        ui->wGeneralSetup->call_on_twOther_currentChanged(false);
    }

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

                    if(rinsing)
                    {
                        if((ui->wMeasuring1->getMethod() == M_METHOD_D5188) || (ui->wMeasuring1->getMethod() == M_METHOD_D5191) || (ui->wMeasuring1->getMethod() == M_METHOD_D6378)){
                            handleRinsing();
                        }else{
                            handleInjectRinsing();
                        }
                    }
                    else if(ui->wMeasuring1->getMethod() == M_METHOD_D5188)
                    {
                        handleD5188();

                    }else if(ui->wMeasuring1->getMethod() == M_METHOD_D6377)
                    {
                        handleD6377();

                    }else if((ui->wMeasuring1->getMethod() == M_METHOD_FREE1) && (ui->wMethodSetup->stdFree1.shaker_disabled))
                    {
                        handleFreeShaker();
                    }else if((ui->wMeasuring1->getMethod() == M_METHOD_FREE2) && (ui->wMethodSetup->stdFree2.shaker_disabled))
                    {
                        handleFreeShaker();
                    }else if((ui->wMeasuring1->getMethod() == M_METHOD_FREE3) && (ui->wMethodSetup->stdFree3.shaker_disabled))
                    {
                        handleFreeShaker();
                    }else if((ui->wMeasuring1->getMethod() == M_METHOD_FREE4) && (ui->wMethodSetup->stdFree4.shaker_disabled))
                    {
                        handleFreeShaker();
                    }else if((ui->wMeasuring1->getMethod() == M_METHOD_D5191) && (ui->wMethodSetup->stdD5191.single_expansion))
                    {
                        handleD5191SingleExpansion();
                    }else{
                        handleOther();
                    }
                }
            }
            else
            {
                if(rinsing)
                {
                    if((ui->wMeasuring1->getMethod() == M_METHOD_D5188) || (ui->wMeasuring1->getMethod() == M_METHOD_D5191) || (ui->wMeasuring1->getMethod() == M_METHOD_D6378)){
                        handleRinsing();
                    }else{
                        handleInjectRinsing();
                    }
                }
                else if(ui->wMeasuring1->getMethod() == M_METHOD_D5188)
                    handleD5188();
                else if(ui->wMeasuring1->getMethod() == M_METHOD_D6377)
                        handleD6377();
                else if((ui->wMeasuring1->getMethod() == M_METHOD_FREE1) && (ui->wMethodSetup->stdFree1.shaker_disabled))
                {
                    handleFreeShaker();
                }else if((ui->wMeasuring1->getMethod() == M_METHOD_FREE2) && (ui->wMethodSetup->stdFree2.shaker_disabled))
                {
                    handleFreeShaker();
                }else if((ui->wMeasuring1->getMethod() == M_METHOD_FREE3) && (ui->wMethodSetup->stdFree3.shaker_disabled))
                {
                    handleFreeShaker();
                }else if((ui->wMeasuring1->getMethod() == M_METHOD_FREE4) && (ui->wMethodSetup->stdFree4.shaker_disabled))
                {
                    handleFreeShaker();
                }else if((ui->wMeasuring1->getMethod() == M_METHOD_D5191) && (ui->wMethodSetup->stdD5191.single_expansion))
                {
                    handleD5191SingleExpansion();
                }else{
                    handleOther();
                }
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
            ui->imageCapture->resize(167,41);
            ui->imageCapture->move(20,889);
            ui->imageCapture->show();

            if(init)
            {
                cAutoCycles = 0;

                if(ui->wMemory->getMemoryCount() >= M_MEMORY_COUNT)
                {
                    onGetConfirmation(M_CONFIRM_MEASURE_WITHOUT_SAVING, M_MEASURING);
                    return;
                }
            }

            double temp;
            switch(ui->wMeasuring1->getMethod())
            {
                case M_METHOD_D6377: temp = ui->wMethodSetup->stdD6377.InjectTemp;
                break;

                case M_METHOD_FREE1: temp = ui->wMethodSetup->stdFree1.InjectTemp;
                break;

                case M_METHOD_FREE2: temp = ui->wMethodSetup->stdFree2.InjectTemp;
                break;

                case M_METHOD_FREE3: temp = ui->wMethodSetup->stdFree3.InjectTemp;
                break;

                case M_METHOD_FREE4: temp = ui->wMethodSetup->stdFree4.InjectTemp;
                break;

                default : temp = 20.0;
                break;
            }
            tc = cSettings.getTemperatureCount(temp);
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

        case MS_RINSING_STOP:
        case MS_TEST_STOP:

            qDebug() << "TMO Reset";

            cIdleTimeout = 0;
            cStrringErrorCount = 0;

            //ui->wMeasuring1->setIdleTimer(cIdleTimeout);

            ui->wMenuBar->setSelectedMenu(M_MEASURING);
            //onSendCommand(cProtocol.sendMeasuring(0, tc));

            double temp;
            switch(ui->wMeasuring1->getMethod())
            {
                case M_METHOD_D6377: temp = ui->wMethodSetup->stdD6377.InjectTemp;
                break;

                case M_METHOD_FREE1: temp = ui->wMethodSetup->stdFree1.InjectTemp;
                break;

                case M_METHOD_FREE2: temp = ui->wMethodSetup->stdFree2.InjectTemp;
                break;

                case M_METHOD_FREE3: temp = ui->wMethodSetup->stdFree3.InjectTemp;
                break;

                case M_METHOD_FREE4: temp = ui->wMethodSetup->stdFree4.InjectTemp;
                break;

                default : temp = 20.0;
                break;
            }
            tc = cSettings.getTemperatureCount(temp);

            cAccessWidget = ui->wMeasuring1;
            cAccessWidget->setWaitACKStatus(true);
            sendPara(cProtocol.sendMeasuring(0, tc), -2, 60*12);

        break;

        case MS_RINSING_RUN:

        if(cInitSuccess)
        {
            double temp;
            switch(ui->wMeasuring1->getMethod())
            {
                case M_METHOD_D6377: temp = ui->wMethodSetup->stdD6377.InjectTemp;
                break;

                case M_METHOD_FREE1: temp = ui->wMethodSetup->stdFree1.InjectTemp;
                break;

                case M_METHOD_FREE2: temp = ui->wMethodSetup->stdFree2.InjectTemp;
                break;

                case M_METHOD_FREE3: temp = ui->wMethodSetup->stdFree3.InjectTemp;
                break;

                case M_METHOD_FREE4: temp = ui->wMethodSetup->stdFree4.InjectTemp;
                break;

                default : temp = 20.0;
                break;
            }
            tc = cSettings.getTemperatureCount(temp);
            rinsing = true;
            ui->wMeasuring1->setRunning(true);
            ui->wMenuBar->setRunningMenu(M_MEASURING);

            cRinseCycles = 0; 
            ui->wCleaning->updateStatus(cRinseCycles + 1, ui->wUserSetup->user_setup.rinse_cycle + 1);

            cAccessWidget = ui->wMeasuring1;
            cAccessWidget->setWaitACKStatus(true);

            sendPara(cProtocol.sendMeasuringStart(0, tc), 2, 60*12);

        }
        else
        {
            onShowMsgBox("Information", "Initial test failed\nRinsing can not be started!");
        }

        break;

        /*case MS_RINSING_STOP:

            qDebug() << "TMO Reset";
            cIdleTimeout = 0;

            //ui->wMeasuring1->setIdleTimer(cIdleTimeout);

            ui->wCleaning->setRunning(false);
            ui->wMenuBar->setSelectedMenu(M_CLEANING);

            cAccessWidget = ui->wCleaning;
            cAccessWidget->setWaitACKStatus(true);
            sendPara(cProtocol.sendMeasuring(0, tc), -2, 60*12);

        break;*/

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

    QString str = "onSendCommand:" + cmd;

    QString logMethod;
    QString currentTab;

    if(ui->wMeasuring1->isVisible())
    {
        switch(ui->wMeasuring1->getMethod())
        {
        case M_METHOD_D5191: logMethod = "D5191 ";
            break;

        case M_METHOD_D6377: logMethod = "D6377 ";
            break;

        case M_METHOD_D6378: logMethod = "D6378 ";
            break;

        case M_METHOD_D5188: logMethod = "D5188 ";
            break;

        case M_METHOD_FREE1: logMethod = "Free1 ";
            break;

        case M_METHOD_FREE2: logMethod = "Free2 ";
            break;

        case M_METHOD_FREE3: logMethod = "Free3 ";
            break;

        case M_METHOD_FREE4: logMethod = "Free4 ";
            break;

        default: logMethod = " ";
            break;
        }
    }
    if(ui->wUserSetup->isVisible())
        currentTab = "User Tab ";
    if(ui->wMemory->isVisible())
        currentTab = "Memory Tab ";
    if(ui->wGeneralSetup->isVisible())
        currentTab = "General SetUp Tab ";
    if(ui->wMethodSetup->isVisible())
        currentTab = "Method SetUp Tab ";
    if(ui->wServiceSetup->isVisible())
        currentTab = "Service Tab ";
    if(ui->wCalibrationSetup->isVisible())
        currentTab = "Calibration Tab ";

    if(ui->wServiceSetup->logPathEnabled())
        ui->wServiceSetup->commandLog(currentTab + logMethod + str);
    else if(ui->wServiceSetup->internalLogData())
    {
        qDebug()<<"First Time";
        ui->wServiceSetup->commandLog(str);
    }

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

    QString str = "onSendCommand SA:" + cmd;

    QString logMethod;
    QString currentTab;

    if(ui->wMeasuring1->isVisible())
    {
        switch(ui->wMeasuring1->getMethod())
        {
        case M_METHOD_D5191: logMethod = "D5191 ";
            break;

        case M_METHOD_D6377: logMethod = "D6377 ";
            break;

        case M_METHOD_D6378: logMethod = "D6378 ";
            break;

        case M_METHOD_D5188: logMethod = "D5188 ";
            break;

        case M_METHOD_FREE1: logMethod = "Free1 ";
            break;

        case M_METHOD_FREE2: logMethod = "Free2 ";
            break;

        case M_METHOD_FREE3: logMethod = "Free3 ";
            break;

        case M_METHOD_FREE4: logMethod = "Free4 ";
            break;

        default: logMethod = " ";
            break;
        }
    }
    if(ui->wUserSetup->isVisible())
        currentTab = "User Tab ";
    if(ui->wMemory->isVisible())
        currentTab = "Memory Tab ";
    if(ui->wGeneralSetup->isVisible())
        currentTab = "General SetUp Tab ";
    if(ui->wMethodSetup->isVisible())
        currentTab = "Method SetUp Tab ";
    if(ui->wServiceSetup->isVisible())
        currentTab = "Service Tab ";
    if(ui->wCalibrationSetup->isVisible())
        currentTab = "Calibration Tab ";

    if(ui->wServiceSetup->logPathEnabled())
        ui->wServiceSetup->commandLog((currentTab + logMethod + str));
    else if(ui->wServiceSetup->internalLogData())
    {
        qDebug()<<"First Time";
        ui->wServiceSetup->commandLog(str);
    }
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

        QString str = "sendPara:" + tmp + "cStage:" + QString::number(stage) + "T:" + QString::number(timeout);

        QString logMethod;
        QString currentTab;

        if(ui->wMeasuring1->isVisible())
        {
            switch(ui->wMeasuring1->getMethod())
            {
            case M_METHOD_D5191: logMethod = "D5191 ";
                break;

            case M_METHOD_D6377: logMethod = "D6377 ";
                break;

            case M_METHOD_D6378: logMethod = "D6378 ";
                break;

            case M_METHOD_D5188: logMethod = "D5188 ";
                break;

            case M_METHOD_FREE1: logMethod = "Free1 ";
                break;

            case M_METHOD_FREE2: logMethod = "Free2 ";
                break;

            case M_METHOD_FREE3: logMethod = "Free3 ";
                break;

            case M_METHOD_FREE4: logMethod = "Free4 ";
                break;

            default: logMethod = " ";
                break;
            }
        }
        if(ui->wUserSetup->isVisible())
            currentTab = "User Tab ";
        if(ui->wMemory->isVisible())
            currentTab = "Memory Tab ";
        if(ui->wGeneralSetup->isVisible())
            currentTab = "General SetUp Tab ";
        if(ui->wMethodSetup->isVisible())
            currentTab = "Method SetUp Tab ";
        if(ui->wServiceSetup->isVisible())
            currentTab = "Service Tab ";
        if(ui->wCalibrationSetup->isVisible())
            currentTab = "Calibration Tab ";

        if(ui->wServiceSetup->logPathEnabled())
            ui->wServiceSetup->commandLog(currentTab + logMethod + str);
        else if(ui->wServiceSetup->internalLogData())
        {
            qDebug()<<"First Time";
            ui->wServiceSetup->commandLog(str);
        }
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
    if(cStage <= 7 )
    {
        if((ui->wMeasuring1->getMethod() == M_METHOD_D5188) || (ui->wMeasuring1->getMethod() == M_METHOD_D5191) || (ui->wMeasuring1->getMethod() == M_METHOD_D6378)){
            handleRinsing();
        }else{
            handleInjectRinsing();
        }
    }
    else
    {

        switch(cStage)
        {
            case 8:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_IN)
                        {
                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_D5191: cVolume = qRound((ui->wCalibrationSetup->cCalibD5191.StageVolume)*100);
                                                     deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_D6378: cVolume = qRound((ui->wCalibrationSetup->cCalibD6378.StageVolume)*100);
                                                     deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_FREE1: cVolume = qRound((ui->wCalibrationSetup->cCalibFree1.StageVolume)*100);
                                                     deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_FREE2: cVolume = qRound((ui->wCalibrationSetup->cCalibFree2.StageVolume)*100);
                                                     deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_FREE3: cVolume = qRound((ui->wCalibrationSetup->cCalibFree3.StageVolume)*100);
                                                     deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_FREE4: cVolume = qRound((ui->wCalibrationSetup->cCalibFree4.StageVolume)*100);
                                                     deltaVolume = 100 - cVolume;
                                break;

                                default : cVolume = 100;
                                          deltaVolume = 100 - cVolume;
                                break;
                            }

                            sendPara(cProtocol.sendPistonPosition(cVolume), 9, 60);

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

            case 9:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                     10, 60);

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

            case 10:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_CLOSED)
                        {
                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_D5191: cVolume = qRound((ui->wCalibrationSetup->cCalibD5191.FirstVolume)*100) - deltaVolume;
                                                    deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_D6378: cVolume = qRound((ui->wCalibrationSetup->cCalibD6378.FirstVolume)*100) - deltaVolume;
                                                    deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_FREE1: cVolume = qRound((ui->wCalibrationSetup->cCalibFree1.FirstVolume)*100) - deltaVolume;
                                                    deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_FREE2: cVolume = qRound((ui->wCalibrationSetup->cCalibFree2.FirstVolume)*100) - deltaVolume;
                                                    deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_FREE3: cVolume = qRound((ui->wCalibrationSetup->cCalibFree3.FirstVolume)*100) - deltaVolume;
                                                    deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_FREE4: cVolume = qRound((ui->wCalibrationSetup->cCalibFree4.FirstVolume)*100) - deltaVolume;
                                                    deltaVolume = (170-cVolume);
                                break;

                                default : cVolume = 170 - deltaVolume;
                                            deltaVolume = (170-cVolume);
                                break;
                            }
                            sendPara(cProtocol.sendPistonPosition(cVolume), 11, 60);

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

            case 11:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
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

                            cTmTest = cTmTest+2;

                            int tc = cSettings.getTemperatureCount(cTmTest);

                            sendPara(cProtocol.sendTemperature(tc),
                                     12, cREqTime + M_EQUILIBRIUM_TIME_OUT);


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
            case 12:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
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
                                     13, cREqTime + M_EQUILIBRIUM_TIME_OUT);


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
                                setError(M_ERROR_TEMPERATURE);
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

                            ui->wMeasuring1->setLblMessage(tr("Measurement in progress \n Expansion 1/3"));

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx1= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);
                                switch(ui->wMeasuring1->getMethod())
                                {
                                    case M_METHOD_D5191: cVolume = qRound((ui->wCalibrationSetup->cCalibD5191.SecondVolume)*100) - deltaVolume;
                                                        deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_D6378: cVolume = qRound((ui->wCalibrationSetup->cCalibD6378.SecondVolume)*100) - deltaVolume;
                                                        deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_FREE1: cVolume = qRound((ui->wCalibrationSetup->cCalibFree1.SecondVolume)*100) - deltaVolume;
                                                        deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_FREE2: cVolume = qRound((ui->wCalibrationSetup->cCalibFree2.SecondVolume)*100) - deltaVolume;
                                                        deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_FREE3: cVolume = qRound((ui->wCalibrationSetup->cCalibFree3.SecondVolume)*100) - deltaVolume;
                                                        deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_FREE4: cVolume = qRound((ui->wCalibrationSetup->cCalibFree4.SecondVolume)*100) - deltaVolume;
                                                        deltaVolume = (250-cVolume);
                                    break;

                                    default : cVolume = 250 - deltaVolume;
                                            deltaVolume = (250-cVolume);
                                    break;
                                }
                                sendPara(cProtocol.sendPistonPosition(cVolume), 14, 60);

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

            case 14:
                {
                    cParasUpdated = false;

                    if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                    {
                        switch(ui->wMeasuring1->getMethod())
                        {
                            case M_METHOD_FREE1: cREqTime = ui->wMethodSetup->stdFree1.tpx2; break;
                            case M_METHOD_FREE2: cREqTime = ui->wMethodSetup->stdFree2.tpx2; break;
                            case M_METHOD_FREE3: cREqTime = ui->wMethodSetup->stdFree3.tpx2; break;
                            case M_METHOD_FREE4: cREqTime = ui->wMethodSetup->stdFree4.tpx2; break;
                            default : cREqTime = 60; break;
                        }

                        cStage = 15;
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

            case 15:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
                        {
                            cEqTime++;

                            ui->wMeasuring1->setLblMessage(tr("Measurement in progress \n Expansion 2/3"));

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx2= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);
                                switch(ui->wMeasuring1->getMethod())
                                {
                                    case M_METHOD_D5191: cVolume = qRound((ui->wCalibrationSetup->cCalibD5191.ThirdVOlume)*100) - deltaVolume;
                                                        deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_D6378: cVolume = qRound((ui->wCalibrationSetup->cCalibD6378.ThirdVOlume)*100) - deltaVolume;
                                                        deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_FREE1: cVolume = qRound((ui->wCalibrationSetup->cCalibFree1.ThirdVOlume)*100) - deltaVolume;
                                                        deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_FREE2: cVolume = qRound((ui->wCalibrationSetup->cCalibFree2.ThirdVOlume)*100) - deltaVolume;
                                                        deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_FREE3: cVolume = qRound((ui->wCalibrationSetup->cCalibFree3.ThirdVOlume)*100) - deltaVolume;
                                                        deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_FREE4: cVolume = qRound((ui->wCalibrationSetup->cCalibFree4.ThirdVOlume)*100) - deltaVolume;
                                                        deltaVolume = (500-cVolume);
                                    break;

                                    default : cVolume = 500 - deltaVolume;
                                            deltaVolume = (500-cVolume);
                                    break;
                                }
                                sendPara(cProtocol.sendPistonPosition(cVolume), 16, 60);

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

            case 16:
                    {
                        cParasUpdated = false;

                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                        {
                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_FREE1: cREqTime = ui->wMethodSetup->stdFree1.tpx3; break;
                                case M_METHOD_FREE2: cREqTime = ui->wMethodSetup->stdFree2.tpx3; break;
                                case M_METHOD_FREE3: cREqTime = ui->wMethodSetup->stdFree3.tpx3; break;
                                case M_METHOD_FREE4: cREqTime = ui->wMethodSetup->stdFree4.tpx3; break;
                                default : cREqTime = 60; break;
                            }

                            cStage = 17;
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

            case 17:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
                        {
                            cEqTime++;

                            ui->wMeasuring1->setLblMessage(tr("Measurement in progress \n Expansion 3/3"));

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx3= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                                ui->wMeasuring1->setStatus("");

                                ui->imageCapture->resize(167,25);
                                ui->imageCapture->move(20,900);
                                ui->imageCapture->show();

                                if(ui->wMeasuring1->getMethod() == M_METHOD_D5191)
                                    ui->wMeasuring1->showResultD5191(cPrTpx1, cPrTpx2, cPrTpx3);
                                else if(ui->wMeasuring1->getMethod() == M_METHOD_D6378)
                                    ui->wMeasuring1->showResultD6378(cPrTpx1, cPrTpx2, cPrTpx3);
                                else
                                    ui->wMeasuring1->showResultFree(cPrTpx1, cPrTpx2, cPrTpx3);

                                ui->wServiceSetup->incrementCount();

                                switch(ui->wMeasuring1->getMethod())
                                {
                                case M_METHOD_FREE1: cTmTest = ui->wMethodSetup->stdFree1.InjectTemp;
                                    break;

                                case M_METHOD_FREE2: cTmTest = ui->wMethodSetup->stdFree2.InjectTemp;
                                    break;

                                case M_METHOD_FREE3: cTmTest = ui->wMethodSetup->stdFree3.InjectTemp;
                                    break;

                                case M_METHOD_FREE4: cTmTest = ui->wMethodSetup->stdFree4.InjectTemp;
                                    break;

                                default : cTmTest = 20.0;
                                    break;
                                }
                                int tc = cSettings.getTemperatureCount(cTmTest);

                                sendPara( cProtocol.sendTemperature(tc),
                                         18, 60*12);

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

            case 18:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if(((ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE))) && cStageTimeOut <=700)
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST),
                                     19, 60);

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
//                                        if(ui->wMethodSetup->stdD5191.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_D6378:
//                                        if(ui->wMethodSetup->stdD6378.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE1:
//                                        if(ui->wMethodSetup->stdFree1.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE2:
//                                        if(ui->wMethodSetup->stdFree2.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE3:
//                                        if(ui->wMethodSetup->stdFree3.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE4:
//                                        if(ui->wMethodSetup->stdFree4.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;
                                }
                            }

                        }
                    }

                    break;

            case 19:
                    {
                        cParasUpdated = false;

                        if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                        {
                            sendPara(cProtocol.sendPistonPosition(0), 20, 60);
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

            case 20:
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

void MainWindow::handleFreeShaker(void)
{
    if(cStage <= 7 )
    {
        if((ui->wMeasuring1->getMethod() == M_METHOD_D5188) || (ui->wMeasuring1->getMethod() == M_METHOD_D5191) || (ui->wMeasuring1->getMethod() == M_METHOD_D6378)){
            handleRinsing();
        }else{
            handleInjectRinsing();
        }
    }
    else
    {

        switch(cStage)
        {
            case 8:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_IN)
                        {
                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_D5191: cVolume = qRound((ui->wCalibrationSetup->cCalibD5191.StageVolume)*100);
                                                    deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_D6378: cVolume = qRound((ui->wCalibrationSetup->cCalibD6378.StageVolume)*100);
                                                    deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_FREE1: cVolume = qRound((ui->wCalibrationSetup->cCalibFree1.StageVolume)*100);
                                                    deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_FREE2: cVolume = qRound((ui->wCalibrationSetup->cCalibFree2.StageVolume)*100);
                                                    deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_FREE3: cVolume = qRound((ui->wCalibrationSetup->cCalibFree3.StageVolume)*100);
                                                    deltaVolume = 100 - cVolume;
                                break;

                                case M_METHOD_FREE4: cVolume = qRound((ui->wCalibrationSetup->cCalibFree4.StageVolume)*100);
                                                    deltaVolume = 100 - cVolume;
                                break;

                                default : cVolume = 100;
                                        deltaVolume = 100 - cVolume;
                                break;
                            }
                            sendPara(cProtocol.sendPistonPosition(cVolume), 9, 60);

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

            case 9:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                     10, 60);

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

            case 10:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_CLOSED)
                        {
                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_D5191: cVolume = qRound((ui->wCalibrationSetup->cCalibD5191.FirstVolume)*100) - deltaVolume;
                                deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_D6378: cVolume = qRound((ui->wCalibrationSetup->cCalibD6378.FirstVolume)*100) - deltaVolume;
                                deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_FREE1: cVolume = qRound((ui->wCalibrationSetup->cCalibFree1.FirstVolume)*100) - deltaVolume;
                                deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_FREE2: cVolume = qRound((ui->wCalibrationSetup->cCalibFree2.FirstVolume)*100) - deltaVolume;
                                deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_FREE3: cVolume = qRound((ui->wCalibrationSetup->cCalibFree3.FirstVolume)*100) - deltaVolume;
                                deltaVolume = (170-cVolume);
                                break;

                                case M_METHOD_FREE4: cVolume = qRound((ui->wCalibrationSetup->cCalibFree4.FirstVolume)*100) - deltaVolume;
                                deltaVolume = (170-cVolume);
                                break;

                                default : cVolume = 170 - deltaVolume;
                                deltaVolume = (170-cVolume);
                                break;
                            }
                            sendPara(cProtocol.sendPistonPosition(cVolume), 11, 60);

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

            case 11:
                    {
                        cParasUpdated = false;

                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                        {

                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_FREE1: shakerSpeed = ui->wMethodSetup->stdFree1.shaker_speed;
                                break;

                                case M_METHOD_FREE2: shakerSpeed = ui->wMethodSetup->stdFree2.shaker_speed;
                                break;

                                case M_METHOD_FREE3: shakerSpeed = ui->wMethodSetup->stdFree3.shaker_speed;
                                break;

                                case M_METHOD_FREE4: shakerSpeed = ui->wMethodSetup->stdFree4.shaker_speed;
                                break;

                                default : shakerSpeed = 90;
                                break;
                            }

                            sendPara(cProtocol.sendShakerSpeed(1, shakerSpeed), 12, 60);
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

            case 12:
                    {
                        cParasUpdated = false;
                        if((cStepperSpeed <= shakerSpeed+5) && (cStepperSpeed >= shakerSpeed-5))
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

                            cTmTest = cTmTest + 2;

                            int tc = cSettings.getTemperatureCount(cTmTest);

                            sendPara(cProtocol.sendTemperature(tc),
                                     13, cREqTime + M_EQUILIBRIUM_TIME_OUT);


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
                                setError(M_ERROR_SHAKER_MOTOR);
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
                                     14, cREqTime + M_EQUILIBRIUM_TIME_OUT);


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
                                setError(M_ERROR_TEMPERATURE);
                            }
                            else cStageTimeOut--;
                        }
                    }

                    break;
            case 14:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
                        {
                            cEqTime++;

                            ui->wMeasuring1->setLblMessage(tr("Measurement in progress \n Expansion 1/3"));

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx1= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);
                                switch(ui->wMeasuring1->getMethod())
                                {
                                    case M_METHOD_D5191: cVolume = qRound((ui->wCalibrationSetup->cCalibD5191.SecondVolume)*100) - deltaVolume;
                                    deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_D6378: cVolume = qRound((ui->wCalibrationSetup->cCalibD6378.SecondVolume)*100) - deltaVolume;
                                    deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_FREE1: cVolume = qRound((ui->wCalibrationSetup->cCalibFree1.SecondVolume)*100) - deltaVolume;
                                    deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_FREE2: cVolume = qRound((ui->wCalibrationSetup->cCalibFree2.SecondVolume)*100) - deltaVolume;
                                    deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_FREE3: cVolume = qRound((ui->wCalibrationSetup->cCalibFree3.SecondVolume)*100) - deltaVolume;
                                    deltaVolume = (250-cVolume);
                                    break;

                                    case M_METHOD_FREE4: cVolume = qRound((ui->wCalibrationSetup->cCalibFree4.SecondVolume)*100) - deltaVolume;
                                    deltaVolume = (250-cVolume);
                                    break;

                                    default : cVolume = 250 - deltaVolume;
                                    deltaVolume = (250-cVolume);
                                    break;
                                }
                                sendPara(cProtocol.sendPistonPosition(cVolume), 15, 60);

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

            case 15:
                {
                    cParasUpdated = false;

                    if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                    {
                        switch(ui->wMeasuring1->getMethod())
                        {
                            case M_METHOD_FREE1: cREqTime = ui->wMethodSetup->stdFree1.tpx2; break;
                            case M_METHOD_FREE2: cREqTime = ui->wMethodSetup->stdFree2.tpx2; break;
                            case M_METHOD_FREE3: cREqTime = ui->wMethodSetup->stdFree3.tpx2; break;
                            case M_METHOD_FREE4: cREqTime = ui->wMethodSetup->stdFree4.tpx2; break;
                            default : cREqTime = 60; break;
                        }

                        cStage = 16;
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

            case 16:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
                        {
                            cEqTime++;

                            ui->wMeasuring1->setLblMessage(tr("Measurement in progress \n Expansion 2/3"));

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx2= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);
                                switch(ui->wMeasuring1->getMethod())
                                {
                                    case M_METHOD_D5191: cVolume = qRound((ui->wCalibrationSetup->cCalibD5191.ThirdVOlume)*100) - deltaVolume;
                                    deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_D6378: cVolume = qRound((ui->wCalibrationSetup->cCalibD6378.ThirdVOlume)*100) - deltaVolume;
                                    deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_FREE1: cVolume = qRound((ui->wCalibrationSetup->cCalibFree1.ThirdVOlume)*100) - deltaVolume;
                                    deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_FREE2: cVolume = qRound((ui->wCalibrationSetup->cCalibFree2.ThirdVOlume)*100) - deltaVolume;
                                    deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_FREE3: cVolume = qRound((ui->wCalibrationSetup->cCalibFree3.ThirdVOlume)*100) - deltaVolume;
                                    deltaVolume = (500-cVolume);
                                    break;

                                    case M_METHOD_FREE4: cVolume = qRound((ui->wCalibrationSetup->cCalibFree4.ThirdVOlume)*100) - deltaVolume;
                                    deltaVolume = (500-cVolume);
                                    break;

                                    default : cVolume = 500 - deltaVolume;
                                    deltaVolume = (500-cVolume);
                                    break;
                                }
                                sendPara(cProtocol.sendPistonPosition(cVolume), 17, 60);

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

            case 17:
                    {
                        cParasUpdated = false;

                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                        {
                            switch(ui->wMeasuring1->getMethod())
                            {
                                case M_METHOD_FREE1: cREqTime = ui->wMethodSetup->stdFree1.tpx3; break;
                                case M_METHOD_FREE2: cREqTime = ui->wMethodSetup->stdFree2.tpx3; break;
                                case M_METHOD_FREE3: cREqTime = ui->wMethodSetup->stdFree3.tpx3; break;
                                case M_METHOD_FREE4: cREqTime = ui->wMethodSetup->stdFree4.tpx3; break;
                                default : cREqTime = 60; break;
                            }

                            cStage = 18;
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

            case 18:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
                        {
                            cEqTime++;

                            ui->wMeasuring1->setLblMessage(tr("Measurement in progress \n Expansion 3/3"));

                            if(cEqTime >= cREqTime)
                            {
                                cEqTime = 0;
                                sendPara(cProtocol.sendShakerSpeed(0, 0), 19, 60);
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

            case 19:
                    {
                        cParasUpdated = false;

                        if((cStepperSpeed == 0))
                        {
//                            cEqTime++;

//                            if(cEqTime >= cREqTime)
                            if(1)
                            {
                                cPrTpx3= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                                ui->wMeasuring1->setStatus("");

                                ui->imageCapture->resize(167,25);
                                ui->imageCapture->move(20,900);
                                ui->imageCapture->show();

                                if(ui->wMeasuring1->getMethod() == M_METHOD_D5191)
                                    ui->wMeasuring1->showResultD5191(cPrTpx1, cPrTpx2, cPrTpx3);
                                else if(ui->wMeasuring1->getMethod() == M_METHOD_D6378)
                                    ui->wMeasuring1->showResultD6378(cPrTpx1, cPrTpx2, cPrTpx3);
                                else
                                    ui->wMeasuring1->showResultFree(cPrTpx1, cPrTpx2, cPrTpx3);

                                ui->wServiceSetup->incrementCount();

                                switch(ui->wMeasuring1->getMethod())
                                {
                                case M_METHOD_FREE1: cTmTest = ui->wMethodSetup->stdFree1.InjectTemp;
                                    break;

                                case M_METHOD_FREE2: cTmTest = ui->wMethodSetup->stdFree2.InjectTemp;
                                    break;

                                case M_METHOD_FREE3: cTmTest = ui->wMethodSetup->stdFree3.InjectTemp;
                                    break;

                                case M_METHOD_FREE4: cTmTest = ui->wMethodSetup->stdFree4.InjectTemp;
                                    break;

                                default : cTmTest = 20.0;
                                    break;
                                }
                                int tc = cSettings.getTemperatureCount(cTmTest);
                                sendPara( cProtocol.sendTemperature(tc),
                                          20, 60*12);

                                if(ui->wServiceSetup->getDebug())
                                    ui->wMeasuring1->setStatus(STRING_MEASURING_COOLING + cSettings.getTemperature(tc));
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
                            setError(M_ERROR_SHAKER_MOTOR);
                        }
                        else cStageTimeOut--;

                    }

                    break;

            case 20:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if(((ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE))) && cStageTimeOut <=700)
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST),
                                     21, 60);

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
                                    case M_METHOD_FREE1:
//                                        if(ui->wMethodSetup->stdFree1.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE2:
//                                        if(ui->wMethodSetup->stdFree2.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE3:
//                                        if(ui->wMethodSetup->stdFree3.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE4:
//                                        if(ui->wMethodSetup->stdFree4.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;
                                }
                            }

                        }
                    }

                    break;

            case 21:
                    {
                        cParasUpdated = false;

                        if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                        {
                            sendPara(cProtocol.sendPistonPosition(0), 22, 60);
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

            case 22:
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

void MainWindow::handleD5191SingleExpansion(void)
{
    if(cStage <= 7 )
    {
        handleRinsing();
    }
    else
    {

        switch(cStage)
        {

            case 8:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_IN)
                        {
                            cVolume = qRound((ui->wCalibrationSetup->cCalibSingleD5191.StageVolume)*100);
                            deltaVolume = 100 - cVolume;
                            sendPara(cProtocol.sendPistonPosition(cVolume), 9, 60);

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

            case 9:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                     10, 60);

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

            case 10:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_CLOSED)
                        {
                            cVolume = qRound((ui->wCalibrationSetup->cCalibSingleD5191.FirstVolume)*100) - deltaVolume;
                            sendPara(cProtocol.sendPistonPosition(cVolume), 11, 60);

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_MOVING_PISTON_5_ML);

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

            case 11:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
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

                                default : cREqTime = 240;
                                          cTmTest = 37.80;
                                break;
                            }

                            cTmTest = cTmTest + 2;

                            int tc = cSettings.getTemperatureCount(cTmTest);

                            sendPara(cProtocol.sendTemperature(tc),
                                     12, cREqTime + M_EQUILIBRIUM_TIME_OUT);


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

            case 12:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( ( ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE )))
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

                                default : cREqTime = 240;
                                          cTmTest = 37.80;
                                break;
                            }

                            int tc = cSettings.getTemperatureCount(cTmTest);

                            sendPara(cProtocol.sendTemperature(tc),
                                     13, cREqTime + M_EQUILIBRIUM_TIME_OUT);


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
                                setError(M_ERROR_TEMPERATURE);
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

                            ui->wMeasuring1->setLblMessage(tr("Measurement in progress \n Expansion 1/1"));
                            if(cEqTime%60==0){
                                p3 = p2;
                                p2 = p1;
                                p1 = cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);
                                qDebug()<<"p1: "<<p1<<" p2: "<<p2<<" p3: ";
                            }

                            if(cEqTime >= cREqTime)
                            {
                                cPrTpx1= cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                                ui->imageCapture->resize(167,25);
                                ui->imageCapture->move(20,900);
                                ui->imageCapture->show();

                                ui->wMeasuring1->showResultD5191Single(cPrTpx1);
                                ui->wServiceSetup->incrementCount();

                                sendPara( cProtocol.sendTemperature(cSettings.getTemperatureCount(20)),
                                          14, 60*12);

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

            case 14:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if(((ctmp >= (20 - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (20 + M_TEMPERATURE_TOLERANCE))) && cStageTimeOut <=700)
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

                            if(cStageTimeOut == 710)
                            {
                                switch(ui->wMeasuring1->getMethod())
                                {
                                    case M_METHOD_D5191:
//                                        if(ui->wMethodSetup->stdD5191.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_D6378:
//                                        if(ui->wMethodSetup->stdD6378.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE1:
//                                        if(ui->wMethodSetup->stdFree1.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE2:
//                                        if(ui->wMethodSetup->stdFree2.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE3:
//                                        if(ui->wMethodSetup->stdFree3.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;

                                    case M_METHOD_FREE4:
//                                        if(ui->wMethodSetup->stdFree4.alarm_enabled)
                                        if(ui->wUserSetup->user_setup.alarm_buzzer_enable)
                                            onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                                    break;
                                }
                            }

                        }
                    }

                    break;

            case 15:
                    {
                        cParasUpdated = false;

                        if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                        {
                            sendPara(cProtocol.sendPistonPosition(0), 16, 60);
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
            ui->wServiceSetup->sInitDone = false;

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

    if( cStage <= 7 )
    {
        handleRinsing();
    }
    else
    {
        switch(cStage)
        {
            case 8:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_IN)
                        {
                            cVolume = qRound((ui->wCalibrationSetup->cCalibD5188.StageVolume)*100);
                            deltaVolume = 25 - cVolume;
                            sendPara(cProtocol.sendPistonPosition(cVolume), 9, 60);

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

            case 9:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                     10, 60);

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

            case 10:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_CLOSED)
                        {
                            cVolume = qRound((ui->wCalibrationSetup->cCalibD5188.FirstVolume)*100) - deltaVolume;
                            sendPara(cProtocol.sendPistonPosition(cVolume), 11, 60);

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

            case 11:
                    {
                        cParasUpdated = false;
                        if((cPistonPosition <= cVolume + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cVolume - M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendShakerSpeed(1, ui->wMethodSetup->stdD5188.shaker_speed), 12, 60);
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

            case 12:
                {
                    cParasUpdated = false;

                    int D5188_Shaker_speed = ui->wMethodSetup->stdD5188.shaker_speed;

                    if((cStepperSpeed <= D5188_Shaker_speed+5) && (cStepperSpeed >= D5188_Shaker_speed-5))
                    {
                        //NNNNN

                        cPrCount = cSettings.getPressureCount(101.3);
                        //cPrTpx1 = cSettings.getTemperatureCelsius(cRawCTemperature);

                        sendPara(cProtocol.sendPressure(cPrCount), 13, 60*30);

                        QString str = QString::number(cPrCount);
                        if(ui->wServiceSetup->logPathEnabled())
                            ui->wServiceSetup->commandLog((str));
                        else if(ui->wServiceSetup->internalLogData())
                        {
                            qDebug()<<"First Time";
                            ui->wServiceSetup->commandLog(str);
                        }

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

            case 13:
                {
                    cParasUpdated = false;

                    double dtpr1 = cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure);

                    QString str = "dtpr1: " + QString::number(dtpr1);
                    if(ui->wServiceSetup->logPathEnabled())
                        ui->wServiceSetup->commandLog((str));
                    else if(ui->wServiceSetup->internalLogData())
                    {
                        qDebug()<<"First Time";
                        ui->wServiceSetup->commandLog(str);
                    }

                    if((cRawCPressure >= cPrCount-50) && (cRawCPressure <= cPrCount+50))
                    {
                        if(dtpr1 < (101.3 - 0.3))
                        {
                            str = "before sending cPrCount from (dtpr1 < (101.3 - 0.3)): " + QString::number(cPrCount);
                            if(ui->wServiceSetup->logPathEnabled())
                                ui->wServiceSetup->commandLog((str));
                            else if(ui->wServiceSetup->internalLogData())
                            {
                                qDebug()<<"First Time";
                                ui->wServiceSetup->commandLog(str);
                            }
                            cPrCount = cRawCPressure+50;
                            onSendCommand(cProtocol.sendPressure(cPrCount));

                            str = "after sending cPrCount from (dtpr1 < (101.3 - 0.3)): " + QString::number(cPrCount);
                            if(ui->wServiceSetup->logPathEnabled())
                                ui->wServiceSetup->commandLog((str));
                            else if(ui->wServiceSetup->internalLogData())
                            {
                                qDebug()<<"First Time";
                                ui->wServiceSetup->commandLog(str);
                            }

                            cREqTime = 0;
                            cEqTime = 0;
                        }
                        else if(dtpr1 > (101.3 + 0.3))
                        {
                            str = "before sending cPrCount from (dtpr1 > (101.3 + 0.3)): " + QString::number(cPrCount);
                            if(ui->wServiceSetup->logPathEnabled())
                                ui->wServiceSetup->commandLog((str));
                            else if(ui->wServiceSetup->internalLogData())
                            {
                                qDebug()<<"First Time";
                                ui->wServiceSetup->commandLog(str);
                            }
                            cPrCount = cRawCPressure-50;
                            onSendCommand(cProtocol.sendPressure(cPrCount));


                            str = "after sending cPrCount from (dtpr1 > (101.3 + 0.3)): " + QString::number(cPrCount);
                            if(ui->wServiceSetup->logPathEnabled())
                                ui->wServiceSetup->commandLog((str));
                            else if(ui->wServiceSetup->internalLogData())
                            {
                                qDebug()<<"First Time";
                                ui->wServiceSetup->commandLog(str);
                            }

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

                                ui->imageCapture->resize(167,25);
                                ui->imageCapture->move(20,900);
                                ui->imageCapture->show();

                                ui->wMeasuring1->showResultD5188(cSettings.getTemperatureCelsius(cRawCTemperature));
                                ui->wServiceSetup->incrementCount();
                                sendPara(cProtocol.sendShakerSpeed(0, 0), 14, 60);
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

            case 14:
                    {
                        cParasUpdated = false;

                        if((cStepperSpeed == 0) && (cStageTimeOut <=56))
                        {
                            sendPara( cProtocol.sendTemperature(cSettings.getTemperatureCount(20)),
                                      15, 60*18); //180+300);

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

//                            if(ui->wMethodSetup->stdD5188.alarm_enabled && cStageTimeOut == 58)
                            if(ui->wUserSetup->user_setup.alarm_buzzer_enable && cStageTimeOut == 58)
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

void MainWindow::handleD6377(void)
{

    if( cStage <= 7 )
    {
//        handleRinsing();
        handleInjectRinsing();
    }
    else
    {
        switch(cStage)
        {
            case 8:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_IN)
                        {
                            int stageVol = (int)((ui->wCalibrationSetup->cCalibD6377.StageVolume)*100);
                            deltaVolume = 100 - stageVol;
                            sendPara(cProtocol.sendPistonPosition(stageVol), 9, 60);

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

            case 9:
                    {
                        cParasUpdated = false;

                        int stageVol = (int)((ui->wCalibrationSetup->cCalibD6377.StageVolume)*100);

                        if((cPistonPosition <= stageVol+M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= stageVol-M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_CLOSED),
                                     10, 60);

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

            case 10:
                    {
                        cParasUpdated = false;
                        if(cValvePosition == M_VALVE_POSITION_CLOSED)
                        {
//                            int vl = (ui->wMethodSetup->stdD6377.vl_ratio * 100) + 100;
//                            int vl = (int)((ui->wCalibrationSetup->cCalibD6377.FirstVolume)*100);
//                            int vl = static_cast<int>(std::round((ui->wCalibrationSetup->cCalibD6377.FirstVolume) * 100));
                            int vl = qRound((ui->wCalibrationSetup->cCalibD6377.FirstVolume) * 100) - deltaVolume;
                            deltaVolume = 500 - vl;
                            qDebug()<<"(ui->wCalibrationSetup->cCalibD6377.FirstVolume): "<<(ui->wCalibrationSetup->cCalibD6377.FirstVolume);
                            qDebug()<<"(int)((ui->wCalibrationSetup->cCalibD6377.FirstVolume)*100): "<<(int)((ui->wCalibrationSetup->cCalibD6377.FirstVolume)*100);
                            qDebug()<<"vl = (int)((ui->wCalibrationSetup->cCalibD6377.FirstVolume)*100); value: "<<vl;
                            sendPara(cProtocol.sendPistonPosition(vl), 11, 60);

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

            case 11:
                    {
                        cParasUpdated = false;

//                        int cvl = (ui->wMethodSetup->stdD6377.vl_ratio * 100) + 100;
                        int cvl = qRound((ui->wCalibrationSetup->cCalibD6377.FirstVolume) * 100) - deltaVolume;

                        if((cPistonPosition <= cvl + M_PISTON_POSITION_TOLERANCE) && (cPistonPosition >= cvl - M_PISTON_POSITION_TOLERANCE))
                        {
                            sendPara(cProtocol.sendShakerSpeed(1, ui->wMethodSetup->stdD6377.shaker_speed), 12, 60);
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

            case 12:
                    {
                        cParasUpdated = false;

                        int D6377_Shaker_Speed = ui->wMethodSetup->stdD6377.shaker_speed;

                        if((cStepperSpeed <= D6377_Shaker_Speed+5) && (cStepperSpeed >= D6377_Shaker_Speed-5))
                        {
                            cREqTime = ui->wMethodSetup->stdD6377.time;

                            cTmTest = ui->wMethodSetup->stdD6377.temperature + 2;
                            int tc = cSettings.getTemperatureCount(cTmTest);

                            sendPara(cProtocol.sendTemperature(tc),
                                     13, cREqTime + M_EQUILIBRIUM_TIME_OUT);

                            qDebug()<<"cSettings.getTemperatureCount(ui->wMethodSetup->stdD6377.temperature) tc: "<<tc;

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(ui->wMethodSetup->stdD6377.temperature));
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

            case 13:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( (ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE)))
                        {
                            cREqTime = ui->wMethodSetup->stdD6377.time;

                            cTmTest = ui->wMethodSetup->stdD6377.temperature;
                            int tc = cSettings.getTemperatureCount(cTmTest);

                            sendPara(cProtocol.sendTemperature(tc),
                                     14, cREqTime + M_EQUILIBRIUM_TIME_OUT);

                            qDebug()<<"cSettings.getTemperatureCount(ui->wMethodSetup->stdD6377.temperature) tc: "<<tc;

                            if(ui->wServiceSetup->getDebug())
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(ui->wMethodSetup->stdD6377.temperature));
                            else
                                ui->wMeasuring1->setStatus(STRING_MEASURING_TEMPERATURE_STABILIZING);

                            cEqTime = 0;
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

            case 14:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if( (ctmp >= (cTmTest - M_TEMPERATURE_TOLERANCE))
                            && (ctmp <= (cTmTest + M_TEMPERATURE_TOLERANCE)))
                        {
                            cEqTime++;

                            ui->wMeasuring1->setLblMessage(tr("Measurement in progress \n Expansion 1/1"));
                            if(cEqTime >= cREqTime)
                            {
                                cStage = 15;
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
                                ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_TEMPERATURE_STABILIZE + cSettings.getTemperature(ui->wMethodSetup->stdD6377.temperature));
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

            case 15:
                    {
                        cParasUpdated = false;

                        cEqTime++;

                        if(cEqTime >=60)
                        {
                            cEqTime = 0;

                            ui->wMeasuring1->setStatus("");

                            ui->imageCapture->resize(167,25);
                            ui->imageCapture->move(20,900);
                            ui->imageCapture->show();

                            ui->wMeasuring1->showResultD6377(cSettings.getPressurekPaMM(cRawCTemperature, cRawCPressure));
                            ui->wServiceSetup->incrementCount();

                            sendPara(cProtocol.sendShakerSpeed( 0, 0), 16, 60);
                            cStrringErrorCount = 0;
                        }
                        else {
                            ui->wMeasuring1->setStatus(STRING_MEASURING_WAITING_FOR + QString::number(60-cEqTime) + " Sec");

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

                        if((cStepperSpeed == 0) && (cStageTimeOut <=56))
                        {

                            int tc = cSettings.getTemperatureCount(ui->wMethodSetup->stdD6377.InjectTemp);
                           sendPara( cProtocol.sendTemperature(tc),
                                     17, 60*12); //180+180);

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

//                            if(ui->wMethodSetup->stdD6377.alarm_enabled && cStageTimeOut == 58)
                            if(ui->wUserSetup->user_setup.alarm_buzzer_enable && cStageTimeOut == 58)
                                onSendCommand(cProtocol.sendAlertBuzzer(M_BUZZER_START));
                        }
                    }

                    break;

            case 17:
                    {
                        cParasUpdated = false;

                        double ctmp = cSettings.getTemperatureCelsius(cRawCTemperature);

                        if((ctmp >= (ui->wMethodSetup->stdD6377.InjectTemp - M_TEMPERATURE_TOLERANCE ))
                            && (ctmp <= (ui->wMethodSetup->stdD6377.InjectTemp + M_TEMPERATURE_TOLERANCE )))
                        {
                            sendPara(cProtocol.sendValvePosition(M_VALVE_POSITION_EXHAUST),
                                     18, 60);

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

            case 18:
                    {
                        cParasUpdated = false;

                        if(cValvePosition == M_VALVE_POSITION_EXHAUST)
                        {
                            sendPara(cProtocol.sendPistonPosition(0), 19, 60);

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

            case 19:
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
    QString str = "p_tot: " + QString::number(p_tot) + " p_gas: " + QString::number(p_gas) + " p_abs: " + QString::number(p_abs) + " method: " + method +
            " formula: " + formula + " aconst: " + QString::number(aconst) + " bconst: " + QString::number(bconst) + " cconst: " + QString::number(cconst) + " result: " + QString::number(result) +
            " ttime: " + QString::number(ttime) + " vlratio: " + QString::number(vlratio) + " para_measured: " + QString::number(para_measured);

    if(ui->wServiceSetup->logPathEnabled())
        ui->wServiceSetup->commandLog((str));
    else if(ui->wServiceSetup->internalLogData())
    {
        qDebug()<<"First Time";
        ui->wServiceSetup->commandLog(str);
    }

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

    switch (menu) {

        case M_MEASURING:
            if(ui->wUserSetup->isVisible()) ui->wUserSetup->hide();
            if(ui->wMemory->isVisible()) ui->wMemory->hide();
        break;

        case M_CLEANING:
            if(ui->wMeasuring1->isVisible()) ui->wMeasuring1->hide();
            if(ui->wMemory->isVisible()) ui->wMemory->hide();
        break;

        case M_MEMORY:
            if(ui->wMeasuring1->isVisible()) ui->wMeasuring1->hide();
            if(ui->wUserSetup->isVisible()) ui->wUserSetup->hide();
            if(ui->wMemory->isVisible() && !ui->wMemory->isSwitchEnabled(menu)) return;
        break;

        case M_SETUP:

//            if(ui->wMemory->isVisible()) ui->wMemory->hide();

//            if(ui->wUserSetup->isVisible() && !ui->wUserSetup->isSwitchEnabled(menu)) return;
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

    if(cMenu < M_CLEANING) ui->listSetupMenu->move(558,60+120);
    else if(cMenu == M_MEMORY) ui->listSetupMenu->move(558,60+40);
    else ui->listSetupMenu->move(558,60);

    switch (menu) {

    case M_MEASURING:
        ui->imageCapture->resize(167,41);
        ui->imageCapture->move(20,881);
        ui->imageCapture->show();
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
//         ui->wCleaning->Show();
        ui->imageCapture->resize(167,80);
        ui->imageCapture->move(20,920);
        ui->imageCapture->show();

        ui->wUserSetup->Show();
        ui->wUserSetup->show();
        ui->fTitle->hide();
        ui->wMenuBar->move(0, 10);
         ui->wMenuBar->setSelectedMenu(menu);
         //--------------- 8-May-2023 added below
          //if(cWaitForACK)
          {
//             cAccessWidget = ui->wCleaning;
            cAccessWidget = ui->wCleaning;
             cAccessWidget->setWaitACKStatus(cWaitForACK);
          }
         //--------------------

         cMenu = menu;
//         cWidget = ui->wCleaning;
         cWidget = ui->wUserSetup;
         break;

    case M_MEMORY:

        if(cWidget) cWidget->hide();
        ui->fTitle->hide();
        ui->wMenuBar->move(0, 10);

        ui->imageCapture->resize(167,22);
        ui->imageCapture->move(30,905);
        ui->imageCapture->show();

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

                ui->imageCapture->resize(167,80);
                ui->imageCapture->move(20,920);
                ui->imageCapture->show();

                switch(rMenu)
                {

                    case M_PWD_SERVICE: if(cWidget) cWidget->hide();
                                        if(rUser == "admin") {
                                            ui->wServiceSetup->IS_ADMIN_USER_Service=1;
                                        }
                                        else {
                                            ui->wServiceSetup->IS_ADMIN_USER_Service=0;
                                        }
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
                                            ui->wCalibrationSetup->updateD6377Range(((ui->wMethodSetup->stdD6377.vl_ratio * 100)+100));
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
            ui->imageCapture->resize(167,80);
            ui->imageCapture->move(20,920);
            ui->imageCapture->show();

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
            ui->imageCapture->resize(167,80);
            ui->imageCapture->move(20,920);
            ui->imageCapture->show();

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
            ui->imageCapture->resize(167,80);
            ui->imageCapture->move(20,920);
            ui->imageCapture->show();

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
            ui->wServiceSetup->sInitDone = false;

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
               readSaveLogFile(USER_SETUP_FILES, true);
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

             if(tmp) {
                 ui->wGeneralSetup->saveFile();
                 readSaveLogFile(GENERAL_SETUP_FILES, false);
             } else {
                 ui->wGeneralSetup->readFile();
                 readSaveLogFile(GENERAL_SETUP_FILES, true);
             }

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
                readSaveLogFile(METHOD_SETUP_FILES, false);
             }
             else
             {
                ui->wMethodSetup->readFile();
                readSaveLogFile(METHOD_SETUP_FILES, true);
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
                 if(ui->wCalibrationSetup->getcParaMethodVolumeChanged()){
                     ui->wCalibrationSetup->readFile();
                     ui->wCalibrationSetup->readMethodVolumeFile();
                     ui->wCalibrationSetup->sendTemcommand();
                 }else{
                    ui->wCalibrationSetup->readFile();
                    ui->wCalibrationSetup->readMethodVolumeFile();
                 }

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
                ui->wCalibrationSetup->saveMethodVolumeFile();

                readSaveLogFile(CALIBRATION_SETUP_FILES, false);
                readSaveLogFile(VOLUME_ADJUSTMENT_FILES, false);
             }
             else
             {
                ui->wCalibrationSetup->readFile();
                ui->wCalibrationSetup->readMethodVolumeFile();

                readSaveLogFile(CALIBRATION_SETUP_FILES, true);
                readSaveLogFile(VOLUME_ADJUSTMENT_FILES, true);
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
                    ftime.replace(" ", "_");

                    fname =  fdate + "_" + ftime + "_" +
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

void MainWindow::onD6377VlRatio(double vl){
    qDebug()<<"Updating D6377 vl_ratio";
    ui->wCalibrationSetup->on_D6377_Vl_ration(vl, false);
    ui->wCalibrationSetup->updateD6377Range(((ui->wMethodSetup->stdD6377.vl_ratio * 100)+100));
}

void MainWindow::on_imageCapture_clicked()
{
    /*qDebug()<<"image capture clicked";
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

        QString filename = QString("/run/media/sda1/screenshot/screenshot_%1.png").arg(timestamp);
        QWidget *widget = QApplication::activeWindow();
        QPixmap pixmap = QPixmap::grabWidget(widget);
        ui->imageCapture->setFocusPolicy(Qt::NoFocus);
        qDebug()<<"path : "<<filename;
        pixmap.save(QString(filename));
        QString originalStyleSheet = this->styleSheet();
        this->setStyleSheet("background-color: rgb(21, 100, 192);");

        QTimer::singleShot(50, this, [=]() {
            this->setStyleSheet(originalStyleSheet);
        });
    }else{
        qDebug()<<"folder doesn't exist";
    }*/

    qDebug() << "image capture clicked";
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString screenshotDirPath = "/run/media/sda1/screenshot";
        QDir screenshotDir(screenshotDirPath);
        if (!screenshotDir.exists())
        {
            if (screenshotDir.mkpath(screenshotDirPath))
            {
                qDebug() << "Screenshot folder created successfully.";
            }
            else
            {
                qDebug() << "Failed to create screenshot folder.";
                return; // Exit the function if the folder could not be created
            }
        }
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
        QString filename = QString("%1/screenshot_%2.png").arg(screenshotDirPath).arg(timestamp);
        QWidget *widget = QApplication::activeWindow();
        QPixmap pixmap = QPixmap::grabWidget(widget);
        ui->imageCapture->setFocusPolicy(Qt::NoFocus);
        qDebug() << "path : " << filename;
        if (pixmap.save(filename))
        {
            qDebug() << "Screenshot saved successfully.";
//            QString originalStyleSheet = this->styleSheet();
            this->setStyleSheet("background-color: rgb(21, 100, 192);");

            QTimer::singleShot(50, this, [=]() {
//                this->setStyleSheet(originalStyleSheet);
                this->setStyleSheet("background-color: rgb(0, 160, 255);");
            });
        }
        else
        {
            qDebug() << "Failed to save screenshot.";
        }
    }
    else
    {
        qDebug() << "Pendrive doesn't exist";
    }
}
