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
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new Constructor;

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

Attribute* Constructor::getAttributeOf(Identifier _name)
{
	for (int i = _attributes.size(); --i >= 0;)
		if (_attributes[i]->name == _name)
			return _attributes[i];

	return nullptr;
}

UndoManager* Constructor::getUndoManager() {
	if (undoManager == nullptr)
		undoManager = new UndoManager();
	
	return undoManager;
}