#ifndef QUERYPROCESSOR_H
#define QUERYPROCESSOR_H

#include "indexhandler.h"
#include <string>
#include <iostream>

class queryProcessor
{
public:
    queryProcessor(const char*, const char*, const char*);
private:
    indexHandler iHandle;
    void searchStructure(bool, const char*, const char*, const char*);
};

#endif // QUERYPROCESSOR_H
