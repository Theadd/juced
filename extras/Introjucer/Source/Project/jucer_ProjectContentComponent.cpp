/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#include "jucer_ProjectContentComponent.h"
#include "../Application/jucer_MainWindow.h"
#include "../Application/jucer_Application.h"
#include "../Code Editor/jucer_SourceCodeEditor.h"
#include "jucer_ConfigPage.h"
#include "jucer_TreeViewTypes.h"
#include "../Project Saving/jucer_ProjectExporter.h"


//==============================================================================
class FileTreeTab   : public TreePanelBase
{
public:
    FileTreeTab (Project& p)
        : TreePanelBase (&p, "fileTreeState")
    {
        tree.setMultiSelectEnabled (true);
        setRoot (new GroupTreeViewItem (p.getMainGroup()));
    }
};

//==============================================================================
class ConfigTreeTab   : public TreePanelBase
{
public:
    ConfigTreeTab (Project& p)
        : TreePanelBase (&p, "settingsTreeState")
    {
        tree.setMultiSelectEnabled (false);
        setRoot (createProjectConfigTreeViewRoot (p));

        if (tree.getNumSelectedItems() == 0)
            tree.getRootItem()->setSelected (true, true);

       #if JUCE_MAC || JUCE_WINDOWS
        addAndMakeVisible (&openProjectButton);
        openProjectButton.setCommandToTrigger (commandManager, CommandIDs::openInIDE, true);
        openProjectButton.setButtonText (commandManager->getNameOfCommand (CommandIDs::openInIDE));
        openProjectButton.setColour (TextButton::buttonColourId, Colours::white.withAlpha (0.5f));

        addAndMakeVisible (&saveAndOpenButton);
        saveAndOpenButton.setCommandToTrigger (commandManager, CommandIDs::saveAndOpenInIDE, true);
        saveAndOpenButton.setButtonText (commandManager->getNameOfCommand (CommandIDs::saveAndOpenInIDE));
        saveAndOpenButton.setColour (TextButton::buttonColourId, Colours::white.withAlpha (0.5f));
       #endif
    }

    void resized()
    {
        Rectangle<int> r (getAvailableBounds());
        r.removeFromBottom (6);

        if (saveAndOpenButton.isVisible())
            saveAndOpenButton.setBounds (r.removeFromBottom (30).reduced (16, 4));

        if (openProjectButton.isVisible())
            openProjectButton.setBounds (r.removeFromBottom (30).reduced (16, 4));

        tree.setBounds (r);
    }

    TextButton openProjectButton, saveAndOpenButton;
};

//==============================================================================
class LogoComponent  : public Component
{
public:
    LogoComponent() {}

    void paint (Graphics& g)
    {
        const Path& logo = getIcons().mainJuceLogo;
        const AffineTransform trans (RectanglePlacement (RectanglePlacement::centred)
                                        .getTransformToFit (logo.getBounds(),
                                                            getLocalBounds().toFloat()));

        g.setColour (findColour (mainBackgroundColourId).contrasting (0.3f));
        g.fillPath (logo, trans);
    }
};

//==============================================================================
ProjectContentComponent::ProjectContentComponent()
    : project (nullptr),
      currentDocument (nullptr),
      treeViewTabs (TabbedButtonBar::TabsAtTop)
{
    setOpaque (true);
    setWantsKeyboardFocus (true);

    addAndMakeVisible (logo = new LogoComponent());

    treeSizeConstrainer.setMinimumWidth (200);
    treeSizeConstrainer.setMaximumWidth (500);

    treeViewTabs.setOutline (0);
    treeViewTabs.getTabbedButtonBar().setMinimumTabScaleFactor (0.3);

    IntrojucerApp::getApp().openDocumentManager.addListener (this);
}

ProjectContentComponent::~ProjectContentComponent()
{
    IntrojucerApp::getApp().openDocumentManager.removeListener (this);

    logo = nullptr;
    setProject (nullptr);
    contentView = nullptr;
    removeChildComponent (&bubbleMessage);
    jassert (getNumChildComponents() <= 1);
}

