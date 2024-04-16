#include "sservice.h"
#include "ui_sservice.h"

sService::sService(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sService)
{
    ui->setupUi(this);

    QListView *view = new QListView(ui->cbSelectorValve);
    view->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 5px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); }\
                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
                        QListView::item{height: 41px}");

    ui->cbSelectorValve->setView(view);

    ui->twErrorLog->setColumnWidth(0, 567);
    ui->twErrorLog->setColumnWidth(1, 165+300);

    connect(ui->wFirmware, SIGNAL(clicked()), this, SLOT(onFirmwareClicked()));

    connect(ui->leTemperature, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leTemperature, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leRPM, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leRPM, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->lePistonPosition, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->lePistonPosition, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    QDoubleValidator* tempValidator = new QDoubleValidator(RANGE_SERVICE_CALIB_TEMPERATURE_MIN, RANGE_SERVICE_CALIB_TEMPERATURE_MAX, RANGE_SERVICE_CALIB_TEMPERATURE_DECIMAL_PLACES, ui->leTemperature);
    tempValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->leTemperature->setValidator(tempValidator);

    QDoubleValidator* rpmValidator = new QDoubleValidator(RANGE_SHAKER_RPM_MIN, RANGE_SHAKER_RPM_MAX, 0, ui->leRPM);
    rpmValidator ->setNotation(QDoubleValidator::StandardNotation);
    ui->leRPM->setValidator(rpmValidator);

    QDoubleValidator* pistonValidator = new QDoubleValidator(RANGE_PISTON_POSITION_MIN, RANGE_PISTON_POSITION_MAX, RANGE_PISTON_POSITION_DECIMAL_PLACES, ui->lePistonPosition);
    pistonValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->lePistonPosition->setValidator(pistonValidator);

    cParasChanged = false;
    cPrevTab = -1;
    ui->twErrorLog->clearContents();
    ui->twErrorLog->model()->removeRows(0, ui->twErrorLog->rowCount());

    cLogStage = 0;
    cUsbLogTimeout = USB_LOG_TIMEOUT;

    cLiveDataUpdated = false;
    cLogFile = NULL;

    cDiagnosticMode = false;
    cHide = false;
    cEnSwitch = true;
    sServiceSaved = false;

    cvp = 0;
    cpp = 0;
    catm = 0;
    cctm = 0;
    cpr = 0;
    css = 0;
    cerr = 0;

    /*
    QString str;
    str.append(FW_VERSION);
    str.append(" "); str.append(FW_DATE); str.append(" ");
    str.append(FW_TIME);
    */

    cVerFW.clear();
    cVerFW.append(FW_VERSION);
    cVerFW.append(" "); cVerFW.append(FW_DATE); cVerFW.append(" ");
    cVerFW.append(FW_TIME);

    cVerMCU = "MCU: Ver. 00.00.00";

    ui->wFirmware->setFirmware(cVerFW + "\n" + cVerMCU);
    cDebug = false;
}

sService::~sService()
{
    delete ui;
}

void sService::Show()
{
    readErrorLogFile();

    ui->lblFileSelected->setText("");

    ui->pbRun->setEnabled(true);
    ui->pbStop->setEnabled(false);
    ui->lwStatus->clear();
    ui->pbSave->hide();

    showServiceSetup();

    cPrevTab = 0;
    ui->twService->setCurrentIndex(0);

    ui->wFirmware->setFirmware(cVerFW + "\n" + cVerMCU);

    this->show();
    cHide = false;

    setWaitACKStatus(true);
    emit sendCommand(cProtocol.sendMeasuring(1, 0), this);

}

void sService::setDefaults()
{
    service_setup.total_count = DEFAULT_SET_TOTAL_COUNT;
    service_setup.count_since_last_reset = DEFAULT_SET_COUNT_SINCE_LAST_RESET;
    service_setup.continuous_enable = DEFAULT_SET_CONTINEOUS_RUN;
    service_setup.data_log_usb = DEFAULT_SET_DATA_LOG_USB;
    cParasChanged = true;
}

