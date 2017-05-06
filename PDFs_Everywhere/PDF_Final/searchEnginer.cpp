#include "searchEngine.h"

DocumentParser::DocumentParser()
{
}

void DocumentParser::parse(const char* stopList, const char* pathName)
{
    docParse.stopWords(stopList, pathName);
}

void DocumentParser::createPdf()
{
    PdfStreamedDocument document("trythis.pdf");
    PdfPainter painter;
    PdfPage* pPage;

    pPage = document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4));
    painter.SetPage( pPage);
    const PdfEncoding* pEncoding = new PdfIdentityEncoding();
    PdfFont *pFont = document.CreateFont("TimesNewRoman", false, false, pEncoding);\
    PdfString pString("Words one. WORDS TWO. words three.");
    painter.SetFont(pFont);
    painter.DrawText(100.0, pPage->GetPageSize().GetHeight()-100.0,pString);
    painter.FinishPage();
    document.Close();
}

void DocumentParser::findFiles(string wordOne, string  wordTwo)
{
    /*if (invertedIndex.searchHead(wordOne) == true)
    {
        invertedIndex.printInnerData(wordOne);
    }
    else
    {
        cout << "ERROR: The word " << wordOne << " not found" << endl;
    }
    if (invertedIndex.searchHead(wordTwo) == true)
    {
        invertedIndex.printInnerData(wordTwo);
    }
    else
    {
        cout << "ERROR: The word " << wordTwo << " not found" << endl;
    }*/
}
