/*
  ==============================================================================

    PropertiesComponent
    Created: 7 Mar 2013 6:03:29pm
    Author:  admin

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

class PropertyListBuilder
{
public:
    PropertyListBuilder() {}

    void add (PropertyComponent* propertyComp)
    {
        components.add (propertyComp);
    }

    void add (PropertyComponent* propertyComp, const String& tooltip)
    {
        propertyComp->setTooltip (tooltip);
        add (propertyComp);
    }

    void addSearchPathProperty (const Value& value, const String& name, const String& mainHelpText)
    {
        add (new TextPropertyComponent (value, name, 16384, true),
             mainHelpText + " Use semi-colons or new-lines to separate multiple paths.");
    }

    void setPreferredHeight (int height)
    {
        for (int j = components.size(); --j >= 0;)
            components.getUnchecked(j)->setPreferredHeight (height);
    }

    Array <PropertyComponent*> components;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyListBuilder)
};


class PropertyGroup  : public Component
{
public:
    PropertyGroup()  {}

    void setProperties (const PropertyListBuilder& newProps)
    {
        properties.clear();
        properties.addArray (newProps.components);

        for (int i = properties.size(); --i >= 0;)
            addAndMakeVisible (properties.getUnchecked(i));
    }

    int updateSize (int x, int y, int width)
    {
        int height = 38;

        for (int i = 0; i < properties.size(); ++i)
        {
            PropertyComponent* pp = properties.getUnchecked(i);
            pp->setBounds (10, height, width - 20, pp->getPreferredHeight());
            height += pp->getHeight();
        }

        height += 16;
        setBounds (x, y, width, height);
        return height;
    }

    void paint (Graphics& g)
    {
        const Colour bkg (Colour((uint8) 245, (uint8) 245, (uint8) 245));

        g.setColour (Colours::white.withAlpha (0.35f));
        g.fillRect (0, 30, getWidth(), getHeight() - 38);

        g.setFont (Font (15.0f, Font::bold));
        g.setColour (bkg.contrasting (0.7f));
        g.drawFittedText (getName(), 12, 0, getWidth() - 16, 25, Justification::bottomLeft, 1);
    }

    OwnedArray<PropertyComponent> properties;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyGroup)
};



class PropertyPanelViewport  : public Component
{
public:
    PropertyPanelViewport (Component* content)
    {
        addAndMakeVisible (&viewport);
        //addAndMakeVisible (&rolloverHelp);
        viewport.setViewedComponent (content, true);
		//content->setBounds(0, 0, 200, 300);
		resized();
    }

    void paint (Graphics& g)
    {
        //IntrojucerLookAndFeel::fillWithBackgroundTexture (*this, g);
		g.fillAll (Colour((uint8) 128, (uint8) 128, (uint8) 128));
    }

    void resized()
    {
        Rectangle<int> r (getLocalBounds());
        //rolloverHelp.setBounds (r.removeFromBottom (70).reduced (10, 0));
		viewport.getViewedComponent()->setBounds(0, 0, r.getWidth(), r.getHeight());
        viewport.setBounds (r);
    }

    Viewport viewport;
    //RolloverHelpComp rolloverHelp;

private:
	ScopedPointer<Component> content;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyPanelViewport)
};


class PropertiesComponent  : public Component
{
public:
	/*ProjectExporter::BuildConfiguration* conf,*/ 
    PropertiesComponent (const String& expName)
    {
		group.setName (expName);
		//TODO: remove
		str1 = new String("propietat nom");
		val_str1 = new Value(group.getName());
		str2 = new String("propietat user notes\n mes notes ee\nasd");
		val_str2 = new Value(*str2);
		//
        addAndMakeVisible (&group);

        PropertyListBuilder props;
        createPropertyEditors (props);
        group.setProperties (props);
        group.setName (expName + " [nomGrup]");// + " / " + conf->getName());
        parentSizeChanged();
    }

	void createPropertyEditors (PropertyListBuilder& props)
	{
		props.add (new TextPropertyComponent (*val_str1, "Name", 96, false),
               "The name of this configuration.");

		props.add (new TextPropertyComponent (*val_str2, "Notes", 32768, true),
               "Extra comments: This field is not used for code or project generation, it's just a space where you can express your thoughts.");
		props.add (new TextPropertyComponent (*val_str1, "Name", 96, false),
               "The name of this configuration.");

		props.add (new TextPropertyComponent (*val_str2, "Notes", 32768, true),
               "Extra comments: This field is not used for code or project generation, it's just a space where you can express your thoughts.");
		props.add (new TextPropertyComponent (*val_str1, "Name", 96, false),
               "The name of this configuration.");

		props.add (new TextPropertyComponent (*val_str2, "Notes", 32768, true),
               "Extra comments: This field is not used for code or project generation, it's just a space where you can express your thoughts.");
		props.add (new TextPropertyComponent (*val_str1, "Name", 96, false),
               "The name of this configuration.");

		props.add (new TextPropertyComponent (*val_str2, "Notes", 32768, true),
               "Extra comments: This field is not used for code or project generation, it's just a space where you can express your thoughts.");

	}

	void paint (Graphics& g)
    {
        //IntrojucerLookAndFeel::fillWithBackgroundTexture (*this, g);
		g.fillAll (Colour((uint8) 255, (uint8) 0, (uint8) 0));
    }

	void resized()
    {
        group.updateSize(0, 0, getWidth());
    }


	//Value getNameValue() { return getValue (Ids::name); }
	//Value getUserNotes()                                { return getValue (Ids::userNotes); }

    //Value getValue (const Identifier& nm)               { return config.getPropertyAsValue (nm, getUndoManager()); }
    //UndoManager* getUndoManager() const                 { return project.getUndoManagerFor (config); }

    //void parentSizeChanged()  { updateSize (*this, group); }

private:
    PropertyGroup group;
	ScopedPointer<String> str1;
	ScopedPointer<String> str2;
	ScopedPointer<Value> val_str1;
	ScopedPointer<Value> val_str2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertiesComponent)
};




