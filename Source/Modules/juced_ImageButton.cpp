/*
  ==============================================================================

    juced_ImageButton.cpp
    Created: 13 Apr 2013 10:07:27pm
    Author:  admin

  ==============================================================================
*/

#include "juced_ImageButton.h"

int juced_ImageButton::_numObjects = 0; 

juced_ImageButton::juced_ImageButton()  : ImageButton ()
{
	setName("ImageButton");
	setProperty(Attributes::objectType, Modules::ImageButton.toString());
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::normalImage, "");
	setProperty(Attributes::overImage, "");
	setProperty(Attributes::downImage, "");
	setProperty(Attributes::className, "ImageButton");
	setProperty(Attributes::toolName, "juced_ImageButton");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_ImageButton::mouseUp (const MouseEvent& event) {}
void juced_ImageButton::mouseDrag (const MouseEvent& event) {}
void juced_ImageButton::mouseDoubleClick (const MouseEvent& event) {}
void juced_ImageButton::mouseMove (const MouseEvent& event) {}
void juced_ImageButton::mouseDown (const MouseEvent& event) {}
void juced_ImageButton::mouseEnter (const MouseEvent& event) {}
void juced_ImageButton::mouseExit (const MouseEvent& event) {}
void juced_ImageButton::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}