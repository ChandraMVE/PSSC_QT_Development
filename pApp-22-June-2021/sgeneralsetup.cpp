#include "sgeneralsetup.h"
#include "ui_sgeneralsetup.h"
#include <QDir> //naveen

sGeneralSetup::sGeneralSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sGeneralSetup)
{
    ui->setupUi(this);


    QListView *view1 = new QListView(ui->cbDateFormat);
    view1->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbDateFormat->setView(view1);


    QListView *view2 = new QListView(ui->cbTimeFormat);
    view2->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbTimeFormat->setView(view2);


    QListView *view3 = new QListView(ui->cbLanguage);
    view3->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbLanguage->setView(view3);

    QListView *view4 = new QListView(ui->cbPressureScale);
    view4->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbPressureScale->setView(view4);


    QListView *view5 = new QListView(ui->cbTemperatureScale);
    view5->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbTemperatureScale->setView(view5);


    QListView *view6 = new QListView(ui->cbAutoMeasuring);
    view6->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbAutoMeasuring->setView(view6);

    QListView *view7 = new QListView(ui->cbEmulation);
    view7->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbEmulation->setView(view7);

    QListView *view8 = new QListView(ui->cbBaud);
    view8->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbBaud->setView(view8);

    QListView *view9 = new QListView(ui->cbParity);
    view9->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbParity->setView(view9);

    QListView *view10 = new QListView(ui->cbFlow);
    view10->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbFlow->setView(view10);

    QListView *view11 = new QListView(ui->cbStop);
    view11->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbStop->setView(view11);

    QListView *view12 = new QListView(ui->cbData);
    view12->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbData->setView(view12);

    QListView *view13 = new QListView(ui->cbPageSize);
    view13->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbPageSize->setView(view13);

    QListView *view14 = new QListView(ui->cbReportFormat);
    view14->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbReportFormat->setView(view14);

    QListView *view15 = new QListView(ui->cbUser);
    view15->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbUser->setView(view15);


    QListView *view16 = new QListView(ui->cbDay);
    view16->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbDay->setView(view16);

    QListView *view17 = new QListView(ui->cbMonth);
    view17->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbMonth->setView(view17);

    QListView *view18 = new QListView(ui->cbYear);
    view18->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbYear->setView(view18);

    QListView *view19 = new QListView(ui->cbHour);
    view19->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbHour->setView(view19);

    QListView *view20 = new QListView(ui->cbMinute);
    view20->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbMinute->setView(view20);

    QListView *view21 = new QListView(ui->cbAMPM);
    view21->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbAMPM->setView(view21);

    QListView *view22 = new QListView(ui->cbGMT);
    view22->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item::hover { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255);}\
                        QListView::item{height: 41px}");

    ui->cbGMT->setView(view22);


    setDefaults();

    connect(ui->leCompany, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->leCompany, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));

    connect(ui->leLocation, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->leLocation, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));

    connect(ui->leUnitId, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));
    connect(ui->leUnitId, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));

    connect(ui->leNetworkName, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(ui->leNetworkName, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leIPAddress, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(ui->leIPAddress, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypadNumeric(int)));

    connect(ui->leIPMask, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(ui->leIPMask, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypadNumeric(int)));

    connect(ui->leGateway, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(ui->leGateway, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypadNumeric(int)));

    connect(ui->leDNS, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
    connect(ui->leDNS, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypadNumeric(int)));

    connect(ui->leOldPassword, SIGNAL(textChanged(QString)), this, SLOT(onPassTextChanged(QString)));
    connect(ui->leOldPassword, SIGNAL(showKeypad(int)), this, SLOT(onShowPassKeypad(int)));

    connect(ui->leNewPassword, SIGNAL(textChanged(QString)), this, SLOT(onPassTextChanged(QString)));
    connect(ui->leNewPassword, SIGNAL(showKeypad(int)), this, SLOT(onShowPassKeypad(int)));

    connect(ui->leConfirmPassword, SIGNAL(textChanged(QString)), this, SLOT(onPassTextChanged(QString)));
    connect(ui->leConfirmPassword, SIGNAL(showKeypad(int)), this, SLOT(onShowPassKeypad(int)));

    cParasChanged = false;
    cPrevTab = -1;
    cPrevDeviceTab = -1;
    cPrevOtherTab = -1;
    cEnSwitch = true;

    ui->cbDay->clear();
    for(int tmp=1; tmp <=31; tmp++)
        ui->cbDay->addItem(QString::number(tmp));

    ui->cbMonth->clear();
    for(int tmp=1; tmp <=12; tmp++)
        ui->cbMonth->addItem(QString::number(tmp));

    ui->cbYear->clear();
    for(int tmp=2021; tmp <=2051; tmp++)
        ui->cbYear->addItem(QString::number(tmp));

    ui->cbHour->clear();
    for(int tmp=1; tmp <=12; tmp++)
        ui->cbHour->addItem(QString::number(tmp));

    ui->cbMinute->clear();
    for(int tmp=0; tmp <=59; tmp++)
        ui->cbMinute->addItem(QString::number(tmp));


    QRegularExpression cnRegex ("[^<>'\"/;`?,{}@!~&:|\^]{0,25}$");
    QRegularExpressionValidator *cnValidator = new QRegularExpressionValidator(cnRegex, this);

    ui->leCompany->setValidator(cnValidator);

    QRegularExpression lcRegex ("[^<>'\"/;`?,{}@!~&:|\^]{0,20}$");
    QRegularExpressionValidator *lcValidator = new QRegularExpressionValidator(lcRegex, this);

    ui->leLocation->setValidator(lcValidator);
    ui->leUnitId->setValidator(lcValidator);

    QRegularExpression hnRegex ("^[a-zA-Z0-9_]{0,15}$");

    QRegularExpressionValidator *hnValidator = new QRegularExpressionValidator(hnRegex, this);
    ui->leNetworkName->setValidator(hnValidator);

    QString IpRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    QRegularExpression IpRegex ("^" + IpRange
                                + "(\\." + IpRange + ")"
                                + "(\\." + IpRange + ")"
                                + "(\\." + IpRange + ")$");

    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(IpRegex, this);

    QRegularExpression passRegex ("[^<>'\"/;`?,{}@!~&:|\^]{0,20}$");

    QRegularExpressionValidator *passValidator = new QRegularExpressionValidator(passRegex, this);

    ui->leOldPassword->setValidator(passValidator);
    ui->leNewPassword->setValidator(passValidator);
    ui->leConfirmPassword->setValidator(passValidator);

    ui->leIPAddress->setValidator(ipValidator);
    ui->leIPMask->setValidator(ipValidator);
    ui->leGateway->setValidator(ipValidator);
    ui->leDNS->setValidator(ipValidator);
}

