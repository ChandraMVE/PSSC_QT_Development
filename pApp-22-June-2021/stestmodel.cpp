#include "stestmodel.h"
#include <QPixmap>

#include <QBrush>

sTestModel::sTestModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    cHeaderModel = NULL;
    cSerialPrinter = new QSerialPort(this);
}

int sTestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listTestRecord.size();
}

int sTestModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 14;
}

QVariant sTestModel::data(const QModelIndex &index, int role) const
{
   
    sTestRecord cTestRecord  = listTestRecord.at(index.row());

    if( cHeaderModel && role == Qt::BackgroundRole)
    {
        if(cTestRecord.tm_sel == 1)
        {
            if(cHeaderModel->getData(index.column()) == 1) return QBrush(QColor(21, 100, 192)); 
            else return QBrush(Qt::white);
        }
    }

    if (role == Qt::DecorationRole && index.column() == 0){
        if (cTestRecord.tm_sel == 1) return QPixmap(":/images/icons/tvcheck.png");
        else return QPixmap(":/images/icons/tvncheck.png");
    } else if (role == Qt::DisplayRole && index.column() == 1) {
        return cTestRecord.tm_operator;
    } else if (role == Qt::DisplayRole && index.column() == 2) {
        return cTestRecord.tm_sample_id;
    } else if (role == Qt::DisplayRole && index.column() == 3) {
        return cSettings.getDate(cTestRecord.tm_datetime);
    } else if (role == Qt::DisplayRole && index.column() == 4) {
        return cSettings.getTime(cTestRecord.tm_datetime);
    } else if (role == Qt::DisplayRole && index.column() == 5) {
        return cSettings.getPressure(cTestRecord.tm_method, cTestRecord.tm_p_tot);
    } else if (role == Qt::DisplayRole && index.column() == 6) {
        return cSettings.getPressure(cTestRecord.tm_method, cTestRecord.tm_p_gas);
    } else if (role == Qt::DisplayRole && index.column() == 7) {
        return cSettings.getPressure(cTestRecord.tm_method, cTestRecord.tm_p_abs);
    } else if (role == Qt::DisplayRole && index.column() == 8) {
        return cTestRecord.tm_method;
    } else if (role == Qt::DisplayRole && index.column() == 9) {
        return cSettings.getFormula(cTestRecord.tm_method, cTestRecord.tm_formula,
                          cTestRecord.tm_aconst, cTestRecord.tm_bconst,
                          cTestRecord.tm_cconst);
    } else if (role == Qt::DisplayRole && index.column() == 10) {
        return cSettings.getResult(cTestRecord.tm_method, cTestRecord.tm_result);
    } else if (role == Qt::DisplayRole && index.column() == 11) {
        return cSettings.getTestTime(cTestRecord.tm_method, cTestRecord.tm_ttime);
    } else if (role == Qt::DisplayRole && index.column() == 12) {
        return cSettings.getVLRatio(cTestRecord.tm_vlratio);
    } else if (role == Qt::DisplayRole && index.column() == 13) {
        return cSettings.getParaMeasured(cTestRecord.tm_method, cTestRecord.tm_para_measured);
    }

    return QVariant();
}

QVariant sTestModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

bool sTestModel::setData(const QModelIndex &index)
{
   
    if(index.column() == 0)
    {
        sTestRecord cTestRecord  = listTestRecord.at(index.row());

        if(cTestRecord.tm_sel == 1)
        {
            cTestRecord.tm_sel = 0;
            listTestRecord.replace(index.row(), cTestRecord);
        }
        else
        {
            cTestRecord.tm_sel = 1;
            listTestRecord.replace(index.row(), cTestRecord);
        }

       emit(dataChanged(index, index));
    }

    return true;
}

int sTestModel::getSelectedCount()
{
    if(cHeaderModel)
    {
        bool cSelected = false;
        int rCount=0;

        for(int tmp=1; tmp<=10; tmp++)
        {
            if(cHeaderModel->getData(tmp))
            {
                cSelected = true;
                break;
            }
        }

        if(cSelected)
        {
            for(int tmp=0; tmp < listTestRecord.count() ; tmp++)
            {
                sTestRecord cTestRecord  = listTestRecord.at(tmp);

                if(cTestRecord.tm_sel)
                {
                    rCount++;
                    break;
                }
            }

            return rCount;

        }
        else
        {
            return -1;
        }

    }
    else
        return -1;
}

void sTestModel::setHeaderModel(sTestModelHeader *model)
{
    cHeaderModel = model;
}

void sTestModel::setAll()
{
    if(cHeaderModel)
    {
        QList<sTestRecord>::iterator it = listTestRecord.begin();

        while (it != listTestRecord.end()) {
            it->tm_sel = cHeaderModel->getData(0);
            ++it;
        }

    }
}

bool sTestModel::AddRecord(int selValue, QString noperator, QString sampleID, QString datetime, double p_tot, double p_gas, double p_abs, QString method, QString formula, double aconst, double bconst, double cconst, double result, double ttime, double vlratio, double para_measured)
{
    beginInsertRows(QModelIndex(), 0, 0);
    sTestRecord nRecord = sTestRecord(selValue, noperator, sampleID, datetime, p_tot, p_gas, p_abs, method, formula, aconst, bconst, cconst, result, ttime, vlratio, para_measured);
    listTestRecord.insert(0, nRecord);
    endInsertRows();
    return true;
}

