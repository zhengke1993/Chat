TEMPLATE = app
TARGET = chatterboxd
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += console

QT += network

HEADERS += ChatterBoxServer.h
SOURCES += ChatterBoxServer.cpp main.cpp
