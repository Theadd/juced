/*
  ==============================================================================

    juced_Label.cpp
    Created: 3 Mar 2013 11:27:23pm
    Author:  admin

  ==============================================================================
*/

#include "juced_Label.h"

int juced_Label::_numObjects = 0; 

juced_Label::juced_Label()  : Label ()
{
	setText("Text label", false);
	setName("Label");
	setProperty(Attributes::objectType, Modules::Label.toString());
	setProperty(Attributes::text, getText());
	setProperty(Attributes::font, getFont().toString());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	setProperty(Attributes::textColour, findColour(textColourId).toDisplayString(true));
	setProperty(Attributes::showEditor, false);
	setProperty(Attributes::editable, false);
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
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