#-------------------------------------------------
#
# Project created by QtCreator 2015-09-30T22:45:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MarioProject
TEMPLATE = app
QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS +=  -std=c++11

RESOURCES += mario.qrc


SOURCES += main.cpp \
    gameboard.cpp \
    brick.cpp \
    floor.cpp \
    safe.cpp \
    mario.cpp \
    person.cpp \
    model.cpp \
    splashscreen.cpp \
    header.cpp \
    background.cpp \
    mushroom.cpp \
    gold.cpp \
    darkeater.cpp

HEADERS  += gameboard.h \
    brick.h \
    floor.h \
    safe.h \
    mario.h \
    person.h \
    model.h \
    splashscreen.h \
    header.h \
    background.h \
    mushroom.h \
    gold.h \
    darkeater.h

DISTFILES +=
