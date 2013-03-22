/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
	setSize (800, 600);
    juced = new JUCE_Designer();
	addAndMakeVisible(juced);
	Component* toolbox;
	toolbox = juced->createToolbox(1, 32, 5);
	juced->addToolboxItem(toolbox, "juced_Window", "Window", BinaryData::window_png, BinaryData::window_pngSize);
	juced->addToolboxItem(toolbox, "juced_Label", "Text label", BinaryData::label_png, BinaryData::label_pngSize);
	juced->addToolboxItem(toolbox, "juced_TextButton", "Text button", BinaryData::button_png, BinaryData::button_pngSize);
	//juced->addToolboxItem(toolbox, "juced_Textbox", "Textbox", BinaryData::textbox_png, BinaryData::textbox_pngSize);
	//juced->addToolboxItem(toolbox, "juced_Combobox", "Combobox", BinaryData::combobox_png, BinaryData::combobox_pngSize);
	//juced->addToolboxItem(toolbox, "juced_Listbox", "Listbox", BinaryData::listbox_png, BinaryData::listbox_pngSize);
	//juced->addToolboxItem(toolbox, "juced_TabPanel", "Tab panel", BinaryData::tabs_png, BinaryData::tabs_pngSize);
	toolbox->setAlwaysOnTop(true);
	juced->addAndMakeVisible(toolbox, 11);

	Viewport *propertyView = juced->getPropertyView();
	addAndMakeVisible(propertyView);
	propertyView->setBounds(100, 100, 200, 400);
	propertyView->setOpaque(true);
	//int style = (ComponentPeer::windowHasTitleBar | ComponentPeer::windowIsResizable);
	propertyView->addToDesktop((int)(ComponentPeer::windowHasTitleBar | ComponentPeer::windowIsResizable));

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
    Rectangle<int> r (getLocalBounds());
	if (juced != nullptr)
		juced->setBounds(0, 0, r.getWidth(), r.getHeight());
}
