#-------------------------------------------------
#
# Project created by QtCreator 2020-06-01T19:16:20
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wisdom
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    form.cpp \
    owner.cpp \
    admin.cpp \
    add.cpp \
    modify.cpp

HEADERS  += widget.h \
    form.h \
    owner.h \
    admin.h \
    add.h \
    modify.h

FORMS    += widget.ui \
    form.ui \
    owner.ui \
    admin.ui \
    add.ui \
    modify.ui

RESOURCES += \
    qrc.qrc \
    qss.qrc

RC_ICONS = system.ico