sGeneralSetup::~sGeneralSetup()
{
    delete ui;
}

void sGeneralSetup::setDateFormat(const QStringList tmp)
{
      ui->cbDateFormat->clear();
      ui->cbDateFormat->insertItems(0, tmp);
}

void sGeneralSetup::setTimeFormat(const QStringList tmp)
{
    ui->cbTimeFormat->clear();
    ui->cbTimeFormat->insertItems(0, tmp);
}

void sGeneralSetup::setLanguage(const QStringList tmp)
{
    ui->cbLanguage->clear();
    ui->cbLanguage->insertItems(0, tmp);
}

void sGeneralSetup::setPressureScale(const QStringList tmp)
{
    ui->cbPressureScale->clear();
    ui->cbPressureScale->insertItems(0, tmp);
}

void sGeneralSetup::setTemperatureScale(const QStringList tmp)
{
    ui->cbTemperatureScale->clear();
    ui->cbTemperatureScale->insertItems(0, tmp);
}

void sGeneralSetup::setPageSize(const QStringList tmp)
{
    ui->cbPageSize->clear();
    ui->cbPageSize->insertItems(0, tmp);
}

void sGeneralSetup::setReportFormat(const QStringList tmp)
{
    ui->cbReportFormat->clear();
    ui->cbReportFormat->insertItems(0, tmp);
}

