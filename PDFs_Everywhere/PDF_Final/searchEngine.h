#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include <podofo.h>
#include <string>

#include "avltree.h"
#include "textextractor.h"

#include <mylinkedlist.h>
#include <myadjacencylist.h>

using namespace PoDoFo;
using namespace std;

class DocumentParser
{
public:
    DocumentParser();
    void parse(const char*, const char*);   // begins parsing process

    void createPdf();   // test function // can be removed later
    void findFiles(string, string);
private:
    TextExtractor docParse;
};

#endif // DOCUMENTPARSER_H
