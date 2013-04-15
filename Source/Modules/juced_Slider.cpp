/*
  ==============================================================================

    juced_Slider.cpp
    Created: 12 Apr 2013 4:02:39pm
    Author:  admin

  ==============================================================================
*/

#include "juced_Slider.h"

int juced_Slider::_numObjects = 0; 

juced_Slider::juced_Slider()  : Slider ()
{
	setName("Slider");
	setProperty(Attributes::objectType, Modules::Slider.toString());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::className, "Slider");
	setProperty(Attributes::toolName, "juced_Slider");
	setProperty(Attributes::declareExtended, false);

	setRange (0, 10, 0);
	setProperty(Attributes::minimum, 0);
	setProperty(Attributes::maximum, 10);
	setProperty(Attributes::interval, 0);
	setProperty(Attributes::value, getValue());
    setSliderStyle (Slider::LinearHorizontal);
    setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
	setProperty(Attributes::textEntryBoxWidth, 80);
	setProperty(Attributes::textEntryBoxHeight, 20);
	setProperty(Attributes::textBoxReadOnly, false);
	setProperty(Attributes::textEntryBoxPosition, "NoTextBox");
	setProperty(Attributes::sliderStyle, "LinearHorizontal");

	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_Slider::mouseUp (const MouseEvent& event) {}
void juced_Slider::mouseDrag (const MouseEvent& event) {}
void juced_Slider::mouseDoubleClick (const MouseEvent& event) {}
void juced_Slider::mouseMove (const MouseEvent& event) {}
void juced_Slider::mouseDown (const MouseEvent& event) {}
void juced_Slider::mouseEnter (const MouseEvent& event) {}
void juced_Slider::mouseExit (const MouseEvent& event) {}
void juced_Slider::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}