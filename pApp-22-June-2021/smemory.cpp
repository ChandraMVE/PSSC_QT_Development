#include "smemory.h"
#include "ui_smemory.h"
#include <QScrollBar>
#include <QEventLoop>
#include <QTimer>

sMemory::sMemory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sMemory)
{
    ui->setupUi(this);

    setDefaults();

    MemoryModel = new sTestModel(this);
    MemoryModelHeader = new sTestModelHeader(this);

    ui->wTableView->setModel(MemoryModel);

    ui->wTableView->horizontalHeader()->setVisible(true);
    ui->wTableView->setWordWrap(true);
    ui->wTableView->show();

    ui->wTableView->setSelectionMode(QAbstractItemView::NoSelection);

    ui->wTableView->setColumnWidth(0, T_SEL_COL_WIDTH);
    ui->wTableView->setColumnWidth(1, T_OPERATOR_COL_WIDTH);
    ui->wTableView->setColumnWidth(2, T_SAMPLE_ID_COL_WIDTH); 
    ui->wTableView->setColumnWidth(3, T_DATE_COL_WIDTH); 
    ui->wTableView->setColumnWidth(4, T_TIME_COL_WIDTH); 
    ui->wTableView->setColumnWidth(5, T_PTOT_COL_WIDTH);  
    ui->wTableView->setColumnWidth(6, T_PGAS_COL_WIDTH);  
    ui->wTableView->setColumnWidth(7, T_PABS_COL_WIDTH);  
    ui->wTableView->setColumnWidth(8, T_METHOD_COL_WIDTH);  
    ui->wTableView->setColumnWidth(9, T_FORMULA_COL_WIDTH);  
    ui->wTableView->setColumnWidth(10, T_RESULTS_COL_WIDTH);  
    ui->wTableView->setColumnWidth(11, T_TTIME_COL_WIDTH);  
    ui->wTableView->setColumnWidth(12, T_VLRATIO_COL_WIDTH);  
    ui->wTableView->setColumnWidth(13, T_P_MEASURED_COL_WIDTH); 

    ui->wTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ui->wTableView->resizeRowsToContents();

    MemoryModelHeader->populateData(
                selected_cols.sel, selected_cols.nooperator, selected_cols.sample_id,
                selected_cols.date, selected_cols.time,
                selected_cols.p_tot, selected_cols.p_gas, selected_cols.p_abs,
                selected_cols.method, selected_cols.formula, selected_cols.result,
                selected_cols.ttime, selected_cols.vl_ratio, selected_cols.para_measured);

    MemoryModel->setHeaderModel(MemoryModelHeader);

    ui->wTableViewHeader->setModel(MemoryModelHeader);
    ui->wTableViewHeader->horizontalHeader()->setVisible(false);

    ui->wTableViewHeader->setWordWrap(true);
    ui->wTableViewHeader->show();
    ui->wTableViewHeader->setSelectionMode(QAbstractItemView::NoSelection);

//    ui->wTableViewHeader->setColumnWidth(0, T_SEL_COL_WIDTH + 10);
    ui->wTableViewHeader->setColumnWidth(0, T_SEL_COL_WIDTH);
    ui->wTableViewHeader->setColumnWidth(1, T_OPERATOR_COL_WIDTH); 
    ui->wTableViewHeader->setColumnWidth(2, T_SAMPLE_ID_COL_WIDTH); 
    ui->wTableViewHeader->setColumnWidth(3, T_DATE_COL_WIDTH); 
    ui->wTableViewHeader->setColumnWidth(4, T_TIME_COL_WIDTH);  
    ui->wTableViewHeader->setColumnWidth(5, T_PTOT_COL_WIDTH); 
    ui->wTableViewHeader->setColumnWidth(6, T_PGAS_COL_WIDTH);  
    ui->wTableViewHeader->setColumnWidth(7, T_PABS_COL_WIDTH);  
    ui->wTableViewHeader->setColumnWidth(8, T_METHOD_COL_WIDTH);  
    ui->wTableViewHeader->setColumnWidth(9, T_FORMULA_COL_WIDTH);  
    ui->wTableViewHeader->setColumnWidth(10, T_RESULTS_COL_WIDTH);  
    ui->wTableViewHeader->setColumnWidth(11, T_TTIME_COL_WIDTH);  
    ui->wTableViewHeader->setColumnWidth(12, T_VLRATIO_COL_WIDTH);  
    ui->wTableViewHeader->setColumnWidth(13, T_P_MEASURED_COL_WIDTH); 

    ui->wTableViewHeader->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed); 

    ui->wTableViewHeader->setRowHeight(0, 54); //changed from 68 to 54

