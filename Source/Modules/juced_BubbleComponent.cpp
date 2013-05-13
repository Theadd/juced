/*
  ==============================================================================

    juced_BubbleComponent.cpp
    Created: 13 May 2013 7:27:55am
    Author:  admin

  ==============================================================================
*/

#include "juced_BubbleComponent.h"

int juced_BubbleMessageComponent::_numObjects = 0; 

juced_BubbleMessageComponent::juced_BubbleMessageComponent()  : BubbleMessageComponent ()
{
	//setText("Text label", false);
	//setName("Label");
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
	setProperty(Attributes::className, "BubbleMessageComponent");
	setProperty(Attributes::toolName, "juced_BubbleMessageComponent");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_BubbleMessageComponent::mouseUp (const MouseEvent& event) {}
void juced_BubbleMessageComponent::mouseDrag (const MouseEvent& event) {}
void juced_BubbleMessageComponent::mouseDoubleClick (const MouseEvent& event) {}
void juced_BubbleMessageComponent::mouseMove (const MouseEvent& event) {}
void juced_BubbleMessageComponent::mouseDown (const MouseEvent& event) {}
void juced_BubbleMessageComponent::mouseEnter (const MouseEvent& event) {}
void juced_BubbleMessageComponent::mouseExit (const MouseEvent& event) {}
void juced_BubbleMessageComponent::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}