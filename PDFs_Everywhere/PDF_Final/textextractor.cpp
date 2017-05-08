/***************************************************************************
 *   Copyright (C) 2008 by Dominik Seichter                                *
 *   domseichter@web.de                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "textextractor.h"


TextExtractor::TextExtractor()
{

}

TextExtractor::~TextExtractor()
{
}

string TextExtractor::filter(string text, const char* fileName)
{
    string result;

    fileInOut.open(fileName, ios::in);
    {
        if (!fileInOut)
        {
            cout << fileName << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
        string word;
        fileInOut >> word;
        while (!fileInOut.eof())
        {
            stopWordsList.insert(word);
            fileInOut >> word;
        }
    }
    fileInOut.close();

    // cout << text << endl;
    std::remove_copy_if(text.begin(), text.end(),
                            std::back_inserter(result), //Store output
                            std::ptr_fun<int, int>(&std::ispunct)
                           );
    if (result != "\0" && result != "\n" && result != "\t" && result != "\r" && result != "\v" && result != " " && result != "")
    {
        transform(result.begin(), result.end(), result.begin(),::tolower);
        Porter2Stemmer::stem(result);
        if (stopWordsList.find(result) == false)
        {
            return result;
        }
    }
    text.empty();
    return "a";
}

void TextExtractor::stopWords(const char* fileName, const char* pathName, const char* indexFileIn)
{
    indexFile = indexFileIn;
    fileInOut.open(fileName, ios::in);
    {
        if (!fileInOut)
        {
            cout << fileName << " : File did not open" << endl;
            exit (EXIT_FAILURE);
        }
        string word;
        fileInOut >> word;
        while (!fileInOut.eof())
        {
            stopWordsList.insert(word);
            fileInOut >> word;
        }
    }
    fileInOut.close();
    throughDirectory(pathName);
}

void TextExtractor::throughDirectory(const char* dirIn)
{
    int pageCount = 0;

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
        Init(pointDirent->d_name, pageCount);
    }
    closedir (pointDir);
    //persistentIndex
    // create another class for the index handler
    indexHandler iHandle;
    iHandle.createIndex(invertedIndexTree, indexFile, pageCount);

    //string wordOne = "variable ";
    //string wordTwo = "banana ";
    //findFiles(wordOne, wordTwo);
}

void TextExtractor::Init( const char* pszInput, int& pageCount)
{
    try
    {
        PdfMemDocument document( pszInput );
        currentFile = pszInput;

        int nCount = document.GetPageCount();
        pageCount += nCount;
        for( int i=0; i < nCount; i++ )
        {
            PdfPage* pPage = document.GetPage( i );

            this->ExtractText( &document, pPage);
        }
    }
    catch (const PdfError& e)
        {
            cout << "File: '" << pszInput << "' not supported" <<  endl << endl << endl;
        }
}

void TextExtractor::ExtractText( PdfMemDocument* pDocument, PdfPage* pPage)
{
    const char*      pszToken = NULL;
    PdfVariant       var;
    EPdfContentsType eType;

    PdfContentsTokenizer tokenizer( pPage );

    bool   bTextBlock   = false;
    PdfFont* pCurFont   = NULL;

    std::stack<PdfVariant> stack;

    while( tokenizer.ReadNext( eType, pszToken, var ) )
    {
        if( eType == ePdfContentsType_Keyword )
        {
            // support 'l' and 'm' tokens
            if( strcmp( pszToken, "l" ) == 0 ||
                strcmp( pszToken, "m" ) == 0 )
            {

                stack.pop();
                stack.pop();
            }
            else if( strcmp( pszToken, "BT" ) == 0 )
            {
                bTextBlock   = true;
                // BT does not reset font
                // pCurFont     = NULL;
            }
            else if( strcmp( pszToken, "ET" ) == 0 )
            {
                // ignore warning
                //if( !bTextBlock )
                    //fprintf( stderr, "WARNING: Found ET without BT!\n" );
            }

            if( bTextBlock )
            {
                if( strcmp( pszToken, "Tf" ) == 0 )
                {
                    stack.pop();
                    PdfName fontName = stack.top().GetName();
                    PdfObject* pFont = pPage->GetFromResources( PdfName("Font"), fontName );
                    // ignore warning
                    /*if( !pFont )
                    {
                        PODOFO_RAISE_ERROR_INFO( ePdfError_InvalidHandle, "Cannot create font!" );
                    }*/

                    pCurFont = pDocument->GetFont( pFont );
                    // ignore warning
                    /*if( !pCurFont )
                    {
                        fprintf( stderr, "WARNING: Unable to create font for object %i %i R\n",
                                 pFont->Reference().ObjectNumber(),
                                 pFont->Reference().GenerationNumber() );
                    }*/
                }
                else if( strcmp( pszToken, "Tj" ) == 0 ||
                         strcmp( pszToken, "'" ) == 0 )
                {
                    AddTextElement(pCurFont, stack.top().GetString());
                    stack.pop();
                }
                else if( strcmp( pszToken, "\"" ) == 0 )
                {
                    AddTextElement(pCurFont, stack.top().GetString());
                    stack.pop();
                    stack.pop(); // remove char spacing from stack
                    stack.pop(); // remove word spacing from stack
                }
                else if( strcmp( pszToken, "TJ" ) == 0 )
                {
                    PdfArray array = stack.top().GetArray();
                    stack.pop();
                    std::string buffer;

                    for( int i=0; i<static_cast<int>(array.GetSize()); i++ )
                    {
                        if( array[i].IsString())
                        {

                            if (array[i].GetString() != "\0" && array[i].GetString() != "\n" && array[i].GetString() != "\t" && array[i].GetString() != "\r" && array[i].GetString() != "\v" && array[i].GetString() != " " && array[i].GetString() != "")
                            {
                                PdfString tempPdf = array[i].GetString();
                                std:: string temp = tempPdf.GetString();
                                std:: string text;
                                std:: remove_copy_if(temp.begin(), temp.end(),
                                                        std::back_inserter(text), //Store output
                                                        std::ptr_fun<int, int>(&std::ispunct)
                                                       );
                                buffer.append(temp);
                            }
                            else
                            {
                                AddTextElement(pCurFont, buffer);
                                buffer.empty();
                            }

                        }
                    }
                }
            }
        }
        else if ( eType == ePdfContentsType_Variant )
        {
            stack.push( var );
        }
        else
        {
            // Impossible; type must be keyword or variant
            PODOFO_RAISE_ERROR( ePdfError_InternalLogic );
        }
    }
}