void ProjectContentComponent::paint (Graphics& g)
{
    IntrojucerLookAndFeel::fillWithBackgroundTexture (*this, g);
}

void ProjectContentComponent::paintOverChildren (Graphics& g)
{
    if (resizerBar != nullptr)
    {
        const int shadowSize = 15;
        const int x = resizerBar->getX();

        ColourGradient cg (Colours::black.withAlpha (0.25f), (float) x, 0,
                           Colours::transparentBlack,        (float) (x - shadowSize), 0, false);
        cg.addColour (0.4, Colours::black.withAlpha (0.07f));
        cg.addColour (0.6, Colours::black.withAlpha (0.02f));

        g.setGradientFill (cg);
        g.fillRect (x - shadowSize, 0, shadowSize, getHeight());
    }
}

void ProjectContentComponent::resized()
{
    Rectangle<int> r (getLocalBounds());

    if (treeViewTabs.isVisible())
        treeViewTabs.setBounds (r.removeFromLeft (treeViewTabs.getWidth()));

    if (resizerBar != nullptr)
        resizerBar->setBounds (r.withWidth (4));

    if (contentView != nullptr)
        contentView->setBounds (r);

    logo->setBounds (r.reduced (r.getWidth() / 4, r.getHeight() / 4));
}

void ProjectContentComponent::lookAndFeelChanged()
{
    repaint();
}

void ProjectContentComponent::childBoundsChanged (Component* child)
{
    if (child == &treeViewTabs)
        resized();
}

void ProjectContentComponent::setProject (Project* newProject)
{
    if (project != newProject)
    {
        if (project != nullptr)
            project->removeChangeListener (this);

        contentView = nullptr;
        resizerBar = nullptr;

        deleteProjectTabs();
        project = newProject;
        rebuildProjectTabs();
    }
}

void ProjectContentComponent::rebuildProjectTabs()
{
    deleteProjectTabs();

    if (project != nullptr)
    {
        addAndMakeVisible (&treeViewTabs);

        createProjectTabs();

        PropertiesFile& settings = project->getStoredProperties();

        const String lastTabName (settings.getValue ("lastTab"));
        int lastTabIndex = treeViewTabs.getTabNames().indexOf (lastTabName);

        if (lastTabIndex < 0 || lastTabIndex > treeViewTabs.getNumTabs())
            lastTabIndex = 1;

        treeViewTabs.setCurrentTabIndex (lastTabIndex);

        int lastTreeWidth = settings.getValue ("projectPanelWidth").getIntValue();
        if (lastTreeWidth < 150)
            lastTreeWidth = 240;

        treeViewTabs.setBounds (0, 0, lastTreeWidth, getHeight());

        addAndMakeVisible (resizerBar = new ResizableEdgeComponent (&treeViewTabs, &treeSizeConstrainer,
                                                                    ResizableEdgeComponent::rightEdge));
        resizerBar->setAlwaysOnTop (true);

        project->addChangeListener (this);

        updateMissingFileStatuses();
    }
    else
    {
        treeViewTabs.setVisible (false);
    }

    resized();
}

void ProjectContentComponent::createProjectTabs()
{
    jassert (project != nullptr);
    const Colour tabColour (Colours::transparentBlack);

    treeViewTabs.addTab ("Files",  tabColour, new FileTreeTab (*project), true);
    treeViewTabs.addTab ("Config", tabColour, new ConfigTreeTab (*project), true);
}

void ProjectContentComponent::deleteProjectTabs()
{
    if (project != nullptr && treeViewTabs.isShowing())
    {
        PropertiesFile& settings = project->getStoredProperties();

        if (treeViewTabs.getWidth() > 0)
            settings.setValue ("projectPanelWidth", treeViewTabs.getWidth());

        if (treeViewTabs.getNumTabs() > 0)
            settings.setValue ("lastTab", treeViewTabs.getCurrentTabName());
    }

    treeViewTabs.clearTabs();
}

