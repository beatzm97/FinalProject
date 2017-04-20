#include "documentparser.h"

DocumentParser::DocumentParser()
{

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
        PdfMemDocument pdf(fileIn);
        cout << "File Open: " << fileIn << endl;
        cout <<  "Page Count: " << pdf.GetPageCount() << endl;
        for (int pn = 0; pn < pdf.GetPageCount(); pn++)
        {
            PdfPage* page = pdf.GetPage(pn);
            PdfContentsTokenizer tok(page);
            const char* token = nullptr;
            PdfVariant var; // var is a variant type that supports all data types supported by PDFs
            EPdfContentsType type;

            while (tok.ReadNext(type, token, var) ==  true)
            {
                if (type == ePdfContentsType_Keyword)
                {
                    //cout << type << endl;
                    //cout <<  token << endl;
                    /*if (var.IsBool())
                    {
                        cout << "boolean" << endl;
                    }
                    if(var.IsNumber())
                    {
                        //cout << "number" << endl;
                        cout << var.GetNumber() << endl;
                    }
                    if (var.IsReal())
                    {
                        cout << "real" << endl;
                        cout << var.GetReal() << endl;
                    }*/
                    /*if (var.IsHexString())
                    {
                        cout << "hexstring" << endl;
                        PdfString s =  var.GetString();
                        string s1 = s.GetString();
                        cout << s1 << endl;
                    }*/
                    /*if (var.IsName())
                    {
                        cout << "name" << endl;
                        PdfName n = var.GetName();
                        string s1 = n.GetEscapedName();
                        cout << s1 << endl;
                    }*/
                    // NOTE: repeating phrases are at the end
                    // meaning at the end of all arrays in the file
                    // end of all the strings in the file
                    // removing a type will still end the file with repeating phrases

                    if(var.IsArray())
                    {
                        PdfArray& a = var.GetArray();
                        for (unsigned int i = 0; i< a.GetSize(); ++i)
                        {
                            if (a[i].IsString())
                            {
                                PdfString s = a[i].GetString();
                                string s1 = s.GetString();
                                cout << s1;
                            }
                        }
                    }
                    if(var.IsString())
                    {
                        PdfString s = var.GetString();
                        string s1 = s.GetString();
                        cout << s1;
                    }
                    /*if(var.IsDictionary())
                    {
                        cout << "dictionary" << endl;
                    }*/
                    /*if (var.IsRawData())
                    {
                        cout << "raw data" << endl;
                        PdfData d = var.GetRawData();
                        string s1 = d.data();
                        cout << s1 << endl;
                    }*/
                    /*if (var.IsNull())
                    {
                        cout << "null" << endl; // makes sense for first input
                    }
                    if (var.IsReference())
                    {
                        cout << "reference" << endl;
                    }*/
                }
            }
            // process type, token and var
        }
        cout << endl << endl << endl << endl;
    }
    catch (const PdfError& e)
    {
        cout << "File: '" << fileIn << "' not supported" <<  endl << endl << endl;
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
        openPdf(file);
    }
    closedir (pointDir);
}