void sGeneralSetup::setEmulation(const QStringList tmp)
{
    ui->cbEmulation->clear();
    ui->cbEmulation->insertItems(0, tmp);
}

void sGeneralSetup::setBaudRate(const QStringList tmp)
{
    ui->cbBaud->clear();
    ui->cbBaud->insertItems(0, tmp);
}

void sGeneralSetup::setParity(const QStringList tmp)
{
    ui->cbParity->clear();
    ui->cbParity->insertItems(0, tmp);
}

void sGeneralSetup::setFlow(const QStringList tmp)
{
    ui->cbFlow->clear();
    ui->cbFlow->insertItems(0, tmp);
}

void sGeneralSetup::setStopBits(const QStringList tmp)
{
    ui->cbStop->clear();
    ui->cbStop->insertItems(0, tmp);
}

void sGeneralSetup::setDataBits(const QStringList tmp)
{
    ui->cbData->clear();
    ui->cbData->insertItems(0, tmp);
}

void sGeneralSetup::setRinseCycles(const QStringList tmp)
{
    ui->cbAutoMeasuring->clear();
    ui->cbAutoMeasuring->insertItems(0, tmp);
}

void sGeneralSetup::Show(QString type)
{
    cType = type;
    cPrevTab = 0;
    cPrevDeviceTab = 0;
    cPrevOtherTab = 0;

    ui->twGeneralSetup->setCurrentIndex(0);
    ui->twDevice->setCurrentIndex(0);
    ui->twOther->setCurrentIndex(0);

    if(cType == "admin")
    {
        ui->cbUser->setCurrentIndex(M_USER_ADMIN);
        ui->cbUser->setEnabled(true);

        ui->lblOldPassword->show();
        ui->leOldPassword->show();

        ui->lblOldPassword->move(40, 130);
        ui->leOldPassword->move(280, 130);

        ui->lblNewPassword->move(40, 230);
        ui->leNewPassword->move(280, 230);

        ui->lblConfirmPassword->move(40, 330);
        ui->leConfirmPassword->move(280, 330);

    }
    else if(cType == "service")
    {
        ui->cbUser->setCurrentIndex(M_USER_SERVICE);
        ui->cbUser->setEnabled(true);

        ui->lblOldPassword->show();
        ui->leOldPassword->show();

        ui->lblOldPassword->move(40, 110);
        ui->leOldPassword->move(240, 110);

        ui->lblNewPassword->move(40, 170);
        ui->leNewPassword->move(240, 170);

        ui->lblConfirmPassword->move(40, 230);
        ui->leConfirmPassword->move(240, 230);

    }
    else if(cType == "pssc")
    {
        ui->cbUser->setCurrentIndex(M_USER_ADMIN);
        ui->cbUser->setEnabled(true);

        ui->lblOldPassword->hide();
        ui->leOldPassword->hide();

        ui->lblNewPassword->move(40, 110);
        ui->leNewPassword->move(240, 110);

        ui->lblConfirmPassword->move(40, 170);
        ui->leConfirmPassword->move(240, 170);

    }

    showGeneralSetup();
    this->show();
}

