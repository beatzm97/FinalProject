TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += /usr/include/podofo
LIBS  += -L/usr/include/podofo \
    -lpodofo

SOURCES += main.cpp \
    tests.cpp \
    stopwords.cpp \
    textextractor.cpp \
    murmurhash2.cpp \
    porter2_stemmer.cpp \
    indexhandler.cpp \
    searchEngine.cpp \
    queryprocessor.cpp \
    maintenancemode.cpp \
    htable.cpp

HEADERS += \
    catch.hpp \
    avltree.h \
    textextractor.h \
    avltreelayered.h \
    murmurhash2.h \
    porter2_stemmer.h \
    string_view.h \
    hash.h \
    searchEngine.h \
    indexhandler.h \
    queryprocessor.h \
    maintenancemode.h \
    htable.h
