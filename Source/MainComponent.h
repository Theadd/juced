/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef __MAINCOMPONENT_H_865F8056__
#define __MAINCOMPONENT_H_865F8056__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Styles\LookAndFeelCustom.h"
#include "JUCE_Designer.h"
//#include "Interface/Toolbox.cpp"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();

private:
    //==============================================================================
	ScopedPointer<JUCE_Designer> juced;
	LookAndFeelCustom customLookAndFeel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // __MAINCOMPONENT_H_865F8056__
