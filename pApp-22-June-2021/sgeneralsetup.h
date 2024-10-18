#ifndef SGENERALSETUP_H
#define SGENERALSETUP_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDateTime>
#include <QListView>

#include <defaults_general.h>
#include <defines.h>

struct GENERAL_SETUP {
    int date_format;
    int time_format;
    int language;
    int pressure_scale;
    int temperature_scale;
    int auto_measuring_cycle;
    QString company;
    QString location;
    QString unit_id;

    int emulation;
    int baud;
    int parity;
    int flow;
    int stop_bits;
    int data_bits;

    int page_size;
    int report_format;

    QString network_name;
    int network_enable;
    QString ip_address;
    QString ip_mask;
    QString ip_gateway;
    QString ip_dns;

    QString admin_password;
    QString service_password;

    int gmt;

    friend QDataStream &operator<< (QDataStream &out, const GENERAL_SETUP &tmp)
    {
        out << tmp.date_format << tmp.time_format << tmp.language << tmp.pressure_scale << tmp.temperature_scale
            << tmp.auto_measuring_cycle << tmp.company << tmp.location << tmp.unit_id
            << tmp.emulation << tmp.baud << tmp.parity << tmp.flow
            << tmp.stop_bits << tmp.data_bits
            << tmp.page_size << tmp.report_format
            << tmp.network_name << tmp.network_enable
            << tmp.ip_address << tmp.ip_mask << tmp.ip_gateway << tmp.ip_dns
            << tmp.admin_password << tmp.service_password << tmp.gmt ;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, GENERAL_SETUP &tmp)
    {
        in >> tmp.date_format >> tmp.time_format >> tmp.language >> tmp.pressure_scale >> tmp.temperature_scale
           >> tmp.auto_measuring_cycle >> tmp.company >> tmp.location >> tmp.unit_id
           >> tmp.emulation >> tmp.baud >> tmp.parity >> tmp.flow
           >> tmp.stop_bits >> tmp.data_bits
           >> tmp.page_size >> tmp.report_format
           >> tmp.network_name >> tmp.network_enable
           >> tmp.ip_address >> tmp.ip_mask >> tmp.ip_gateway >> tmp.ip_dns
           >> tmp.admin_password >> tmp.service_password >> tmp.gmt ;

        return in;
    }
};

struct newUsers{
    QString userName;
    QString userPassword;

    friend QTextStream &operator<< (QTextStream &out, const newUsers &tmp)
    {
        out << tmp.userName << tmp.userPassword ;

        return out;
    }

    friend QTextStream &operator>> (QTextStream &in, newUsers &tmp)
    {
        in >> tmp.userName >> tmp.userPassword ;

        return in;
    }

};

namespace Ui {
class sGeneralSetup;
}

class sGeneralSetup : public QWidget
{
    Q_OBJECT

public:
    explicit sGeneralSetup(QWidget *parent = 0);
    ~sGeneralSetup();
    void setDateFormat(const QStringList tmp);
    void setTimeFormat(const QStringList tmp);
    void setLanguage(const QStringList tmp);
    void setPressureScale(const QStringList tmp);
    void setTemperatureScale(const QStringList tmp);
    void setRinseCycles(const QStringList tmp);
    void setPageSize(const QStringList tmp);
    void setReportFormat(const QStringList tmp);
    void setEmulation(const QStringList tmp);
    void setBaudRate(const QStringList tmp);
    void setParity(const QStringList tmp);
    void setFlow(const QStringList tmp);
    void setStopBits(const QStringList tmp);
    void setDataBits(const QStringList tmp);

    void Show(QString type);
    void setDefaults();
    bool readFile();
    bool saveFile();
    bool saveUserFile();
    bool readUserFile();
    void saveNetworkFile();
    void saveHostnameFile();

    void showGeneralSetup();
    void updateGeneralSetup();

    void SaveRTC();
    void SavePassword();
    bool isSwitchEnabled(int tmp);

    int getGMTSeconds(void);
    bool getTabDateTimeVisible(); //naveen
    void call_on_twOther_currentChanged(int tmp); //naveen
    void editDateTime(bool tmp); //naveen
    int getCurrentGMTSeconds(void);
    void updateUser();
    bool userLogin(QString rUser, QString rPwd);

    bool GeneralSetUpFilesSaved;

signals:
    void showKeypad( QObject *, int, bool);
    void showHome(bool);
    void getConfirmation(int, int);
    void showMsgBox(QString title, QString msg);

private slots:
    void onShowKeypad(int tmp);
    void onShowKeypadNumeric(int tmp);
    void onTextChanged(QString tmp);
    void onShowPassKeypad(int tmp);
    void onPassTextChanged(QString tmp);


    void on_pbSave_clicked();
    void on_pbExit_clicked();

    void on_cbNEnable_clicked();
    void on_twGeneralSetup_currentChanged(int index);
    void on_twDevice_currentChanged(int index);
    void on_twOther_currentChanged(int index);

    void on_imageCapture_clicked();

    void on_pbAdd_clicked();

    void on_pbDelete_clicked();

private:
    Ui::sGeneralSetup *ui;
    bool cParasChanged;
    QString cType;
    int cPrevTab;
    int cPrevDeviceTab;
    int cPrevOtherTab;
    bool cEnSwitch;
    bool DateTimeDisplay;
    QRegularExpressionValidator *passValidator;
    bool newUser;
    bool newUserPasswordChange;

public:
    struct GENERAL_SETUP general_setup;
    QList<newUsers> nUsers;
    bool languageChanged;

};

#endif // SGENERALSETUP_H
