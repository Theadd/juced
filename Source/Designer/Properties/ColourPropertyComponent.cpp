/*
  ==============================================================================

    ColourPropertyComponent.cpp
    Created: 18 Mar 2013 1:02:53pm
    Author:  admin

  ==============================================================================
*/

#include "../Globals.h"
#include "TextWithButtonPropertyComponent.h"

/** PropertyComponent that shows a CallOutBox with a ColourSelector in it.

	Used to allow the user change Colour Attributes from fomponents

	Inherits TextWithButtonPropertyComponent, ChangeListener.
*/
class ColourPropertyComponent  : public TextWithButtonPropertyComponent,
								 public ChangeListener
{
public:
	Colour colour;

	/** Creates a colour selector property component

        @see ColourSelector, TextWithButtonPropertyComponent
		@param ValueToControl Value reference to control.
		@param propertyName String containing the display name for this PropertyComponent.
    */
	ColourPropertyComponent (const Value &ValueToControl, const String &propertyName) : TextWithButtonPropertyComponent(ValueToControl, propertyName)
    {
		Colour colour = Colour::fromString(ValueToControl.toString());	//Misc::getColourFromStringDisplay(ValueToControl.toString());
		textLabel->setColour(Label::backgroundColourId, colour);
		textLabel->setColour(Label::textColourId, colour.withAlpha(1.0f).contrasting(1.0f));
		textLabel->setText(colour.toDisplayString(true), false);
	}

	/** Called when the user clicks the button. */
	void buttonClicked (Button *buttonThatWasClicked)
	{
		if (buttonThatWasClicked != this->button) return;

        ColourSelector* colourSelector = new ColourSelector();
        colourSelector->setName ("background");
        colourSelector->setCurrentColour (colour);
        colourSelector->addChangeListener (this);
        colourSelector->setColour (ColourSelector::backgroundColourId, Colours::transparentBlack);
        colourSelector->setSize (300, 400);

        CallOutBox::launchAsynchronously (colourSelector, getScreenBounds(), nullptr);
	}

	/** Called whenever the colour within the ColourSelector changes. */
	void changeListenerCallback (ChangeBroadcaster *source)
	{
		ColourSelector* cs = dynamic_cast <ColourSelector*> (source);
		colour = cs->getCurrentColour();
		textLabel->setColour(Label::backgroundColourId, colour);
		textLabel->setColour(Label::textColourId, colour.withAlpha(1.0f).contrasting(1.0f));
		textLabel->setText(colour.toDisplayString(true), false);
	}

};