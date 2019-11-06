﻿/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __TK_IMAGE_ACTION_H__
#define __TK_IMAGE_ACTION_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkIndentAction

class WmarkParserImageAction : public IRdParserAction
{
public:
	WmarkParserImageAction() noexcept;
	~WmarkParserImageAction() noexcept;

// IRdParserAction methods
	virtual void SetParameter(const std::any& param);
	virtual bool DoAction(const std::string& strToken, std::vector<std::string>& vecError);

private:
	RdParserActionMetaData* m_pData;
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
