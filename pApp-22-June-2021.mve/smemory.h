#ifndef SMEMORY_H
#define SMEMORY_H

#include <QWidget>
#include <QDate>
#include <QTime>

#include <defines.h>
#include <defaults_memory.h>
#include <stestmodel.h>
#include <stestmodelheader.h>
#include <ssettings.h>

struct SELECTED_COLS {
    int sel;
    int nooperator;
    int sample_id;
    int date;
    int time;
    int p_tot;
    int p_gas;
    int p_abs;
    int method;
    int formula;
    int result;
    int ttime;
    int vl_ratio;
    int para_measured;

    // overload the operators

    friend QDataStream &operator<< (QDataStream &out, const SELECTED_COLS &tmp)
    {
        out << tmp.sel << tmp.nooperator << tmp.sample_id << tmp.date << tmp.time
            << tmp.p_tot << tmp.p_gas << tmp.p_abs << tmp.method << tmp.formula
            << tmp.result << tmp.ttime << tmp.vl_ratio << tmp.para_measured;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, SELECTED_COLS &tmp)
    {
        in  >> tmp.sel >> tmp.nooperator >> tmp.sample_id >> tmp.date >> tmp.time
            >> tmp.p_tot >> tmp.p_gas >> tmp.p_abs >> tmp.method >> tmp.formula
            >> tmp.result >> tmp.ttime >> tmp.vl_ratio >> tmp.para_measured;

        return in;
    }
};

namespace Ui {
class sMemory;
}

class sMemory : public QWidget
{
    Q_OBJECT

public:
    explicit sMemory(QWidget *parent = 0);
    ~sMemory();

    void Show(void);
    void setDefaults(void);
    bool readFile();
    void saveFile();
    void updateMemorySetup();
    bool readTests(void);
    bool deleteTests(void);
    bool transferTests(QString fname);
    bool saveResult(QString noperator, QString sampleID, QString datetime,
                    double p_tot, double p_gas, double p_abs,
                    QString method,
                    QString formula,
                    double aconst, double bconst, double cconst,
                    double result,
                    double t_time, double vlratio, double para_measured);

    int getMemoryCount(void);

signals:
    void showHome(bool);
    void showMsgBox(QString title, QString msg);
    void showStatusBox(QString title, QString msg);
    void getConfirmation(int);

private slots:
    void on_wTableViewHeader_clicked(const QModelIndex &index);
    void on_wTableView_clicked(const QModelIndex &index);
    void on_pbExit_clicked();
    void on_pbDelete_clicked();
    void on_pbTransfer_clicked();
    void on_pbPrint_clicked();
    void onShowMsgBox(QString title, QString msg);
    void onShowStatusBox(QString title, QString msg);

private:
    Ui::sMemory *ui;

    sTestModel *MemoryModel;
    sTestModelHeader *MemoryModelHeader;
    struct SELECTED_COLS selected_cols;
    bool cParasChanged;
    sSettings cSettings;

};

#endif // SMEMORY_H
