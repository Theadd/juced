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

	setName("window");
	setProperty(Attributes::objectType, "Window");
	setProperty(Attributes::height, getHeight());
	setProperty(Attributes::width, getWidth());
	setProperty(Attributes::backgroundColour, findColour(backgroundColourId).toDisplayString(true));
	setProperty(Attributes::name, getName());
	setProperty(Attributes::className, "juced_Window");
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
	AlertWindow::showMessageBox(AlertWindow::NoIcon, "Crash!", "Don't do this");
	return;
}

void juced_Window::setContentOwned (Component *newContentComponent, bool resizeToFitWhenContentChangesSize)
{
	Rectangle<int> r (getLocalBounds());
	newContentComponent->setBounds(0, 0, r.getWidth(), r.getHeight() - getTitleBarHeight());
	DocumentWindow::setContentOwned(newContentComponent, resizeToFitWhenContentChangesSize);
}

