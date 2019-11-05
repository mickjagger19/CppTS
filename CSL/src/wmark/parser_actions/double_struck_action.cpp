/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "double_struck_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserDoubleStruckAction

WmarkParserDoubleStruckAction::WmarkParserDoubleStruckAction() noexcept
{
}
WmarkParserDoubleStruckAction::~WmarkParserDoubleStruckAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserDoubleStruckAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserDoubleStruckAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//DoubleStruck
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_DOUBLE_STRUCK);
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 )
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
    down(pos);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
