/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

//code convert

// Ansi -> wstring

void CodeConvertHelper::AnsiToWide(const char* sz1, std::wstring& str2)
{
	str2.clear();
	std::mbstate_t state = {};
	size_t len = std::mbsrtowcs(nullptr, &sz1, 0, &state);
	if( len != (size_t)-1 ) {
		str2.resize(len + 1);
		len = std::mbsrtowcs(&(str2.at(0)), &sz1, len, &state);
		assert( len != (size_t)-1 );
		str2.resize(len);
	}
}

// wstring -> Ansi

void CodeConvertHelper::WideToAnsi(const wchar_t* sz1, std::string& str2)
{
	str2.clear();
	std::mbstate_t state = {};
	size_t len = std::wcsrtombs(nullptr, &sz1, 0, &state);
	if( len != (size_t)-1 ) {
		str2.resize(len + 1);
		len = std::wcsrtombs(&(str2.at(0)), &sz1, len, &state);
		assert( len != (size_t)-1 );
		str2.resize(len);
	}
}

// UTF8 -> wstring

void CodeConvertHelper::UTF8ToWide(const char* sz1, std::wstring& str2)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	str2 = conv.from_bytes(sz1);
}
void CodeConvertHelper::UTF8ToWide(const std::string& str1, std::wstring& str2)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	str2 = conv.from_bytes(str1);
}

// wstring -> UTF8

void CodeConvertHelper::WideToUTF8(const wchar_t* wsz1, std::string& str2)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	str2 = conv.to_bytes(wsz1);
}
void CodeConvertHelper::WideToUTF8(const std::wstring& str1, std::string& str2)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	str2 = conv.to_bytes(str1);
}

//path

void FsPathHelper::ToPlatform(char* szBuffer) throw()
{
#ifdef WIN32
	char* ps = szBuffer;
	while( *ps != 0 ) {
		if( *ps == '/' )
			*ps = '\\';
		++ ps;
	}
#endif
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
