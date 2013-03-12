/*
  ==============================================================================

    BaseModules.h
    Created: 11 Mar 2013 7:49:07pm
    Author:  admin

  ==============================================================================
*/

#ifndef __BASEMODULES_H_E6ABB6F5__
#define __BASEMODULES_H_E6ABB6F5__

#include "../JuceLibraryCode/JuceHeader.h"

/*
namespace dTags
{
    const Identifier juced_Window       ("window");
    const Identifier juced_Component            ("component");
	const Identifier juced_Unknown            ("unknown");
}*/

namespace Ids
{
    #define DECLARE_ID(name)      const Identifier name (#name)

    DECLARE_ID (name);
    DECLARE_ID (file);
    DECLARE_ID (text);
    DECLARE_ID (width);
    DECLARE_ID (height);
	DECLARE_ID (className);
    DECLARE_ID (classDesc);
	DECLARE_ID (objectType);
	DECLARE_ID (object);

    const Identifier ID ("id");
    const Identifier class_ ("class");

    #undef DECLARE_ID
}

class juced_BaseWindow    : public DocumentWindow,
							public DynamicObject
{
public:

	juced_BaseWindow (String _name, Colour _colour, DocumentWindow::TitleBarButtons _buttons);

};




#endif  // __BASEMODULES_H_E6ABB6F5__
