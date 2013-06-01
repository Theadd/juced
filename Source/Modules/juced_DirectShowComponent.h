/*
  ==============================================================================

    juced_DirectShowComponent.h
    Created: 22 May 2013 10:53:46pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_DIRECTSHOWCOMPONENT_H_43DF349E__
#define __JUCED_DIRECTSHOWCOMPONENT_H_43DF349E__

#include "../Designer/Globals.h"

class juced_DirectShowComponent    : public Component,
                                     public DynamicObject
{
public:

    juced_DirectShowComponent();

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



#endif  // __JUCED_DIRECTSHOWCOMPONENT_H_43DF349E__

