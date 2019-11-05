/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "WmarkHtmlGenerator.h"

#include "base/WmarkDef.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkHtmlGeneratorHelper

void WmarkHtmlGeneratorHelper::InitActions(std::map<uint32_t, WmarkMetaDataTraversalAction>& map)
{
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_COMMENT, std::move(get_CommentGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_PARAGRAPH, std::move(get_ParagraphGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_TEXT, std::move(get_TextGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_INDENT, std::move(get_IndentGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_HEADING, std::move(get_HeadingGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_ITALIC, std::move(get_ItalicGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_BOLD, std::move(get_BoldGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_CODE, std::move(get_CodeGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_IMAGE, std::move(get_ImageGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_OL, std::move(get_OLGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_UL, std::move(get_ULGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_LI, std::move(get_LIGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_MATH, std::move(get_MathGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_TAG, std::move(get_TagGenerator())));
	map.insert(std::pair<uint32_t, WmarkMetaDataTraversalAction>(WMARK_NODETYPE_DOUBLE_STRUCK, std::move(get_DoubleStruckGenerator())));
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
