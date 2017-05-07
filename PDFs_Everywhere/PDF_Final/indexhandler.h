#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <fstream>
#include <iostream>
#include "avltreelayered.h"
#include <vector>
#include <utility>

class indexHandler
{
public:
    indexHandler();

    void createIndex(avlTreeLayered<string> invertedIndexT, string indexFile, int pageCount);
    void searchStats(const char*);
    void intoAVL(const char*);
private:
    fstream fileInOut;
    avlTreeLayered<string> indexAVL;

};

#endif // INDEXHANDLER_H