void sGeneralSetup::setDefaults()
{
    general_setup.date_format = DEFAULT_DATE_FORMAT;
    general_setup.time_format = DEFAULT_TIME_FORMAT;
    general_setup.gmt = DEFAULT_USER_GMT;
    general_setup.company =  DEFAULT_COMPANY;
    general_setup.location =  DEFAULT_LOCATION;
    general_setup.unit_id =  DEFAULT_UNIT_ID;
    general_setup.language = DEFAULT_LANGUAGE;
    general_setup.pressure_scale = DEFAULT_PRESSURE_SCALE;
    general_setup.temperature_scale = DEFAULT_TEMPERATURE_SCALE;
    general_setup.auto_measuring_cycle = DEFAULT_AUTO_MEASURING_CYCLES;

    general_setup.emulation = DEFAULT_EMULATION;
    general_setup.baud = DEFAULT_BAUD;
    general_setup.parity = DEFAULT_PARITY;
    general_setup.flow = DEFAULT_FLOW;
    general_setup.stop_bits = DEFAULT_STOP_BITS;
    general_setup.data_bits = DEFAULT_DATA_BITS;

    general_setup.page_size = DEFAULT_PAGE_SIZE;
    general_setup.report_format = DEFAULT_REPORT_FORMAT;

    general_setup.network_name = DEFAULT_NETWORK_NAME;
    general_setup.network_enable = DEFAULT_NETWORK_ENABLE;
    general_setup.ip_address = DEFAULT_IP_ADDRESS;
    general_setup.ip_mask = DEFAULT_IP_MASK;
    general_setup.ip_gateway = DEFAULT_IP_GATEWAY;
    general_setup.ip_dns = DEFAULT_IP_DNS;

    general_setup.admin_password = DEFAULT_ADMIN_PASSWORD;
    general_setup.service_password = DEFAULT_SERVICE_PASSWORD;

}

bool sGeneralSetup::readFile()
{

    QString fname = QApplication::applicationDirPath() + FN_GENERAL_SETUP;

    cEnSwitch = true;

    QFile in(fname);

    if(in.open(QIODevice::ReadOnly))
    {

        QDataStream save(&in);
        save >> general_setup;
        in.close();

        cParasChanged = false;
        showGeneralSetup();
        return true;
    }
    else
    {
        setDefaults();
        cParasChanged = true;
        return false;
    }
}

bool sGeneralSetup::saveFile()
{
    QString fname = QApplication::applicationDirPath() + FN_GENERAL_SETUP;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);
        save << general_setup;
        out.close();
        cParasChanged = false;
        saveHostnameFile();
        saveNetworkFile();
        emit showMsgBox(tr("General Setup"), tr("General Setup Changes Saved!"));
        return true;
    }
    else
    {
        cEnSwitch = false;
        emit showMsgBox(tr("General Setup"), tr("Error Saving File!"));
        return false;
    }
}

void sGeneralSetup::saveNetworkFile()
{
    //QString fname = NETWORK_FILE_NAME;
    QString fname = QApplication::applicationDirPath() + NETWORK_FILE_NAME;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream save(&out);

        if(general_setup.network_enable)
        {
            save << "[Match]" << endl;
            save << "Name=eth0" << endl << endl;
            save << "[Network]" << endl;
            save << "Address=" << general_setup.ip_address << endl;
            save << "Netmask=" << general_setup.ip_mask << endl;
            save << "Gateway=" << general_setup.ip_gateway << endl;
            save << "DNS=" << general_setup.ip_dns << endl << endl;
        }

        out.close();
        cParasChanged = false;
        cEnSwitch = true;
        emit showMsgBox(tr("General Setup"), tr("Network Changes Saved!"));
    }
    else
    {
        cEnSwitch = false;
        emit showMsgBox(tr("General Setup"), tr("Error Saving File!"));
    }
}

void sGeneralSetup::saveHostnameFile()
{
    //QString fname = HOST_FILE_NAME;
    QString fname = QApplication::applicationDirPath() + HOST_FILE_NAME;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream save(&out);
        save << general_setup.network_name;
        out.close();
        cParasChanged = false;
        cEnSwitch = true;
        emit showMsgBox(tr("General Setup"), tr("Host File Changes Saved!"));
    }
    else
    {
        cEnSwitch = false;
        emit showMsgBox(tr("General Setup"), tr("Error Saving File!"));
    }
}

