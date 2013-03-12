/*
  ==============================================================================

    juced_Window.cpp
    Created: 2 Mar 2013 6:43:07pm
    Author:  admin

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#include "../Designer/BaseModules.h"
#include "juced_MainComponent.h"

class juced_Window    : public juced_BaseWindow
{
public:

	int minWidth;
	int minHeight;

	const var foo (const var* params, int numParams)
    {
		this->closeButtonPressed();
		return var::null;
    }

    juced_Window()  : juced_BaseWindow ("juced_Window",
                                    Colours::lightgrey,
                                    DocumentWindow::allButtons)
    {
		minWidth = 150;
		minHeight = 150;
		

        //setContentOwned (new juced_MainComponent(), true);

        centreWithSize (getWidth(), getHeight());
        setVisible (true);
		//mainComponent = new juced_MainComponent();
		//setContentComponent(mainComponent);
		//setMethod ("closeButtonPressed", (var::MethodFunction) &closeButtonPressed);
		#define DECLARE_METHOD(name)  setMethod (#name, (var::MethodFunction) &juced_Window::name)

        DECLARE_METHOD (foo);

		#undef DECLARE_METHOD

		setProperty(Ids::height, getHeight());
		setProperty(Ids::width, getWidth());
		setProperty(Ids::name, getName());
		setProperty(Ids::className, "juced_Window");
		setComponentID(Uuid().toString());
		setProperty(Ids::ID, getComponentID());

    }

	void closeButtonPressed()
    {
            
        //JUCEApplication::getInstance()->systemRequestedQuit();
		AlertWindow::showMessageBox(AlertWindow::NoIcon, "Callback method:", "closeButtonPressed()");
    }

	typedef ReferenceCountedObjectPtr<juced_Window> Ptr;

private:
	//ScopedPointer<juced_MainComponent> mainComponent;

};