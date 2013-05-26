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

PlaceableComponent::~PlaceableComponent()
{
	Constructor::log("PC003 - ~PlaceableComponent() call");

	if (_dynamicObject != nullptr)
		(dynamic_cast<Component *> (_dynamicObject.get()))->removeMouseListener(Constructor::getInstance()->getDesigner());

	Constructor::log("PC103 - Delete _componentTree");
	//_componentTree->removeAllProperties(0);
	if (_componentTree != nullptr)
		delete _componentTree;
	/*
	Constructor::log("PC103 - Delete _dynamicObject, reference count: " + String(_dynamicObject->getReferenceCount()));
	while (_dynamicObject != nullptr && _dynamicObject->getReferenceCount()) {
		if (_dynamicObject != nullptr) Constructor::log("PC103 - _dynamicObject != nullptr");
		Constructor::log("PC103 - Reference count: " + String(_dynamicObject->getReferenceCount()));
		_dynamicObject->decReferenceCount();
		Constructor::log("PC103 - [2] _dynamicObject != nullptr: " + String(_dynamicObject != nullptr));
	}
	Constructor::log("PC103 - Delete _dynamicObject pointer");
	_dynamicObject = nullptr;*/
	Constructor::log("PC103 - Delete _dynamicObject pointer");
	if (_dynamicObject != nullptr) {
		DynamicObject *temp = _dynamicObject.release();
		temp = nullptr;
		delete temp;
	}
	
	Constructor::log("PC103 - Done");
}

bool PlaceableComponent::perform ()
{
	Constructor::log("PC001 - Perform init (" + _selectedToolName + "), bounds: " + _bounds.toString());
	bool isBeingCreated = false;
	Constructor::log("PC101 - Find associated BigTree of the parent component");
	//If user draw inside a component, let's find it's associated BigTree of the parent component
	BigTree parentTree;
	BigTree *bigTree = Constructor::getInstance()->getBigTreeRoot();
	if (_parentComponentID.isNotEmpty() && bigTree != nullptr) {
		BigTree bTree(bigTree->getChildWithProperty(Attributes::ID, _parentComponentID, true));
		if (bTree.isValid()) parentTree = bTree;
	}

	//If user is placing the component as a root component and there was already one don't create the component
	if (!parentTree.isValid() && Constructor::getInstance()->getBigTreeRoot() != nullptr) {
		Constructor::log("PC301 - BigTree root was already specified");
		return false;
	}

	//If component does not exist yet, create an instance of it
	if (_dynamicObject == nullptr) {
		Constructor::log("PC101 - Component does not exist yet, creating an instance of it");
		isBeingCreated = true;
		if ((_dynamicObject = createObjectFromToolName(&_selectedToolName)) == nullptr) {
			//selectedToolName does not match any object type
			return false;
		}
	}
	
	Constructor::log("PC101 - Get parent component if parent BigTree is valid, editor component otherwise");
	//get parent component if parent BigTree is valid, editor component otherwise
	Component *parentComponent;
	if (parentTree.isValid()) {
		parentComponent = dynamic_cast<Component *> (parentTree.getProperty(Attributes::object).getDynamicObject());
	} else {
		parentComponent = Constructor::getInstance()->getDesigner();
	}
	
	Constructor::log("PC101 - Place component inside parent component and add its mouse listener");
	//Place component inside parent component and add its mouse listener
	parentComponent->addAndMakeVisible(dynamic_cast<Component *> (_dynamicObject.get()));
	(dynamic_cast<Component *> (_dynamicObject.get()))->addMouseListener(Constructor::getInstance()->getDesigner(), false);
	/*if (isBeingCreated) {
		Constructor::log("PC101 - Set component bounds");
		(dynamic_cast<Component *> (_dynamicObject))->setBounds(_bounds);
	}*/

	Constructor::log("PC101 - Update component's ID if specified");
	//update component's ID if specified
	if (_componentID.isNotEmpty()) {
		(dynamic_cast<Component *> (_dynamicObject.get()))->setComponentID(_componentID);
		_dynamicObject->setProperty(Attributes::ID, _componentID);
	} else _componentID = _dynamicObject->getProperty(Attributes::ID);

	Constructor::log("PC101 - Get component's BigTree or create a new one if it is invalid");
	//get component's BigTree or create a new one if it is invalid
	BigTree *objTree = new BigTree();
	if (!_componentTree->isValid()) {
		//current component's BigTree is invalid, create a new one
		Constructor::log("PC101 - current component's BigTree is invalid, create a new one");
		delete _componentTree;
		Constructor::log("PC101 - deleted, creating BigTree of object type: " + _dynamicObject->getProperty(Attributes::objectType).toString());
		//wait(250);
		objTree = new BigTree(_dynamicObject, _dynamicObject->getProperty(Attributes::objectType));
		Constructor::log("PC101 - created, valid: " + String(objTree->isValid()) + " @" + String((int)&_componentTree));
		//DBG((static_cast<void *> (&_componentTree)));
		//wait(1000);
		*_componentTree = BigTree(*objTree);
		Constructor::log("PC101 - copied");
	} else {
		Constructor::log("PC101 - else!! wtf");
		//get current component's BigTree
		*objTree = BigTree(*_componentTree);
		//objTree->setDynamicObject(_dynamicObject);
		jassert  (objTree->isValid());
	}
	Constructor::log("PC101 - done getting component's bigtree");
	
	//Add component's BigTree as a child of parent's BigTree
	if (parentTree.isValid()) {
		Constructor::log("PC101 - Add component's BigTree as a child of parent's BigTree");
		parentTree.addChild(*objTree, -1, 0);
	} else {
		//There was no parent BigTree so we assume this is going to be the main component container
		Constructor::log("PC101 - Set BigTree root as this component's BigTree");
		objTree->setProperty(Attributes::declareExtended, true, 0);
		Constructor::getInstance()->setBigTreeRoot(objTree);
	}
	
	//Set component bounds.
	if (isBeingCreated) {
		Constructor::log("PC101 - Set component bounds");
		objTree->setProperty(Attributes::x, _bounds.getX(), 0);
		objTree->setProperty(Attributes::y, _bounds.getY(), 0);
		objTree->setProperty(Attributes::width, _bounds.getWidth(), 0);
		objTree->setProperty(Attributes::height, _bounds.getHeight(), 0);
	}
	
	//set common value properties
	if (!objTree->hasProperty(Attributes::lookAndFeel))
		objTree->setProperty(Attributes::lookAndFeel, String("Inherit"), 0);
	if (!objTree->hasProperty(Attributes::castMouseEvents))
		objTree->setProperty(Attributes::castMouseEvents, false, 0);

	//if parent component is a component owner (must own its child), specify it
	if  (parentTree.isValid() && parentTree.hasProperty(Attributes::contentOwner)) {
		bool contentOwner = parentTree.getProperty(Attributes::contentOwner);
		if (contentOwner) {
			ResizableWindow *parentWindow = dynamic_cast<ResizableWindow *> (parentTree.getProperty(Attributes::object).getDynamicObject());
			parentWindow->setContentOwned(dynamic_cast<Component *> (_dynamicObject.get()), false);
		}
	} else if  (parentTree.isValid() && parentTree.hasProperty(Attributes::contentViewed)) {
		bool contentViewed = parentTree.getProperty(Attributes::contentViewed);
		if (contentViewed) {
			Viewport *parentViewport = dynamic_cast<Viewport *> (parentTree.getProperty(Attributes::object).getDynamicObject());
			parentViewport->setViewedComponent(dynamic_cast<Component *> (_dynamicObject.get()), false);
		}
	}
	
	Constructor::log("PC101 - Perform done");
	return true;
}

