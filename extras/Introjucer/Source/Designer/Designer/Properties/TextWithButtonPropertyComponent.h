/*
  ==============================================================================

    TextWithButtonPropertyComponent.cpp
    Created: 18 Mar 2013 1:03:13pm
    Author:  admin

  ==============================================================================
*/

#ifndef __TEXTWITHBUTTONPROPERTYCOMPONENT_H_E68AF029__
#define __TEXTWITHBUTTONPROPERTYCOMPONENT_H_E68AF029__

#include "../Globals.h"

/** Virtual PropertyComponent with small TextButton on the right.

This class cannot be declared directly, other classes inherits from this one.

Inherits TextPropertyComponent, Button::Listener.

Inherited by ColourPropertyComponent
*/
class TextWithButtonPropertyComponent  : public TextPropertyComponent,
										 public Button::Listener
{
public:
	/** Pointer to TextButton object. */
	TextButton *button;
	/** Pointer to Label object. */
	Label *textLabel;

	/** Creates a PropertyComponent with an editable Label and a TextButton on the right.
	@param ValueToControl Value reference to control.
	@param propertyName String containing the display name for this PropertyComponent.
	*/
    TextWithButtonPropertyComponent (const Value &ValueToControl, const String &propertyName);

	~TextWithButtonPropertyComponent();

	/** Virtual function called when the user clicks the TextButton. */
	virtual void buttonClicked (Button *button) = 0;

	/** Called automatically to resize child components.
	If reimplemented, use TextWithButtonPropertyComponent::resized() to inherit default resizing.
	*/
	void resized();
};

#endif  // __TEXTWITHBUTTONPROPERTYCOMPONENT_H_E68AF029__