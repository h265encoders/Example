#-------------------------------------------------
#
# Project created by QtCreator 2019-05-11T05:50:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UI
TEMPLATE = app

chip = HI3531D
include(/home/linkpi/work/LinkLib/Link.pri)
DESTDIR +=../bin

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui
