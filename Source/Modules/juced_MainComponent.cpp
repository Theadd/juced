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
	setName("component");
	setProperty(Attributes::objectType, "Component");
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::name, getName());
	setProperty(Attributes::className, "juced_MainComponent");
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());
}

juced_MainComponent::~juced_MainComponent()
{
}

void juced_MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::white);

}

void juced_MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
