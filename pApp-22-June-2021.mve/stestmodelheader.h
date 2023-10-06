#ifndef STESTMODELHEADER_H
#define STESTMODELHEADER_H

#include <QAbstractTableModel>
#include <QPixmap>

class sTestModelHeader : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit sTestModelHeader(QObject *parent = 0);

    void populateData(int selValue, int n_operator,
                      int sampleID, int date,int time,
                      int p_tot, int p_gas, int p_abs,
                      int method, int formula, int result,
                      int ttime, int vlratio, int para_measured);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    bool setData(const QModelIndex &index);
    int getData(int col);

private:

    int ctm_sel;
    int ctm_operator;
    int ctm_sample_id;
    int ctm_date;
    int ctm_time;
    int ctm_p_tot;
    int ctm_p_gas;
    int ctm_p_abs;
    int ctm_method;
    int ctm_formula;
    int ctm_result;
    int ctm_ttime;
    int ctm_vlratio;
    int ctm_para_measured;

};

#endif // STESTMODELHEADER_H