TreeView* ProjectContentComponent::getFilesTreeView() const
{
    if (FileTreeTab* ft = dynamic_cast<FileTreeTab*> (treeViewTabs.getTabContentComponent (0)))
        return &(ft->tree);

    return nullptr;
}

ProjectTreeViewBase* ProjectContentComponent::getFilesTreeRoot() const
{
    if (TreeView* tv = getFilesTreeView())
        return dynamic_cast <ProjectTreeViewBase*> (tv->getRootItem());

    return nullptr;
}

void ProjectContentComponent::saveTreeViewState()
{
    for (int i = treeViewTabs.getNumTabs(); --i >= 0;)
        if (TreePanelBase* t = dynamic_cast<TreePanelBase*> (treeViewTabs.getTabContentComponent (i)))
            t->saveOpenness();
}

void ProjectContentComponent::saveOpenDocumentList()
{
    if (project != nullptr)
    {
        ScopedPointer<XmlElement> xml (recentDocumentList.createXML());

        if (xml != nullptr)
            project->getStoredProperties().setValue ("lastDocs", xml);
    }
}

void ProjectContentComponent::reloadLastOpenDocuments()
{
    if (project != nullptr)
    {
        ScopedPointer<XmlElement> xml (project->getStoredProperties().getXmlValue ("lastDocs"));

        if (xml != nullptr)
        {
            recentDocumentList.restoreFromXML (*project, *xml);
            showDocument (recentDocumentList.getCurrentDocument(), true);
        }
    }
}

void ProjectContentComponent::documentAboutToClose (OpenDocumentManager::Document* document)
{
    hideDocument (document);
}

void ProjectContentComponent::changeListenerCallback (ChangeBroadcaster*)
{
    updateMissingFileStatuses();
}

void ProjectContentComponent::updateMissingFileStatuses()
{
    if (ProjectTreeViewBase* p = getFilesTreeRoot())
        p->checkFileStatus();
}

bool ProjectContentComponent::showEditorForFile (const File& f, bool grabFocus)
{
    return getCurrentFile() == f
            || showDocument (IntrojucerApp::getApp().openDocumentManager.openFile (project, f), grabFocus);
}

File ProjectContentComponent::getCurrentFile() const
{
    return currentDocument != nullptr ? currentDocument->getFile()
                                      : File::nonexistent;
}

bool ProjectContentComponent::showDocument (OpenDocumentManager::Document* doc, bool grabFocus)
{
    if (doc == nullptr)
        return false;

    if (doc->hasFileBeenModifiedExternally())
        doc->reloadFromFile();

    if (doc == getCurrentDocument() && contentView != nullptr)
    {
        if (grabFocus)
            contentView->grabKeyboardFocus();

        return true;
    }

    recentDocumentList.newDocumentOpened (doc);

    bool opened = setEditorComponent (doc->createEditor(), doc);

    if (opened && grabFocus)
        contentView->grabKeyboardFocus();

    return opened;
}

void ProjectContentComponent::hideEditor()
{
    currentDocument = nullptr;
    contentView = nullptr;
    updateMainWindowTitle();
    commandManager->commandStatusChanged();
    resized();
}

void ProjectContentComponent::hideDocument (OpenDocumentManager::Document* doc)
{
    if (doc == currentDocument)
    {
        if (OpenDocumentManager::Document* replacement = recentDocumentList.getClosestPreviousDocOtherThan (doc))
            showDocument (replacement, true);
        else
            hideEditor();
    }
}

