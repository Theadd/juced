/*
  ==============================================================================

    Globals.h
    Created: 13 Mar 2013 5:51:46pm
    Author:  admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#ifndef __GLOBALS_H_4F86195D__
#define __GLOBALS_H_4F86195D__

namespace Modules
{
    const Identifier Window       ("Window");
    const Identifier Component    ("Component");
	const Identifier Label        ("Label");
    const Identifier Unknown	  ("Unknown");
}

namespace Attributes
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

	inline bool isVisibleAsProperty (Identifier _name)
	{
		return (_name == Attributes::name |
			_name == Attributes::text |
			_name == Attributes::width |
			_name == Attributes::height );
	}

}

#endif   // __GLOBALS_H_4F86195D__