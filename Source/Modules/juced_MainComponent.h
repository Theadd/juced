/*
  ==============================================================================

    juced_MainComponent.h
    Created: 3 Mar 2013 2:44:43pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_MAINCOMPONENT_H_1B08AA79__
#define __JUCED_MAINCOMPONENT_H_1B08AA79__

#include "../Designer/Globals.h"

class juced_MainComponent : public Component,
							public DynamicObject
{
public:
    
	//ValueTree *linkedValueTree;

    juced_MainComponent();
    ~juced_MainComponent();

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
