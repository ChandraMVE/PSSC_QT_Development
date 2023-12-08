######################################################################
# Automatically generated by qmake (3.1) Tue Jun 22 13:21:17 2021
######################################################################

QT       += core gui serialport printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = pApp-3-Nov-2022
INCLUDEPATH += .

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += defaults_calibration.h \
           defaults_general.h \
           defaults_memory.h \
           defaults_method.h \
           defaults_service.h \
           defaults_user.h \
           define_strings.h \
           defines.h \
           mainwindow.h \
           scalibration.h \
           scheckpass.h \
           scleaning.h \
           sfileselect.h \
           sgeneralsetup.h \
           skeypad.h \
           smeasuring.h \
           smeasuring2.h \
           smemory.h \
           smenubar.h \
           smethodsetup.h \
           sprotocol.h \
           sqleextend.h \
           sservice.h \
           ssettings.h \
           stestmodel.h \
           stestmodelheader.h \
           stestrecord.h \
           saccesswidget.h \
           slabel.h \
           susersetup.h
FORMS += mainwindow.ui \
         scalibration.ui \
         scheckpass.ui \
         scleaning.ui \
         sfileselect.ui \
         sgeneralsetup.ui \
         skeypad.ui \
         smeasuring.ui \
         smeasuring2.ui \
         smemory.ui \
         smenubar.ui \
         smethodsetup.ui \
         sservice.ui \
         slabel.ui \
         susersetup.ui
SOURCES += main.cpp \
           mainwindow.cpp \
           scalibration.cpp \
           scheckpass.cpp \
           scleaning.cpp \
           sfileselect.cpp \
           sgeneralsetup.cpp \
           skeypad.cpp \
           smeasuring.cpp \
           smeasuring2.cpp \
           smemory.cpp \
           smenubar.cpp \
           smethodsetup.cpp \
           sprotocol.cpp \
           sqleextend.cpp \
           sservice.cpp \
           ssettings.cpp \
           stestmodel.cpp \
           stestmodelheader.cpp \
           stestrecord.cpp \
           saccesswidget.cpp \
           slabel.cpp \
           susersetup.cpp
RESOURCES += pRes.qrc
TRANSLATIONS += languages/pApp_de.ts languages/pApp_fr.ts languages/pApp_la.ts
