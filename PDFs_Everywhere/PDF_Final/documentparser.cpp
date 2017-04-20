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
    PdfMemDocument pdf(fileIn);
    cout << "File Open" << endl;
    cout <<  pdf.GetPageCount() << endl;
    for (int pn = 0; pn < pdf.GetPageCount(); pn++)
    {
        PdfPage* page = pdf.GetPage(pn);
        // cout << pdf.GetPage(pn) << endl; // prints address which makes sense
        PdfContentsTokenizer tok(page);
        //cout << "tok will help us read through a pdf file" << endl;
        const char* token = nullptr;
        //cout << "set our token item to nullptr, its not referring to anything" << endl;
        PdfVariant var;
        //cout <<  "var is a variant type that supports all data typees supported by PDF" << endl;
        EPdfContentsType type;
        //cout << "type is either a keyword/variant/ or imagedata" << endl;
        //cout << "keywords: words in doc; variant: parameter for a keyword; imagedata: raw inline image" << endl;


        while (tok.ReadNext(type, token, var) ==  true)
        {
            //cout << "in first if statement" << endl;
            ///cout << "a token was read, false if no more tokens are left to read" << endl;
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
}
