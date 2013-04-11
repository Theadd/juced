class InnerWindow    : public DocumentWindow
{
public:
	InnerWindow()  : DocumentWindow ("Inner",
									Colours::lightgrey,
									DocumentWindow::allButtons)
	{
		setBounds(19, 44, 135, 120);
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
		centreWithSize (135, 120);
		setVisible (true);
	}

	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();	
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

		setResizable(true, true);
		centreWithSize (180, 170);
		setVisible (true);
	}

	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();	
	}

private:
	Component container;
Label label1;
InnerWindow innerwindow;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MiniWindow)
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
container.setBounds(0, 0, 110, 79);
container.setName("container");
setContentOwned (&container, true);
textButton4.setBounds(29, 18, 45, 40);
textButton4.setName("textButton");
textButton4.setButtonText("FFS!");
textButton4.setConnectedEdges(0);
container.addAndMakeVisible(&textButton4);

		setResizable(true, true);
		centreWithSize (110, 105);
		setVisible (true);
	}

	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();	
	}

private:
	Component container;
TextButton textButton4;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PepeWindow)
};

class PequeWindow    : public DocumentWindow
{
public:
	PequeWindow()  : DocumentWindow ("Peque",
									Colours::lightgrey,
									DocumentWindow::allButtons)
	{
		setBounds(39, 108, 115, 120);
setColour(DocumentWindow::backgroundColourId, Colour::fromString("FFCFDA00"));
setName("Peque");
setTitleBarHeight(26);
setTitleBarButtonsRequired(1, 0);
setTitleBarTextCentred(1);
container3.setBounds(0, 0, 115, 94);
container3.setName("container");
setContentOwned (&container3, true);

		setResizable(true, true);
		centreWithSize (115, 120);
		setVisible (true);
	}

	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();	
	}

private:
	Component container3;

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

		setResizable(true, true);
		centreWithSize (455, 390);
		setVisible (true);
	}

	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();	
	}

private:
	Component container;
MiniWindow miniwindow;TextButton textButton1;
TextButton textButton2;
TextButton textButton3;
PepeWindow pepewindow;PequeWindow pequewindow;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

