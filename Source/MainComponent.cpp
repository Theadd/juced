/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
	setSize (500, 400);
    juced = new JUCE_Designer();
	addAndMakeVisible(juced);
	Component* toolbox;
	toolbox = juced->createToolbox(1, 32, 5);
	juced->addToolboxItem(toolbox, "juced_Window", "Window", BinaryData::window_png, BinaryData::window_pngSize);
	juced->addToolboxItem(toolbox, "juced_Label", "Text label", BinaryData::label_png, BinaryData::label_pngSize);
	juced->addToolboxItem(toolbox, "juced_Textbox", "Textbox", BinaryData::textbox_png, BinaryData::textbox_pngSize);
	juced->addToolboxItem(toolbox, "juced_Button", "Text button", BinaryData::button_png, BinaryData::button_pngSize);
	juced->addToolboxItem(toolbox, "juced_Combobox", "Combobox", BinaryData::combobox_png, BinaryData::combobox_pngSize);
	juced->addToolboxItem(toolbox, "juced_Listbox", "Listbox", BinaryData::listbox_png, BinaryData::listbox_pngSize);
	juced->addToolboxItem(toolbox, "juced_TabPanel", "Tab panel", BinaryData::tabs_png, BinaryData::tabs_pngSize);
	juced->addAndMakeVisible(toolbox);

}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour((uint8) 245, (uint8) 245, (uint8) 245));
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