bool sService::readFile()
{
    QString fname = QApplication::applicationDirPath() + FN_SERVICE_SETUP;

    QFile in(fname);
    cEnSwitch = true;

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream save(&in);
        save >> service_setup;
        in.close();

        setUSBLog();

        cParasChanged = false;

        return true;
    }
    else
    {
        
        setDefaults();
        setUSBLog();

        return false;
    }
}

bool sService::readErrorLogFile()
{
    QString fname = QApplication::applicationDirPath() + FN_ERROR_LOG;

    for(int tmp = ui->twErrorLog->rowCount(); tmp >=0 ; tmp--)
    {
        ui->twErrorLog->removeRow(tmp);
    }

    struct ERROR_LOG nRecord;

    QFile in(fname);

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream read(&in);
        while(!read.atEnd())
        {
             read >> nRecord;

             QString str = cSettings.getDateTime(nRecord.error_datetime);

            ui->twErrorLog->insertRow(0);
            ui->twErrorLog->setItem(0, 0, new QTableWidgetItem(nRecord.error_description));
            ui->twErrorLog->setItem(0, 1, new QTableWidgetItem(str));

        }

        in.close();

        return true;

    }
    else
    {
        return false;
    }
}

void sService::saveFile()
{
    QString fname = QApplication::applicationDirPath() + FN_SERVICE_SETUP;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);
        save << service_setup;
        out.close();
        cParasChanged = false;
        cEnSwitch = true;
        sServiceSaved = true;
    }
    else
    {
        cEnSwitch = false;
        sServiceSaved = false;
        emit showMsgBox(tr("Service Setup"), tr("Error Saving File!"));
    }
}

void sService::setUSBLog()
{
    if(service_setup.data_log_usb)
    {
        if(!timer.isActive())
        {
            cLogStage = 1;
            timer.start(5000, this);
        }
    }
    else
    {
        if(timer.isActive())
        {
            cLogStage = 0;
            timer.stop();
        }

        if(cLogFile)
        {
            cLogFile->close();
            emit showMsgBox(tr("Service Setup"), tr("USB Log Disabled\nSafe to remove USB Pen Drive."));
        }
    }
}

bool sService::addErrorLog(QString error_description, QString error_datetime)
{
    
    ui->twErrorLog->insertRow(0);
    ui->twErrorLog->setItem(0, 0, new QTableWidgetItem(error_description));

    QString str = cSettings.getDateTime(error_datetime);

    ui->twErrorLog->setItem(0, 1, new QTableWidgetItem(str));

    if(ui->twErrorLog->rowCount() > ERROR_LOG_MAX)
    {
        ui->twErrorLog->model()->removeRow(ERROR_LOG_MAX);
    }

    QString fname = QApplication::applicationDirPath() + FN_ERROR_LOG;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);

        for(int tmp = ui->twErrorLog->rowCount()-1; tmp >= 0; tmp--)
        {
           
            struct ERROR_LOG nRecord;
            nRecord.error_description = ui->twErrorLog->item(tmp, 0)->text();

            QString str = cSettings.saveDateTime(ui->twErrorLog->item(tmp, 1)->text());
            nRecord.error_datetime = str;

            save << nRecord;

        }

        out.close();
        return true;
    }
    else
    {
        return false;
    }
}

void sService::showServiceSetup()
{
    QString str;

    ui->cbTEnable->setChecked(DEFAULT_SET_TEMPERATURE_ENABLE);
    str.sprintf("%.2f", DEFAULT_SET_TEMPERATURE);
    ui->leTemperature->clear();
    ui->leTemperature->insert(str);

    ui->leTemperature->setReadOnly(!ui->cbTEnable->isChecked());
    ui->pbTSet->setEnabled(ui->cbTEnable->isChecked());

    ui->cbSMEnable->setChecked(DEFAULT_SET_SHAKER_ENABLE);
    ui->leRPM->setReadOnly(!ui->cbSMEnable->isChecked());
    ui->pbRPMSet->setEnabled(ui->cbSMEnable->isChecked());

    str.sprintf("%d", DEFAULT_SET_SHAKER_RPM);
    ui->leRPM->clear();
    ui->leRPM->insert(str);

    ui->cbSelectorValve->setCurrentIndex(DEFAULT_SET_SELECTOR_VALVE);

    str.sprintf("%.2f", DEFAULT_SET_PISTON_POSITION);
    ui->lePistonPosition->clear();
    ui->lePistonPosition->insert(str);

    str.sprintf("%u", service_setup.total_count);
    ui->lblTotalCount->setText(str);

    str.sprintf("%u", service_setup.count_since_last_reset);
    ui->lblSinceLastReset->setText(str);

    ui->cbCREnable->setChecked(service_setup.continuous_enable);
    ui->cbUDLEnable->setChecked(service_setup.data_log_usb);

    ui->pbFWUpdate->setEnabled(false);
    ui->lblFileSelected->setText("---");

}

