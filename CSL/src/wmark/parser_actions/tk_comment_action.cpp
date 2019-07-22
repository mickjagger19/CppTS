/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_comment_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkCommentAction

WmarkParserTkCommentAction::WmarkParserTkCommentAction() noexcept : m_pData(nullptr)
{
}
WmarkParserTkCommentAction::~WmarkParserTkCommentAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkCommentAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkCommentAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//comment
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaDataPosition pos = m_pData->spMeta->InsertAstNode(WMARK_NODETYPE_COMMENT);
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