bool sTestModel::RemoveRecord()
{
    QString fname = QApplication::applicationDirPath() + FN_TESTS;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);

        for(int tmp=listTestRecord.count()-1; tmp >=0 ; tmp--)
        {
            sTestRecord cTestRecord  = listTestRecord.at(tmp);

            if(!cTestRecord.tm_sel)
            {
                struct TestStruct nRecord = TestStruct(cTestRecord.tm_sel,
                        cTestRecord.tm_operator, cTestRecord.tm_sample_id,
                        cTestRecord.tm_datetime,
                        cTestRecord.tm_p_tot, cTestRecord.tm_p_gas,
                        cTestRecord.tm_p_abs,
                        cTestRecord.tm_method, cTestRecord.tm_formula,
                        cTestRecord.tm_aconst, cTestRecord.tm_bconst,
                        cTestRecord.tm_cconst,
                        cTestRecord.tm_result,
                        cTestRecord.tm_ttime, cTestRecord.tm_vlratio,
                        cTestRecord.tm_para_measured);

                save << nRecord.noperator << nRecord.sample_id << nRecord.datetime << nRecord.p_tot << nRecord.p_gas << nRecord.p_abs
                     << nRecord.method << nRecord.formula
                     << nRecord.aconst << nRecord.bconst << nRecord.cconst
                     << nRecord.result
                     << nRecord.ttime << nRecord.vlratio
                     << nRecord.para_measured;
            }
        }

        out.close();

        ReadAllRecords();

        return true;
    }
    else
    {
        return false;
    }
}

bool sTestModel::ReadAllRecords()
{

    QString fname = QApplication::applicationDirPath() + FN_TESTS;

    struct TestStruct nRecord;

    beginRemoveRows(QModelIndex(), 0, listTestRecord.count()-1);
    listTestRecord.clear();
    endRemoveRows();

    QFile in(fname);

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream read(&in);
        while(!read.atEnd())
        {
            read >> nRecord.noperator >> nRecord.sample_id >> nRecord.datetime >> nRecord.p_tot >> nRecord.p_gas >> nRecord.p_abs
                 >> nRecord.method >> nRecord.formula
                 >> nRecord.aconst >> nRecord.bconst >> nRecord.cconst
                 >> nRecord.result
                 >> nRecord.ttime >> nRecord.vlratio
                 >> nRecord.para_measured;

             AddRecord(0, nRecord.noperator, nRecord.sample_id, nRecord.datetime,
                          nRecord.p_tot, nRecord.p_gas, nRecord.p_abs,
                          nRecord.method, nRecord.formula,
                          nRecord.aconst, nRecord.bconst, nRecord.cconst,
                          nRecord.result,
                          nRecord.ttime, nRecord.vlratio, nRecord.para_measured);
        }

        in.close();
        return true;

    }
    else
    {
        return false;
    }
}

bool sTestModel::AppendRecord(int selValue, QString noperator, QString sampleID, QString datetime, double p_tot, double p_gas, double p_abs, QString method, QString formula, double aconst, double bconst, double cconst, double result, double ttime, double vlratio, double para_measured)
{

    QString fname = QApplication::applicationDirPath() + FN_TESTS;

    struct TestStruct nRecord = TestStruct(selValue, noperator, sampleID, datetime, p_tot, p_gas, p_abs, method, formula, aconst, bconst, cconst, result, ttime, vlratio, para_measured);

    QFile out(fname);

    if(out.open(QIODevice::Append))
    {
        QDataStream save(&out);

        save << nRecord.noperator << nRecord.sample_id << nRecord.datetime
             << nRecord.p_tot << nRecord.p_gas << nRecord.p_abs
             << nRecord.method << nRecord.formula
             << nRecord.aconst << nRecord.bconst << nRecord.cconst
             << nRecord.result
             << nRecord.ttime << nRecord.vlratio
             << nRecord.para_measured;

        out.close();

        AddRecord(selValue, noperator, sampleID, datetime, p_tot, p_gas, p_abs,
                  method, formula,
                  aconst, bconst, cconst,
                  result, ttime, vlratio, para_measured);

        return true;
    }
    else
    {
        return false;
    }
}

