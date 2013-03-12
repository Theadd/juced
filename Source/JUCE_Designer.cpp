
#include "JUCE_Designer.h"

JUCE_Designer::JUCE_Designer ()
{
	setSize (800, 600);
	
	PropertiesComponent *properties = new PropertiesComponent("Properties View");
	propertiesViewport = new PropertyPanelViewport(properties);
	addAndMakeVisible(propertiesViewport);
	propertiesViewport->setBounds(32, 0, 200, 400);
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
	//juced_Window::Ptr pWin = new juced_Window();
	//juced_Window *win = pWin.getObject();
	juced_Window *win = new juced_Window();

	win->setBounds(x, y, (width >= win->minWidth) ? width : win->minWidth, (height >= win->minHeight) ? height : win->minHeight);

	bigTree = new BigTree(win, win->getProperty(Ids::objectType));

	parent->addAndMakeVisible(win);


	//setContentOwned (new juced_MainComponent(), true);
	//juced_MainComponent::Ptr pComp = new juced_MainComponent();
	//juced_MainComponent *comp = pComp.getObject();
	juced_MainComponent *comp = new juced_MainComponent();
	win->setContentOwned(comp, true);
	BigTree *compTree = new BigTree(comp, comp->getProperty(Ids::objectType));
	bigTree->addChild(*compTree, -1, 0);
	win->getContentComponent()->addMouseListener(this, true);

	PropertiesComponent *properties = new PropertiesComponent(win->getProperty(Ids::objectType).toString(), bigTree);
	propertiesViewport->setViewedComponent(properties);

}


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

			ValueTree parentTree;
			if (event.originalComponent != this)
				parentTree = bigTree->getChildWithProperty(Ids::ID, event.originalComponent->getComponentID());

			MouseEvent relativeEvent = event.getEventRelativeTo(event.originalComponent);

			if (selectedToolName->equalsIgnoreCase("juced_Window")) {
				addWindow(event.originalComponent, relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());
			} else if (selectedToolName->equalsIgnoreCase("juced_Label")) {
				//juced_Label::Ptr pLabel = new juced_Label();
				//juced_Label *label = pLabel.getObject();
				juced_Label *label = new juced_Label();
				//label->setText("label1", false);
				event.originalComponent->addAndMakeVisible(label);
				label->setBounds(relativeEvent.getMouseDownX(), relativeEvent.getMouseDownY(), relativeEvent.getDistanceFromDragStartX(), relativeEvent.getDistanceFromDragStartY());
				label->addMouseListener(this, false);
				//juced_Labels.add(label);

				BigTree *labelTree = new BigTree(label, label->getProperty(Ids::objectType));
				if (parentTree.isValid()) {
					parentTree.addChild(*labelTree, -1, 0);
				} else AlertWindow::showMessageBox(AlertWindow::NoIcon, "parent tree", "is not valid");

				PropertiesComponent *properties = new PropertiesComponent(label->getProperty(Ids::objectType).toString(), labelTree);
				propertiesViewport->setViewedComponent(properties);

				//TODO: remove
				//XmlElement *obj_xml = bigTree->createXml();

				//Create xml file from XmlElement
				//File file = File(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "test.xml");
				//file.create();
				//obj_xml->writeToFile(file, "");
				//file.revealToUser();
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