/*
  ==============================================================================

    juced_ProgressBar.h
    Created: 13 May 2013 7:27:41am
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_PROGRESSBAR_H_1BE74C4__
#define __JUCED_PROGRESSBAR_H_1BE74C4__

#include "../Designer/Globals.h"

class juced_ProgressBar    : public ProgressBar,
					   public DynamicObject
{
public:

	//ValueTree *linkedValueTree;

    juced_ProgressBar();

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




#endif  // __JUCED_PROGRESSBAR_H_1BE74C4__
