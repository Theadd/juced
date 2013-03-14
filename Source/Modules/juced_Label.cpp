/*
  ==============================================================================

    juced_Label.cpp
    Created: 3 Mar 2013 11:27:23pm
    Author:  admin

  ==============================================================================
*/

#include "juced_Label.h"

juced_Label::juced_Label()  : Label ()
{
	setText("Text label", false);
	setName("label");
	setProperty(Attributes::objectType, Modules::Label.toString());
	setProperty(Attributes::text, getText());
	setProperty(Attributes::font, getFont().toString());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	setProperty(Attributes::textColour, findColour(textColourId).toDisplayString(true));
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	setProperty(Attributes::className, "juced_Label");
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

