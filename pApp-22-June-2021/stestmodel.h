#ifndef STESTMODEL_H
#define STESTMODEL_H

#include <QAbstractTableModel>
#include <QApplication>
#include <QFile>
#include <QPainter>
#include <QLabel>
#include <QDateTime>
#include <QSocketNotifier>
#include <QProcess>
#include <QPrinter>
#include <QPainter>
#include <QElapsedTimer>
#include <QSerialPort>
#include <QThread>

#include <ssettings.h>
#include <stestmodelheader.h>
#include <stestrecord.h>
#include <defaults_memory.h>

#include <fcntl.h>
#include <unistd.h>

#ifndef Q_OS_WIN32
#include <sys/ioctl.h>
#endif

#include <errno.h>

#define LPGETSTATUS	0x060b

class QSocketNotifier;

class sTestModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit sTestModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index);
    int getSelectedCount(void);

    void setHeaderModel(sTestModelHeader *model);
    void setAll(void);

    bool AddRecord(int selValue, QString noperator, QString sampleID, QString datetime,
                   double p_tot, double p_gas, double p_abs,
                   QString method,
                   QString formula,
                   double aconst, double bconst, double cconst,
                   double result,
                   double ttime,
                   double vlratio,
                   double para_measured);

    bool RemoveRecord(void);

    bool ReadAllRecords(void);
    bool AppendRecord(int selValue, QString noperator, QString sampleID, QString datetime,
                      double p_tot, double p_gas, double p_abs,
                      QString method,
                      QString formula,
                      double aconst, double bconst, double cconst,
                      double result,
                      double ttime,
                      double vlratio,
                      double para_measured);

    bool TransferRecords(QString fname);
    bool PrintRecords(bool precords, struct TestStruct *test);
    bool SerialPrinter(bool precords);
    int writeSerialPrinter(const QByteArray &data, int len);

    void drawData(QPainter *painter, int x, int y, int width, int height, QString str, QTextOption *textoption);
    void setBrush(QPainter *painter, QBrush *brush, int row);

    bool CreateSingleDeskjet(bool precords);
    bool CreateMultilineDeskjet(void);

    bool CreatePrintSpool(bool precords);
    int PrinterStatus(int);
    int PrintData(int, char);

    int PrintQString(QString tmp);
    int InitPrinter(void);
    bool ClosePrinter(void);

signals:
    void showStatusBox(QString title, QString msg, bool show);
    void showMsgBox(QString title, QString msg);

private slots:
    void readPrintStatus(void);
    void readSerialPrinter(void);
    void handleErrorSerialPrinter(QSerialPort::SerialPortError error);

private:
    QList<sTestRecord> listTestRecord;
    sTestModelHeader *cHeaderModel;
    sSettings cSettings;

    int m_fd;
    QSocketNotifier *m_notifier;
    QFile *pfile;
    int cPrinterError;
    QSerialPort *cSerialPrinter;

    struct TestStruct *cPrintRecord;

};

#endif // STESTMODEL_H
