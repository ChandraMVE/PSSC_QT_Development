#include "smeasuring.h"
#include "ui_smeasuring.h"

sMeasuring::sMeasuring(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMeasuring)
{
    ui->setupUi(this);

#ifndef Q_OS_WIN32
    ui->pbStop_2->hide();
#endif



//    QListView *view = new QListView(ui->cbMethod);
//    view->setStyleSheet("QListView { border: 2px solid rgb(21, 100, 192); font: 75 16pt \"Roboto Medium\"; border-radius: 8px; background-color: rgb(255, 255, 255); selection-background-color:  rgb(21, 100, 192); selection-color: rgb(255, 255, 255); outline: none;}\
//                        QListView::item::selected { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255); }\
//                        QListView::item::hover { background-color:  rgb(21, 100, 192); color:  rgb(255, 255, 255);}\
//                        QListView::item{height: 41px}");

//    ui->cbMethod->setView(view);

    ui->wResult->resize(ui->twMeasuring->width(), ui->twMeasuring->height());
    ui->wResult->move((ui->twMeasuring->x()-10), (ui->twMeasuring->y()));
    ui->wResult->setStatus("");
    ui->wResult->hide();

    connect(ui->leSampleId, SIGNAL(click()), this, SLOT(onClickSampleId()));
    connect(ui->leOperator, SIGNAL(click()), this, SLOT(onClickOperator()));
    connect(ui->leMethod, SIGNAL(click()), this, SLOT(onClickMethod()));

    connect(ui->leSampleId, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leSampleId, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    connect(ui->leOperator, SIGNAL(textChanged(QString)), this, SLOT(ontextChanged(QString)));
    connect(ui->leOperator, SIGNAL(showKeypad(int)), this, SLOT(onShowKeypad(int)));

    QRegularExpression opRegex ("[^<>'\"/;`?,{}@!~&:|\^]{0,20}$");

    QRegularExpressionValidator *opValidator = new QRegularExpressionValidator(opRegex, this);
    QRegularExpressionValidator *siValidator = new QRegularExpressionValidator(opRegex, this);

    ui->leSampleId->setValidator(siValidator);
    ui->leOperator->setValidator(opValidator);

    cPrevOperator = "";
    cPrevSampleId = "";

    ui->leOperator->setText("");
    ui->leSampleId->setText("");

    ui->lwSampleId->hide();
    ui->lwOperator->hide();
    ui->lwMethods->hide();
//    ui->pbMethod->setEnabled(false);
    ui->leMethod->setEnabled(false);

    ui->lwSampleId->resize(471, 171);
    ui->lwOperator->resize(471, 171);
    ui->lwMethods->resize(471, 171);

    ui->lblMessage->resize(680,141);
    ui->lblAutoCount->hide();
    ui->lblStatus->hide();
    cRunState = false;

    ui->imageCapture->hide();

}

sMeasuring::~sMeasuring()
{
    delete ui;
}

void sMeasuring::Show()
{
    if(ui->lwOperator->count() > 0) ui->lwOperator->setCurrentRow(0);
    if(ui->lwSampleId->count() > 0) ui->lwSampleId->setCurrentRow(0);

    ui->leOperator->setText("");
    ui->leSampleId->setText("");

    readLastIdsFile();

    cPrevOperator = ui->leOperator->text();
    cPrevSampleId = ui->leSampleId->text();

    ui->lwOperator->hide();
    ui->lwSampleId->hide();
    ui->lwMethods->hide();

//    ui->cbMethod->hide();
    //ui->cbMethod->setCurrentIndex(0);

    this->show();

}

void sMeasuring::setMethods(const QStringList tmp)
{
//    ui->cbMethod->clear();
//    ui->cbMethod->insertItems(0, tmp);

    ui->lwMethods->clear();
    ui->lwMethods->insertItems(0, tmp);
}

void sMeasuring::setMessage(QString tmp)
{
    ui->lblMessage->setText(tmp);
}

void sMeasuring::setAutoCount(int current, int total)
{
    QString str = tr("Auto Repeats:") + QString::number(current) + "/"
                  + QString::number(total);

    if(!ui->lblAutoCount->isVisible()) ui->lblMessage->resize(471, 71);

    ui->lblAutoCount->setText(str);
    ui->lblAutoCount->show();
}

/*
void sMeasuring::setIdleTimer(int tmp)
{
    tmp = M_IDLE_TIME_OUT - tmp;

    if(tmp)
    {
        QString str = QString::number(tmp);
        ui->lblIdleTimer->setText(str);
    }
    else ui->lblIdleTimer->setText("");
}
*/

void sMeasuring::setStatus(QString tmp)
{
    if(ui->wResult->isVisible()) 
        ui->wResult->setStatus(tmp);
    else
        ui->lblStatus->setText(tmp);
}

QString sMeasuring::getOperator() const
{
    return ui->leOperator->text();
}

QString sMeasuring::getSampleId() const
{
    return ui->leSampleId->text();
}

void sMeasuring::onLiveData(int tm, int pr)
{
    QString tmpUnit = cSettings.getTemperatureScale();
    QString presUnit = cSettings.getPressureScale();
    if(ui->lblTemperature->isVisible()) 
    {
        QString str;
//        qDebug()<<"onLiveData from MCU: The Temp "<<tm<<" pressure "<<pr;
        str = cSettings.getTemperatureLiveSS(tm);
        ui->lblTemperature->setText(str + " " +tmpUnit);
//        qDebug()<<"On lblTemperature: "<<str+ " " +tmpUnit;
        str = cSettings.getPressureLiveSS(tm, pr);
        ui->lblPressure->setText(str+" "+presUnit);
//        qDebug()<<"On lblPressure: "<<str+" "+presUnit;
    }
}

int sMeasuring::getMethod()
{
//    return ui->cbMethod->currentIndex();
//    qDebug()<<"ui->lwMethods->currentIndex().row(): " << ui->lwMethods->currentIndex().row();
    if(ui->lwMethods->currentIndex().row() == -1)
        return 0;
    else
        return ui->lwMethods->currentIndex().row();
}

void sMeasuring::hideLists()
{
    if(ui->lwSampleId->isVisible()) ui->lwSampleId->hide();
    if(ui->lwOperator->isVisible()) ui->lwOperator->hide();
    if(ui->lwMethods->isVisible()) ui->lwMethods->hide();
}

void sMeasuring::readOperatorsFile()
{
    QString fname = QApplication::applicationDirPath() + FN_OPERATORS;

    QFile in(fname);

    ui->lwOperator->clear();

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream read(&in);

        while(!read.atEnd())
        {
             read >> operator_names;
             ui->lwOperator->insertItem(0, operator_names.operator_name);
        }

        in.close();

        if(ui->lwOperator->count())
        {
            ui->lwOperator->setCurrentRow(0);
            ui->leOperator->setText(ui->lwOperator->currentItem()->text());
        }

    }

}

void sMeasuring::readSampleIdsFile()
{
    QString fname = QApplication::applicationDirPath() + FN_SAMPLE_ID;

    QFile in(fname);

    ui->lwSampleId->clear();

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream read(&in);

        while(!read.atEnd())
        {
             read >> sample_ids;
             ui->lwSampleId->insertItem(0, sample_ids.sample_id);
        }

        in.close();

        if(ui->lwSampleId->count())
        {
            ui->lwSampleId->setCurrentRow(0);
            ui->leSampleId->setText(ui->lwSampleId->currentItem()->text());
        }

    }

}