//    ui->wTableViewHeader->hide();

    QObject::connect(ui->wTableView->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->wTableViewHeader->horizontalScrollBar(), SLOT(setValue(int)));
    QObject::connect(ui->wTableViewHeader->horizontalScrollBar(), SIGNAL(valueChanged(int)), ui->wTableView->horizontalScrollBar(), SLOT(setValue(int)));
    QObject::connect(ui->wTableView->model(), SIGNAL(showMsgBox(QString, QString)), this, SLOT(onShowMsgBox(QString, QString)));
    QObject::connect(ui->wTableView->model(), SIGNAL(showStatusBox(QString, QString, bool)), this, SLOT(onShowStatusBox(QString, QString, bool)));

    cParasChanged = false;
    cEnSwitch = true;

    ui->imageCapture->hide();
}

sMemory::~sMemory()
{
    delete ui;
}

void sMemory::Show()
{
    this->show();

    MemoryModelHeader->populateData(
                selected_cols.sel, selected_cols.nooperator, selected_cols.sample_id,
                selected_cols.date, selected_cols.time,
                selected_cols.p_tot, selected_cols.p_gas, selected_cols.p_abs,
                selected_cols.method, selected_cols.formula, selected_cols.result,
                selected_cols.ttime, selected_cols.vl_ratio, selected_cols.para_measured);

    ui->wTableView->update(); 
    ui->wTableView->resizeRowsToContents();

}

void sMemory::setDefaults()
{
    selected_cols.sel = DEFAULT_SEL_HEADER_SELECT;
    selected_cols.nooperator = DEFAULT_SEL_HEADER_OPERATOR;
    selected_cols.sample_id = DEFAULT_SEL_HEADER_SAMPLE_D;
    selected_cols.date = DEFAULT_SEL_HEADER_DATE;
    selected_cols.time = DEFAULT_SEL_HEADER_TIME;
    selected_cols.p_tot = DEFAULT_SEL_HEADER_PTOTAL;
    selected_cols.p_gas = DEFAULT_SEL_HEADER_PGAS;
    selected_cols.p_abs = DEFAULT_SEL_HEADER_PABS;
    selected_cols.method = DEFAULT_SEL_HEADER_METHOD;
    selected_cols.formula = DEFAULT_SEL_HEADER_FORMULA;
    selected_cols.result = DEFAULT_SEL_HEADER_RESULT;
    selected_cols.ttime = DEFAULT_SEL_HEADER_TEST_TIME;
    selected_cols.vl_ratio= DEFAULT_SEL_HEADER_VL_RATIO;
    selected_cols.para_measured = DEFAULT_SEL_HEADER_PARA_MEASURED;
}

bool sMemory::readFile()
{
    QString fname = QApplication::applicationDirPath() + FN_MEMORY_SETUP;

    QFile in(fname);

    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream save(&in);
        save >> selected_cols;
        in.close();

        cParasChanged = false;

        MemoryModelHeader->populateData(
                    selected_cols.sel, selected_cols.nooperator, selected_cols.sample_id,
                    selected_cols.date, selected_cols.time,
                    selected_cols.p_tot, selected_cols.p_gas, selected_cols.p_abs,
                    selected_cols.method, selected_cols.formula, selected_cols.result,
                    selected_cols.ttime, selected_cols.vl_ratio, selected_cols.para_measured);

        return true;
    }
    else
    {
        setDefaults();
        cParasChanged = true;
        return false;
    }
}