bool ProjectContentComponent::setEditorComponent (Component* editor,
                                                  OpenDocumentManager::Document* doc)
{
	AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "commented alert for copy & paste");
	juced = new JUCE_Designer();

	addAndMakeVisible(juced);
	juced->setBounds(this->getLocalBounds());
	juced->setAlwaysOnTop(true);
	Component* toolbox;
	toolbox = juced->createToolbox(1, 32, 5);
	juced->addToolboxItem(toolbox, "juced_Window", "Window", BinaryData::window_png, BinaryData::window_pngSize);
	juced->addToolboxItem(toolbox, "juced_Label", "Text label", BinaryData::label_png, BinaryData::label_pngSize);
	juced->addToolboxItem(toolbox, "juced_TextButton", "Text button", BinaryData::button_png, BinaryData::button_pngSize);
	//juced->addToolboxItem(toolbox, "juced_Textbox", "Textbox", BinaryData::textbox_png, BinaryData::textbox_pngSize);
	//juced->addToolboxItem(toolbox, "juced_Combobox", "Combobox", BinaryData::combobox_png, BinaryData::combobox_pngSize);
	//juced->addToolboxItem(toolbox, "juced_Listbox", "Listbox", BinaryData::listbox_png, BinaryData::listbox_pngSize);
	//juced->addToolboxItem(toolbox, "juced_TabPanel", "Tab panel", BinaryData::tabs_png, BinaryData::tabs_pngSize);
	toolbox->setAlwaysOnTop(true);
	juced->addAndMakeVisible(toolbox, 11);

	Viewport *propertyView = juced->getPropertyView();
	addAndMakeVisible(propertyView);
	propertyView->setBounds(100, 100, 200, 400);
	propertyView->setOpaque(true);
	//int style = (ComponentPeer::windowHasTitleBar | ComponentPeer::windowIsResizable);
	propertyView->addToDesktop((int)(ComponentPeer::windowHasTitleBar | ComponentPeer::windowIsResizable));

    if (editor != nullptr)
    {
        contentView = nullptr;
        contentView = juced;//editor;
        currentDocument = doc;
        addAndMakeVisible (juced);//(editor);
        resized();

        updateMainWindowTitle();
        commandManager->commandStatusChanged();
        return true;
    }

    updateMainWindowTitle();
    return false;
}

void ProjectContentComponent::closeDocument()
{
    if (currentDocument != nullptr)
        IntrojucerApp::getApp().openDocumentManager.closeDocument (currentDocument, true);
    else if (contentView != nullptr)
        if (! goToPreviousFile())
            hideEditor();
}

void ProjectContentComponent::saveDocument()
{
    if (currentDocument != nullptr)
    {
        if (! currentDocument->save())
            AlertWindow::showMessageBox (AlertWindow::WarningIcon,
                                         TRANS("Save failed!"),
                                         TRANS("Couldn't save the file:")
                                           + "\n" + currentDocument->getFile().getFullPathName());
    }
    else
        saveProject();

    updateMainWindowTitle();
}

bool ProjectContentComponent::goToPreviousFile()
{
    OpenDocumentManager::Document* doc = recentDocumentList.getCurrentDocument();

    if (doc == nullptr || doc == getCurrentDocument())
        doc = recentDocumentList.getPrevious();

    return showDocument (doc, true);
}

bool ProjectContentComponent::goToNextFile()
{
    return showDocument (recentDocumentList.getNext(), true);
}

bool ProjectContentComponent::canGoToCounterpart() const
{
    return currentDocument != nullptr
            && currentDocument->getCounterpartFile().exists();
}

bool ProjectContentComponent::goToCounterpart()
{
    if (currentDocument != nullptr)
    {
        const File file (currentDocument->getCounterpartFile());

        if (file.exists())
            return showEditorForFile (file, true);
    }

    return false;
}

bool ProjectContentComponent::saveProject()
{
    return project != nullptr
            && project->save (true, true) == FileBasedDocument::savedOk;
}

void ProjectContentComponent::closeProject()
{
    if (MainWindow* const mw = findParentComponentOfClass<MainWindow>())
        mw->closeCurrentProject();
}

void ProjectContentComponent::openInIDE()
{
    if (project != nullptr)
    {
        for (Project::ExporterIterator exporter (*project); exporter.next();)
            if (exporter->launchProject())
                break;
    }
}

void ProjectContentComponent::deleteSelectedTreeItems()
{
    if (TreePanelBase* const tree = dynamic_cast<TreePanelBase*> (treeViewTabs.getCurrentContentComponent()))
        tree->deleteSelectedItems();
}

