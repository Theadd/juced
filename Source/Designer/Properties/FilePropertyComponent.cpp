/*
  ==============================================================================

    FilePropertyComponent.cpp
    Created: 13 Apr 2013 10:18:02pm
    Author:  admin

  ==============================================================================
*/

#include "../Globals.h"
#include "TextWithButtonPropertyComponent.h"

/** PropertyComponent that shows a File selector dialog.

	Inherits TextWithButtonPropertyComponent, ChangeListener.
*/
class FilePropertyComponent  : public TextWithButtonPropertyComponent
{
public:
	String path;
	ImagePreviewComponent preview;

	FilePropertyComponent (const Value &ValueToControl, const String &propertyName) : TextWithButtonPropertyComponent(ValueToControl, propertyName)
    {
		preview.setSize(150, 150);
		path = ValueToControl.toString();
		textLabel->setText(path, false);
	}

	/** Called when the user clicks the button. */
	void buttonClicked (Button *buttonThatWasClicked)
	{
		if (buttonThatWasClicked != this->button) return;

        FileChooser myChooser ("Please select a file", File::getSpecialLocation (File::userHomeDirectory), "*.*");
		if (myChooser.browseForFileToOpen(&preview))
		{
			path = myChooser.getResult().getFullPathName();
			textLabel->setText(Constructor::getInstance()->setResourceFile(path), false);
		}
	}


};

