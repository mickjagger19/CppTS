/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////
#ifndef __WMARK_HTML_GENERATOR_H__
#define __WMARK_HTML_GENERATOR_H__
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkHtmlGeneratorHelper

class WmarkHtmlGeneratorHelper
{
public:
	static void InitActions(std::map<uint32_t, WmarkMetaDataTraversalAction>& map);

private:
	static WmarkMetaDataTraversalAction get_CommentGenerator();
	static WmarkMetaDataTraversalAction get_ParagraphGenerator();
	static WmarkMetaDataTraversalAction get_TextGenerator();
	static WmarkMetaDataTraversalAction get_IndentGenerator();
	static WmarkMetaDataTraversalAction get_ItalicGenerator();
	static WmarkMetaDataTraversalAction get_BoldGenerator();
	static WmarkMetaDataTraversalAction get_HeadingGenerator();
	static WmarkMetaDataTraversalAction get_CodeGenerator();
	static WmarkMetaDataTraversalAction get_ImageGenerator();
	static WmarkMetaDataTraversalAction get_OLGenerator();
	static WmarkMetaDataTraversalAction get_ULGenerator();
	static WmarkMetaDataTraversalAction get_LIGenerator();
	static WmarkMetaDataTraversalAction get_MathGenerator();
	static WmarkMetaDataTraversalAction get_TagGenerator();
	static WmarkMetaDataTraversalAction get_DoubleStruckGenerator();
};

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
