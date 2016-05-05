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
    partition.cpp \
    targettrace.cpp \
    controler.cpp

HEADERS  += mainwindow.h \
    CodeBook.h \
    partition.h \
    targettrace.h \
    controler.h

FORMS    += \
    mainwindow.ui

INCLUDEPATH += /usr/local/arm/opencv/include/

LIBS += -L /usr/local/arm/opencv/lib/ -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core

#unix {
#    LIBS += /lib/libopencv*.so
#}

#win32 {
#    INCLUDEPATH+=c:/opencv/build/include/
#    LIBS+=c:/opencv/build/x86/vc12/lib/opencv_*.lib
#}


