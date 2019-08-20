QT += core
QT -= gui

TARGET = PowerCtrl
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp \
    Worker.cpp

HEADERS += \
    Worker.h

