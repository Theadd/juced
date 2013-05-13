/*
  ==============================================================================

    juced_BubbleMessageComponentComponent.h
    Created: 13 May 2013 7:27:55am
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_BUBBLECOMPONENT_H_1B44532F__
#define __JUCED_BUBBLECOMPONENT_H_1B44532F__

#include "../Designer/Globals.h"

class juced_BubbleMessageComponent    : public BubbleMessageComponent,
					   public DynamicObject
{
public:

	//ValueTree *linkedValueTree;

    juced_BubbleMessageComponent();

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




#endif  // __JUCED_BUBBLECOMPONENT_H_1B44532F__
