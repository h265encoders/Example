QT += core
QT -= gui

TARGET = LowLatencyDEC
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp

