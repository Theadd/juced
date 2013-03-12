/*
  ==============================================================================

    juced_Label.h
    Created: 11 Mar 2013 9:34:46pm
    Author:  admin

  ==============================================================================
*/

#ifndef __JUCED_LABEL_H_9DD865FB__
#define __JUCED_LABEL_H_9DD865FB__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Designer/BaseModules.h"

class juced_Label    : public Label,
					   public DynamicObject
{
public:

	ValueTree *linkedValueTree;

    juced_Label();

	typedef ReferenceCountedObjectPtr<juced_Label> Ptr;

private:

};


#endif  // __JUCED_LABEL_H_9DD865FB__
