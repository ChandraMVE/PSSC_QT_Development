#include "ssettings.h"

struct GENERAL_SETUP *sSettings::sSettings::cgs = 0;
struct USER_SETUP *sSettings::sSettings::cus = 0;

struct CALIB_TEMPERATURE *sSettings::sSettings::ctm = 0;
struct CALIB_PRESSURE *sSettings::sSettings::cpr = 0;

QStringList *sSettings::qslPressureScale;
QStringList *sSettings::qslTemperatureScale;
QStringList *sSettings::qslPressureMultiplier;
QStringList *sSettings::qslPressureDP;
QStringList *sSettings::qslTemperatureDP;
QStringList *sSettings::qslShowDateFormat;
QStringList *sSettings::qslShowTimeFormat;

sSettings::sSettings()
{

}

void sSettings::setGeneralSetup(GENERAL_SETUP *lcgs)
{
    cgs = lcgs;
}

void sSettings::setUserSetup(USER_SETUP *lcus)
{
    cus = lcus;
}

void sSettings::setTemperatureCalib(CALIB_TEMPERATURE *lctm)
{
    ctm = lctm;
}

void sSettings::setPressureCalib(CALIB_PRESSURE *lcpr)
{
    cpr = lcpr;
}

QString sSettings::getCompany()
{
    return cgs->company;
}

QString sSettings::getLocation()
{
    return cgs->location;
}

QString sSettings::getUnitId()
{
    return cgs->unit_id;
}

QString sSettings::getSerialNo()
{
    QString fname = QApplication::applicationDirPath() + FN_SERIAL_SETUP;
    QString str = "RVP_Demo_Device";
    QFile in(fname);

    if(in.open(QIODevice::ReadOnly))
    {

        QTextStream intx(&in);
        str = intx.readLine();
        in.close();
    }

    return str;
}

int sSettings::getPageSize()
{
    return cgs->page_size;
}

int sSettings::getReportFormat()
{
    return cgs->report_format;
}

qint32 sSettings::getBaud()
{
    switch(cgs->baud)
    {
        case 0: return QSerialPort::Baud2400; break;
        case 1: return QSerialPort::Baud4800; break;
        case 2: return QSerialPort::Baud9600; break;
        case 3: return QSerialPort::Baud19200; break;
        default: return QSerialPort::Baud9600; break;
    }
}

QSerialPort::Parity sSettings::getParity()
{
    switch(cgs->parity)
    {
        case 0:  return QSerialPort::NoParity; break;
        case 1:  return QSerialPort::OddParity; break;
        case 2:  return QSerialPort::EvenParity; break;
        default: return QSerialPort::OddParity; break;
    }
}

QSerialPort::FlowControl sSettings::getFlowControl()
{
    switch(cgs->flow)
    {
        case 0: return QSerialPort::NoFlowControl; break;
        case 1: return QSerialPort::SoftwareControl; break;
        case 2: return QSerialPort::HardwareControl; break;
        default: return QSerialPort::NoFlowControl; break;
    }
}

QSerialPort::StopBits sSettings::getStopBits()
{
    switch(cgs->stop_bits)
    {
        case 0: return QSerialPort::OneStop; break;
        case 1: return QSerialPort::TwoStop; break;
        default: return QSerialPort::OneStop; break;
    }
}

QSerialPort::DataBits sSettings::getDataBits()
{
    switch(cgs->data_bits)
    {
        case 0: return QSerialPort::Data7; break;
        case 1: return QSerialPort::Data8; break;
        default: return QSerialPort::Data8; break;
    }
}


QString sSettings::getDateFormat() const
{
    return qslShowDateFormat->at(cgs->date_format);
}

QString sSettings::getTimeFormat() const
{
    return qslShowTimeFormat->at(cgs->time_format);
}

