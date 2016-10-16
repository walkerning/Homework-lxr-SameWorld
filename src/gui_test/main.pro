QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main

SOURCES += main.cpp

HEADERS  += interface.h

FORMS    += interface.ui

QMAKE_LFLAGS += '-Wl,-rpath,@executable_path'

# build dir
release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
