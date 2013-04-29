/*
  ==============================================================================

    juced_ListBox.h
    Created: 30 Apr 2013 12:39:51am
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_LISTBOX_H_AAEDCAAB__
#define __JUCED_LISTBOX_H_AAEDCAAB__

#include "../Designer/Globals.h"

class juced_ListBox    : public ListBox,
					   public DynamicObject
{
public:

	//ValueTree *linkedValueTree;

    juced_ListBox();

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



#endif  // __JUCED_LISTBOX_H_AAEDCAAB__
