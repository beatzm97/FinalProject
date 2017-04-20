#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include <podofo.h>
#include <string>

using namespace PoDoFo;
using namespace std;

class DocumentParser
{
public:
    DocumentParser();
    void createPdf();
    void openPdf(const char*);
private:
};

#endif // DOCUMENTPARSER_H
