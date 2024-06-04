#ifndef SUSERSETUP_H
#define SUSERSETUP_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QListView>

#include <defines.h>
#include <defaults_user.h>
#include <sprotocol.h>
#include "saccesswidget.h"

struct USER_SETUP {
    int alarm_buzzer_enable;
    int alarm_vol;
    int error_buzzer_enable;
    int rinse_cycle;
    int auto_print;

    friend QDataStream &operator<< (QDataStream &out, const USER_SETUP &tmp)
    {
        out << tmp.alarm_buzzer_enable << tmp.alarm_vol << tmp.error_buzzer_enable << tmp.rinse_cycle << tmp.auto_print;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, USER_SETUP &tmp)
    {
        in >> tmp.alarm_buzzer_enable >> tmp.alarm_vol >> tmp.error_buzzer_enable >> tmp.rinse_cycle >> tmp.auto_print;

        return in;
    }
};


namespace Ui {
class sUserSetup;
}

class sUserSetup : public QWidget, public sAccessWidget
{
    Q_OBJECT

public:
    explicit sUserSetup(QWidget *parent = 0);
    ~sUserSetup();
    void Show();
    void sendBuzAndVol(void);
    QString getBuzAndVol(void);

    void setDefaults();
    bool readFile();
    void saveFile();
    void showUserSetup();
    void updateUserSetup();

    void setWaitACKStatus(bool tmp);
    bool getWaitACKStatus(void);
    void hideAfterACK(bool tmp);
    bool getHideAfterACK();
    bool isSwitchEnabled(int tmp);

signals:
    void showHome(bool);
    void getConfirmation(int, int);
    void sendCommand(QString cmd, sAccessWidget *sa);
    void showMsgBox(QString title, QString msg);

private slots:
    void on_pbSave_clicked();
    void on_pbExit_clicked();

    void on_imageCapture_clicked();

private:
    Ui::sUserSetup *ui;
    QStringList qslGMTSeconds;
    bool cParasChanged;
    sProtocol cProtocol;
    bool cHide;
    bool cEnSwitch;

public:
    struct USER_SETUP user_setup;
};

#endif // SUSERSETUP_H
