/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "WmarkScanner.h"

#include "WmarkIDs.h"

#include "scan_actions/tk_action.h"
#include "scan_actions/comment_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerHelper

void WmarkScannerHelper::Initialize(RdScanner& rds)
{
	rds.ClearActions();
	//add
	rds.AddAction(WMARK_SCANNER_TK_ACTION,
		std::static_pointer_cast<IRdScannerAction, WmarkScannerTkAction>(std::make_shared<WmarkScannerTkAction>())
		);
	rds.AddAction(WMARK_SCANNER_COMMENT_ACTION,
		std::static_pointer_cast<IRdScannerAction, WmarkScannerCommentAction>(std::make_shared<WmarkScannerCommentAction>())
		);
	rds.AddAction(WMARK_SCANNER_TEXT_ACTION,
		std::static_pointer_cast<IRdScannerAction, WmarkScannerTextAction>(std::make_shared<WmarkScannerTextAction>())
		);
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
