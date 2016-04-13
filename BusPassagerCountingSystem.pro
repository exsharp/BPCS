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
    util.cpp \
    partition.cpp

HEADERS  += mainwindow.h \
    CodeBook.h \
    util.h \
    integralprojection.h

FORMS    += \
    mainwindow.ui

unix {
    LIBS += /lib/libopencv*.so
}

win32 {
    INCLUDEPATH+=c:/opencv/build/include/
    LIBS+=c:/opencv/build/x86/vc12/lib/opencv_*.lib
}


