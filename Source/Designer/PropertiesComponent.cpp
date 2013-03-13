/*
  ==============================================================================

    PropertiesComponent
    Created: 7 Mar 2013 6:03:29pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"

/*
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
*/

class PropertyView  : public Viewport
{
public:
    PropertyView (Component* content) : Viewport()
    {
        setViewedComponent (content);
		setScrollBarsShown(true, false);
    }

	void setViewedComponent (Component* content) {
		Viewport::setViewedComponent (content, true);
		resized();
	}

    void paint (Graphics& g)
    {
		g.fillAll (Colours::white);
		#ifdef __JUCER_APPEARANCESETTINGS_H_34D762C7__
			IntrojucerLookAndFeel::fillWithBackgroundTexture (*this, g);
		#endif
    }

    void resized()
    {
        Rectangle<int> r (getLocalBounds());
		if (!isVerticalScrollBarShown() || !getVerticalScrollBar()->isVisible()) {
			getViewedComponent()->setBounds(0, 0, r.getWidth(), r.getHeight());
		} else {
			getViewedComponent()->setBounds(0, 0, r.getWidth() - getScrollBarThickness(), r.getHeight());
		}
    }

private:
	ScopedPointer<Component> content;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyView)
};


class PropertyGroup  : public Component
{
public:

    PropertyGroup ()
    {
		setName ("Properties View");
		PropertyGroup (nullptr);
    }

	PropertyGroup (ValueTree *tree) {
		setName ("Properties View");
		if (tree != nullptr) {
			setName((tree->hasProperty(Attributes::name)) ? tree->getProperty(Attributes::name) : "undefined");
			setName((tree->hasProperty(Attributes::objectType)) ? getName() + " : " + tree->getProperty(Attributes::objectType.toString()) : getName());
			Identifier t;
			for (int i = tree->getNumProperties(); --i >= 0;) {
				t = tree->getPropertyName(i);
				if (Attributes::isVisibleAsProperty(t)) {	// != Attributes::object) {
					properties.add (new TextPropertyComponent (tree->getPropertyAsValue(t, 0), t.toString(), 96, false));
				}
			}
		}

		for (int i = properties.size(); --i >= 0;)
            addAndMakeVisible (properties.getUnchecked(i));

		//parentSizeChanged();
		resized();
	}


	void paint (Graphics& g)
    {
		const Colour bkg (Colour((uint8) 245, (uint8) 245, (uint8) 245));	//(Colours::black);//

        g.setColour (Colours::lightgrey.withAlpha (0.35f));
        if (properties.size() > 0)
			g.fillRect (0, 30, getWidth(), getHeight() - 38);

        g.setFont (Font (15.0f, Font::bold));
        g.setColour (bkg.contrasting (0.7f));
        g.drawFittedText (getName(), 12, 0, getWidth() - 16, 25, Justification::bottomLeft, 1);
    }

	void resized()
    {
        int height = 38;

        for (int i = 0; i < properties.size(); ++i)
        {
            PropertyComponent* pp = properties.getUnchecked(i);
            pp->setBounds (10, height, getWidth() - 20, pp->getPreferredHeight());
            height += pp->getHeight();
        }

        height += 16;
        setBounds (0, 0, getWidth(), height);
        //return height;	TODO: update parent container to fit this group of properties
    }

	OwnedArray<PropertyComponent> properties;

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyGroup)
};




