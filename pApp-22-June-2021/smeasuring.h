#ifndef SMEASURING_H
#define SMEASURING_H

#include <QWidget>

#include <ssettings.h>
#include <smethodsetup.h>
#include "saccesswidget.h"

#include <QFile>
#include <QString>
#include <QList>
#include <QListWidgetItem>
#include <QLineEdit>

#include <defaults_user.h>
#include <defaults_measuring.h>

struct OPERATORS {

    QString operator_name;

    friend QDataStream &operator<< (QDataStream &out, const OPERATORS &tmp)
    {
        out << tmp.operator_name;
        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, OPERATORS &tmp)
    {
        in >> tmp.operator_name;
        return in;
    }
};

struct SAMPLE_IDS {

    QString sample_id;

    friend QDataStream &operator<< (QDataStream &out, const SAMPLE_IDS &tmp)
    {
        out << tmp.sample_id;
        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, SAMPLE_IDS &tmp)
    {
        in >> tmp.sample_id;
        return in;
    }
};

struct LAST_IDS {

    QString operator_name;
    QString sample_id;
    QString test_id;

    friend QDataStream &operator<< (QDataStream &out, const LAST_IDS &tmp)
    {
        out << tmp.operator_name << tmp.sample_id << tmp.test_id;
        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, LAST_IDS &tmp)
    {
        in >> tmp.operator_name >> tmp.sample_id >> tmp.test_id;
        return in;
    }
};

namespace Ui {
class sMeasuring;
}

class sMeasuring : public QWidget, public sAccessWidget
{
    Q_OBJECT

public:
    explicit sMeasuring(QWidget *parent = 0);
    ~sMeasuring();
    void Show(void);
    void setMethods(const QStringList tmp);
    void setMessage(QString tmp);
    void setAutoCount(int current, int total);
    //void setIdleTimer(int tmp);
    void setStatus(QString tmp);

    void setTmPrScale(int tmScaleIndex, QString tmScale, int tmDP, QString prScale, double prMultiplier, int prDP);
    QString getPressure(double pr) const;
    QString getPressure(double pr, int dp) const;
    QString getTemperature(double tm) const;
    QString getVLRatio(double vl) const;
    QString getFormulaConstantsAB(double constants) const;
    QString getOperator(void) const;
    QString getSampleId(void) const;

    void onLiveData(int tm, int pr);
    int  getMethod(void);
    void hideLists(void);
    void readOperatorsFile();
    void readSampleIdsFile();
    void saveOperatorsFile();
    void deleteOperatorsFile();
    void saveSampleIdsFile();
    void deleteSampleIdsFile();
    int getcbMethodVisibility();
    void mkVisibleCbMethod();

    void readLastIdsFile();
    void saveLastIdsFile();

    void showResultD5191(double prtpx1, double prtpx2, double prtpx3);
    void showResultEN_13016_1(double prtpx1, double prtpx2, double prtpx3);
    void showResultGB_T_8017(double prtpx1, double prtpx2, double prtpx3);
    void showResultIP_394(double prtpx1, double prtpx2, double prtpx3);
    void showResultSH_T_0794(double prtpx1, double prtpx2, double prtpx3);

    void showResultD5191Single(double prtpx1);
    void showResultEN_13016_1Single(double prtpx1);
    void showResultGB_T_8017Single(double prtpx1);
    void showResultIP_394Single(double prtpx1);
    void showResultSH_T_0794Single(double prtpx1);

    void showResultD6377(double result);
    void showResultIP_481(double result);

    void showResultD6378(double prtpx1, double prtpx2, double prtpx3);
    void showResultEN_13016_2(double prtpx1, double prtpx2, double prtpx3);
    void showResultIP409(double prtpx1, double prtpx2, double prtpx3);
    void showResultJIS_K2258_2(double prtpx1, double prtpx2, double prtpx3);
    void showResultSH_T_0769(double prtpx1, double prtpx2, double prtpx3);
    void showResultSN_T_2932(double prtpx1, double prtpx2, double prtpx3);

    void showResultD5188(double result);
    void showResultFree(double prtpx1, double prtpx2, double prtpx3);
    void hideResult(void);
    void setRunState(bool rs);
    bool checkValidInputs(void);
    void setRunning(bool);
    void setLblMessage(QString tmp); //naveen

    void setWaitACKStatus(bool tmp);
    bool getWaitACKStatus(void);
    void hideAfterACK(bool tmp);
    bool getHideAfterACK();


signals:
    void showKeypad( QObject *, int, bool);
    void showMsgBox(QString title, QString msg);

    void runClicked(int state, bool init);

    bool saveResult(double p_tot, double p_gas, double p_abs,
                    QString method, QString formula,
                    double aconst, double bconst, double cconst,
                    double result,
                    double ttime, double vlratio,
                    double para_measured);


private slots:

    void onShowKeypad(int tmp);
    void ontextChanged(QString tmp);
    void on_pbRun_clicked();
    void on_pbStop_clicked();

    void on_pbSampleId_clicked();
    void onClickSampleId();
    void onClickOperator();
    void onClickMethod();

    void on_leSampleId_textChanged(const QString &arg1);
    void on_lwSampleId_itemClicked(QListWidgetItem *item);

    void on_pbOperator_clicked();

    void on_lwOperator_itemClicked(QListWidgetItem *item);
    void on_leOperator_textChanged(const QString &arg1);
    void on_leSampleId_returnPressed();
    void on_leOperator_returnPressed();

    void on_pbStop_2_clicked();

    void on_imageCapture_clicked();

    void on_pbRinse_clicked();

    void on_pbMethod_clicked();

    void on_lwMethods_itemClicked(QListWidgetItem *item);

private:
    Ui::sMeasuring *ui;

    struct OPERATORS operator_names;
    struct SAMPLE_IDS sample_ids;
    struct LAST_IDS last_ids;

    QString cPrevOperator;
    QString cPrevSampleId;
    bool cRunState;

public:
    struct GENERAL_SETUP *cgs;
    struct STD_D5191 *cstdD5191, *cstdEN_13016_1, *cstdGB_T_8017, *cstdIP_394, *cstdSH_T_0794;
    struct STD_D6377 *cstdD6377, *cstdIP_481;
    struct STD_D6378 *cstdD6378, *cstdEN_13016_2, *cstdIP409, *cstdJIS_K2258_2, *cstdSH_T_0769, *cstdSN_T_2932;
    struct STD_D5188 *cstdD5188;
    struct STD_Free *cstdFree1, *cstdFree2, *cstdFree3, *cstdFree4;

    QStringList *qslD5191, *qslEN_13016_1, *qslGB_T_8017, *qslIP_394, *qslSH_T_0794;
    QStringList *qslD6378, *qslEN_13016_2, *qslIP_409, *qslJIS_K2258_2, *qslSH_T_0769, *qslSN_T_2932;
    QStringList *qslFree1, *qslFree2, *qslFree3, *qslFree4;

    QStringList *qslPressureScale;
    QStringList *qslTemperatureScale;
    QStringList *qslPassFail;

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

    double cPressureMultiplier;
    int cTmScaleIndex;

    int cPressureDecimalPlaces;
    int cTemperatureDecimalPlaces;

    QString cPressureScale;
    QString cTemperatureScale;

    sSettings cSettings;

};

#endif // SMEASURING_H
