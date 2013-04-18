/*
  ==============================================================================

    juced_ComboBox.cpp
    Created: 17 Apr 2013 11:22:20pm
    Author:  admin

  ==============================================================================
*/

#include "juced_ComboBox.h"

int juced_ComboBox::_numObjects = 0; 

juced_ComboBox::juced_ComboBox()  : ComboBox ()
{
	setText("ComboBox", false);
	setName("Box");
	setProperty(Attributes::objectType, Modules::ComboBox.toString());
	setProperty(Attributes::text, getText());
	//setProperty(Attributes::font, getFont().toString());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	setProperty(Attributes::textColour, findColour(textColourId).toDisplayString(true));
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::className, "ComboBox");
	setProperty(Attributes::toolName, "juced_ComboBox");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_ComboBox::mouseUp (const MouseEvent& event) {}
void juced_ComboBox::mouseDrag (const MouseEvent& event) {}
void juced_ComboBox::mouseDoubleClick (const MouseEvent& event) {}
void juced_ComboBox::mouseMove (const MouseEvent& event) {}
void juced_ComboBox::mouseDown (const MouseEvent& event) {}
void juced_ComboBox::mouseEnter (const MouseEvent& event) {}
void juced_ComboBox::mouseExit (const MouseEvent& event) {}
void juced_ComboBox::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}