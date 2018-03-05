#-------------------------------------------------
#
# Project created by QtCreator 2017-08-12T21:03:55
#
#-------------------------------------------------

QT       += core gui axcontainer
RC_ICONS = app.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testWidget
TEMPLATE = app


SOURCES += main.cpp\
    titlebar.cpp \
    frameless_helper.cpp \
    framelesswindow.cpp \
    mainwindow.cpp \
    form.cpp

HEADERS  += \
    titlebar.h \
    frameless_helper.h \
    framelesswindow.h \
    mainwindow.h \
    form.h

FORMS    += \
    framelesswindow.ui \
    mainwindow.ui \
    form.ui

RESOURCES += \
    res.qrc



