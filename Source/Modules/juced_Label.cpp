/*
  ==============================================================================

    juced_Label.cpp
    Created: 3 Mar 2013 11:27:23pm
    Author:  admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

class juced_Label    : public Label
{
public:

    juced_Label()  : Label ()
    {

    }

	bool isChildAllowed () {
		return false;
	}

private:

};