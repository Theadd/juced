/*
  ==============================================================================

    juced_ImageButton.h
    Created: 13 Apr 2013 10:07:27pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_IMAGEBUTTON_H_FF5FFB74__
#define __JUCED_IMAGEBUTTON_H_FF5FFB74__

#include "../Designer/Globals.h"

class juced_ImageButton    : public ImageButton,
					   public DynamicObject
{
public:

    juced_ImageButton();

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

#endif  // __JUCED_IMAGEBUTTON_H_FF5FFB74__
