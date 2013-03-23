/*
  ==============================================================================

    PlaceableComponent.cpp
    Created: 22 Mar 2013 10:44:54pm
    Author:  admin

  ==============================================================================
*/

#include "PlaceableComponent.h"

PlaceableComponent::PlaceableComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds, String componentID) : _selectedToolName(selectedToolName), _parentComponentID(parentComponentID), _bounds(bounds), _componentID(componentID)
{
	_componentTree = new BigTree();
	_dynamicObject = nullptr;
}

bool PlaceableComponent::perform ()
{
	Constructor::displayMsg("1");
	//If user draw inside a component, let's find it's associated BigTree of the parent component
	BigTree parentTree;
	BigTree *bigTree = Constructor::getInstance()->getBigTreeRoot();
	if (_parentComponentID.isNotEmpty() && bigTree != nullptr) {
		BigTree bTree(bigTree->getChildWithProperty(Attributes::ID, _parentComponentID, true));
		if (bTree.isValid()) parentTree = bTree;
	}

	Constructor::displayMsg("2");
	//If component does not exist yet, create an instance of it
	if (_dynamicObject == nullptr) {
		Constructor::displayMsg("2.1");
		if ((_dynamicObject = createObjectFromToolName(&_selectedToolName)) == nullptr) {
			//selectedToolName does not match any object type
			return false;
		}
	}
	
	Constructor::displayMsg("3");
	//get parent component if parent BigTree is valid, editor component otherwise
	Component *parentComponent;
	if (parentTree.isValid()) {
		parentComponent = dynamic_cast<Component *> (parentTree.getProperty(Attributes::object).getDynamicObject());
	} else {
		parentComponent = Constructor::getInstance()->getDesigner();
	}
	
	Constructor::displayMsg("4");
	//Place component inside parent component and add its mouse listener
	parentComponent->addAndMakeVisible(dynamic_cast<Component *> (_dynamicObject));
	(dynamic_cast<Component *> (_dynamicObject))->addMouseListener(Constructor::getInstance()->getDesigner(), false);

	Constructor::displayMsg("5");
	//update component's ID if specified
	if (_componentID.isNotEmpty()) {
		_dynamicObject->setProperty(Attributes::ID, _componentID);
	} else _componentID = _dynamicObject->getProperty(Attributes::ID);

	Constructor::displayMsg("6");
	//get component's BigTree or create a new one if it is invalid
	BigTree *objTree = new BigTree();
	if (!_componentTree->isValid()) {
		//current component's BigTree is invalid, create a new one
		objTree = new BigTree(_dynamicObject, _dynamicObject->getProperty(Attributes::objectType));
		*_componentTree = BigTree(*objTree);
	} else {
		//get current component's BigTree
		*objTree = BigTree(*_componentTree);
		//objTree->setDynamicObject(_dynamicObject);
		jassert  (objTree->isValid());
	}
	
	Constructor::displayMsg("7");
	//Add component's BigTree as a child of parent's BigTree
	if (parentTree.isValid()) {
		parentTree.addChild(*objTree, -1, 0);
	} else {
		//There was no parent BigTree so we assume this is going to be the main component container
		jassert (Constructor::getInstance()->getBigTreeRoot() == nullptr);	//BigTree root was already specified
		Constructor::getInstance()->setBigTreeRoot(objTree);
	}
	
	Constructor::displayMsg("8");
	//Set component bounds.
	objTree->setProperty(Attributes::x, _bounds.getX(), 0);
	objTree->setProperty(Attributes::y, _bounds.getY(), 0);
	objTree->setProperty(Attributes::width, _bounds.getWidth(), 0);
	objTree->setProperty(Attributes::height, _bounds.getHeight(), 0);

	//If component's BigTree already existed no bounds will be set by setProperty since they already had that value
	dynamic_cast<Component *> (_dynamicObject)->setBounds(_bounds);

	return true;
}

bool PlaceableComponent::undo ()
{
	Constructor::getInstance()->getSelectionBox()->setVisible(false);

	//Find it's associated BigTree of the parent component
	BigTree parentTree;
	BigTree *bigTree = Constructor::getInstance()->getBigTreeRoot();
	if (_parentComponentID.isNotEmpty() && bigTree != nullptr) {
		BigTree bTree(bigTree->getChildWithProperty(Attributes::ID, _parentComponentID, true));
		if (bTree.isValid()) parentTree = bTree;
	}

	//get parent component if parent BigTree is valid, editor component otherwise
	Component *parentComponent;
	if (parentTree.isValid()) {
		parentComponent = dynamic_cast<Component *> (parentTree.getProperty(Attributes::object).getDynamicObject());
	} else {
		parentComponent = Constructor::getInstance()->getDesigner();
	}

	//remove component from it's parent and remove mouse listener
	parentComponent->removeChildComponent(dynamic_cast<Component *> (_dynamicObject));
	dynamic_cast<Component *> (_dynamicObject)->removeMouseListener(Constructor::getInstance()->getDesigner());

	if (parentTree.isValid()) {
		//remove this component's BigTree from it's parent
		BigTree objectTree(parentTree.getChildWithProperty(Attributes::ID, _componentID, true));
		parentTree.removeChild(objectTree, 0);//(*_componentTree, 0);//(objectTree, 0);
	}

	return true;
}


DynamicObject* PlaceableComponent::createObjectFromToolName (String *selectedToolName)
{
	if (selectedToolName->equalsIgnoreCase("juced_Label")) {
		juced_Label *object = new juced_Label();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_TextButton")) {
		juced_TextButton *object = new juced_TextButton();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_Window")) {
		juced_Window *object = new juced_Window();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_MainComponent")) {
		juced_MainComponent *object = new juced_MainComponent();
		return (DynamicObject *)object;
	}
	return nullptr;
}

Component* PlaceableComponent::getComponent()
{
	if (_dynamicObject == nullptr) return nullptr;
	return dynamic_cast<Component *> (_dynamicObject);
}