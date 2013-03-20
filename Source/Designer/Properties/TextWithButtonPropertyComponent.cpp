/*
  ==============================================================================

    TextWithButtonPropertyComponent.cpp
    Created: 18 Mar 2013 1:20:48pm
    Author:  admin

  ==============================================================================
*/

#include "TextWithButtonPropertyComponent.h"

TextWithButtonPropertyComponent::TextWithButtonPropertyComponent (const Value &ValueToControl, const String &propertyName) : TextPropertyComponent(ValueToControl, propertyName, 96, false)
{
	textLabel = (Label *) this->getChildComponent(0);
	button = new TextButton("...");
	addAndMakeVisible(button);
	button->setConnectedEdges((int)(TextButton::ConnectedOnRight | TextButton::ConnectedOnLeft));
	button->addListener(this);
	resized();
}

TextWithButtonPropertyComponent::~TextWithButtonPropertyComponent()
{
	button->removeListener(this);
}

void TextWithButtonPropertyComponent::resized()
{
	TextPropertyComponent::resized();
	textLabel->setSize(getWidth() - textLabel->getHeight() - textLabel->getX() - 2, textLabel->getHeight());
    button->setBounds(getWidth() - textLabel->getHeight() - 1, textLabel->getY(), textLabel->getHeight(), textLabel->getHeight());
}
