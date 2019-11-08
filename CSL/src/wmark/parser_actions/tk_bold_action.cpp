﻿/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_bold_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkBoldAction

WmarkParserTkBoldAction::WmarkParserTkBoldAction() noexcept
{
}
WmarkParserTkBoldAction::~WmarkParserTkBoldAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkBoldAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkBoldAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//Bold
	assert( m_pData->posParent.uAddress != 0 );
    std::cout << "bold" << std::endl;
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_BOLD);
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
