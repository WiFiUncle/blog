#-------------------------------------------------
#
# Project created by QtCreator 2018-03-07T16:34:39
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jsonDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        mynetworkobject.cpp

HEADERS  += mainwindow.h\
            mynetworkobject.h

FORMS    += mainwindow.ui
