QT += core
QT -= gui

TARGET = DIY
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

chip = HI3531D
include(/home/linkpi/work/LinkLib/Link.pri)
DESTDIR +=../bin
SOURCES += main.cpp \
    Bypass.cpp

HEADERS += \
    Bypass.h

