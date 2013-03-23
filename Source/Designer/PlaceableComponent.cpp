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
}

bool PlaceableComponent::perform ()
{
	//If user draw inside a component, let's find it's associated BigTree of the parent component
	BigTree parentTree;
	BigTree *bigTree = Constructor::getInstance()->getBigTreeRoot();
	if (_parentComponentID.isNotEmpty() && bigTree != nullptr) {
		BigTree bTree(bigTree->getChildWithProperty(Attributes::ID, _parentComponentID, true));
		if (bTree.isValid()) parentTree = bTree;
	}

	DynamicObject *dynamicObj;
	if ((dynamicObj = createObjectFromToolName(&_selectedToolName)) != nullptr) {

		Component *parentComponent;
		if (parentTree.isValid()) {
			parentComponent = dynamic_cast<Component *> (parentTree.getProperty(Attributes::object).getDynamicObject());
		} else {
			parentComponent = Constructor::getInstance()->getDesigner();
		}
		parentComponent->addAndMakeVisible(dynamic_cast<Component *> (dynamicObj));
		(dynamic_cast<Component *> (dynamicObj))->addMouseListener(Constructor::getInstance()->getDesigner(), false);

		if (_componentID.isNotEmpty()) {
			//set component's ID if specified
			//(dynamic_cast<Component *> (dynamicObj))->setComponentID(_componentID);
			//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "1");
			dynamicObj->setProperty(Attributes::ID, _componentID);
			//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "2");
		} else _componentID = dynamicObj->getProperty(Attributes::ID);

		
		//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "3");
		BigTree *objTree = new BigTree();
		if (!_componentTree->isValid()) {
			//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "3.1");
			objTree = new BigTree(dynamicObj, dynamicObj->getProperty(Attributes::objectType));
			//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "3.2");
			*_componentTree = BigTree(*objTree);
			//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "3.3");
		} else {
			//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "4.-1");
			*objTree = BigTree(*_componentTree);
			objTree->setDynamicObject(dynamicObj);
			jassert  (objTree->isValid());
		}
		//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "4");
		if (parentTree.isValid()) {
			parentTree.addChild(*objTree, -1, 0);
		} else {
			AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "parent tree  is not valid");
			Constructor::getInstance()->setBigTreeRoot(objTree);
		}

		objTree->setProperty(Attributes::x, _bounds.getX(), 0);
		objTree->setProperty(Attributes::y, _bounds.getY(), 0);
		objTree->setProperty(Attributes::width, _bounds.getWidth(), 0);
		objTree->setProperty(Attributes::height, _bounds.getHeight(), 0);

		_component = dynamic_cast<Component *> (dynamicObj);
		_component->setBounds(_bounds);

	} else {
		//selectedToolName does not match any object type
		return false;
	}

	return true;
}

bool PlaceableComponent::undo ()
{
	Constructor::getInstance()->getSelectionBox()->setVisible(false);

	BigTree parentTree;
	BigTree *bigTree = Constructor::getInstance()->getBigTreeRoot();
	if (_parentComponentID.isNotEmpty() && bigTree != nullptr) {
		BigTree bTree(bigTree->getChildWithProperty(Attributes::ID, _parentComponentID, true));
		if (bTree.isValid()) parentTree = bTree;
	}

	Component *parentComponent;
	if (parentTree.isValid()) {
		parentComponent = dynamic_cast<Component *> (parentTree.getProperty(Attributes::object).getDynamicObject());
	} else {
		parentComponent = Constructor::getInstance()->getDesigner();
	}
	//remove component from it's parent
	parentComponent->removeChildComponent(_component);
	_component->removeMouseListener(Constructor::getInstance()->getDesigner());

	if (parentTree.isValid()) {
		//remove this component's BigTree from it's parent
		BigTree objectTree(parentTree.getChildWithProperty(Attributes::ID, _componentID, true));
		parentTree.removeChild(objectTree, 0);//(*_componentTree, 0);//(objectTree, 0);
	}
	//finally, delete component
	//_component = nullptr;

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
	}
	return nullptr;
}

Component* PlaceableComponent::getComponent()
{
	return _component;
}