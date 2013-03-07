
#include "JUCE_Designer.h"

JUCE_Designer::JUCE_Designer ()
{
	setSize (500, 400);
	
}

JUCE_Designer::~JUCE_Designer() { }

Component* JUCE_Designer::createToolbox (int itemsPerRow, int itemSize, int itemPadding) {
	Toolbox *toolbox = new Toolbox(itemsPerRow, itemSize, itemPadding);
	toolbox->setBounds(0, 0, 1, 1);
	toolbox->loadTooltips();
	toolboxes.add(toolbox);
	return toolbox;
}

void JUCE_Designer::addToolboxItem (Component* _toolbox, const String& name, const String& toolTip, const char* image, int imageSize) {
	Toolbox *toolbox = (Toolbox*) _toolbox;
	toolbox->addItem(name, toolTip, image, imageSize);
}

String* JUCE_Designer::getSelectedToolName () {
	for (int i = 0; i < toolboxes.size(); i++) {
		if (toolboxes[i]->getSelectedToolName()->isNotEmpty()) {
			return toolboxes[i]->getSelectedToolName();
		}
	}
	return (new String(""));
}

void JUCE_Designer::deselectTool () {
	for (int i = 0; i < toolboxes.size(); i++) {
		toolboxes[i]->deselectTool();
	}
}

void JUCE_Designer::addWindow (Component *parent, int x, int y, int width, int height) {
	juced_Window *win = new juced_Window();
	parent->addAndMakeVisible(win);
	win->setBounds(x, y, (width >= win->minWidth) ? width : win->minWidth, (height >= win->minHeight) ? height : win->minHeight);
	win->getContentComponent()->addMouseListener(this, true);
	juced_Windows.add(win);
}

//==============================================================================
void JUCE_Designer::paint (Graphics& g)
{
    g.fillAll (Colour((uint8) 245, (uint8) 245, (uint8) 245));

    g.setFont (Font (16.0f));
    g.setColour (Colours::black);
    //g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
	for (float x = 15.0f; x < (float) getWidth(); x+=15.0f) {
		g.drawLine(x, 0.0f, x, (float) getHeight(), 0.1f);
		g.drawLine(0.0f, x, (float) getWidth(), x, 0.1f);
	}
}

void JUCE_Designer::resized()
{

}

void JUCE_Designer::lookAndFeelChanged()
{

}

void JUCE_Designer::childrenChanged()
{

}

void JUCE_Designer::mouseDown (const MouseEvent& event)
{
	if (getSelectedToolName()->isNotEmpty()) {
		selectionArea = new SelectionArea();
		addAndMakeVisible(selectionArea);
		MouseEvent relativeEvent = event.getEventRelativeTo(this);
		selectionArea->setBounds(relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), 1, 1);
	}
}

void JUCE_Designer::mouseDrag (const MouseEvent& event)
{
	if (selectionArea != nullptr) {
		MouseEvent relativeEvent = event.getEventRelativeTo(this);
		selectionArea->setBounds(relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());

	}
}

void JUCE_Designer::mouseUp (const MouseEvent& event)
{
	String *selectedToolName = getSelectedToolName();
	if (!event.mouseWasClicked()) {
		if (selectedToolName->isNotEmpty()) {
			MouseEvent relativeEvent = event.getEventRelativeTo(event.originalComponent);
			if (selectedToolName->equalsIgnoreCase("juced_Window")) {
				addWindow(event.originalComponent, relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());
			} else if (selectedToolName->equalsIgnoreCase("juced_Label")) {
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
		if (selectedToolName->isEmpty()) {
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
	deselectTool();
}

void JUCE_Designer::mouseDoubleClick (const MouseEvent& e)
{

}

bool JUCE_Designer::keyPressed (const KeyPress& key)
{

    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
}

void JUCE_Designer::focusOfChildComponentChanged (FocusChangeType cause)
{

}