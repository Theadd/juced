
#include "JUCE_Designer.h"

JUCE_Designer::JUCE_Designer ()
{
	//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "commented alert for copy & paste");
	setSize (800, 600);

	addAndMakeVisible(&grid, 10);
	
	JUCED_PropertyGroup *properties = new JUCED_PropertyGroup();
	propertyView = new PropertyView(properties);
	propertyView->setBounds(100, 100, 200, 400);

	addAndMakeVisible(&mousePositionLabel);
	mousePositionLabel.setAlwaysOnTop(true);
	mousePositionLabel.setFont(Font(12.0f));
	mousePositionLabel.setBounds(getWidth() - 80, getHeight() - 25, 80, 25);
	mousePositionLabel.setInterceptsMouseClicks(false, false);

	addAndMakeVisible(&infoLabel);
	infoLabel.setAlwaysOnTop(true);
	infoLabel.setFont(Font(12.0f));
	infoLabel.setBounds(5, getHeight() - 115, 350, 115);
	infoLabel.setInterceptsMouseClicks(false, false);
	infoLabel.setText("[Ctrl + R] Randomly resize grid\n[Ctrl + Z] Undo change history\n[Ctrl + Y] Redo change history\n[Ctrl + S] Save current design\n[Ctrl + O] Open last saved design\n[Ctrl + G] Generate design source code\n[Ctrl + TAB] Select parent of selected component\n[Hold Ctrl] Don't snap to grid when editing/drawing", false);
	infoLabel.setColour(Label::textColourId, Colours::white);
	infoLabel.setComponentEffect(new DropShadowEffect());

	Constructor *constructor = Constructor::getInstance();
	constructor->setWorkingDirectory(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()));
	constructor->loadAttributesFromXmlFile(File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "attributes.xml"));
	constructor->loadEnumerationsFromXmlFile(File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "enumerations.xml"));
	constructor->setDesigner(this);

	SelectionArea *selectionBox = constructor->getSelectionBox();
	addAndMakeVisible(selectionBox);
	selectionBox->setVisible(false);
}

JUCE_Designer::~JUCE_Designer()
{
	Constructor::log("D002 - ~JUCE_Designer() call");
	toolboxes.clear(true);
	selectionArea = nullptr;
	Constructor::log("D102 - Set viewed component of property view to null");
	propertyView->setViewedComponent(new JUCED_PropertyGroup());
	Constructor::log("D102 - Delete property view");
	propertyView = nullptr;
	Constructor::log("D102 - Remove all children");
	removeAllChildren();
	Constructor::log("D102 - Constructor::destroy()");
	Constructor::destroy();
	Constructor::log("D002 - Done (~JUCE_Designer())");
}

Component* JUCE_Designer::createToolbox (int itemsPerRow, int itemSize, int itemPadding) {
	Toolbox *toolbox = new Toolbox(itemsPerRow, itemSize, itemPadding);
	toolbox->setBounds(0, 0, 1, 1);
	toolbox->loadTooltips();
	toolboxes.add(toolbox);
	return toolbox;
}

void JUCE_Designer::addToolboxItem (Component* _toolbox, const String& name, const String& toolTip, const char* image, int imageSize) {
	Toolbox *toolbox = dynamic_cast<Toolbox*> (_toolbox);
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

void JUCE_Designer::writeXmlToFile (String _filename)
{
	Constructor::log("D001 - Export component's structure in XML format to " + _filename);
	if (Constructor::getInstance()->getBigTreeRoot() != nullptr) {
		XmlElement *obj_xml = Constructor::getInstance()->getBigTreeRoot()->createXml();

		//Create xml file from XmlElement
		File file = File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + _filename);
		file.create();
		obj_xml->writeToFile(file, "");
		file.revealToUser();

		delete obj_xml;
	}
}

