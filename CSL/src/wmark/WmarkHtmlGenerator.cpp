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
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
