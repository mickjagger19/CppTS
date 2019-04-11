/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../WmarkIDs.h"

#include "comment_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerCommentAction

WmarkScannerCommentAction::WmarkScannerCommentAction() throw()
{
}
WmarkScannerCommentAction::~WmarkScannerCommentAction() throw()
{
}

// IRdScannerAction
bool WmarkScannerCommentAction::Scan(std::istream& stm, RdActionStack& stk, uint32_t& uID, std::string& strToken)
{
	int iState = 1;
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

		strToken += ch;
		switch( iState ) {
		case 1:
			if( ch != '!' ) {
				stk.push(WMARK_SCANNER_TEXT_ACTION);
				return true;
			}
			iState = 2;
			break;
		case 2:
			if( ch != '-' ) {
				stk.push(WMARK_SCANNER_TEXT_ACTION);
				return true;
			}
			iState = 3;
			break;
		case 3:
			if( ch != '-' ) {
				stk.push(WMARK_SCANNER_TEXT_ACTION);
				return true;
			}
			iState = 4;
			break;
		case 4:
			if( ch == '-' )
				iState = 5;
			break;
		case 5:
			if( ch != '-' ) {
				stk.push(WMARK_SCANNER_TEXT_ACTION);
				return true;
			}
			iState = 6;
			break;
		case 6:
			if( ch != '>' ) {
				stk.push(WMARK_SCANNER_TEXT_ACTION);
				return true;
			}
			iState = 7;
			break;
		default:
			return false;
		}
	} while( iState != 7 );

	//comment
	uID = WMARK_TK_COMMENT;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
