/*
  ==============================================================================

    Importer.cpp
    Created: 12 Apr 2013 9:39:40pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "BigTree.h"
#include "Constructor.h"
#include "Importer.h"


Importer::Importer(File xmlFile)
{
	Constructor::log("I001 - Importer constructor call");
	XmlElement *xml = XmlDocument::parse(xmlFile);

	create(xml);
	delete xml;
}

Importer::Importer(XmlElement *xml, String parentComponentID)
{
	Constructor::log("I002 - Importer child constructor call");
	create(xml, parentComponentID);
}

void Importer::create(XmlElement *xml, String parentComponentID)
{
	Constructor::log("I003 - Importer create call");
	Constructor *constructor = Constructor::getInstance();

	//getting required fields to create the component
	String toolName = xml->getStringAttribute("toolName");
	String id = xml->getStringAttribute("id");
	Rectangle<int> bounds(xml->getIntAttribute("x"), xml->getIntAttribute("y"), xml->getIntAttribute("width"), xml->getIntAttribute("height"));
	//creating the component
	Component *newComponent = constructor->createComponent(toolName, parentComponentID, bounds, id, false);
	//get newComponent's BigTree
	BigTree bTree(constructor->getBigTreeRoot()->getChildWithProperty(Attributes::ID, id, true));
	jassert(bTree.isValid());
	//apply other properties
	for (int i = xml->getNumAttributes(); --i >= 0;) {
		String attributeName = xml->getAttributeName(i);
		//skip attributes we already dealt with when creating the component
		if (attributeName == "toolName") continue;
		if (attributeName == "id") continue;
		if (attributeName == "x") continue;
		if (attributeName == "y") continue;
		if (attributeName == "width") continue;
		if (attributeName == "height") continue;
		
		String attributeValue = xml->getAttributeValue(i);

		/*Attribute *attrib = constructor->getAttributeOf(Identifier(attributeName));
		if (attrib != nullptr) {
			if (attrib->type == AttributeType::file) {
				attributeValue = attributeValue.replace("%workingDirectory%", constructor->getWorkingDirectory());
			}
		}*/
		//set object property
		Constructor::log("I103 - Set property " + attributeName);
		bTree.setProperty(attributeName, attributeValue, 0);

	}
	Constructor::log("I103 - Recursively deal with its children");
	//recursively deal with its children
	forEachXmlChildElement (*xml, xmlnode)
	{
		Importer importer(xmlnode, id);
	}
	Constructor::log("I103 - Done");
}