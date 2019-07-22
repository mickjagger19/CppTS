/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "WmarkScanner.h"

#include "base/WmarkDef.h"

#include "scan_actions/tk_action.h"
#include "scan_actions/comment_action.h"
#include "scan_actions/text_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerHelper

void WmarkScannerHelper::CreateActions(std::shared_ptr<IRdScannerAction>& spTkAction,
									std::shared_ptr<IRdScannerAction>& spCommentAction,
									std::shared_ptr<IRdScannerAction>& spTextAction)
{
	spTkAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerTkAction>(std::make_shared<WmarkScannerTkAction>());
	spCommentAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerCommentAction>(std::make_shared<WmarkScannerCommentAction>());
	spTextAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerTextAction>(std::make_shared<WmarkScannerTextAction>());
}

void WmarkScannerHelper::SetActions(RdScanner& rds,
									const std::shared_ptr<IRdScannerAction>& spTkAction,
									const std::shared_ptr<IRdScannerAction>& spCommentAction,
									const std::shared_ptr<IRdScannerAction>& spTextAction)
{
	rds.ClearActions();
	//add
	rds.AddAction(WMARK_SCANNER_TK_ACTION, spTkAction);
	rds.AddAction(WMARK_SCANNER_COMMENT_ACTION, spCommentAction);
	rds.AddAction(WMARK_SCANNER_TEXT_ACTION, spTextAction);
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
