/*
  ==============================================================================

    juced_ImageComponent.cpp
    Created: 26 May 2013 3:58:03am
    Author:  admin

  ==============================================================================
*/

#include "juced_ImageComponent.h"

int juced_ImageComponent::_numObjects = 0; 

juced_ImageComponent::juced_ImageComponent()  : ImageComponent ()
{
	setName("ImageComponent");
	setProperty(Attributes::objectType, Modules::ImageComponent.toString());
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::image, "");
	setProperty(Attributes::className, "ImageComponent");
	setProperty(Attributes::toolName, "juced_ImageComponent");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

void juced_ImageComponent::mouseUp (const MouseEvent& event) {}
void juced_ImageComponent::mouseDrag (const MouseEvent& event) {}
void juced_ImageComponent::mouseDoubleClick (const MouseEvent& event) {}
void juced_ImageComponent::mouseMove (const MouseEvent& event) {}
void juced_ImageComponent::mouseDown (const MouseEvent& event) {}
void juced_ImageComponent::mouseEnter (const MouseEvent& event) {}
void juced_ImageComponent::mouseExit (const MouseEvent& event) {}
void juced_ImageComponent::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}