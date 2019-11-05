/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_code_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkCodeAction

WmarkParserTkCodeAction::WmarkParserTkCodeAction() noexcept
{
}
WmarkParserTkCodeAction::~WmarkParserTkCodeAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkCodeAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkCodeAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//Code
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_CODE);
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
    if (m_pData->posCurrent.uAddress == 0) { // the first allocated node
        m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
    } else
        m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);

	down(pos);
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
