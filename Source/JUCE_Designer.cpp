
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
	
	Constructor *constructor = Constructor::getInstance();
	constructor->loadAttributesFromXmlFile(File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "attributes.xml"));

	selectionBox = new SelectionArea(true);
	addAndMakeVisible(selectionBox);
	selectionBox->setAlwaysOnTop(true);
	selectionBox->setInterceptsMouseClicks(false, true);
	selectionBox->setVisible(false);
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

void JUCE_Designer::addWindow (Component *parent, int x, int y, int width, int height)
{
	if (parent == this && bigTree != nullptr) return;	//only one main window allowed

	juced_Window *win = new juced_Window();
	parent->addAndMakeVisible(win);
	win->setBounds(x, y, (width >= win->minWidth) ? width : win->minWidth, (height >= win->minHeight) ? height : win->minHeight);
	
	win->setProperty(Attributes::x, x);
	win->setProperty(Attributes::y, y);
	win->setProperty(Attributes::width, (width >= win->minWidth) ? width : win->minWidth);
	win->setProperty(Attributes::height, (height >= win->minHeight) ? height : win->minHeight);

	

	juced_MainComponent *comp = new juced_MainComponent();
	comp->setProperty(Attributes::x, 0);
	comp->setProperty(Attributes::y, 0);
	comp->setProperty(Attributes::width, win->getWidth());
	comp->setProperty(Attributes::height, win->getHeight() - win->getTitleBarHeight());
	win->setContentOwned(comp, true);
	win->getContentComponent()->addMouseListener(this, true);
	BigTree *compTree = new BigTree(comp, comp->getProperty(Attributes::objectType));
	if (parent == this) {
		bigTree = new BigTree(win, win->getProperty(Attributes::objectType));
		bigTree->addChild(*compTree, -1, 0);
	} else {
		BigTree *objTree = new BigTree(win, win->getProperty(Attributes::objectType));
		BigTree parentTree(bigTree->getChildWithProperty(Attributes::ID, parent->getComponentID(), true));
		jassert (parentTree.isValid());		//this should not happen
		parentTree.addChild(*objTree, -1, 0);
		objTree->addChild(*compTree, -1, 0);
	}

	selectComponent(comp);

}

void JUCE_Designer::writeXmlToFile (String _filename)
{
	XmlElement *obj_xml = bigTree->createXml();

	//Create xml file from XmlElement
	File file = File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + _filename);
	file.create();
	obj_xml->writeToFile(file, "");
	file.revealToUser();
}

void JUCE_Designer::selectComponent (Component *componentToSelect)
{
	if (componentToSelect != this) {
		selectionBox->setVisible(false);
		Point<int> pos = componentToSelect->getScreenPosition() - this->getScreenPosition();
		selectedComponentPositionDifference = pos - componentToSelect->getPosition();
		selectionBox->setSelectionBounds(pos.getX(), pos.getY(), componentToSelect->getWidth(), componentToSelect->getHeight());
		selectedComponent = componentToSelect;

		BigTree valueTree(bigTree->getChildWithProperty(Attributes::ID, selectedComponent->getComponentID(), true));

		PropertyGroup *properties = new PropertyGroup(&valueTree);
		propertyView->setViewedComponent(properties);
		selectionBox->setVisible(true);

	} else {
		//set selection box invisible and clean properties window since user clicked the editor itself
		selectionBox->setVisible(false);
		PropertyGroup *properties = new PropertyGroup();
		propertyView->setViewedComponent(properties);
		//bring properties view to front (just in case)
		propertyView->toFront(false);
	}
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

			BigTree parentTree;
			if (event.originalComponent != this) {
				BigTree bTree(bigTree->getChildWithProperty(Attributes::ID, event.originalComponent->getComponentID(), true));
				if (bTree.isValid()) parentTree = bTree;
			}

			MouseEvent relativeEvent = event.getEventRelativeTo(event.originalComponent);

			if (selectedToolName->equalsIgnoreCase("juced_Window")) {
				addWindow(event.originalComponent, relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());
			} else {
				//Create a component of the selected tool name unless it is placed outside a window
				if (parentTree.isValid()) {
					DynamicObject *dynamicObj;
					if ((dynamicObj = createObjectFromToolName(selectedToolName)) != nullptr) {

						event.originalComponent->addAndMakeVisible(dynamic_cast<Component *> (dynamicObj));
						(dynamic_cast<Component *> (dynamicObj))->addMouseListener(this, false);

						BigTree *objTree = new BigTree(dynamicObj, dynamicObj->getProperty(Attributes::objectType));
					
						parentTree.addChild(*objTree, -1, 0);

						objTree->setProperty(Attributes::x, relativeEvent.getMouseDownX(), 0);
						objTree->setProperty(Attributes::y, relativeEvent.getMouseDownY(), 0);
						objTree->setProperty(Attributes::width, relativeEvent.getDistanceFromDragStartX(), 0);
						objTree->setProperty(Attributes::height, relativeEvent.getDistanceFromDragStartY(), 0);

						selectComponent(dynamic_cast<Component *> (dynamicObj));
						//PropertyGroup *properties = new PropertyGroup(objTree);
						//propertyView->setViewedComponent(properties);
						//activePropertyGroup = properties;
						//selectedComponentTree = objTree;
					}
				}
			}
			selectionArea = nullptr;
		}
	} else {
		if (selectedToolName->isEmpty()) {
			//Selecting an object
			selectComponent(event.originalComponent);
		}
	}
	deselectTool();
}

