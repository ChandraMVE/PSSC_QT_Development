#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *pSplash = new QSplashScreen();
    pSplash->move(0, 0);

    pSplash->setPixmap(QPixmap(":images/logo/splash.jpg"));

    MainWindow w;

    QPixmap cursor_pixmap = QPixmap(":images/cursors/pointer.png");  
    QCursor cursor_default = QCursor(cursor_pixmap, 19, 0);
    a.setOverrideCursor(cursor_default);

    w.hide();
    pSplash->show();

    QTimer::singleShot(5, pSplash, SLOT(hide()));
    QTimer::singleShot(500, &w, SLOT(onLoad()));

    return a.exec();

}
