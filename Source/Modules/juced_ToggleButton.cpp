/*
  ==============================================================================

    juced_ToggleButton.cpp
    Created: 27 May 2013 3:26:51am
    Author:  admin

  ==============================================================================
*/

#include "juced_ToggleButton.h"

int juced_ToggleButton::_numObjects = 0;

juced_ToggleButton::juced_ToggleButton()  : ToggleButton ()
{
	setName("ToggleButton");
	setButtonText("Toggle");
	setProperty(Attributes::objectType, Modules::TextButton.toString());
	setProperty(Attributes::buttonColour, findColour(TextButton::buttonColourId).toDisplayString(true));
	setProperty(Attributes::buttonOnColour, findColour(TextButton::buttonOnColourId).toDisplayString(true));
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::buttonText, getButtonText());
	//setProperty(Attributes::connectedEdges, getConnectedEdgeFlags());
	setProperty(Attributes::className, "ToggleButton");
	setProperty(Attributes::toolName, "juced_ToggleButton");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_ToggleButton::mouseUp (const MouseEvent& event) {}
void juced_ToggleButton::mouseDrag (const MouseEvent& event) {}
void juced_ToggleButton::mouseDoubleClick (const MouseEvent& event) {}
void juced_ToggleButton::mouseMove (const MouseEvent& event) {}
void juced_ToggleButton::mouseDown (const MouseEvent& event) {}
void juced_ToggleButton::mouseEnter (const MouseEvent& event) {}
void juced_ToggleButton::mouseExit (const MouseEvent& event) {}
void juced_ToggleButton::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}