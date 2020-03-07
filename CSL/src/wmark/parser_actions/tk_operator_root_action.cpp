/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "tk_operator_root_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserTkOperatorRootAction

WmarkParserTkOperatorRootAction::WmarkParserTkOperatorRootAction() noexcept
{
}
WmarkParserTkOperatorRootAction::~WmarkParserTkOperatorRootAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserTkOperatorRootAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserTkOperatorRootAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//Root
	assert( m_pData->posParent.uAddress != 0 );
	
	up();
	
	//subNode duplicate
	RdMetaAstNodeInfo currentInfo;
	m_pData->spMeta->GetAstNodeInfo(m_pData->posCurrent, currentInfo);
	
	RdMetaAstNodeInfo childInfo;
	m_pData->spMeta->GetAstNodeInfo(currentInfo.posChild, childInfo);
	
	m_pData->spMeta->SetAstChild(m_pData->posCurrent, childInfo.posNext);
	RdMetaDataPosition pos;
	pos.uAddress = 0;
	m_pData->spMeta->SetAstNext(currentInfo.posChild, pos);
	m_pData->spMeta->SetAstNext(childInfo.posNext, currentInfo.posChild);
	
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