void sService::updateServiceSetup()
{
    if(service_setup.total_count != ui->lblTotalCount->text().toULong())
    {
        cParasChanged = true;
    }
    service_setup.total_count = ui->lblTotalCount->text().toULong();

    if(service_setup.continuous_enable != ui->cbCREnable->checkState())
    {
        cParasChanged = true;
    }
    service_setup.continuous_enable = ui->cbCREnable->checkState();

    if(service_setup.data_log_usb != ui->cbUDLEnable->checkState())
    {
        cParasChanged = true;
    }
    service_setup.data_log_usb = ui->cbUDLEnable->checkState();
}

void sService::incrementCount()
{
    service_setup.total_count++;
    service_setup.count_since_last_reset++;

    saveFile();
}

void sService::onShowKeypad(int tmp)
{
    emit showKeypad(QObject::sender(), KAYPAD_NUMERIC, false);
}

void sService::on_pbSave_clicked()
{
    updateServiceSetup();
    setUSBLog();

    saveFile();

    if(sServiceSaved){
        sServiceSaved = false;
        emit showMsgBox(tr("Service Setup"), tr("Service Changes Saved!"));
    }

    /* 8-July-2022
    {
        int tc = cSettings.getTemperatureCount(20); 
        emit sendCommand(cProtocol.sendMeasuring(0, tc));
    }
    */
}

void sService::on_pbExit_clicked()
{
    checkExit(M_MEASURING);

    if(!cParasChanged)
    {
        this->hide();
        emit showHome(false);
    }
//    else{ //naveen
//        emit showHome(false);
//    }
}

void sService::on_cbTEnable_clicked()
{
    ui->leTemperature->setReadOnly(!ui->cbTEnable->isChecked());
    ui->pbTSet->setEnabled(ui->cbTEnable->isChecked());

    if(!ui->cbTEnable->isChecked())
    {
        setWaitACKStatus(true);
        emit sendCommand(cProtocol.sendMeasuring(1, 0), this);
    }
}

void sService::ontextChanged(QString tmp)
{
    QLineEdit *tle = qobject_cast<QLineEdit *>(QObject::sender());

    if(tle)
    {
        if(!tle->hasAcceptableInput())
        {
            tle->setProperty("error", true);
            tle->style()->polish(tle);
        }
        else
        {
            tle->setProperty("error", false);
            tle->style()->polish(tle);
        }
    }
}

void sService::on_pbSVSet_clicked()
{
    setWaitACKStatus(true);
    emit sendCommand(cProtocol.sendValvePosition(ui->cbSelectorValve->currentIndex()), this);
}

void sService::on_pbTSet_clicked()
{
    if(ui->leTemperature->hasAcceptableInput())
    {
        double tm = ui->leTemperature->text().toDouble();

        setWaitACKStatus(true);
        int tmp = cSettings.getTemperatureCount(tm);
        emit sendCommand(cProtocol.sendTemperature(tmp), this);

    }
}

void sService::on_pbRunReset_clicked()
{
    ui->lblSinceLastReset->setText("0");
}

void sService::on_pbPPSet_clicked()
{
    if(ui->lePistonPosition->hasAcceptableInput())
    {
        int pp = ui->lePistonPosition->text().toDouble() * 100;

        setWaitACKStatus(true);
        emit sendCommand(cProtocol.sendPistonPosition(pp), this);

    }
}

void sService::on_pbRPMSet_clicked()
{
    if(ui->leRPM->hasAcceptableInput())
    {
        setWaitACKStatus(true);
        int tmp = ui->leRPM->text().toDouble();
        emit sendCommand(cProtocol.sendShakerSpeed(1, tmp), this);
    }
}