void JUCE_Designer::mouseDoubleClick (const MouseEvent& event)
{
	Time e = event.eventTime;	//useless - to avoid warnings
}

bool JUCE_Designer::keyPressed (const KeyPress& key)
{
	if (key.getKeyCode() == 90) {
		Constructor::getInstance()->getUndoManager()->undo();
	} else if (key.getKeyCode() == 89) {
		Constructor::getInstance()->getUndoManager()->redo();
	}
	mousePositionLabel.setText(String(key.getKeyCode()), 0);
    return false;  // Return true if your handler uses this key event, or false to allow it to be passed-on.
}

void JUCE_Designer::focusOfChildComponentChanged (FocusChangeType cause)
{
	if (cause == 1) {}	//useless - to avoid warnings
}

void JUCE_Designer::focusGained (FocusChangeType cause)
{
	if (cause == 1) {}	//useless - to avoid warnings
}

void JUCE_Designer::childBoundsChanged (Component * child)
{
	if (child == selectionBox) {
		if (selectedComponent != nullptr && selectionBox->isReady()) {

			BigTree valueTree(bigTree->getChildWithProperty(Attributes::ID, selectedComponent->getComponentID(), true));
			valueTree.setProperty(Attributes::width, child->getWidth() - (selectionBox->getBoxSize() * 2), Constructor::getInstance()->getUndoManager());
			valueTree.setProperty(Attributes::height, child->getHeight() - (selectionBox->getBoxSize() * 2), Constructor::getInstance()->getUndoManager());
			valueTree.setProperty(Attributes::x, child->getX() + selectionBox->getBoxSize() - selectedComponentPositionDifference.getX(), Constructor::getInstance()->getUndoManager());
			valueTree.setProperty(Attributes::y, child->getY() + selectionBox->getBoxSize() - selectedComponentPositionDifference.getY(), Constructor::getInstance()->getUndoManager());

		}
	} else if (child == selectedComponent) {
		//selected component bounds changed, if it was not done using the selectionBox, update selectionBox bounds
		/*bool resizeSelection = false;
		if (abs((child->getX() + selectedComponentPositionDifference.getX()) - selectionBox->getX()) > 2 * selectionBox->getBoxSize())
			resizeSelection = true;
		if (abs((child->getY() + selectedComponentPositionDifference.getY()) - selectionBox->getY()) > 2 * selectionBox->getBoxSize())
			resizeSelection = true;
		if (abs(selectionBox->getWidth() - child->getWidth()) > 2 * selectionBox->getBoxSize())
			resizeSelection = true;
		if (abs(selectionBox->getHeight() - child->getHeight()) > 2 * selectionBox->getBoxSize())
			resizeSelection = true;
		if (resizeSelection)
			selectComponent(child);*/
	}

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