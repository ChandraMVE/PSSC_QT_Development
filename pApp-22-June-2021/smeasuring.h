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

    void readLastIdsFile();
    void saveLastIdsFile();

    void showResultD5191(double prtpx1, double prtpx2, double prtpx3);
    void showResultD6377(double result);
    void showResultD6378(double prtpx1, double prtpx2, double prtpx3);
    void showResultD5188(double result);
    void showResultFree(double prtpx1, double prtpx2, double prtpx3);
    void hideResult(void);
    void setRunState(bool rs);
    bool checkValidInputs(void);
    void setRunning(bool);

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

    void on_leSampleId_textChanged(const QString &arg1);
    void on_lwSampleId_itemClicked(QListWidgetItem *item);

    void on_pbOperator_clicked();

    void on_lwOperator_itemClicked(QListWidgetItem *item);
    void on_leOperator_textChanged(const QString &arg1);
    void on_leSampleId_returnPressed();
    void on_leOperator_returnPressed();

    void on_pbStop_2_clicked();

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
    struct STD_D5191 *cstdD5191;
    struct STD_D6377 *cstdD6377;
    struct STD_D6378 *cstdD6378;
    struct STD_D5188 *cstdD5188;
    struct STD_Free *cstdFree1, *cstdFree2, *cstdFree3, *cstdFree4;

    QStringList *qslD5191;
    QStringList *qslD6378;
    QStringList *qslFree1, *qslFree2, *qslFree3, *qslFree4;

    QStringList *qslPressureScale;
    QStringList *qslTemperatureScale;
    QStringList *qslPassFail;

    QStringList *qslFormulaD5191aConstant;
    QStringList *qslFormulaD5191bConstant;
    QStringList *qslFormulaD5191cConstant;

    QStringList *qslFormulaD6378aConstant;
    QStringList *qslFormulaD6378bConstant;
    QStringList *qslFormulaD6378cConstant;

    double cPressureMultiplier;
    int cTmScaleIndex;

    int cPressureDecimalPlaces;
    int cTemperatureDecimalPlaces;

    QString cPressureScale;
    QString cTemperatureScale;

    sSettings cSettings;

};

#endif // SMEASURING_H