void JUCE_Designer::generateCode ()
{
	Constructor::log("D003 - Generate code structure");
	if (Constructor::getInstance()->getBigTreeRoot() != nullptr) {

		File savePath;
		FileChooser myChooser ("Please select a directory to save the generated project", File::getSpecialLocation (File::userHomeDirectory), "*.*");
		if (myChooser.browseForDirectory()) {
			savePath = myChooser.getResult().getFullPathName();
		} else return;

		CodeGenerator codeGenerator(Constructor::getInstance()->getBigTreeRoot());
		String generatedCodeString = codeGenerator.getCode();
		Constructor::log("D103 - Code generated");
		//uncompress default template
		ZipFile defaultTemplateZip(File(File::addTrailingSeparator(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "Templates") + "default.zip"));
		defaultTemplateZip.uncompressTo(savePath, true);
		Constructor::log("D103 - Uncompressed template");
		File generatedCodeFile(File::addTrailingSeparator(savePath.getFullPathName()) + "Source" + File::separatorString + "GeneratedCode.cpp");
		String code(generatedCodeFile.loadFileAsString());
		code = code.replace("%generatedCode%", generatedCodeString);
		generatedCodeFile.replaceWithText(code);
		Constructor::log("D103 - Replaced GeneratedCode.cpp : " + generatedCodeFile.getFullPathName() + " SIZE: " + String(code.length()));

		//Main.cpp
		File mainFile(File::addTrailingSeparator(savePath.getFullPathName()) + "Source" + File::separatorString + "Main.cpp");
		String mainFileCode(mainFile.loadFileAsString());
		mainFileCode = mainFileCode.replace("%varName%", codeGenerator.getVarName());
		mainFile.replaceWithText(mainFileCode);
		//File file = File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + _filename);
		//file.create();
		//file.replaceWithText(codeGenerator.getCode());
		system(String("AStyle.exe -n --style=allman " + File::addTrailingSeparator(savePath.getFullPathName()) + "Source" + File::separatorString + "GeneratedCode.cpp").getCharPointer());
		savePath.revealToUser();
	}
}

void JUCE_Designer::selectComponent (Component *componentToSelect, bool isSelectedTwice = false)
{
	SelectionArea *selectionBox = Constructor::getInstance()->getSelectionBox();

	if (componentToSelect != this) {
		selectionBox->setVisible(false);

		Constructor::log("D104 - removeComponentListener(selectionBox)");
		if (Constructor::getInstance()->getSelectedComponent() != nullptr)
			Constructor::getInstance()->getSelectedComponent()->removeComponentListener(selectionBox);

		Point<int> pos = componentToSelect->getScreenPosition() - this->getScreenPosition();
		selectedComponentPositionDifference = pos - componentToSelect->getPosition();
		selectionBox->setSelectionBounds(pos.getX(), pos.getY(), componentToSelect->getWidth(), componentToSelect->getHeight());
		Constructor::getInstance()->setSelectedComponent(componentToSelect);

		BigTree valueTree(Constructor::getInstance()->getBigTreeRoot()->getChildWithProperty(Attributes::ID, componentToSelect->getComponentID(), true));

		bool allowTransform = true;
		if (valueTree.hasProperty(Attributes::allowTransform))
				allowTransform = valueTree.getProperty(Attributes::allowTransform);

		selectionBox->setAllowTransform(allowTransform);

		//AlertWindow::showMessageBox(AlertWindow::NoIcon, "SELECTED COMPONENT ID", valueTree.getProperty(Attributes::ID).toString());

		JUCED_PropertyGroup *properties = new JUCED_PropertyGroup(&valueTree);
		propertyView->setViewedComponent(properties);
		selectionBox->setVisible(true);

		
		componentToSelect->addComponentListener(selectionBox);

		if (valueTree.getProperty(Attributes::objectType).toString().equalsIgnoreCase("Window") && !isSelectedTwice)
			selectComponent(componentToSelect, true);

	} else {
		//set selection box invisible and clean properties window since user clicked the editor itself
		selectionBox->setVisible(false);

		/*if (selectedComponent != nullptr)
			selectedComponent->removeComponentListener(selectionBox);*/

		JUCED_PropertyGroup *properties = new JUCED_PropertyGroup();
		propertyView->setViewedComponent(properties);
		//bring properties view to front (just in case)
		propertyView->toFront(false);
	}
}

void JUCE_Designer::paint (Graphics& g)
{
    g.fillAll (Colour((uint8) 49, (uint8) 124, (uint8) 205));
	#ifdef __JUCER_APPEARANCESETTINGS_H_34D762C7__
		IntrojucerLookAndFeel::fillWithBackgroundTexture (*this, g);
	#endif
}

void JUCE_Designer::resized()
{
	grid.setBounds(0, 0, getWidth(), getHeight());
	mousePositionLabel.setBounds(getWidth() - mousePositionLabel.getWidth(), getHeight() - mousePositionLabel.getHeight(), mousePositionLabel.getWidth(), mousePositionLabel.getHeight());
	infoLabel.setBounds(5, getHeight() - infoLabel.getHeight(), 350, infoLabel.getHeight());
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
	bool ctrlKeyDown = event.mods.isCtrlDown();

	if (getSelectedToolName()->isNotEmpty()) {
		selectionArea = new SelectionArea();
		addAndMakeVisible(selectionArea);
		MouseEvent relativeEvent = event.getEventRelativeTo(this);
		selectionArea->setSelectionBounds(relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), 1, 1, !ctrlKeyDown, !ctrlKeyDown);

	} else {
		if (event.originalComponent == Constructor::getInstance()->getSelectedComponent()) {
			//user is going to move the component using drag & drop
			componentPositionOnDragStart = event.originalComponent->getScreenPosition() - this->getScreenPosition();
		}
	}
	
}

