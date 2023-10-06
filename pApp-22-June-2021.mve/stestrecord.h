#ifndef STESTRECORD_H
#define STESTRECORD_H

#include <QString>

struct TestStruct
{
    int sel;
    double p_tot;
    double p_gas;
    double p_abs;

    double para_measured;
    QString noperator;
    QString sample_id;
    QString datetime;
    QString method;
    QString formula;
    double aconst;
    double bconst;
    double cconst;
    double ttime;
    double vlratio;
    double result;

    TestStruct()
    {

    }

    TestStruct(int lsel, QString loperator, QString lsample_id, QString ldatetime,
               double lp_tot, double lp_gas, double lp_abs,
               QString lmethod, QString lformula,
               double laconst, double lbconst, double lcconst,
               double lresult,
               double lt_time, double lvlratio,
               double lpara_measured)
    {
        sel = lsel;
        noperator = loperator;
        sample_id = lsample_id;
        datetime = ldatetime;
        p_tot = lp_tot;
        p_gas = lp_gas;
        p_abs = lp_abs;
        method = lmethod;
        formula = lformula;
        result = lresult;
        aconst = laconst;
        bconst = lbconst;
        cconst = lcconst;

        ttime = lt_time;
        vlratio = lvlratio;
        para_measured = lpara_measured;
    }

};

class sTestRecord
{
public:
    sTestRecord();
    sTestRecord(const int &selValue, const QString &noperator, const QString &sampleID,
                const QString &datetime,
                const double &p_tot, const double &p_gas, const double &p_abs,
                const QString &method,
                const QString &formula,
                const double &aconst, const double &bconst, const double &cconst,
                const double &result,
                const double &ttime,
                const double &vlratio,
                const double &para_measured);
public:
    int tm_sel;
    QString tm_operator;
    QString tm_sample_id;
    QString tm_datetime;
    double tm_p_tot;
    double tm_p_gas;
    double tm_p_abs;
    QString tm_method;
    QString tm_formula;
    double tm_aconst;
    double tm_bconst;
    double tm_cconst;
    double tm_result;
    double tm_ttime;
    double tm_vlratio;
    double tm_para_measured;

};

#endif // STESTRECORD_H
