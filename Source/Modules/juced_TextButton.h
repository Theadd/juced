/*
  ==============================================================================

    juced_TextButton.h
    Created: 16 Mar 2013 12:39:06pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_TEXTBUTTON_H_4A5B470C__
#define __JUCED_TEXTBUTTON_H_4A5B470C__


#include "../Designer/Globals.h"

class juced_TextButton    : public TextButton,
					   public DynamicObject
{
public:

    juced_TextButton();

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


#endif  // __JUCED_TEXTBUTTON_H_4A5B470C__
