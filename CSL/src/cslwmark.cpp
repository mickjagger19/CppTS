/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "cslwmark.h"

#include "wmark/WmarkScanner.h"
#include "wmark/WmarkParser.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// Utility

WmarkUtility::WmarkUtility() throw()
{
}

WmarkUtility::~WmarkUtility() throw()
{
}

bool WmarkUtility::Initialize()
{
	//actions
	WmarkScannerHelper::CreateActions(m_spTkAction, m_spCommentAction, m_spTextAction);
	//table
	return WmarkParserHelper::CreateTable(m_spTable);
}

// Parser

WmarkParser::WmarkParser() throw() : m_uMaxErrorNumber(0)
{
}

WmarkParser::~WmarkParser() throw()
{
}

void WmarkParser::Initialize(uint32_t uMaxErrorNumber, const std::shared_ptr<WmarkUtility>& spU)
{
	//scanner
	m_spScanner = std::make_shared<RdScanner>();
	WmarkScannerHelper::SetActions(*m_spScanner, spU->m_spTkAction, spU->m_spCommentAction, spU->m_spTextAction);
	//parser
	m_parser.SetScanner(m_spScanner);
	m_parser.SetTable(spU->m_spTable);
	//data
	m_data.posParent.uAddress = 0;
	m_data.posCurrent.uAddress = 0;
	//actions
	WmarkParserHelper::InitActions(m_parser, &m_data);
	//utility
	m_spUtility = spU;
	//error number
	m_uMaxErrorNumber = uMaxErrorNumber;
}

void WmarkParser::SetInput(const std::shared_ptr<std::istream>& spStream) throw()
{
	assert( m_spScanner.get() != nullptr );
	m_spScanner->SetStream(spStream);
}

void WmarkParser::SetOutput(const std::shared_ptr<RdMetaData>& spMeta) throw()
{
	assert( spMeta.get() != nullptr );
	m_data.spMeta = spMeta;
}

void WmarkParser::Start()
{
	WmarkParserHelper::Start(m_parser);
	m_data.posParent.uAddress = 0;
	m_data.posCurrent.uAddress = 0;
}

int32_t WmarkParser::Parse()
{
	bool bEmpty;
	int32_t iRet = m_parser.Parse(bEmpty);
	if( iRet == -1 ) {
		if( !m_parser.Revert() )
			return -1;
		return 1;
	}
	if( iRet > 0 ) {
		if( m_uMaxErrorNumber != 0 && m_parser.GetErrorArray().size() >= (size_t)m_uMaxErrorNumber )
			return 0;
	}
	return iRet;
}

const std::vector<std::string>& WmarkParser::GetErrorArray() const throw()
{
	return m_parser.GetErrorArray();
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