void ProjectContentComponent::updateMainWindowTitle()
{
    if (MainWindow* mw = findParentComponentOfClass<MainWindow>())
    {
        String title;
        File file;
        bool edited = false;

        if (currentDocument != nullptr)
        {
            title = currentDocument->getName();
            edited = currentDocument->needsSaving();
            file = currentDocument->getFile();
        }

        if (ComponentPeer* peer = mw->getPeer())
        {
            if (! peer->setDocumentEditedStatus (edited))
                if (edited)
                    title << "*";

            peer->setRepresentedFile (file);
        }

        mw->updateTitle (title);
    }
}

void ProjectContentComponent::showBubbleMessage (const Rectangle<int>& pos, const String& text)
{
    addChildComponent (&bubbleMessage);
    bubbleMessage.setColour (BubbleComponent::backgroundColourId, Colours::white.withAlpha (0.7f));
    bubbleMessage.setColour (BubbleComponent::outlineColourId, Colours::black.withAlpha (0.8f));
    bubbleMessage.setAlwaysOnTop (true);

    bubbleMessage.showAt (pos, AttributedString (text), 3000, true, false);
}

//==============================================================================
ApplicationCommandTarget* ProjectContentComponent::getNextCommandTarget()
{
    return findFirstTargetParentComponent();
}

void ProjectContentComponent::getAllCommands (Array <CommandID>& commands)
{
    const CommandID ids[] = { CommandIDs::saveDocument,
                              CommandIDs::closeDocument,
                              CommandIDs::saveProject,
                              CommandIDs::closeProject,
                              CommandIDs::openInIDE,
                              CommandIDs::saveAndOpenInIDE,
                              CommandIDs::showFilePanel,
                              CommandIDs::showConfigPanel,
                              CommandIDs::goToPreviousDoc,
                              CommandIDs::goToNextDoc,
                              CommandIDs::goToCounterpart,
                              CommandIDs::deleteSelectedItem };

    commands.addArray (ids, numElementsInArray (ids));
}

