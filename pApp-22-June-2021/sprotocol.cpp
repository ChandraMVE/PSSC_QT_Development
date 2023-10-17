#include "sprotocol.h"

sProtocol::sProtocol()
{

}

QString sProtocol::sendMeasuring(int ed, int tmp)
{
    QString str = "#Y" + QString::number(ed) + ",0,"
                       + QString::number(tmp).rightJustified(6, '0') + ",";

   QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

   return str+str2;
}

QString sProtocol::sendMeasuringStart(int ed, int tmp)
{
    QString str = "#Y" + QString::number(ed) + ",1,"
                    + QString::number(tmp).rightJustified(6, '0') + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendTemperature(int tmp)
{
    QString str = "#P1,0," + QString::number(tmp).rightJustified(6, '0') + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendPressure(int tmp)
{
    QString str = "#P1,1," + QString::number(tmp).rightJustified(6, '0') + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendValvePosition(int tmp)
{
    QString str  = "#K1," + QString::number(tmp) + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendPistonPosition(int tmp)
{
    QString str = "#M1," + QString::number(tmp).rightJustified(3, '0') + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendShakerSpeed(int ed, int tmp)
{
    QString str = "#O" + QString::number(ed) + ","
                  + QString::number(tmp).rightJustified(3, '0') + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendClearError(int tmp)
{
    QString str = "#T0," + QString::number(tmp).rightJustified(3, '0') + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendAckError()
{
    QString str = "#T0," + QString::number(0).rightJustified(3, '0') + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendAbortDiagnostic(void)
{
    QString str1 = "#T1," + QString::number(0).rightJustified(3, '0') + ",";

    QString str2 = "W" + QString::number(calcCRC(str1)).rightJustified(3, '0')+ "$";

    return str1+str2;
}

QString sProtocol::sendAlertBuzzer(int tmp)
{
    QString str = "#S" + QString::number(tmp) + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendErrorBuzzer(int tmp)
{
    QString str = "#R" + QString::number(tmp) + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendTimeOutError(int tmp)
{
    QString str = "#T1" + QString::number(tmp) + ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

QString sProtocol::sendBuzAndVol(int en, int vol)
{
    QString str = "#Q" + QString::number(en ? 1:0) +
                  "," + QString::number(vol) +
                  ",";

    QString str2 = "W" + QString::number(calcCRC(str)).rightJustified(3, '0')+ "$";

    return str+str2;
}

unsigned char sProtocol::calcCRC(QString tmp)
{
    int count = tmp.length();

    unsigned char  crc = 0;
    unsigned char  crcPoly = 0x07;
    unsigned char  i;

    QByteArray ba = tmp.toLocal8Bit();
    char *c_str = ba.data();

    while (count-- > 0)
    {
        crc = crc ^ (unsigned char) *c_str++;
        i = 8;

        do
        {
            if (crc & 0x80) crc = crc << 1 ^ crcPoly;
            else crc = crc << 1;

        } while(--i);
    }

    return (crc);
}
