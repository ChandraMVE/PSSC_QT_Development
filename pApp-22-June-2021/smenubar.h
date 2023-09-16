#ifndef SMENUBAR_H
#define SMENUBAR_H

#include <QWidget>
#include "defines.h"
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class sMenuBar;
}

class sMenuBar : public QWidget
{
    Q_OBJECT

public:
    explicit sMenuBar(QWidget *parent = 0);
    ~sMenuBar();

    void setSelectedMenu(int menu);
    void setRunningMenu(int menu);

signals:
    void MenuClicked(int menu);

private slots:
    void on_pbMeasuring_clicked();

    void on_pbCleaning_clicked();

    void on_pbMemory_clicked();

    void on_pbSetup_clicked();

private:
    Ui::sMenuBar *ui;
    QString styleActive;
    QString styleDisabled;
    QString styleRunning;
    QString styleSelected;

    int pMenu;

};

#endif // SMENUBAR_H
