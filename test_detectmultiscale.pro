#-------------------------------------------------
#
# Project created by QtCreator 2012-10-23T11:26:13
#
#-------------------------------------------------

QT       -= gui

TARGET = test_detectmultiscale
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += maincpp.cpp \
    mainwindow.cpp

INCLUDEPATH += C:/Users/archo/OneDrive/Bureau/opencv-4.11.0/build/install/include
LIBS += -LC:/Users/archo/OneDrive/Bureau/opencv-4.11.0/build/bin \
    -lopencv_core4110 \
    -lopencv_highgui4110 \
    -lopencv_imgproc4110 \
    -lopencv_imgcodecs4110 \
    -lopencv_videoio4110 \
    -lopencv_features2d4110 \
    -lopencv_calib3d4110 \
    -lopencv_objdetect4110

HEADERS += \
    mainwindow.h

QT += widgets
