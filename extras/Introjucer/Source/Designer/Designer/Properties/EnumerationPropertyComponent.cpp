/*
  ==============================================================================

    EnumerationPropertyComponent.cpp
    Created: 22 Mar 2013 5:04:07pm
    Author:  admin

  ==============================================================================
*/

/*
  ==============================================================================

    ColourPropertyComponent.cpp
    Created: 18 Mar 2013 1:02:53pm
    Author:  admin

  ==============================================================================
*/

#include "../Globals.h"
#include "TextWithButtonPropertyComponent.h"

/** PropertyComponent that shows a multiple selection popup.

	Used to allow the user set an enum based property

	Inherits TextWithButtonPropertyComponent.
*/
class EnumerationPropertyComponent  : public TextWithButtonPropertyComponent
{
public:

	/** Creates a multiple selection property component from an array of Enumeration (struct) objects

        @see TextWithButtonPropertyComponent, Constructor::getEnumerationsOf, Enumeration

		@param ValueToControl Value reference to control.
		@param propertyName String containing the display name for this PropertyComponent.
		@param enumerations Array<Enumeration*> pointer to Enumeration list.
    */
	EnumerationPropertyComponent (const Value &ValueToControl, const String &propertyName, Array<Enumeration*> *enumerations) : TextWithButtonPropertyComponent(ValueToControl, propertyName), _enumerations(enumerations)
    {

	}

	/** Called when the user clicks the button. 
	
	Shows a popup containing the ticked enumerations.
	*/
	void buttonClicked (Button *buttonThatWasClicked)
	{
		if (buttonThatWasClicked != this->button) return;

		PopupMenu popup;
		bool ticked = false;
		for (int i = _enumerations->size(); --i >= 0;) {
			Enumeration* e = _enumerations->getUnchecked(i);
			if ((int)(getText().getIntValue() & e->value) > 0) {
				ticked = true;
			} else {
				ticked = false;
			}
			popup.addItem(e->value, e->display, true, ticked);
		}

		textLabel->setText(String(getText().getIntValue() ^ popup.show()), false);
	}

private:
	Array<Enumeration*> *_enumerations;

};