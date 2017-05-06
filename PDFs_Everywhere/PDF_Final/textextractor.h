#ifndef _TEXT_EXTRACTOR_H_
#define _TEXT_EXTRACTOR_H_

#include <podofo.h>
#include <cstdio>
#include "avltree.h"
#include <iostream>
#include <stack>
#include <string.h>
#include <string>
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

    void Init( const char* pszInput, avlTree<string> stopWordsIn);

 private:
    /** Extract all text from the given page
     *
     *  \param pDocument the owning document
     *  \param pPage extract the text of this page.
     */
    void ExtractText( PdfMemDocument* pDocument, PdfPage* pPage, avlTree<string> stopWordsIn);

    /** Adds a text string to a list which can be sorted by
     *  position on the page later, so that the whole structure
     *  of the text including formatting can be reconstructed.
     *
     *  \param dCurPosX x position of the text
     *  \param dCurPosY y position of the text
     *  \param pCurFont font of the text
     *  \param rString the actual string
     */
    void AddTextElement(PdfFont* pCurFont, const PdfString & rString, avlTree<string> stopWordsIn);
};

#endif // _TEXT_EXTRACTOR_H_
