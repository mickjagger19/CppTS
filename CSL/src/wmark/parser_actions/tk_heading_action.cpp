/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_heading_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkHeadingAction

WmarkParserTkHeadingAction::WmarkParserTkHeadingAction() noexcept
{
}
WmarkParserTkHeadingAction::~WmarkParserTkHeadingAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkHeadingAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkHeadingAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//Heading
	assert( m_pData->posParent.uAddress != 0 );
    //string
    size_t uSize = strToken.length();
    if (uSize >= (size_t) (std::numeric_limits<uint32_t>::max()))
        return false;
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_HEADING);
    RdMetaDataPosition posData = m_pData->spMeta->InsertData((uint32_t) uSize + 1);
    char *szData = (char *) m_pData->spMeta->GetData(posData);
    ::memcpy(szData, strToken.c_str(), uSize);
    szData[uSize] = '\0';
    //data
    m_pData->spMeta->SetAstData(pos, posData);
    //link
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
