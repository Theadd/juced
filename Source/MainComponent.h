/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef __MAINCOMPONENT_H_865F8056__
#define __MAINCOMPONENT_H_865F8056__

#include "../JuceLibraryCode/JuceHeader.h"
#include "JUCE_Designer.h"
//#include "Interface/Toolbox.cpp"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, ComponentListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
	void componentMovedOrResized (Component &component, bool wasMoved, bool wasResized);

private:
    //==============================================================================

	ScopedPointer<JUCE_Designer> juced;
	Viewport *propertyView;
	ScopedPointer<ResizableEdgeComponent> resizableBorder;
	ScopedPointer<ComponentBoundsConstrainer> constrainer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // __MAINCOMPONENT_H_865F8056__
