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
	toolbox = new Toolbox(1, 32, 5);
	toolbox->addItem("juced_Window", "Window", BinaryData::window_png, BinaryData::window_pngSize);
	toolbox->addItem("juced_Label", "Text label", BinaryData::label_png, BinaryData::label_pngSize);
	toolbox->addItem("juced_Textbox", "Textbox", BinaryData::textbox_png, BinaryData::textbox_pngSize);
	toolbox->addItem("juced_Button", "Text button", BinaryData::button_png, BinaryData::button_pngSize);
	toolbox->addItem("juced_Combobox", "Combobox", BinaryData::combobox_png, BinaryData::combobox_pngSize);
	toolbox->addItem("juced_Listbox", "Listbox", BinaryData::listbox_png, BinaryData::listbox_pngSize);
	toolbox->addItem("juced_TabPanel", "Tab panel", BinaryData::tabs_png, BinaryData::tabs_pngSize);
	addAndMakeVisible(toolbox);
	toolbox->setBounds(0, 0, 1, 1);
	toolbox->loadTooltips();

}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour((uint8) 245, (uint8) 245, (uint8) 245));

    g.setFont (Font (16.0f));
    g.setColour (Colours::black);
    //g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
	for (int x = 15; x < getWidth(); x+=15) {
		g.drawLine(x, 0, x, getHeight(), 0.1f);
		g.drawLine(0, x, getWidth(), x, 0.1f);
	}
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainContentComponent::addWindow(Component *parent, int x, int y, int width, int height) {
	juced_Window *win = new juced_Window();
	parent->addAndMakeVisible(win);
	win->setBounds(x, y, (width >= win->minWidth) ? width : win->minWidth, (height >= win->minHeight) ? height : win->minHeight);
	win->getContentComponent()->addMouseListener(this, true);
	juced_Windows.add(win);
}

void MainContentComponent::mouseUp (const MouseEvent &event) {
		
	if (!event.mouseWasClicked()) {
		String *pString = toolbox->getSelectedToolName();
		if ((*pString).isNotEmpty()) {
			MouseEvent relativeEvent = event.getEventRelativeTo(event.originalComponent);
			if ((*pString).equalsIgnoreCase("juced_Window")) {
				addWindow(event.originalComponent, relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());
			} else if ((*pString).equalsIgnoreCase("juced_Label")) {
				//addWindow(event.originalComponent, relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());
				juced_Label *label = new juced_Label();
				label->setText("label1", false);
				event.originalComponent->addAndMakeVisible(label);
				label->setBounds(relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());
				label->addMouseListener(this, false);
				juced_Labels.add(label);
			}
			selectionArea = nullptr;
		}
	} else {
		if ((*toolbox->getSelectedToolName()).isEmpty()) {
			if (event.originalComponent != this) {
				//Selecting a component
				selectionArea = new SelectionArea(true);
				addAndMakeVisible(selectionArea);
				//MouseEvent relativeEvent = event.getEventRelativeTo(this);
				//Point<int> p = event.originalComponent->getLocalPoint(this, event.originalComponent->getPosition());
				selectionArea->setSelectionBounds(event.originalComponent->getX(), event.originalComponent->getY(), event.originalComponent->getWidth(), event.originalComponent->getHeight());
			}
		}
	}
	toolbox->unselectTool();
}

void MainContentComponent::mouseDown (const MouseEvent &event) {
	if ((*toolbox->getSelectedToolName()).isNotEmpty()) {
		selectionArea = new SelectionArea();
		addAndMakeVisible(selectionArea);
		MouseEvent relativeEvent = event.getEventRelativeTo(this);
		selectionArea->setBounds(relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), 1, 1);
	}
}

void MainContentComponent::mouseDrag (const MouseEvent &event) {
	if (selectionArea != nullptr) {
		MouseEvent relativeEvent = event.getEventRelativeTo(this);
		selectionArea->setBounds(relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());

	}
}