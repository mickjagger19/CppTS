﻿/*
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

WmarkParserBlockElementAction::WmarkParserBlockElementAction() noexcept
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
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_PARAGRAPH);
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 ) // to link the child with parent
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else // to link the children together
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
    down(pos);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
