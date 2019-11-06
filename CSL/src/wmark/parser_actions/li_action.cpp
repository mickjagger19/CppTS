/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "li_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserOlAction

WmarkParserLIAction::WmarkParserLIAction() noexcept : m_pData(nullptr)
{
}
WmarkParserLIAction::~WmarkParserLIAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserLIAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserLIAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//li
	std::cout << "parser act li" << std::endl;
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_LI);

	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 ) {
        std::cout << "first" << std::endl;
        m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
    }
	else {
        std::cout << "next" << std::endl;
        m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
    }
    m_pData->posParent = pos;
    m_pData->posCurrent.uAddress = 0;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
