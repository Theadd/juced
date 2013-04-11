class %varName%    : public DocumentWindow
{
public:
	%varName%()  : DocumentWindow ("%name%",
									Colours::lightgrey,
									DocumentWindow::allButtons)
	{
		setContentOwned (new Component(), true);
		//Component *container = getContentComponent();
		//container->setSize(%width%, %height%);
		setResizable(true, true);
		centreWithSize (%width%, %height%);
		setVisible (true);
		
		%initialization_code%
	}

	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();	
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (%varName%)
};