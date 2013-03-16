/*
  ==============================================================================

    Constructor.h
    Created: 16 Mar 2013 4:58:15pm
    Author:  admin

  ==============================================================================
*/

#ifndef __CONSTRUCTOR_H_E78AE279__
#define __CONSTRUCTOR_H_E78AE279__

#include "Globals.h"
#include "../Modules/juced_Label.h"
#include "../Modules/juced_TextButton.h"
#include "../Modules/juced_Window.h"
#include "../Modules/juced_MainComponent.h"

struct Attribute
{
	Identifier name;
	String group;
	bool visible;
	Identifier type;
	String display;
	Identifier valueType;
};

class Constructor {
public:
	Array<Attribute*> _attributes;
	int numAttributes;

	static Constructor* getInstance();
	void loadAttributesFromXmlFile(const File &xmlFile);
	Attribute* getAttributeOf(Identifier _name);

private:
   Constructor(){};  // Private so that it can  not be called
   Constructor(Constructor const&){};             // copy constructor is private
   Constructor& operator=(Constructor const&){};  // assignment operator is private
   static Constructor* m_pInstance;
};



#endif  // __CONSTRUCTOR_H_E78AE279__
