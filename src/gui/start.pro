QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = start

SOURCES += start.cpp  main.cpp ../chess.cpp

HEADERS  += start.h  ../chess.h  ../user.h

FORMS    += start.ui

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
