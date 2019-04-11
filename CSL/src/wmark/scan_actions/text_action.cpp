/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../WmarkIDs.h"

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
bool WmarkScannerTextAction::Scan(std::istream& stm, RdActionStack& stk, uint32_t& uID, std::string& strToken)
{
	do {
		//get a character
		char ch;
		stm.get(ch);
		if( stm.eof() ) {
			uID = WMARK_TK_TEXT;
			return true;
		}
		if( !stm.good() )
			return false;

		if( ch == '\r' || ch == '\n' ) {
			stm.unget();
			break;
		}

		strToken += ch;
	} while( true );

	uID = WMARK_TK_TEXT;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
