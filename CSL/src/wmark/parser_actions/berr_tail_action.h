﻿/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __BERR_TAIL_ACTION_H__
#define __BERR_TAIL_ACTION_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserBerrTailAction

class WmarkParserBerrTailAction : public IRdParserAction
{
public:
	WmarkParserBerrTailAction() noexcept;
	~WmarkParserBerrTailAction() noexcept;

// IRdParserAction methods
	virtual void SetParameter(const std::any& param);
	virtual bool DoAction(const std::string& strToken, std::vector<std::string>& vecError);

};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
