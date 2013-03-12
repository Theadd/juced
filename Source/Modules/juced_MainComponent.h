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
#include "../Designer/BaseModules.h"

class juced_MainComponent : public Component,
							public DynamicObject
{
public:
    
	ValueTree *linkedValueTree;

    juced_MainComponent();
    ~juced_MainComponent();

    void paint(Graphics&);
    void resized();

	typedef ReferenceCountedObjectPtr<juced_MainComponent> Ptr;

private:

};


#endif  // __JUCED_MAINCOMPONENT_H_1B08AA79__
