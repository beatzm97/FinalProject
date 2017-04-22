TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += /usr/include/podofo
LIBS  += -L/usr/include/podofo \
    -lpodofo

SOURCES += main.cpp \
    documentparser.cpp \
    tests.cpp

HEADERS += \
    documentparser.h \
    catch.hpp \
    myavl_tree.h