void sMeasuring::saveOperatorsFile()
{
    QString fname = QApplication::applicationDirPath() + FN_OPERATORS;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);

        for(int row = ui->lwOperator->count()-1; row >=0; row--)
        {
            operator_names.operator_name  = ui->lwOperator->item(row)->text();
            save << operator_names;
        }
        out.close();
    }
    else
    {
        emit showMsgBox(tr("Measuring"), tr("Error Saving File!"));
    }
}

void sMeasuring::deleteOperatorsFile()
{
    for(int row = ui->lwOperator->count()-1; row >=0; row--)
    {
        if(cPrevOperator == ui->lwOperator->item(row)->text())
        {
            delete ui->lwOperator->takeItem(row);

            if(cPrevOperator == last_ids.operator_name)
                saveLastIdsFile();
        }
    }

    QString fname = QApplication::applicationDirPath() + FN_OPERATORS;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);

        for(int row = ui->lwOperator->count()-1; row >=0; row--)
        {
            if(cPrevOperator != ui->lwOperator->item(row)->text())
            {
                operator_names.operator_name  = ui->lwOperator->item(row)->text();
                save << operator_names;
            }

        }
        out.close();
    }
    else
    {
        emit showMsgBox(tr("Measuring"), tr("Error Saving File!"));
    }
}

void sMeasuring::saveSampleIdsFile()
{
    QString fname = QApplication::applicationDirPath() + FN_SAMPLE_ID;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);

        for(int row = ui->lwSampleId->count()-1; row >=0; row--)
        {
            sample_ids.sample_id  = ui->lwSampleId->item(row)->text();
            save << sample_ids;
        }
        out.close();
    }
    else
    {
        emit showMsgBox(tr("Measuring"), tr("Error Saving File!"));
    }
}

void sMeasuring::deleteSampleIdsFile()
{
    for(int row = ui->lwSampleId->count()-1; row >=0; row--)
    {
        if(cPrevSampleId == ui->lwSampleId->item(row)->text())
        {
            delete ui->lwSampleId->takeItem(row);

            if(cPrevSampleId == last_ids.sample_id)
                saveLastIdsFile();
        }
    }

    QString fname = QApplication::applicationDirPath() + FN_SAMPLE_ID;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);

        for(int row = ui->lwSampleId->count()-1; row >=0; row--)
        {
            if(cPrevSampleId != ui->lwSampleId->item(row)->text())
            {
                sample_ids.sample_id  = ui->lwSampleId->item(row)->text();
                save << sample_ids;
            }

        }
        out.close();
    }
    else
    {
        emit showMsgBox(tr("Measuring"), tr("Error Saving File!"));
    }
}

void sMeasuring::readLastIdsFile()
{
    QString fname = QApplication::applicationDirPath() + FN_LAST_IDS;

    QFile in(fname);

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream read(&in);

        read >> last_ids;

        if(last_ids.operator_name.length())
        {
            ui->leOperator->setText(last_ids.operator_name);
        }

        if(last_ids.sample_id.length())
        {
            ui->leSampleId->setText(last_ids.sample_id);
        }

        if(last_ids.test_id.length())
        {
//            ui->cbMethod->setCurrentText(last_ids.test_id);
            qDebug()<<"last_ids.test_id: "<< last_ids.test_id;
            QString tmp = last_ids.test_id;
            int row = (tmp == "D5191")? 0:(tmp == "D6377")?1:(tmp == "D6378")? 2:(tmp == "D5188")?3:(tmp == "EN 13016-1")? 4:(tmp == "EN 13016-2")?5:(tmp == "GB/T 8017")? 6:(tmp == "IP 394")?7:(tmp == "IP 409")?8:(tmp == "IP 481")?9:(tmp == "JIS K2258-2")?10:(tmp == "SH/T 0769")?11:(tmp == "SH/T 0794")?12:(tmp == "SN/T 2932")?13:(tmp == "Free 1")?14:(tmp == "Free 2")?15:(tmp == "Free 3")?16:17;
            ui->lwMethods->setCurrentRow(row);
            ui->leMethod->setText(last_ids.test_id);
        }

        in.close();
    }
    else{
        ui->lwMethods->setCurrentRow(0);
        ui->leMethod->setText("D5191");
    }

}

void sMeasuring::saveLastIdsFile()
{
    QString fname = QApplication::applicationDirPath() + FN_LAST_IDS;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);

        last_ids.operator_name = ui->leOperator->text();
        last_ids.sample_id = ui->leSampleId->text();
        last_ids.test_id = ui->leMethod->text();

        save << last_ids;

        out.close();
    }
    else
    {
        emit showMsgBox(tr("Measuring"), tr("Error Saving File!"));
    }
}

