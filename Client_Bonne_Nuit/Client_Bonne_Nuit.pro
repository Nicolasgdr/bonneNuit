QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += console c++17



SOURCES += \
        Controller.cpp \
        button_game.cpp \
        good_night_gui.cpp \
        main.cpp \
        welcome_home_page.cpp

HEADERS += \
    Controller.h \
    button_game.h \
    good_night_gui.h \
    welcome_home_page.h

FORMS += \
    good_night_gui.ui \
    welcome_home_page.ui


RESOURCES += \
    bn_img.qrc

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
