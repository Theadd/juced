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

namespace ValueType
{
	const Identifier text		("text");
	const Identifier integer	("integer");
	const Identifier rgba		("rgba");
}

namespace Modules
{
    const Identifier Window       ("Window");
    const Identifier Component    ("Component");
	const Identifier Label        ("Label");
	const Identifier TextButton   ("TextButton");
    const Identifier Unknown	  ("Unknown");
}

namespace AttributeType
{
    const Identifier text       ("text");
    const Identifier textarea    ("textarea");
	const Identifier font        ("font");
    const Identifier colour	  ("colour");
}

namespace Attributes
{
    #define DECLARE_ID(name)      const Identifier name (#name)

    DECLARE_ID (name);
    DECLARE_ID (file);
    DECLARE_ID (text);
	DECLARE_ID (buttonText);
    DECLARE_ID (width);
    DECLARE_ID (height);
    DECLARE_ID (x);
    DECLARE_ID (y);
	DECLARE_ID (font);
	DECLARE_ID (backgroundColour);
	//const Identifier backgroundColour ("Background colour");
	DECLARE_ID (textColour);
	DECLARE_ID (buttonColour);
	DECLARE_ID (buttonOnColour);
	DECLARE_ID (className);
    DECLARE_ID (classDesc);
	DECLARE_ID (objectType);
	DECLARE_ID (object);

    const Identifier ID ("id");
    const Identifier class_ ("class");

    #undef DECLARE_ID

	inline bool isVisibleAsProperty (Identifier _name)
	{
		return (_name == Attributes::name ||
			_name == Attributes::text ||
			_name == Attributes::buttonText ||
			_name == Attributes::font ||
			_name == Attributes::backgroundColour ||
			_name == Attributes::textColour ||
			_name == Attributes::buttonColour ||
			_name == Attributes::buttonOnColour ||
			_name == Attributes::x ||
			_name == Attributes::y ||
			_name == Attributes::width ||
			_name == Attributes::height );
	}

	inline Identifier getAttributeType (Identifier _name)
	{
		if (_name.toString().containsIgnoreCase("colour")) {
			return AttributeType::colour;
		} else {
			return AttributeType::text;
		}
		//return ((_name == Attributes::backgroundColour || _name == Attributes::textColour) ? AttributeType::colour : AttributeType::text);
	}

}

/*
namespace Misc
{
	inline Colour getColourFromStringDisplay (String _colour)
	{
		int i = _colour.getHexValue32();
		return Colour::fromRGBA(i & 4278190080, i & 16711680, i & 65280, i & 255);

	}
}*/

#endif   // __GLOBALS_H_4F86195D__