bool sTestModel::TransferRecords(QString fname)
{

    fname = QApplication::applicationDirPath() + "/" + fname;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QTextStream save(&out);

        if(cHeaderModel->getData(1)) save << tr("Operator") << ",";
        if(cHeaderModel->getData(2)) save << tr("Sample Id") << ",";
        if(cHeaderModel->getData(3)) save << tr("Date") << ",";
        if(cHeaderModel->getData(4)) save << tr("Time") << ",";
        if(cHeaderModel->getData(5)) save << tr("Ptot") << ",";
        if(cHeaderModel->getData(6)) save << tr("Pgas") << ",";
        if(cHeaderModel->getData(7)) save << tr("Pabs") << ",";
        if(cHeaderModel->getData(8)) save << tr("Method") << ",";
        if(cHeaderModel->getData(9)) save << tr("Formula") << ",";
        if(cHeaderModel->getData(10)) save << tr("Result") << ",";
        if(cHeaderModel->getData(11)) save << tr("Test Time") << ",";
        if(cHeaderModel->getData(12)) save << tr("V/L Ratio") << ",";
        if(cHeaderModel->getData(13)) save << tr("Para Measured");

        save << endl;

        for(int tmp=0; tmp < listTestRecord.count(); tmp++)
        {
            sTestRecord cTestRecord  = listTestRecord.at(tmp);

            if(cTestRecord.tm_sel)
            {
                struct TestStruct nRecord = TestStruct(cTestRecord.tm_sel,
                        cTestRecord.tm_operator, cTestRecord.tm_sample_id,
                        cTestRecord.tm_datetime,
                        cTestRecord.tm_p_tot, cTestRecord.tm_p_gas,
                        cTestRecord.tm_p_abs,
                        cTestRecord.tm_method, cTestRecord.tm_formula,
                        cTestRecord.tm_aconst, cTestRecord.tm_bconst,
                        cTestRecord.tm_cconst,
                        cTestRecord.tm_result,
                        cTestRecord.tm_ttime, cTestRecord.tm_vlratio,
                        cTestRecord.tm_para_measured);

                if(cHeaderModel->getData(1)) save << nRecord.noperator << ",";
                if(cHeaderModel->getData(2)) save << nRecord.sample_id << ",";

                if(cHeaderModel->getData(3)) save << cSettings.getDate(nRecord.datetime) << ",";
                if(cHeaderModel->getData(4)) save << cSettings.getTime(nRecord.datetime) << ",";

                if(cHeaderModel->getData(5)) save << cSettings.getPressure(nRecord.method, nRecord.p_tot) << ",";
                if(cHeaderModel->getData(6)) save << cSettings.getPressure(nRecord.method, nRecord.p_gas) << ",";
                if(cHeaderModel->getData(7)) save << cSettings.getPressure(nRecord.method, nRecord.p_abs) << ",";

                if(cHeaderModel->getData(8)) save << nRecord.method << ",";

                if(cHeaderModel->getData(9)) save << cSettings.getFormula(nRecord.method, nRecord.formula, nRecord.aconst, nRecord.bconst, nRecord.cconst) << ",";
                if(cHeaderModel->getData(10)) save << cSettings.getResult(nRecord.method, nRecord.result) << ",";
                if(cHeaderModel->getData(11)) save << cSettings.getTestTime(nRecord.method, nRecord.ttime) << ",";
                if(cHeaderModel->getData(12)) save << cSettings.getVLRatio(nRecord.vlratio) << ",";
                if(cHeaderModel->getData(13)) save << cSettings.getParaMeasured(nRecord.method, nRecord.para_measured) << ",";

                save << endl;
            }
        }

        out.close();

        return true;
    }
    else
    {
        return false;
    }
}

bool sTestModel::PrintRecords()
{

    if(!cSettings.checkFileExists("/dev/usb/lp0"))
    {
        return SerialPrinter();
    }
    else
    {
        emit showStatusBox(tr("Memory Print"), tr("Wait..."));

        QString str = "usb-devices | grep Product";

        QProcess process;
        process.start("sh", QStringList()<< "-c" << str);

        process.waitForFinished();
        QString output = process.readAllStandardOutput();
        QString err = process.readAllStandardError();

        if(output.contains("Product=SP712"))
        {

             if(CreatePrintSpool()) 
             {
                pfile = new QFile("/dev/usb/lp0");

                if(!pfile->open(QFile::ReadWrite | QFile::Unbuffered | QFile::Text))
                {

                }

                m_fd = pfile->handle();

                auto flags = fcntl(m_fd, F_GETFL, 0);
                if(flags == -1)
                {

                }

                flags = fcntl(m_fd, F_SETFL, flags | O_NONBLOCK);
                if(flags == -1)
                {

                }

                if(m_fd < 0)
                {
                   emit showMsgBox(tr("Memory Print"), tr("Printer not found!"));
                   return false;
                }
                else
                {
                    cPrinterError = 0;

                    m_notifier = new QSocketNotifier(m_fd, QSocketNotifier::Read, this);
                    connect(m_notifier, SIGNAL(activated(int)), this, SLOT(readPrintStatus()));

                    QString fname = QApplication::applicationDirPath() + "/tmp/print.txt";

                    QFile file(fname);
                    file.open(QIODevice::ReadOnly);

                    {
                        QElapsedTimer timeout;
                        timeout.start();

                        while(timeout.elapsed() < 3000) QCoreApplication::processEvents();

                        if((cPrinterError==1) || timeout.elapsed()>3000) emit showMsgBox(tr("Memory Print"), tr("Error Printing!"));
                        else emit showStatusBox(tr("Memory Print"), tr("Printing..."));
                    }

                    while( cPrinterError ==2)
                    {
                        QCoreApplication::processEvents();

                        if(!file.atEnd())
                        {
                            extern int errno ;
                            char file_data[2];
                            int ret=0;

                            file.read(file_data, 1);

                            while(((ret = ::write(m_fd, file_data, 1)) < 0) && errno == EAGAIN)
                                QCoreApplication::processEvents();

                            if(ret <0)
                            {
                                emit showMsgBox(tr("Memory Print"), tr("Error 1 Printing!"));
                                cPrinterError=1;
                                break;
                            }
                        }
                        else
                        {
                            file.close();
                            break;
                        }
                    }

                    {

                        pfile->flush();
                        pfile->close();

                        disconnect(m_notifier, SIGNAL(activated(int)), this, SLOT(readPrintStatus()));

                        delete(m_notifier);
                        delete(pfile);

                        cSettings.removeTmpFiles();

                        if(cPrinterError==2)
                        {
                            emit showMsgBox(tr("Memory Print"), tr("Printing done!"));
                            return true;
                        }
                        else return false;
                    }

                } 

             }
             else
             {
                emit showMsgBox(tr("Memory Print"), tr("Error Spooling!"));
                 return false;
             }

        }
        else if(output.contains("Product=HP LaserJet Pro M40"))
        {
             if(cSettings.getReportFormat()==0) CreateMultilineDeskjet();
             else CreateSingleDeskjet();

             emit showMsgBox(tr("Memory Print"), tr("Printing done!"));

             return true;
        }

        emit showMsgBox(tr("Memory Print"), tr("Error Printing!"));

    }
}

