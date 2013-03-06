/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  5 Mar 2013 9:28:21am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__
#define __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class JUCE_Designer  : public Component
{
public:
    //==============================================================================
    JUCE_Designer ();
    ~JUCE_Designer();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void lookAndFeelChanged();
    void childrenChanged();
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
    void mouseDoubleClick (const MouseEvent& e);
    bool keyPressed (const KeyPress& key);
    void focusOfChildComponentChanged (FocusChangeType cause);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JUCE_Designer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__
