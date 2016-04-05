#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T13:00:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BusPassagerCountingSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CodeBook.cpp \
    util.cpp

HEADERS  += mainwindow.h \
    CodeBook.h \
    util.h

FORMS    += \
    mainwindow.ui

LIBS += /lib/libopencv*.so
