#ifndef SMEASURING2_H
#define SMEASURING2_H

#include <QWidget>

namespace Ui {
class sMeasuring2;
}

class sMeasuring2 : public QWidget
{
    Q_OBJECT

public:
    explicit sMeasuring2(QWidget *parent = 0);
    ~sMeasuring2();
    void setSampleId(QString tmp);
    void setOperator(QString tmp);
    void setMethod(QString tmp);
    void setMethodFormula(QString tmp, QString formula);
    void setResult(QString tmp, QString scale);
    void setStatus(QString tmp);

    void setVLPr(QString vl, QString pr, QString scale, QString pass);
    void setShaker(QString sh); //naveen
    void setFreeShaker(QString speed); //naveen
    void setVLTm(QString vl, QString pr, QString scale, QString pass);
    void set3Prs(QString pabs, QString pgas, QString ptot, QString scale, QString pass);

private slots:
//    void on_imageCapture_clicked();

private:
    Ui::sMeasuring2 *ui;

};

#endif // SMEASURING2_H
