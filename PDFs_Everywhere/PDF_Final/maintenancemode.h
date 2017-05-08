#ifndef MAINTENANCEMODE_H
#define MAINTENANCEMODE_H

#include <fstream>
#include <iostream>
#include <utility>
#include "textextractor.h"

using namespace std;

class maintenanceMode
{
public:
    maintenanceMode(const char*, const char*, const char*);
private:
    fstream fileInOut;
    void clearIndex(const char*);
    void appendIndex(string, const char*, const char*, const char*);
};

#endif // MAINTENANCEMODE_H
