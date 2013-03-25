/*
  ==============================================================================

    juced_Window.h
    Created: 13 Mar 2013 5:50:59pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_WINDOW_H_4F81997D__
#define __JUCED_WINDOW_H_4F81997D__

#include "../Designer/Globals.h"

class juced_Window    : public DocumentWindow,
						public DynamicObject
{
public:

	int minWidth;
	int minHeight;

    juced_Window();

	void closeButtonPressed ();
	void minimizeButtonPressed ();
	void maximizeButtonPressed ();
	void setContentOwned (Component *newContentComponent, bool resizeToFitWhenContentChangesSize);

private:

};

#endif  // __JUCED_WINDOW_H_4F81997D__
