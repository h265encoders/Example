QT += core
QT -= gui

TARGET = DIY
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp \
    Bypass.cpp \
    Sink.cpp \
    Source.cpp

HEADERS += \
    Bypass.h \
    Sink.h \
    Source.h

