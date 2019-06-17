TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt
QT +=gui
QT +=widgets
LIBS += `pkg-config --libs opencv` -lqwt

SOURCES += main.cpp

HEADERS += \
    convert.h
