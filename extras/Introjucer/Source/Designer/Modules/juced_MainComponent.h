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

    void paint(Graphics&);
    void resized();

private:

};


#endif  // __JUCED_MAINCOMPONENT_H_1B08AA79__
