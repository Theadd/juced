/*
  ==============================================================================

    Project.cpp
    Created: 23 Apr 2013 6:06:09pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "BigTree.h"
#include "Project.h"

Project::Project()
{

}

Project::Project (const File& _file) : file(_file)
{

}

Project::~Project()
{

}

Project::Item::Item (const File& _file, Project& _project) : codeFile(_file), project(_project)
{
	if (_file.isHidden()) {
		//do nothing
	}
}

Project::Item::Item (const Item& other) : project(other.project), codeFile(other.codeFile)
{

}

bool Project::Item::isDesign()
{
	return _isDesign;
}

void Project::addItem (const File& _file)
{
	items.add(new Item(_file, *this));
}

void Project::openItem (String _filename)
{

}
