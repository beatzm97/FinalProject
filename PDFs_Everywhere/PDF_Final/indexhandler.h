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

    void createIndex(avlTreeLayered<string> invertedIndexT, string indexFile);
    void top50Words(const char*);
private:
    fstream fileInOut;

};

#endif // INDEXHANDLER_H
