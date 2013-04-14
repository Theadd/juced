/*
  ==============================================================================

    juced_ImageButton.cpp
    Created: 13 Apr 2013 10:07:27pm
    Author:  admin

  ==============================================================================
*/

#include "juced_ImageButton.h"

juced_ImageButton::juced_ImageButton()  : ImageButton ()
{
	setName("imageButton");
	setProperty(Attributes::objectType, Modules::ImageButton.toString());
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	setProperty(Attributes::varName, getName());
	setProperty(Attributes::normalImage, "Image()");
	setProperty(Attributes::overImage, "Image()");
	setProperty(Attributes::downImage, "Image()");
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