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
    stopwords.cpp \
    textextractor.cpp \
    murmurhash2.cpp \
    hasht.cpp

HEADERS += \
    catch.hpp \
    documentparser.h \
    stopwords.h \
    avltree.h \
    myadjacencylist.h \
    mylinkedlist.h \
    textextractor.h \
    avltreelayered.h \
    murmurhash2.h \
    hashtable.h \
    hasht.h
