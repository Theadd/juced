/*
  ==============================================================================

    BaseModules.cpp
    Created: 11 Mar 2013 7:49:07pm
    Author:  admin

  ==============================================================================
*/

#include "BaseModules.h"

juced_BaseWindow::juced_BaseWindow (String _name, Colour _colour, DocumentWindow::TitleBarButtons _buttons) : 
					DocumentWindow (_name, _colour, _buttons)
{
	setProperty(Ids::objectType, "window");
	
}
