/*
  ==============================================================================

    juced_ImageComponent.h
    Created: 26 May 2013 3:58:03am
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_IMAGECOMPONENT_H_7362AFEF__
#define __JUCED_IMAGECOMPONENT_H_7362AFEF__

#include "../Designer/Globals.h"

class juced_ImageComponent    : public ImageComponent,
					   public DynamicObject
{
public:

    juced_ImageComponent();

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


#endif  // __JUCED_IMAGECOMPONENT_H_7362AFEF__
