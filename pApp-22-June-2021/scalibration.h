#ifndef SCALIBRATION_H
#define SCALIBRATION_H

#include <QWidget>
#include <QDoubleValidator>
#include <QProcess>

#include <defines.h>
#include <defaults_calibration.h>

#include <ssettings.h>
#include <sprotocol.h>

namespace Ui {
class sCalibration;
}

struct CALIB_TEMPERATURE {
    int method;

    double tlow;
    int tlow_count;

    double thigh;
    int thigh_count;

    double tzero;
    double toffset;

    double tgain;
    double slope;
    double constant;
};

struct CALIB_PRESSURE {

    double plow;
    int plow_count;

    double phigh;
    int phigh_count;

    double pzero;
    double poffset;

    double pgain;

    double slope20;
    double constant20;


    int prl_index;
    double prl_low;
    double prl_high;

    bool prl_enabled[20];
    int prl_temperature[20];
    double prl_low_correction[20];
    double prl_high_correction[20];
    double prl_slope[20];
    double prl_constant[20];

};


class sCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit sCalibration(QWidget *parent = 0);
    ~sCalibration();
    void Show();
    void setDefaults(void);
    bool readFile();
    bool saveFile();

    void showTemperatureCalib();
    void updateTemperatureCalib();
    void showPressureCalib();
    void updatePressureCalib();
    void onLiveData(int cValvePosition, int cRawCTemperature,int cRawCPressure, int cCurrentUCError);
    void initAvg(void);
    int doAvg(int tmp);
    int getAvg();

    void updatePressureStatus();
    void handleCalib(void);
    void abortCurrentProcess(void);

    QString getTemperatureCS(double tm) const; 
    QString getPressureCS(double tm) const; 
    int getTemperatureCount(double tm);  
    QString getTemperatureLive(int tm);
    QString getPressureLive(int pr) const;
    double getPressure20(int pr);
    double getSlope(double tmh, int tmhc, double tmhl, int tmlc);
    double getConstant(double tmh, double tmsl, int tmhc);

    int getTFirst();
    int getTFinal();

    void setTempTabReadOnly(bool tmp);
    void setPressureTabReadOnly(bool tmp);

    void setPRLRunning(int tmp);
    bool isLinerzationVisible(void);
    void setAutoCalibrationStatus(QString tmp);
    void setAutoCalibrationSubStatus(QString tmp);

    void setZero(int tmp, double ctmp);
    void setAmbient(int tmp, double ctmp);
    void setLivePrTable(void);
    int getLinerizationCount(void);

signals:
    void showKeypad(QObject *, int, bool);
    void showHome(bool);
    void getConfirmation(int);
    void sendCommand(QString cmd);
    void runClicked(int state, bool init);
    void showMsgBox(QString title, QString msg);
    void showStatusBox(QString title, QString msg);
    void updateMainWindow(void);


private slots:
    void onShowKeypad(int tmp);
    void on_pbSave_clicked();

    void on_pbExit_clicked();

    void on_pbPCPCal_clicked();

    void on_pbTCTOffset_clicked();

    void on_tvPressure_cellClicked(int row, int column);

    void on_lePrHidden_editingFinished();

    void on_pbTCTOffsetSet_clicked();

    void on_pbTCTHighSet_clicked();

    void on_pbTCTLowSet_clicked();

    void on_pbTCTSet_clicked();

    void on_cbTCTEnable_clicked();

    void on_cbTCalibMethod_currentIndexChanged(int index);
    void ontextChanged(QString tmp);

    void on_cbPCTEnable_clicked();

    void on_pbPCTSet_clicked();

    void on_pbPCPLowSet_clicked();

    void on_pbPCPHighSet_clicked();

    void on_pbTouchCalibrate_clicked();

    void on_twCalibration_currentChanged(int index);

    void on_pbPCAutoStart_clicked();
    void on_pbPCAutoStop_clicked();

    void on_cbPCSelectorValve_currentIndexChanged(int index);

    void on_pbPCTableShow_clicked();


private:
    Ui::sCalibration *ui;
    bool cParasChanged;

    QWidget *cWidgetPressure;
    QString cStringPressure;

    QWidget *cWidgetPrLinear;
    QString cStringPrLinear;

    QWidget *cWidgetPrLinearzation;
    QString cStringPrLinearzation;

    int cTemperatureCount;
    int cPressureCount;

    double cTCTLow;
    double cTCTHigh;
    int cTCTLowCount;
    int cTCTHighCount;

    double cPCPLow;
    double cPCPHigh;
    int cPCPLowCount;
    int cPCPHighCount;

    int cAvgSum;
    int cAvgCount;
    int cAvgWaitPeriod;
    int cAvgBuffer[AVG_BUFFER_SIZE];
    int cStage;

    int cPrAutoCalibIndex;

    sProtocol cProtocol;
    int cPrevTab;

public:
    struct CALIB_TEMPERATURE cCalibTm;
    struct CALIB_PRESSURE cCalibPr;

};

#endif // SCALIBRATION_H

