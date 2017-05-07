#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <iostream>
#include <podofo.h>
#include <string>

#include "avltree.h"
#include "textextractor.h"

#include <mylinkedlist.h>
#include <myadjacencylist.h>

#include "indexhandler.h"

using namespace PoDoFo;
using namespace std;

class searchEngine
{
public:
    searchEngine();
    void parse(const char*, const char*, const char*);   // begins parsing process
    void searchStats(const char*);

private:
    TextExtractor docParse;
    indexHandler iHandle;
};

#endif // SEARCH_ENGINE_H
