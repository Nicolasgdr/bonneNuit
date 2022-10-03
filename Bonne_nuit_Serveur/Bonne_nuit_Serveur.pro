QT -= gui
QT += network
QT += core
QT += sql
CONFIG -= app_bundle
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++17


SOURCES += \
    Db.cpp \
    Server.cpp \
    Game_handler.cpp \
    main.cpp \
    Thread_players.cpp

HEADERS += \
    Db.h \
    Server.h \
    Game_handler.h \
    Thread_players.h \




win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../gn-libs/debug/ -lgn-libs
else:win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../gn-libs/release/ -lgn-libs
else:unix: LIBS += -L$$PWD/../gn-libs/ -lgn-libs

INCLUDEPATH += $$PWD/../gn-libs
DEPENDPATH += $$PWD/../gn-libs

win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../gn-libs/debug/libgn-libs.a
else:win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../gn-libs/release/libgn-libs.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../gn-libs/release/gn-libs.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../gn-libs/debug/gn-libs.lib
else:unix: PRE_TARGETDEPS += $$PWD/../gn-libs/libgn-libs.a
