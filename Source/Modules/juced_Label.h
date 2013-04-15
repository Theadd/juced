/*
  ==============================================================================

    juced_Label.h
    Created: 11 Mar 2013 9:34:46pm
    Author:  admin

  ==============================================================================
*/



#ifndef __JUCED_LABEL_H_9DD865FB__
#define __JUCED_LABEL_H_9DD865FB__

#include "../Designer/Globals.h"

class juced_Label    : public Label,
					   public DynamicObject
{
public:

	//ValueTree *linkedValueTree;

    juced_Label();

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


#endif  // __JUCED_LABEL_H_9DD865FB__