void sService::onLiveData(int vp, int pp, int atm, int ctm, int pr, int ss, int err)
{
    QString str;
    str = cSettings.getTemperatureLive(ctm);
    ui->lblTemperature->setText(str);
    ui->lblTemperature_2->setText(str);

    str = cSettings.getPressureLive(ctm, pr);
    ui->lblPressure->setText(str);
    ui->lblPressure_2->setText(str);

    double piston = pp/100.0;
    str.sprintf("%.2f", piston);
    ui->lblPistonPosition->setText(str);

    if(vp >=0 && vp <= 2)
        ui->lblSelectorValve->setText(ui->cbSelectorValve->itemText(vp));

    str.sprintf("%d", ss);
    ui->lblRPM->setText(str);
}

void sService::onLogData(int vp, int pp, int atm, int ctm, int pr, int ss, int err)
{
    cvp = vp;
    cpp = pp;
    catm = atm;
    cctm = ctm;
    cpr = pr;
    css = ss;
    cerr = err;
    cLiveDataUpdated = true;
}

void sService::setFileSelected(QString fs)
{
    ui->lblFileSelected->setText(fs);

    if(fs.contains("---"))
       ui->pbFWUpdate->setEnabled(false);
    else
        ui->pbFWUpdate->setEnabled(true);
}

bool sService::getUSBLogEnabled()
{
    return service_setup.data_log_usb; 
}

bool sService::getContinuousRunEnabled()
{
    return service_setup.continuous_enable;
}

bool sService::logData()
{
    if(cSettings.checkUSBMounted())
    {
        if(!cSettings.checkFolderExists(USB_LOG_FOLDER))
        {

#ifdef Q_OS_WIN32
            QDir dir("c:/");
#else
            QDir dir("/");
#endif

            dir.mkpath(USB_LOG_FOLDER);
        }

        if(cSettings.checkFolderExists(USB_LOG_FOLDER))
        {
            QString fname = USB_LOG_FOLDER + cSettings.getUnitId() + "_" +
                            cSettings.getCurrentDateTime().date().toString(cSettings.getDateFormat().replace('/', "_"))
                            + ".txt";

            cLogFile = new QFile(fname);

            if(cLogFile->open(QIODevice::Append | QIODevice::Text))
            {
                cLogStage = 3;
            }
            else
            {
                emit showMsgBox(tr("Service Setup"), tr("Error Creating Log File!"));
            }

        }
        else
        {
            emit showMsgBox(tr("Service Setup"), tr("Error Creating Log Folder!"));
        }

    }
    else
        return false;
		
    return true;
}

bool sService::isDiagnosticMode()
{
    return cDiagnosticMode;
}

void sService::addStatus(QString tmp)
{
    ui->lwStatus->addItem(tmp);
}

void sService::updateStatus(QString tmp)
{
    ui->lwStatus->addItem(tmp);
}

void sService::testDone()
{
    ui->twService->setTabEnabled(0, true);
    ui->twService->setTabEnabled(1, true);
    ui->twService->setTabEnabled(3, true);

    ui->pbRun->setEnabled(true);
    ui->pbStop->setEnabled(false);
    ui->pbExit->setEnabled(true);

    cDiagnosticMode = false;
    cEnSwitch = true;
}

