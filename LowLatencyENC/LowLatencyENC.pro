QT += core
QT -= gui

TARGET = LowLatencyENC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp

