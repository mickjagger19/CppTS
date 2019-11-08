﻿/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../base/WmarkDef.h"

#include "berr_tail_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkParserBerrTailAction

WmarkParserBerrTailAction::WmarkParserBerrTailAction() noexcept
{
}
WmarkParserBerrTailAction::~WmarkParserBerrTailAction() noexcept
{
}

// IRdParserAction methods

void WmarkParserBerrTailAction::SetParameter(const std::any& param)
{
    m_pData = std::any_cast<RdParserActionMetaData *>(param);
}

bool WmarkParserBerrTailAction::DoAction(const std::string& strToken, std::vector<std::string>& vecError)
{
	//up
	assert( m_pData->posParent.uAddress != 0 );
    up();
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
