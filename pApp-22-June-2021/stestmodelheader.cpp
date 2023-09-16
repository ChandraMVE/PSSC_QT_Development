#include "stestmodelheader.h"

sTestModelHeader::sTestModelHeader(QObject *parent)
{

}

void sTestModelHeader::populateData(int selValue, int n_operator, int sampleID, int date, int time, int p_tot, int p_gas, int p_abs, int method, int formula, int result, int ttime, int vlratio, int para_measured)
{
    ctm_sel = selValue;
    ctm_operator = n_operator;
    ctm_sample_id = sampleID;
    ctm_date = date;
    ctm_time = time;
    ctm_p_tot = p_tot;
    ctm_p_gas = p_gas;
    ctm_p_abs = p_abs;
    ctm_method = method;
    ctm_formula = formula;
    ctm_result = result;
    ctm_ttime = ttime;
    ctm_vlratio = vlratio;
    ctm_para_measured = para_measured;
}


int sTestModelHeader::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1; 
}

int sTestModelHeader::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 14; 
}

QVariant sTestModelHeader::data(const QModelIndex &index, int role) const
{
    
    if (role == Qt::DisplayRole) {
        if (index.column() == 0 ) {
            return QString("Sel");
        } else if (index.column() == 1) {
            return QString("Operator");
        } else if (index.column() == 2) {
            return QString("Sample Id");
        } else if (index.column() == 3) {
            return QString("Date");
        } else if (index.column() == 4) {
            return QString("Time");
        } else if (index.column() == 5) {
            return QString("P tot");
        } else if (index.column() == 6) {
            return QString("P gas");
        } else if (index.column() == 7) {
            return QString("P abs");
        } else if (index.column() == 8) {
            return QString("Method");
        } else if (index.column() == 9) {
            return QString("Formula");
        } else if (index.column() == 10) {
            return QString("Results");
        } else if (index.column() == 11) {
            return QString(" Test Time");
        } else if (index.column() == 12) {
            return QString("V/L Ratio");
        } else if (index.column() == 13) {
            return QString("Para measured");
        }
    }
    else if(role == Qt::DecorationRole) {

        if (index.column() == 0) {

            if(ctm_sel == 1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");


        } else if (index.column() == 1) {

            if(ctm_operator==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 2) {

            if(ctm_sample_id==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 3) {
       
            if(ctm_date==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 4) {
          
            if(ctm_time==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 5) {
           
            if(ctm_p_tot==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 6) {
           
            if(ctm_p_gas==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 7) {
           
            if(ctm_p_abs==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 8) {
            
            if(ctm_method==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 9) {
            
            if(ctm_formula==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 10) {
            
            if(ctm_result==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 11) {
            
            if(ctm_ttime==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 12) {
            
            if(ctm_vlratio==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        } else if (index.column() == 13) {
           
            if(ctm_para_measured==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");
        }
    }

    return QVariant();
}

QVariant sTestModelHeader::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DecorationRole) {

        if (section == 0) {

            if(ctm_sel==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");

        }

        if (section == 1) {
       
            if(ctm_operator==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");
        }

        if (section == 2) {
        
            if(ctm_sample_id==1) return QPixmap(":/images/icons/thcheck.png");
            else return QPixmap(":/images/icons/thncheck.png");
        }

    }

    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0 ) {
            return QString("Sel");
        } else if (section == 1) {
            return QString("Operator");
        } else if (section == 2) {
            return QString("Sample Id");
        } else if (section == 3) {
            return QString("Date");
        } else if (section == 4) {
            return QString("Time");
        } else if (section == 5) {
            return QString("P tot");
        } else if (section == 6) {
            return QString("P gas");
        } else if (section == 7) {
            return QString("P abs");
        } else if (section == 8) {
            return QString("Method");
        } else if (section == 9) {
            return QString("Formula");
        } else if (section == 10) {
            return QString("Results");
        } else if (section == 11) {
            return QString("Test Time");
        } else if (section == 12) {
            return QString("V/L Ratio");
        } else if (section == 13) {
            return QString("Para measured");
        }
    }

    return QVariant();
}

bool sTestModelHeader::setData(const QModelIndex &index)
{
    switch(index.column())
    {
        case 0: 
                ctm_sel = !ctm_sel;
                break;

        case 1: 
                ctm_operator = !ctm_operator;
                break;

        case 2: 
                ctm_sample_id = !ctm_sample_id;
                break;

        case 3: 
                ctm_date = !ctm_date;
                break;

        case 4: 
                ctm_time = !ctm_time;
                break;

        case 5: 
                ctm_p_tot = !ctm_p_tot;
                break;

        case 6: 
                ctm_p_gas = !ctm_p_gas;
                break;

        case 7: 
                ctm_p_abs = !ctm_p_abs;
                break;

        case 8: 
                ctm_method = !ctm_method;
                break;

        case 9:
                ctm_formula = !ctm_formula;
                break;

        case 10: 
                ctm_result  = !ctm_result;
                break;

        case 11:
                ctm_ttime = !ctm_ttime;
                break;
        case 12: 
                ctm_vlratio = !ctm_vlratio;
                break;

        case 13: 
                ctm_para_measured = !ctm_para_measured;
                break;
    }

    emit(dataChanged(index, index));

    return true;

}

int sTestModelHeader::getData(int col)
{
    switch(col)
    {
        case 0: return ctm_sel;
        case 1: return ctm_operator;
        case 2: return ctm_sample_id;
        case 3: return ctm_date;
        case 4: return ctm_time;
        case 5: return ctm_p_tot;
        case 6: return ctm_p_gas;
        case 7: return ctm_p_abs;
        case 8: return ctm_method;
        case 9: return ctm_formula;
        case 10: return ctm_result;
        case 11: return ctm_ttime;
        case 12: return ctm_vlratio;
        case 13: return ctm_para_measured;
    }

    return -1;
}
