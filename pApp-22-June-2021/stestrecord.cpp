#include "stestrecord.h"

sTestRecord::sTestRecord()
{

}

sTestRecord::sTestRecord(
        const int &selValue, const QString &noperator, const QString &sampleID,
        const QString &datetime,
        const double &p_tot, const double &p_gas, const double &p_abs,
        const QString &method, const QString &formula,
        const double &aconst, const double &bconst, const double &cconst,
        const double &result,
        const double &ttime, const double &vlratio,
        const double &para_measured)
{
    tm_sel = selValue;
    tm_operator = noperator;
    tm_sample_id = sampleID;
    tm_datetime = datetime;
    tm_p_tot = p_tot;
    tm_p_gas = p_gas;
    tm_p_abs = p_abs;
    tm_method = method;
    tm_formula = formula;
    tm_aconst = aconst;
    tm_bconst = bconst;
    tm_cconst = cconst;

    tm_result = result;
    tm_ttime = ttime;
    tm_vlratio = vlratio;
    tm_para_measured = para_measured;
}
