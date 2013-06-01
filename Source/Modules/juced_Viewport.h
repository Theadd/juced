/*
  ==============================================================================

    juced_Viewport.h
    Created: 23 May 2013 1:31:16am
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_VIEWPORT_H_C8C6C7F3__
#define __JUCED_VIEWPORT_H_C8C6C7F3__

#include "../Designer/Globals.h"

class juced_Viewport	: public Viewport,
						  public DynamicObject
{
public:

    juced_Viewport();
	//void juced_Viewport::paint (Graphics& g);

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


#endif  // __JUCED_VIEWPORT_H_C8C6C7F3__
