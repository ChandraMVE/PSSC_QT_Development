#ifndef SFILESELECT_H
#define SFILESELECT_H

#include <QWidget>
#include <QDir>
#include <QFileInfoList>
#include <defines.h>

namespace Ui {
class sFileSelect;
}

class sFileSelect : public QWidget
{
    Q_OBJECT

public:
    explicit sFileSelect(QWidget *parent = 0);
    ~sFileSelect();
    void Show(void);

signals:
    void FileSelected(QString fs);

private slots:
    void on_pbSelected_clicked();

    void on_pbCancel_clicked();

    void on_pbOK_clicked();

    void on_imageCapture_clicked();

private:
    Ui::sFileSelect *ui;
};

#endif // SFILESELECT_H
