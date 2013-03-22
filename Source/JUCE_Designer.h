
#ifndef __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__
#define __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__

#include "Designer/Globals.h"
#include "Modules/juced_Window.h"
#include "Modules/juced_MainComponent.h"
#include "Modules/juced_Label.h"
#include "Modules/juced_TextButton.h"
#include "Designer/SelectionArea.h"
#include "Designer/Toolbox.cpp"
#include "Designer/PropertyGroup.cpp"
#include "Designer/PropertyView.cpp"
#include "Designer/BigTree.h"
#include "Designer/Constructor.h"

class JUCE_Designer  : public Component
{
public:

    JUCE_Designer ();
    ~JUCE_Designer();

	Component* createToolbox (int itemsPerRow, int itemSize, int itemPadding);
	void addToolboxItem (Component* toolbox, const String& name, const String& toolTip, const char* image, int imageSize);
	Viewport* getPropertyView ();
	String* getSelectedToolName ();
	void deselectTool ();
    void addWindow (Component *parent, int x, int y, int width, int height);
	void writeXmlToFile (String _filename);
	void selectComponent (Component *componentToSelect);

    void paint (Graphics& g);
    void resized();
    void lookAndFeelChanged();
    void childrenChanged();
	void mouseMove (const MouseEvent& event);
    void mouseDown (const MouseEvent& event);
    void mouseDrag (const MouseEvent& event);
    void mouseUp (const MouseEvent& event);
    void mouseDoubleClick (const MouseEvent& event);
    bool keyPressed (const KeyPress& key);
    void focusOfChildComponentChanged (FocusChangeType cause);
	void focusGained (FocusChangeType cause);
	void childBoundsChanged (Component * child);

	class Grid : public Component
	{
	public:
		Grid ();
		void paint (Graphics& g);
	};

	Grid grid;

private:
	Label mousePositionLabel;
	//OwnedArray<juced_Window> juced_Windows;
	//OwnedArray<juced_Label> juced_Labels;
	OwnedArray<Toolbox> toolboxes;
	ScopedPointer<SelectionArea> selectionArea;
	
	Component *selectedComponent;
	ValueTree *selectedComponentTree;
	Point<int> selectedComponentPositionDifference;
	Point<int> componentPositionOnDragStart;
	ScopedPointer<BigTree> bigTree;
	PropertyGroup *activePropertyGroup;
	//ScopedPointer<ComponentBuilder> builder;
	
	ScopedPointer<PropertyView> propertyView;

	DynamicObject* createObjectFromToolName (String *selectedToolName);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JUCE_Designer)
};

#endif   // __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__
