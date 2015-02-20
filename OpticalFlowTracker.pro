#-------------------------------------------------
#
# Project created by QtCreator 2014-04-30T07:19:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpticalFlowTracker
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    trackfeature.cpp

HEADERS += dialog.h \
    trackfeature.h

FORMS += dialog.ui
LIBS  += `pkg-config opencv --libs`
CONFIG+= console

