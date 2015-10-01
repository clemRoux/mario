#-------------------------------------------------
#
# Project created by QtCreator 2015-09-30T22:45:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarioProject
TEMPLATE = app

RESOURCES += mario.qrc


SOURCES += main.cpp \
    gameboard.cpp \
    brick.cpp \
    floor.cpp \
    safe.cpp

HEADERS  += gameboard.h \
    brick.h \
    floor.h \
    safe.h
