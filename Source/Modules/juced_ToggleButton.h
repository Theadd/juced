/*
  ==============================================================================

    juced_ToggleButton.h
    Created: 27 May 2013 3:26:51am
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_TOGGLEBUTTON_H_23066D73__
#define __JUCED_TOGGLEBUTTON_H_23066D73__

#include "../Designer/Globals.h"

class juced_ToggleButton    : public ToggleButton,
					   public DynamicObject
{
public:

    juced_ToggleButton();

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


#endif  // __JUCED_TOGGLEBUTTON_H_23066D73__
