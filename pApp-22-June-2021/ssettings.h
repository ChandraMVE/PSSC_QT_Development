#ifndef SSETTINGS_H
#define SSETTINGS_H

#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QProcess>
#include <QSerialPort>
#include "defaults_calibration.h"

#include <sgeneralsetup.h>
#include <susersetup.h>
#include <scalibration.h>

class sSettings
{
    static struct GENERAL_SETUP *cgs;
    static struct USER_SETUP *cus;
    static struct CALIB_TEMPERATURE *ctm;
    static struct CALIB_PRESSURE *cpr;

public:
    static QStringList *qslPressureScale;
    static QStringList *qslTemperatureScale;
    static QStringList *qslPressureMultiplier;
    static QStringList *qslPressureDP;
    static QStringList *qslTemperatureDP;
    static QStringList *qslShowDateFormat;
    static QStringList *qslShowTimeFormat;

public:
    sSettings();
    void setGeneralSetup(struct GENERAL_SETUP *lcgs);
    void setUserSetup(struct USER_SETUP *lcus);
    void setTemperatureCalib(struct CALIB_TEMPERATURE *lctm);
    void setPressureCalib(struct CALIB_PRESSURE *lcpr);

    QString getCompany();
    QString getLocation();
    QString getUnitId();
    QString getSerialNo();
    int getPageSize();
    int getReportFormat();

    qint32 getBaud();
    QSerialPort::Parity getParity();
    QSerialPort::FlowControl getFlowControl();
    QSerialPort::StopBits getStopBits();
    QSerialPort::DataBits getDataBits();

    QString getDateFormat(void) const;
    QString getTimeFormat(void) const;

    QString getDate(QString tmp) const;
    QString getTime(QString tmp) const;

    QString getDateTime(QString tmp) const;
    QString saveDateTime(QString tmp) const;

    QDateTime getCurrentDateTime(void) const;


    QString getTemperatureLive(int tm);
    QString getPressureLive(int tm, int pr);

    int getTemperatureCount(double tm); 
    double getTemperatureCelsius(int tm); 
    int getPressureCount(double pr);

    double getTemperatureMM(int tm); 

    double calculateTemperature(int tm);
    double calculatePressure(int tm, int pr);
    int calculateTemperatureCount(double tm);
    int calculatePressureCount(double tm);

    QString getTemperatureLiveSS(int tm); 
    QString getPressureLiveSS(int tm, int pr); 

    QString getTemperatureCS(double tm) const; 
    QString getPressureCS(double tm) const; 

    QString getTemperature(double tm) const;
    QString printGetTemperature(double tm) const;
    QString getTemperatureWS(double tm) const;
    QString getTemperatureMS(double tm) const;
    double  getTemperatureCelsiusMS(double tm);
    QString getTemperatureScale(void) const;

    QString getPressure(double pr) const;
    QString printGetPressure(double pr) const;
    QString getPressureWS(double pr) const;
    QString getPressureMS(double pr) const;
    QString getPressureNMS(double pr) const; //naveen
    QString getPressureNaMS(double pr) const; //naveen
    double getPressurekPaMS(double pr);

    double getPressurekPaMM(int tm, int pr); 

    int getPressureDPMS(void);
    QString getPressureFormula(double pr) const;
    QString getPressureScale(void) const;

    QString getPressure(QString method, double pr) const;
    QString printGetPressure(QString method, double pr) const;
    QString getFormula(QString method, QString formula, double aconst, double bconst, double cconst) const;
    QString getResult(QString method, double result) const;
    QString printGetResult(QString method, double result) const;
    QString getTestTime(double ttime) const;
    QString getTestTime(QString method, double ttime) const;
    QString getShakerSpeed(double ttime) const;

    QString getParaMeasured(QString method, double pm) const;
    QString getVLRatio(double vl) const;
    QString getShaker(int sh) const;
    QString getFormulaConstantsAB(double constants) const;

    bool checkUSBMounted(void);
    bool checkFolderExists(QString ff);
    bool checkFileExists(QString ff);
    bool removeTmpFiles(void);

};

#endif // SSETTINGS_H
