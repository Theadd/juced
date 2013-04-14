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
	setProperty(Attributes::varName, getName());
	setProperty(Attributes::className, "Label");
	setProperty(Attributes::toolName, "juced_Label");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_Label::mouseUp (const MouseEvent& event) {}
void juced_Label::mouseDrag (const MouseEvent& event) {}
void juced_Label::mouseDoubleClick (const MouseEvent& event) {}
void juced_Label::mouseMove (const MouseEvent& event) {}
void juced_Label::mouseDown (const MouseEvent& event) {}
void juced_Label::mouseEnter (const MouseEvent& event) {}
void juced_Label::mouseExit (const MouseEvent& event) {}
void juced_Label::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}