void sMeasuring::showResultD5191Single(double prtpx3){
    double p_tot = 0;

    p_tot = prtpx3;

    double result = 0;

    double ttime = cstdD5191->time;
    double vlratio = cstdD5191->vl_ratio;
    double para_measured = cstdD5191->temperature;

    double aconstant = qslFormulaD5191aConstant->at(cstdD5191->formula).toDouble();
    double bconstant = qslFormulaD5191bConstant->at(cstdD5191->formula).toDouble();
    double cconstant = qslFormulaD5191cConstant->at(cstdD5191->formula).toDouble();

    result = (aconstant * p_tot) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdD5191->formula==0)
    {
        ui->wResult->setMethod(tr("D5191 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdD5191->formula==1)
    {
        ui->wResult->setMethod(tr("D5191 EPA Results"));
        formula = "EPA";
    }
    else if(cstdD5191->formula==2)
    {
        ui->wResult->setMethod(tr("D5191 CARB Results"));
        formula = "CARB";
    }

    if(cstdD5191->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdD5191->from).toDouble();
        double to = cSettings.getPressureWS(cstdD5191->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->setPtot(cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, 0, 0,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultEN_13016_1Single(double prtpx3){
    double p_tot = 0;

    p_tot = prtpx3;

    double result = 0;

    double ttime = cstdEN_13016_1->time;
    double vlratio = cstdEN_13016_1->vl_ratio;
    double para_measured = cstdEN_13016_1->temperature;

    double aconstant = qslFormulaEN_13016_1aConstant->at(cstdEN_13016_1->formula).toDouble();
    double bconstant = qslFormulaEN_13016_1bConstant->at(cstdEN_13016_1->formula).toDouble();
    double cconstant = qslFormulaEN_13016_1cConstant->at(cstdEN_13016_1->formula).toDouble();

    result = (aconstant * p_tot) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdEN_13016_1->formula==0)
    {
        ui->wResult->setMethod(tr("EN 13016-1 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdEN_13016_1->formula==1)
    {
        ui->wResult->setMethod(tr("EN 13016-1 EPA Results"));
        formula = "EPA";
    }
    else if(cstdEN_13016_1->formula==2)
    {
        ui->wResult->setMethod(tr("EN 13016-1 CARB Results"));
        formula = "CARB";
    }

    if(cstdEN_13016_1->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdEN_13016_1->from).toDouble();
        double to = cSettings.getPressureWS(cstdEN_13016_1->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->setPtot(cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, 0, 0,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultGB_T_8017Single(double prtpx3){
    double p_tot = 0;

    p_tot = prtpx3;

    double result = 0;

    double ttime = cstdGB_T_8017->time;
    double vlratio = cstdGB_T_8017->vl_ratio;
    double para_measured = cstdGB_T_8017->temperature;

    double aconstant = qslFormulaGB_T_8017aConstant->at(cstdGB_T_8017->formula).toDouble();
    double bconstant = qslFormulaGB_T_8017bConstant->at(cstdGB_T_8017->formula).toDouble();
    double cconstant = qslFormulaGB_T_8017cConstant->at(cstdGB_T_8017->formula).toDouble();

    result = (aconstant * p_tot) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdGB_T_8017->formula==0)
    {
        ui->wResult->setMethod(tr("GB/T 8017 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdGB_T_8017->formula==1)
    {
        ui->wResult->setMethod(tr("GB/T 8017 EPA Results"));
        formula = "EPA";
    }
    else if(cstdGB_T_8017->formula==2)
    {
        ui->wResult->setMethod(tr("GB/T 8017 CARB Results"));
        formula = "CARB";
    }

    if(cstdGB_T_8017->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdGB_T_8017->from).toDouble();
        double to = cSettings.getPressureWS(cstdGB_T_8017->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->setPtot(cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, 0, 0,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultIP_394Single(double prtpx3){
    double p_tot = 0;

    p_tot = prtpx3;

    double result = 0;

    double ttime = cstdIP_394->time;
    double vlratio = cstdIP_394->vl_ratio;
    double para_measured = cstdIP_394->temperature;

    double aconstant = qslFormulaIP_394aConstant->at(cstdIP_394->formula).toDouble();
    double bconstant = qslFormulaIP_394bConstant->at(cstdIP_394->formula).toDouble();
    double cconstant = qslFormulaIP_394cConstant->at(cstdIP_394->formula).toDouble();

    result = (aconstant * p_tot) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdIP_394->formula==0)
    {
        ui->wResult->setMethod(tr("IP 394 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdIP_394->formula==1)
    {
        ui->wResult->setMethod(tr("IP 394 EPA Results"));
        formula = "EPA";
    }
    else if(cstdIP_394->formula==2)
    {
        ui->wResult->setMethod(tr("IP 394 CARB Results"));
        formula = "CARB";
    }

    if(cstdIP_394->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdIP_394->from).toDouble();
        double to = cSettings.getPressureWS(cstdIP_394->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->setPtot(cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, 0, 0,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultSH_T_0794Single(double prtpx3){
    double p_tot = 0;

    p_tot = prtpx3;

    double result = 0;

    double ttime = cstdSH_T_0794->time;
    double vlratio = cstdSH_T_0794->vl_ratio;
    double para_measured = cstdSH_T_0794->temperature;

    double aconstant = qslFormulaSH_T_0794aConstant->at(cstdSH_T_0794->formula).toDouble();
    double bconstant = qslFormulaSH_T_0794bConstant->at(cstdSH_T_0794->formula).toDouble();
    double cconstant = qslFormulaSH_T_0794cConstant->at(cstdSH_T_0794->formula).toDouble();

    result = (aconstant * p_tot) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdSH_T_0794->formula==0)
    {
        ui->wResult->setMethod(tr("SH/T 0794 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdSH_T_0794->formula==1)
    {
        ui->wResult->setMethod(tr("SH/T 0794 EPA Results"));
        formula = "EPA";
    }
    else if(cstdSH_T_0794->formula==2)
    {
        ui->wResult->setMethod(tr("SH/T 0794 CARB Results"));
        formula = "CARB";
    }

    if(cstdSH_T_0794->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdSH_T_0794->from).toDouble();
        double to = cSettings.getPressureWS(cstdSH_T_0794->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->setPtot(cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, 0, 0,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultD5191(double prtpx1, double prtpx2, double prtpx3)
{
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1 - prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double ttime = cstdD5191->time;
    double vlratio = cstdD5191->vl_ratio;
    double para_measured = cstdD5191->temperature;

    double aconstant = qslFormulaD5191aConstant->at(cstdD5191->formula).toDouble();
    double bconstant = qslFormulaD5191bConstant->at(cstdD5191->formula).toDouble();
    double cconstant = qslFormulaD5191cConstant->at(cstdD5191->formula).toDouble();

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdD5191->formula==0)
    {
        ui->wResult->setMethod(tr("D5191 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdD5191->formula==1)
    {
        ui->wResult->setMethod(tr("D5191 EPA Results"));
        formula = "EPA";
    }
    else if(cstdD5191->formula==2)
    {
        ui->wResult->setMethod(tr("D5191 CARB Results"));
        formula = "CARB";
    }

    if(cstdD5191->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdD5191->from).toDouble();
        double to = cSettings.getPressureWS(cstdD5191->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultEN_13016_1(double prtpx1, double prtpx2, double prtpx3){
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1 - prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double ttime = cstdEN_13016_1->time;
    double vlratio = cstdEN_13016_1->vl_ratio;
    double para_measured = cstdEN_13016_1->temperature;

    double aconstant = qslFormulaEN_13016_1aConstant->at(cstdEN_13016_1->formula).toDouble();
    double bconstant = qslFormulaEN_13016_1bConstant->at(cstdEN_13016_1->formula).toDouble();
    double cconstant = qslFormulaEN_13016_1cConstant->at(cstdEN_13016_1->formula).toDouble();

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdEN_13016_1->formula==0)
    {
        ui->wResult->setMethod(tr("EN 13016-1 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdEN_13016_1->formula==1)
    {
        ui->wResult->setMethod(tr("EN 13016-1 EPA Results"));
        formula = "EPA";
    }
    else if(cstdEN_13016_1->formula==2)
    {
        ui->wResult->setMethod(tr("EN 13016-1 CARB Results"));
        formula = "CARB";
    }

    if(cstdEN_13016_1->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdEN_13016_1->from).toDouble();
        double to = cSettings.getPressureWS(cstdEN_13016_1->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultGB_T_8017(double prtpx1, double prtpx2, double prtpx3){
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1 - prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double ttime = cstdGB_T_8017->time;
    double vlratio = cstdGB_T_8017->vl_ratio;
    double para_measured = cstdGB_T_8017->temperature;

    double aconstant = qslFormulaGB_T_8017aConstant->at(cstdGB_T_8017->formula).toDouble();
    double bconstant = qslFormulaGB_T_8017bConstant->at(cstdGB_T_8017->formula).toDouble();
    double cconstant = qslFormulaGB_T_8017cConstant->at(cstdGB_T_8017->formula).toDouble();

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdGB_T_8017->formula==0)
    {
        ui->wResult->setMethod(tr("GB/T 8017 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdGB_T_8017->formula==1)
    {
        ui->wResult->setMethod(tr("GB/T 8017 EPA Results"));
        formula = "EPA";
    }
    else if(cstdGB_T_8017->formula==2)
    {
        ui->wResult->setMethod(tr("GB/T 8017 CARB Results"));
        formula = "CARB";
    }

    if(cstdGB_T_8017->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdGB_T_8017->from).toDouble();
        double to = cSettings.getPressureWS(cstdGB_T_8017->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultIP_394(double prtpx1, double prtpx2, double prtpx3){
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1 - prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double ttime = cstdIP_394->time;
    double vlratio = cstdIP_394->vl_ratio;
    double para_measured = cstdIP_394->temperature;

    double aconstant = qslFormulaIP_394aConstant->at(cstdIP_394->formula).toDouble();
    double bconstant = qslFormulaIP_394bConstant->at(cstdIP_394->formula).toDouble();
    double cconstant = qslFormulaIP_394cConstant->at(cstdIP_394->formula).toDouble();

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdIP_394->formula==0)
    {
        ui->wResult->setMethod(tr("IP 394 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdIP_394->formula==1)
    {
        ui->wResult->setMethod(tr("IP 394 EPA Results"));
        formula = "EPA";
    }
    else if(cstdIP_394->formula==2)
    {
        ui->wResult->setMethod(tr("IP 394 CARB Results"));
        formula = "CARB";
    }

    if(cstdIP_394->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdIP_394->from).toDouble();
        double to = cSettings.getPressureWS(cstdIP_394->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultSH_T_0794(double prtpx1, double prtpx2, double prtpx3){
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1 - prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double ttime = cstdSH_T_0794->time;
    double vlratio = cstdSH_T_0794->vl_ratio;
    double para_measured = cstdSH_T_0794->temperature;

    double aconstant = qslFormulaSH_T_0794aConstant->at(cstdSH_T_0794->formula).toDouble();
    double bconstant = qslFormulaSH_T_0794bConstant->at(cstdSH_T_0794->formula).toDouble();
    double cconstant = qslFormulaSH_T_0794cConstant->at(cstdSH_T_0794->formula).toDouble();

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdSH_T_0794->formula==0)
    {
        ui->wResult->setMethod(tr("SH/T 0794 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdSH_T_0794->formula==1)
    {
        ui->wResult->setMethod(tr("SH/T 0794 EPA Results"));
        formula = "EPA";
    }
    else if(cstdSH_T_0794->formula==2)
    {
        ui->wResult->setMethod(tr("SH/T 0794 CARB Results"));
        formula = "CARB";
    }

    if(cstdSH_T_0794->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdSH_T_0794->from).toDouble();
        double to = cSettings.getPressureWS(cstdSH_T_0794->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}


void sMeasuring::showResultD5188(double result)
{

    QString passfail;
    QString method = ui->leMethod->text();

    double vlratio = cstdD5188->vl_ratio;
    double para_measured = cstdD5188->pressure;

    if(cstdD5188->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdD5188->from).toDouble();
        double to = cSettings.getPressureWS(cstdD5188->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setMethod(tr("D5188 V/L Results"));
    ui->wResult->setResult(cSettings.getTemperatureWS(result), cSettings.getTemperatureScale());
    ui->wResult->setVLPr(cSettings.getVLRatio(cstdD5188->vl_ratio), cSettings.getPressureWS(cstdD5188->pressure), cSettings.getPressureScale(), passfail);
    QString formula = "T V/L"; 
	
    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(0, 0, 0,
                    method, formula,
                    0, 0, 0,
                    result,
                    0, vlratio,
                    para_measured);

}

void sMeasuring::showResultD6377(double result)
{

    QString passfail;
    QString method = ui->leMethod->text();
    double ttime = cstdD6377->time;
    double vlratio = cstdD6377->vl_ratio;
    double para_measured = cstdD6377->temperature;;

    if(cstdD6377->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdD6377->from).toDouble();
        double to = cSettings.getPressureWS(cstdD6377->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setMethod(tr("D6377 VPCRx Results"));
    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->setVLPr(cSettings.getVLRatio(cstdD6377->vl_ratio), cSettings.getTemperatureWS(para_measured), cSettings.getTemperatureScale() , passfail);
    ui->wResult->setShaker(cSettings.getShaker(cstdD6377->shaker_speed));

    QString formula = "VPCR4";

    ui->wResult->setSampleId(ui->leSampleId->text());
    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(0, 0, 0,
                    method, formula,
                    0, 0, 0,
                    result,
                    ttime, vlratio,
                    para_measured);

}

void sMeasuring::showResultIP_481(double result)
{

    QString passfail;
    QString method = ui->leMethod->text();
    double ttime = cstdIP_481->time;
    double vlratio = cstdIP_481->vl_ratio;
    double para_measured = cstdIP_481->temperature;;

    if(cstdIP_481->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdIP_481->from).toDouble();
        double to = cSettings.getPressureWS(cstdIP_481->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setMethod(tr("IP 481 VPCRx Results"));
    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->setVLPr(cSettings.getVLRatio(cstdIP_481->vl_ratio), cSettings.getTemperatureWS(para_measured), cSettings.getTemperatureScale() , passfail);
    ui->wResult->setShaker(cSettings.getShaker(cstdIP_481->shaker_speed));

    QString formula = "VPCR4";

    ui->wResult->setSampleId(ui->leSampleId->text());
    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(0, 0, 0,
                    method, formula,
                    0, 0, 0,
                    result,
                    ttime, vlratio,
                    para_measured);

}

void sMeasuring::showResultD6378(double prtpx1, double prtpx2, double prtpx3)
{
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1- prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double aconstant = qslFormulaD6378aConstant->at(cstdD6378->formula).toDouble();
    double bconstant = qslFormulaD6378bConstant->at(cstdD6378->formula).toDouble();
    double cconstant = qslFormulaD6378cConstant->at(cstdD6378->formula).toDouble();

    double ttime = cstdD6378->time;
    double vlratio = cstdD6378->vl_ratio;
    double para_measured = cstdD6378->temperature;

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdD6378->formula==0)
    {
        ui->wResult->setMethod(tr("D6378 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdD6378->formula==1)
    {
        ui->wResult->setMethod(tr("D6378 EPA Results"));
        formula = "EPA";
    }
    else if(cstdD6378->formula==2)
    {
        ui->wResult->setMethod(tr("D6378 CARB Results"));
        formula = "CARB";
    }

    if(cstdD6378->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdD6378->from).toDouble();
        double to = cSettings.getPressureWS(cstdD6378->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultEN_13016_2(double prtpx1, double prtpx2, double prtpx3)
{
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1- prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double aconstant = qslFormulaEN_13016_2aConstant->at(cstdEN_13016_2->formula).toDouble();
    double bconstant = qslFormulaEN_13016_2bConstant->at(cstdEN_13016_2->formula).toDouble();
    double cconstant = qslFormulaEN_13016_2cConstant->at(cstdEN_13016_2->formula).toDouble();

    double ttime = cstdEN_13016_2->time;
    double vlratio = cstdEN_13016_2->vl_ratio;
    double para_measured = cstdEN_13016_2->temperature;

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdEN_13016_2->formula==0)
    {
        ui->wResult->setMethod(tr("EN 13016-2 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdEN_13016_2->formula==1)
    {
        ui->wResult->setMethod(tr("EN 13016-2 EPA Results"));
        formula = "EPA";
    }
    else if(cstdEN_13016_2->formula==2)
    {
        ui->wResult->setMethod(tr("EN 13016-2 CARB Results"));
        formula = "CARB";
    }

    if(cstdEN_13016_2->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdEN_13016_2->from).toDouble();
        double to = cSettings.getPressureWS(cstdEN_13016_2->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultIP409(double prtpx1, double prtpx2, double prtpx3)
{
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1- prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double aconstant = qslFormulaIP_409aConstant->at(cstdIP409->formula).toDouble();
    double bconstant = qslFormulaIP_409bConstant->at(cstdIP409->formula).toDouble();
    double cconstant = qslFormulaIP_409cConstant->at(cstdIP409->formula).toDouble();

    double ttime = cstdIP409->time;
    double vlratio = cstdIP409->vl_ratio;
    double para_measured = cstdIP409->temperature;

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdIP409->formula==0)
    {
        ui->wResult->setMethod(tr("IP 409 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdIP409->formula==1)
    {
        ui->wResult->setMethod(tr("IP 409 EPA Results"));
        formula = "EPA";
    }
    else if(cstdIP409->formula==2)
    {
        ui->wResult->setMethod(tr("IP 409 CARB Results"));
        formula = "CARB";
    }

    if(cstdIP409->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdIP409->from).toDouble();
        double to = cSettings.getPressureWS(cstdIP409->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultJIS_K2258_2(double prtpx1, double prtpx2, double prtpx3)
{
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1- prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double aconstant = qslFormulaJIS_K2258_2aConstant->at(cstdJIS_K2258_2->formula).toDouble();
    double bconstant = qslFormulaJIS_K2258_2bConstant->at(cstdJIS_K2258_2->formula).toDouble();
    double cconstant = qslFormulaJIS_K2258_2cConstant->at(cstdJIS_K2258_2->formula).toDouble();

    double ttime = cstdJIS_K2258_2->time;
    double vlratio = cstdJIS_K2258_2->vl_ratio;
    double para_measured = cstdJIS_K2258_2->temperature;

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdJIS_K2258_2->formula==0)
    {
        ui->wResult->setMethod(tr("JIS K2258-2 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdJIS_K2258_2->formula==1)
    {
        ui->wResult->setMethod(tr("JIS K2258-2 EPA Results"));
        formula = "EPA";
    }
    else if(cstdJIS_K2258_2->formula==2)
    {
        ui->wResult->setMethod(tr("JIS K2258-2 CARB Results"));
        formula = "CARB";
    }

    if(cstdJIS_K2258_2->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdJIS_K2258_2->from).toDouble();
        double to = cSettings.getPressureWS(cstdJIS_K2258_2->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultSH_T_0769(double prtpx1, double prtpx2, double prtpx3)
{
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1- prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double aconstant = qslFormulaSH_T_0769aConstant->at(cstdSH_T_0769->formula).toDouble();
    double bconstant = qslFormulaSH_T_0769bConstant->at(cstdSH_T_0769->formula).toDouble();
    double cconstant = qslFormulaSH_T_0769cConstant->at(cstdSH_T_0769->formula).toDouble();

    double ttime = cstdSH_T_0769->time;
    double vlratio = cstdSH_T_0769->vl_ratio;
    double para_measured = cstdSH_T_0769->temperature;

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdSH_T_0769->formula==0)
    {
        ui->wResult->setMethod(tr("SH/T 0769 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdSH_T_0769->formula==1)
    {
        ui->wResult->setMethod(tr("SH/T 0769 EPA Results"));
        formula = "EPA";
    }
    else if(cstdSH_T_0769->formula==2)
    {
        ui->wResult->setMethod(tr("SH/T 0769 CARB Results"));
        formula = "CARB";
    }

    if(cstdSH_T_0769->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdSH_T_0769->from).toDouble();
        double to = cSettings.getPressureWS(cstdSH_T_0769->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultSN_T_2932(double prtpx1, double prtpx2, double prtpx3)
{
    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1- prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);

    p_abs = p_tot - p_gas;

    double aconstant = qslFormulaSN_T_2932aConstant->at(cstdSN_T_2932->formula).toDouble();
    double bconstant = qslFormulaSN_T_2932bConstant->at(cstdSN_T_2932->formula).toDouble();
    double cconstant = qslFormulaSN_T_2932cConstant->at(cstdSN_T_2932->formula).toDouble();

    double ttime = cstdSN_T_2932->time;
    double vlratio = cstdSN_T_2932->vl_ratio;
    double para_measured = cstdSN_T_2932->temperature;

    result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

    QString formula;
    QString passfail;
    QString method = ui->leMethod->text();

    if(cstdSN_T_2932->formula==0)
    {
        ui->wResult->setMethod(tr("SN/T 2932 ASTM Results"));
        formula = "ASTM";
    }
    else if(cstdSN_T_2932->formula==1)
    {
        ui->wResult->setMethod(tr("SN/T 2932 EPA Results"));
        formula = "EPA";
    }
    else if(cstdSN_T_2932->formula==2)
    {
        ui->wResult->setMethod(tr("SN/T 2932 CARB Results"));
        formula = "CARB";
    }

    if(cstdSN_T_2932->passfail_enabled)
    {
        double cpr = cSettings.getPressureWS(result).toDouble();
        double from = cSettings.getPressureWS(cstdSN_T_2932->from).toDouble();
        double to = cSettings.getPressureWS(cstdSN_T_2932->to).toDouble();

        if( cpr >= from && cpr <= to) passfail = "Pass";
        else passfail = "Fail";
    }

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), passfail);

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::showResultFree(double prtpx1, double prtpx2, double prtpx3)
{
    int fn = getMethod() - M_METHOD_SN_T_2932;

    double ttime;
    double vlratio;
    double para_measured;

    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    double v1 = 1.7;
    double v2 = 2.5;
    double v3 = 5.0;

    p_tot = prtpx3;

    double tpr = (prtpx1- prtpx3) * (prtpx2- prtpx3);
    double bpr = (prtpx1 - prtpx3);
    double bv = ((v3-v1)/(v2-v1))*(prtpx1- prtpx2);
    double result = 0;

    p_gas = tpr/(bv-bpr);
    p_abs = p_tot - p_gas;

    QString passfail;
    double aconstant, bconstant, cconstant;
    int shakerSpeed;

    QString method = ui->leMethod->text();

    switch(fn)
    {
        case 1:

        ttime = cstdFree1->tpx1 + cstdFree1->tpx2 + cstdFree1->tpx3;
        vlratio = cstdFree1->vl_ratio;
        para_measured = cstdFree1->temperature;

        aconstant = cstdFree1->aconstant;
        bconstant = cstdFree1->bconstant;
        cconstant = cstdFree1->cconstant;

        result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

        if(cstdFree1->passfail_enabled)
        {
            double cpr = cSettings.getPressureWS(result).toDouble();
            double from = cSettings.getPressureWS(cstdFree1->from).toDouble();
            double to = cSettings.getPressureWS(cstdFree1->to).toDouble();

            if( cpr >= from && cpr <= to) passfail = "Pass";
            else passfail = "Fail";
        }

        if(cstdFree1->shaker_disabled){
            shakerSpeed = cstdFree1->shaker_speed;
        }

        break;

        case 2:

        ttime = cstdFree2->tpx1 + cstdFree2->tpx2 + cstdFree2->tpx3;
        vlratio = cstdFree2->vl_ratio;
        para_measured = cstdFree2->temperature;

        aconstant = cstdFree2->aconstant;
        bconstant = cstdFree2->bconstant;
        cconstant = cstdFree2->cconstant;

        result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

        if(cstdFree2->passfail_enabled)
        {
            double cpr = cSettings.getPressureWS(result).toDouble();
            double from = cSettings.getPressureWS(cstdFree2->from).toDouble();
            double to = cSettings.getPressureWS(cstdFree2->to).toDouble();

            if( cpr >= from && cpr <= to) passfail = "Pass";
            else passfail = "Fail";
        }

        if(cstdFree2->shaker_disabled){
            shakerSpeed = cstdFree2->shaker_speed;
        }

        break;

        case 3:

        ttime = cstdFree3->tpx1 + cstdFree3->tpx2 + cstdFree3->tpx3;
        vlratio = cstdFree3->vl_ratio;
        para_measured = cstdFree3->temperature;

        aconstant = cstdFree3->aconstant;
        bconstant = cstdFree3->bconstant;
        cconstant = cstdFree3->cconstant;

        result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

        if(cstdFree3->passfail_enabled)
        {
            double cpr = cSettings.getPressureWS(result).toDouble();
            double from = cSettings.getPressureWS(cstdFree3->from).toDouble();
            double to = cSettings.getPressureWS(cstdFree3->to).toDouble();

            if( cpr >= from && cpr <= to) passfail = "Pass";
            else passfail = "Fail";
        }

        if(cstdFree3->shaker_disabled){
            shakerSpeed = cstdFree3->shaker_speed;
        }

        break;

        case 4:

        ttime = cstdFree4->tpx1 + cstdFree4->tpx2 + cstdFree4->tpx3;
        vlratio = cstdFree4->vl_ratio;
        para_measured = cstdFree4->temperature;

        aconstant = cstdFree4->aconstant;
        bconstant = cstdFree4->bconstant;
        cconstant = cstdFree4->cconstant;

        result = (aconstant * p_tot) - (bconstant * p_gas) - cconstant;

        if(cstdFree4->passfail_enabled)
        {
            double cpr = cSettings.getPressureWS(result).toDouble();
            double from = cSettings.getPressureWS(cstdFree4->from).toDouble();
            double to = cSettings.getPressureWS(cstdFree4->to).toDouble();

            if( cpr >= from && cpr <= to) passfail = "Pass";
            else passfail = "Fail";
        }

        if(cstdFree4->shaker_disabled){
            shakerSpeed = cstdFree4->shaker_speed;
        }

        break;


    }


    QString str;
    QString formula;

    str = tr("Corr. Formula ") + "= " +
                        cSettings.getFormulaConstantsAB(aconstant) +
                        " x Ptot - " +
                        cSettings.getFormulaConstantsAB(bconstant) +
                        " x Pgas - " +
                        cSettings.getPressureFormula(cconstant);

    ui->wResult->setMethodFormula(tr("Free ") + QString::number(fn) + tr(" Results"), str);

    formula = "Free " + QString::number(fn);
    method =  "Free " + QString::number(fn);

    ui->wResult->setSampleId(ui->leSampleId->text());

    ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
    ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), "Pass");
    if(getMethod() == M_METHOD_NEW_FREE1 && cstdFree1->shaker_disabled){
        ui->wResult->setFreeShaker(cSettings.getShaker(shakerSpeed));
    }else if(getMethod() == M_METHOD_NEW_FREE2 && cstdFree2->shaker_disabled){
        ui->wResult->setFreeShaker(cSettings.getShaker(shakerSpeed));
    }else if(getMethod() == M_METHOD_NEW_FREE3 && cstdFree3->shaker_disabled){
        ui->wResult->setFreeShaker(cSettings.getShaker(shakerSpeed));
    }else if(getMethod() == M_METHOD_NEW_FREE4 && cstdFree4->shaker_disabled){
        ui->wResult->setFreeShaker(cSettings.getShaker(shakerSpeed));
    }

    ui->twMeasuring->hide();
    ui->wResult->setStatus("");
    ui->wResult->show();

    emit saveResult(p_tot, p_gas, p_abs,
                    method, formula,
                    aconstant, bconstant, cconstant,
                    result,
                    ttime, vlratio,
                    para_measured);
}

void sMeasuring::hideResult() 
{
    ui->wResult->setStatus("");
    ui->wResult->hide();
    ui->twMeasuring->show();
}

void sMeasuring::setRunState(bool rs)
{
    if(rs)
    {
        ui->pbRinse->setEnabled(false);
        ui->pbRun->setEnabled(false);
        ui->pbStop->setEnabled(true);
    }
    else
    {
        ui->pbRinse->setEnabled(true);
        ui->pbRun->setEnabled(true);
        ui->pbStop->setEnabled(false);
    }
}

bool sMeasuring::checkValidInputs()
{
  
    if( (!ui->leSampleId->hasAcceptableInput() || (0 && !ui->leSampleId->text().length()))
       ||(!ui->leOperator->hasAcceptableInput() || (0 && !ui->leOperator->text().length())))
    {
        return false;
    }
    else
        return true;
}

void sMeasuring::onShowKeypad(int tmp)
{
    emit showKeypad(QObject::sender(), KAYPAD_ALPHA_NUMERIC, true);
}

void sMeasuring::ontextChanged(QString tmp)
{

    QLineEdit *tle = qobject_cast<QLineEdit *>(QObject::sender());

    if(tle)
    {
        if((!tle->hasAcceptableInput()) || ( 0 && ((!tle->text().length()) || (tle->text().startsWith(' ')))))
        {
            tle->setProperty("error", true);
            tle->style()->polish(tle);
        }
        else
        {
            tle->setProperty("error", false);
            tle->style()->polish(tle);
        }

        setRunState(!checkValidInputs());

    }

}

void sMeasuring::setLblMessage(QString tmp){
    ui->lblMessage->setText(tmp);
}

void sMeasuring::setRunning(bool state)
{
    cRunState = state;

    switch(state)
    {
        case 0: 
                ui->wResult->setStatus("");
                ui->wResult->hide();
                ui->twMeasuring->show();

//                ui->cbMethod->setEnabled(true);
                ui->pbMethod->setEnabled(true);

                ui->leSampleId->setEnabled(true);
                ui->pbSampleId->setEnabled(true);
                ui->leOperator->setEnabled(true);
                ui->pbOperator->setEnabled(true);

                setRunState(!checkValidInputs());

                ui->lblMessage->setText(tr("Select new parameters OR\nPress Run to Start"));
                ui->lblMessage->resize(680,70);
                ui->lblAutoCount->hide();
                ui->lblStatus->hide();
                ui->lblStatus->setText("");

                break;

        case 1: //running
//                ui->cbMethod->setEnabled(false);
                ui->pbMethod->setEnabled(false);
                ui->leSampleId->setEnabled(false);
                ui->pbSampleId->setEnabled(false);
                ui->leOperator->setEnabled(false);
                ui->pbOperator->setEnabled(false);

                setRunState(true);

                ui->lblMessage->setText(tr("Measurement in progress"));
                ui->lblMessage->resize(680, 70);
                ui->lblAutoCount->hide(); 
                ui->lblStatus->show();

                saveLastIdsFile();
                break;

    }


}

void sMeasuring::setWaitACKStatus(bool tmp)
{
    if(!cRunState) ui->pbRun->setEnabled(!tmp);
}

bool sMeasuring::getWaitACKStatus()
{
    return true;
}

void sMeasuring::hideAfterACK(bool tmp)
{

}

bool sMeasuring::getHideAfterACK()
{
    return false;
}

void sMeasuring::on_pbRun_clicked()
{
    emit runClicked(MS_TEST_RUN, true);
}

void sMeasuring::on_pbStop_clicked()
{

    setRunning(0); 
    emit runClicked(MS_TEST_STOP, false);
}


void sMeasuring::on_pbStop_2_clicked()
{
    ui->twMeasuring->hide();
    ui->wResult->show();

    QString noperator = ui->leOperator->text();
    QString sampleID = ui->leSampleId->text(); 

    double p_tot = 0;
    double p_gas = 0;
    double p_abs = 0;

    QString formula = "";
    QString method = ui->leMethod->text();
    QString pass = "";

    double aconstant = 0;
    double bconstant = 0;
    double cconstant = 0;

    double result = 89.99;
    double ttime = 0;
    double vlratio = 0;
    double para_measured = 0;

    QString scale = qslPressureScale->at(cgs->pressure_scale);

    p_abs = 21.9012;
    p_gas = 76.09123;
    p_tot = 121.5456;
    para_measured = 37.78901;

    ui->wResult->setSampleId(sampleID);

    switch(getMethod())
    {
        case 0:

        ttime = cstdD5191->time;
        vlratio = cstdD5191->vl_ratio;
        para_measured = cstdD5191->temperature;

        aconstant = qslFormulaD5191aConstant->at(cstdD5191->formula).toDouble();
        bconstant = qslFormulaD5191bConstant->at(cstdD5191->formula).toDouble();
        cconstant = qslFormulaD5191cConstant->at(cstdD5191->formula).toDouble();

        if(cstdD5191->formula==0)
        {
            ui->wResult->setMethod(tr("DVPE <B>D5191</B> Results <B>ASTM</B>"));
            formula = "ASTM";
        }
        else if(cstdD5191->formula==1)
        {
            ui->wResult->setMethod(tr("DVPE <B>D5191</B> Results <B>EPA</B>"));
            formula = "EPA";
        }
        else if(cstdD5191->formula==2)
        {
            ui->wResult->setMethod(tr("DVPE <B>D5191</B> Results <B>CARB</B>"));
            formula = "CARB";
        }

        ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
        ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), "Pass");

        break;

        case 1:
        formula = ui->leMethod->text();

        ttime = cstdD6377->time;
        vlratio = cstdD6377->vl_ratio;
        para_measured = cstdD6377->temperature;


        ui->wResult->setMethod(tr("VPCR₄ Ptotal <B>D6377</B> Results"));
        ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
        ui->wResult->setVLPr(cSettings.getVLRatio(vlratio), cSettings.getPressureWS(para_measured), cSettings.getTemperatureScale() , "PASS");

        formula = "VPCR₄";
        break;

        case 2:
        aconstant = qslFormulaD6378aConstant->at(cstdD6378->formula).toDouble();
        bconstant = qslFormulaD6378bConstant->at(cstdD6378->formula).toDouble();
        cconstant = qslFormulaD6378cConstant->at(cstdD6378->formula).toDouble();

        ttime = cstdD6378->time;
        vlratio = cstdD6378->vl_ratio;
        para_measured = cstdD6378->temperature;

        if(cstdD6378->formula==0)
        {
            ui->wResult->setMethod(tr("Triple expansion <B>D6378</B><br>Results <B>ASTM</B>"));
            formula = "ASTM";
        }
        else if(cstdD6378->formula==1)
        {
            ui->wResult->setMethod(tr("Triple expansion <B>D6378</B><br>Results <B>EPA</B>"));
            formula = "EPA";
        }
        else if(cstdD6378->formula==2)
        {
            ui->wResult->setMethod(tr("Triple expansion <B>D6378</B><br>Results <B>CARB</B>"));
            formula = "CARB";
        }

        ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
        ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), "Fail");

        break;

        case 3:
        vlratio = cstdD5188->vl_ratio;
        para_measured = cstdD5188->pressure;

        ui->wResult->setMethod(tr("V/L <B>D5188</B> Results"));
        ui->wResult->setResult(cSettings.getTemperatureWS(result), cSettings.getTemperatureScale());
        ui->wResult->setVLPr(cSettings.getVLRatio(vlratio), cSettings.getPressureWS(para_measured), cSettings.getPressureScale(), "PASS");
        formula = "T V/L"; 

        break;

        case 4:
        
        ttime = cstdFree1->tpx1 + cstdFree1->tpx2 + cstdFree1->tpx3;
        vlratio = cstdFree1->vl_ratio;
        para_measured = cstdFree1->temperature;

        aconstant = cstdFree1->aconstant;
        bconstant = cstdFree1->bconstant;
        cconstant = cstdFree1->cconstant;

        {
            QString str;
            str = tr("Free 1 = ") +
                                cSettings.getFormulaConstantsAB(aconstant) +
                                " x Ptot - " +
                                cSettings.getFormulaConstantsAB(bconstant) +
                                " x Pgas - " +
                                cSettings.getPressureFormula(cconstant);

            ui->wResult->setMethodFormula(tr("<B>Free 1 </B>Results"), str);
        }


        ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
        ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), "Pass");

        formula = "Free 1";

        method = "Free 1";

        break;

        case 5: 

        ttime = cstdFree2->tpx1 + cstdFree2->tpx2 + cstdFree2->tpx3;
        vlratio = cstdFree2->vl_ratio;
        para_measured = cstdFree2->temperature;

        aconstant = cstdFree2->aconstant;
        bconstant = cstdFree2->bconstant;
        cconstant = cstdFree2->cconstant;

        {
            QString str;
            str = tr("Free 2 = ") +
                                cSettings.getFormulaConstantsAB(aconstant) +
                                " x Ptot - " +
                                cSettings.getFormulaConstantsAB(bconstant) +
                                " x Pgas - " +
                                cSettings.getPressureFormula(cconstant);

            ui->wResult->setMethodFormula(tr("<B>Free 2 </B>Results"), str);
        }

        ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
        ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), "Pass");

        formula = "Free 2";
        method = "Free 2";

        break;

        case 6:
        
        ttime = cstdFree3->tpx1 + cstdFree3->tpx2 + cstdFree3->tpx3;
        vlratio = cstdFree3->vl_ratio;
        para_measured = cstdFree3->temperature;

        aconstant = cstdFree3->aconstant;
        bconstant = cstdFree3->bconstant;
        cconstant = cstdFree3->cconstant;

        {
            QString str;
            str = tr("Free 3 = ") +
                                cSettings.getFormulaConstantsAB(aconstant) +
                                " x Ptot - " +
                                cSettings.getFormulaConstantsAB(bconstant) +
                                " x Pgas - " +
                                cSettings.getPressureFormula(cconstant);

            ui->wResult->setMethodFormula(tr("<B>Free 3 </B>Results"), str);
        }

        ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
        ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), "Pass");

        formula = "Free 3";
        method = "Free 3";

        break;

        case 7:
        ttime = cstdFree4->tpx1 + cstdFree4->tpx2 + cstdFree4->tpx3;
        vlratio = cstdFree4->vl_ratio;
        para_measured = cstdFree4->temperature;

        aconstant = cstdFree4->aconstant;
        bconstant = cstdFree4->bconstant;
        cconstant = cstdFree4->cconstant;

        {

            QString str;
            str = tr("Free 4 = ") +
                                cSettings.getFormulaConstantsAB(aconstant) +
                                " x Ptot - " +
                                cSettings.getFormulaConstantsAB(bconstant) +
                                " x Pgas - " +
                                cSettings.getPressureFormula(cconstant);

            ui->wResult->setMethodFormula(tr("<B>Free 4 </B>Results"), str);
        }


        ui->wResult->setResult(cSettings.getPressureWS(result), cSettings.getPressureScale());
        ui->wResult->set3Prs(cSettings.getPressureWS(p_abs), cSettings.getPressureWS(p_gas), cSettings.getPressureWS(p_tot), cSettings.getPressureScale(), "Pass");

        formula = "Free 4";
        method = "Free 4";
        break;
    }

    /*
    for(int tmp =0; tmp <990; tmp++)
    {

        emit saveResult(
                        p_tot, p_gas, p_abs,
                        method, formula,
                        aconstant, bconstant, cconstant,
                        result,
                        ttime, vlratio,
                        para_measured);
    }
    */
}


void sMeasuring::on_pbSampleId_clicked()
{
    if(ui->lwOperator->isVisible()) ui->lwOperator->hide();

    if(ui->lwSampleId->count() > 0)
    {
        if(ui->lwSampleId->isVisible())
        {
            ui->lwSampleId->hide();
            ui->leSampleId->setFocus();
        }
        else
        {
            QList<QListWidgetItem *> items = ui->lwSampleId->findItems(ui->leSampleId->text(), Qt::MatchExactly);
            if(!(items.isEmpty())){
                ui->lwSampleId->setCurrentItem(ui->lwSampleId->findItems(ui->leSampleId->text(), Qt::MatchExactly).at(0));
                ui->lwSampleId->scrollToItem(ui->lwSampleId->currentItem());
                ui->lwSampleId->show();
                ui->lwSampleId->setFocus();
            }else{
                ui->lwSampleId->show();
            }
        }
    }
    else
        ui->leSampleId->setFocus();

}

void sMeasuring::onClickSampleId()
{
    ui->lwSampleId->hide();
}

void sMeasuring::on_leSampleId_textChanged(const QString &arg1)
{
    if(ui->lwSampleId->isVisible())
    {
        ui->lwSampleId->findItems(arg1, Qt::MatchStartsWith);
    }
}

void sMeasuring::on_lwSampleId_itemClicked(QListWidgetItem *item)
{
    ui->lwSampleId->hide();
    ui->leSampleId->clear();
    ui->leSampleId->insert(ui->lwSampleId->currentItem()->text());
    cPrevSampleId = ui->leSampleId->text();
    ui->leSampleId->setFocus();
}

void sMeasuring::on_leSampleId_returnPressed()
{
    if(ui->leSampleId->text().count() > 0 && cPrevSampleId != ui->leSampleId->text())
    {
        if(!ui->lwSampleId->findItems( ui->leSampleId->text(), Qt::MatchExactly).count())
        {
            if(ui->lwSampleId->count() >= SAMPLE_IDS_MAX)
            {
                int row = ui->lwSampleId->count()-1;
                delete ui->lwSampleId->takeItem(row);
            }

            ui->lwSampleId->insertItem(0, ui->leSampleId->text());
            saveSampleIdsFile();
        }
    }
    else
    {
        deleteSampleIdsFile();
    }

    cPrevSampleId = ""; 
}

void sMeasuring::onClickOperator()
{
    ui->lwOperator->hide();
}

void sMeasuring::onClickMethod(){
    ui->lwMethods->hide();
}

void sMeasuring::on_pbOperator_clicked()
{
    if(ui->lwSampleId->isVisible()) ui->lwSampleId->hide();

    if(ui->lwOperator->count() > 0)
    {
        if(ui->lwOperator->isVisible())
        {
            ui->lwOperator->hide();
            ui->leOperator->setFocus();
        }
        else
        {
            QList<QListWidgetItem *> items = ui->lwOperator->findItems(ui->leOperator->text(), Qt::MatchExactly);
            if(!(items.isEmpty())){
                ui->lwOperator->setCurrentItem(ui->lwOperator->findItems(ui->leOperator->text(), Qt::MatchExactly).at(0));
                ui->lwOperator->scrollToItem(ui->lwOperator->currentItem());
                ui->lwOperator->show();
                ui->lwOperator->setFocus();
            }
            else{
                ui->lwOperator->show();
            }
        }
    }
    else
        ui->leOperator->setFocus();
}

void sMeasuring::on_lwOperator_itemClicked(QListWidgetItem *item)
{
    ui->lwOperator->hide();
    ui->leOperator->clear();
    ui->leOperator->insert(ui->lwOperator->currentItem()->text());
    cPrevOperator = ui->leOperator->text();
    ui->leOperator->setFocus();
}

void sMeasuring::on_leOperator_textChanged(const QString &arg1)
{
    if(ui->lwOperator->isVisible())
    {
        ui->lwOperator->findItems(arg1, Qt::MatchStartsWith);
    }
}

void sMeasuring::on_leOperator_returnPressed()
{
    if(ui->leOperator->text().count() > 0 && cPrevOperator != ui->leOperator->text())
    {
        if(!ui->lwOperator->findItems( ui->leOperator->text(), Qt::MatchExactly).count())
        {
            if(ui->lwOperator->count() >= OPERATORS_IDS_MAX)
            {
                int row = ui->lwOperator->count()-1;
                delete ui->lwOperator->takeItem(row);
            }

            ui->lwOperator->insertItem(0, ui->leOperator->text());
            saveOperatorsFile();
        }
    }
    else
    {
        deleteOperatorsFile();
    }

    cPrevOperator = ""; 
}


void sMeasuring::on_imageCapture_clicked()
{
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists()) {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

//        QString filename = QApplication::applicationDirPath() + QString("/screenshot/_%1_smeasuring_%1.png").arg(timestamp);
        QString filename = QString("/run/media/sda1/screenshot/_%1_smeasuring.png").arg(timestamp);
        QWidget *widget = QApplication::activeWindow();
        QPixmap pixmap = QPixmap::grabWidget(widget);
        ui->imageCapture->setFocusPolicy(Qt::NoFocus);
        qDebug()<<"path : "<<filename;
        pixmap.save(QString(filename));
    }else{
        qDebug()<<"folder doesn't exist";
    }

}

void sMeasuring::on_pbRinse_clicked()
{
    emit runClicked(MS_RINSING_RUN, false);
}

void sMeasuring::on_pbMethod_clicked()
{
    if(ui->lwOperator->isVisible()) ui->lwOperator->hide();
    if(ui->lwSampleId->isVisible()) ui->lwSampleId->hide();
    ui->lwMethods->show();
}

void sMeasuring::on_lwMethods_itemClicked(QListWidgetItem *item)
{
    ui->lwMethods->hide();
    ui->leMethod->clear();
    ui->leMethod->setText(ui->lwMethods->currentItem()->text());
    ui->leMethod->setFocus();
}
