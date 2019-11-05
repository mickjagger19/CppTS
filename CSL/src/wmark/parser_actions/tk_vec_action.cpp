/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_vec_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserVecAction

WmarkParserVecAction::WmarkParserVecAction() noexcept
{
}
WmarkParserVecAction::~WmarkParserVecAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserVecAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserVecAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//text
	assert( m_pData->posParent.uAddress != 0 );
	//string
	size_t uSize = strToken.length();
	if( uSize >= (size_t)(std::numeric_limits<uint32_t>::max()) )
		return false;
	//node
	RdMetaDataPosition pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_TEXT);
	//token, allocate the space for text data
	RdMetaDataPosition posData = m_pData->spMeta->InsertData((uint32_t)uSize + 1);
	char* szData = (char*)m_pData->spMeta->GetData(posData);
	::memcpy(szData, strToken.c_str(), uSize);
	szData[uSize] = '\0';
	//data
	m_pData->spMeta->SetAstData(pos, posData);
	//link
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 )  // in the sub tree
        m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else
        m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
    up();
	
	std::string tag = "mo";
	pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_TAG);
	
	uSize = tag.length();
	posData = m_pData->spMeta->InsertData((uint32_t)uSize + 1);
	szData = (char*)m_pData->spMeta->GetData(posData);
	::memcpy(szData, tag.c_str(), uSize);
	
	//data
	m_pData->spMeta->SetAstData(pos, posData);
	
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 )  // in the sub tree
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
	down(pos);
	
	
	std::string vec = "&rarr;";
	uSize = vec.length();
	if( uSize >= (size_t)(std::numeric_limits<uint32_t>::max()) )
		return false;
	//node
	pos = m_pData->spMeta->AllocateAstNode(WMARK_NODETYPE_TEXT);
	//token, allocate the space for text data
	posData = m_pData->spMeta->InsertData((uint32_t)uSize + 1);
	szData = (char*)m_pData->spMeta->GetData(posData);
	::memcpy(szData, vec.c_str(), uSize);
	szData[uSize] = '\0';
	//data
	m_pData->spMeta->SetAstData(pos, posData);
	//link
	m_pData->spMeta->SetAstParent(pos, m_pData->posParent);
	if( m_pData->posCurrent.uAddress == 0 )  // in the sub tree
		m_pData->spMeta->SetAstChild(m_pData->posParent, pos);
	else
		m_pData->spMeta->SetAstNext(m_pData->posCurrent, pos);
	
	up();
	up();
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
