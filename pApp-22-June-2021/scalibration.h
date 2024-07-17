#ifndef SCALIBRATION_H
#define SCALIBRATION_H

#include <QWidget>
#include <QDoubleValidator>
#include <QProcess>
#include <QListView>

#include <defines.h>
#include <defaults_calibration.h>

#include <ssettings.h>
#include <sprotocol.h>
#include "saccesswidget.h"

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

struct METHOD_VOLUME_CALIB{
    double StageVolume;
    double FirstVolume;
    double SecondVolume;
    double ThirdVOlume;
};

struct METHOD_VOLUME_CALIBD5191{
    double StageVolume;
    double FirstVolume;
    double SecondVolume;
    double ThirdVOlume;
//    int single_expansion;
};

//struct METHOD_VOLUMES_CALIB {
//    METHOD_VOLUME_CALIB cClaibD6377, cClaibD6378, cClaibD5188, cClaibFree1, cClaibFree2, cClaibFree3, cClaibFree4;
//    METHOD_VOLUME_CALIBD5191 cClaibD5191;
//};


class sCalibration : public QWidget, public sAccessWidget
{
    Q_OBJECT

public:
    explicit sCalibration(QWidget *parent = 0);
    ~sCalibration();
    void Show();
    void setDefaults(void);
    bool readFile();
    bool readMethodVolumeFile();
    bool saveFile();
    bool saveMethodVolumeFile();

    void showTemperatureCalib();
    void setMethods(const QStringList tmp);
    void showMethodVolume();
    void MethodSingleExpansion();
    void MethodTripleExpansion();
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

    void setWaitACKStatus(bool tmp);
    bool getWaitACKStatus(void);
    void hideAfterACK(bool tmp);
    bool getHideAfterACK();
    bool isSwitchEnabled(int tmp);
    void checkExit(int tmp);
    void MethodVolumeDefault();
//    void MethodVolumeSetDefualt(METHOD_VOLUMES_CALIB mvc);
    void showVolumeSinExpD5191();
    void showVolumeD5191();
    void showVolumeD6377();
    void showVolumeD6378();
    void showVolumeD5188();
    void showVolumeFree1();
    void showVolumeFree2();
    void showVolumeFree3();
    void showVolumeFree4();

    void updateVolumeSinExpD5191();
    void updateVolumeD5191();
    void updateVolumeD6377();
    void updateVolumeD6378();
    void updateVolumeD5188();
    void updateVolumeFree1();
    void updateVolumeFree2();
    void updateVolumeFree3();
    void updateVolumeFree4();
    void on_D6377_Vl_ration(double vl, bool init);

signals:
    void showKeypad(QObject *, int, bool);
    void showHome(bool);
    void getConfirmation(int, int);
    //void sendCommand(QString cmd);
    void sendCommand(QString cmd, sAccessWidget *sa);
    void runClicked(int state, bool init);
    void showMsgBox(QString title, QString msg);
    //void showStatusBox(QString title, QString msg, bool show);
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


    void on_pbPCSVSet_clicked();

    void on_imageCapture_clicked();

    void on_cbMethod_currentIndexChanged(int index);

    void on_volumeStageP_clicked();

    void on_volumeStageN_clicked();

    void on_volumeFirstP_clicked();

    void on_volumeFirstN_clicked();

    void on_volumeSecondP_clicked();

    void on_volumeSecondN_clicked();

    void on_volumeThirdP_clicked();

    void on_volumeThirdN_clicked();

    void on_cbSingleExpEnable_clicked();

private:
    Ui::sCalibration *ui;
    bool cParasChanged;
    bool cParaMethodVolumeChanged;
    int cPrevMethod;
    bool D6377Vl_updated;

    QWidget *cWidgetPressure;
    QString cStringPressure;

    QWidget *cWidgetPrLinear;
    QString cStringPrLinear;

    QWidget *cWidgetPrLinearzation;
    QString cStringPrLinearzation;

    QWidget *cWidgetMethodVolume;
    QString cStringMethodVolume;

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
    bool cHide;
    bool cEnSwitch;

public:
    int IS_ADMIN_USER;
    int IsLanguage;

public:
    struct CALIB_TEMPERATURE cCalibTm;
    struct CALIB_PRESSURE cCalibPr;
    struct METHOD_VOLUME_CALIB cCalibD6377, cCalibD6378, cCalibD5188, cCalibFree1, cCalibFree2, cCalibFree3, cCalibFree4;
    struct METHOD_VOLUME_CALIBD5191 cCalibD5191, cCalibSingleD5191;
//    struct METHOD_VOLUMES_CALIB MethodVolumeCal;

};

#endif // SCALIBRATION_H

