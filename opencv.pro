QT += core
QT -= gui

CONFIG += c++11

LIBS += `pkg-config opencv --libs`

TARGET = opencv
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
