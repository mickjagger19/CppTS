/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "WmarkParser.h"

#include "base/WmarkDef.h"

#include "parser_actions/accepted_action.h"
#include "parser_actions/program_action.h"
#include "parser_actions/tk_comment_action.h"
#include "parser_actions/block_element_action.h"
#include "parser_actions/up_action.h"
#include "parser_actions/tk_text_action.h"
#include "parser_actions/tk_indent_action.h"
#include "parser_actions/tk_bold_action.h"
#include "parser_actions/tk_italic_action.h"
#include "parser_actions/tk_heading_action.h"
#include "parser_actions/tk_code_action.h"
#include "parser_actions/image_action.h"
#include "parser_actions/li_action.h"
#include "parser_actions/ol_action.h"
#include "parser_actions/ul_action.h"
#include "parser_actions/tk_math_action.h"
#include "parser_actions/nt_mi_action.h"
#include "parser_actions/nt_mo_action.h"
#include "wmark/parser_actions/tk_math_text_action.h"
#include "parser_actions/tk_mrow_action.h"
#include "parser_actions/tk_operator_caret_action.h"
#include "parser_actions/tk_operator_tag_action.h"
#include "parser_actions/tk_operator_root_action.h"
#include "parser_actions/tk_operator_munderover_action.h"
#include "parser_actions/tk_operator_verticalline_action.h"
#include "parser_actions/tk_vec_action.h"
#include "parser_actions/tk_bar_action.h"
#include "parser_actions/double_struck_action.h"

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
//block_element : WMARK_TK_COMMENT
{ WMARK_NT_block_element, LA_NULL }, { WMARK_TK_COMMENT, WMARK_PARSER_ACT_TK_COMMENT }, { TK_NULL, LA_NULL },
//block_element : line_element be_tail
{ WMARK_NT_block_element, WMARK_PARSER_ACT_block_element }, { WMARK_NT_line_element, LA_NULL }, { WMARK_NT_be_tail, LA_NULL }, { TK_NULL, LA_NULL },
//block_element : ol be_tail
{ WMARK_NT_block_element, WMARK_PARSER_ACT_NT_OL }, { WMARK_NT_OLI, LA_NULL }, { WMARK_NT_OL, LA_NULL }, { WMARK_NT_ber_tail, LA_NULL }, { TK_NULL, LA_NULL },
//block_element : ul be_tail
{ WMARK_NT_block_element, WMARK_PARSER_ACT_NT_UL }, { WMARK_NT_ULI, LA_NULL }, { WMARK_NT_UL, LA_NULL }, { WMARK_NT_ber_tail, LA_NULL }, { TK_NULL, LA_NULL },
//ol : oli ol
{ WMARK_NT_OL, LA_NULL }, { WMARK_NT_OLI, LA_NULL }, { WMARK_NT_OL, LA_NULL }, { TK_NULL, LA_NULL },
//ul : uli ul
{ WMARK_NT_UL, LA_NULL }, { WMARK_NT_ULI, LA_NULL }, { WMARK_NT_UL, LA_NULL }, { TK_NULL, LA_NULL },
//oli : TK_EPSILON
{ WMARK_NT_OL, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//uli : TK_EPSILON
{ WMARK_NT_UL, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//oli : WMARK_TK_LI text WMARK_TK_RETURN
{ WMARK_NT_OLI, WMARK_PARSER_ACT_NT_LI }, { WMARK_TK_OLI, LA_NULL }, { WMARK_NT_line_element, LA_NULL}, { WMARK_NT_li_tail, LA_NULL }, { TK_NULL, LA_NULL },
//uli : WMARK_TK_LI text WMARK_TK_RETURN
{ WMARK_NT_ULI, WMARK_PARSER_ACT_NT_LI }, { WMARK_TK_ULI, LA_NULL }, { WMARK_NT_line_element, LA_NULL}, { WMARK_NT_li_tail, LA_NULL }, { TK_NULL, LA_NULL },
//li_tail : WMARK_TK_RETURN
{ WMARK_NT_li_tail, WMARK_PARSER_ACT_UP }, { WMARK_TK_RETURN, LA_NULL }, { TK_NULL, LA_NULL },
//li_tail : TK_EPSILON
{ WMARK_NT_li_tail, WMARK_PARSER_ACT_UP }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//be_tail : WMARK_TK_RETURN ber_tail
{ WMARK_NT_be_tail, LA_NULL }, { WMARK_TK_RETURN, LA_NULL }, { WMARK_NT_ber_tail, LA_NULL }, { TK_NULL, LA_NULL },
//be_tail : TK_EPSILON
{ WMARK_NT_be_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//ber_tail : line_element be_tail
{ WMARK_NT_ber_tail, LA_NULL }, { WMARK_NT_line_element, LA_NULL }, { WMARK_NT_be_tail, LA_NULL }, { TK_NULL, LA_NULL },
//ber_tail : return_list berr_tail
{ WMARK_NT_ber_tail, LA_NULL }, { WMARK_NT_return_list, LA_NULL }, { WMARK_NT_berr_tail, LA_NULL }, { TK_NULL, LA_NULL },
//ber_tail : TK_EPSILON
{ WMARK_NT_ber_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//berr_tail : b_body
{ WMARK_NT_berr_tail, WMARK_PARSER_ACT_UP }, { WMARK_NT_b_body, LA_NULL }, { TK_NULL, LA_NULL },
//berr_tail : TK_EPSILON
{ WMARK_NT_berr_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//return_list : WMARK_TK_RETURN return_list_tail
{ WMARK_NT_return_list, LA_NULL }, { WMARK_TK_RETURN, LA_NULL }, { WMARK_NT_return_list_tail, LA_NULL }, { TK_NULL, LA_NULL },
//return_list_tail : WMARK_TK_RETURN return_list_tail
{ WMARK_NT_return_list_tail, LA_NULL }, { WMARK_TK_RETURN, LA_NULL }, { WMARK_NT_return_list_tail, LA_NULL }, { TK_NULL, LA_NULL },
//return_list_tail : TK_EPSILON
{ WMARK_NT_return_list_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//line_element : text
{ WMARK_NT_line_element, LA_NULL }, { WMARK_NT_text, LA_NULL }, { WMARK_NT_text_tail, LA_NULL }, { TK_NULL, LA_NULL },
//line_element : heading
{ WMARK_NT_line_element, LA_NULL }, { WMARK_TK_HEADING, WMARK_PARSER_ACT_TK_HEADING }, { WMARK_NT_text, LA_NULL }, { WMARK_NT_up, LA_NULL }, { TK_NULL, LA_NULL },
//line_element : WMARK_TK_INDENT
{ WMARK_NT_line_element, LA_NULL }, { WMARK_TK_INDENT, WMARK_PARSER_ACT_TK_INDENT }, { TK_NULL, LA_NULL },
//line_element : WMARK_TK_MATH expression WMARK_TK_MATH                30
{ WMARK_NT_text, LA_NULL }, { WMARK_TK_MATH, WMARK_PARSER_ACT_TK_MATH }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_MATH, WMARK_PARSER_ACT_UP }, { TK_NULL, LA_NULL },
//expression : term expression
{ WMARK_NT_expression, LA_NULL }, { WMARK_NT_base, LA_NULL }, { WMARK_NT_expression, LA_NULL }, { TK_NULL, LA_NULL },
//expression : EPSILON
{ WMARK_NT_expression, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//expression : bb  "TEXT" expression
{ WMARK_NT_expression, WMARK_PARSER_ACT_TK_BOLD }, { WMARK_TK_BB, LA_NULL }, { WMARK_TK_SPACE, LA_NULL }, { WMARK_TK_QUOTATION_MARK, LA_NULL }, { WMARK_TK_TEXT, WMARK_PARSER_ACT_TK_TEXT }, { WMARK_TK_QUOTATION_MARK, WMARK_PARSER_ACT_UP }, { WMARK_NT_expression, LA_NULL }, { TK_NULL, LA_NULL },
//expression : bbb "TEXT" expression
{ WMARK_NT_expression, WMARK_PARSER_ACT_DOUBLE_STRUCK }, { WMARK_TK_BBB, LA_NULL }, { WMARK_TK_SPACE, LA_NULL }, { WMARK_TK_QUOTATION_MARK, LA_NULL }, { WMARK_TK_TEXT, WMARK_PARSER_ACT_TK_TEXT }, { WMARK_TK_QUOTATION_MARK, WMARK_PARSER_ACT_UP }, { WMARK_NT_expression, LA_NULL }, { TK_NULL, LA_NULL },

{ WMARK_NT_MO, WMARK_PARSER_ACT_NT_MO }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
{ WMARK_NT_MO, WMARK_PARSER_ACT_NT_MO }, { WMARK_TK_FOOBAR, LA_NULL}, { TK_NULL, LA_NULL },
//term : sum_ ( expr )  ^ expr term
{ WMARK_NT_base, WMARK_PARSER_ACT_TK_OPERATOR_MUNDEROVER }, { WMARK_TK_OPERATOR_SUM, WMARK_PARSER_ACT_TK_MATH_TEXT }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_MROW }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_UP }, { WMARK_TK_OPERATOR_CARET, LA_NULL }, { WMARK_NT_base, LA_NULL }, { WMARK_TK_SPACE, WMARK_PARSER_ACT_UP }, { WMARK_NT_base, LA_NULL }, { TK_NULL, LA_NULL },
//term : prod_ ( expr ) ^ expr term
{ WMARK_NT_base, WMARK_PARSER_ACT_TK_OPERATOR_MUNDEROVER }, { WMARK_TK_OPERATOR_PROD, WMARK_PARSER_ACT_TK_MATH_TEXT }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_MROW }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_UP }, { WMARK_TK_OPERATOR_CARET, LA_NULL }, { WMARK_NT_base, LA_NULL }, { WMARK_TK_SPACE, WMARK_PARSER_ACT_UP }, { WMARK_NT_base, LA_NULL }, { TK_NULL, LA_NULL },
//term : int_ ( expr ) ^ expr term
{ WMARK_NT_base, WMARK_PARSER_ACT_TK_OPERATOR_MUNDEROVER }, { WMARK_TK_OPERATOR_INT, WMARK_PARSER_ACT_TK_MATH_TEXT }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_MROW }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_UP }, { WMARK_TK_OPERATOR_CARET, LA_NULL }, { WMARK_NT_base, LA_NULL }, { WMARK_TK_SPACE, WMARK_PARSER_ACT_UP }, { WMARK_NT_base, LA_NULL }, { TK_NULL, LA_NULL },
//term : oint_ ( expr ) ^ expr term
{ WMARK_NT_base, WMARK_PARSER_ACT_TK_OPERATOR_MUNDEROVER }, { WMARK_TK_OPERATOR_OINT, WMARK_PARSER_ACT_TK_MATH_TEXT }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_MROW }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_UP }, { WMARK_TK_OPERATOR_CARET, LA_NULL }, { WMARK_NT_base, LA_NULL }, { WMARK_TK_SPACE, WMARK_PARSER_ACT_UP }, { WMARK_NT_base, LA_NULL }, { TK_NULL, LA_NULL },
//base : ^ exponent
{ WMARK_NT_base, WMARK_PARSER_ACT_TK_OPERATOR_MSUP }, { WMARK_TK_OPERATOR_CARET, LA_NULL }, { WMARK_NT_base, LA_NULL }, { WMARK_NT_up, LA_NULL}, { TK_NULL, LA_NULL },
//base : operator
{ WMARK_NT_base, WMARK_PARSER_ACT_NT_MO }, { WMARK_TK_OPERATOR, WMARK_PARSER_ACT_TK_MATH_TEXT }, { TK_NULL, LA_NULL },
//base : ( expr )
{ WMARK_NT_base, WMARK_PARSER_ACT_NT_MO }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_TK_MATH_TEXT }, { WMARK_NT_expression, LA_NULL}, { WMARK_NT_MO, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_TK_MATH_TEXT }, { TK_NULL, LA_NULL },
//base : [ expr ]
{ WMARK_NT_base, WMARK_PARSER_ACT_NT_MO }, { WMARK_TK_OPERATOR_LEFT_SQUARE_BRACKETS, WMARK_PARSER_ACT_TK_MATH_TEXT }, { WMARK_NT_expression, LA_NULL}, { WMARK_NT_MO, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_SQUARE_BRACKETS, WMARK_PARSER_ACT_TK_MATH_TEXT }, { TK_NULL, LA_NULL },
//base : { expr }
{ WMARK_NT_base, WMARK_PARSER_ACT_NT_MO }, { WMARK_TK_OPERATOR_LEFT_CURLY_BRACES, WMARK_PARSER_ACT_TK_MATH_TEXT }, { WMARK_NT_expression, LA_NULL}, { WMARK_NT_MO, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_CURLY_BRACES, WMARK_PARSER_ACT_TK_MATH_TEXT }, { TK_NULL, LA_NULL },
//base : text
{ WMARK_NT_base, WMARK_PARSER_ACT_NT_MI }, { WMARK_TK_TEXT, WMARK_PARSER_ACT_TK_MATH_TEXT }, { TK_NULL, LA_NULL },
//base : FRAC ( base ) ( base )
{ WMARK_NT_base, LA_NULL }, { WMARK_TK_OPERATOR_FRAC, WMARK_PARSER_ACT_TK_OPERATOR_TAG }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_MROW }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_UP }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_MROW }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_UP }, { WMARK_NT_up, LA_NULL }, { TK_NULL, LA_NULL },
//base : sqrt ( base )
{ WMARK_NT_base, LA_NULL }, { WMARK_TK_OPERATOR_SQRT, WMARK_PARSER_ACT_TK_OPERATOR_TAG }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, LA_NULL }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_UP }, { TK_NULL, LA_NULL },
//base : root ( base ) ( base )
{ WMARK_NT_base, LA_NULL }, { WMARK_TK_OPERATOR_ROOT, WMARK_PARSER_ACT_TK_OPERATOR_TAG }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, LA_NULL }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, LA_NULL }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, LA_NULL }, { WMARK_NT_base, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_TK_OPERATOR_ROOT }, { TK_NULL, LA_NULL },
//base : ABS ( expr )
{ WMARK_NT_base, LA_NULL }, { WMARK_TK_OPERATOR_ABS, LA_NULL }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_TK_OPERATOR_VERTICALLINE }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_TK_OPERATOR_VERTICALLINE }, { TK_NULL, LA_NULL },
//base : floor ( expr )
{ WMARK_NT_base, LA_NULL }, { WMARK_TK_OPERATOR_FLOOR, LA_NULL }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_TK_OPERATOR_VERTICALLINE }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_TK_OPERATOR_VERTICALLINE }, { TK_NULL, LA_NULL },
//base : ceil ( expr )
{ WMARK_NT_base, LA_NULL }, { WMARK_TK_OPERATOR_CEIL, LA_NULL }, { WMARK_TK_OPERATOR_LEFT_PARENTHESES, WMARK_PARSER_ACT_TK_OPERATOR_VERTICALLINE }, { WMARK_NT_expression, LA_NULL }, { WMARK_TK_OPERATOR_RIGHT_PARENTHESES, WMARK_PARSER_ACT_TK_OPERATOR_VERTICALLINE }, { TK_NULL, LA_NULL },
//base : vec text
{ WMARK_NT_base, WMARK_PARSER_ACT_TK_OPERATOR_TAG }, { WMARK_TK_VEC, WMARK_PARSER_ACT_NT_MI }, { WMARK_TK_TEXT, WMARK_PARSER_ACT_TK_VEC }, { TK_NULL, LA_NULL },
//base : bar text
{ WMARK_NT_base, WMARK_PARSER_ACT_TK_OPERATOR_TAG }, { WMARK_TK_BAR, WMARK_PARSER_ACT_NT_MI }, { WMARK_TK_TEXT, WMARK_PARSER_ACT_TK_BAR }, { TK_NULL, LA_NULL },
//line_element : WMARK_TK_IMAGE
{ WMARK_NT_text, WMARK_PARSER_ACT_block_element }, { WMARK_TK_IMAGE, WMARK_PARSER_ACT_TK_IMAGE }, { WMARK_NT_up, LA_NULL }, { TK_NULL, LA_NULL },
//text : WMARK_TK_ITALIC text WMARK_TK_ITALIC
{ WMARK_NT_text, WMARK_PARSER_ACT_TK_ITALIC }, { WMARK_TK_ITALIC, LA_NULL }, { WMARK_NT_text, LA_NULL }, { WMARK_TK_ITALIC, WMARK_PARSER_ACT_UP }, { TK_NULL, LA_NULL },
//text : WMARK_TK_BOLD text WMARK_TK_BOLD
{ WMARK_NT_text, WMARK_PARSER_ACT_TK_BOLD }, { WMARK_TK_BOLD, LA_NULL }, { WMARK_NT_text, LA_NULL }, { WMARK_TK_BOLD, WMARK_PARSER_ACT_UP }, { TK_NULL, LA_NULL },
//text : WMARK_TK_CODEINLINE CODETEXT WMARK_TK_CODEINLINE
{ WMARK_NT_text, WMARK_PARSER_ACT_TK_CODE }, { WMARK_TK_CODEINLINE, LA_NULL }, { WMARK_TK_CODETEXT, WMARK_PARSER_ACT_TK_TEXT }, { WMARK_TK_CODEINLINE, WMARK_PARSER_ACT_UP }, { TK_NULL, LA_NULL },
//text : codeinparagraph
{ WMARK_NT_text, WMARK_PARSER_ACT_block_element }, { WMARK_TK_CODEINPARAGRAPH, WMARK_PARSER_ACT_TK_CODE }, { WMARK_TK_CODETEXT, WMARK_PARSER_ACT_TK_TEXT }, { WMARK_TK_CODEINPARAGRAPH, WMARK_PARSER_ACT_UP }, { WMARK_NT_up, LA_NULL}, { TK_NULL, LA_NULL },
//text: WMARK_TK_TEXT
{ WMARK_NT_text, WMARK_PARSER_ACT_TK_TEXT }, { WMARK_TK_TEXT, LA_NULL }, { TK_NULL, LA_NULL },
//bold_text : text
{ WMARK_NT_bold_text, LA_NULL }, { WMARK_TK_TEXT, LA_NULL }, { TK_NULL, LA_NULL },
//italic_text : text
{ WMARK_NT_italic_text, LA_NULL }, { WMARK_TK_TEXT, LA_NULL }, { TK_NULL, LA_NULL },
//up : EPSILON
{ WMARK_NT_up, WMARK_PARSER_ACT_UP }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
//up : FOOBAR
{ WMARK_NT_up, WMARK_PARSER_ACT_UP }, { WMARK_TK_FOOBAR, LA_NULL }, { TK_NULL, LA_NULL },
//text_tail : text
{ WMARK_NT_text_tail, LA_NULL }, { WMARK_NT_text, LA_NULL }, { WMARK_NT_text_tail, LA_NULL }, { TK_NULL, LA_NULL },
//text_tail : TK_EPSILON
{ WMARK_NT_text_tail, LA_NULL }, { TK_EPSILON, LA_NULL }, { TK_NULL, LA_NULL },
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
	//TK_COMMENT
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkCommentAction>(std::make_shared<WmarkParserTkCommentAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_COMMENT, spAction);
	//block_element
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserBlockElementAction>(std::make_shared<WmarkParserBlockElementAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_block_element, spAction);
	//up
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserUPAction>(std::make_shared<WmarkParserUPAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_UP, spAction);
	//TK_TEXT
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkTextAction>(std::make_shared<WmarkParserTkTextAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_TEXT, spAction);
	//TK_INDENT
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkIndentAction>(std::make_shared<WmarkParserTkIndentAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_INDENT, spAction);
	//TK_ITALIC
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkItalicAction>(std::make_shared<WmarkParserTkItalicAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_ITALIC, spAction);
    //TK_Bold
    spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkBoldAction>(std::make_shared<WmarkParserTkBoldAction>());
    spAction->SetParameter(std::make_any<RdParserActionMetaData *>(pData));
    parser.AddAction(WMARK_PARSER_ACT_TK_BOLD, spAction);
    //TK_HEADING
    spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkHeadingAction>(std::make_shared<WmarkParserTkHeadingAction>());
    spAction->SetParameter(std::make_any<RdParserActionMetaData *>(pData));
    parser.AddAction(WMARK_PARSER_ACT_TK_HEADING, spAction);
	//TK_CODE
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkCodeAction>(std::make_shared<WmarkParserTkCodeAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_CODE, spAction);
	 //IMAGE
    spAction = std::static_pointer_cast<IRdParserAction, WmarkParserImageAction>(std::make_shared<WmarkParserImageAction>());
    spAction->SetParameter(std::make_any<RdParserActionMetaData *>(pData));
    parser.AddAction(WMARK_PARSER_ACT_TK_IMAGE, spAction);
	//NT_LI
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserLIAction>(std::make_shared<WmarkParserLIAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_NT_LI, spAction);
    //NT_OL
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserOLAction>(std::make_shared<WmarkParserOLAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_NT_OL, spAction);
	//NT_UL
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserULAction>(std::make_shared<WmarkParserULAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_NT_UL, spAction);
	//TK_Math
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkMathAction>(std::make_shared<WmarkParserTkMathAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_MATH, spAction);
	//Nt_MI
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserNtMIAction>(std::make_shared<WmarkParserNtMIAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_NT_MI, spAction);
	//Nt_MO
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserNtMOAction>(std::make_shared<WmarkParserNtMOAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_NT_MO, spAction);
	//Tk_math_identifier
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserMathTextAction>(std::make_shared<WmarkParserMathTextAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_MATH_TEXT, spAction);
	//MROW
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkMrowAction>(std::make_shared<WmarkParserTkMrowAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_MROW, spAction);
	//Operator_Caret
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkOperatorCaretAction>(std::make_shared<WmarkParserTkOperatorCaretAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_OPERATOR_MSUP, spAction);
	//Operator_Sqrt
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkOperatorTagAction>(std::make_shared<WmarkParserTkOperatorTagAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_OPERATOR_TAG, spAction);
	//Operator_Root
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkOperatorRootAction>(std::make_shared<WmarkParserTkOperatorRootAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_OPERATOR_ROOT, spAction);
	//Operator_Munderover
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkOperatorMunderoverAction>(std::make_shared<WmarkParserTkOperatorMunderoverAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_OPERATOR_MUNDEROVER, spAction);
	//Operator_Verticalline
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserTkOperatorVerticallineAction>(std::make_shared<WmarkParserTkOperatorVerticallineAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_OPERATOR_VERTICALLINE, spAction);
	//Operator_Vec
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserVecAction>(std::make_shared<WmarkParserVecAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_VEC, spAction);
	//Operator_Bars
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserBarAction>(std::make_shared<WmarkParserBarAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_TK_BAR, spAction);
	//Double-Struck
	spAction = std::static_pointer_cast<IRdParserAction, WmarkParserDoubleStruckAction>(std::make_shared<WmarkParserDoubleStruckAction>());
	spAction->SetParameter(std::make_any<RdParserActionMetaData*>(pData));
	parser.AddAction(WMARK_PARSER_ACT_DOUBLE_STRUCK, spAction);
}

void WmarkParserHelper::Start(RdParser& parser)
{
	parser.Start(WMARK_SCANNER_TK_ACTION, WMARK_TK_MAX);
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
