/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "text_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerTextAction

WmarkScannerTextAction::WmarkScannerTextAction() throw()
{
}
WmarkScannerTextAction::~WmarkScannerTextAction() throw()
{
}

// IRdScannerAction
bool WmarkScannerTextAction::Scan(std::istream& stm, RdActionStack& stk, RdToken& token)
{
	do {
		//get a character
		char ch;
		stm.get(ch);
		if( stm.eof() ) {
			token.uID = WMARK_TK_TEXT;
			return true;
		}
		if( !stm.good() )
			return false;

		if( ch == '\r' || ch == '\n' ) {
			stm.unget();
			break;
		}

		token.strToken += ch;
		token.infoEnd.uCol ++;
	} while( true );

	token.uID = WMARK_TK_TEXT;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