void sGeneralSetup::showGeneralSetup()
{
    ui->cbDateFormat->setCurrentIndex(general_setup.date_format);
    ui->cbTimeFormat->setCurrentIndex(general_setup.time_format);
    ui->leCompany->setText(general_setup.company);
    ui->leLocation->setText(general_setup.location);
    ui->leUnitId->setText(general_setup.unit_id);
    ui->cbLanguage->setCurrentIndex(general_setup.language);
    ui->cbPressureScale->setCurrentIndex(general_setup.pressure_scale);
    ui->cbTemperatureScale->setCurrentIndex(general_setup.temperature_scale);
    ui->cbAutoMeasuring->setCurrentIndex(general_setup.auto_measuring_cycle);

    ui->cbEmulation->setCurrentIndex(general_setup.emulation);
    ui->cbBaud->setCurrentIndex(general_setup.baud);
    ui->cbParity->setCurrentIndex(general_setup.parity);
    ui->cbFlow->setCurrentIndex(general_setup.flow);
    ui->cbStop->setCurrentIndex(general_setup.stop_bits);
    ui->cbData->setCurrentIndex(general_setup.data_bits);

    ui->cbPageSize->setCurrentIndex(general_setup.page_size);
    ui->cbReportFormat->setCurrentIndex(general_setup.report_format);

    ui->leNetworkName->setText(general_setup.network_name);

    ui->cbNEnable->setChecked(general_setup.network_enable);

    ui->leIPAddress->setText(general_setup.ip_address);
    ui->leIPMask->setText(general_setup.ip_mask);
    ui->leGateway->setText(general_setup.ip_gateway);
    ui->leDNS->setText(general_setup.ip_dns);

    ui->leIPAddress->setReadOnly(!ui->cbNEnable->isChecked());
    ui->leIPMask->setReadOnly(!ui->cbNEnable->isChecked());
    ui->leGateway->setReadOnly(!ui->cbNEnable->isChecked());
    ui->leDNS->setReadOnly(!ui->cbNEnable->isChecked());

    ui->leOldPassword->setText("");
    ui->leNewPassword->setText("");
    ui->leConfirmPassword->setText("");

    ui->twGeneralSetup->setFocus();

    ui->cbGMT->setCurrentIndex(general_setup.gmt);

}

void sGeneralSetup::updateGeneralSetup()
{
    //sn cParasChanged = false;

    if(general_setup.date_format != ui->cbDateFormat->currentIndex()) cParasChanged = true;
    general_setup.date_format = ui->cbDateFormat->currentIndex();

    if(general_setup.time_format != ui->cbTimeFormat->currentIndex()) cParasChanged = true;
    general_setup.time_format = ui->cbTimeFormat->currentIndex();

    if(general_setup.company != ui->leCompany->text()) cParasChanged = true;
    general_setup.company = ui->leCompany->text();

    if(general_setup.location != ui->leLocation->text()) cParasChanged = true;
    general_setup.location = ui->leLocation->text();

    if(general_setup.unit_id != ui->leUnitId->text()) cParasChanged = true;
    general_setup.unit_id = ui->leUnitId->text();

    if(general_setup.language != ui->cbLanguage->currentIndex()) cParasChanged = true;
    general_setup.language = ui->cbLanguage->currentIndex();

    if(general_setup.pressure_scale != ui->cbPressureScale->currentIndex()) cParasChanged = true;
    general_setup.pressure_scale = ui->cbPressureScale->currentIndex();

    if(general_setup.temperature_scale != ui->cbTemperatureScale->currentIndex()) cParasChanged = true;
    general_setup.temperature_scale = ui->cbTemperatureScale->currentIndex();

    if(general_setup.auto_measuring_cycle != ui->cbAutoMeasuring->currentIndex()) cParasChanged = true;
    general_setup.auto_measuring_cycle = ui->cbAutoMeasuring->currentIndex();

    if(general_setup.emulation != ui->cbEmulation->currentIndex()) cParasChanged = true;
    general_setup.emulation = ui->cbEmulation->currentIndex();

    if(general_setup.baud != ui->cbBaud->currentIndex()) cParasChanged = true;
    general_setup.baud = ui->cbBaud->currentIndex();

    if(general_setup.parity != ui->cbParity->currentIndex()) cParasChanged = true;
    general_setup.parity = ui->cbParity->currentIndex();

    if(general_setup.flow!= ui->cbFlow->currentIndex()) cParasChanged = true;
    general_setup.flow = ui->cbFlow->currentIndex();

    if(general_setup.stop_bits != ui->cbStop->currentIndex()) cParasChanged = true;
    general_setup.stop_bits = ui->cbStop->currentIndex();

    if(general_setup.data_bits != ui->cbData->currentIndex()) cParasChanged = true;
    general_setup.data_bits = ui->cbData->currentIndex();

    if(general_setup.page_size != ui->cbPageSize->currentIndex()) cParasChanged = true;
    general_setup.page_size = ui->cbPageSize->currentIndex();

    if(general_setup.report_format != ui->cbReportFormat->currentIndex()) cParasChanged = true;
    general_setup.report_format = ui->cbReportFormat->currentIndex();

    if(general_setup.network_name != ui->leNetworkName->text()) cParasChanged = true;
    general_setup.network_name = ui->leNetworkName->text();

    if(general_setup.network_enable != ui->cbNEnable->checkState()) cParasChanged = true;
    general_setup.network_enable = ui->cbNEnable->checkState();

    if(general_setup.ip_address != ui->leIPAddress->text()) cParasChanged = true;
    general_setup.ip_address = ui->leIPAddress->text();

    if(general_setup.ip_mask != ui->leIPMask->text()) cParasChanged = true;
    general_setup.ip_mask = ui->leIPMask->text();

    if(general_setup.ip_gateway != ui->leGateway->text()) cParasChanged = true;
    general_setup.ip_gateway = ui->leGateway->text();

    if(general_setup.ip_dns != ui->leDNS->text()) cParasChanged = true;
    general_setup.ip_dns = ui->leDNS->text();

    if(general_setup.gmt != ui->cbGMT->currentIndex()) cParasChanged = true;
    general_setup.gmt = ui->cbGMT->currentIndex();

}

