#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <fstream>
#include <iostream>
#include <algorithm>
#include "avltreelayered.h"
#include <vector>
#include <utility>
#include "textextractor.h"

class indexHandler
{
public:
    indexHandler();

    void createIndex(avlTreeLayered<string> invertedIndexT, string indexFile, int pageCount);
    void searchStats(const char*);
    void intoAVL(const char*);
    void searchAVL(string, const char*, const char*);
private:
    fstream fileInOut;
    avlTreeLayered<string> indexAVL;
};

#endif // INDEXHANDLER_H
