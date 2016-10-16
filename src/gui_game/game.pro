QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game

SOURCES += game.cpp  main.cpp my_item.cpp

HEADERS  += game.h

FORMS    += game.ui

#QMAKE_CFLAGS += -stdlib=libc++
#CONFIG += stl c++11
QMAKE_LFLAGS += '-Wl,-rpath,@executable_path'

# build dir
release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