void JUCE_Designer::mouseDrag (const MouseEvent& event)
{
	if (selectionArea != nullptr) {
		//creating a new component
		bool ctrlKeyDown = event.mods.isCtrlDown();
		MouseEvent relativeEvent = event.getEventRelativeTo(this);
		selectionArea->setSelectionBounds(relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY(), !ctrlKeyDown, !ctrlKeyDown, !ctrlKeyDown, !ctrlKeyDown);

	} else if (event.originalComponent == Constructor::getInstance()->getSelectedComponent()) {
		//moving an existing component
		bool ctrlKeyDown = event.mods.isCtrlDown();
		Constructor::getInstance()->getSelectionBox()->setListenToChanges(false);
		
		Constructor::getInstance()->getSelectionBox()->setSelectionBounds(componentPositionOnDragStart.getX() + event.getDistanceFromDragStartX(), componentPositionOnDragStart.getY() + event.getDistanceFromDragStartY(), Constructor::getInstance()->getSelectedComponent()->getWidth(), Constructor::getInstance()->getSelectedComponent()->getHeight(), !ctrlKeyDown, !ctrlKeyDown);
	}
}

void JUCE_Designer::mouseUp (const MouseEvent& event)
{
	Constructor::getInstance()->getSelectionBox()->setListenToChanges(true);

	String *selectedToolName = getSelectedToolName();
	if (!event.mouseWasClicked()) {
		if (selectedToolName->isNotEmpty()) {

			MouseEvent relativeEvent = event.getEventRelativeTo(event.originalComponent);
			Constructor *constructor = Constructor::getInstance();

			Rectangle<int> bounds(relativeEvent.getMouseDownX() - constructor->getDrawBoundsModX(), relativeEvent.getMouseDownY()  - constructor->getDrawBoundsModY(), relativeEvent.getDistanceFromDragStartX() - constructor->getDrawBoundsModWidth(), relativeEvent.getDistanceFromDragStartY() - constructor->getDrawBoundsModHeight());
			Component* newComponent = constructor->createComponent(*selectedToolName, event.originalComponent->getComponentID(), bounds);

			if (newComponent != nullptr)
				selectComponent(newComponent);

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
	mousePositionLabel.setText(String(key.getKeyCode()), 0);
	if (key.getKeyCode() == 90 && key.getModifiers().isCtrlDown()) {
		Constructor::getInstance()->getSelectionBox()->setVisible(false);
		Constructor::getInstance()->getSelectionBox()->setListenToChanges(false);
		Constructor::getInstance()->getUndoManager()->undo();
		Constructor::getInstance()->getSelectionBox()->setListenToChanges(true);
	} else if (key.getKeyCode() == 89 && key.getModifiers().isCtrlDown()) {
		Constructor::getInstance()->getSelectionBox()->setVisible(false);
		Constructor::getInstance()->getSelectionBox()->setListenToChanges(false);
		Constructor::getInstance()->getUndoManager()->redo();
		Constructor::getInstance()->getSelectionBox()->setListenToChanges(true);
	} else if (key.getKeyCode() == 82 && key.getModifiers().isCtrlDown()) {
		int rand = 0;
		while ((rand = Random::getSystemRandom().nextInt() % 21) < 4);
		Constructor::getInstance()->setGridSize(rand);
		grid.repaint();
		mousePositionLabel.setText(String(Constructor::getInstance()->getGridSize()), 0);
	/*} else if (key.getKeyCode() == 83 && key.getModifiers().isCtrlDown()) {	//export
		this->writeXmlToFile("save.xml");
	} else if (key.getKeyCode() == 79 && key.getModifiers().isCtrlDown()) {	//import
		Constructor::getInstance()->resetCurrentState();
		Constructor::getInstance()->importFromXml(File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "save.xml"));
	*/
	} else if (key.getKeyCode() == 71 && key.getModifiers().isCtrlDown()) {
		this->generateCode();
	} else if (key.getKeyCode() == key.leftKey) {
		if (Constructor::getInstance()->getSelectedComponent() != nullptr) {
			BigTree valueTree(Constructor::getInstance()->getBigTreeRoot()->getChildWithProperty(Attributes::ID, Constructor::getInstance()->getSelectedComponent()->getComponentID(), true));
			int currentPosX = valueTree.getProperty(Attributes::x);
			valueTree.setProperty(Attributes::x, currentPosX - 1, Constructor::getInstance()->getUndoManager());
		}
	} else if (key.getKeyCode() == key.rightKey) {
		if (Constructor::getInstance()->getSelectedComponent() != nullptr) {
			BigTree valueTree(Constructor::getInstance()->getBigTreeRoot()->getChildWithProperty(Attributes::ID, Constructor::getInstance()->getSelectedComponent()->getComponentID(), true));
			int currentPosX = valueTree.getProperty(Attributes::x);
			valueTree.setProperty(Attributes::x, currentPosX + 1, Constructor::getInstance()->getUndoManager());
		}
	} else if (key.getKeyCode() == key.upKey) {
		if (Constructor::getInstance()->getSelectedComponent() != nullptr) {
			BigTree valueTree(Constructor::getInstance()->getBigTreeRoot()->getChildWithProperty(Attributes::ID, Constructor::getInstance()->getSelectedComponent()->getComponentID(), true));
			int currentPosY = valueTree.getProperty(Attributes::y);
			valueTree.setProperty(Attributes::y, currentPosY - 1, Constructor::getInstance()->getUndoManager());
		}
	} else if (key.getKeyCode() == key.downKey) {
		if (Constructor::getInstance()->getSelectedComponent() != nullptr) {
			BigTree valueTree(Constructor::getInstance()->getBigTreeRoot()->getChildWithProperty(Attributes::ID, Constructor::getInstance()->getSelectedComponent()->getComponentID(), true));
			int currentPosY = valueTree.getProperty(Attributes::y);
			valueTree.setProperty(Attributes::y, currentPosY + 1, Constructor::getInstance()->getUndoManager());
		}
	} else if (key.getKeyCode() == 9 && key.getModifiers().isCtrlDown()) {
		try {
			if (Constructor::getInstance()->getSelectedComponent() != nullptr) {
				Component *selectedParent = Constructor::getInstance()->getSelectedComponent()->getParentComponent();
				if (selectedParent != nullptr && selectedParent != this) {
					selectComponent(selectedParent);
					selectComponent(selectedParent);
				}
			}
		} catch (...) {
			DBG(("Exception caught while selecting parent component of selected component"));
		}
	}
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
	SelectionArea *selectionBox = Constructor::getInstance()->getSelectionBox();

	if (child == selectionBox) {
		if (Constructor::getInstance()->getSelectedComponent() != nullptr && selectionBox->isReady()) {

			BigTree valueTree(Constructor::getInstance()->getBigTreeRoot()->getChildWithProperty(Attributes::ID, Constructor::getInstance()->getSelectedComponent()->getComponentID(), true));
			valueTree.setProperty(Attributes::width, child->getWidth() - (selectionBox->getBoxSize() * 2), Constructor::getInstance()->getUndoManager());
			valueTree.setProperty(Attributes::height, child->getHeight() - (selectionBox->getBoxSize() * 2), Constructor::getInstance()->getUndoManager());
			valueTree.setProperty(Attributes::x, child->getX() + selectionBox->getBoxSize() - selectedComponentPositionDifference.getX(), Constructor::getInstance()->getUndoManager());
			valueTree.setProperty(Attributes::y, child->getY() + selectionBox->getBoxSize() - selectedComponentPositionDifference.getY(), Constructor::getInstance()->getUndoManager());

		}
	}

}

//===================================================================

void JUCE_Designer::Grid::paint (Graphics& g)
{
	float gridSize = (float) Constructor::getInstance()->getGridSize();
	int doubleLineInterval = 85 - (85 % (int) gridSize);
	g.fillAll (Colours::transparentWhite);
    g.setColour (Colours::white);
	for (float x = gridSize; x < (float) getWidth(); x += gridSize) {
		g.setOpacity((((int) x) % doubleLineInterval == 0) ? 0.15f : 0.06f);
		g.drawVerticalLine((int)x, 0.0f, (float) getHeight());
		g.drawHorizontalLine((int)x, 0.0f, (float) getWidth());
		if (((int) x) % doubleLineInterval == 0) {
			g.setOpacity(0.35f);
			for (float i = (float) (int)(getHeight() / doubleLineInterval + 1); --i > 0;) {
				g.drawVerticalLine((int)x, ((float) doubleLineInterval) * i - 3.0f, ((float) doubleLineInterval) * i + 4.0f);
				g.drawHorizontalLine(doubleLineInterval * ((int) i), x - 3.0f, x + 4.0f);
			}
		}
	}
}

JUCE_Designer::Grid::Grid ()
{
	setAlwaysOnTop(true);
	setInterceptsMouseClicks(false, false);
}