void sGeneralSetup::onShowKeypad(int tmp)
{
    emit showKeypad(QObject::sender(), KAYPAD_ALPHA_NUMERIC, false);
}

void sGeneralSetup::onShowKeypadNumeric(int tmp)
{
    emit showKeypad(QObject::sender(), KAYPAD_NUMERIC, false);
}

void sGeneralSetup::onTextChanged(QString tmp)
{
    QLineEdit *tle = qobject_cast<QLineEdit *>(QObject::sender());

    if(tle)
    {

        if((!tle->hasAcceptableInput()) || (!tle->text().length()) || (tle->text().startsWith(' ')))
        {
            tle->setProperty("error", true);
            tle->style()->polish(tle);

            if(ui->frGeneral->isVisible())
            {
                ui->twGeneralSetup->setTabEnabled(1, false);
                ui->twGeneralSetup->setTabEnabled(2, false);
                ui->pbSave->setEnabled(false);

            }
            else if(ui->frNetwork->isVisible())
            {
                ui->twGeneralSetup->setTabEnabled(0, false);
                ui->twGeneralSetup->setTabEnabled(2, false);
                ui->twDevice->setTabEnabled(0, false);
                ui->pbSave->setEnabled(false);
            }
        }
        else
        {
            tle->setProperty("error", false);
            tle->style()->polish(tle);

            if(ui->frGeneral->isVisible())
            {
                ui->twGeneralSetup->setTabEnabled(1, true);
                ui->twGeneralSetup->setTabEnabled(2, true);
                ui->pbSave->setEnabled(true);
            }
            else if(ui->frNetwork->isVisible())
            {
                ui->twGeneralSetup->setTabEnabled(0, true);
                ui->twGeneralSetup->setTabEnabled(2, true);
                ui->twDevice->setTabEnabled(0, true);
                ui->pbSave->setEnabled(true);
            }

        }
    }
}

void sGeneralSetup::onShowPassKeypad(int tmp)
{
    emit showKeypad(QObject::sender(), KAYPAD_ALPHA_NUMERIC, true);
}

