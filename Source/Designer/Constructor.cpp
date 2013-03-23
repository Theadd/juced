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
	  m_pInstance->_bigTreeRoot = nullptr;
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

void Constructor::displayMsg(String msg)
{
	//dynamic_cast<JUCE_Designer *> (Constructor::getInstance()->getDesigner())->displayMsg(msg);
	Constructor *instance = Constructor::getInstance();
	if (instance->_msgDisplay == nullptr) {
		instance->_msgDisplay = new TextEditor("Display");
		instance->getDesigner()->addAndMakeVisible(instance->_msgDisplay);
		instance->_msgDisplay->setMultiLine(true);
		instance->_msgDisplay->setAlwaysOnTop(true);
		instance->_msgDisplay->setFont(Font(12.0f));
		instance->_msgDisplay->setBounds(0, instance->getDesigner()->getHeight() - 150, 800, 150);
		instance->_msgDisplay->setInterceptsMouseClicks(false, false);
		instance->_msgDisplay->setColour(TextEditor::backgroundColourId, Colours::transparentBlack);
		instance->_msgDisplay->setScrollbarsShown(false);
		BorderSize<int> border(0);
		instance->_msgDisplay->setBorder(border);
	}
	instance->_msgDisplay->setText(instance->_msgDisplay->getText() + "\n" + msg);
	instance->_msgDisplay->moveCaretToEnd();
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
	_bigTreeRoot = bigTreeRoot;
}

BigTree* Constructor::getBigTreeRoot()
{
	if (_bigTreeRoot != nullptr)
		return _bigTreeRoot;

	return nullptr;
}

Component* Constructor::createComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds)
{
	PlaceableComponent *newComponent = new PlaceableComponent(selectedToolName, parentComponentID, bounds);
	getUndoManager()->perform(newComponent, "Create new " + selectedToolName);
	return newComponent->getComponent();
}