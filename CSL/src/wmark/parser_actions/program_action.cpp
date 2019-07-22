/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "program_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserProgramAction

WmarkParserProgramAction::WmarkParserProgramAction() noexcept : m_pData(nullptr)
{
}
WmarkParserProgramAction::~WmarkParserProgramAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserProgramAction::SetParameter(const std::any& param)
{
	m_pData = std::any_cast<RdParserActionMetaData*>(param);
}

bool WmarkParserProgramAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//root
	if( m_pData->posParent.uAddress == 0 && m_pData->posCurrent.uAddress == 0 ) {
		RdMetaDataPosition pos = m_pData->spMeta->InsertAstNode(WMARK_NODETYPE_ROOT);
		RdMetaDataPosition posRoot = m_pData->spMeta->GetAstRoot(m_pData->spMeta->GetAstStart());
		m_pData->spMeta->SetAstParent(pos, posRoot);
		m_pData->spMeta->SetAstChild(posRoot, pos);
		m_pData->posParent = pos;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
