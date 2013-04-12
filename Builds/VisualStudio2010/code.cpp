class MainWindow    : public DocumentWindow
{
public:
	MainWindow()  : DocumentWindow ("window",
									Colours::lightgrey,
									DocumentWindow::allButtons)
	{
		setBounds(100, 50, 395, 350);
setColour(DocumentWindow::backgroundColourId, Colour::fromString("FFD3D3D3"));
setName("window");
setTitleBarHeight(26);
setTitleBarButtonsRequired(7, 0);
setTitleBarTextCentred(1);
container.setBounds(0, 0, 395, 324);
container.setName("container");
setContentOwned (&container, true);
slider.setBounds(34, 23, 125, 130);
slider.setColour(Slider::backgroundColourId, Colour::fromString("00000000"));
slider.setName("slider");
slider.setRange(30, 80, 2);
slider.setValue(32);
slider.setTextBoxStyle(Slider::TextBoxBelow, 1, 100, 22);
slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
container.addAndMakeVisible(&slider);

		setResizable(true, true);
		centreWithSize (395, 350);
		setVisible (true);
	}

	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();	
	}

private:
	Component container;
Slider slider;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

