#ifndef SSERVICE_H
#define SSERVICE_H

#include <QWidget>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QBasicTimer>
#include <QElapsedTimer>

#include <defines.h>
#include <defaults_service.h>
#include <ssettings.h>
#include <sprotocol.h>
#include "saccesswidget.h"

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

class sService : public QWidget, public sAccessWidget
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
    void setWaitACKStatus(bool tmp);
    bool getWaitACKStatus(void);
    void hideAfterACK(bool tmp);
    bool getHideAfterACK();
    bool isSwitchEnabled(int tmp);
    void checkExit(int tmp);
    void setDebug();
    int getDebug();
    void setVersion(QString tmp);

protected:
    void timerEvent(QTimerEvent *e);

signals:
    void showKeypad( QObject *,int,bool);
    //void showHome(bool);
    //void sendCommand(QString cmd);
    void sendCommand(QString cmd, sAccessWidget *sa);
    void showFileSelect(void);
    void showMsgBox(QString title, QString msg);
    void showStatusBox(QString title, QString msg, bool show);
    void runClicked(int state, bool init);
    void getConfirmation(int, int);
    void showHome(bool);
    void getPass(void);

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

  void onFirmwareClicked();
  void on_imageCapture_clicked();

private:
    Ui::sService *ui;
    struct SERVICE_SETUP service_setup;
    bool cParasChanged;
    int cPrevTab;
    sSettings cSettings;
    int cLogStage;
    int cUsbLogTimeout;
    bool cDiagnosticMode;
    bool cHide;
    bool cEnSwitch;

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
    bool cDebug;
    QString cVerFW, cVerMCU;

};

#endif // SSERVICE_H
