#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <iostream>
#include <podofo.h>
#include <string>

#include "textextractor.h"
#include "indexhandler.h"
#include "queryprocessor.h"
#include "maintenancemode.h"



using namespace PoDoFo;
using namespace std;

class searchEngine
{
public:
    searchEngine(const char*, const char*, const char*);
    void parse(const char*, const char*, const char*);   // begins parsing process

private:
    void qMode(const char*, const char*, const char*);
    void mMode(const char*, const char*, const char*);
};

#endif // SEARCH_ENGINE_H
