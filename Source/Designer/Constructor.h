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
//struct Enumeration;
/**
    Object required to build components and show its properties.

    Only one instance of this object is allowed.

    To use, simply get an instance of this class using the getInstance() static method.
	Example: Constructor *constructor = Constructor::getInstance();
*/
class Constructor {
public:
	Array<Attribute*> _attributes;

	/** This function is called to create an instance of the class.

		Calling the constructor publicly is not allowed. The constructor
		is private and is only called by this Instance function.
	*/
	static Constructor* getInstance();

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

	static void displayMsg(String msg);

	void setDesigner(Component *juce_designer);
	Component* getDesigner();

	void setBigTreeRoot(BigTree *bigTreeRoot);
	BigTree* getBigTreeRoot();

	Component* createComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds);


private:
	ScopedPointer<UndoManager> undoManager;
	ScopedPointer<TextEditor> _msgDisplay;

	friend class SelectionArea;
	friend class JUCE_Designer;
	friend class BigTree;
	ScopedPointer<SelectionArea> _selectionBox;
	
	struct _Enumerations {
		Identifier name;
		Array< Enumeration* >* enumerations;
	};
	Array< _Enumerations > _enumerations;

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
	static Constructor* m_pInstance;
};



#endif  // __CONSTRUCTOR_H_E78AE279__
