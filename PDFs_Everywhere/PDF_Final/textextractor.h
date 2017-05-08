#ifndef _TEXT_EXTRACTOR_H_
#define _TEXT_EXTRACTOR_H_

#include <podofo.h>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include "avltree.h"
#include <iostream>
#include <stack>
#include <string.h>
#include <string>
#include "porter2_stemmer.h"
#include "avltreelayered.h"
#include <dirent.h>
#include "indexhandler.h"
#include <fstream>
#include <unistd.h>

using namespace PoDoFo;

#ifndef MAX_PATH
#define MAX_PATH 512
#endif // MAX_PATH

/** This class uses the PoDoFo lib to parse
 *  a PDF file and to write all text it finds
 *  in this PDF document to stdout.
 */
class TextExtractor {
 public:
    TextExtractor();
    virtual ~TextExtractor();

    void stopWords(const char*, const char*, const char*);   // creates stopWordsList
    string filter(string, const char*);
    void documentContents(string, const char*);

    void appendIndex(string, const char*, const char*, const char*);


 private:
    bool traverse;
    bool complete = true;
    int pageCount = 0;
    string currentFile;
    string indexFile;
    avlTreeLayered<string> invertedIndexTree;
    avlTree<string> stopWordsList;
    fstream fileInOut;

    /** Traverse through the provided directory, so that each file
     * will be parsed through, filtered, and added to the chosen structure
     *
     * \param pathIn given path holding all the documents of interest
     */
    void throughDirectory(const char*); // traverses through a directory, extracts file names, passes to openPdf

    /** Receives a file name and calls another function
     * to extract the text from the pdf
     * \param pszInput file name, pdf that will be parsed through
     */
    void Init( const char* pszInput);

    /** Extract all text from the given page
     *
     *  \param pDocument the owning document
     *  \param pPage extract the text of this page.
     */
    void ExtractText( PdfMemDocument* pDocument, PdfPage* pPage);

    /** Adds a text string to a list which can be sorted by
     *  position on the page later, so that the whole structure
     *  of the text including formatting can be reconstructed.
     *
     *  \param dCurPosX x position of the text
     *  \param dCurPosY y position of the text
     *  \param pCurFont font of the text
     *  \param rString the actual string
     */
    void AddTextElement(PdfFont* pCurFont, const PdfString & rString);
};

#endif // _TEXT_EXTRACTOR_H_
