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
    int getLanguage();
    void wmSetupsetSelected(bool); //naveen

signals:
    void MenuClicked(int menu);

private slots:
    void onMeasuringClicked();
    void onCleaningClicked();
    void onMemoryClicked();
    void onSetupClicked();

private:
    Ui::sMenuBar *ui;
    QString styleActive;
    QString styleDisabled;
    QString styleRunning;
    QString styleSelected;

    int pMenu;

};

#endif // SMENUBAR_H
