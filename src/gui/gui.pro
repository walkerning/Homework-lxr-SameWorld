######################################################################
# Automatically generated by qmake (2.01a) ?? 10? 17 20:47:23 2016
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . items
INCLUDEPATH += . items

# Input
HEADERS += game.h \
           game_view.h \
           level.h \
           start.h \
           window.h \
           items/game_item.h \
           items/items.h \
           items/level_item.h \
           ../piece.h \
           ../user.h \
           ../chess.h
FORMS += game.ui level.ui start.ui
SOURCES += game.cpp \
           game_view.cpp \
           level.cpp \
           main.cpp \
           start.cpp \
           window.cpp \
           items/game_item.cpp \
           items/level_item.cpp \
           ../chess.cpp
RESOURCES += game.qrc

# build dir
release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
