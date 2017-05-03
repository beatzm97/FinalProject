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
#include <iostream>
using namespace std;
#include <string>
#include <stack>

TextExtractor::TextExtractor()
{

}

TextExtractor::~TextExtractor()
{
}

void TextExtractor::Init( const char* pszInput )
{
    if( !pszInput )
    {
        PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
    }

    PdfMemDocument document( pszInput );    // opening file

    int nCount = document.GetPageCount();   // getting page count
    for( int i=0; i<nCount; i++ )   // will perform loop for each page
    {
        PdfPage* pPage = document.GetPage( i ); // pointer to page

        this->ExtractText( &document, pPage );  // function call
    }
}

void TextExtractor::ExtractText( PdfMemDocument* pDocument, PdfPage* pPage )
{
    // pDocument = pointer to document  // pPage pointer to page
    const char*      pszToken = nullptr;   // token is nullptr
    PdfVariant       var;   // variant is not initialized
    EPdfContentsType eType; // contentType is not initialized

    PdfContentsTokenizer tokenizer( pPage );    // tokenizer for page

    double dCurPosX     = 0.0;  // xposition
    double dCurPosY     = 0.0;  // ypositiion
    bool   bTextBlock   = false;    // boolean set to false
    PdfFont* pCurFont   = nullptr; // pdfFont is nullptr

    std::stack<PdfVariant> stack;   // stack

    // will read the type, token, and variant of the next object in pdf
    // for whole page until there are no more objects left on the page
    while( tokenizer.ReadNext( eType, pszToken, var ) )
    {
        // if recognized as a valid content type
        if( eType == ePdfContentsType_Keyword )
        {
            // should not worry about these
            // support 'l' and 'm' tokens
            if( strcmp( pszToken, "l" ) == 0 ||
                strcmp( pszToken, "m" ) == 0 )
            {
                dCurPosX = stack.top().GetReal();
                stack.pop();
                dCurPosY = stack.top().GetReal();
                stack.pop();
            }
            // beginning of text stream
            else if( strcmp( pszToken, "BT" ) == 0 )
            {
                cout << pszToken << " ";
                bTextBlock   = true;    // bool = true bc text
                // BT does not reset font
                // pCurFont     = NULL;
            }
            // end of text stream
            else if( strcmp( pszToken, "ET" ) == 0 )
            {
                // error if found first, if bool not set to true when found
                cout << pszToken << " ";
                if( !bTextBlock )
                    fprintf( stderr, "WARNING: Found ET without BT!\n" );
            }

            if( bTextBlock )
            {
                // font pdf token, dont really need
                if( strcmp( pszToken, "Tf" ) == 0 )
                {
                    cout << pszToken << " ";
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
                // strings!
                else if( strcmp( pszToken, "Tj" ) == 0 ||
                         strcmp( pszToken, "'" ) == 0 )
                {
                    cout << pszToken << " ";
                    //AddTextElement( dCurPosX, dCurPosY, pCurFont, stack.top().GetString() );
                    //stack.pop();
                }
                // line break
                else if( strcmp( pszToken, "\"" ) == 0 )
                {
                    cout << pszToken << " ";
                    //AddTextElement( dCurPosX, dCurPosY, pCurFont, stack.top().GetString() );
                    //stack.pop();
                    //stack.pop(); // remove char spacing from stack
                    //stack.pop(); // remove word spacing from stack
                }
                // char array
                else if( strcmp( pszToken, "TJ" ) == 0 )
                {
                    cout << pszToken << " ";
                    PdfArray array = stack.top().GetArray();
                    stack.pop();

                    string str1;
                    for( int i=0; i<static_cast<int>(array.GetSize()); i++ )
                    {
                        if( array[i].IsString() || array[i].IsHexString())
                        {
                            PdfString step1 = array[i].GetString();
                            string step2 = step1.GetString();
                            str1.append(step2);
                        }
                    }
                    AddTextElement( dCurPosX, dCurPosY, pCurFont, str1 );
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

void TextExtractor::AddTextElement( double dCurPosX, double dCurPosY,
        PdfFont* pCurFont, const PdfString & rString )
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
    cout << rString.GetString()<< endl;
}
