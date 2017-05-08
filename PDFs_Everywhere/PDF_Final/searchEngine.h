#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <iostream>
#include <podofo.h>
#include <string>

#include "avltree.h"
#include "avltreelayered.h"
#include "textextractor.h"
#include "indexhandler.h"
#include "queryprocessor.h"

#include <mylinkedlist.h>
#include <myadjacencylist.h>


using namespace PoDoFo;
using namespace std;

class searchEngine
{
public:
    searchEngine(const char*, const char*, const char*);
    void parse(const char*, const char*, const char*);   // begins parsing process
    //void searchStats(const char*);

private:
    void qMode(const char*, const char*, const char*);
    //TextExtractor docParse;
    //indexHandler iHandle;
    avlTreeLayered<string> avlIndex;
    bool preference; // true -> avlTree // false -> hashTable
};

#endif // SEARCH_ENGINE_H
