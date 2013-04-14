/*
  ==============================================================================

    juced_Window.cpp
    Created: 2 Mar 2013 6:43:07pm
    Author:  admin

  ==============================================================================
*/

#include "juced_Window.h"



juced_Window::juced_Window()  : DocumentWindow ("juced_Window",
                                Colours::lightgrey,
                                DocumentWindow::allButtons)
{
	minWidth = 150;
	minHeight = 150;
		
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
	removeMouseListener(this);

	setName("window");
	setProperty(Attributes::objectType, "Window");
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	setProperty(Attributes::name, getName());
	setProperty(Attributes::varName, "MainWindow");
	setProperty(Attributes::className, "DocumentWindow");
	setProperty(Attributes::toolName, "juced_Window");
	setProperty(Attributes::contentOwner, true);
	setProperty(Attributes::titleBarHeight, getTitleBarHeight());
	setProperty(Attributes::titleBarButtons, 7);
	setProperty(Attributes::titleBarButtonsOnLeft, false);
	setProperty(Attributes::titleBarTextCentered, true);
	setProperty(Attributes::declareExtended, false);
	setComponentID(Uuid().toString());
	setProperty(Attributes::ID, getComponentID());

}

void juced_Window::closeButtonPressed ()
{
    //JUCEApplication::getInstance()->systemRequestedQuit();

}

void juced_Window::minimizeButtonPressed ()
{

}

void juced_Window::maximizeButtonPressed ()
{

}

void juced_Window::setContentOwned (Component *newContentComponent, bool resizeToFitWhenContentChangesSize)
{
	Rectangle<int> r (getLocalBounds());
	newContentComponent->setBounds(0, 0, r.getWidth(), r.getHeight() - getTitleBarHeight());
	DocumentWindow::setContentOwned(newContentComponent, resizeToFitWhenContentChangesSize);
}

void juced_Window::mouseUp (const MouseEvent& event) {}
void juced_Window::mouseDrag (const MouseEvent& event) {}
void juced_Window::mouseDoubleClick (const MouseEvent& event) {}
void juced_Window::mouseMove (const MouseEvent& event) {}
void juced_Window::mouseDown (const MouseEvent& event) {}
void juced_Window::mouseEnter (const MouseEvent& event) {}
void juced_Window::mouseExit (const MouseEvent& event) {}
void juced_Window::mouseWheelMove (const MouseEvent &event, const MouseWheelDetails &wheel) {}