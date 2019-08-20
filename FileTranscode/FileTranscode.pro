QT += core
QT -= gui

TARGET = FileTranscode
CONFIG += console  c++11
CONFIG -= app_bundle

TEMPLATE = app

include(../build.pri)

SOURCES += main.cpp

