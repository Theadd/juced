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
    setSize (500, 400);
	setProperty(Ids::objectType, "component");
	setProperty(Ids::height, getHeight());
	setProperty(Ids::width, getWidth());
	setProperty(Ids::name, getName());
	setProperty(Ids::className, "juced_MainComponent");
	setComponentID(Uuid().toString());
	setProperty(Ids::ID, getComponentID());
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
