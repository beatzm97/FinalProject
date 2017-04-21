#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include <podofo.h>
#include <string>
#include <dirent.h>

using namespace PoDoFo;
using namespace std;

class DocumentParser
{
public:
    DocumentParser();
    void createPdf();   // test function // can be removed later
    void openPdf(const char*);  // parse through PDF
    void throughDirectory(const char*); // traverses through a directory, extracts file names, passes to openPdf
private:
};

#endif // DOCUMENTPARSER_H
