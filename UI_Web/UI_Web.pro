QT       += core gui webkit webkitwidgets

TARGET = UI_Web

TEMPLATE = app

include(../build.pri)
LIBS+=-L $$CROSS/icu/lib -licudata -licui18n -licuuc

SOURCES += main.cpp

DISTFILES += \
    ../bin/web.html

