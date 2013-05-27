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
#include "../Modules/juced_Slider.h"
#include "../Modules/juced_ImageButton.h"
#include "../Modules/juced_ComboBox.h"
#include "../Modules/juced_ListBox.h"
#include "../Modules/juced_ProgressBar.h"
#include "../Modules/juced_BubbleComponent.h"
#include "../Modules/juced_DirectShowComponent.h"
#include "../Modules/juced_Component.h"
#include "../Modules/juced_Viewport.h"
#include "../Modules/juced_ImageComponent.h"
#include "../Modules/juced_ToggleButton.h"

class BigTree;

/** This class represents the actions for create, undo and redo of components creation. 

	@see Constructor::createComponent
*/
class PlaceableComponent : public UndoableAction
{
public:
	/** Creates a PlaceableComponent object.
		
		@param selectedToolName String containing the name of the component class to represent.
		@param parentComponentID parent's component ID
		@param bounds Rectangle<int> containing the bounds that will occupy the new component.
		@param componentID Optional String that will set component's ID to this value when creating it.
	*/
	PlaceableComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds, String componentID = String::empty);

	~PlaceableComponent();

	/** Method called by the UndoManager to create the specified component (redo also). */
	bool perform ();

	/** Method called by the UndoManager to undo the creation of the represented component. */
	bool undo ();

	/** Returns a pointer to the component being represented by this object. */
	Component* getComponent();

private:
	String _selectedToolName;
	String _parentComponentID;
	Rectangle<int> _bounds;
	ScopedPointer<DynamicObject> _dynamicObject;
	String _componentID;

	friend class BigTree;
	BigTree* _componentTree;

	DynamicObject* createObjectFromToolName (String *selectedToolName);

	JUCE_LEAK_DETECTOR (PlaceableComponent)
};


#endif  // __PLACEABLECOMPONENT_H_96136B71__
