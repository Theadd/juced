/*
  ==============================================================================

    juced_Slider.h
    Created: 12 Apr 2013 4:02:39pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_SLIDER_H_4622BE2E__
#define __JUCED_SLIDER_H_4622BE2E__


#include "../Designer/Globals.h"

class juced_Slider    : public Slider,
					   public DynamicObject
{
public:

	//ValueTree *linkedValueTree;

    juced_Slider();

	void mouseUp (const MouseEvent& event);
	void mouseDrag (const MouseEvent& event);
	void mouseDoubleClick (const MouseEvent& event);
	void mouseMove (const MouseEvent& event);
	void mouseDown (const MouseEvent& event);
	void mouseEnter (const MouseEvent& event);
	void mouseExit (const MouseEvent& event);
	void mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel);

private:

};


#endif  // __JUCED_SLIDER_H_4622BE2E__