bool sTestModel::SerialPrinter()
{
    if(cSerialPrinter->isOpen())
        cSerialPrinter->close();

    cSerialPrinter->setPortName("/dev/ttymxc2");

    if (cSerialPrinter->open(QIODevice::ReadWrite))
    {
        if (cSerialPrinter->setBaudRate(cSettings.getBaud())
                && cSerialPrinter->setDataBits(cSettings.getDataBits())
                && cSerialPrinter->setParity(cSettings.getParity())
                && cSerialPrinter->setStopBits(cSettings.getStopBits())
                && cSerialPrinter->setFlowControl(cSettings.getFlowControl()))
        {

            if(CreatePrintSpool()) 
            {
                connect(cSerialPrinter, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleErrorSerialPrinter(QSerialPort::SerialPortError)));
                connect(cSerialPrinter, SIGNAL(readyRead()), this, SLOT(readSerialPrinter()));

                   cPrinterError = 0;

                   QString fname = QApplication::applicationDirPath() + "/tmp/print.txt";

                   QFile file(fname);
                   file.open(QIODevice::ReadOnly);

                   emit showStatusBox(tr("Memory Print"), tr("Printing..."));

                   cPrinterError = 2;

                   while( cPrinterError ==2)
                   {
                       QCoreApplication::processEvents();

                       if(!file.atEnd())
                       {

                           char file_data[2];
                           int ret=0;

                           file.read(file_data, 1);

                           while((ret = cSerialPrinter->write(&file_data[0], 1)) < 0)
                           {
                               QCoreApplication::processEvents();
                           }

                           cSerialPrinter->flush();
                           QThread::msleep(5);

                           if(ret <0)
                           {
                               emit showMsgBox(tr("Memory Print"), tr("Error 1 Printing!"));
                               cPrinterError=1;
                               break;
                           }
                       }
                       else
                       {
                           file.close();
                           break;
                       }
                   }

                   {

                       cSerialPrinter->flush();
                       cSerialPrinter->close();

                       disconnect(cSerialPrinter, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleErrorSerialPrinter(QSerialPort::SerialPortError)));
                       disconnect(cSerialPrinter, SIGNAL(readyRead()), this, SLOT(readSerialPrinter()));

                       cSettings.removeTmpFiles();

                       if(cPrinterError==2)
                       {
                           emit showMsgBox(tr("Memory Print"), tr("Printing done!"));
                           return true;
                       }
                       else return false;
                   }

               } 

            }
            else
            {
               emit showMsgBox(tr("Memory Print"), tr("Error Spooling!"));
                return false;
            }

        }
        else
        {
            cSerialPrinter->close();
            emit showMsgBox(tr("Memory Print"), cSerialPrinter->errorString());

            return false;
    }
}

int sTestModel::writeSerialPrinter(const QByteArray &data, int len)
{
    return cSerialPrinter->write(data, len);
}

int sTestModel::PrinterStatus(int fd)
{
    char status;

    if(::ioctl(fd, LPGETSTATUS, &status) < 0)
    {
        return 0;
    }

    return status;
}

int sTestModel::PrintData(int fd, char dtmp)
{
    char tmp[2];
    tmp[0] = dtmp;

    if( ::write(fd, (void *)&dtmp, 1) < 0)
    {
        return -1;
    }
    else
        return 0;

}

void sTestModel::drawData(QPainter *painter, int x, int y, int width, int height, QString str, QTextOption *textoption)
{
    int spacing = 50;

    QRect rectTitle(x, y, width, height);
    painter->drawRect(rectTitle);

    QRect rectTitleText(x+spacing, y+spacing, width+spacing, height+spacing);
    painter->drawText(rectTitleText, str, *textoption);

}

void sTestModel::setBrush(QPainter *painter, QBrush *brush, int row)
{
    if(row%2)
        brush->setColor(QColor(230,230,230));
    else
        brush->setColor(Qt::white);

    painter->setBrush(*brush);

}

