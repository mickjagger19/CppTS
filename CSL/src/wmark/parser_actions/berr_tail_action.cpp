/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "berr_tail_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserBerrTailAction

WmarkParserBerrTailAction::WmarkParserBerrTailAction() noexcept : m_pData(nullptr)
{
}
WmarkParserBerrTailAction::~WmarkParserBerrTailAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserBerrTailAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserBerrTailAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//up
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaAstNodeInfo info;
	m_pData->spMeta->GetAstNodeInfo(m_pData->posParent, info);
	m_pData->posCurrent = m_pData->posParent;
	m_pData->posParent = info.posParent;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
