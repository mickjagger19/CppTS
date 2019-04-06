/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// RdScanner

RdScanner::RdScanner() throw() : m_uStartAction(0)
{
}
RdScanner::~RdScanner() throw()
{
}

void RdScanner::SetStream(const std::shared_ptr<std::istream>& spStream) throw()
{
	assert( spStream.get() != NULL );
	m_spStream = spStream;
}

void RdScanner::ClearActions() throw()
{
	m_map.clear();
}

void RdScanner::AddAction(uint32_t uActionID, const std::shared_ptr<IRdScannerAction>& spAction)
{
	m_map.insert(std::pair<uint32_t, std::shared_ptr<IRdScannerAction>>(uActionID, spAction));
}

void RdScanner::Start(uint32_t uStartAction) throw()
{
	assert( m_spStream.get() != NULL );
	//clear
	while( !m_stack.empty() )
		m_stack.pop();
	m_uStartAction = uStartAction;
}

bool RdScanner::GetToken(uint32_t& uID, std::string& strToken)
{
	assert( m_spStream.get() != NULL );
	uID = TK_ERROR;
	strToken.clear();
	m_stack.push(m_uStartAction);
	//loop
	while( !m_stack.empty() ) {
		uint32_t uActionID = m_stack.top();
		m_stack.pop();
		auto it(m_map.find(uActionID));
		assert( it != m_map.end() );
		bool bRet = it->second->Scan(*(m_spStream.get()), m_stack, uID, strToken);
		if( !bRet )
			return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
