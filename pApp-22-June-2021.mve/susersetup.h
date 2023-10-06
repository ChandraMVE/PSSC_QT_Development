#ifndef SUSERSETUP_H
#define SUSERSETUP_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>

#include <defines.h>
#include <defaults_user.h>

struct USER_SETUP {
    int alarm_vol;
    int error_buzzer_enable;
    int gmt;
    int rinse_cycle;

    friend QDataStream &operator<< (QDataStream &out, const USER_SETUP &tmp)
    {
        out << tmp.alarm_vol << tmp.error_buzzer_enable << tmp.gmt << tmp.rinse_cycle;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, USER_SETUP &tmp)
    {
        in >> tmp.alarm_vol >> tmp.error_buzzer_enable >> tmp.gmt >> tmp.rinse_cycle;

        return in;
    }
};


namespace Ui {
class sUserSetup;
}

class sUserSetup : public QWidget
{
    Q_OBJECT

public:
    explicit sUserSetup(QWidget *parent = 0);
    ~sUserSetup();
    void Show();
    int getGMTSeconds(void);
    void sendBuzAndVol(void);

    void setDefaults();
    bool readFile();
    void saveFile();
    void showUserSetup();
    void updateUserSetup();

signals:
    void showHome(bool);
    void getConfirmation(int);
    void sendCommand(QString cmd);
    void showMsgBox(QString title, QString msg);

private slots:
    void on_pbSave_clicked();
    void on_pbExit_clicked();

private:
    Ui::sUserSetup *ui;
    QStringList qslGMTSeconds;
    bool cParasChanged;

public:
    struct USER_SETUP user_setup;
};

#endif // SUSERSETUP_H
