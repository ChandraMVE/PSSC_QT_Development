#ifndef SCHECKPASS_H
#define SCHECKPASS_H

#include <QMessageBox>
#include <QWidget>
#include "defines.h"

namespace Ui {
class sCheckPass;
}

class sCheckPass : public QWidget
{
    Q_OBJECT

public:
    explicit sCheckPass(QWidget *parent = 0);
    ~sCheckPass();
    void Show_CheckPass(int, bool);
    void Show_ShowMessage(int, int);
    void Show_Message(QString title, QString msg);
    void Show_Status(QString title, QString msg);
    void Show_ErrorMessage(QString title, QString msg);
    bool isErrorVisible();
    void Show_Confirmation(int);

signals:
    void SendData(QString, QString, int, int);
    void showKeypad( QObject *, int, bool);
    void Confirmed(int, bool);

private slots:
    void onShowKeypad(int tmp);
    void on_pbConfirm_clicked();
    void on_pbOK_clicked();
    void on_pbCan_clicked();

    void on_pbYes_clicked();

    void on_pbNo_clicked();

private:
    Ui::sCheckPass *ui;
    int cShowMessageType;
    int cConfirmType;
    int cCheckPassType;
    int cCalls;
};

#endif // SCHECKPASS_H
