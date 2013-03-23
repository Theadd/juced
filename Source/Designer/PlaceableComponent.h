/*
  ==============================================================================

    PlaceableComponent.h
    Created: 22 Mar 2013 10:44:54pm
    Author:  admin

  ==============================================================================
*/

#ifndef __PLACEABLECOMPONENT_H_96136B71__
#define __PLACEABLECOMPONENT_H_96136B71__

#include "Globals.h"
#include "BigTree.h"
#include "Constructor.h"

#include "../Modules/juced_Label.h"
#include "../Modules/juced_TextButton.h"
#include "../Modules/juced_Window.h"
#include "../Modules/juced_MainComponent.h"

class BigTree;

class PlaceableComponent : public UndoableAction
{
public:
	
	PlaceableComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds, String componentID = String());

	bool perform ();

	bool undo ();

	Component* getComponent();

private:
	String _selectedToolName;
	String _parentComponentID;
	Rectangle<int> _bounds;
	DynamicObject* _dynamicObject;
	String _componentID;

	friend class BigTree;
	BigTree* _componentTree;

	

	DynamicObject* createObjectFromToolName (String *selectedToolName);

};


#endif  // __PLACEABLECOMPONENT_H_96136B71__
