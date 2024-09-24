#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QTranslator>
#include <QDate>
#include <QTime>
#include <QMouseEvent>
#include <QStringList>

#include <QtSerialPort/QSerialPort>

#include "ssettings.h"
#include "sprotocol.h"
#include "saccesswidget.h"

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
    void handleError(void);
    void handleRinsing(void);
    void handleInjectRinsing(void);
    void handleD5188(void);
    void handleD6377(void);
    void handleOther(void);
    void handleFreeShaker(void);//naveen
    void handleD5191SingleExpansion(void); //naveen
    void handleDiagnostic(void);
    void handleCalibration(void);
    void handleDiagCommError(void);
    void setError(int tmp);
    void checkCommError(void);
    void showCommError(int tmp);

    void startLogging(void);
    void showError(void);
    void abortCurrentTask();
    void readSaveLogFile(int tmp, bool readSuccessfully);
    void internalLogSaving(QString tmp);

protected:
    void changeEvent(QEvent*);
    void timerEvent(QTimerEvent *e);
//    void mouseMoveEvent(QMouseEvent *event) override;
    /*void mouseMoveEvent(QMouseEvent *event) override {
            QPoint currentPos = event->pos();
            QPoint globalPos = mapToGlobal(currentPos);
            // Calculate the direction adjustment
            QPoint adjustedMovement = calculateAdjustedMovement(event);

            // Move the cursor to the adjusted position
            QCursor::setPos(globalPos + adjustedMovement);
        }*/

private slots:
    void onLoad();

    void readSerial(void);
    void handleErrorSerial(QSerialPort::SerialPortError error);

    void onMenuClicked(int menu);
    void on_listSetupMenu_itemClicked(QListWidgetItem *item);

    void onSendCommand(QString cmd);
    void onSendCommand(QString cmd, sAccessWidget *sa);


    bool onSaveResult(double p_tot, double p_gas, double p_abs,
                      QString method, QString formula,
                      double aconst, double bconst, double cconst,
                      double result,
                      double ttime, double vlratio,
                      double para_measured);

    void onRunClicked(int state, bool init);
    void onGetPass(void);
    void onPassDataReceived(QString, QString, int, int);
    void onShowKeypad(QObject *tobj, int tmp, bool);
    void onShowHome(bool);
    void onShowFileSelect(void);
    void onFileSelected(QString fs);
    void onUpdateMainWindow(void);
    void onGetConfirmation(int tmp, int);
    void onShowMsgBox(QString title, QString msg);
    void onShowStatusBox(QString title, QString msg, bool show);
    void onConfirmed(int, bool, int);
    void onD6377VlRatio(double vl);
//    void onMethodVolumesDefault(struct METHOD_VOLUMES_Main methodVol);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_imageCapture_clicked();

signals:
    void liveData(int vp, int pp, int atm, int ctm, int pr, int ss);

private:
    Ui::MainWindow *ui;
    int cMenu;
    QWidget *cWidget;

    void (*benchFunc)(void);

    QTranslator translatorLa;
    QTranslator translatorDe;
    QTranslator translatorFr;
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

    QString cPCMD;
    bool cACKReceived;
    bool cNACKReceived;
    bool cWaitForACK;
    bool cUACKReceived;

    int  cNAKCount;


    bool cParasUpdated;
    bool cInitDone;
    bool cInitSuccess;
    bool cStartTimeoutFlag;
    int  cIdleTimeout;

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
    int  cVolume;
    int deltaVolume;

    int shakerSpeed; //naveen
    double p1=0, p2=0, p3=0; //naveen
    bool rinsing;

    double cTmTest;
    double cPrTpx1;
    double cPrTpx2;
    double cPrTpx3;
    int    cPrCount;

    bool cDiagTestSuccess;
    bool cDiagErrorHandle;

//    QPoint lastMousePos;
    /*QPoint lastPos;
    QPoint calculateAdjustedMovement(QMouseEvent *event) {
        QPoint movement = event->pos() - lastPos;

        // Adjust the movement directions according to your specific case
        int adjustedX = 0;
        int adjustedY = 0;
        // Scenario mappings as described:
        // 1. If mouse moves Up (negative Y movement), cursor moves Left
        if (movement.y() < 0) adjustedX = -movement.y();
        // 2. If mouse moves Right (positive X movement), cursor moves Up
        if (movement.x() > 0) adjustedY = -movement.x();
        // 3. If mouse moves Down (positive Y movement), cursor moves Right
        if (movement.y() > 0) adjustedX = movement.y();
        // 4. If mouse moves Left (negative X movement), cursor moves Down
        if (movement.x() < 0) adjustedY = -movement.x();

        lastPos = event->pos();
        return QPoint(adjustedX, adjustedY);
    }*/

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
    sAccessWidget *cAccessWidget;
    struct TestStruct *cTest;

    bool sMeasuringCbMethod;

};

#endif // MAINWINDOW_H
