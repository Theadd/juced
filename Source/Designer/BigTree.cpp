/*
  ==============================================================================

    BigTree.cpp
    Created: 11 Mar 2013 8:38:49am
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "../Modules/juced_Label.h"
#include "../Modules/juced_TextButton.h"
#include "../Modules/juced_Window.h"
#include "../Modules/juced_MainComponent.h"

class BigTree : public ValueTree,
				public ValueTree::Listener
{
public:
    //==============================================================================
	BigTree() : ValueTree(Modules::Unknown.toString())
	{

	}

	BigTree(ValueTree &other) : ValueTree(other)
	{

	}

	BigTree(DynamicObject *object, var _type) : ValueTree(_type.toString()) {
		getDynamicObjectProperties(object);
		addListener(this);
	}

	BigTree(DynamicObject *object) : ValueTree(Modules::Unknown.toString())
	{
		getDynamicObjectProperties(object);
		addListener(this);
	}

	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
	{
		//Deal with changes on this ValueTree only, not their childs.
		if (treeWhosePropertyHasChanged == *this) {

			jassert (this->hasProperty(Attributes::objectType));	//Object requires: setProperty(Ids::objectType, "object named type")

			//since Windows don't inherit from Component class we deal with it separately
			if (this->getProperty(Attributes::objectType) == Modules::Window) {
				juced_Window *obj = (juced_Window *)this->getProperty(Attributes::object).getDynamicObject();
				if (property == Attributes::height) {
					int height = treeWhosePropertyHasChanged.getProperty(property);
					obj->setSize(obj->getWidth(), height);
				} else if (property == Attributes::name) {
					obj->setName(treeWhosePropertyHasChanged.getProperty(property).toString());
				}
			} else {
				//deal with other type of components since its not a window
				bool propertyChanged = true;
				if (this->getProperty(Attributes::objectType) == Modules::Label) {
					//deal with Label specific properties
					juced_Label *cObject = (juced_Label *)this->getProperty(Attributes::object).getDynamicObject();
					if (property == Attributes::text) {
						cObject->setText(treeWhosePropertyHasChanged.getProperty(property).toString(), false);
					} else if (property == Attributes::backgroundColour) {
						Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
						cObject->setColour(Label::backgroundColourId, newColour);
					} else if (property == Attributes::textColour) {
						Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
						cObject->setColour(Label::textColourId, newColour);
					} else {
						propertyChanged = false;
					}
				} else if (this->getProperty(Attributes::objectType) == Modules::TextButton) {
					//deal with TextButton specific properties
					juced_TextButton *cObject = (juced_TextButton *)this->getProperty(Attributes::object).getDynamicObject();
					if (property == Attributes::buttonText) {
						cObject->setButtonText(treeWhosePropertyHasChanged.getProperty(property).toString());
					} else if (property == Attributes::buttonColour) {
						Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
						cObject->setColour(TextButton::ColourIds::buttonColourId, newColour);
					} else if (property == Attributes::buttonOnColour) {
						Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
						cObject->setColour(TextButton::ColourIds::buttonOnColourId, newColour);
					} else {
						propertyChanged = false;
					}
				}
				if (!propertyChanged) {
					//deal with common component properties
					Component *obj = dynamic_cast<Component *> (this->getProperty(Attributes::object).getDynamicObject());
					if (property == Attributes::x) {
						int value = treeWhosePropertyHasChanged.getProperty(property);
						obj->setBounds(value, obj->getY(), obj->getWidth(), obj->getHeight());
					} else if (property == Attributes::y) {
						int value = treeWhosePropertyHasChanged.getProperty(property);
						obj->setBounds(obj->getX(), value, obj->getWidth(), obj->getHeight());
					} else if (property == Attributes::width) {
						int value = treeWhosePropertyHasChanged.getProperty(property);
						obj->setBounds(obj->getX(), obj->getY(), value, obj->getHeight());
					} else if (property == Attributes::height) {
						int value = treeWhosePropertyHasChanged.getProperty(property);
						obj->setBounds(obj->getX(), obj->getY(), obj->getWidth(), value);
					} else if (property == Attributes::name) {
						obj->setName(treeWhosePropertyHasChanged.getProperty(property).toString());
					}
				}
			}
		}
	}

    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) {}

    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved) {}


	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved) {}

	void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) {}

	void valueTreeRedirected (ValueTree& treeWhichHasBeenChanged) {}

	BigTree getChild(int index) const
	{
		return BigTree(ValueTree::getChild(index));
	}

	void recursive_removeProperty(Identifier name, UndoManager *undoManager) {

		removeProperty(name, undoManager);
		for (int i = getNumChildren(); --i >= 0;) {
			getChild(i).recursive_removeProperty(name, undoManager);
		}
	}

	XmlElement* createXml()
	{

		BigTree *printableTree = new BigTree(createCopy());
		printableTree->recursive_removeProperty(Attributes::object, 0);
		ValueTree *vTree = (ValueTree *) printableTree;
		return vTree->createXml();
	}

private:

	void getDynamicObjectProperties(DynamicObject *object) {
		setProperty(Attributes::object, var(object), 0);

		NamedValueSet values = object->getProperties();
		for (int i = values.size(); --i >= 0;) {
			setProperty(values.getName(i), values.getValueAt(i), 0);
		}
		
	}
};


