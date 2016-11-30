#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T22:26:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CT4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    table.cpp \
    logicengine.cpp

HEADERS  += mainwindow.h \
    table.h \
    logicengine.h

FORMS    += mainwindow.ui

CONFIG += console qtestlib

RESOURCES += \
    resources.qrc
