#ifndef SMETHODSETUP_H
#define SMETHODSETUP_H

#include <QWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QDoubleValidator>

#include <defines.h>
#include <defaults_method.h>
#include <sgeneralsetup.h>

#include <ssettings.h>

namespace Ui {
class sMethodSetup;
}

//typedef
struct STD_D5191{
    int formula;

    double aconstant;
    double bconstant;
    double cconstant;

//    double InjectTemp;
    double temperature;
    double time;
    double vl_ratio;
    int passfail_enabled;
    int single_expansion;
//    int alarm_enabled;
    double from;
    double to;
};// stdD5191;

struct STD_D6377 {
    double InjectTemp;
    double temperature;
    double time;
    double vl_ratio;
    int shaker_speed;
    int passfail_enabled;
//    int alarm_enabled;
    double from;
    double to;
};

struct STD_D6378 {
    int formula;

    double aconstant;
    double bconstant;
    double cconstant;

//    double InjectTemp;
    double temperature;
    double time;
    double vl_ratio;
    int passfail_enabled;
//    int alarm_enabled;
    double from;
    double to;
};

struct STD_D5188 {
    double pressure;
    double vl_ratio;
    int shaker_speed;
    int passfail_enabled;
//    int alarm_enabled;
    double from;
    double to;
};

struct STD_Free {
    double aconstant;
    double bconstant;
    double cconstant;
    double InjectTemp;
    double temperature;
    double tpx1;
    double tpx2;
    double tpx3;
    double vl_ratio;
    int shaker_disabled;
    int shaker_speed;
    int passfail_enabled;
//    int alarm_enabled;
    double from;
    double to;
};

/*struct METHOD_VOLUME_MET{
    double StageVolume;
    double FirstVolume;
    double SecondVolume;
    double ThirdVOlume;
};

struct METHOD_VOLUME_D5191{
    double StageVolume;
    double FirstVolume;
    double SecondVolume;
    double ThirdVOlume;
    int single_expansion;
};

struct METHOD_VOLUMES {
    METHOD_VOLUME_MET MD6377, MD6378, MD5188, MFree1, MFree2, MFree3, MFree4;
    METHOD_VOLUME_D5191 MD5191;
};*/

class sMethodSetup : public QWidget
{
    Q_OBJECT

public:
    explicit sMethodSetup(QWidget *parent = 0);
    ~sMethodSetup();
    void setMethods(const QStringList tmp);
    void setD5191(const QStringList tmp);
    void setD6378(const QStringList tmp);
    void setEN_13016_1(const QStringList tmp);
    void setEN_13016_2(const QStringList tmp);
    void setGB_T_8017(const QStringList tmp);
    void setIP_394(const QStringList tmp);
    void setIP_409(const QStringList tmp);
    void setJIS_K2258_2(const QStringList tmp);
    void setSH_T_0769(const QStringList tmp);
    void setSH_T_0794(const QStringList tmp);
    void setSN_T_2932(const QStringList tmp);

    void setFree1(const QStringList tmp);
    void setFree2(const QStringList tmp);
    void setFree3(const QStringList tmp);
    void setFree4(const QStringList tmp);

    void Show();
    void setDefaults();
    bool readFile();
    void saveFile();

    void showD5191(void);
    void showD6377(void);
    void showD6378(void);
    void showD5188(void);

    void showEN_13016_1(void);
    void showEN_13016_2(void);
    void showGB_T_8017(void);
    void showIP_394(void);
    void showIP_409(void);
    void showIP_481(void);
    void showJIS_K2258_2(void);
    void showSH_T_0769(void);
    void showSH_T_0794(void);
    void showSN_T_2932(void);

    void showFree1(void);
    void showFree2(void);
    void showFree3(void);
    void showFree4(void);

    void updateD5191(void);
    void updateD6377(void);
    void updateD6378(void);
    void updateD5188(void);

    void updateEN_13016_1(void);
    void updateEN_13016_2(void);
    void updateGB_T_8017(void);
    void updateIP_394(void);
    void updateIP_409(void);
    void updateIP_481(void);
    void updateJIS_K2258_2(void);
    void updateSH_T_0769(void);
    void updateSH_T_0794(void);
    void updateSN_T_2932(void);

    void updateFree1(void);
    void updateFree2(void);
    void updateFree3(void);
    void updateFree4(void);
    bool isSwitchEnabled(int tmp);
    void checkExit(int tmp);

