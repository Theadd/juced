/*
  ==============================================================================

    Constructor.h
    Created: 16 Mar 2013 4:58:15pm
    Author:  admin

  ==============================================================================
*/

#ifndef __CONSTRUCTOR_H_E78AE279__
#define __CONSTRUCTOR_H_E78AE279__

#include "Globals.h"
#include "SelectionArea.h"
#include "BigTree.h"
#include "PlaceableComponent.h"

#include "../Modules/juced_Label.h"
#include "../Modules/juced_TextButton.h"
#include "../Modules/juced_Window.h"
#include "../Modules/juced_MainComponent.h"

/** Struct to hold all parameters of a given attribute identifier.

	@see getAttributeOf
	@see Attributes
*/




class SelectionArea;
class BigTree;
class PlaceableComponent;
//struct Enumeration;
/**
    Object required to build components and show its properties.

    Only one instance of this object is allowed.

    To use, simply get an instance of this class using the getInstance() static method.
	Example: Constructor *constructor = Constructor::getInstance();
*/
class Constructor {
public:

	/** This function is called to create an instance of the class.

		Calling the constructor publicly is not allowed. The constructor
		is private and is only called by this Instance function.
	*/
	static Constructor* getInstance();

	static void destroy();

	~Constructor();

	/** Function called within JUCE_Designer constructor.
		
		Loads all parameters from a list of attribute types in a XML file.

		@param xmlFile File object that points to XML file in disc.
		@see getAttributeOf
	*/
	void loadAttributesFromXmlFile(const File &xmlFile);

	void loadEnumerationsFromXmlFile(const File &xmlFile);

	/** Returns a struct pointer of attribute parameters given it's Identifier.

		@param _name Attribute identifier.
		@see Attribute
		@see Attributes
	*/
	Attribute* getAttributeOf(Identifier _name);

	Array< Enumeration* >* getEnumerationsOf(Identifier _name);

	/** Returns a pointer to an UndoManager.

		@see UndoManager, BigTree, ValueTree
	*/
	UndoManager* getUndoManager();
	SelectionArea* getSelectionBox();

	void setDrawBoundsMod(int x, int y, int width, int height);
	int getDrawBoundsModX();
	int getDrawBoundsModY();
	int getDrawBoundsModWidth();
	int getDrawBoundsModHeight();

	void setGridSize(int newGridSize);
	int getGridSize();

	Component* getSelectedComponent();
	void setSelectedComponent(Component *selectedComponent);

	static void log(String msg);

	void setDesigner(Component *juce_designer);
	Component* getDesigner();

	void setBigTreeRoot(BigTree *bigTreeRoot);
	BigTree* getBigTreeRoot();

	Component* createComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds);


private:
	ScopedPointer<UndoManager> undoManager;
	Component *_selectedComponent;
	

	friend class SelectionArea;
	friend class JUCE_Designer;
	friend class BigTree;
	friend class PlaceableComponent;
	ScopedPointer<SelectionArea> _selectionBox;
	OwnedArray<PlaceableComponent> _placeableComponents;
	
	struct _Enumerations {
		Identifier name;
		Array< Enumeration* >* enumerations;
	};
	Array< _Enumerations > _enumerations;
	Array<Attribute*> _attributes;

	Component *_designer;
	BigTree* _bigTreeRoot;
	//OwnedArray<Action> _actions;
	int _gridSize;
	int _drawBoundsModX;
	int _drawBoundsModY;
	int _drawBoundsModWidth;
	int _drawBoundsModHeight;
	Constructor(){};  // Private so that it can  not be called
	Constructor(Constructor const&){};             // copy constructor is private
	Constructor& operator=(Constructor const&){};  // assignment operator is private
	static ScopedPointer<Constructor> m_pInstance;

	JUCE_LEAK_DETECTOR (Constructor)
};



#endif  // __CONSTRUCTOR_H_E78AE279__
