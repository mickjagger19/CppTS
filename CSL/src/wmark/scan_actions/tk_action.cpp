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
	
	if (codeType == CODE_OPEN) {
		stk.push(WMARK_SCANNER_CODETEXT_ACTION);
		codeType = CODE_CLOSE;
		return true;
	}
	
	//$
	if( ch == '$' ) {
		isAsciiMath = !isAsciiMath;
		token.uID = WMARK_TK_MATH;
		return true;
	}
	
	if ( isAsciiMath ){
		token.strToken.clear();
		stm.unget();
		stk.push(WMARK_SCANNER_MATH_ACTION);
		return true;
	}
	
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

    //`
    if (ch == '`') {
        stm.get(ch);
        if (stm.eof()) {
            token.uID = WMARK_TK_CODEINLINE;
            return true;
        }
        if (ch == '`') {
            if (stm.eof()) {
                stm.unget();
                token.uID = WMARK_TK_CODEINLINE;
                return true;
            }
            stm.get(ch);
            if (ch == '`') {
                token.uID = WMARK_TK_CODEINPARAGRAPH;
                if (codeType == NON_CODE)
                    codeType = CODE_OPEN;
                else if (codeType == CODE_CLOSE)
                    codeType = NON_CODE;
                return true;
            }
            stm.unget();
        }
        if (codeType == NON_CODE)
            codeType = CODE_OPEN;
        else if (codeType == CODE_CLOSE)
            codeType = NON_CODE;
        stm.unget();
        token.uID = WMARK_TK_CODEINLINE;
        return true;
    }

    //$
    if( ch == '$') {
    	token.uID = WMARK_TK_MATH;
	    if (codeType == NON_CODE)
		    codeType = CODE_OPEN;
	    else if (codeType == CODE_CLOSE)
		    codeType = NON_CODE;
    	return true;
    }
    
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

	if ( ch == '-' || ch == '+' ){
	    if (stm.eof()){
            token.uID = WMARK_TK_TEXT;
            return true;
	    }
	    stm.get(ch);
	    if ( ch == ' ' ){
	        token.uID = WMARK_TK_ULI;
	        return true;
	    }
	    stm.unget();
        stk.push(WMARK_SCANNER_TEXT_ACTION);
        return true;
	}

    //*
    if ( ch == '*' ) {
        stm.get(ch);
        if (stm.eof()) {
            token.uID = WMARK_TK_ITALIC;
            return true;
        }
        if (!stm.good()) {
            return false;
        }
        if ( ch == '*' ){
            token.uID = WMARK_TK_BOLD;
            return true;
        }
        else if ( ch == ' ' && !isItalic ){
            token.uID = WMARK_TK_ULI;
            return true;
        } else {
            stm.unget();
            isItalic = !isItalic;
            token.uID = WMARK_TK_ITALIC;
            return true;
        }
    }

    if( ch == '!' ) {
        stk.push(WMARK_SCANNER_IMAGE_ACTION);
        return true;
	}

	//number
	if( ch >= '0' && ch <= '9' ){
	    stm.unget();
        stk.push(WMARK_SCANNER_OL_ACTION);
        return true;
	}
	//others
	stk.push(WMARK_SCANNER_TEXT_ACTION);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