void sGeneralSetup::onPassTextChanged(QString tmp)
{
    QLineEdit *tle = qobject_cast<QLineEdit *>(QObject::sender());

    if(tle)
    {

        if((!tle->hasAcceptableInput()) || (0 && (!tle->text().length()) || (tle->text().startsWith(' '))))
        {
            tle->setProperty("error", true);
            tle->style()->polish(tle);

            if(ui->frGeneral->isVisible())
            {
                ui->twGeneralSetup->setTabEnabled(1, false);
                ui->twGeneralSetup->setTabEnabled(2, false);
                ui->pbSave->setEnabled(false);

            }
            else if(ui->frNetwork->isVisible())
            {
                ui->twGeneralSetup->setTabEnabled(0, false);
                ui->twGeneralSetup->setTabEnabled(2, false);
                ui->twDevice->setTabEnabled(0, false);
                ui->pbSave->setEnabled(false);
            }
        }
        else
        {
            tle->setProperty("error", false);
            tle->style()->polish(tle);

            if(ui->frGeneral->isVisible())
            {
                ui->twGeneralSetup->setTabEnabled(1, true);
                ui->twGeneralSetup->setTabEnabled(2, true);
                ui->pbSave->setEnabled(true);
            }
            else if(ui->frNetwork->isVisible())
            {
                ui->twGeneralSetup->setTabEnabled(0, true);
                ui->twGeneralSetup->setTabEnabled(2, true);
                ui->twDevice->setTabEnabled(0, true);
                ui->pbSave->setEnabled(true);
            }

        }
    }
}

void sGeneralSetup::on_pbSave_clicked()
{

    if(ui->tabDateTime->isVisible()) SaveRTC();
    else if(ui->tabPassword->isVisible()) SavePassword();
    else
    {
        updateGeneralSetup();

        if(cParasChanged)
        {
            saveFile();
        }
    }
}

void sGeneralSetup::on_pbExit_clicked()
{
    updateGeneralSetup();

    if(cParasChanged)
    {
        cEnSwitch = false;
        emit getConfirmation(M_CONFIRM_GENERAL, M_MEASURING);
    }

    if(!cParasChanged)
    {
        this->hide();
        emit showHome(false);
    }

    //this->hide();
    //emit showHome(false);

}

void sGeneralSetup::on_cbNEnable_clicked()
{
    ui->leIPAddress->setReadOnly(!ui->cbNEnable->isChecked());
    ui->leIPMask->setReadOnly(!ui->cbNEnable->isChecked());
    ui->leGateway->setReadOnly(!ui->cbNEnable->isChecked());
    ui->leDNS->setReadOnly(!ui->cbNEnable->isChecked());
}

void sGeneralSetup::SaveRTC()
{

    QString str;

    str.sprintf("%d/%02d/%02d %02d:%02d ",
                ui->cbYear->currentText().toInt(),
                ui->cbDay->currentText().toInt(),
                ui->cbMonth->currentText().toInt(),
                ui->cbHour->currentText().toInt(),
                ui->cbMinute->currentText().toInt());

    str = str + ui->cbAMPM->currentText();

    QDateTime dt = QDateTime::fromString(str, "yyyy/dd/MM hh:mm AP");

    if(!dt.isValid())
        emit showMsgBox(tr("General Setup"), tr("Select Valid Date!"));
    else
    {

        QString string = dt.toString("\"yyyyMMdd hh:mm\"");
        QString dateTimeString ("date -s ");
        dateTimeString.append(string);

        int systemDateTimeStatus= system(dateTimeString.toStdString().c_str());

        if (systemDateTimeStatus == -1)
        {

        }
        else
        {
            int systemHwClockStatus = system("/sbin/hwclock -w");
            if (systemHwClockStatus == -1 )
            {

            }
            else
                emit showMsgBox(tr("General Setup"), tr("Date Time Updated!"));
        }
    }
    updateGeneralSetup();
    if(cParasChanged)
    {
        saveFile();
    }
}