bool sTestModel::CreateSingleDeskjet()
{
    QPrinter printer(QPrinter::HighResolution); 
    QString psize;

    if(cSettings.getPageSize()==REPORT_PAGE_SIZE_A4)
    {
        printer.setPageSize(QPrinter::A4);
        psize = "-o media=A4";
    }
    else
    {
        printer.setPageSize(QPrinter::Letter);
        psize = "-o media=Letter";
    }

    printer.setOrientation(QPrinter::Portrait);

    printer.setPageMargins (15, 15, 15, 15, QPrinter::Millimeter);
    printer.setFullPage(false);

    QString pfile = QApplication::applicationDirPath() + "/tmp/outputs_" + cSettings.getCurrentDateTime().toString("dd_MM_yyyy_hh_mm_ss_z") + ".pdf";

    printer.setOutputFileName(pfile);
    printer.setOutputFormat(QPrinter::PdfFormat); 

    QPainter painter(&printer); 
	
    for(int tmp=0; tmp < listTestRecord.count(); tmp++)
    {
        sTestRecord cTestRecord  = listTestRecord.at(tmp);

        if(cTestRecord.tm_sel)
        {
            struct TestStruct nRecord = TestStruct(cTestRecord.tm_sel,
                    cTestRecord.tm_operator, cTestRecord.tm_sample_id,
                    cTestRecord.tm_datetime,
                    cTestRecord.tm_p_tot, cTestRecord.tm_p_gas, cTestRecord.tm_p_abs,
                    cTestRecord.tm_method, cTestRecord.tm_formula,
                    cTestRecord.tm_aconst, cTestRecord.tm_bconst,
                    cTestRecord.tm_cconst,
                    cTestRecord.tm_result,
                    cTestRecord.tm_ttime, cTestRecord.tm_vlratio,
                    cTestRecord.tm_para_measured);

            if(tmp>0) printer.newPage();

            int w = printer.width();
            int h = printer.height();
            int hw = w/2;
            int dw = w/4;
            int tw = w/4;
            int vw = w-(w/4);

            int tm = 30, bm=15, lm=15, rm=15;
            int x=lm, y=tm;

            int row=0;

            QFont font_header = QFont("Arial", 20, QFont::Bold);
            QFont font_datetime = QFont("Arial", 18, QFont::Normal);

            QFont font_footer = QFont("Arial", 20,QFont::Bold, true);

            QFont font_title = QFont("Arial", 18, QFont::Bold);
            QFont font_value = QFont("Arial", 18, QFont::Normal);

            QTextOption to_header;
            to_header.setAlignment(Qt::AlignCenter);
            to_header.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

            QTextOption to_footer;
            to_footer.setAlignment(Qt::AlignLeft);
            to_footer.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

            QTextOption to_title;
            to_title.setAlignment(Qt::AlignLeft);
            to_title.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

            QTextOption to_value;
            to_value.setAlignment(Qt::AlignLeft);
            to_value.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

            QBrush brush;
            brush.setStyle(Qt::SolidPattern);

            setBrush(&painter, &brush, row);

            painter.drawRect(15, 30, printer.width(), printer.height());

            painter.setFont(font_header);
            drawData(&painter, x, y, hw, 800, "RVP Pro", &to_header);

            painter.setFont(font_footer);
            painter.drawText(x, h-15-30, "RVP Pro by PSSC");

            row++;

            if(cHeaderModel->getData(REPORT_DATE) || cHeaderModel->getData(REPORT_TIME))
            {
                painter.setFont(font_datetime);
                drawData(&painter, x+hw, y, dw, 800, "Date\n"+ cSettings.getDate(nRecord.datetime), &to_value);
                drawData(&painter, x+hw+dw, y, dw, 800, "Time\n"+ cSettings.getTime(nRecord.datetime), &to_value);
                y+=800;
            }

            if(cHeaderModel->getData(REPORT_TEST_METHOD))
            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 600, "Test method", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 600, cTestRecord.tm_method, &to_title);
                y+=600;
                row++;
            }

            if(cHeaderModel->getData(REPORT_FORMULA))
            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 800, "Correlation formula", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 800, cSettings.getFormula(nRecord.method, nRecord.formula,
                                                                         nRecord.aconst, nRecord.bconst,
                                                                         nRecord.cconst), &to_title);
                y+=800;
                row++;
            }

            if(cHeaderModel->getData(REPORT_SAMPLE_ID))
            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 600, "Sample id", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 600, cTestRecord.tm_sample_id, &to_title);
                y+=600;
                row++;
            }


            if( cHeaderModel->getData(REPORT_RESULT) ||
                cHeaderModel->getData(REPORT_P_TOT)  ||
                cHeaderModel->getData(REPORT_P_GAS)  ||
                cHeaderModel->getData(REPORT_P_ABS))
            {
                if(cTestRecord.tm_method != "D6377" && cTestRecord.tm_method != "D5188")
                {
                    setBrush(&painter, &brush, row);

                    painter.setFont(font_title);
                    drawData(&painter, x, y, tw, 1400, "Test result", &to_title);
                    drawData(&painter, x+dw, y, vw, 600, cSettings.getResult(nRecord.method, nRecord.result), &to_value);

                    painter.setFont(font_value);
                    drawData(&painter, x+dw, y+600, dw, 800, "Ptot\n" + cSettings.getPressure(nRecord.method, nRecord.p_tot), &to_value);
                    drawData(&painter, x+dw+dw, y+600, dw, 800, "Pgas\n" + cSettings.getPressure(nRecord.method, nRecord.p_gas), &to_value);
                    drawData(&painter, x+dw+dw+dw, y+600, dw, 800, "Pabs\n" + cSettings.getPressure(nRecord.method, nRecord.p_abs), &to_value);
                    y+=1400;
                    row++;
                }
                else
                {
                    setBrush(&painter, &brush, row);
                    painter.setFont(font_title);
                    drawData(&painter, x, y, tw, 600, "Test result", &to_title);
                    drawData(&painter, x+tw, y, vw, 600, cSettings.getResult(nRecord.method, nRecord.result), &to_value);
                    y+=600;
                    row++;
                }
            }



            if(cHeaderModel->getData(REPORT_TEST_TIME) && (cTestRecord.tm_method != "D5188"))
            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 600, "Test time", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 600, cSettings.getTestTime(nRecord.method, nRecord.ttime), &to_value);
                y+=600;
                row++;
            }

            if(cHeaderModel->getData(REPORT_VL_RATIO))
            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 600, "VL ratio", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 600, cSettings.getVLRatio(nRecord.vlratio), &to_value);
                y+=600;
                row++;
            }

            if(cHeaderModel->getData(REPORT_PARA_MEASURED))
            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 800, "Para\nmeasured", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 800, cSettings.getParaMeasured(nRecord.method, nRecord.para_measured), &to_value);
                y+=800;
                row++;
            }

            if(cHeaderModel->getData(REPORT_OPERATOR_ID))
            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 600, "Operator", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 600, nRecord.noperator, &to_value);
                y+=600;
                row++;
            }

            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 1200, "Comments", &to_title);
                drawData(&painter, x+tw, y, vw, 1200, "", &to_title);
                y+=1200;
                row++;
            }

            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 600, "Location", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 600, cSettings.getLocation(), &to_value);
                y+=600;
                row++;
            }

            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 600, "Unit id", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 600, cSettings.getUnitId(), &to_value);
                y+=600;
                row++;
            }

            {
                setBrush(&painter, &brush, row);
                painter.setFont(font_title);
                drawData(&painter, x, y, tw, 600, "Serial no.", &to_title);
                painter.setFont(font_value);
                drawData(&painter, x+tw, y, vw, 600, cSettings.getSerialNo(), &to_value);
                y+=600;
                row++;
            }
        }
    }

    painter.end();

    QProcess process;

    process.start("lpr -P usbdesktopprinter " + psize + pfile );

    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    QString err = process.readAllStandardError();

    cSettings.removeTmpFiles();

    return true;

}

