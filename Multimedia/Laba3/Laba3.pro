#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T14:46:43
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Laba3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    histogram.cpp

HEADERS  += mainwindow.h \
    histogram.h

FORMS    += mainwindow.ui \
    histogram.ui

LIBS += `pkg-config --libs opencv`
