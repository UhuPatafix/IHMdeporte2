#-------------------------------------------------
#
# Project created by QtCreator 2017-02-22T16:06:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IHMdeporte2
TEMPLATE = app

QT += widgets
QT += gui
QT += core

#CONFIG += qwt

#INCLUDEPATH += D:/Qwt/qwt-6.1.3/qwt-6.1.3/include/

SOURCES += main.cpp\
        ihmdeportee.cpp

HEADERS  += ihmdeportee.h

FORMS    += ihmdeportee.ui

CONFIG += mobility
MOBILITY = location







