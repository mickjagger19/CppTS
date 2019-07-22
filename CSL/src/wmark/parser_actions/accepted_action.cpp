/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "accepted_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserAcceptedAction

WmarkParserAcceptedAction::WmarkParserAcceptedAction() noexcept : m_pData(nullptr)
{
}
WmarkParserAcceptedAction::~WmarkParserAcceptedAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserAcceptedAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserAcceptedAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//symbol
	RdMetaDataPosition pos = m_pData->spMeta->InsertSymbol(WMARK_ROOT_SYMBOL, 0, true);
	RdMetaDataPosition posData = m_pData->spMeta->InsertData(sizeof(RdMetaDataPosition));
	*((RdMetaDataPosition*)(m_pData->spMeta->GetData(posData))) = m_pData->spMeta->GetAstStart();
	m_pData->spMeta->SetData(pos, posData);
	//finish
	m_pData->spMeta->FinishZeroLevel(true);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