void TextExtractor::AddTextElement(PdfFont* pCurFont, const PdfString & rString)
{
    if( !pCurFont )
    {
        // ignore warning
        //fprintf( stderr, "WARNING: Found text but do not have a current font: %s\n", rString.GetString() );
        return;
    }

    if( !pCurFont->GetEncoding() )
    {
        // ignore warning
        //fprintf( stderr, "WARNING: Found text but do not have a current encoding: %s\n", rString.GetString() );
        return;
    }

    // For now just write to console
    PdfString unicode = pCurFont->GetEncoding()->ConvertToUnicode( rString, pCurFont );
    const char* pszData = unicode.GetStringUtf8().c_str();
    while( *pszData )
    {
        ++pszData;
    }
    //printf("%s \n", unicode.GetStringUtf8().c_str() );
    //printf("w: %s \n", rString.GetString());
    // print statement that worked
    //std::cout << rString.GetString() << endl;

    string text =  rString.GetString();
    string result;
    std::remove_copy_if(text.begin(), text.end(),
                            std::back_inserter(result), //Store output
                            std::ptr_fun<int, int>(&std::ispunct)
                           );
    if (result != "\0" && result != "\n" && result != "\t" && result != "\r" && result != "\v" && result != " " && result != "")
    {
        transform(result.begin(), result.end(), result.begin(),::tolower);
        Porter2Stemmer::stem(result);
        if (stopWordsList.find(result) == false)
        {
            invertedIndexTree.insert(result, currentFile);
        }
    }
}
