
#include "JUCE_Designer.h"

JUCE_Designer::JUCE_Designer ()
{
	setSize (800, 600);

	addAndMakeVisible(&grid, 10);
	
	PropertyGroup *properties = new PropertyGroup();
	propertyView = new PropertyView(properties);
	propertyView->setBounds(100, 100, 200, 400);

	addAndMakeVisible(&mousePositionLabel);
	mousePositionLabel.setAlwaysOnTop(true);
	mousePositionLabel.setFont(Font(12.0f));
	mousePositionLabel.setBounds(getWidth() - 80, getHeight() - 25, 80, 25);
	mousePositionLabel.setInterceptsMouseClicks(false, false);
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

Viewport* JUCE_Designer::getPropertyView ()
{
	return propertyView;
}

String* JUCE_Designer::getSelectedToolName () {
	//for (int i = 0; i < toolboxes.size(); i++) {
	for (int i = toolboxes.size(); --i >= 0;) {
		if (toolboxes[i]->getSelectedToolName()->isNotEmpty()) {
			return toolboxes[i]->getSelectedToolName();
		}
	}
	return (new String(""));
}

void JUCE_Designer::deselectTool () {
	//for (int i = 0; i < toolboxes.size(); i++) {
	for (int i = toolboxes.size(); --i >= 0;) {	
		toolboxes[i]->deselectTool();
	}
}

void JUCE_Designer::addWindow (Component *parent, int x, int y, int width, int height) {

	juced_Window *win = new juced_Window();
	parent->addAndMakeVisible(win);
	win->setBounds(x, y, (width >= win->minWidth) ? width : win->minWidth, (height >= win->minHeight) ? height : win->minHeight);
	
	win->setProperty(Attributes::x, x);
	win->setProperty(Attributes::y, y);
	win->setProperty(Attributes::width, (width >= win->minWidth) ? width : win->minWidth);
	win->setProperty(Attributes::height, (height >= win->minHeight) ? height : win->minHeight);

	bigTree = new BigTree(win, win->getProperty(Attributes::objectType));

	juced_MainComponent *comp = new juced_MainComponent();
	win->setContentOwned(comp, true);
	BigTree *compTree = new BigTree(comp, comp->getProperty(Attributes::objectType));
	bigTree->addChild(*compTree, -1, 0);
	win->getContentComponent()->addMouseListener(this, true);

	PropertyGroup *properties = new PropertyGroup(bigTree);
	propertyView->setViewedComponent(properties);

}

void JUCE_Designer::writeXmlToFile (String _filename)
{
	XmlElement *obj_xml = bigTree->createXml();

	//Create xml file from XmlElement
	File file = File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + _filename);
	file.create();
	obj_xml->writeToFile(file, "");
	//file.revealToUser();
}


void JUCE_Designer::paint (Graphics& g)
{
    g.fillAll (Colour((uint8) 245, (uint8) 245, (uint8) 245));
	#ifdef __JUCER_APPEARANCESETTINGS_H_34D762C7__
		IntrojucerLookAndFeel::fillWithBackgroundTexture (*this, g);
	#endif
}

void JUCE_Designer::resized()
{
	grid.setBounds(0, 0, getWidth(), getHeight());
	mousePositionLabel.setBounds(getWidth() - mousePositionLabel.getWidth(), getHeight() - mousePositionLabel.getHeight(), mousePositionLabel.getWidth(), mousePositionLabel.getHeight());
	
}

void JUCE_Designer::lookAndFeelChanged()
{

}

void JUCE_Designer::childrenChanged()
{

}

void JUCE_Designer::mouseMove (const MouseEvent& event)
{
	MouseEvent relativeEvent = event.getEventRelativeTo(this);
	mousePositionLabel.setText(String(relativeEvent.x) + " , " + String(relativeEvent.y), false);
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

			ValueTree parentTree;
			if (event.originalComponent != this)
				parentTree = bigTree->getChildWithProperty(Attributes::ID, event.originalComponent->getComponentID());

			MouseEvent relativeEvent = event.getEventRelativeTo(event.originalComponent);

			if (selectedToolName->equalsIgnoreCase("juced_Window")) {
				addWindow(event.originalComponent, relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());
			} else {

				DynamicObject *dynamicObj;
				if ((dynamicObj = createObjectFromToolName(selectedToolName)) != nullptr) {

					event.originalComponent->addAndMakeVisible(dynamic_cast<Component *> (dynamicObj));
					(dynamic_cast<Component *> (dynamicObj))->addMouseListener(this, false);

					BigTree *objTree = new BigTree(dynamicObj, dynamicObj->getProperty(Attributes::objectType));
					if (parentTree.isValid()) {
						parentTree.addChild(*objTree, -1, 0);
					} else AlertWindow::showMessageBox(AlertWindow::NoIcon, "parent tree", "is not valid");

					objTree->setProperty(Attributes::x, relativeEvent.getMouseDownX(), 0);
					objTree->setProperty(Attributes::y, relativeEvent.getMouseDownY(), 0);
					objTree->setProperty(Attributes::width, relativeEvent.getDistanceFromDragStartX(), 0);
					objTree->setProperty(Attributes::height, relativeEvent.getDistanceFromDragStartY(), 0);

					PropertyGroup *properties = new PropertyGroup(objTree);
					propertyView->setViewedComponent(properties);
				}
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
				selectedComponent = event.originalComponent;
			} else {
				if (selectedComponent != nullptr)
					selectedComponent = nullptr;
			}
		}
	}
	deselectTool();
}

void JUCE_Designer::mouseDoubleClick (const MouseEvent& event)
{
	Time e = event.eventTime;	//TODO: remove
}

bool JUCE_Designer::keyPressed (const KeyPress& key)
{
	if (key.isCurrentlyDown()) {}	//TODO: remove
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
}

void JUCE_Designer::focusOfChildComponentChanged (FocusChangeType cause)
{
	if (cause == 1) {}	//TODO: remove
}

void JUCE_Designer::focusGained (FocusChangeType cause)
{
	propertyView->grabKeyboardFocus();
}


//====================private methods================================

DynamicObject* JUCE_Designer::createObjectFromToolName (String *selectedToolName)
{
	if (selectedToolName->equalsIgnoreCase("juced_Label")) {
		juced_Label *object = new juced_Label();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_TextButton")) {
		juced_TextButton *object = new juced_TextButton();
		return (DynamicObject *)object;
	}
	return nullptr;
}

//===================================================================

void JUCE_Designer::Grid::paint (Graphics& g)
{
    g.fillAll (Colours::transparentWhite);
    g.setColour (Colours::black);
	float opacity = 0.1f;
	for (float x = 10.0f; x < (float) getWidth(); x+=10.0f) {
		opacity = (((int) x) % 40 == 0) ? 0.15f : 0.06f;
		g.drawLine(x, 0.0f, x, (float) getHeight(), opacity);
		g.drawLine(0.0f, x, (float) getWidth(), x, opacity);
	}
}

JUCE_Designer::Grid::Grid ()
{
	setAlwaysOnTop(true);
	setInterceptsMouseClicks(false, false);
}