#ifndef SCLEANING_H
#define SCLEANING_H

#include <QWidget>
#include <ssettings.h>

namespace Ui {
class sCleaning;
}

class sCleaning : public QWidget
{
    Q_OBJECT

public:
    explicit sCleaning(QWidget *parent = 0);
    ~sCleaning();
    void onLiveData(int tm, int pr);
    void Show(void);
    void setRunning(bool tmp);
    void updateStatus(int current, int total);

signals:
    void showHome(bool);
    void runClicked(int state, bool init);

private slots:
    void on_pbRun_clicked();
    void on_pbStop_clicked();

private:
    Ui::sCleaning *ui;

    sSettings cSettings;
};

#endif // SCLEANING_H
