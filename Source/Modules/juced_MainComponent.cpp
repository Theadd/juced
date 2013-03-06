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
}

juced_MainComponent::~juced_MainComponent()
{
}

void juced_MainComponent::paint (Graphics& g)
{
    g.fillAll (Colour((uint8) 0, (uint8) 245, (uint8) 0));

}

void juced_MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

bool juced_MainComponent::isChildAllowed () {
	return true;
}