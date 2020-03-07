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
#include "scan_actions/codetext_action.h"
#include "scan_actions/image_action.h"
#include "scan_actions/ol_action.h"
#include "scan_actions/asciimath_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerHelper

void WmarkScannerHelper::CreateActions(std::shared_ptr<IRdScannerAction>& spTkAction,
									std::shared_ptr<IRdScannerAction>& spCommentAction,
									std::shared_ptr<IRdScannerAction>& spTextAction,
									std::shared_ptr<IRdScannerAction>& spCodeTextAction,
									std::shared_ptr<IRdScannerAction>& spImageAction,
									std::shared_ptr<IRdScannerAction>& spOlAction,
									std::shared_ptr<IRdScannerAction>& spAsciiMathAction)
{
	spTkAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerTkAction>(std::make_shared<WmarkScannerTkAction>());
	spCommentAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerCommentAction>(std::make_shared<WmarkScannerCommentAction>());
	spTextAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerTextAction>(std::make_shared<WmarkScannerTextAction>());
	spCodeTextAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerCodeTextAction>(std::make_shared<WmarkScannerCodeTextAction>());
	spImageAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerImageAction>(std::make_shared<WmarkScannerImageAction>());
	spOlAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerOlAction>(std::make_shared<WmarkScannerOlAction>());
	spAsciiMathAction = std::static_pointer_cast<IRdScannerAction, WmarkScannerAsciiMathAction>(std::make_shared<WmarkScannerAsciiMathAction>());
}

void WmarkScannerHelper::SetActions(RdScanner& rds,
									const std::shared_ptr<IRdScannerAction>& spTkAction,
									const std::shared_ptr<IRdScannerAction>& spCommentAction,
									const std::shared_ptr<IRdScannerAction>& spTextAction,
									const std::shared_ptr<IRdScannerAction>& spCodeTextAction,
									const std::shared_ptr<IRdScannerAction>& spImageAction,
									const std::shared_ptr<IRdScannerAction>& spOlAction,
									const std::shared_ptr<IRdScannerAction>& spAsciiMathAction)
{
	rds.ClearActions();
	//add
	rds.AddAction(WMARK_SCANNER_TK_ACTION, spTkAction);
	rds.AddAction(WMARK_SCANNER_COMMENT_ACTION, spCommentAction);
	rds.AddAction(WMARK_SCANNER_TEXT_ACTION, spTextAction);
	rds.AddAction(WMARK_SCANNER_CODETEXT_ACTION, spCodeTextAction);
	rds.AddAction(WMARK_SCANNER_IMAGE_ACTION, spImageAction);
	rds.AddAction(WMARK_SCANNER_OL_ACTION, spOlAction);
	rds.AddAction(WMARK_SCANNER_MATH_ACTION, spAsciiMathAction);
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
