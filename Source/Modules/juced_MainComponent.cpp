/*
  ==============================================================================

    juced_MainComponent.cpp
    Created: 3 Mar 2013 2:44:43pm
    Author:  admin

  ==============================================================================
*/

#include "juced_MainComponent.h"

juced_MainComponent::juced_MainComponent()
{
    //setSize (500, 400);
	setName("container");
	setProperty(Attributes::objectType, Modules::Component.toString());
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	setProperty(Attributes::varName, getName());
	setProperty(Attributes::className, "Component");
	setProperty(Attributes::toolName, "juced_MainComponent");
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
	setProperty(Attributes::allowTransform, false);
}

juced_MainComponent::~juced_MainComponent()
{
}

/*void juced_MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentWhite);

}*/

void juced_MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void juced_MainComponent::mouseUp (const MouseEvent& event) {}
void juced_MainComponent::mouseDrag (const MouseEvent& event) {}
void juced_MainComponent::mouseDoubleClick (const MouseEvent& event) {}
void juced_MainComponent::mouseMove (const MouseEvent& event) {}
void juced_MainComponent::mouseDown (const MouseEvent& event) {}
void juced_MainComponent::mouseEnter (const MouseEvent& event) {}
void juced_MainComponent::mouseExit (const MouseEvent& event) {}
void juced_MainComponent::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}