#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <iostream>
#include <podofo.h>
#include <string>
#include <dirent.h>
#include <fstream>
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

    void stopWords(const char*);   // creates stopWordsList
    void createPdf();   // test function // can be removed later
    void openPdf(const char*);  // parse through PDF
    void throughDirectory(const char*); // traverses through a directory, extracts file names, passes to openPdf
    void findFiles(string, string);
private:
    avlTree<string> stopWordsList;
    fstream fileIn;
    MyAdjacencyList<string> invertedIndex;
    TextExtractor docParse;
};

#endif // DOCUMENTPARSER_H
