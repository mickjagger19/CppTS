/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __WMARK_SCANNER_H__
#define __WMARK_SCANNER_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkScannerHelper

class WmarkScannerHelper
{
public:
	static void CreateActions(std::shared_ptr<IRdScannerAction>& spTkAction,
							std::shared_ptr<IRdScannerAction>& spCommentAction,
							std::shared_ptr<IRdScannerAction>& spTextAction,
							std::shared_ptr<IRdScannerAction>& spCodeTextAction,
							std::shared_ptr<IRdScannerAction>& spImageAction,
	                        std::shared_ptr<IRdScannerAction>& spOlAction,
	                        std::shared_ptr<IRdScannerAction>& spAsciiMathAction);
	static void SetActions(RdScanner& rds,
						const std::shared_ptr<IRdScannerAction>& spTkAction,
						const std::shared_ptr<IRdScannerAction>& spCommentAction,
						const std::shared_ptr<IRdScannerAction>& spTextAction,
						const std::shared_ptr<IRdScannerAction>& spCodeTextAction,
						const std::shared_ptr<IRdScannerAction>& spImageAction,
						const std::shared_ptr<IRdScannerAction>& spOlAction,
						const std::shared_ptr<IRdScannerAction>& spAsciiMathAction);
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
