/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// redirect io

RedirectIoProcess::RedirectIoProcess() throw() : m_fp(NULL)
{
}
RedirectIoProcess::~RedirectIoProcess() throw()
{
	Close();
}

int RedirectIoProcess::Close() throw()
{
	int ret = 0;
	if( m_fp != NULL ) {
#ifdef WIN32
		ret = ::_pclose(m_fp);
#else
		ret = ::pclose(m_fp);
#endif
		m_fp = NULL;
	}
	return ret;
}

bool RedirectIoProcess::Start(const char* szCommand, const char* szMode) throw()
{
	assert( m_fp == NULL );
#ifdef WIN32
	m_fp = ::_popen(szCommand, szMode);
#else
	m_fp = ::popen(szCommand, szMode);
#endif
	return m_fp != NULL;
}

FILE* RedirectIoProcess::GetFile() const throw()
{
	return m_fp;
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
