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
	setName("textButton");
	setButtonText("Text Button");
	setProperty(Attributes::objectType, Modules::TextButton.toString());
	setProperty(Attributes::font, getFont().toString());
	setProperty(Attributes::buttonColour, findColour(TextButton::buttonColourId).toDisplayString(true));
	setProperty(Attributes::buttonOnColour, findColour(TextButton::buttonOnColourId).toDisplayString(true));
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	setProperty(Attributes::varName, getName());
	setProperty(Attributes::buttonText, getButtonText());
	setProperty(Attributes::connectedEdges, getConnectedEdgeFlags());
	setProperty(Attributes::className, "TextButton");
	setProperty(Attributes::toolName, "juced_TextButton");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_TextButton::mouseUp (const MouseEvent& event) {}
void juced_TextButton::mouseDrag (const MouseEvent& event) {}
void juced_TextButton::mouseDoubleClick (const MouseEvent& event) {}
void juced_TextButton::mouseMove (const MouseEvent& event) {}
void juced_TextButton::mouseDown (const MouseEvent& event) {}
void juced_TextButton::mouseEnter (const MouseEvent& event) {}
void juced_TextButton::mouseExit (const MouseEvent& event) {}
void juced_TextButton::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}