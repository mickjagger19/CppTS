/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "ol_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerOlAction

WmarkScannerOlAction::WmarkScannerOlAction() throw() {
}

WmarkScannerOlAction::~WmarkScannerOlAction() throw() {
}

// IRdScannerAction
bool WmarkScannerOlAction::Scan(std::istream &stm, RdActionStack &stk, RdToken &token) {

    int iState = 1;
    int char_counter = 1;
    do {
        //get a character
        char ch;
        stm.get(ch);
        char_counter++;
        if (stm.eof()) {
            if (iState >= 3){
                token.uID = WMARK_TK_OLI;
            } else {
                while (char_counter-- > 0)
                    stm.unget();
                stk.push(WMARK_SCANNER_TEXT_ACTION);
            }
            return true;
        }
        if (!stm.good())
            return false;

        token.strToken += ch;
        token.infoEnd.uCol++;

        switch (iState) {
            case 1: //numbers
                if (ch == '.') iState = 2;
                else if (ch < '0' || ch > '9') {
                    stk.push(WMARK_SCANNER_TEXT_ACTION);
                    return true;
                }
                break;
            case 2: //.
                if (ch != ' ') {
                    stk.push(WMARK_SCANNER_TEXT_ACTION);
                    return true;
                }
                iState = 3;
                break;
            default:
                return false;
        }

    } while (iState != 3);

    token.uID = WMARK_TK_OLI;
    return true;

}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
