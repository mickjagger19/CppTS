/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __WMARK_DEF_H__
#define __WMARK_DEF_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

//Action IDs for scanner
enum {
	WMARK_SCANNER_TK_ACTION = 1,
	WMARK_SCANNER_COMMENT_ACTION,
	WMARK_SCANNER_TEXT_ACTION,
};

//Token IDs
enum {
	WMARK_TK_RETURN = 1,
	WMARK_TK_COMMENT,
	WMARK_TK_INDENT,
	WMARK_TK_TEXT,
    WMARK_TK_HEADING,
	WMARK_TK_BOLD,
	WMARK_TK_ITALIC,
	WMARK_TK_MAX
};

//NT
enum {
	WMARK_NT_program = 501,
	WMARK_NT_return_list,
	WMARK_NT_r_body,
	WMARK_NT_b_body,
	WMARK_NT_block_element,
	WMARK_NT_be_tail,
	WMARK_NT_ber_tail,
	WMARK_NT_berr_tail,
	WMARK_NT_return_list_tail,
	WMARK_NT_line_element,
	WMARK_NT_text,
	WMARK_NT_text_tail,
};

//actions for parser
enum {
	WMARK_PARSER_ACT_program = 1,
	WMARK_PARSER_ACT_TK_COMMENT,
	WMARK_PARSER_ACT_block_element,
	WMARK_PARSER_ACT_UP,
	WMARK_PARSER_ACT_TK_TEXT,
	WMARK_PARSER_ACT_TK_INDENT,
	WMARK_PARSER_ACT_TK_ITALIC,
	WMARK_PARSER_ACT_TK_BOLD,
	WMARK_PARSER_ACT_TK_HEADING,
};

//meta types
enum {
	WMARK_NODETYPE_ROOT = 1,
	WMARK_NODETYPE_COMMENT,
	WMARK_NODETYPE_PARAGRAPH,
	WMARK_NODETYPE_TEXT,
	WMARK_NODETYPE_INDENT,
	WMARK_NODETYPE_ITALIC,
	WMARK_NODETYPE_BOLD,
	WMARK_NODETYPE_HEADING,
};

//meta data
#define WMARK_ROOT_SYMBOL  "document"

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
