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

    double temperature;
    double time;
    double vl_ratio;
    int passfail_enabled;
    int alarm_enabled;
    double from;
    double to;
};// stdD5191;

struct STD_D6377 {
    double temperature;
    double time;
    double vl_ratio;
    int shaker_speed;
    int passfail_enabled;
    int alarm_enabled;
    double from;
    double to;
};

struct STD_D6378 {
    int formula;

    double aconstant;
    double bconstant;
    double cconstant;

    double temperature;
    double time;
    double vl_ratio;
    int passfail_enabled;
    int alarm_enabled;
    double from;
    double to;
};

struct STD_D5188 {
    double pressure;
    double vl_ratio;
    int shaker_speed;
    int passfail_enabled;
    int alarm_enabled;
    double from;
    double to;
};

struct STD_Free {
    double aconstant;
    double bconstant;
    double cconstant;
    double temperature;
    double tpx1;
    double tpx2;
    double tpx3;
    double vl_ratio;
    int passfail_enabled;
    int alarm_enabled;
    double from;
    double to;
};

class sMethodSetup : public QWidget
{
    Q_OBJECT

public:
    explicit sMethodSetup(QWidget *parent = 0);
    ~sMethodSetup();
    void setMethods(const QStringList tmp);
    void setD5191(const QStringList tmp);
    void setD6378(const QStringList tmp);
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

    void showFree1(void);
    void showFree2(void);
    void showFree3(void);
    void showFree4(void);

    void updateD5191(void);
    void updateD6377(void);
    void updateD6378(void);
    void updateD5188(void);

    void updateFree1(void);
    void updateFree2(void);
    void updateFree3(void);
    void updateFree4(void);
    bool isSwitchEnabled(int tmp);
    void checkExit(int tmp);

signals:
    void showKeypad( QObject *, int, bool);
    void showHome(bool);
    void getConfirmation(int, int);
    void showMsgBox(QString title, QString msg);

private slots:
    void on_cbMethod_currentIndexChanged(int index);
    void on_cbEnable_clicked();
    void onShowKeypad(int tmp);
    void ontextChanged(QString tmp);

    void on_pbSave_clicked();
    void on_pbExit_clicked();

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

    QDoubleValidator *dvaConst;
    QDoubleValidator *dvbConst;
    QDoubleValidator *dvcConst;

    QDoubleValidator *dvPara1;
    QDoubleValidator *dvPara2;
    QDoubleValidator *dvPara3;
    QDoubleValidator *dvPara4;

    QDoubleValidator *dvTestTemperature;
    QDoubleValidator *dvTPx1;
    QDoubleValidator *dvTPx2;
    QDoubleValidator *dvTPx3;
    QDoubleValidator *dvVLRatio;

    QDoubleValidator *dvFrom;
    QDoubleValidator *dvTo;


public:
    struct STD_D5191 stdD5191;
    struct STD_D6377 stdD6377;
    struct STD_D6378 stdD6378;
    struct STD_D5188 stdD5188;
    struct STD_Free stdFree1, stdFree2, stdFree3, stdFree4;

    QStringList qslD5191;
    QStringList qslD6378;
    QStringList qslFree1, qslFree2, qslFree3, qslFree4;

    QStringList *qslFormulaD5191aConstant;
    QStringList *qslFormulaD5191bConstant;
    QStringList *qslFormulaD5191cConstant;

    QStringList *qslFormulaD6378aConstant;
    QStringList *qslFormulaD6378bConstant;
    QStringList *qslFormulaD6378cConstant;

    sSettings cSettings;

};

#endif // SMETHODSETUP_H