void ProjectContentComponent::getCommandInfo (const CommandID commandID, ApplicationCommandInfo& result)
{
    String documentName;
    if (currentDocument != nullptr)
        documentName = " '" + currentDocument->getName().substring (0, 32) + "'";

   #if JUCE_MAC
    const ModifierKeys cmdCtrl (ModifierKeys::ctrlModifier | ModifierKeys::commandModifier);
   #else
    const ModifierKeys cmdCtrl (ModifierKeys::ctrlModifier | ModifierKeys::altModifier);
   #endif

    switch (commandID)
    {
    case CommandIDs::saveProject:
        result.setInfo ("Save Project",
                        "Saves the current project",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        break;

    case CommandIDs::closeProject:
        result.setInfo ("Close Project",
                        "Closes the current project",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        break;

    case CommandIDs::saveDocument:
        result.setInfo ("Save" + documentName,
                        "Saves the current document",
                        CommandCategories::general, 0);
        result.setActive (currentDocument != nullptr || project != nullptr);
        result.defaultKeypresses.add (KeyPress ('s', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::closeDocument:
        result.setInfo ("Close" + documentName,
                        "Closes the current document",
                        CommandCategories::general, 0);
        result.setActive (contentView != nullptr);
        result.defaultKeypresses.add (KeyPress ('w', cmdCtrl, 0));
        break;

    case CommandIDs::goToPreviousDoc:
        result.setInfo ("Previous Document", "Go to previous document", CommandCategories::general, 0);
        result.setActive (recentDocumentList.canGoToPrevious());
        result.defaultKeypresses.add (KeyPress (KeyPress::leftKey, cmdCtrl, 0));
        break;

    case CommandIDs::goToNextDoc:
        result.setInfo ("Next Document", "Go to next document", CommandCategories::general, 0);
        result.setActive (recentDocumentList.canGoToNext());
        result.defaultKeypresses.add (KeyPress (KeyPress::rightKey, cmdCtrl, 0));
        break;

    case CommandIDs::goToCounterpart:
        result.setInfo ("Open corresponding header or cpp file", "Open counterpart file", CommandCategories::general, 0);
        result.setActive (canGoToCounterpart());
        result.defaultKeypresses.add (KeyPress (KeyPress::upKey, cmdCtrl, 0));
        break;

    case CommandIDs::openInIDE:
       #if JUCE_MAC
        result.setInfo ("Open in Xcode...",
       #elif JUCE_WINDOWS
        result.setInfo ("Open in Visual Studio...",
       #else
        result.setInfo ("Open as a Makefile...",
       #endif
                        "Launches the project in an external IDE",
                        CommandCategories::general, 0);
        result.setActive (ProjectExporter::canProjectBeLaunched (project));
        break;

    case CommandIDs::saveAndOpenInIDE:
       #if JUCE_MAC
        result.setInfo ("Save Project and Open in Xcode...",
       #elif JUCE_WINDOWS
        result.setInfo ("Save Project and Open in Visual Studio...",
       #else
        result.setInfo ("Save Project and Open as a Makefile...",
       #endif
                        "Saves the project and launches it in an external IDE",
                        CommandCategories::general, 0);
        result.setActive (ProjectExporter::canProjectBeLaunched (project));
        result.defaultKeypresses.add (KeyPress ('l', ModifierKeys::commandModifier | ModifierKeys::shiftModifier, 0));
        break;

    case CommandIDs::showFilePanel:
        result.setInfo ("Show File Panel",
                        "Shows the tree of files for this project",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        result.defaultKeypresses.add (KeyPress ('p', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::showConfigPanel:
        result.setInfo ("Show Config Panel",
                        "Shows the build options for the project",
                        CommandCategories::general, 0);
        result.setActive (project != nullptr);
        result.defaultKeypresses.add (KeyPress ('i', ModifierKeys::commandModifier, 0));
        break;

    case CommandIDs::deleteSelectedItem:
        result.setInfo ("Delete Selected File", String::empty, CommandCategories::general, 0);
        result.defaultKeypresses.add (KeyPress (KeyPress::deleteKey, 0, 0));
        result.defaultKeypresses.add (KeyPress (KeyPress::backspaceKey, 0, 0));
        result.setActive (dynamic_cast<TreePanelBase*> (treeViewTabs.getCurrentContentComponent()) != nullptr);
        break;

    default:
        break;
    }
}

bool ProjectContentComponent::isCommandActive (const CommandID)
{
    return project != nullptr;
}

bool ProjectContentComponent::perform (const InvocationInfo& info)
{
    switch (info.commandID)
    {
        case CommandIDs::saveProject:
        case CommandIDs::closeProject:
        case CommandIDs::saveDocument:
        case CommandIDs::closeDocument:
        case CommandIDs::goToPreviousDoc:
        case CommandIDs::goToNextDoc:
        case CommandIDs::goToCounterpart:
        case CommandIDs::saveAndOpenInIDE:
            if (reinvokeCommandAfterCancellingModalComps (info))
            {
                grabKeyboardFocus(); // to force any open labels to close their text editors
                return true;
            }

            break;

        default:
            break;
    }

    switch (info.commandID)
    {
        case CommandIDs::saveProject:               saveProject(); break;
        case CommandIDs::closeProject:              closeProject(); break;
        case CommandIDs::saveDocument:              saveDocument(); break;

        case CommandIDs::closeDocument:             closeDocument(); break;
        case CommandIDs::goToPreviousDoc:           goToPreviousFile(); break;
        case CommandIDs::goToNextDoc:               goToNextFile(); break;
        case CommandIDs::goToCounterpart:           goToCounterpart(); break;

        case CommandIDs::showFilePanel:             treeViewTabs.setCurrentTabIndex (0); break;
        case CommandIDs::showConfigPanel:           treeViewTabs.setCurrentTabIndex (1); break;

        case CommandIDs::openInIDE:                 openInIDE(); break;

        case CommandIDs::deleteSelectedItem:        deleteSelectedTreeItems(); break;

        case CommandIDs::saveAndOpenInIDE:
            if (saveProject())
                openInIDE();

            break;

        default:
            return false;
    }

    return true;
}
