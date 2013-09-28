#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T16:41:11
#
#-------------------------------------------------
TARGET = debug
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += qt
QT       += core
QT       -= gui
QT       += sql
TEMPLATE = app
TUXEIPSRC_DIR = F:/tamaniadora/tuxeip/tuxeip/src
#c:/tamaniadora/tuxeip/tuxeip/src
TUXEIPLIB_DIR = F:/tamaniadora/tuxeip/tuxeip/release
#c:/tamaniadora/tuxeip/tuxeip/src/release
SQLITESRC_DIR = F:/tamaniadora/tuxeip/tux_sqlite/src
#C:/tamaniadora/tuxeip/sqlite
SQLITELIB_DIR = F:/tamaniadora/tuxeip/tux_sqlite/release
#C:/tamaniadora/tuxeip/sqlite/tux_sqlite/release

SOURCES += main.cpp

win32-g++ {
QMAKE_LFLAGS      += -static-libgcc
win32:INCLUDEPATH += $(PVBDIR)/rllib/lib
win32:LIBS        += $(PVBDIR)/win-mingw/bin/librllib.a
win32:DEFINES     += VALGRING

win32:LIBS        += $$TUXEIPLIB_DIR/libtuxeip.a
win32:INCLUDEPATH += $$TUXEIPSRC_DIR
win32:LIBS	  += $$SQLITELIB_DIR/libtux_sqlite.a
win32:INCLUDEPATH += $$SQLITESRC_DIR
}