bool sTestModel::CreateMultilineDeskjet()
{
    QPrinter printer(QPrinter::HighResolution); 
    QString psize;

    if(cSettings.getPageSize()==REPORT_PAGE_SIZE_A4)
    {
        printer.setPageSize(QPrinter::A4);
        psize = "-o media=A4 ";
    }
    else
    {
        printer.setPageSize(QPrinter::Letter);
        psize = "-o media=Letter ";
    }

    printer.setOrientation(QPrinter::Landscape);

    printer.setPageMargins (15, 15, 15, 15, QPrinter::Millimeter);
    printer.setFullPage(false);
    
    QString pfile = QApplication::applicationDirPath() + "/tmp/outputml_" + cSettings.getCurrentDateTime().toString("dd_MM_yyyy_hh_mm_ss_z") + ".pdf";

    printer.setOutputFileName(pfile);
    printer.setOutputFormat(QPrinter::PdfFormat);
    QPainter painter(&printer);

    int w = printer.width();
    int h = printer.height();

    QFont font_header = QFont("Arial", 20, QFont::Bold);
    QFont font_footer = QFont("Arial", 14,QFont::Bold, true);

    QFont font_title = QFont("Arial", 12, QFont::Normal);
    QFont font_value = QFont("Arial", 12, QFont::Normal);

    QFont font_data_header = QFont("Arial", 12, QFont::Bold);
    QFont font_data = QFont("Arial", 12, QFont::Normal);

    QTextOption to_header;
    to_header.setAlignment(Qt::AlignCenter);
    to_header.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    QTextOption to_footer;
    to_footer.setAlignment(Qt::AlignLeft);
    to_footer.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    QTextOption to_title;
    to_title.setAlignment(Qt::AlignLeft);
    to_title.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    QTextOption to_value;
    to_value.setAlignment(Qt::AlignLeft);
    to_value.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    QStringList qslTitle;
    QList <int> qilWidth;
    int col=0;

    if(cHeaderModel->getData(REPORT_DATE) || cHeaderModel->getData(REPORT_TIME))
    {
        qilWidth.insert(col, 1200);
        qslTitle.insert(col, "Date");
       
        col++;
        qilWidth.insert(col, 1200);
        qslTitle.insert(col, "Time");
        col++;
    }

    if(cHeaderModel->getData(REPORT_TEST_METHOD))
    {
        qilWidth.insert(col, 1300);
        qslTitle.insert(col, "Test method");
        col++;
    }

    if(cHeaderModel->getData(REPORT_FORMULA))
    {
        qilWidth.insert(col, 1200+1200+1200+1000);
        qslTitle.insert(col, "Formula");
        col++;
    }

    if(cHeaderModel->getData(REPORT_SAMPLE_ID))
    {
        qilWidth.insert(col, 1200+1200+1200+100);
        qslTitle.insert(col, "Sample id");
        col++;
    }

    if( cHeaderModel->getData(REPORT_RESULT))
    {
        qilWidth.insert(col, 1200);
        qslTitle.insert(col, "Result");
        col++;
    }
    if(cHeaderModel->getData(REPORT_P_TOT))
    {
        qilWidth.insert(col, 1200);
        qslTitle.insert(col, "Ptotal");
        col++;
    }
    if(cHeaderModel->getData(REPORT_P_GAS))
    {
        qilWidth.insert(col, 1200);
        qslTitle.insert(col, "Pgas");
        col++;
    }
    if(cHeaderModel->getData(REPORT_P_ABS))
    {
        qilWidth.insert(col, 1200);
        qslTitle.insert(col, "Pabs");
        col++;
    }

    if(cHeaderModel->getData(REPORT_TEST_TIME))
    {
        qilWidth.insert(col, 1000);
        qslTitle.insert(col, "Test time");
        col++;
    }

    if(cHeaderModel->getData(REPORT_VL_RATIO))
    {
        qilWidth.insert(col, 900);
        qslTitle.insert(col, "VL ratio");
        col++;
    }

    if(cHeaderModel->getData(REPORT_PARA_MEASURED))
    {
        qilWidth.insert(col, 1200+325+50);
        qslTitle.insert(col, "Para measured");
        col++;
    }

    if(cHeaderModel->getData(REPORT_OPERATOR_ID))
    {
        qilWidth.insert(col, 1200+1200+1200);
        qslTitle.insert(col, "Operator");
        col++;
    }

    w = w-300;

    int tw = w/4;
    int vw = w-(w/4);

    int tm = 15, bm = 15, lm = 15, rm = 15;
    int x = lm, y = tm;
    int spacing = 50;

    bool newPage = true;
    bool firstPage = true;

    int rowHeight = 300;
    int multiline = 1;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    for(int tmp=0; tmp < listTestRecord.count(); tmp++)
    {
        sTestRecord cTestRecord  = listTestRecord.at(tmp);

        if(cTestRecord.tm_sel)
        {
            struct TestStruct nRecord = TestStruct(cTestRecord.tm_sel,
                    cTestRecord.tm_operator, cTestRecord.tm_sample_id,
                    cTestRecord.tm_datetime,
                    cTestRecord.tm_p_tot, cTestRecord.tm_p_gas, cTestRecord.tm_p_abs,
                    cTestRecord.tm_method, cTestRecord.tm_formula,
                    cTestRecord.tm_aconst, cTestRecord.tm_bconst,
                    cTestRecord.tm_cconst,
                    cTestRecord.tm_result,
                    cTestRecord.tm_ttime, cTestRecord.tm_vlratio,
                    cTestRecord.tm_para_measured);

            if(newPage && !firstPage) printer.newPage();

            if(newPage)
            {
                firstPage = false;
                newPage = false;
                x = lm;
                y = tm;
                multiline = 1;

                painter.setFont(font_footer);
                painter.drawText(x, h-30, "RVP Pro by PSSC");

                {
                    brush.setColor(QColor(230,230,230));
                    painter.setBrush(brush);
                    painter.setFont(font_title);
                    drawData(&painter, x, y, tw, 400, "Location", &to_title);
                    painter.setFont(font_value);
                    drawData(&painter, x+tw, y, vw, 400, cSettings.getLocation(), &to_value);
                    y+=400;
                }

                {
                    brush.setColor(Qt::white);
                    painter.setBrush(brush);
                    painter.setFont(font_title);
                    drawData(&painter, x, y, tw, 400, "Unit id", &to_title);
                    painter.setFont(font_value);
                    drawData(&painter, x+tw, y, vw, 400, cSettings.getUnitId(), &to_value);
                    y+=400;
                }

                {
                    brush.setColor(QColor(230,230,230));
                    painter.setBrush(brush);
                    painter.setFont(font_title);
                    drawData(&painter, x, y, tw, 400, "Serial no.", &to_title);
                    painter.setFont(font_value);
                    drawData(&painter, x+tw, y, vw, 400, cSettings.getSerialNo(), &to_value);
                    y+=400;
                }

                brush.setColor(Qt::white);
                painter.setBrush(brush);

                painter.setFont(font_data_header);

                int xt = x;
                int spacing = 50;

                for(int title=0; title<qilWidth.length(); title++)
                {
                    if(xt + qilWidth.at(title) > w)
                    {
                        xt = x;
                        y += rowHeight;
                        multiline++;
                    }

                    QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(title)+spacing, rowHeight+spacing);
                    painter.drawText(rectTitleText, qslTitle.at(title), to_title);

                    xt += qilWidth.at(title);
                }

                y+=rowHeight;

                painter.drawLine(x, y, x+w, y);

                painter.setFont(font_data);

            }

            int xt = x, col=0;

            if(cHeaderModel->getData(REPORT_DATE) || cHeaderModel->getData(REPORT_TIME))
            {

                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText1(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText1, cSettings.getDate(nRecord.datetime), to_value);
                xt += qilWidth.at(col);
                col++;

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, cSettings.getTime(nRecord.datetime), to_value);
                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_TEST_METHOD))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, cTestRecord.tm_method, to_value);
                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_FORMULA))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, cSettings.getFormula(nRecord.method, nRecord.formula,
                                                                     nRecord.aconst, nRecord.bconst,
                                                                     nRecord.cconst), to_value);
                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_SAMPLE_ID))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, cTestRecord.tm_sample_id, to_value);
                xt += qilWidth.at(col);
                col++;
            }

            if( cHeaderModel->getData(REPORT_RESULT))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, cSettings.getResult(nRecord.method, nRecord.result), to_value);
                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_P_TOT))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);

                if(cTestRecord.tm_method != "D6377" && cTestRecord.tm_method != "D5188")
                    painter.drawText(rectTitleText, cSettings.getPressure(nRecord.method, nRecord.p_tot), to_value);
                else
                    painter.drawText(rectTitleText, "-", to_value);

                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_P_GAS))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);

                if(cTestRecord.tm_method != "D6377" && cTestRecord.tm_method != "D5188")
                    painter.drawText(rectTitleText, cSettings.getPressure(nRecord.method, nRecord.p_gas), to_value);
                else
                    painter.drawText(rectTitleText, "-", to_value);

                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_P_ABS))
            {

                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);

                if(cTestRecord.tm_method != "D6377" && cTestRecord.tm_method != "D5188")
                    painter.drawText(rectTitleText, cSettings.getPressure(nRecord.method, nRecord.p_abs), to_value);
                else
                    painter.drawText(rectTitleText, "-", to_value);

                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_TEST_TIME))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, cSettings.getTestTime(nRecord.method, nRecord.ttime), to_value);

                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_VL_RATIO))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, cSettings.getVLRatio(nRecord.vlratio), to_value);
                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_PARA_MEASURED))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, cSettings.getParaMeasured(nRecord.method, nRecord.para_measured), to_value);
                xt += qilWidth.at(col);
                col++;
            }

            if(cHeaderModel->getData(REPORT_OPERATOR_ID))
            {
                if(xt + qilWidth.at(col) > w)
                {
                    xt = x;
                    y += rowHeight;
                }

                QRect rectTitleText(xt+spacing, y+spacing, qilWidth.at(col)+spacing, rowHeight+spacing);
                painter.drawText(rectTitleText, nRecord.noperator, to_value);
                xt += qilWidth.at(col);
                col++;
            }

            y+=rowHeight;
            painter.drawLine(x, y, x+w, y);

            if((y+(rowHeight * (multiline+1))+50) > (h-15))
            {
                newPage = true;
            }

        }
    }

    painter.end();

    QProcess process;

    process.start("lpr -P usbdesktopprinter " + psize + pfile );

    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    QString err = process.readAllStandardError();

    cSettings.removeTmpFiles();

    return true;
}

