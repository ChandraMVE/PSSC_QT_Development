#ifndef SSERVICE_H
#define SSERVICE_H

#include <QWidget>
#include <QDir>
#include <QProcess>
#include <QBasicTimer>

#include <defines.h>
#include <defaults_service.h>
#include <ssettings.h>
#include <sprotocol.h>

struct SERVICE_SETUP {
    quint32 total_count;
    quint32 count_since_last_reset;
    int continuous_enable;
    int data_log_usb;

    friend QDataStream &operator<< (QDataStream &out, const SERVICE_SETUP &tmp)
    {
        out << tmp.total_count << tmp.count_since_last_reset << tmp.continuous_enable
            << tmp.data_log_usb;
        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, SERVICE_SETUP &tmp)
    {
        in >> tmp.total_count >> tmp.count_since_last_reset >> tmp.continuous_enable
           >> tmp.data_log_usb;
        return in;
    }
};

struct ERROR_LOG {
    QString error_description;
    QString error_datetime;

    friend QDataStream &operator<< (QDataStream &out, const ERROR_LOG &tmp)
    {
        out << tmp.error_description << tmp.error_datetime;
        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, ERROR_LOG &tmp)
    {
        in >> tmp.error_description >> tmp.error_datetime;
        return in;
    }
};

namespace Ui {
class sService;
}

class sService : public QWidget
{
    Q_OBJECT

public:
    explicit sService(QWidget *parent = 0);
    ~sService();
    void Show();
    void setDefaults();
    bool readFile();
    bool readErrorLogFile();
    void saveFile();
    void setUSBLog(void);
    bool addErrorLog(QString error_description, QString error_datetime);
    void showServiceSetup();
    void updateServiceSetup();
    void incrementCount(void);
    void onLiveData(int vp, int pp, int atm, int ctm, int pr, int ss, int err);
    void onLogData(int vp, int pp, int atm, int ctm, int pr, int ss, int err);
    void setFileSelected(QString fs);
    bool getUSBLogEnabled(void);
    bool getContinuousRunEnabled(void);
    bool logData();
    bool isDiagnosticMode(void);
    void addStatus(QString tmp);
    void updateStatus(QString tmp);
    void testDone(void);

protected:
    void timerEvent(QTimerEvent *e);

signals:
    void showKeypad( QObject *,int,bool);
    void showHome(bool);
    void sendCommand(QString cmd);
    void showFileSelect(void);
    void showMsgBox(QString title, QString msg);
    void runClicked(int state, bool init);
    void getConfirmation(int);

private slots:
    void onShowKeypad(int tmp);
    void on_pbExit_clicked();
    void on_pbSave_clicked();

    void on_cbTEnable_clicked();
    void ontextChanged(QString tmp);

    void on_pbSVSet_clicked();
    void on_pbTSet_clicked();
    void on_pbRunReset_clicked();
    void on_pbPPSet_clicked();
    void on_pbRPMSet_clicked();
    void on_cbSMEnable_clicked();
    void on_pbFileSelect_clicked();
    void on_pbFWUpdate_clicked();

    void on_twService_currentChanged(int index);

    void on_pbRun_clicked();

    void on_pbStop_clicked();

private:
    Ui::sService *ui;
    struct SERVICE_SETUP service_setup;
    bool cParasChanged;
    int cPrevTab;
    sSettings cSettings;
    int cLogStage;
    int cUsbLogTimeout;
    bool cDiagnosticMode;

    QBasicTimer timer;
    int cvp;
    int cpp;
    int catm;
    int cctm;
    int cpr;
    int css;
    int cerr;

    bool cLiveDataUpdated;
    QFile *cLogFile;
    sProtocol cProtocol;

};

#endif // SSERVICE_H
