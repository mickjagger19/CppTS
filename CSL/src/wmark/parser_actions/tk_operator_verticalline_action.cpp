/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_operator_verticalline_action.h"
#include "nt_mo_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkOperatorVerticallineAction

WmarkParserTkOperatorVerticallineAction::WmarkParserTkOperatorVerticallineAction() noexcept
{
}
WmarkParserTkOperatorVerticallineAction::~WmarkParserTkOperatorVerticallineAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkOperatorVerticallineAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkOperatorVerticallineAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//OperatorVerticalline
	
	assert( m_pData->posParent.uAddress != 0 );
	std::string tag = "mo";
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_TAG);
	
	size_t uSize = tag.length();
	RdMetaDataPosition posData = m_pData->spMeta->InsertData((uint32_t)uSize + 1);
	char* szData = (char*)m_pData->spMeta->GetData(posData);
	::memcpy(szData, tag.c_str(), uSize);
	
	//data
	m_pData->spMeta->SetAstData(pos, posData);
	
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 )
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
	down(pos);
	
	tag = strToken.c_str();
	pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_TEXT);
	
	uSize = tag.length();
	posData = m_pData->spMeta->InsertData((uint32_t)uSize + 1);
	szData = (char*)m_pData->spMeta->GetData(posData);
	::memcpy(szData, tag.c_str(), uSize);
	
	//data
	m_pData->spMeta->SetAstData(pos, posData);
	
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 )
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
	up();
 
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
