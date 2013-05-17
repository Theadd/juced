/*
  ==============================================================================

    juced_Component.h
    Created: 15 May 2013 4:26:01pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_COMPONENT_H_6B6D7789__
#define __JUCED_COMPONENT_H_6B6D7789__

#include "../Designer/Globals.h"

class juced_Component : public Component,
							public DynamicObject
{
public:
    
	//ValueTree *linkedValueTree;

    juced_Component();
    ~juced_Component();

    //void paint(Graphics&);
    void resized();

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


#endif  // __JUCED_MAINCOMPONENT_H_1B08AA79__

