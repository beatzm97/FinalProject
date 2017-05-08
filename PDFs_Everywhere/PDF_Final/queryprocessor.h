#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include "indexhandler.h"
#include <string>
#include <fstream>
#include <iostream>

class queryProcessor
{
public:
    queryProcessor(const char*, const char*, const char*);
private:
    indexHandler iHandle;
    fstream fileInOut;
    void searchStructure(bool, const char*, const char*, const char*);
    bool checkFile(const char*);
};

#endif // QUERYPROCESSOR_H
