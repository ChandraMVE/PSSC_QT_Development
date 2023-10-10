#ifndef SLABEL_H
#define SLABEL_H

#include <QWidget>

namespace Ui {
class slabel;
}

class slabel : public QWidget
{
    Q_OBJECT

public:
    explicit slabel(QWidget *parent = 0);
    ~slabel();

    void setText(QString caption);
    void setEnabled(bool tmp);
    void setSelected(bool tmp);
    void setRunning();
    void setFirmware(QString caption);


signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *);

private:
    Ui::slabel *ui;
    bool enabled;
};

#endif // SLABEL_H

