/*
  ==============================================================================

    juced_DirectShowComponent.cpp
    Created: 22 May 2013 10:53:46pm
    Author:  admin

  ==============================================================================
*/

#include "juced_DirectShowComponent.h"

int juced_DirectShowComponent::_numObjects = 0; 

juced_DirectShowComponent::juced_DirectShowComponent()   : Component()
{
	setName("DirectShow");
	setProperty(Attributes::objectType, Modules::Label.toString());
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::className, "DirectShowComponent");
	setProperty(Attributes::toolName, "juced_DirectShowComponent");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
	setProperty(Attributes::movie, String::empty);
}

void juced_DirectShowComponent::mouseUp (const MouseEvent& event) {}
void juced_DirectShowComponent::mouseDrag (const MouseEvent& event) {}
void juced_DirectShowComponent::mouseDoubleClick (const MouseEvent& event) {}
void juced_DirectShowComponent::mouseMove (const MouseEvent& event) {}
void juced_DirectShowComponent::mouseDown (const MouseEvent& event) {}
void juced_DirectShowComponent::mouseEnter (const MouseEvent& event) {}
void juced_DirectShowComponent::mouseExit (const MouseEvent& event) {}
void juced_DirectShowComponent::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}
