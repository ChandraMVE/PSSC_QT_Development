#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QDate>
#include <QTime>
#include <QMouseEvent>
#include <QStringList>
#include <QtSerialPort/QSerialPort>

#include "ssettings.h"
#include "sprotocol.h"
#include "define_strings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setLists(void);
    bool eventFilter(QObject *watched, QEvent *e);
    QString getFormated(float tmp, int precision);
    int setLanguage();
    void setMeasuring(void);
    void sendPara(QString tmp, int stage, int timeout);
    void openSerial(QString tmp);
    void writeSerial(const QByteArray &data, int len);
    void closeSerial(void);

    void sendRequest(int stage);
    void checkInit(void);
    void handleRinsing(void);
    void handleD5188(void);
    void handleD6377(void);
    void handleOther(void);
    void handleDiagnostic(void);
    void handleCalibration(void);
    void handleDiagCommError(void);
    void setError(int tmp);
    void checkCommError(void);

    void startLogging(void);
    void showError(void);
    void abortCurrentTask();

protected:
    void timerEvent(QTimerEvent *e);

private slots:
    void onLoad();

    void readSerial(void);
    void handleErrorSerial(QSerialPort::SerialPortError error);

    void onMenuClicked(int menu);
    void on_listSetupMenu_itemClicked(QListWidgetItem *item);

    void onSendCommand(QString cmd);

    bool onSaveResult(double p_tot, double p_gas, double p_abs,
                      QString method, QString formula,
                      double aconst, double bconst, double cconst,
                      double result,
                      double ttime, double vlratio,
                      double para_measured);

    void onRunClicked(int state, bool init);
    void onPassDataReceived(QString, QString, int, int);
    void onShowKeypad(QObject *tobj, int tmp, bool);
    void onShowHome(bool);
    void onShowFileSelect(void);
    void onFileSelected(QString fs);
    void onUpdateMainWindow(void);
    void onGetConfirmation(int tmp);
    void onShowMsgBox(QString title, QString msg);
    void onShowStatusBox(QString title, QString msg);
    void onConfirmed(int, bool);

signals:
    void liveData(int vp, int pp, int atm, int ctm, int pr, int ss);

private:
    Ui::MainWindow *ui;
    int cMenu;
    QWidget *cWidget;

    void (*benchFunc)(void);

    QString dateFormat;
    QString timeFormat;

    QSerialPort *serial;

    int dcount;
    int dstage;
    unsigned char rdata[100];

    bool cFrameError;

    bool cFrameReceived;
    bool cFrameErrorShown;
    int  cFrameTimeOut;

    int  cStage;
    int  cStageTimeOut;
    int  cTimeOutError;

    bool cParasUpdated;
    bool cInitDone;
    bool cInitSuccess;

    int  cValvePosition;
    int  cPistonPosition;
    int  cRawATemperature;
    int  cRawCTemperature;
    int  cRawCPressure;
    int  cStepperSpeed;
    int  cRinseCycles;
    int  cAutoCycles;
    int  cCRTimeout;
    bool cCRFlag;

    int  cEqTime;
    int  cREqTime;

    double cTmTest;
    double cPrTpx1;
    double cPrTpx2;
    double cPrTpx3;

    bool cDiagTestSuccess;

public:
    QStringList qslDateFormat;
    QStringList qslShowDateFormat;
    QStringList qslTimeFormat;
    QStringList qslShowTimeFormat;
    QStringList qslLanguage;
    QStringList qsTemperatureScaleFull;
    QStringList qslPressureScale;
    QStringList qslTemperatureScale;
    QStringList qslRinseCycles;

    QStringList qslEmulation;
    QStringList qslBaudRate;
    QStringList qslParity;
    QStringList qslFlow;
    QStringList qslStopBits;
    QStringList qslDataBits;

    QStringList qslPageSize;
    QStringList qslReportFormat;

    QStringList qslPressureMultiplier;
    QStringList qslPressureDP;
    QStringList qslTemperatureDP;

    QStringList qslMethods;

    QStringList qslFormulaD5191aConstant;
    QStringList qslFormulaD5191bConstant;
    QStringList qslFormulaD5191cConstant;

    QStringList qslFormulaD6378aConstant;
    QStringList qslFormulaD6378bConstant;
    QStringList qslFormulaD6378cConstant;

    QStringList qslFormulaD5191;
    QStringList qslFormulaD6378;

    QStringList qslUCErrors;
    QStringList qslLogErrors;

    QStringList qslFormulaFree1, qslFormulaFree2, qslFormulaFree3, qslFormulaFree4;
    QDateTime cDateTime;

    sSettings cSettings;
    sProtocol cProtocol;

    int cPrevUCError;
    int cCurrentUCError;
    int cErrorPos;
    int cStrringErrorCount;

};

#endif // MAINWINDOW_H
