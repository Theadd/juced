
#ifndef __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__
#define __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Designer/BaseModules.h"
#include "Modules/juced_Window.cpp"
#include "Modules/juced_Label.h"
#include "Designer/SelectionArea.cpp"
#include "Designer/Toolbox.cpp"
#include "Designer/PropertiesComponent.cpp"
#include "Designer/BigTree.cpp"



class JUCE_Designer  : public Component
{
public:

    JUCE_Designer ();
    ~JUCE_Designer();

	Component* createToolbox (int itemsPerRow, int itemSize, int itemPadding);
	void addToolboxItem (Component* toolbox, const String& name, const String& toolTip, const char* image, int imageSize);
	String* getSelectedToolName ();
	void deselectTool ();
    void addWindow (Component *parent, int x, int y, int width, int height);

    void paint (Graphics& g);
    void resized();
    void lookAndFeelChanged();
    void childrenChanged();
    void mouseDown (const MouseEvent& event);
    void mouseDrag (const MouseEvent& event);
    void mouseUp (const MouseEvent& event);
    void mouseDoubleClick (const MouseEvent& event);
    bool keyPressed (const KeyPress& key);
    void focusOfChildComponentChanged (FocusChangeType cause);



private:
	//OwnedArray<juced_Window> juced_Windows;
	//OwnedArray<juced_Label> juced_Labels;
	OwnedArray<Toolbox> toolboxes;
	ScopedPointer<SelectionArea> selectionArea;
	ScopedPointer<Component> selectedComponent;
	ScopedPointer<BigTree> bigTree;
	ScopedPointer<ComponentBuilder> builder;
	
	ScopedPointer<PropertyPanelViewport> propertiesViewport;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JUCE_Designer)
};

#endif   // __JUCER_HEADER_JUCEDESIGNER_JUCEDESIGNER_BDA26567__
