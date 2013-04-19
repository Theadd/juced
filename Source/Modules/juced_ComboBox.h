/*
  ==============================================================================

    juced_ComboBox.h
    Created: 17 Apr 2013 11:22:20pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_COMBOBOX_H_B8A6DCF3__
#define __JUCED_COMBOBOX_H_B8A6DCF3__

#include "../Designer/Globals.h"

class juced_ComboBox    : public ComboBox,
					   public DynamicObject
{
public:

	//ValueTree *linkedValueTree;

    juced_ComboBox();

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


#endif  // __JUCED_COMBOBOX_H_B8A6DCF3__
