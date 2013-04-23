/*
  ==============================================================================

    Project.h
    Created: 23 Apr 2013 6:06:09pm
    Author:  admin

  ==============================================================================
*/

#ifndef __PROJECT_H_6EA05458__
#define __PROJECT_H_6EA05458__


class Project
{
public:

	Project();
    Project (const File& _file);
    ~Project();

    class Item
    {
    public:

        Item (const File& _file, Project& _project);
        Item (const Item& other);

		bool isDesign();

        Project& project;
        BigTree* bigTreeBase;
		//UndoManager& undoManager;
		File codeFile;
		File designFile;
		String filename;

    private:
		
		bool _isDesign;
        Item& operator= (const Item&);
    };

    void addItem (const File& _file);
	void openItem (String _filename);

	String projectName;
	String projectPath;
	int projectType;
	int resourceType;
	String selectedTemplate;
	File file;

	//UndoManager* getUndoManager() const              { return &item->undoManager; }

private:
    friend class Item;
	Item *item;	//actual item shown at the editor

	OwnedArray<Item> items;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Project)
};



#endif  // __PROJECT_H_6EA05458__
