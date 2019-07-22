/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "block_element_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserBlockElementAction

WmarkParserBlockElementAction::WmarkParserBlockElementAction() noexcept : m_pData(nullptr)
{
}
WmarkParserBlockElementAction::~WmarkParserBlockElementAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserBlockElementAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserBlockElementAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//paragraph
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaDataPosition pos = m_pData->spMeta->InsertAstNode(WMARK_NODETYPE_PARAGRAPH);
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 )
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
	//sub tree
	m_pData->posParent = pos;
	m_pData->posCurrent.uAddress = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
