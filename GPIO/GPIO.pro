QT += core
QT -= gui

TARGET = GPIO
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

chip = HI3531D
include(/home/linkpi/work/LinkLib/Link.pri)
DESTDIR +=../bin

SOURCES += main.cpp

