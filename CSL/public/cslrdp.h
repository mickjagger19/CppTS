/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __CSL_RDP_H__
#define __CSL_RDP_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// Recursive descent parser (LL1)

// right-linear grammar

//tokens
#define TK_EPSILON       ((uint32_t)-10)
#define TK_NULL          (0)
#define TK_ERROR         ((uint32_t)-1)
#define TK_END_OF_EVENT  ((uint32_t)-2)
#define TK_START         (1)

// action stack

typedef std::stack<uint32_t>  RdActionStack;

// scanner action
class IRdScannerAction
{
public:
	virtual bool Scan(std::istream& stm, RdActionStack& stk, uint32_t& uID, std::string& strToken) = 0;
};

// RdScanner

class RdScanner
{
public:
	RdScanner() throw();
	~RdScanner() throw();

	void SetStream(const std::shared_ptr<std::istream>& spStream) throw();
	void ClearActions() throw();
	void AddAction(uint32_t uActionID, const std::shared_ptr<IRdScannerAction>& spAction);
	void Start(uint32_t uStartAction) throw();
	bool GetToken(uint32_t& uID, std::string& strToken);

private:
	//map: <action id, action>
	std::map<uint32_t, std::shared_ptr<IRdScannerAction>>  m_map;
	//stream
	std::shared_ptr<std::istream>  m_spStream;
	//stack
	RdActionStack  m_stack;
	//start action
	uint32_t m_uStartAction;
};

// rda table

//LL actions
#define LA_NULL     (0)

//rule table
typedef struct _tagRuleElement
{
	uint32_t uToken;
	uint32_t uAction;
} RULEELEMENT;

typedef struct _tagRuleItem
{
	const RULEELEMENT* pRule;
} RULEITEM;

typedef struct _tagRuleTable
{
	const RULEITEM* pRuleSet;
	int32_t iMaxRuleNo;
} RULETABLE;



// push-down stack

typedef std::stack<RULEELEMENT>  RdPushDownStack;

// RdParser

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
