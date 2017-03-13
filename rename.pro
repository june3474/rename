#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T14:09:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rename
TEMPLATE = app


SOURCES += main.cpp\
        rename.cpp \
    regexdelegate.cpp \
    progress.cpp \
    mylineedit.cpp

HEADERS  += rename.h \
    regexdelegate.h \
    progress.h \
    mylineedit.h

FORMS    += rename.ui \
    progress.ui

RESOURCES +=

DISTFILES += \
    resources/images/arrow.png \
    resources/images/folder.png
