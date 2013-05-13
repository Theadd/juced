/*
  ==============================================================================

    juced_ProgressBar.cpp
    Created: 13 May 2013 7:27:41am
    Author:  admin

  ==============================================================================
*/

#include "juced_ProgressBar.h"

int juced_ProgressBar::_numObjects = 0; 
double juced_ProgressBar::_progress = 0.5;


juced_ProgressBar::juced_ProgressBar()  : ProgressBar (_progress)
{
	//setText("Text label", false);
	setName("ProgressBar");
	setProperty(Attributes::objectType, Modules::Label.toString());
	//setProperty(Attributes::text, getText());
	//setProperty(Attributes::font, getFont().toString());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	//setProperty(Attributes::textColour, findColour(textColourId).toDisplayString(true));
	setProperty(Attributes::showEditor, false);
	setProperty(Attributes::editable, false);
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::className, "ProgressBar");
	setProperty(Attributes::toolName, "juced_ProgressBar");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_ProgressBar::mouseUp (const MouseEvent& event) {}
void juced_ProgressBar::mouseDrag (const MouseEvent& event) {}
void juced_ProgressBar::mouseDoubleClick (const MouseEvent& event) {}
void juced_ProgressBar::mouseMove (const MouseEvent& event) {}
void juced_ProgressBar::mouseDown (const MouseEvent& event) {}
void juced_ProgressBar::mouseEnter (const MouseEvent& event) {}
void juced_ProgressBar::mouseExit (const MouseEvent& event) {}
void juced_ProgressBar::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}