void sService::setWaitACKStatus(bool tmp)
{
    if(ui->twService->currentIndex()==0)
    {
        if(tmp)
        {
            ui->twService->setTabEnabled(0, true);
            ui->twService->setTabEnabled(1, false);
            ui->twService->setTabEnabled(2, false);
            ui->twService->setTabEnabled(3, false);

            ui->pbPPSet->setEnabled(false);
            ui->pbRPMSet->setEnabled(false);
            ui->pbSVSet->setEnabled(false);
            ui->pbTSet->setEnabled(false);
            ui->cbTEnable->setEnabled(false);
            ui->cbSMEnable->setEnabled(false);
            ui->pbExit->setEnabled(false);
        }
        else
        {
            ui->twService->setTabEnabled(0, true);
            ui->twService->setTabEnabled(1, true);
            ui->twService->setTabEnabled(2, true);
            ui->twService->setTabEnabled(3, true);

            ui->cbTEnable->setEnabled(true);
            ui->cbSMEnable->setEnabled(true);
            ui->pbPPSet->setEnabled(true);
            ui->pbRPMSet->setEnabled(ui->cbSMEnable->isChecked());
            ui->pbSVSet->setEnabled(true);
            ui->pbTSet->setEnabled(ui->cbTEnable->isChecked());
            ui->pbExit->setEnabled(true);
        }
    }
    else if(ui->twService->currentIndex()==2)
    {
        if(cDiagnosticMode) return;

        if(tmp)
        {
            ui->twService->setTabEnabled(0, false);
            ui->twService->setTabEnabled(1, false);
            ui->twService->setTabEnabled(2, true);
            ui->twService->setTabEnabled(3, false);
            ui->pbRun->setEnabled(false);
            ui->pbStop->setEnabled(false);
            ui->pbExit->setEnabled(false);
        }
        else
        {
            ui->twService->setTabEnabled(0, true);
            ui->twService->setTabEnabled(1, true);
            ui->twService->setTabEnabled(2, true);
            ui->twService->setTabEnabled(3, true);

            ui->pbRun->setEnabled(true);
            ui->pbStop->setEnabled(false);
            ui->pbExit->setEnabled(true);
        }
    }

}

bool sService::getWaitACKStatus()
{
    return true;
}

void sService::hideAfterACK(bool tmp)
{
    if(!tmp)
    {
        cHide = false;
        //3-May-2023 this->hide();
    }
    else cHide = true;
}

bool sService::getHideAfterACK()
{
    return cHide;
}

bool sService::isSwitchEnabled(int tmp)
{
    checkExit(tmp);
    return cEnSwitch;
}

void sService::checkExit(int tmp)
{
    updateServiceSetup();

    if(cParasChanged)
    {
        cEnSwitch = false;
        emit getConfirmation(M_CONFIRM_SERVICE, tmp);
    }

    //13-May-2023

    if((!cParasChanged) && (!isDiagnosticMode()))

    {
        hideAfterACK(true);
        int tc = cSettings.getTemperatureCount(20);
        emit sendCommand(cProtocol.sendMeasuring(0, tc), this);
    }

    //this->hide();
    //emit showHome(false);
}

void sService::setDebug()
{
    cDebug = !cDebug;
}

int sService::getDebug()
{
    return cDebug;
}

void sService::setVersion(QString tmp)
{
    cVerMCU = "MCU: Ver. " + tmp;
}

void sService::timerEvent(QTimerEvent *e)
{
    if (e->timerId() == timer.timerId())
    {
        switch(cLogStage)
        {
            case 0: break;
            case 1: if(!logData())
                    {
                        emit showMsgBox(tr("Service Setup"), tr("To USB Log, No USB Pen Drive Found!\nReconnect USB Pen Drive & try again!"));
                        cLogStage = 2;
                    }
                    else
                        cLogStage = 3;
                    break;

            case 2: logData(); break;

            case 3:
                if(cLogFile)
                {
                    if(cLiveDataUpdated)
                    {
                        cLiveDataUpdated = false;

                        QString cdt = cSettings.getCurrentDateTime().toString("dd/MM/yyyy hh:mm:ss");

                        QTextStream cTextStream(cLogFile);

                        cTextStream << " " << cSettings.getDate(cdt) << " "
                                    << cSettings.getTime(cdt) << ":"
                                    << "Tm:" << cSettings.getTemperatureLive(cctm)
                                    << ", Pr:" << cSettings.getPressureLive(cctm, cpr)
                                    << ", Valve:" << ui->cbSelectorValve->itemText(cvp)
                                    << ", PP:" << QString::number(cpp/100.0, 'f', 2)
                                    << ", SS:" << QString::number(css);

                        cTextStream << endl;
                    }

                }
                else
                {
                   cLogFile->close();
                   cLogStage = 1;
                   emit showMsgBox(tr("Service Setup"), tr("Error Logging to USB Pen Drive!"));
                }

            break;
        }
    }
    else
    {
        QWidget::timerEvent(e);
    }
}

