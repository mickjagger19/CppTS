/*
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

WmarkMetaDataTraversalAction WmarkHtmlGeneratorHelper::get_ImageGenerator()
{
    // ![title](link)
    // <img src="link" alt="title" />
	return [](bool bOpen, RdMetaData& data, RdMetaDataPosition pos, std::ostream& stm)->bool
			{
	            std::string img = (const char*)data.GetData(pos);
				stm << "<img src=\"" << img.substr(img.find_last_of('(') + 1, img.length() - img.find_last_of('(') - 2);
                stm <<"\" alt=\"" << img.substr(2, img.find_last_of(']') - img.find_first_of('[') - 1) << "\" />";
                return true;
			};
}

////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