bool sTestModel::CreatePrintSpool(void)
{

    QString fname = QApplication::applicationDirPath() + "/tmp/print.txt";

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream save(&out);

        for(int tmp=0; tmp < listTestRecord.count(); tmp++)
        {
            sTestRecord cTestRecord  = listTestRecord.at(tmp);

            if(cTestRecord.tm_sel)
            {
                struct TestStruct nRecord = TestStruct(cTestRecord.tm_sel,
                        cTestRecord.tm_operator, cTestRecord.tm_sample_id,
                        cTestRecord.tm_datetime,
                        cTestRecord.tm_p_tot, cTestRecord.tm_p_gas, cTestRecord.tm_p_abs,
                        cTestRecord.tm_method, cTestRecord.tm_formula,
                        cTestRecord.tm_aconst, cTestRecord.tm_bconst,
                        cTestRecord.tm_cconst,
                        cTestRecord.tm_result,
                        cTestRecord.tm_ttime, cTestRecord.tm_vlratio,
                        cTestRecord.tm_para_measured);

                save << "------------------------------------------" << endl;
                save << cSettings.getCompany() << endl;
                save << cSettings.getLocation() << endl;
                save << cSettings.getUnitId()<< endl;
                save << "SERIAL NO:" << cSettings.getSerialNo() << endl;
                save << "------------------------------------------" << endl;

                if(cHeaderModel->getData(8)) save << tr("Tested Method: ") << cTestRecord.tm_method << endl;

                if(cHeaderModel->getData(3) || cHeaderModel->getData(4))
                    save << tr("Date Time: ") << cSettings.getDate(nRecord.datetime) << " "
                    << cSettings.getTime(nRecord.datetime) << endl;

                if(cHeaderModel->getData(2)) save << tr("Sample Id: ") << nRecord.sample_id << endl;

                if(cHeaderModel->getData(10)) save << tr("TEST RESULT: ") << cSettings.getResult(nRecord.method, nRecord.result) << endl;

                if(cTestRecord.tm_method != "D6377" && cTestRecord.tm_method != "D5188")
                {
                    save << tr("Ptot: ") << cSettings.getPressure(nRecord.method, nRecord.p_tot) << endl;
                    save << tr("Pgas: ") << cSettings.getPressure(nRecord.method, nRecord.p_gas) << endl;
                    save << tr("Pabs: ") << cSettings.getPressure(nRecord.method, nRecord.p_abs) << endl;
                }

                if(cHeaderModel->getData(13))
                    save << tr("Para Measured: ") << cSettings.getParaMeasured(nRecord.method, nRecord.para_measured) << endl;

                if(cHeaderModel->getData(9))
                    save << tr("Correlation formula used: ") << endl
                        << cSettings.getFormula(nRecord.method, nRecord.formula,
                                      nRecord.aconst, nRecord.bconst,
                                      nRecord.cconst) << endl;

                if(cHeaderModel->getData(11) && (cTestRecord.tm_method != "D5188"))
                    save << tr("Test Time: ") << cSettings.getTestTime(nRecord.method, nRecord.ttime) << endl;
                if(cHeaderModel->getData(12)) save << tr("VL Ratio: ") << cSettings.getVLRatio(nRecord.vlratio) << endl;

                if(cHeaderModel->getData(1))
                    save << tr("Operator: ")
                         << nRecord.noperator << endl << endl;

                save << tr("Comment: ") << endl << endl << endl;

                save << endl << endl;

            }
        }

        out.close();

        return true;
    }
    else
        return false;
}