void sService::on_cbSMEnable_clicked()
{
    ui->leRPM->setReadOnly(!ui->cbSMEnable->isChecked());
    ui->pbRPMSet->setEnabled(ui->cbSMEnable->isChecked());

    if(!ui->cbSMEnable->isChecked())
    {
        setWaitACKStatus(true);
        emit sendCommand(cProtocol.sendShakerSpeed(0, 0), this);
    }
}

void sService::on_pbFileSelect_clicked()
{
    emit showFileSelect();
}

void sService::on_pbFWUpdate_clicked()
{
    QString fname1 =  FF_FIRMWARE_FOLDER;
    fname1.append("/");
    fname1.append(ui->lblFileSelected->text());

    QString fname2 = QApplication::applicationDirPath() + FN_UPDATE_FIRMWARE;


    {
        ui->pbFWUpdate->setEnabled(false);

        emit showStatusBox(tr("Service Setup"), tr("Updating Firmware...\nPlease Wait..."), true);

        QElapsedTimer timeout;
        timeout.start();

        while(timeout.elapsed() < 3000) QCoreApplication::processEvents();

    }


    QFile::remove(fname2);  //24-May-2022



    if(QFile::copy( fname1, fname2))
    {
        //23-May-2022 emit showMsgBox(tr("Service Setup"), tr("Firmware Copied\nRestart Machine to reflect changes!"));
        //added below lines to confimr file size is greater than 0

        QFileInfo fi(fname2);

        if(fi.size())
            emit showMsgBox(tr("Service Setup"), tr("Firmware Copied\nRestart Machine to reflect changes!"));
        else
        {
            if (fi.isFile()) QFile::remove(fname2);

            emit showMsgBox(tr("Service Setup"), tr("Error Saving Firmware File!"));
        }
    }
    else
    {
        emit showMsgBox(tr("Service Setup"), tr("Error Saving Firmware File!"));
    }

    ui->pbFWUpdate->setEnabled(true);
}

void sService::on_twService_currentChanged(int index)
{
    if(!isVisible()) return;

    ui->pbFWUpdate->setEnabled(false);
    ui->lblFileSelected->setText("---");
    ui->lwStatus->clear();

    if(cPrevTab!=index)
    {
        if(cPrevTab==1)
        {
            updateServiceSetup();

            if(cParasChanged)
                emit getConfirmation(M_CONFIRM_SERVICE_SWITCH, M_MEASURING);
        }

        cPrevTab = index;
    }

    if(index == 1) ui->pbSave->show();
    else ui->pbSave->hide();

    //if(index <= 1)
    //    showServiceSetup();

    if(index == 2)
    {
        setWaitACKStatus(true);
        int tc = cSettings.getTemperatureCount(20); 
        emit sendCommand(cProtocol.sendMeasuring(0, tc), this);
    }
    else if(index == 0)
    {

        setWaitACKStatus(true);
        emit sendCommand(cProtocol.sendMeasuring(1, 0), this);
    }

    if(index <= 1)
        showServiceSetup();

}

void sService::on_pbRun_clicked()
{
    ui->twService->setTabEnabled(0, false);
    ui->twService->setTabEnabled(1, false);
    ui->twService->setTabEnabled(3, false);

    ui->pbRun->setEnabled(false);
    ui->pbStop->setEnabled(true);
    ui->pbExit->setEnabled(false);

    cDiagnosticMode = true;
    cEnSwitch = false;

    emit runClicked(MS_DIAGNOSTIC_RUN, false);

}

void sService::on_pbStop_clicked()
{
    ui->twService->setTabEnabled(0, true);
    ui->twService->setTabEnabled(1, true);
    ui->twService->setTabEnabled(3, true);

    ui->pbRun->setEnabled(true);
    ui->pbStop->setEnabled(false);
    ui->pbExit->setEnabled(true);

    cDiagnosticMode = false;
    cEnSwitch = true;

    emit runClicked(MS_DIAGNOSTIC_STOP, false);

}

void sService::onFirmwareClicked()
{
    emit getPass();
}

void sService::on_imageCapture_clicked()
{
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

        //QString filename = QApplication::applicationDirPath() + QString("/screenshot/sservice_%1.png").arg(timestamp);
        QString filename = QString("/run/media/sda1/screenshot/_%1_sservice.png").arg(timestamp);
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
