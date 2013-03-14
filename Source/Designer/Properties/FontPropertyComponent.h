/*
  ==============================================================================

    FontPropertyComponent.h
    Created: 13 Mar 2013 9:38:32pm
    Author:  admin

  ==============================================================================
*/

#ifndef __FONTPROPERTYCOMPONENT_H_9E7AFC25__
#define __FONTPROPERTYCOMPONENT_H_9E7AFC25__

#include "../Globals.h"

class FontPropertyComponent    : public ChoicePropertyComponent
{
public:
    FontPropertyComponent (const String& name);
    ~FontPropertyComponent();

    //==============================================================================
    static const String defaultFont;
    static const String defaultSans;
    static const String defaultSerif;
    static const String defaultMono;

    static void preloadAllFonts();

    virtual void setTypefaceName (const String& newFontName) = 0;
    virtual String getTypefaceName() const = 0;

    static const Font applyNameToFont (const String& typefaceName, const Font& font);
    static const String getTypefaceNameCode (const String& typefaceName);
    static const String getFontStyleCode (const Font& font);

    static const String getCompleteFontCode (const Font& font, const String& typefaceName);

    //==============================================================================
    void setIndex (int newIndex);
    int getIndex() const;
};



#endif  // __FONTPROPERTYCOMPONENT_H_9E7AFC25__