void sGeneralSetup::SavePassword()
{
    QString user, password;

    user = ui->cbUser->currentText();

    if(user == "admin") password = general_setup.admin_password;
    else if(user == "service") password = general_setup.service_password;

    if(user == "admin" || user == "service")
    {
        if(ui->leOldPassword->text() != password && (!ui->cbUser->isEnabled()))
        {
            emit showMsgBox(tr("General Setup"), tr("Invalid Old Password!"));
         }
        else if(ui->leNewPassword->text() != ui->leConfirmPassword->text())
        {
                emit showMsgBox(tr("General Setup"),
                                tr("New & Confirm Password mismatch!"));
        }
        else
        {
            if(user == "admin")
                general_setup.admin_password = ui->leNewPassword->text();
            else
                if(user == "service")
                    general_setup.service_password = ui->leNewPassword->text();

            if(saveFile())
            {
                emit showMsgBox(tr("General Setup"),
                            tr("Password Updated!"));
            }

            ui->leOldPassword->setText("");
            ui->leNewPassword->setText("");
            ui->leConfirmPassword->setText("");
        }
    }
}

bool sGeneralSetup::isSwitchEnabled(int tmp)
{
    updateGeneralSetup();

    if(cParasChanged)
    {
        cEnSwitch = false;
        emit getConfirmation(M_CONFIRM_GENERAL, tmp);
    }

    return cEnSwitch;
}

void sGeneralSetup::on_twGeneralSetup_currentChanged(int index)
{
    if(!isVisible()) return;

    if(cPrevTab!=index)
    {
        switch(cPrevTab)
        {
            case 0:
            case 1:
                    updateGeneralSetup();
                    if(cParasChanged)
                        emit getConfirmation(M_CONFIRM_GENERAL_SWITCH, M_MEASURING);

                    break;
            case 2:

            break;
        }

        cPrevTab = index;
    }

    if(index <= 1)
        ui->pbSave->setText(tr("Save"));
    else
        ui->pbSave->setText(tr("Update"));

    switch(index)
    {
        case 0:
        case 1:
                showGeneralSetup();
                break;
        case 2:
                break;

    }
}

void sGeneralSetup::on_twDevice_currentChanged(int index)
{
    if(!isVisible()) return;

    if(cPrevDeviceTab!=index)
    {

        updateGeneralSetup();
        if(cParasChanged)
            emit getConfirmation(M_CONFIRM_GENERAL_SWITCH, M_MEASURING);

        cPrevDeviceTab = index;
    }

    showGeneralSetup();

}

void sGeneralSetup::on_twOther_currentChanged(int index)
{
    if(!index)
    {
        QDateTime cdt = QDateTime::currentDateTime();

        ui->cbYear->setCurrentIndex(cdt.date().year() - 2021);
        ui->cbDay->setCurrentIndex(cdt.date().day() - 1);
        ui->cbMonth->setCurrentIndex(cdt.date().month() - 1);

        if(cdt.time().hour()>12)
        {
            ui->cbHour->setCurrentIndex(cdt.time().hour()-12);
            ui->cbAMPM->setCurrentIndex(1);
        }
        else
        {
            ui->cbHour->setCurrentIndex(cdt.time().hour()-1);
            ui->cbAMPM->setCurrentIndex(0);
        }

        ui->cbMinute->setCurrentIndex(cdt.time().minute()-1);

    }
    else
    {
        ui->leOldPassword->setText("");
        ui->leNewPassword->setText("");
        ui->leConfirmPassword->setText("");
    }

    ui->twOther->setFocus();
}

void sGeneralSetup::on_imageCapture_clicked()
{
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

        QString filename = QString("/run/media/sda1/screenshot/_%1_sgeneralsetup.png").arg(timestamp);
        QWidget *widget = QApplication::activeWindow();
        QPixmap pixmap = QPixmap::grabWidget(widget);
        ui->imageCapture->setFocusPolicy(Qt::NoFocus);
        qDebug()<<"path : "<<filename;
        pixmap.save(QString(filename));
    }else{
        qDebug()<<"folder doesn't exist";
    }
}

int sGeneralSetup::getGMTSeconds()
{
    return ((1800*general_setup.gmt)-43200);
}
