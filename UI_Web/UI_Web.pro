QT       += core gui webkit webkitwidgets

TARGET = UI_Web

TEMPLATE = app

chip = HI3531D
include(/home/linkpi/work/LinkLib/Link.pri)
LIBS+=-L $$CROSS/icu/lib -licudata -licui18n -licuuc
DESTDIR +=../bin

SOURCES += main.cpp

DISTFILES += \
    ../bin/web.html

