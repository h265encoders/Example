QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OLED
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

LIBS +=-lLinkUI

SOURCES += main.cpp \
    Widget.cpp

FORMS += \
    Widget.ui

HEADERS += \
    Widget.h

DISTFILES += \
    test.png

RESOURCES += \
    res.qrc