    bool MethodSetUpFilesSaved;

signals:
    void showKeypad( QObject *, int, bool);
    void showHome(bool);
    void getConfirmation(int, int);
    void showMsgBox(QString title, QString msg);
    void D6377_VlRatio(double);
    void IP_481_VlRatio(double);
//    void methodVolumesDefault(struct METHOD_VOLUMES methodVol);

private slots:
    void on_cbMethod_currentIndexChanged(int index);
    void on_cbEnable_clicked();
    void onShowKeypad(int tmp);
    void ontextChanged(QString tmp);

    void on_pbSave_clicked();
    void on_pbExit_clicked();

    void on_imageCapture_clicked();

    void on_cbShakerDisable_clicked();

private:
    Ui::sMethodSetup *ui;
    QWidget *cWidgetFormula;
    QString cStringFormula;

    QWidget *cWidgetStdParas;
    QString cStringStdParas;

    QWidget *cWidgetFreeParas;
    QString cStringFreeParas;

    QWidget *cWidgetPassFail;
    QString cStringPassFail;
    int cPrevMethod;
    bool cParasChanged;
    bool cEnSwitch;
    bool exitClicked;

    QDoubleValidator *dvaConst;
    QDoubleValidator *dvbConst;
    QDoubleValidator *dvcConst;

    QDoubleValidator *dvInjectPara6;
    QDoubleValidator *dvPara1;
    QDoubleValidator *dvPara2;
    QDoubleValidator *dvPara3;
    QDoubleValidator *dvPara4;

    QDoubleValidator *dvInjectTemperature;
    QDoubleValidator *dvTestTemperature;
    QDoubleValidator *dvTPx1;
    QDoubleValidator *dvTPx2;
    QDoubleValidator *dvTPx3;
    QDoubleValidator *dvVLRatio;
    QDoubleValidator *dvShaker;

    QDoubleValidator *dvFrom;
    QDoubleValidator *dvTo;


public:
    struct STD_D5191 stdD5191,stdEN_13016_1,stdGB_T_8017,stdIP_394,stdSH_T_0794;
    struct STD_D6377 stdD6377,stdIP_481;
    struct STD_D6378 stdD6378,stdEN_13016_2,stdIP409,stdJIS_K2258_2,stdSH_T_0769, stdSN_T_2932;
    struct STD_D5188 stdD5188;
    struct STD_Free stdFree1, stdFree2, stdFree3, stdFree4;
//    struct METHOD_VOLUMES methodVolumes;
//    struct METHOD_VOLUMES_Main methodVolumes;

    QStringList qslD5191, qslEN_13016_1, qslGB_T_8017, qslIP_394, qslSH_T_0794;
    QStringList qslD6378, qslEN_13016_2, qslIP_409, qslJIS_K2258_2, qslSH_T_0769, qslSN_T_2932;
    QStringList qslFree1, qslFree2, qslFree3, qslFree4;

    QStringList *qslFormulaD5191aConstant;
    QStringList *qslFormulaD5191bConstant;
    QStringList *qslFormulaD5191cConstant;

    QStringList *qslFormulaEN_13016_1aConstant;
    QStringList *qslFormulaEN_13016_1bConstant;
    QStringList *qslFormulaEN_13016_1cConstant;

    QStringList *qslFormulaGB_T_8017aConstant;
    QStringList *qslFormulaGB_T_8017bConstant;
    QStringList *qslFormulaGB_T_8017cConstant;

    QStringList *qslFormulaIP_394aConstant;
    QStringList *qslFormulaIP_394bConstant;
    QStringList *qslFormulaIP_394cConstant;

    QStringList *qslFormulaSH_T_0794aConstant;
    QStringList *qslFormulaSH_T_0794bConstant;
    QStringList *qslFormulaSH_T_0794cConstant;

    QStringList *qslFormulaD6378aConstant;
    QStringList *qslFormulaD6378bConstant;
    QStringList *qslFormulaD6378cConstant;

    QStringList *qslFormulaEN_13016_2aConstant;
    QStringList *qslFormulaEN_13016_2bConstant;
    QStringList *qslFormulaEN_13016_2cConstant;

    QStringList *qslFormulaIP_409aConstant;
    QStringList *qslFormulaIP_409bConstant;
    QStringList *qslFormulaIP_409cConstant;

    QStringList *qslFormulaJIS_K2258_2aConstant;
    QStringList *qslFormulaJIS_K2258_2bConstant;
    QStringList *qslFormulaJIS_K2258_2cConstant;

    QStringList *qslFormulaSH_T_0769aConstant;
    QStringList *qslFormulaSH_T_0769bConstant;
    QStringList *qslFormulaSH_T_0769cConstant;

    QStringList *qslFormulaSN_T_2932aConstant;
    QStringList *qslFormulaSN_T_2932bConstant;
    QStringList *qslFormulaSN_T_2932cConstant;

    sSettings cSettings;

};

#endif // SMETHODSETUP_H