void sMemory::saveFile()
{

    QString fname = QApplication::applicationDirPath() + FN_MEMORY_SETUP;

    QFile out(fname);

    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream save(&out);
        save << selected_cols;
        out.close();
        cParasChanged = false;
    }
    
}

void sMemory::updateMemorySetup()
{
    selected_cols.sel = DEFAULT_SEL_HEADER_SELECT;

    if(selected_cols.nooperator != MemoryModelHeader->getData(1)) cParasChanged = 1;
    selected_cols.nooperator = MemoryModelHeader->getData(1);

    if(selected_cols.sample_id != MemoryModelHeader->getData(2)) cParasChanged = 1;
    selected_cols.sample_id = MemoryModelHeader->getData(2);

    if(selected_cols.date != MemoryModelHeader->getData(3)) cParasChanged = 1;
    selected_cols.date = MemoryModelHeader->getData(3);

    if(selected_cols.time != MemoryModelHeader->getData(4)) cParasChanged = 1;
    selected_cols.time = MemoryModelHeader->getData(4);


    if(selected_cols.p_tot != MemoryModelHeader->getData(5)) cParasChanged = true;
    selected_cols.p_tot = MemoryModelHeader->getData(5);

    if(selected_cols.p_gas != MemoryModelHeader->getData(6)) cParasChanged = true;
    selected_cols.p_gas = MemoryModelHeader->getData(6);

    if(selected_cols.p_abs != MemoryModelHeader->getData(7)) cParasChanged = true;
    selected_cols.p_abs = MemoryModelHeader->getData(7);

    if(selected_cols.method != MemoryModelHeader->getData(8)) cParasChanged = true;
    selected_cols.method = MemoryModelHeader->getData(8);

    if(selected_cols.formula != MemoryModelHeader->getData(9)) cParasChanged = true;
    selected_cols.formula = MemoryModelHeader->getData(9);

    if(selected_cols.result != MemoryModelHeader->getData(10)) cParasChanged = true;
    selected_cols.result = MemoryModelHeader->getData(10);

    if(selected_cols.ttime != MemoryModelHeader->getData(11)) cParasChanged = true;
    selected_cols.ttime = MemoryModelHeader->getData(11);

    if(selected_cols.vl_ratio != MemoryModelHeader->getData(12)) cParasChanged = true;
    selected_cols.vl_ratio = MemoryModelHeader->getData(12);

    if(selected_cols.para_measured != MemoryModelHeader->getData(13)) cParasChanged = true;
    selected_cols.para_measured = MemoryModelHeader->getData(13);

}

bool sMemory::readTests()
{
    return MemoryModel->ReadAllRecords();
}

bool sMemory::deleteTests()
{
    bool ret = MemoryModel->RemoveRecord();
    ui->wTableView->resizeRowsToContents();

    cEnSwitch = true;

    return ret;
}

bool sMemory::transferTests(QString fname)
{
    emit showStatusBox(tr("Memory Transfer"),tr("Selected Memory is Transferring..."),true);
    QEventLoop delay;
    QTimer::singleShot(1000,&delay,&QEventLoop::quit);
    delay.exec();
    bool tmp = MemoryModel->TransferRecords(fname);
    cEnSwitch = true;
    return tmp;
}

bool sMemory::saveResult(QString noperator, QString sampleID, QString datetime, double p_tot, double p_gas, double p_abs, QString method, QString formula, double aconst, double bconst, double cconst, double result, double t_time, double vlratio, double para_measured)
{
    return MemoryModel->AppendRecord(1, noperator, sampleID, datetime, p_tot, p_gas, p_abs, method, formula, aconst, bconst, cconst, result, t_time, vlratio, para_measured);
}

