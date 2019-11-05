/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerTkAction

WmarkScannerTkAction::WmarkScannerTkAction() throw()
{
}
WmarkScannerTkAction::~WmarkScannerTkAction() throw()
{
}

// IRdScannerAction
bool WmarkScannerTkAction::Scan(std::istream& stm, RdActionStack& stk, RdToken& token)
{
	//get a character
	char ch;
	stm.get(ch);
	if( stm.eof() ) {
		token.uID = TK_END_OF_EVENT;
		return true;
	}
	if( !stm.good() )
		return false;
	token.strToken += ch;

	//return
	if( ch == '\n' ) {
		token.uID = WMARK_TK_RETURN;
		token.infoEnd.uRow ++;
		token.infoEnd.uCol = 0;
		return true;
	}
	if( ch == '\r' ) {
		stm.get(ch);
		if( stm.eof() ) {
			token.uID = WMARK_TK_RETURN;
			token.infoEnd.uRow ++;
			token.infoEnd.uCol = 0;
			return true;
		}
		if( !stm.good() )
			return false;
		token.infoEnd.uRow ++;
		token.infoEnd.uCol = 0;
		if( ch == '\n' ) {
			token.strToken += ch;
			token.uID = WMARK_TK_RETURN;
			return true;
		}
		stm.unget();
		token.uID = WMARK_TK_RETURN;
		return true;
	}

	token.infoEnd.uCol ++;

	//indent
	if( ch == '\t' ) {
		token.uID = WMARK_TK_INDENT;
		return true;
	}

	//heading
	if ( ch == '#' ){
        int heading_level = 1;
        do { // get heading level
            stm.get(ch);
            if (!stm.good())
                return false;
            token.strToken += ch;
            token.infoEnd.uCol++;
            if (ch == '#' && (heading_level + 1 <= MAX_HEADING_LEVEL)) {
                heading_level ++;
            } else if (ch == ' ') break;
            else {  // '#' can only be followed by itself or space
                stk.push(WMARK_SCANNER_TEXT_ACTION);
                return true;
            }
        } while (true);

        token.uID = WMARK_TK_HEADING;
        return true;
	}

	//<
	if( ch == '<' ) {
		stk.push(WMARK_SCANNER_COMMENT_ACTION);
		return true;
	}

	//others
	stk.push(WMARK_SCANNER_TEXT_ACTION);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
