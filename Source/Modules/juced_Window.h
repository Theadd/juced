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
		
	void mouseUp (const MouseEvent& event);
	void mouseDrag (const MouseEvent& event);
	void mouseDoubleClick (const MouseEvent& event);
	void mouseMove (const MouseEvent& event);
	void mouseDown (const MouseEvent& event);
	void mouseEnter (const MouseEvent& event);
	void mouseExit (const MouseEvent& event);
	void mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel);
	
private:
	static int _numObjects;
};

#endif  // __JUCED_WINDOW_H_4F81997D__
