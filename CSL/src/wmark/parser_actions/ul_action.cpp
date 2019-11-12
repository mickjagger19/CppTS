/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "ul_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserOLAction

WmarkParserULAction::WmarkParserULAction() noexcept
{
}
WmarkParserULAction::~WmarkParserULAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserULAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserULAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//unordered list
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_UL);
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 ) // to link the child with parent
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else // to link the children together
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
	//sub tree
    down(pos);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
