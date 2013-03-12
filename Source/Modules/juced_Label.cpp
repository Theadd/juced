/*
  ==============================================================================

    juced_Label.cpp
    Created: 3 Mar 2013 11:27:23pm
    Author:  admin

  ==============================================================================
*/

#include "juced_Label.h"

juced_Label::juced_Label()  : Label ()
{
	this->setText("Text label", false);
	setProperty(Ids::objectType, "label");
	setProperty(Ids::text, getText());
	setProperty(Ids::height, getHeight());
	setProperty(Ids::width, getWidth());
	setProperty(Ids::name, getName());
	setProperty(Ids::className, "juced_Label");
	setComponentID(Uuid().toString());
	setProperty(Ids::ID, getComponentID());
}

