/*
  ==============================================================================

    juced_Slider.cpp
    Created: 12 Apr 2013 4:02:39pm
    Author:  admin

  ==============================================================================
*/

#include "juced_Slider.h"

juced_Slider::juced_Slider()  : Slider ()
{
	setName("slider");
	setProperty(Attributes::objectType, Modules::Slider.toString());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	setProperty(Attributes::varName, getName());
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

