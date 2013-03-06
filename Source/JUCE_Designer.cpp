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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "JUCE_Designer.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
JUCE_Designer::JUCE_Designer ()
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (300, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

JUCE_Designer::~JUCE_Designer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void JUCE_Designer::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void JUCE_Designer::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void JUCE_Designer::lookAndFeelChanged()
{
    //[UserCode_lookAndFeelChanged] -- Add your code here...
    //[/UserCode_lookAndFeelChanged]
}

void JUCE_Designer::childrenChanged()
{
    //[UserCode_childrenChanged] -- Add your code here...
    //[/UserCode_childrenChanged]
}

void JUCE_Designer::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //[/UserCode_mouseDown]
}

void JUCE_Designer::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    //[/UserCode_mouseDrag]
}

void JUCE_Designer::mouseUp (const MouseEvent& e)
{
    //[UserCode_mouseUp] -- Add your code here...
    //[/UserCode_mouseUp]
}

void JUCE_Designer::mouseDoubleClick (const MouseEvent& e)
{
    //[UserCode_mouseDoubleClick] -- Add your code here...
    //[/UserCode_mouseDoubleClick]
}

bool JUCE_Designer::keyPressed (const KeyPress& key)
{
    //[UserCode_keyPressed] -- Add your code here...
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
    //[/UserCode_keyPressed]
}

void JUCE_Designer::focusOfChildComponentChanged (FocusChangeType cause)
{
    //[UserCode_focusOfChildComponentChanged] -- Add your code here...
    //[/UserCode_focusOfChildComponentChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="JUCE_Designer" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="0" initialWidth="300" initialHeight="400">
  <METHODS>
    <METHOD name="childrenChanged()"/>
    <METHOD name="mouseUp (const MouseEvent&amp; e)"/>
    <METHOD name="keyPressed (const KeyPress&amp; key)"/>
    <METHOD name="lookAndFeelChanged()"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDoubleClick (const MouseEvent&amp; e)"/>
    <METHOD name="focusOfChildComponentChanged (FocusChangeType cause)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif



//[EndFile] You can add extra defines here...
//[/EndFile]
