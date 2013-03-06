/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef __MAINCOMPONENT_H_865F8056__
#define __MAINCOMPONENT_H_865F8056__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Modules/juced_Window.cpp"
#include "Modules/juced_Label.cpp"
#include "Interface/SelectionArea.cpp"
#include "Interface/Toolbox.cpp"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component,
							   public MouseListener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
	void addWindow(Component*, int, int, int, int);
	void mouseUp (const MouseEvent&);
	void mouseDown (const MouseEvent&);
	void mouseDrag (const MouseEvent &);

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
	OwnedArray<juced_Window> juced_Windows;
	OwnedArray<juced_Label> juced_Labels;
	//ScopedPointer<juced_Window> win;
	ScopedPointer<Toolbox> toolbox;
	ScopedPointer<SelectionArea> selectionArea;
};


#endif  // __MAINCOMPONENT_H_865F8056__