bool sMemory::printResult(struct TestStruct *test)
{
    return MemoryModel->PrintRecords(false, test);
}

int sMemory::getMemoryCount()
{
    return MemoryModel->rowCount();
}

bool sMemory::isSwitchEnabled(int tmp)
{
    ui->pbPrint->setEnabled(true);
    ui->pbTransfer->setEnabled(true);
    ui->pbDelete->setEnabled(true);

    updateMemorySetup();

    if(cParasChanged) saveFile();

    return cEnSwitch;
}

void sMemory::on_wTableViewHeader_clicked(const QModelIndex &index)
{

   MemoryModelHeader->setData(index);

   if(index.column()==0) MemoryModel->setAll();

   ui->wTableView->update();
}

void sMemory::on_wTableView_clicked(const QModelIndex &index)
{
    MemoryModel->setData(index);

    ui->wTableView->update();
}

void sMemory::on_pbExit_clicked()
{
    ui->pbPrint->setEnabled(true);
    ui->pbTransfer->setEnabled(true);
    ui->pbDelete->setEnabled(true);

    updateMemorySetup();

    if(cParasChanged) saveFile();

    {
        this->hide();
        emit showHome(false);
    }
}

void sMemory::on_pbDelete_clicked()
{
    cEnSwitch = false;

    ui->pbDelete->setEnabled(false);

    if(MemoryModel->getSelectedCount() > 0)
        emit getConfirmation(M_CONFIRM_DELETE, M_MEMORY);
    else
    {
        emit showMsgBox(tr("Memory Delete"), tr("Select  tests/columns!"));
        cEnSwitch = true;
    }

    ui->pbDelete->setEnabled(true);
}

void sMemory::on_pbTransfer_clicked()
{
    cEnSwitch = false;

    ui->pbTransfer->setEnabled(false);

    if(MemoryModel->getSelectedCount() > 0)
        emit getConfirmation(M_CONFIRM_TRANSFER, M_MEMORY);
    else
    {
        emit showMsgBox(tr("Memory Transfer"), tr("Select  tests/columns!"));
        cEnSwitch = true;
    }

    ui->pbTransfer->setEnabled(true);
}

void sMemory::on_pbPrint_clicked()
{

    cEnSwitch = false;

    ui->pbPrint->setEnabled(false);
	
    if(MemoryModel->getSelectedCount() > 0)
    {
            MemoryModel->PrintRecords(true, NULL);
            cEnSwitch = true;
    }
    else
    {
        emit showMsgBox(tr("Memory Print"), tr("Select  tests/columns!"));
        cEnSwitch = true;
    }

    ui->pbPrint->setEnabled(true);
}

void sMemory::onShowMsgBox(QString title, QString msg)
{
    emit showMsgBox(title, msg);
}

void sMemory::onShowStatusBox(QString title, QString msg, bool show)
{
    emit showStatusBox(title, msg, show);
}

void sMemory::on_imageCapture_clicked()
{
    QDir usbRootDir("/run/media/sda1/");
    if (usbRootDir.exists())
    {
        QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");

//        QString filename = QApplication::applicationDirPath() + QString("/screenshot/smemory_%1.png").arg(timestamp);
        QString filename = QString("/run/media/sda1/screenshot/_%1_smemory.png").arg(timestamp);
        QWidget *widget = QApplication::activeWindow();
        QPixmap pixmap = QPixmap::grabWidget(widget);
        //    QString path = QApplication::applicationDirPath() + "/screenshot/screenshot.png";
        ui->imageCapture->setFocusPolicy(Qt::NoFocus);
        qDebug()<<"path : "<<filename;
        pixmap.save(QString(filename));
    }else{
        qDebug()<<"folder doesn't exist";
    }
}