int sTestModel::PrintQString(QString tmp)
{
    QByteArray ba = tmp.toLocal8Bit();
    char *c_str2 = ba.data();
    return ::write(m_fd, &c_str2[0], ba.length());
}

void sTestModel::readPrintStatus(void)
{
    char buffer[10];
    int rn=0, tmp = 0;

    rn = ::read(m_fd, buffer, 9);

    if(rn==9)
    {
        if(((~buffer[0] & 0x90) == 0x90) && (buffer[0] & 1) &&
           ((~buffer[1] & 0x11) == 0x11))
        {
            if((~buffer[2] & 0x91) == 0x91)
            {
                if(buffer[2] & 8)
                {
                    cPrinterError = 1;
                }
                else
                {
                    cPrinterError = 2;
                }
            }
        }
    }

}

void sTestModel::readSerialPrinter()
{

    QByteArray buffer = cSerialPrinter->readAll();

    if(buffer.length() == 9)
    {
        if(((~buffer[0] & 0x90) == 0x90) && (buffer[0] & 1) &&
           ((~buffer[1] & 0x11) == 0x11))
        {
            if((~buffer[2] & 0x91) == 0x91)
            {
                if(buffer[2] & 8)
                {
                    cPrinterError = 1;
                }
                else
                {
                    cPrinterError = 2; 
                }
            }
            
        }
    }
}

void sTestModel::handleErrorSerialPrinter(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        emit showMsgBox(tr("Memory Print"), cSerialPrinter->errorString());
        if(cSerialPrinter->isOpen()) cSerialPrinter->close();
    }
}
