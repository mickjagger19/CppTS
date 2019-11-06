/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "image_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerImageAction

WmarkScannerImageAction::WmarkScannerImageAction() throw()
{
}
WmarkScannerImageAction::~WmarkScannerImageAction() throw()
{
}

// IRdScannerAction, the markdown syntax of img is as:
// ![title](link)
bool WmarkScannerImageAction::Scan(std::istream& stm, RdActionStack& stk, RdToken& token)
{
	int iState = 1;
	do {
        //get a character
        char ch;
        stm.get(ch);
        if (stm.eof()) {
            token.uID = WMARK_TK_TEXT;
            token.uID = TK_ERROR;
            return true;
        }
        if (!stm.good())
            return false;

        token.strToken += ch;
        token.infoEnd.uCol++;

        switch (iState) {
            case 1:
                if ( ch != '[' ){
                    stk.push(WMARK_SCANNER_TEXT_ACTION);
                    return true;
                }
                iState = 2;
                break;
            case 2:
                if ( ch != ']' ){ // dealing with title
                    break;
                }
                // ] found
                iState = 3;
                break;
            case 3:
                if ( ch != '(' ){
                    stk.push(WMARK_SCANNER_TEXT_ACTION);
                    return true;
                }
                // ( found
                iState = 4;
                break;
            case 4:
                if (ch != ')') { // dealing with link
                    break;
                }
                // ) found
                iState = 5;
                break;
            default:
                return false;
        }
	} while( iState != 5 );

	//image
	token.uID = WMARK_TK_IMAGE;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
