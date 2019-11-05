/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "codetext_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerCodeTextAction

WmarkScannerCodeTextAction::WmarkScannerCodeTextAction() throw()
{
}
WmarkScannerCodeTextAction::~WmarkScannerCodeTextAction() throw()
{
}

// IRdScannerAction
bool WmarkScannerCodeTextAction::Scan(std::istream& stm, RdActionStack& stk, RdToken& token)
{
    bool first = true;
	do {
		//get a character
		char ch;
		stm.get(ch);
		if( stm.eof() ) {
			token.uID = WMARK_TK_CODETEXT;
			return true;
		}
		if( !stm.good() )
			return false;

		if (first && (ch == '\r' || ch == '\n')){
            std::cout << ch << std::endl;
            stm.get(ch);
            if (ch == '\n') {
                continue;
            }
            stm.unget();
		    continue; // skip the first return
		}
        if (ch == '`' || ch == '$') {
            stm.unget();
            token.uID = WMARK_TK_CODETEXT;
            return true;
		}


		token.strToken += ch;
		token.infoEnd.uCol ++;
        first = false;
	} while( true );

}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
