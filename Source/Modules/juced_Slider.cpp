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
	setProperty(Attributes::objectType, Modules::Label.toString());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	setProperty(Attributes::varName, getName());
	setProperty(Attributes::className, "Slider");
	setProperty(Attributes::declareExtended, false);

	setRange (0, 10, 0);
    setSliderStyle (Slider::Rotary);
    setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);

	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

