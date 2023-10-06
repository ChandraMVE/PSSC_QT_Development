#ifndef SKEYPAD_H
#define SKEYPAD_H

#include <QWidget>
#include <QKeyEvent>
#include <QLineEdit>
#include <QStyle>

#include <defines.h>

namespace Ui {
class sKeypad;
}

class sKeypad : public QWidget
{
    Q_OBJECT

public:
    explicit sKeypad(QWidget *parent = 0);
    ~sKeypad();
    void ShowKeyPad();
    void ShowKeypad(QObject *tobj, int Type, bool ZeroLength);
    void setData(QString tmp);

signals:
    void SendData(QString);

private slots:
    void onTextChanged(QString tmp);

    void on_pbClicked(void);

    void on_pbBackClicked();
    void on_pbCapsClicked();
    void on_pb123Clicked();
    void on_pbABCClicked();
    void on_pbCancelClicked();
    void on_pbEnterClicked();
    void on_pbSpaceClicked();

private:
    Ui::sKeypad *ui;
    QObject *cLocal;
    int cType;
    bool cZeroLength;
    QLineEdit *cleInput;

};

#endif // SKEYPAD_H
