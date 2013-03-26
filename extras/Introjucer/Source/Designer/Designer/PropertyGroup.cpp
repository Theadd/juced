/*
  ==============================================================================

    PropertyGroup.cpp
    Created: 20 Mar 2013 2:33:46pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "Constructor.h"
#include "Properties/TextWithButtonPropertyComponent.h"
#include "Properties/ColourPropertyComponent.cpp"
#include "Properties/EnumerationPropertyComponent.cpp"


class JUCED_PropertyGroup : public PropertyPanel
{
public:
	JUCED_PropertyGroup () : PropertyPanel()
    {
		setName ("Properties View");
    }

	JUCED_PropertyGroup (ValueTree *tree) : PropertyPanel()
	{
		setName ("Properties View");
		if (tree != nullptr) {
			setName((tree->hasProperty(Attributes::name)) ? tree->getProperty(Attributes::name) : "undefined");
			setName((tree->hasProperty(Attributes::objectType)) ? getName() + " : " + tree->getProperty(Attributes::objectType.toString()) : getName());
			Identifier t;
			for (int i = tree->getNumProperties(); --i >= 0;) {
				t = tree->getPropertyName(i);
				Attribute *attrib;
				if ((attrib = Constructor::getInstance()->getAttributeOf(t)) != nullptr) {
					if (attrib->visible) {
						//get propertycomponent object of specified type
						PropertyComponent *comp;
						if (attrib->type == AttributeType::colour) {
							comp = new JUCED_ColourPropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display);
						} else if (attrib->type == AttributeType::enumeration) {
							comp = new EnumerationPropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display, Constructor::getInstance()->getEnumerationsOf(attrib->name));
						} else {
							comp = new TextPropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display, 96, false);
						}
						//add object to specified group
						if (attrib->group.equalsIgnoreCase("General")) {
							generalGroup.add(comp);
						} else if (attrib->group.equalsIgnoreCase("Bounds")) {
							boundsGroup.add(comp);
						} else if (attrib->group.equalsIgnoreCase("Colours")) {
							coloursGroup.add(comp);
						} else if (attrib->group.equalsIgnoreCase("Behaviour")) {
							behaviourGroup.add(comp);
						}
					}
				}
			}
		}

		if (generalGroup.size() > 0) addSection("General", generalGroup);
		if (boundsGroup.size() > 0) addSection("Bounds", boundsGroup);
		if (coloursGroup.size() > 0) addSection("Colours", coloursGroup);
		if (behaviourGroup.size() > 0) addSection("Behaviour", behaviourGroup);

		refreshAll();
	}

private:
	Array<PropertyComponent*> boundsGroup;
	Array<PropertyComponent*> generalGroup;
	Array<PropertyComponent*> coloursGroup;
	Array<PropertyComponent*> behaviourGroup;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JUCED_PropertyGroup)
};
