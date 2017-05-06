#include "documentparser.h"

DocumentParser::DocumentParser()
{
}

void DocumentParser::stopWords(const char* fileName)
{
    fileIn.open(fileName, ios::in);
    {
        if (!fileIn)
        {
            cout << fileName << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
        string word;
        fileIn >> word;
        while (!fileIn.eof())
        {
            stopWordsList.insert(word);
            fileIn >> word;
        }
    }
    cout << "stopWords list created" << endl;
    fileIn.close();
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

void DocumentParser::openPdf(const char * fileIn)
{
    try
    {
        docParse.Init(fileIn, stopWordsList);

        /*PdfMemDocument pdf(fileIn);
        //cout << "File Open: " << fileIn << endl;
        //cout <<  "Page Count: " << pdf.GetPageCount() << endl;
        for (int pNum = 0; pNum < pdf.GetPageCount(); pNum++)
        {
            PdfPage* page = pdf.GetPage(pNum);
            PdfContentsTokenizer tok(page);
            const char* token = nullptr;
            PdfVariant var; // var is a variant type that supports all data types supported by PDFs
            EPdfContentsType type;

            while (tok.ReadNext(type, token, var) ==  true)
            {
                if (type == ePdfContentsType_Keyword)
                {
                    // NOTE: repeating phrases are at the end -> footnotes
                    // was told to ignore that error

                    if(var.IsArray())
                    {
                        PdfArray& arr = var.GetArray();
                        for (unsigned int i = 0; i< arr.GetSize(); ++i)
                        {
                            if (arr[i].IsString())
                            {
                                PdfString pdfS = arr[i].GetString();
                                string regS = pdfS.GetString();
                                string file = fileIn;
                                if (stopWordsList.find(regS) ==  false)
                                {
                                    invertedIndex.insert(regS, file);

                                }
                                cout << regS << " ";
                            }
                        }
                    }
                    if(var.IsString())
                    {
                        PdfString pdfS = var.GetString();
                        string regS = pdfS.GetString();
                        if (stopWordsList.find(regS) ==  false)
                        {
                            invertedIndex.insert(regS, fileIn);
                        }
                        cout << regS << " ";
                    }
                }
            }
        }
        //cout << endl << endl << endl << endl;   // separate file entries*/

    }
    catch (const PdfError& e)
    {
        cout << "File: '" << fileIn << "' not supported" <<  endl;//<< endl << endl;
    }
}

void DocumentParser::throughDirectory(const char* dirIn)
{
    struct dirent *pointDirent;
    DIR *pointDir;
    int count = 0;

    cout << "Following path: " << dirIn << endl;

    pointDir = opendir (dirIn);
    if (pointDir == NULL)
    {
        cout << "Cannot open directory located at: " << dirIn << endl;
    }
    while ((pointDirent = readdir(pointDir)) != NULL)
    {
        const char* file = pointDirent->d_name;
        cout << count << " " << file << endl;
        count++;
        openPdf(pointDirent->d_name);
    }
    closedir (pointDir);
    string wordOne = "variable ";
    string wordTwo = "banana ";
    findFiles(wordOne, wordTwo);
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
