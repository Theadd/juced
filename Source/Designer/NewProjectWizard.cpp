/*
  ==============================================================================

    NewProjectWizard.cpp
    Created: 22 Apr 2013 12:06:22am
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "Constructor.h"

class NewProjectContainer : public Component
{
public:

    NewProjectContainer() : Component()
    {
        setBounds(0, 0, 400, 325);
        setName("Container");
        Label1.setBounds(15, 13, 120, 20);
        Label1.setText("Project name", false);
        Label1.setColour(Label::backgroundColourId, Colour::fromString("00000000"));
        Label1.setColour(Label::textColourId, Colour::fromString("FF000000"));
        Label1.setEditable(0);
        Label1.setName("Label");
        addAndMakeVisible(&Label1);
        Label2.setBounds(15, 37, 120, 20);
        Label2.setText("Project path", false);
        Label2.setColour(Label::backgroundColourId, Colour::fromString("00000000"));
        Label2.setColour(Label::textColourId, Colour::fromString("FF000000"));
        Label2.setEditable(0);
        Label2.setName("Label");
        addAndMakeVisible(&Label2);
        Label3.setBounds(15, 61, 120, 20);
        Label3.setText("Project type", false);
        Label3.setColour(Label::backgroundColourId, Colour::fromString("00000000"));
        Label3.setColour(Label::textColourId, Colour::fromString("FF000000"));
        Label3.setEditable(0);
        Label3.setName("Label");
        addAndMakeVisible(&Label3);
        Label4.setBounds(15, 85, 120, 20);
        Label4.setText("Resource type", false);
        Label4.setColour(Label::backgroundColourId, Colour::fromString("00000000"));
        Label4.setColour(Label::textColourId, Colour::fromString("FF000000"));
        Label4.setEditable(0);
        Label4.setName("Label");
        addAndMakeVisible(&Label4);
        Label5.setBounds(209, 108, 120, 20);
        Label5.setText("Template:", false);
        Label5.setColour(Label::backgroundColourId, Colour::fromString("00000000"));
        Label5.setColour(Label::textColourId, Colour::fromString("FF000000"));
        Label5.setEditable(0);
        Label5.setName("Label");
        addAndMakeVisible(&Label5);
        projectType.setBounds(139, 61, 240, 20);
        projectType.setText("GUI Application", false);
        projectType.setColour(ComboBox::backgroundColourId, Colour::fromString("FFFFFFFF"));
        projectType.setColour(ComboBox::textColourId, Colour::fromString("FF000000"));
        projectType.addItem("GUI Application", 1);
        projectType.setName("Box");
        addAndMakeVisible(&projectType);
        selectedTemplate.addMouseListener(this, false);
        selectedTemplate.setBounds(214, 128, 165, 20);
        selectedTemplate.setText("Empty", false);
        selectedTemplate.setColour(ComboBox::backgroundColourId, Colour::fromString("FFFFFFFF"));
        selectedTemplate.setColour(ComboBox::textColourId, Colour::fromString("FF000000"));
        selectedTemplate.addItem("Empty", 1);
        selectedTemplate.addItem("Empty with DirectShow", 2);
        //selectedTemplate.addItem("Wizard", 3);
        selectedTemplate.setName("Box");
        addAndMakeVisible(&selectedTemplate);
        resourceType.setBounds(139, 85, 240, 20);
        resourceType.setText("BinaryData", false);
        resourceType.setColour(ComboBox::backgroundColourId, Colour::fromString("FFFFFFFF"));
        resourceType.setColour(ComboBox::textColourId, Colour::fromString("FF000000"));
        resourceType.addItem("BinaryData", 1);
        //resourceType.addItem("Load files from BinaryData folder", 2);
        //resourceType.addItem("Load files from resources folder", 3);
        resourceType.setName("Box");
        addAndMakeVisible(&resourceType);
        projectName.setBounds(139, 13, 240, 20);
        projectName.setText("sample", false);
        projectName.setColour(Label::backgroundColourId, Colour::fromString("FFFFFFFF"));
        projectName.setColour(Label::textColourId, Colour::fromString("FF000000"));
        projectName.showEditor();
        projectName.setEditable(1);
        projectName.setName("Label");
        addAndMakeVisible(&projectName);
		//project folder
		projectPath = new FilenameComponent("Project path", File(), true, true, true, "", "", "");
		projectPath->setBounds(139, 37, 240, 20);
		addAndMakeVisible(projectPath);

		//FilenameComponent(const String &name, const File &currentFile, bool canEditFilename, bool isDirectory, bool isForSaving, const String &fileBrowserWildcard, const String &enforcedSuffix, const String &textWhenNothingSelected)

        templateInfo.setBounds(209, 153, 175, 100);
        templateInfo.setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur sit amet purus neque.", false);
        templateInfo.setColour(Label::backgroundColourId, Colour::fromString("00000000"));
        templateInfo.setColour(Label::textColourId, Colour::fromString("FF000000"));
        templateInfo.setEditable(0);
        templateInfo.setName("Label");
		templateInfo.setJustificationType(Justification(Justification::topLeft));
        addAndMakeVisible(&templateInfo);
        createButton.addMouseListener(this, false);
        createButton.setBounds(309, 258, 65, 25);
        createButton.setName("TextButton");
        createButton.setButtonText("Create");
        createButton.setConnectedEdges(0);
        addAndMakeVisible(&createButton);
        cancelButton.addMouseListener(this, false);
        cancelButton.setBounds(214, 258, 70, 25);
        cancelButton.setName("TextButton");
        cancelButton.setButtonText("Cancel");
        cancelButton.setConnectedEdges(0);
        addAndMakeVisible(&cancelButton);

    }

	~NewProjectContainer()
	{
		deleteAndZero(projectPath);
	}

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseUp(event);

		if (event.eventComponent == &cancelButton) {
			DialogWindow* dw = this->findParentComponentOfClass<DialogWindow>();
			if (dw != nullptr)
				dw->exitModalState (0);
		} else if (event.eventComponent == &createButton) {
			DialogWindow* dw = this->findParentComponentOfClass<DialogWindow>();
			if (dw != nullptr)
				dw->exitModalState (1);
		}
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            Component::mouseDoubleClick(event);
    }

	ComboBox projectType;
    ComboBox selectedTemplate;
    ComboBox resourceType;
    Label projectName;
    Label templateInfo;
	FilenameComponent *projectPath;

private:
    Label Label1;
    Label Label2;
    Label Label3;
    Label Label4;
    Label Label5;
    TextButton createButton;
    TextButton cancelButton;

};


class NewProjectWizard    : public DialogWindow
{
public:
    NewProjectWizard()  : DialogWindow ("New project", Colours::lightgrey, true)
    {
		//DialogWindow (const String &name, const Colour &backgroundColour, bool escapeKeyTriggersCloseButton, bool addToDesktop=true)
        //centreWithSize(400, 325);
        //setContentOwned (&newProjectContainer, false);
        //setVisible (true);
		
    }

    void mouseUp (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseUp(event);
    }

    void mouseDrag (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDrag(event);
    }

    void mouseDoubleClick (const MouseEvent& event)
    {
        if (event.eventComponent == this)
            DocumentWindow::mouseDoubleClick(event);
    }

	String getProjectName()
	{
		return newProjectContainer.projectName.getText(true);
	}

	String getProjectPath()
	{
		return newProjectContainer.projectPath->getCurrentFile().getFullPathName();
	}

	int getProjectType()
	{
		return newProjectContainer.projectType.getSelectedId();
	}

	int getResourceType()
	{
		return newProjectContainer.resourceType.getSelectedId();
	}

	String getTemplate()
	{
		return newProjectContainer.selectedTemplate.getText();
	}

	int show()
	{
		return showModalDialog ("New project", &newProjectContainer, Constructor::getInstance()->getDesigner(), Colours::lightgrey, true, false, false);
	}

private:
    NewProjectContainer newProjectContainer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectWizard)
};
