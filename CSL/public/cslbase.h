/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __CSL_BASE_H__
#define __CSL_BASE_H__
////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <cassert>
#include <cstring>

#include <memory>
#include <vector>
#include <stack>
#include <map>
#include <set>

#include <string>
#include <codecvt>
#include <cwchar>
#include <locale>

#include <stdexcept>
#include <fstream>
#include <iostream>

#include <functional>
#include <tuple>
#include <limits>

#include <thread>
#include <chrono>

//C++17
#include <filesystem>
#include <any>

////////////////////////////////////////////////////////////////////////////////

// types

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

//code convert

class CodeConvertHelper
{
public:
	// Ansi -> wstring
	static void AnsiToWide(const char* sz1, std::wstring& str2);
	// wstring -> Ansi
	static void WideToAnsi(const wchar_t* sz1, std::string& str2);
	// UTF8 -> wstring
	static void UTF8ToWide(const char* sz1, std::wstring& str2);
	static void UTF8ToWide(const std::string& str1, std::wstring& str2);
	// wstring -> UTF8
	static void WideToUTF8(const wchar_t* wsz1, std::string& str2);
	static void WideToUTF8(const std::wstring& str1, std::string& str2);
};

//path

class FsPathHelper
{
public:
	static void ToPlatform(char* szBuffer) throw();
	static const char* GetHomeDirectory() throw();
};

//stream

class StreamHelper
{
public:
	//return: true -- has UTF8 BOM
	static bool CheckBOM_UTF8(std::istream& stm);
};

//test

class TestBody
{
public:
	//T : Lambda
	template <typename T>
	static bool Run(const T& t) throw()
	{
		try {
			t();
		}
		catch(...) {
			//**********
			std::cout << "Exception error: (" << __FILE__ << ")(" << __LINE__ << ")" << std::endl;
			//**********
			return false;
		}
		return true;
	}
	static void Assert(bool bValue, const char* szFile, int iLineNum)
	{
		if( !bValue ) {
			//**********
			std::cout << "Assert error: (" << szFile << ")(" << iLineNum << ")" << std::endl;
			//**********
			throw std::exception();
		}
	}
	//T : Lambda
	template <typename T>
	static void Exception(const T& t)
	{
		try {
			t();
		}
		catch(...) {
			//**********
			std::cout << "Correct Exception : (" << __FILE__ << ")(" << __LINE__ << ")" << std::endl;
			//**********
			return ;
		}
		Assert(false, __FILE__, __LINE__);
	}
};

//framework

/*
class ParameterBase
{
public:
	uint32_t m_uType;
};
*/

// Command
//   [](std::any&& param)->bool
typedef std::function<bool(std::any&&)>  CommandFunc;

// Property Notification
//   [](uint32_t)
typedef std::function<void(uint32_t)>  PropertyNotification;

class PropertyTrigger
{
public:
	PropertyTrigger() noexcept;
	PropertyTrigger(const PropertyTrigger&) = delete;
	PropertyTrigger& operator=(const PropertyTrigger&) = delete;
	~PropertyTrigger() noexcept;

	void ClearNotifications() noexcept;
	void AddNotification(PropertyNotification&& pn);

	void Fire(uint32_t uID);

private:
	std::vector<PropertyNotification> m_vecPN;
};

// state machine

class IStateBase
{
public:
	//virtual int32_t Process(uint32_t uEvent, const std::shared_ptr<ParameterBase>& param) = 0;
	virtual int32_t Process(uint32_t uEvent, const std::any& param) = 0;
};

class StateManager
{
public:
	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;

	void Add(int32_t iState, const std::shared_ptr<IStateBase>& spState)
	{
		m_map.insert(std::pair<int32_t, std::shared_ptr<IStateBase>>(iState, spState));
	}
	void SetStartState(int32_t iStartState) throw()
	{
		m_iCurrentState = iStartState;
	}
	void Process(uint32_t uEvent, const std::any& param)
	{
		auto iter(m_map.find(m_iCurrentState));
		if( iter != m_map.end() )
			m_iCurrentState = iter->second->Process(uEvent, param);
	}
	int32_t GetCurrentState() const throw()
	{
		return m_iCurrentState;
	}

private:
	int32_t m_iCurrentState;
	std::map<int32_t, std::shared_ptr<IStateBase>> m_map;
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
