/*
  ==============================================================================

    juced_Viewport.cpp
    Created: 23 May 2013 1:31:16am
    Author:  admin

  ==============================================================================
*/

#include "juced_Viewport.h"

int juced_Viewport::_numObjects = 0; 

juced_Viewport::juced_Viewport()  : Viewport ()
{
	setName("Viewport");
	setProperty(Attributes::objectType, Modules::Viewport.toString());
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::className, "Viewport");
	setProperty(Attributes::toolName, "juced_Viewport");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());

	setProperty(Attributes::contentViewed, true);
	setProperty(Attributes::scrollBarThickness, getScrollBarThickness());
	setScrollBarsShown(true, false);
}

void juced_Viewport::paint (Graphics& g)
{
    //g.fillAll (Colour((uint8) 245, (uint8) 245, (uint8) 245));
	//g.fillAll (Colour((uint8) 40, (uint8) 121, (uint8) 208));
}

void juced_Viewport::mouseUp (const MouseEvent& event) {}
void juced_Viewport::mouseDrag (const MouseEvent& event) {}
void juced_Viewport::mouseDoubleClick (const MouseEvent& event) {}
void juced_Viewport::mouseMove (const MouseEvent& event) {}
void juced_Viewport::mouseDown (const MouseEvent& event) {}
void juced_Viewport::mouseEnter (const MouseEvent& event) {}
void juced_Viewport::mouseExit (const MouseEvent& event) {}
void juced_Viewport::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}

