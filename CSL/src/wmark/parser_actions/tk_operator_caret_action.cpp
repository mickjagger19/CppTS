/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_operator_caret_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkOperatorCaretAction

WmarkParserTkOperatorCaretAction::WmarkParserTkOperatorCaretAction() noexcept
{
}
WmarkParserTkOperatorCaretAction::~WmarkParserTkOperatorCaretAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkOperatorCaretAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkOperatorCaretAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//Caret
	assert( m_pData->posParent.uAddress != 0 );
	
	//subNode duplicate
	RdMetaAstNodeInfo currentInfo;
	m_pData->spMeta->GetAstNodeInfo(m_pData->posCurrent, currentInfo);
	RdMetaDataPosition subNode = m_pData->spMeta->AllocateAstNode(currentInfo.uType);
	m_pData->spMeta->SetAstParent(subNode, m_pData->posCurrent);
	m_pData->spMeta->SetAstChild(subNode, currentInfo.posChild);
	m_pData->spMeta->SetAstData(subNode, currentInfo.posData);
	m_pData->spMeta->SetAstNext(subNode, currentInfo.posNext);
	
	//newNode
	m_pData->spMeta->SetAstType(m_pData->posCurrent, WMARK_NODETYPE_TAG);
	std::string tag = "msup";
	
	size_t uSize = tag.length();
	RdMetaDataPosition posData = m_pData->spMeta->InsertData((uint32_t)uSize + 1);
	char* szData = (char*)m_pData->spMeta->GetData(posData);
	::memcpy(szData, tag.c_str(), uSize);
	
	//data
	m_pData->spMeta->SetAstData(m_pData->posCurrent, posData);
	
	m_pData->spMeta->SetAstParent(m_pData->posCurrent,  m_pData->posParent);
	RdMetaDataPosition pos;
	pos.uAddress = 0;
	m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
	m_pData->spMeta->SetAstChild(m_pData->posCurrent, subNode);
	
	//child->current  ------->  child->subNode
	m_pData->spMeta->SetAstParent(currentInfo.posChild, subNode);
	
	m_pData->posParent = m_pData->posCurrent;
	m_pData->posCurrent = subNode;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