bool PlaceableComponent::undo ()
{
	Constructor::log("PC002 - Undo init");

	//Find it's associated BigTree of the parent component
	Constructor::log("PC102 - Get parentTree");
	BigTree parentTree;
	BigTree *bigTree = Constructor::getInstance()->getBigTreeRoot();
	if (_parentComponentID.isNotEmpty() && bigTree != nullptr) {
		BigTree bTree(bigTree->getChildWithProperty(Attributes::ID, _parentComponentID, true));
		if (bTree.isValid()) parentTree = bTree;
	}

	//get parent component if parent BigTree is valid, editor component otherwise
	Constructor::log("PC102 - Get parentComponent");
	Component *parentComponent;
	if (parentTree.isValid()) {
		parentComponent = dynamic_cast<Component *> (parentTree.getProperty(Attributes::object).getDynamicObject());
	} else {
		parentComponent = Constructor::getInstance()->getDesigner();
	}

	//remove component from it's parent and remove mouse listener
	Constructor::log("PC102 - Remove component from parent and remove it's mouse listener");
	parentComponent->removeChildComponent(dynamic_cast<Component *> (_dynamicObject.get()));
	dynamic_cast<Component *> (_dynamicObject.get())->removeMouseListener(Constructor::getInstance()->getDesigner());

	if (parentTree.isValid()) {
		//remove this component's BigTree from it's parent
		Constructor::log("PC102 - Remove this component's BigTree from it's parent");
		BigTree objectTree(parentTree.getChildWithProperty(Attributes::ID, _componentID, true));
		parentTree.removeChild(objectTree, 0);//(*_componentTree, 0);//(objectTree, 0);
	} else if (bigTree->getProperty(Attributes::ID).toString() == _componentID){
		//If component's BigTree was BigTree root, set it to null
		Constructor::log("PC102 - Set BigTree to nullptr");
		Constructor::getInstance()->setBigTreeRoot(nullptr);
	}

	Constructor::log("PC102 - Undo done");
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
	} else if (selectedToolName->equalsIgnoreCase("juced_Slider")) {
		juced_Slider *object = new juced_Slider();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_ImageButton")) {
		juced_ImageButton *object = new juced_ImageButton();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_ComboBox")) {
		juced_ComboBox *object = new juced_ComboBox();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_ListBox")) {
		juced_ListBox *object = new juced_ListBox();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_ProgressBar")) {
		juced_ProgressBar *object = new juced_ProgressBar();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_BubbleMessageComponent")) {
		juced_BubbleMessageComponent *object = new juced_BubbleMessageComponent();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_DirectShowComponent")) {
		juced_DirectShowComponent *object = new juced_DirectShowComponent();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_Component")) {
		juced_Component *object = new juced_Component();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_Viewport")) {
		juced_Viewport *object = new juced_Viewport();
		return (DynamicObject *)object;
	} else if (selectedToolName->equalsIgnoreCase("juced_ImageComponent")) {
		juced_ImageComponent *object = new juced_ImageComponent();
		return (DynamicObject *)object;
	}
	return nullptr;
}

Component* PlaceableComponent::getComponent()
{
	if (_dynamicObject == nullptr) return nullptr;
	return dynamic_cast<Component *> (_dynamicObject.get());
}