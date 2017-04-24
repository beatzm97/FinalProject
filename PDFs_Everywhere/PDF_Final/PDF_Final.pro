TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += /usr/include/podofo
LIBS  += -L/usr/include/podofo \
    -lpodofo

SOURCES += main.cpp \
    documentparser.cpp \
    tests.cpp \
    stopwords.cpp

HEADERS += \
    catch.hpp \
    documentparser.h \
    myavl_tree.h \
    stopwords.h \
    avltree.h \
    myadjacencylist.h \
    mylinkedlist.h
