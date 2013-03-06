/*
  ==============================================================================

    juced_Window.cpp
    Created: 2 Mar 2013 6:43:07pm
    Author:  admin

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "juced_MainComponent.h"

class juced_Window    : public DocumentWindow
{
public:

	int minWidth;
	int minHeight;

    juced_Window()  : DocumentWindow ("juced_Window",
                                    Colours::lightgrey,
                                    DocumentWindow::allButtons)
    {
		minWidth = 150;
		minHeight = 150;

        setContentOwned (new juced_MainComponent(), true);

        centreWithSize (getWidth(), getHeight());
        setVisible (true);
		//mainComponent = new juced_MainComponent();
		//setContentComponent(mainComponent);

    }

    void closeButtonPressed()
    {
            
        //JUCEApplication::getInstance()->systemRequestedQuit();
		AlertWindow::showMessageBox(AlertWindow::NoIcon, "Callback method:", "closeButtonPressed()");
    }

	bool isChildAllowed () {
		return false;
	}

private:
	//ScopedPointer<juced_MainComponent> mainComponent;

};