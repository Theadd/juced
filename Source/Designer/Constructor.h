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
#include "Importer.h"
#include "CodeGenerator.h"


#include "../Modules/juced_Label.h"
#include "../Modules/juced_TextButton.h"
#include "../Modules/juced_Window.h"
#include "../Modules/juced_MainComponent.h"

#include "../Styles/LookAndFeelCustom.h"

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

	String projectName;
	String projectPath;
	int projectType;
	int resourceType;
	String selectedTemplate;
	String rootVarName;

        static Constructor* m_pInstance;

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

	Choices getChoicesOf(Identifier _name);

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

	String getTemplatesDir();

	Component* createComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds, String componentID = String::empty, bool addDependencies = true);

	LookAndFeel* getNamedLookAndFeel(String name);

	void setWorkingDirectory(String path);
	String getWorkingDirectory();

	void importFromXml(File xmlFile);

	void resetCurrentState();

	bool createNewProject();

	bool openProject();

	void quickSave();

	void updateRootVarName ();

	/** Copy a given file absolute path into project resources directory and returns copied filename with extension. **/
	String setResourceFile(String path);

	/** Returns an absolute path to a file located in project resources directory. **/
	String getResourceFilePath(String filename);

	ApplicationCommandManager* getCommandManager();

	ApplicationCommandManager commandManager;

private:
	ScopedPointer<UndoManager> undoManager;
	Component *_selectedComponent;
	
	String _workingDirectory;

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

	LookAndFeelCustom customLookAndFeel;

	Constructor(){};  // Private so that it can  not be called
	Constructor(Constructor const&){};             // copy constructor is private
	Constructor& operator=(Constructor const&){};  // assignment operator is private
	

	JUCE_LEAK_DETECTOR (Constructor)
};



#endif  // __CONSTRUCTOR_H_E78AE279__
