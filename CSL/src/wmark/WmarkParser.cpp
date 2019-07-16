/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "WmarkParser.h"

#include "WmarkDef.h"

#include "parser_actions/accepted_action.h"
#include "parser_actions/program_action.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

//rules
const RULEELEMENT g_Rules[] = {
//=============================================================================
//program : return_list r_body
{ WMARK_NT_program, WMARK_PARSER_ACT_program }, { WMARK_NT_return_list, LA_NULL }, { WMARK_NT_r_body, LA_NULL }, { TK_NULL, LA_NULL },
//program : b_body
{ WMARK_NT_program, WMARK_PARSER_ACT_program }, { WMARK_NT_b_body, LA_NULL }, { TK_NULL, LA_NULL },
//r_body : b_body
{ WMARK_NT_r_body, LA_NULL }, { WMARK_NT_b_body, LA_NULL }, { TK_NULL, LA_NULL },
//r_body : TK_EPSILON
{ WMARK_NT_r_body, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//b_body : block_element be_tail
{ WMARK_NT_b_body, LA_NULL }, { WMARK_NT_block_element, LA_NULL }, { WMARK_NT_be_tail, LA_NULL }, { TK_NULL, LA_NULL },
//be_tail : WMARK_TK_RETURN ber_tail
{ WMARK_NT_be_tail, LA_NULL }, { WMARK_TK_RETURN, LA_NULL }, { WMARK_NT_ber_tail, LA_NULL }, { TK_NULL, LA_NULL },
//be_tail : TK_EPSILON
{ WMARK_NT_be_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//ber_tail : return_list berr_tail
{ WMARK_NT_ber_tail, LA_NULL }, { WMARK_NT_return_list, LA_NULL }, { WMARK_NT_berr_tail, LA_NULL }, { TK_NULL, LA_NULL },
//ber_tail : TK_EPSILON
{ WMARK_NT_ber_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//berr_tail : b_body
{ WMARK_NT_berr_tail, LA_NULL }, { WMARK_NT_b_body, LA_NULL }, { TK_NULL, LA_NULL },
//berr_tail : TK_EPSILON
{ WMARK_NT_berr_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//return_list : WMARK_TK_RETURN return_list_tail
{ WMARK_NT_return_list, LA_NULL }, { WMARK_TK_RETURN, LA_NULL }, { WMARK_NT_return_list_tail, LA_NULL }, { TK_NULL, LA_NULL },
//return_list_tail : WMARK_TK_RETURN return_list_tail
{ WMARK_NT_return_list_tail, LA_NULL }, { WMARK_TK_RETURN, LA_NULL }, { WMARK_NT_return_list_tail, LA_NULL }, { TK_NULL, LA_NULL },
//return_list_tail : TK_EPSILON
{ WMARK_NT_return_list_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//block_element : WMARK_TK_COMMENT
{ WMARK_NT_block_element, LA_NULL }, { WMARK_TK_COMMENT, LA_NULL }, { TK_NULL, LA_NULL },
//block_element : WMARK_TK_TEXT
{ WMARK_NT_block_element, LA_NULL }, { WMARK_TK_TEXT, LA_NULL }, { TK_NULL, LA_NULL },
//block_element : WMARK_TK_IDENT
{ WMARK_NT_block_element, LA_NULL }, { WMARK_TK_INDENT, LA_NULL }, { TK_NULL, LA_NULL },
//=============================================================================
//end
{ TK_NULL, LA_NULL }
};

// WmarkParserHelper

bool WmarkParserHelper::CreateTable(std::shared_ptr<RdaTable>& spTable)
{
	spTable = std::make_shared<RdaTable>();
	return spTable->Generate(g_Rules, WMARK_TK_MAX);
}

void WmarkParserHelper::InitActions(RdParser& parser, RdParserActionMetaData* pData)
{
	parser.ClearActions();
	std::shared_ptr<IRdParserAction> spAction;
	//accepted
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserAcceptedAction>(std::make_shared<WmarkParserAcceptedAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.SetAcceptedAction(spAction);
	//program
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserProgramAction>(std::make_shared<WmarkParserProgramAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_program, spAction);
}

void WmarkParserHelper::Start(RdParser& parser)
{
	parser.Start(WMARK_SCANNER_TK_ACTION, WMARK_TK_MAX);
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
