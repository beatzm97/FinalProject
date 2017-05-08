#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H

#include <fstream>
#include <iostream>
#include <algorithm>
#include "avltreelayered.h"
#include "htable.h"
#include <vector>
#include <utility>
#include "textextractor.h"

class indexHandler
{
public:
    indexHandler();

    void createIndex(avlTreeLayered<string>&, string, int);
    void searchStats(const char*);
    void intoAVL(const char*);
    void searchAVL(string, const char*, const char*, const char*);
    void searchHash(string, const char*, const char*, const char*);
private:
    void outputDoc(vector<string>, const char*);
    fstream fileInOut;
    avlTreeLayered<string> indexAVL;
    hTable indexHash;
};

#endif // INDEXHANDLER_H
