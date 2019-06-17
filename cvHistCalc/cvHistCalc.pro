TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

QT += core gui widgets

SOURCES += main.cpp

LIBS += `pkg-config --libs opencv`

HEADERS += \
    main.h
