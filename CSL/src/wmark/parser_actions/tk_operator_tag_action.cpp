/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_operator_tag_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkOperatorTagAction

WmarkParserTkOperatorTagAction::WmarkParserTkOperatorTagAction() noexcept
{
}
WmarkParserTkOperatorTagAction::~WmarkParserTkOperatorTagAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkOperatorTagAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkOperatorTagAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//OperatorTag
	assert( m_pData->posParent.uAddress != 0 );
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_TAG);
	
	size_t uSize = strToken.length();
	RdMetaDataPosition posData = m_pData->spMeta->InsertData((uint32_t)uSize + 1);
	char* szData = (char*)m_pData->spMeta->GetData(posData);
	::memcpy(szData, strToken.c_str(), uSize);
	
	//data
	m_pData->spMeta->SetAstData(pos, posData);
	
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
