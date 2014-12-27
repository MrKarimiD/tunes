#-------------------------------------------------
#
# Project created by QtCreator 2014-12-27T23:09:04
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = secondPhase
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    album_db.cpp \
    album.cpp \
    person.cpp \
    purchase_list.cpp \
    purchase.cpp \
    track.cpp \
    staff.cpp \
    customer.cpp \
    person_db.cpp

OTHER_FILES += \
    albums.txt \
    staff.txt

HEADERS += \
    album_db.h \
    album.h \
    person.h \
    purchase_list.h \
    purchase.h \
    track.h \
    staff.h \
    customer.h \
    person_db.h
