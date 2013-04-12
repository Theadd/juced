/*
  ==============================================================================

    Importer.h
    Created: 12 Apr 2013 9:39:39pm
    Author:  admin

  ==============================================================================
*/

#ifndef __IMPORTER_H_598AFFA7__
#define __IMPORTER_H_598AFFA7__


class Importer
{
public:

    Importer(File xmlFile);

	Importer(XmlElement *xml, String parentComponentID = String::empty);

private:

	void create(XmlElement *xml, String parentComponentID = String::empty);
};


#endif  // __IMPORTER_H_598AFFA7__
