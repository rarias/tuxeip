#-------------------------------------------------
#
# Project created by QtCreator 2013-09-04T11:30:21
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = tux_sqlite
TEMPLATE = lib

DEFINES += TUX_SQLITE_LIBRARY

SOURCES += tux_sqlite.cpp

HEADERS += tux_sqlite.h\
        tux_sqlite_global.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

#!macx {
#unix:LIBS          += /usr/lib/libpvsmt.so -lpthread
#unix:INCLUDEPATH   += /opt/pvb/pvserver
#}

#macx:LIBS          += /opt/pvb/pvserver/libpvsmt.a /usr/lib/libpthread.dylib
#macx:INCLUDEPATH   += /opt/pvb/pvserver

#win32-g++ {
#QMAKE_LFLAGS       += -static-libgcc
#win32:INCLUDEPATH  += $(PVBDIR)/pvserver
#}
#else {
#win32:INCLUDEPATH  += $(PVBDIR)/pvserver
#}
