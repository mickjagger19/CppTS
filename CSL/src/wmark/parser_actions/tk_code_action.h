﻿/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __TK_CODE_ACTION_H__
#define __TK_CODE_ACTION_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkCodeAction

class WmarkParserTkCodeAction : public IRdParserAction
{
public:
	WmarkParserTkCodeAction() noexcept;
	~WmarkParserTkCodeAction() noexcept;

// IRdParserAction methods
	virtual void SetParameter(const std::any& param);
	virtual bool DoAction(const std::string& strToken, std::vector<std::string>& vecError);
	
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
