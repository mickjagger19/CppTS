/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

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

bool WmarkParserTkTextAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//text
	assert( m_pData->posParent.uAddress != 0 );
	//string
	size_t uSize = strToken.length();
	if( uSize >= (size_t)(std::numeric_limits<uint32_t>::max()) )
		return false;
	//node
	RdMetaDataPosition pos = m_pData->spMeta->InsertAstNode(WMARK_NODETYPE_TEXT);
	//token
	RdMetaDataPosition posData = m_pData->spMeta->InsertData((uint32_t)uSize + 1);
	char* szData = (char*)m_pData->spMeta->GetData(posData);
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
	m_pData->posCurrent = pos;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
