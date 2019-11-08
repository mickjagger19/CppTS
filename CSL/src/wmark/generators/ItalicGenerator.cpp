﻿/*
** Xin YUAN, 2019, BSD (2)
*/

////////////////////////////////////////////////////////////////////////////////

#include "precomp.h"

#include "../WmarkHtmlGenerator.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
namespace CSL {
////////////////////////////////////////////////////////////////////////////////

// WmarkHtmlGeneratorHelper

WmarkMetaDataTraversalAction WmarkHtmlGeneratorHelper::get_ItalicGenerator()
{
	return [](bool bOpen, RdMetaData& data, RdMetaDataPosition pos, std::ostream& stm)->bool
			{
				stm << (bOpen ? "\r\n" : "") <<  '<' << (bOpen ? "" : "/") << "em>" << (bOpen ? "" : "\r\n") ;
				return true;
			};
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
