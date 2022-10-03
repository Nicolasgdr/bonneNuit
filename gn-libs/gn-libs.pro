QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/Game.cpp \
    Model/Square.cpp \
    gn-encap/good_night_encap.cpp \
    gn-encap/json_generator.cpp \
    gn-encap/json_interpreter.cpp

HEADERS += \
    Model/Board.h \
    Model/Color.h \
    Model/Game.h \
    Model/Player.hpp \
    Model/Position.hpp \
    Model/Square.h \
    Model/State.h \
    Model/Type.h \
    Model/random.hpp \
    gn-encap/good_night_encap.h \
    gn-encap/json_generator.h \
    gn-encap/json_interpreter.h \
    good_night_lib.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
