/*
  ==============================================================================

    juced_Component.cpp
    Created: 15 May 2013 4:26:01pm
    Author:  admin

  ==============================================================================
*/

#include "juced_Component.h"

int juced_Component::_numObjects = 0; 

juced_Component::juced_Component()
{
    //setSize (500, 400);
	setName("Component");
	setProperty(Attributes::objectType, Modules::Component.toString());
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	++_numObjects;
	setProperty(Attributes::varName, getName() + String(_numObjects));
	setProperty(Attributes::className, "Component");
	setProperty(Attributes::toolName, "juced_Component");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

juced_Component::~juced_Component()
{
}

/*void juced_MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentWhite);

}*/

void juced_Component::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void juced_Component::mouseUp (const MouseEvent& event) {}
void juced_Component::mouseDrag (const MouseEvent& event) {}
void juced_Component::mouseDoubleClick (const MouseEvent& event) {}
void juced_Component::mouseMove (const MouseEvent& event) {}
void juced_Component::mouseDown (const MouseEvent& event) {}
void juced_Component::mouseEnter (const MouseEvent& event) {}
void juced_Component::mouseExit (const MouseEvent& event) {}
void juced_Component::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}