QString sSettings::getDate(QString tmp) const
{
    QDateTime dt = QDateTime::fromString(tmp, STORAGE_DATETIME_FORMAT);

    return dt.toString(qslShowDateFormat->at(cgs->date_format));
}

QString sSettings::getTime(QString tmp) const
{
    QDateTime dt = QDateTime::fromString(tmp, STORAGE_DATETIME_FORMAT);
    return dt.toString(qslShowTimeFormat->at(cgs->time_format));
}

QString sSettings::getDateTime(QString tmp) const
{
    QString str;
    QDateTime dt = QDateTime::fromString(tmp, STORAGE_DATETIME_FORMAT);

    str = qslShowDateFormat->at(cgs->date_format) + " " +
          qslShowTimeFormat->at(cgs->time_format);

    return dt.toString(str);
}

QString sSettings::saveDateTime(QString tmp) const
{
    QString str;
    str = qslShowDateFormat->at(cgs->date_format) + " " +
          qslShowTimeFormat->at(cgs->time_format);

    QDateTime dt = QDateTime::fromString(tmp, str);

    return dt.toString(STORAGE_DATETIME_FORMAT);
}

QDateTime sSettings::getCurrentDateTime() const
{
    QDateTime cdt;
    cdt = QDateTime::currentDateTime().addSecs(cgs->gmt);
    return cdt;
}

QString sSettings::getTemperatureLive(int tm)
{
    double ttm = calculateTemperature(tm);

    return (QString::number(ttm, 'f', 2));
}

QString sSettings::getPressureLive(int tm, int pr) 
{
    double tpr = calculatePressure(tm, pr);

    return (QString::number(tpr, 'f', 1)); 
}

int sSettings::getTemperatureCount(double tm) 
{
    return calculateTemperatureCount(tm);
}

int sSettings::getPressureCount(double pr)  
{

    int cnt = calculatePressureCount(pr);

    if(cnt  < 0) return 0;
    else return cnt;

}

double sSettings::getTemperatureCelsius(int tm)
{
    double ttm = calculateTemperature(tm);

    return ttm;
}

double sSettings::getTemperatureMM(int tm)
{
    double ttm = calculateTemperature(tm);

    if(!cgs->temperature_scale) 
        return ttm;
    else
        return ((ttm *  9/5) + 32);
}

double sSettings::calculateTemperature(int tm)
{
    return (ctm->slope * tm + ctm->constant) + ctm->toffset;   
}

double sSettings::calculatePressure(int tmp, int pr)
{
    int index = cpr->prl_index;

    double pr20 = (cpr->slope20 * pr + cpr->constant20);

    if(!cpr->prl_index)
    {
        return pr20;
    }
    else
    {
        double tm = calculateTemperature(tmp);

        float value = (int)(tm * 100 + .5);
        
        tm = (float)value / 100;
        
        for(;index>=0; index--)
        {
           
            if( tm >= cpr->prl_temperature[index] || index == 0)
            {
                    double low = (cpr->prl_low_correction[index] + (tm-cpr->prl_temperature[index]) * ((cpr->prl_low_correction[index+1]-cpr->prl_low_correction[index]) / (cpr->prl_temperature[index+1]-cpr->prl_temperature[index])));
                    double high = (cpr->prl_high_correction[index] + (tm-cpr->prl_temperature[index]) * ((cpr->prl_high_correction[index+1]-cpr->prl_high_correction[index]) / (cpr->prl_temperature[index+1]-cpr->prl_temperature[index])));

                    double prc;

                    if(index != cpr->prl_index)
                    {
                        prc = (low + (pr20 - cpr->prl_low) * ((high-low) / (cpr->prl_high-cpr->prl_low)));
                    }
                    else
                    {
                        prc = (cpr->prl_slope[index] * pr20 + cpr->prl_constant[index]);
                    }

                   

                    return (pr20 + prc);

            }
        }
    }
}

