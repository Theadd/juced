/*
  ==============================================================================

    juced_MainComponent.h
    Created: 3 Mar 2013 2:44:43pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_MAINCOMPONENT_H_1B08AA79__
#define __JUCED_MAINCOMPONENT_H_1B08AA79__

#include "../JuceLibraryCode/JuceHeader.h"

class juced_MainComponent : public Component,
							public MouseListener
{
public:
    //==============================================================================
    juced_MainComponent();
    ~juced_MainComponent();

    void paint(Graphics&);
    void resized();
	bool isChildAllowed();

private:

};


#endif  // __JUCED_MAINCOMPONENT_H_1B08AA79__
