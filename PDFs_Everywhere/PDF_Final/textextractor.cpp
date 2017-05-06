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

void TextExtractor::Init( const char* pszInput, avlTree<string> stopWordsList)
{
    if( !pszInput )
    {
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    PdfMemDocument document( pszInput );

    int nCount = document.GetPageCount();
    for( int i=0; i<nCount; i++ )
    {
        PdfPage* pPage = document.GetPage( i );

        this->ExtractText( &document, pPage, stopWordsList );
    }
}

void TextExtractor::ExtractText( PdfMemDocument* pDocument, PdfPage* pPage, avlTree<string> stopWordsList)
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
                if( !bTextBlock )
                    fprintf( stderr, "WARNING: Found ET without BT!\n" );
            }

            if( bTextBlock )
            {
                if( strcmp( pszToken, "Tf" ) == 0 )
                {
                    stack.pop();
                    PdfName fontName = stack.top().GetName();
                    PdfObject* pFont = pPage->GetFromResources( PdfName("Font"), fontName );
                    if( !pFont )
                    {
                        PODOFO_RAISE_ERROR_INFO( ePdfError_InvalidHandle, "Cannot create font!" );
                    }

                    pCurFont = pDocument->GetFont( pFont );
                    if( !pCurFont )
                    {
                        fprintf( stderr, "WARNING: Unable to create font for object %i %i R\n",
                                 pFont->Reference().ObjectNumber(),
                                 pFont->Reference().GenerationNumber() );
                    }
                }
                else if( strcmp( pszToken, "Tj" ) == 0 ||
                         strcmp( pszToken, "'" ) == 0 )
                {
                    AddTextElement(pCurFont, stack.top().GetString(), stopWordsList);
                    stack.pop();
                }
                else if( strcmp( pszToken, "\"" ) == 0 )
                {
                    AddTextElement(pCurFont, stack.top().GetString(), stopWordsList);
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
                            if (array[i].GetString() != " " && array[i].GetString() != "," && array[i].GetString() != "."
                                    && array[i].GetString() != "\n")
                            {
                                PdfString tempPdf = array[i].GetString();
                                std:: string temp = tempPdf.GetString();
                                buffer.append(temp);
                            }
                            else
                            {
                                AddTextElement(pCurFont, buffer, stopWordsList);
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

void TextExtractor::AddTextElement(PdfFont* pCurFont, const PdfString & rString,  avlTree<string> stopWordsList)
{
    if( !pCurFont )
    {
        fprintf( stderr, "WARNING: Found text but do not have a current font: %s\n", rString.GetString() );
        return;
    }

    if( !pCurFont->GetEncoding() )
    {
        fprintf( stderr, "WARNING: Found text but do not have a current encoding: %s\n", rString.GetString() );
        return;
    }

    // For now just write to console
    PdfString unicode = pCurFont->GetEncoding()->ConvertToUnicode( rString, pCurFont );
    const char* pszData = unicode.GetStringUtf8().c_str();
    while( *pszData ) {
        //printf("%02x", static_cast<unsigned char>(*pszData) );
        ++pszData;
    }
    //std:: cout << *pszData << endl;
//    printf("%s \n", unicode.GetStringUtf8().c_str() );
    //printf("w: %s \n", rString.GetString());
    std::cout << rString.GetString() << endl;

    /*if (stopWordsList.find(rString.GetString()) == false)
    {

    }*/
}
