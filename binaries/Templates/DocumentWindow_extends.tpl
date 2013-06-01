class %varName%    : public DocumentWindow
{
public:
	%varName%()  : %className% ("%name%",
									Colours::lightgrey,
									DocumentWindow::allButtons)
	{
		%definitions%
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
			%className%::mouseUp(event);
	}

	void mouseDrag (const MouseEvent& event)
	{
		if (event.eventComponent == this)
			%className%::mouseDrag(event);
	}

	void mouseDoubleClick (const MouseEvent& event)
	{
		if (event.eventComponent == this)
			%className%::mouseDoubleClick(event);
	}

private:
	%declarations%
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (%varName%)
};

