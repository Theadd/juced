/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef __MAINCOMPONENT_H_865F8056__
#define __MAINCOMPONENT_H_865F8056__

#include "../JuceLibraryCode/JuceHeader.h"
#include "JUCE_Designer.h"
//#include "Interface/Toolbox.cpp"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   :	public Component, ComponentListener,
								public MenuBarModel,
								public ApplicationCommandTarget
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&);
    void resized();
	void componentMovedOrResized (Component &component, bool wasMoved, bool wasResized);

	StringArray getMenuBarNames();
	PopupMenu getMenuForIndex (int menuIndex, const String& /*menuName*/);
	void menuItemSelected (int menuItemID, int /*topLevelMenuIndex*/);
	ApplicationCommandTarget* getNextCommandTarget();
	void getAllCommands (Array <CommandID>& commands);
	void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result);
	bool perform (const InvocationInfo& info);

private:
    //==============================================================================

	ScopedPointer<JUCE_Designer> juced;
	Viewport *propertyView;
	ScopedPointer<ResizableEdgeComponent> resizableBorder;
	ScopedPointer<ComponentBoundsConstrainer> constrainer;
	ImageComponent logo;

	enum CommandIDs
    {
        newProject              = 0x2000,
		quickSave				= 0x2001,
		quickLoad				= 0x2002,
		openProject				= 0x2003
    };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // __MAINCOMPONENT_H_865F8056__
