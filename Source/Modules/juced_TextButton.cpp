/*
  ==============================================================================

    juced_TextButton.cpp
    Created: 16 Mar 2013 12:39:06pm
    Author:  admin

  ==============================================================================
*/

#include "juced_TextButton.h"

juced_TextButton::juced_TextButton()  : TextButton ()
{
	setName("TextButton");
	setButtonText("Text Button");
	setProperty(Attributes::objectType, Modules::TextButton.toString());
	setProperty(Attributes::font, getFont().toString());
	setProperty(Attributes::buttonColour, findColour(TextButton::buttonColourId).toDisplayString(true));
	setProperty(Attributes::buttonOnColour, findColour(TextButton::buttonOnColourId).toDisplayString(true));
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	setProperty(Attributes::buttonText, getButtonText());
	setProperty(Attributes::connectedEdges, getConnectedEdgeFlags());
	setProperty(Attributes::className, "juced_TextButton");
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}
