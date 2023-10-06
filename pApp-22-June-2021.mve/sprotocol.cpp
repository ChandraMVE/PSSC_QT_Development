#include "sprotocol.h"

sProtocol::sProtocol()
{

}

QString sProtocol::sendMeasuring(int ed, int tmp)
{
    QString str = "#Y" + QString::number(ed) + ","
                  + QString::number(tmp).rightJustified(6, '0') + "$";
    return str;
}

QString sProtocol::sendTemperature(int tmp)
{
    QString str = "#P1,0," + QString::number(tmp).rightJustified(6, '0') + "$";
    return str;
}

QString sProtocol::sendPressure(int tmp)
{
    QString str = "#P1,1," + QString::number(tmp).rightJustified(6, '0') + "$";
    return str;
}

QString sProtocol::sendValvePosition(int tmp)
{
    QString str  = "#K1," + QString::number(tmp) + "$";
    return str;
}

QString sProtocol::sendPistonPosition(int tmp)
{
    QString str = "#M1," + QString::number(tmp).rightJustified(3, '0') + "$";
    return str;
}

QString sProtocol::sendShakerSpeed(int ed, int tmp)
{
    QString str = "#O" + QString::number(ed) + ","
                  + QString::number(tmp).rightJustified(3, '0') + "$";
    return str;
}

QString sProtocol::sendClearError(int tmp)
{
    QString str = "#T0," + QString::number(tmp).rightJustified(3, '0') + "$";
    return str;
}

QString sProtocol::sendAckError()
{
    QString str = "#T0," + QString::number(0).rightJustified(3, '0') + "$"; 
    return str;
}

QString sProtocol::sendAlertBuzzer(int tmp)
{
    QString str = "#S" + QString::number(tmp) + "$";
    return str;
}

QString sProtocol::sendErrorBuzzer(int tmp)
{
    QString str = "#R" + QString::number(tmp) + "$";
    return str;
}

QString sProtocol::sendTimeOutError(int tmp)
{
    QString str = "#T1" + QString::number(tmp) + "$";
    return str;
}