int sSettings::calculateTemperatureCount(double tm)
{
    double dx, dy, sl, cc;
    dx = ctm->thigh - ctm->tlow;
    dy = ctm->thigh_count - ctm->tlow_count;
    sl = dy/dx;
    cc = ctm->thigh_count - (sl*ctm->thigh);

    return (sl*(tm-ctm->toffset)+cc); 
}

int sSettings::calculatePressureCount(double tm)
{
    double dx, dy, sl, cc;
    dx = cpr->phigh - cpr->plow;
    dy = cpr->phigh_count - cpr->plow_count;
    sl = dy/dx;
    cc = cpr->phigh_count - (sl*cpr->phigh);

    return (sl*tm+cc);
}

QString sSettings::getTemperatureLiveSS(int tm)
{
    double ttm = calculateTemperature(tm);
    
    if(!cgs->temperature_scale) 
        return (QString::number(ttm, 'f', RANGE_CALIB_TEMPERATURE_PRECISION));
    else
        return (QString::number((ttm *  9/5) + 32, 'f', RANGE_CALIB_TEMPERATURE_PRECISION));
}

QString sSettings::getPressureLiveSS(int tm, int pr) 
{
    
    double tpr = calculatePressure(tm, pr);

    return (QString::number(tpr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', RANGE_CALIB_PRESSURE_PRECISION));
}

QString sSettings::getTemperatureCS(double tm) const
{
    return (QString::number(tm, 'f', 2));
}

QString sSettings::getPressureCS(double tm) const
{
    return (QString::number(tm, 'f', 1));
}

QString sSettings::getTemperature(double tm) const
{
    if(!cgs->temperature_scale) 
        return (QString::number(tm, 'f', qslTemperatureDP->at(cgs->temperature_scale).toInt())) + " C";
    else
        return (QString::number((tm *  9/5) + 32, 'f', qslTemperatureDP->at(cgs->temperature_scale).toInt())) + " F"; 
}

QString sSettings::printGetTemperature(double tm) const
{
    if(!cgs->temperature_scale)
        return (QString::number(tm, 'f', 1)) + " C";
    else
        return (QString::number((tm *  9/5) + 32, 'f', 1)) + " F";
}

QString sSettings::getTemperatureWS(double tm) const
{
    if(!cgs->temperature_scale) 
        return (QString::number(tm, 'f', qslTemperatureDP->at(cgs->temperature_scale).toInt()));
    else
        return (QString::number((tm *  9/5) + 32, 'f', qslTemperatureDP->at(cgs->temperature_scale).toInt()));
}

QString sSettings::getTemperatureMS(double tm) const  
{
    if(!cgs->temperature_scale) 
    {
        return (QString::number(tm, 'f', 1));
    }
    else
    {
        return (QString::number((tm *  9/5) + 32, 'f', 1));
    }
}

double sSettings::getTemperatureCelsiusMS(double tm) 
{
    if(!cgs->temperature_scale) 
    {
        return tm;
    }
    else
    {
        return ((tm -32) *  5/9); 
    }
}

QString sSettings::getTemperatureScale() const
{
    return qslTemperatureScale->at(cgs->temperature_scale);
}

QString sSettings::getPressure(double pr) const
{
    return (QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', 3)) + " " + qslPressureScale->at(cgs->pressure_scale);
}

QString sSettings::printGetPressure(double pr) const
{
    return (QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', 1)) + " " + qslPressureScale->at(cgs->pressure_scale);
}

QString sSettings::getPressureWS(double pr) const
{
    return (QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', qslPressureDP->at(cgs->pressure_scale).toInt()));
}

QString sSettings::getPressureMS(double pr) const
{
    return (QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', qslPressureDP->at(cgs->pressure_scale).toInt()));
}

QString sSettings::getPressureNMS(double pr) const
{
    if(cgs->pressure_scale==0)
    {
        return ((QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', 3))+" kPa");
    }
    else if(cgs->pressure_scale==1)
    {
        return ((QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', 3))+" psi");
    }
    else if(cgs->pressure_scale==2)
    {
        return ((QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', 3))+" hPa");
    }
    else
    {
        return ((QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', 3))+" ATM");
    }
}

QString sSettings::getPressureNaMS(double pr) const
{
    return (QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', 3));
}

double sSettings::getPressurekPaMS(double pr)
{
    return (pr/qslPressureMultiplier->at(cgs->pressure_scale).toDouble());
}

double sSettings::getPressurekPaMM(int tm, int pr)
{
    double tpr = calculatePressure(tm, pr);

    return tpr;
}

int sSettings::getPressureDPMS()
{
    return qslPressureDP->at(cgs->pressure_scale).toInt();
}

QString sSettings::getPressureFormula(double pr) const
{
    return (QString::number(pr * qslPressureMultiplier->at(cgs->pressure_scale).toDouble(), 'f', 3));
}

QString sSettings::getPressureScale() const
{
    return qslPressureScale->at(cgs->pressure_scale);
}

QString sSettings::getPressure(QString method, double pr) const
{
    if(method == "D5188" || method == "D6377") return "";
    else return getPressure(pr);
}

QString sSettings::printGetPressure(QString method, double pr) const
{
    if(method == "D5188" || method == "D6377") return "";
    else return printGetPressure(pr);
}

QString sSettings::getFormula(QString method, QString formula, double aconst, double bconst, double cconst) const
{
    if(method =="D5188" || method =="D6377" )
        return formula;
    else
    {
        QString str = formula + " = " +
                        getFormulaConstantsAB(aconst) +
                        " x Ptot - " +
                        getFormulaConstantsAB(bconst) +
                        " x Pgas - " +
                        getPressure(cconst);
        return str;
    }
}

QString sSettings::getResult(QString method, double result) const
{
    if(method =="D5188")
        return getTemperature(result);
    else
        return getPressure(result);
}

QString sSettings::printGetResult(QString method, double result) const
{
    if(method =="D5188")
        return printGetTemperature(result);
    else
        return printGetPressure(result);
}

QString sSettings::getTestTime(double ttime) const
{
    return (QString::number(ttime, 'f', 0));
}

QString sSettings::getShakerSpeed(double ss) const
{
    return (QString::number(ss, 'f', 1));
}

QString sSettings::getTestTime(QString method, double ttime) const
{
    if(method == "D5188") return "";
    else
        return (QString::number(ttime, 'f', 0));
}

QString sSettings::getParaMeasured(QString method, double pm) const
{
    if(method == "D5188")
        return getPressure(pm);
    else
        return getTemperature(pm);
}

QString sSettings::getVLRatio(double vl) const
{
    return (QString::number(vl, 'f', 2));
}

QString sSettings::getShaker(int sh) const
{
    float tmp = sh/(60.0);
    return (QString::number(tmp,'f',1));
}

QString sSettings::getFormulaConstantsAB(double constants) const
{
    return (QString::number(constants, 'f', 3));
}

bool sSettings::checkUSBMounted()
{

    QString str = "mount | grep sda1";

    QProcess process;
    process.start("sh", QStringList()<< "-c" << str);

    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    QString err = process.readAllStandardError();

    if(output.contains("/run/media/sda1"))
    {
        return true;
    }
    else
        return false;
}

bool sSettings::checkFolderExists(QString ff)
{
    QDir* rootDir = new QDir(ff);
    return rootDir->exists();
}

bool sSettings::checkFileExists(QString ff)
{
    return QFile(ff).exists();
}

bool sSettings::removeTmpFiles()
{
    QString rdir = QApplication::applicationDirPath() + "/tmp";

    bool result = true;

    QDir dir(rdir);

    if (dir.exists(rdir)) {

        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {

            if (info.isFile())
                result = QFile::remove(info.absoluteFilePath());

            if (!result) {
                return result;
            }
        }

    }
    return result;
}


