/*
  ==============================================================================

    Constructor.cpp
    Created: 16 Mar 2013 4:58:15pm
    Author:  admin

  ==============================================================================
*/

#include "Constructor.h"

// Global static pointer used to ensure a single instance of the class.
Constructor* Constructor::m_pInstance = NULL; 

Constructor* Constructor::getInstance()
{
   if (!m_pInstance) {   // Only allow one instance of class to be generated.
      m_pInstance = new Constructor;
	  m_pInstance->setGridSize(5);
	  m_pInstance->_bigTreeRoot = new BigTree();
   }

   return m_pInstance;
}


void Constructor::loadAttributesFromXmlFile(const File &xmlFile)
{

	XmlElement *xml = XmlDocument::parse(xmlFile)->getFirstChildElement();

	while (xml != nullptr)
	{
		Attribute *t = new Attribute;
		t->name = xml->getStringAttribute("name");
		t->group = xml->getStringAttribute("group");
		t->visible = xml->getBoolAttribute("visible");
		t->type = xml->getStringAttribute("type");
		t->display = xml->getStringAttribute("display");
		t->valueType = xml->getStringAttribute("valueType");
		_attributes.add(t);

		xml = xml->getNextElement();
	}

}

void Constructor::loadEnumerationsFromXmlFile(const File &xmlFile)
{

	XmlElement *xml = XmlDocument::parse(xmlFile)->getFirstChildElement();

	while (xml != nullptr)
	{
		_Enumerations *e = new _Enumerations;
		e->name = xml->getStringAttribute("name");
		e->enumerations = new Array< Enumeration* >;

		XmlElement *child = xml->getFirstChildElement();

		while (child != nullptr)
		{
			Enumeration *t = new Enumeration;
			t->name = child->getStringAttribute("name");
			t->display = child->getStringAttribute("display");
			t->value = child->getIntAttribute("value");
			e->enumerations->add(t);
			child = child->getNextElement();
		}
		_enumerations.add(*e);

		xml = xml->getNextElement();
	}

}

Attribute* Constructor::getAttributeOf(Identifier _name)
{
	for (int i = _attributes.size(); --i >= 0;)
		if (_attributes[i]->name == _name)
			return _attributes[i];

	return nullptr;
}

Array< Enumeration* >* Constructor::getEnumerationsOf(Identifier _name)
{
	for (int i = _enumerations.size(); --i >= 0;)
		if (_enumerations[i].name == _name)
			return _enumerations[i].enumerations;

	return nullptr;
}

UndoManager* Constructor::getUndoManager() {
	if (undoManager == nullptr)
		undoManager = new UndoManager();
	
	return undoManager;
}

void Constructor::setDrawBoundsMod(int x, int y, int width, int height)
{
	_drawBoundsModX = x;
	_drawBoundsModY = y;
	_drawBoundsModWidth = width;
	_drawBoundsModHeight = height;
}

int Constructor::getDrawBoundsModX()
{
	return _drawBoundsModX;
}

int Constructor::getDrawBoundsModY()
{
	return _drawBoundsModY;
}

int Constructor::getDrawBoundsModWidth()
{
	return _drawBoundsModWidth;
}

int Constructor::getDrawBoundsModHeight()
{
	return _drawBoundsModHeight;
}

void Constructor::setGridSize(int newGridSize)
{
	_gridSize = newGridSize;
}

int Constructor::getGridSize()
{
	return _gridSize;
}

SelectionArea* Constructor::getSelectionBox()
{
	if (_selectionBox == nullptr) {
		_selectionBox = new SelectionArea(true);
		_selectionBox->setAlwaysOnTop(true);
		_selectionBox->setInterceptsMouseClicks(false, true);
	}

	return _selectionBox;
}

void Constructor::log(String msg)
{
	File logFile(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "designer.log");
	//Create log file if it does not exists
	if (!logFile.exists())
		logFile.create();
	//Apply format
	String::CharPointerType pointer(msg.getCharPointer());
	for (; !pointer.isDigit(); pointer++);
	int logType = (int)(pointer[0]) - 48;
	switch (logType) {
	case 0:
		msg = Time::getCurrentTime().formatted("%M:%S") + ": " + msg;
		break;
	case 1:
		msg = "\t[INFO] " + Time::getCurrentTime().formatted("%M:%S") + ": " + msg;
		break;
	case 2:
		msg = "\t[WARNING] " + Time::getCurrentTime().formatted("%M:%S") + ": " + msg;
		break;
	case 3:
		msg = "\t[ERROR] " + Time::getCurrentTime().formatted("%M:%S") + ": " + msg;
		break;
	}
	//Append msg to log file
	logFile.appendText(msg + "\n");
}

void Constructor::setDesigner(Component* juce_designer)
{
	_designer = juce_designer;
}

Component* Constructor::getDesigner()
{
	jassert (_designer != nullptr);
	return _designer;
}

void Constructor::setBigTreeRoot(BigTree *bigTreeRoot)
{
	//_bigTreeRoot = bigTreeRoot;
	if (bigTreeRoot != nullptr) {
		*_bigTreeRoot = BigTree(*bigTreeRoot);
	} else {
		_bigTreeRoot = new BigTree();
	}
}

BigTree* Constructor::getBigTreeRoot()
{
	if (_bigTreeRoot != nullptr && _bigTreeRoot->isValid())
		return _bigTreeRoot;

	return nullptr;
}

Component* Constructor::createComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds)
{
	PlaceableComponent *newComponent = new PlaceableComponent(selectedToolName, parentComponentID, bounds);
	getUndoManager()->perform(newComponent, "Create new " + selectedToolName);
	//getUndoManager()->setCurrentTransactionName("Create new " + selectedToolName);
	if (selectedToolName == "juced_Window") {
		bounds.setX(0);
		bounds.setY(0);
		bounds.setHeight(bounds.getHeight() - (dynamic_cast<DocumentWindow*> (newComponent->getComponent()))->getTitleBarHeight());
		PlaceableComponent *childComponent = new PlaceableComponent("juced_MainComponent", newComponent->getComponent()->getComponentID(), bounds);
		getUndoManager()->perform(childComponent);
		(dynamic_cast<DocumentWindow*> (newComponent->getComponent()))->setContentOwned(childComponent->getComponent(), true);
	}
	getUndoManager()->beginNewTransaction();
	return newComponent->getComponent();
}
/*	juced_MainComponent *comp = new juced_MainComponent();
	comp->setProperty(Attributes::x, 0);
	comp->setProperty(Attributes::y, 0);
	comp->setProperty(Attributes::width, win->getWidth());
	comp->setProperty(Attributes::height, win->getHeight() - win->getTitleBarHeight());
	win->setContentOwned(comp, true);
	win->getContentComponent()->addMouseListener(this, true);
	BigTree *compTree = new BigTree(comp, comp->getProperty(Attributes::objectType));
	if (parent == this) {
		bigTree = new BigTree(win, win->getProperty(Attributes::objectType));
		Constructor::getInstance()->setBigTreeRoot(bigTree);
		bigTree->addChild(*compTree, -1, 0);
	} else {
		BigTree *objTree = new BigTree(win, win->getProperty(Attributes::objectType));
		BigTree parentTree(bigTree->getChildWithProperty(Attributes::ID, parent->getComponentID(), true));
		jassert (parentTree.isValid());		//this should not happen
		parentTree.addChild(*objTree, -1, 0);
		objTree->addChild(*compTree, -1, 0);
	}*/