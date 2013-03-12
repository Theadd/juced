/*
  ==============================================================================

    BigTree.cpp
    Created: 11 Mar 2013 8:38:49am
    Author:  admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "BaseModules.h"
#include "../Modules/juced_Label.h"




class BigTree : public ValueTree,
				public ValueTree::Listener
{
public:
    //==============================================================================
	BigTree() : ValueTree("COMPONENT")
	{

	}

	BigTree(ValueTree &other) : ValueTree(other)
	{

	}

	BigTree(DynamicObject *object, var _type) : ValueTree(_type.toString()) {
		getDynamicObjectProperties(object);
		addListener(this);
	}

	BigTree(DynamicObject *object) : ValueTree("unknown")
	{
		getDynamicObjectProperties(object);
		addListener(this);
	}

	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
	{
		//Deal with changes on this ValueTree only, not their childs.
		if (treeWhosePropertyHasChanged == *this) {

			jassert (this->hasProperty(Ids::objectType));	//Object requires: setProperty(Ids::objectType, "object named type")

			if (this->getProperty(Ids::objectType) == "window") {
				juced_BaseWindow *obj = (juced_BaseWindow *)this->getProperty(Ids::object).getDynamicObject();
				if (property == Ids::height) {
					int height = treeWhosePropertyHasChanged.getProperty(property);
					obj->setSize(obj->getWidth(), height);
				} else if (property == Ids::name) {
					obj->setName(treeWhosePropertyHasChanged.getProperty(property).toString());
				}
			} else if (this->getProperty(Ids::objectType) == "label") {
				juced_Label *obj = (juced_Label *)this->getProperty(Ids::object).getDynamicObject();
				if (property == Ids::text) {
					obj->setText(treeWhosePropertyHasChanged.getProperty(property).toString(), false);
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
		printableTree->recursive_removeProperty(Ids::object, 0);
		ValueTree *vTree = (ValueTree *) printableTree;
		return vTree->createXml();
	}

private:

	void getDynamicObjectProperties(DynamicObject *object) {
		setProperty(Ids::object, var(object), 0);

		NamedValueSet values = object->getProperties();
		for (int i = values.size(); --i >= 0;) {
			setProperty(values.getName(i), values.getValueAt(i), 0);
		}
		
	}
};


