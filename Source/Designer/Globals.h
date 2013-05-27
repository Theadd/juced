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

struct Choices
{
	StringArray names;
	StringArray display;
	Array<var> values;
};

struct Enumeration
{
	String name;
	String display;
	int value;
};

struct Attribute
{
	Identifier name;
	String group;
	bool visible;
	Identifier type;
	String display;
	Identifier valueType;
	String syntax;
};

namespace ValueType
{
	const Identifier text		("text");
	const Identifier integer	("integer");
	const Identifier rgba		("rgba");
	const Identifier undefined		("undefined");
}

namespace Modules
{
    const Identifier Window       ("Window");
    const Identifier Component    ("Component");
	const Identifier Label        ("Label");
	const Identifier TextButton   ("TextButton");
	const Identifier Slider		  ("Slider");
	const Identifier ImageButton  ("ImageButton");
    const Identifier ComboBox	  ("ComboBox");
	const Identifier ListBox	  ("ListBox");
	const Identifier ProgressBar  ("ProgressBar");
	const Identifier BubbleComponent	  ("BubbleComponent");
	const Identifier DirectShowComponent	  ("DirectShowComponent");
	const Identifier Viewport  ("Viewport");
	const Identifier ImageComponent  ("ImageComponent");
	const Identifier ToggleButton  ("ToggleButton");
    const Identifier Unknown	  ("Unknown");
}

namespace AttributeType
{
    const Identifier text			("text");
    const Identifier textarea		("textarea");
	const Identifier font			("font");
    const Identifier colour			("colour");
	const Identifier enumeration	("enumeration");
	const Identifier boolean		("boolean");
	const Identifier choice			("choice");
	const Identifier file			("file");
}

namespace Attributes
{
    #define DECLARE_ID(name)      const Identifier name (#name)

    DECLARE_ID (name);
	DECLARE_ID (varName);
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
	DECLARE_ID (normalImage);
	DECLARE_ID (overImage);
	DECLARE_ID (downImage);
	DECLARE_ID (image);
	//combobox
	DECLARE_ID (itemList);
	//label
	DECLARE_ID (editable);
	DECLARE_ID (showEditor);

	DECLARE_ID (allowTransform);
	DECLARE_ID (declareExtended);

	DECLARE_ID (lookAndFeel);
	DECLARE_ID (toolName);	//specific property of the editor to be able to import an exported object from this tool name
	DECLARE_ID (contentOwner);	//set whether or not the component must own it child component
	DECLARE_ID (castMouseEvents);

	DECLARE_ID (textEntryBoxPosition);
	DECLARE_ID (sliderStyle);
	DECLARE_ID (textEntryBoxWidth);
	DECLARE_ID (textEntryBoxHeight);
	DECLARE_ID (textBoxReadOnly);
	DECLARE_ID (minimum);
	DECLARE_ID (maximum);
	DECLARE_ID (interval);
	DECLARE_ID (value);

	DECLARE_ID (movie);
	DECLARE_ID (scrollBarThickness);
	DECLARE_ID (contentViewed);
	DECLARE_ID (usingNativeTitleBar);

	DECLARE_ID (textColour);
	DECLARE_ID (buttonColour);
	DECLARE_ID (buttonOnColour);
	DECLARE_ID (connectedEdges);
	DECLARE_ID (titleBarButtons);
	DECLARE_ID (titleBarButtonsOnLeft);
	DECLARE_ID (titleBarHeight);
	DECLARE_ID (titleBarTextCentered);
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