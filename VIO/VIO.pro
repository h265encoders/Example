QT += core
QT -= gui

TARGET = VIO
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

chip = HI3531D
include(/home/linkpi/work/LinkLib/Link.pri)

SOURCES += main.cpp

