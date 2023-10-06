#ifndef SQLEEXTEND_H
#define SQLEEXTEND_H

#include <QLineEdit>
#include <QTimer>
#include <QMouseEvent>

class sQLEExtend : public QLineEdit
{
    Q_OBJECT
public:
    explicit sQLEExtend(QWidget *parent = 0);
    ~sQLEExtend();

signals:
    void showKeypad(int type);
    void click(void);

protected:
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

    QTimer *cTimer;
    int cKeydown;

public slots:
    void onTimeOut(void);

};

#endif // SQLEEXTEND_H
