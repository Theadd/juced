/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "Designer\Constructor.h"
#include "MainComponent.h"


//==============================================================================
MainContentComponent::MainContentComponent()
{
	setSize (800, 600);
    juced = new JUCE_Designer();
	addAndMakeVisible(juced);
	Component* toolbox;
	toolbox = juced->createToolbox(1, 32, 5);
	juced->addToolboxItem(toolbox, "juced_Window", "Window", BinaryData::window_png, BinaryData::window_pngSize);
	juced->addToolboxItem(toolbox, "juced_Label", "Text label", BinaryData::label_png, BinaryData::label_pngSize);
	juced->addToolboxItem(toolbox, "juced_TextButton", "Text button", BinaryData::button_png, BinaryData::button_pngSize);
	juced->addToolboxItem(toolbox, "juced_Slider", "Slider", BinaryData::slider_png, BinaryData::slider_pngSize);
	juced->addToolboxItem(toolbox, "juced_ImageButton", "Image button", BinaryData::imagebutton_png, BinaryData::imagebutton_pngSize);
	//juced->addToolboxItem(toolbox, "juced_Textbox", "Textbox", BinaryData::textbox_png, BinaryData::textbox_pngSize);
	juced->addToolboxItem(toolbox, "juced_ComboBox", "ComboBox", BinaryData::combobox_png, BinaryData::combobox_pngSize);
	juced->addToolboxItem(toolbox, "juced_Listbox", "Listbox", BinaryData::listbox_png, BinaryData::listbox_pngSize);
	//juced->addToolboxItem(toolbox, "juced_TabPanel", "Tab panel", BinaryData::tabs_png, BinaryData::tabs_pngSize);
	juced->addToolboxItem(toolbox, "juced_ProgressBar", "Progress Bar", BinaryData::progressbar_png, BinaryData::progressbar_pngSize);
	juced->addToolboxItem(toolbox, "juced_BubbleComponent", "Bubble", BinaryData::bubble_png, BinaryData::bubble_pngSize);

	toolbox->setAlwaysOnTop(true);
	juced->addAndMakeVisible(toolbox, 11);
	juced->addComponentListener(this);

	constrainer = new ComponentBoundsConstrainer();
	constrainer->setMinimumOnscreenAmounts(0,0,0,200);	//TODO: not working
	resizableBorder = new ResizableEdgeComponent(juced, constrainer, ResizableEdgeComponent::rightEdge);
	juced->addAndMakeVisible(resizableBorder);

	propertyView = juced->getPropertyView();
	addAndMakeVisible(propertyView);
	propertyView->setBounds(100, 100, 250, 400);
	//propertyView->setOpaque(true);
	//int style = (ComponentPeer::windowHasTitleBar | ComponentPeer::windowIsResizable);
	//propertyView->addToDesktop((int)(ComponentPeer::windowHasTitleBar | ComponentPeer::windowIsResizable));
	propertyView->setVisible(false);
	juced->setVisible(false);
	resized();
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour((uint8) 245, (uint8) 245, (uint8) 245));
}

void MainContentComponent::resized()
{
    Rectangle<int> r (getLocalBounds());
	if (juced != nullptr) {
		juced->setBounds(0, 0, r.getWidth() - propertyView->getWidth(), r.getHeight());
		Rectangle<int> jr (juced->getLocalBounds());
		resizableBorder->setBounds(jr.getWidth() - 5, 0, 5, jr.getHeight());
		propertyView->setBounds(r.getWidth() - propertyView->getWidth(), 0, propertyView->getWidth(), r.getHeight());
	}
}

void MainContentComponent::componentMovedOrResized (Component &component, bool wasMoved, bool wasResized)
{
	if (isVisible() && &component == juced) {
		if (wasResized) {
			Rectangle<int> jr (juced->getLocalBounds());
			resizableBorder->setBounds(jr.getWidth() - 5, 0, 5, jr.getHeight());
			propertyView->setBounds(jr.getWidth(), 0, getWidth() - jr.getWidth(), jr.getHeight());
		}
	}
}

StringArray MainContentComponent::getMenuBarNames()
{
    const char* const names[] = { "File", nullptr };

    return StringArray (names);
}

PopupMenu MainContentComponent::getMenuForIndex (int menuIndex, const String& /*menuName*/)
{
    ApplicationCommandManager* commandManager = Constructor::getInstance()->getCommandManager();

    PopupMenu menu;

    if (menuIndex == 0)
    {
        menu.addCommandItem (commandManager, newProject);
		menu.addCommandItem (commandManager, openProject);
        menu.addSeparator();
		menu.addCommandItem (commandManager, quickSave);
		menu.addCommandItem (commandManager, quickLoad);
		menu.addSeparator();
        menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
    }

    return menu;
}

void MainContentComponent::menuItemSelected (int menuItemID, int /*topLevelMenuIndex*/)
{
    // most of our menu items are invoked automatically as commands, but we can handle the
    // other special cases here..

    DBG(("Selected menu item: " + String(menuItemID)));
}


//==============================================================================
// The following methods implement the ApplicationCommandTarget interface, allowing
// this window to publish a set of actions it can perform, and which can be mapped
// onto menus, keypresses, etc.

ApplicationCommandTarget* MainContentComponent::getNextCommandTarget()
{
    // this will return the next parent component that is an ApplicationCommandTarget (in this
    // case, there probably isn't one, but it's best to use this method in your own apps).
    return findFirstTargetParentComponent();
}

void MainContentComponent::getAllCommands (Array <CommandID>& commands)
{
    // this returns the set of all commands that this target can perform..
    const CommandID ids[] = { newProject, quickSave, quickLoad, openProject};

    commands.addArray (ids, numElementsInArray (ids));
}

// This method is used when something needs to find out the details about one of the commands
// that this object can perform..
void MainContentComponent::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
    const String generalCategory ("General");

    switch (commandID)
    {
    case newProject:
        result.setInfo ("New Project", "Shows the new project wizard dialog", generalCategory, 0);
        result.setTicked (false);
        result.addDefaultKeypress ('n', ModifierKeys::ctrlModifier);
        break;
	case quickSave:
        result.setInfo ("Quick Design Save", "Save current design", generalCategory, 0);
        result.setTicked (false);
        result.addDefaultKeypress ('s', ModifierKeys::ctrlModifier);
        break;
	case quickLoad:
        result.setInfo ("Quick Design Load", "Load design from last quick save", generalCategory, 0);
        result.setTicked (false);
        result.addDefaultKeypress ('l', ModifierKeys::ctrlModifier);
        break;
	case openProject:
        result.setInfo ("Open Project", "Load project from last quick save", generalCategory, 0);
        result.setTicked (false);
        result.addDefaultKeypress ('o', ModifierKeys::ctrlModifier);
        break;

    default:
        break;
    };
}

// this is the ApplicationCommandTarget method that is used to actually perform one of our commands..
bool MainContentComponent::perform (const InvocationInfo& info)
{
    switch (info.commandID)
    {
    case newProject:

        if (Constructor::getInstance()->createNewProject()) {
			propertyView->setVisible(true);
			juced->setVisible(true);
		}
        break;

	case quickSave:

        Constructor::getInstance()->quickSave();
        break;

	case quickLoad:

        if (Constructor::getInstance()->createNewProject()) {
			propertyView->setVisible(true);
			juced->setVisible(true);
		}
        break;

	case openProject:

        if (Constructor::getInstance()->openProject()) {
			propertyView->setVisible(true);
			juced->setVisible(true);
		}
        break;

    default:
        return false;
    };

    return true;
}