#ifndef SPROTOCOL_H
#define SPROTOCOL_H

#include <QString>

class sProtocol
{
public:
    sProtocol();
    QString sendMeasuring(int ed, int tmp);
  QString sendMeasuringStart(int ed, int tmp);
    QString sendTemperature(int tmp);
    QString sendPressure(int tmp);
    QString sendValvePosition(int tmp);
    QString sendPistonPosition(int tmp);
    QString sendShakerSpeed(int ed, int tmp);
    QString sendClearError(int tmp);
    QString sendAckError(void);
 QString sendAbortDiagnostic(void);
    QString sendAlertBuzzer(int tmp);
    QString sendErrorBuzzer(int tmp);
    QString sendTimeOutError(int tmp);
QString sendBuzAndVol(int en, int vol);
    unsigned char calcCRC(QString tmp);

};

#endif // SPROTOCOL_H
