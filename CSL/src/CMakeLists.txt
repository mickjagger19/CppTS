#
# Xin YUAN, 2019, BSD (2)
#

# target

INCLUDE_DIRECTORIES(
	"${CMAKE_CURRENT_BINARY_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/public"
	"${PROJECT_SOURCE_DIR}/src"
	)
ADD_DEFINITIONS(${STRING_CXX_FLAGS})

SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(SRC_PCH_LIST "precomp.cpp")
SET(SRC_LIST "cslbase.cpp" "cslsys.cpp" "cslrdp.cpp" "cslwmark.cpp"
	"wmark/scan_actions/tk_action.cpp" "wmark/scan_actions/comment_action.cpp" "wmark/scan_actions/text_action.cpp"
	"wmark/scan_actions/codetext_action.cpp" "wmark/scan_actions/image_action.cpp" "wmark/scan_actions/ol_action.cpp" "wmark/scan_actions/asciimath_action.cpp"
    "wmark/parser_actions/accepted_action.cpp" "wmark/parser_actions/block_element_action.cpp" "wmark/parser_actions/program_action.cpp"
	"wmark/parser_actions/tk_bold_action.cpp" "wmark/parser_actions/tk_code_action.cpp" "wmark/parser_actions/image_action.cpp"
	"wmark/parser_actions/tk_comment_action.cpp" "wmark/parser_actions/tk_heading_action.cpp"
	"wmark/parser_actions/tk_indent_action.cpp" "wmark/parser_actions/tk_italic_action.cpp" "wmark/parser_actions/tk_text_action.cpp" "wmark/parser_actions/li_action.cpp" "wmark/parser_actions/ol_action.cpp"
	"wmark/parser_actions/up_action.cpp" "wmark/parser_actions/ul_action.cpp" 	"wmark/parser_actions/tk_math_action.h" "wmark/parser_actions/tk_math_action.cpp"
	"wmark/parser_actions/nt_mi_action.cpp" "wmark/parser_actions/nt_mo_action.cpp" "wmark/parser_actions/tk_math_text_action.cpp" "wmark/parser_actions/tk_mrow_action.cpp"
	"wmark/parser_actions/tk_operator_caret_action.cpp" "wmark/parser_actions/tk_operator_tag_action.cpp" "wmark/parser_actions/tk_operator_root_action.cpp"
	"wmark/parser_actions/tk_operator_munderover_action.cpp" "wmark/parser_actions/tk_operator_verticalline_action.cpp" "wmark/parser_actions/tk_vec_action.cpp"
		"wmark/parser_actions/double_struck_action.cpp" "wmark/parser_actions/tk_bar_action.cpp"
	"wmark/generators/BoldGenerator.cpp" "wmark/generators/CommentGenerator.cpp" "wmark/generators/ParagraphGenerator.cpp" "wmark/generators/TextGenerator.cpp"
	"wmark/generators/IndentGenerator.cpp" "wmark/generators/ItalicGenerator.cpp" "wmark/generators/HeadingGenerator.cpp" "wmark/generators/CodeGenerator.cpp"
    "wmark/generators/ImageGenerator.cpp" "wmark/generators/OLGenerator.cpp" "wmark/generators/LIGenerator.cpp" "wmark/generators/ULGenerator.cpp"
	"wmark/generators/MathGenerator.cpp" "wmark/generators/TagGenerator.cpp" "wmark/generators/DoubleStruckGenerator.cpp"
	"wmark/WmarkScanner.cpp" "wmark/WmarkParser.cpp" "wmark/WmarkHtmlGenerator.cpp"
	)
ADD_LIBRARY(CSL-Utility STATIC ${SRC_PCH_LIST} ${SRC_LIST})
SET_PCH(CSL-Utility "exe" "precomp.h" ${SRC_PCH_LIST} ${SRC_LIST})
SET_TARGET_PROPERTIES(CSL-Utility PROPERTIES
	OUTPUT_NAME "CSL-Utility"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET}")
TARGET_LINK_LIBRARIES(CSL-Utility ${STRING_LINK_EXTRA_LIBS})

# end
