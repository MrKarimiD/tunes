#-------------------------------------------------
#
# Project created by QtCreator 2014-12-26T06:33:52
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tunes
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    track.cpp \
    album.cpp \
    person.cpp \
    album_db.cpp

HEADERS += \
    track.h \
    album.h \
    person.h \
    album_db.h
