/*
  ==============================================================================

    GeneratedCode.cpp
    Created: 12 Apr 2013 12:25:09am
    Author:  admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Styles/LookAndFeelCustom.h"


class InnerWindow    : public DocumentWindow
{
public:
    InnerWindow()  : DocumentWindow ("Inner",
                                         Colours::lightgrey,
                                         DocumentWindow::allButtons)
    {
        setBounds(85, 60, 137, 122);
        setColour(DocumentWindow::backgroundColourId, Colour::fromString("FFFFFFFF"));
        setName("Inner");
        setTitleBarHeight(26);
        setTitleBarButtonsRequired(7, 0);
        setTitleBarTextCentred(1);
        container.setBounds(0, 0, 135, 94);
        container.setName("container");
        setContentOwned (&container, true);
        textButton.setBounds(39, 8, 50, 25);
        textButton.setName("textButton");
        textButton.setButtonText("Text Button");
        textButton.setConnectedEdges(0);
        container.addAndMakeVisible(&textButton);

        setResizable(true, true);
        setVisible (true);
    }

    void closeButtonPressed()
    {
        //JUCEApplication::getInstance()->systemRequestedQuit();
    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDoubleClick(event);
    }

private:
    Component container;
    TextButton textButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InnerWindow)
};

class MiniWindow    : public DocumentWindow
{
public:
    MiniWindow()  : DocumentWindow ("Mini",
                                        Colours::lightgrey,
                                        DocumentWindow::allButtons)
    {
        setBounds(224, 78, 180, 170);
        setColour(DocumentWindow::backgroundColourId, Colour::fromString("FF00A96D"));
        setName("Mini");
        setTitleBarHeight(50);
        setTitleBarButtonsRequired(4, 1);
        setTitleBarTextCentred(1);
        container.setBounds(0, 0, 180, 144);
        container.setName("container");
        setContentOwned (&container, true);
        label1.setBounds(64, 14, 70, 45);
        label1.setText("Text label", false);
        label1.setColour(Label::backgroundColourId, Colour::fromString("FF018C90"));
        label1.setColour(Label::textColourId, Colour::fromString("EE68140D"));
        label1.setName("label");
        container.addAndMakeVisible(&label1);
        container.addAndMakeVisible(&innerwindow);
        slider4.setBounds(14, 44, 74, 85);
        slider4.setColour(Slider::backgroundColourId, Colour::fromString("00000000"));
        slider4.setName("slider");
        slider4.setRange(0, 25, 0);
        slider4.setValue(18.435);
        slider4.setTextBoxStyle(Slider::TextBoxAbove, 0, 80, 20);
        slider4.setSliderStyle(Slider::Rotary);
        container.addAndMakeVisible(&slider4);

        setResizable(true, true);
        setVisible (true);
    }

    void closeButtonPressed()
    {
        //JUCEApplication::getInstance()->systemRequestedQuit();
    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDoubleClick(event);
    }

private:
    Component container;
    Label label1;
    InnerWindow innerwindow;
    Slider slider4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiniWindow)
};

class pepeContainer : public Component
{
public:

    pepeContainer() : Component()
    {
        setBounds(0, 0, 110, 79);
        setName("container");
        textButton4.setBounds(29, 18, 45, 40);
        textButton4.setName("textButton");
        textButton4.setButtonText("FFS!");
        textButton4.setConnectedEdges(0);
        textButton4.addMouseListener(this, false);
        addAndMakeVisible(&textButton4);

    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseUp(event);

		if (event.eventComponent == &textButton4)
			textButton4.setButtonText("Wololo!");
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseDoubleClick(event);
    }

private:
    TextButton textButton4;

};


class PepeWindow    : public DocumentWindow
{
public:
    PepeWindow()  : DocumentWindow ("Pepe",
                                        Colours::lightgrey,
                                        DocumentWindow::allButtons)
    {
        setBounds(89, 83, 110, 105);
        setColour(DocumentWindow::backgroundColourId, Colour::fromString("FFA20000"));
        setName("Pepe");
        setTitleBarHeight(26);
        setTitleBarButtonsRequired(7, 0);
        setTitleBarTextCentred(1);
        setContentOwned (&pepecontainer, true);

        setResizable(true, true);
        setVisible (true);
    }

    void closeButtonPressed()
    {
        //JUCEApplication::getInstance()->systemRequestedQuit();
    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDoubleClick(event);
    }

private:
    pepeContainer pepecontainer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PepeWindow)
};

class PequeWindow    : public DocumentWindow
{
public:
    PequeWindow()  : DocumentWindow ("Peque",
                                         Colours::lightgrey,
                                         DocumentWindow::allButtons)
    {
        setBounds(24, 158, 128, 128);
        setColour(DocumentWindow::backgroundColourId, Colour::fromString("FFCFDA00"));
        setName("Peque");
        setTitleBarHeight(26);
        setTitleBarButtonsRequired(1, 0);
        setTitleBarTextCentred(1);
        container3.setBounds(0, 0, 115, 94);
        container3.setName("container");
        setContentOwned (&container3, true);
        slider5.setBounds(24, 13, 60, 60);
        slider5.setColour(Slider::backgroundColourId, Colour::fromString("00000000"));
        slider5.setName("slider");
        slider5.setRange(0, 10, 0);
        slider5.setValue(4);
        slider5.setTextBoxStyle(Slider::NoTextBox, 0, 80, 20);
        slider5.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
        slider5.setLookAndFeel(LookAndFeelCustom::getInstance());
        container3.addAndMakeVisible(&slider5);

        setResizable(true, true);
        setVisible (true);
    }

    void closeButtonPressed()
    {
        //JUCEApplication::getInstance()->systemRequestedQuit();
    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDoubleClick(event);
    }

private:
    Component container3;
    Slider slider5;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PequeWindow)
};

class MainWindow    : public DocumentWindow
{
public:
    MainWindow()  : DocumentWindow ("There will be bugs",
                                        Colours::lightgrey,
                                        DocumentWindow::allButtons)
    {
        setBounds(100, 30, 455, 390);
        setColour(DocumentWindow::backgroundColourId, Colour::fromString("FF006BA7"));
        setName("There will be bugs");
        setTitleBarHeight(26);
        setTitleBarButtonsRequired(7, 0);
        setTitleBarTextCentred(0);
        container.setBounds(0, 0, 455, 364);
        container.setName("container");
        setContentOwned (&container, true);
        container.addAndMakeVisible(&miniwindow);
        textButton1.setBounds(9, 0, 30, 30);
        textButton1.setName("textButton");
        textButton1.setButtonText("1");
        textButton1.setConnectedEdges(6);
        container.addAndMakeVisible(&textButton1);
        textButton2.setBounds(39, 0, 55, 30);
        textButton2.setName("textButton");
        textButton2.setButtonText("2");
        textButton2.setConnectedEdges(3);
        container.addAndMakeVisible(&textButton2);
        textButton3.setBounds(94, 0, 30, 30);
        textButton3.setName("textButton");
        textButton3.setButtonText("3");
        textButton3.setConnectedEdges(5);
        container.addAndMakeVisible(&textButton3);
        container.addAndMakeVisible(&pepewindow);
        container.addAndMakeVisible(&pequewindow);
        slider3.setBounds(134, 3, 290, 25);
        slider3.setColour(Slider::backgroundColourId, Colour::fromString("00000000"));
        slider3.setName("slider");
        slider3.setRange(0, 80, 5);
        slider3.setValue(25);
        slider3.setTextBoxStyle(Slider::TextBoxRight, 0, 80, 20);
        slider3.setSliderStyle(Slider::LinearHorizontal);
        container.addAndMakeVisible(&slider3);
        label2.setBounds(99, 303, 95, 50);
        label2.setText("Wololo!!!", false);
        label2.setColour(Label::backgroundColourId, Colour::fromString("00000000"));
        label2.setColour(Label::textColourId, Colour::fromString("FF000000"));
        label2.setName("label");
        container.addAndMakeVisible(&label2);
        label3.setBounds(239, 278, 155, 55);
        label3.setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aenean varius, metus nec accumsan pelle", false);
        label3.setColour(Label::backgroundColourId, Colour::fromString("00000000"));
        label3.setColour(Label::textColourId, Colour::fromString("FFFFFFFF"));
        label3.setName("label");
        container.addAndMakeVisible(&label3);
        slider2.setBounds(409, 38, 35, 310);
        slider2.setColour(Slider::backgroundColourId, Colour::fromString("00000000"));
        slider2.setName("slider");
        slider2.setRange(0, 100, 0);
        slider2.setValue(35);
        slider2.setTextBoxStyle(Slider::NoTextBox, 0, 80, 20);
        slider2.setSliderStyle(Slider::ThreeValueVertical);
        container.addAndMakeVisible(&slider2);
        slider.setBounds(24, 38, 25, 105);
        slider.setColour(Slider::backgroundColourId, Colour::fromString("00000000"));
        slider.setName("slider");
        slider.setRange(0, 10, 0);
        slider.setValue(0);
        slider.setTextBoxStyle(Slider::NoTextBox, 0, 80, 20);
        slider.setSliderStyle(Slider::IncDecButtons);
        container.addAndMakeVisible(&slider);
        slider6.setBounds(169, 203, 25, 125);
        slider6.setColour(Slider::backgroundColourId, Colour::fromString("00000000"));
        slider6.setName("slider");
        slider6.setRange(0, 10, 0);
        slider6.setValue(0);
        slider6.setTextBoxStyle(Slider::NoTextBox, 0, 80, 20);
        slider6.setSliderStyle(Slider::TwoValueVertical);
        slider6.setLookAndFeel(LookAndFeelCustom::getInstance());
        container.addAndMakeVisible(&slider6);

        setResizable(true, true);
        setVisible (true);
    }

    void closeButtonPressed()
    {
        JUCEApplication::getInstance()->systemRequestedQuit();
    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDoubleClick(event);
    }

private:
    Component container;
    MiniWindow miniwindow;
    TextButton textButton1;
    TextButton textButton2;
    TextButton textButton3;
    PepeWindow pepewindow;
    PequeWindow pequewindow;
    Slider slider3;
    Label label2;
    Label label3;
    Slider slider2;
    Slider slider;
    Slider slider6;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};






