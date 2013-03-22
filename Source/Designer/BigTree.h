/*
  ==============================================================================

    BigTree.h
    Created: 21 Mar 2013 2:15:39pm
    Author:  admin

  ==============================================================================
*/

#ifndef __BIGTREE_H_DFF318BD__
#define __BIGTREE_H_DFF318BD__


#include "Globals.h"
#include "Constructor.h"
#include "SelectionArea.h"
#include "../Modules/juced_Label.h"
#include "../Modules/juced_TextButton.h"
#include "../Modules/juced_Window.h"
#include "../Modules/juced_MainComponent.h"

/** This class holds all object hierarchy and property modification. */
class BigTree : public ValueTree,
				public ValueTree::Listener
{
public:
    /** Creates an invalid BigTree.
	@see ValueTree
	*/
	BigTree();

	/** Creates a reference to another BigTree. */
	BigTree(const ValueTree &other);

	/** Creates a named type BigTree that holds a DynamicObject. */
	BigTree(DynamicObject *object, var _type);

	/** Creates an unnamed BigTree that holds a DynamicObject. */
	BigTree(DynamicObject *object);

	/** Deals with property changes on a determinated object. */
	void valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property);

    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded);

    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved);

	void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved);

	void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged);

	void valueTreeRedirected (ValueTree& treeWhichHasBeenChanged);
	
	/** Looks for any BigTree within it's childs, recursive or not, that has the named property with specified value.
	It will look in this tree first for the given property, then, it's children and if recursive is set, children's children and so on.
	@see Attributes
	@see Constructor::getAttributeOf
	@see Attribute
	@param propertyName Identifier matching a property name.
	@param propertyValue var containing the value to look for.
	@param recursive bool set to look into children's children and so on.
	*/
	BigTree& getChildWithProperty(const Identifier &propertyName, const var &propertyValue, bool recursive);

	/** Returns a BigTree that references a child BigTree on the given index. */
	BigTree getChild(int index) const;

	/** Recursive function to remove a named property from this BigTree and all it's children. */
	void recursive_removeProperty(Identifier name, UndoManager *undoManager);

	/** Returns an XmlElement containing the representation of the current BigTree and all it's children. */
	XmlElement* createXml();

private:

	void getDynamicObjectProperties(DynamicObject *object);
};



#endif  // __BIGTREE_H_DFF318BD__
