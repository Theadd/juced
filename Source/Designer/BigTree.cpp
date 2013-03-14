/*
  ==============================================================================

    BigTree.cpp
    Created: 11 Mar 2013 8:38:49am
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "../Modules/juced_Label.h"
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

			if (this->getProperty(Attributes::objectType) == Modules::Window) {
				juced_Window *obj = (juced_Window *)this->getProperty(Attributes::object).getDynamicObject();
				if (property == Attributes::height) {
					int height = treeWhosePropertyHasChanged.getProperty(property);
					obj->setSize(obj->getWidth(), height);
				} else if (property == Attributes::name) {
					obj->setName(treeWhosePropertyHasChanged.getProperty(property).toString());
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::Label) {
				juced_Label *obj = (juced_Label *)this->getProperty(Attributes::object).getDynamicObject();
				if (property == Attributes::text) {
					obj->setText(treeWhosePropertyHasChanged.getProperty(property).toString(), false);
				} else if (property == Attributes::backgroundColour) {
					Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
					obj->setColour(Label::backgroundColourId, newColour);
				} else if (property == Attributes::textColour) {
					Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
					obj->setColour(Label::textColourId, newColour);
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


