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
#include "Properties/FilePropertyComponent.cpp"


class JUCED_PropertyGroup : public PropertyPanel
{
public:
	JUCED_PropertyGroup () : PropertyPanel()
    {
		setName ("Properties View");
    }

	~JUCED_PropertyGroup()
	{
		Constructor::log("PG001 - ~JUCED_PropertyGroup() call");
		boundsGroup.clear();
		generalGroup.clear();
		coloursGroup.clear();
		appearanceGroup.clear();
		Constructor::log("PG101 - done");
	}

	JUCED_PropertyGroup (ValueTree *tree) : PropertyPanel()
	{
		setName ("Properties View");
		bool allowTransform = true;
		if (tree != nullptr) {
			setName((tree->hasProperty(Attributes::name)) ? tree->getProperty(Attributes::name) : "undefined");
                        String propertyAsString = tree->getProperty(Attributes::objectType.toString());
			setName((tree->hasProperty(Attributes::objectType)) ? getName() + " : " + propertyAsString : getName());
			//if we are not allowed to transform this component, some properties groups will be hidden
			if (tree->hasProperty(Attributes::allowTransform))
				allowTransform = tree->getProperty(Attributes::allowTransform);

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
						} else if (attrib->type == AttributeType::boolean) {
							comp = new BooleanPropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display, "Enable");
						} else if (attrib->type == AttributeType::textarea) {
							comp = new TextPropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display, 1048576, true);
						} else if (attrib->type == AttributeType::file) {
							comp = new FilePropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display);
						} else if (attrib->type == AttributeType::choice) {
							Choices choices = Constructor::getInstance()->getChoicesOf(attrib->name);
							comp = new ChoicePropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display, choices.display, choices.values);
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
						} else if (attrib->group.equalsIgnoreCase("Appearance")) {
							appearanceGroup.add(comp);
						}
					}
				}
			}
		}

		if (generalGroup.size() > 0) addSection("General", generalGroup);
		if (boundsGroup.size() > 0 && allowTransform) addSection("Bounds", boundsGroup);
		if (appearanceGroup.size() > 0) addSection("Appearance", appearanceGroup);
		if (coloursGroup.size() > 0) addSection("Colours", coloursGroup);

		refreshAll();
	}

private:
	Array<PropertyComponent*> boundsGroup;
	Array<PropertyComponent*> generalGroup;
	Array<PropertyComponent*> coloursGroup;
	Array<PropertyComponent*> appearanceGroup;
	
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JUCED_PropertyGroup)
};
