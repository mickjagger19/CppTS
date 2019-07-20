/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../WmarkDef.h"

#include "tk_text_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkTextAction

WmarkParserTkTextAction::WmarkParserTkTextAction() noexcept : m_pData(nullptr)
{
}
WmarkParserTkTextAction::~WmarkParserTkTextAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkTextAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkTextAction::DoAction(std::vector<std::string>& vecError)
{
	//text
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaDataPosition pos = m_pData->spMeta->InsertAstNode(WMARK_NODETYPE_TEXT);
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 )
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
	m_pData->posCurrent = pos;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
