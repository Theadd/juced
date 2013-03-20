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


class PropertyGroup : public PropertyPanel
{
public:
	PropertyGroup () : PropertyPanel()
    {
		setName ("Properties View");
    }

	PropertyGroup (ValueTree *tree) : PropertyPanel()
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
							comp = new ColourPropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display);
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
						}
					}
				}
			}
		}

		if (generalGroup.size() > 0) addSection("General", generalGroup);
		if (boundsGroup.size() > 0) addSection("Bounds", boundsGroup);
		if (coloursGroup.size() > 0) addSection("Colours", coloursGroup);

		refreshAll();
	}

private:
	Array<PropertyComponent*> boundsGroup;
	Array<PropertyComponent*> generalGroup;
	Array<PropertyComponent*> coloursGroup;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyGroup)
};
