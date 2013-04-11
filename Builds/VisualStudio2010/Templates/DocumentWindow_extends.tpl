class %varName%    : public DocumentWindow
{
public:
	%varName%()  : DocumentWindow ("%name%",
									Colours::lightgrey,
									DocumentWindow::allButtons)
	{
		%definitions%
		setResizable(true, true);
		centreWithSize (%width%, %height%);
		setVisible (true);
	}

	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();	
	}

private:
	%declarations%
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (%varName%)
};

