/*
  ==============================================================================

    PropertiesComponent
    Created: 7 Mar 2013 6:03:29pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "Constructor.h"
//#include "Properties\FontPropertyComponent.h"

class TextWithButtonPropertyComponent  : public TextPropertyComponent,
										 public Button::Listener
{
public:
	TextButton *button;
	Label *textLabel;

    TextWithButtonPropertyComponent (const Value &ValueToControl, const String &propertyName) : TextPropertyComponent(ValueToControl, propertyName, 96, false)
    {
		textLabel = (Label *) this->getChildComponent(0);
		button = new TextButton("...");
		addAndMakeVisible(button);
		button->setConnectedEdges((int)(TextButton::ConnectedOnRight | TextButton::ConnectedOnLeft));
		button->addListener(this);
		resized();
    }

	~TextWithButtonPropertyComponent()
	{
		button->removeListener(this);
	}

	/*void buttonClicked (Button *button)
	{
		//AlertWindow::showMessageBox(AlertWindow::NoIcon, "parent tree", "is not valid");
	}*/

	void resized()
	{
		TextPropertyComponent::resized();
		//Label *child = (Label *) this->getChildComponent(0);
		//child->setSize(getWidth() - child->getHeight() - child->getX() - 2, child->getHeight());
		textLabel->setSize(getWidth() - textLabel->getHeight() - textLabel->getX() - 2, textLabel->getHeight());
		
        button->setBounds(getWidth() - textLabel->getHeight() - 1, textLabel->getY(), textLabel->getHeight(), textLabel->getHeight());
	}
};

class ColourPropertyComponent  : public TextWithButtonPropertyComponent,
								 public ChangeListener
{
public:
	Colour colour;

	ColourPropertyComponent (const Value &ValueToControl, const String &propertyName) : TextWithButtonPropertyComponent(ValueToControl, propertyName)
    {
		Colour colour = Colour::fromString(ValueToControl.toString());	//Misc::getColourFromStringDisplay(ValueToControl.toString());
		textLabel->setColour(Label::backgroundColourId, colour);
		textLabel->setColour(Label::textColourId, colour.withAlpha(1.0f).contrasting(1.0f));
		textLabel->setText(colour.toDisplayString(true), false);
	}

	~ColourPropertyComponent ()
	{

	}

	void buttonClicked (Button *buttonThatWasClicked)
	{
		if (buttonThatWasClicked != this->button) return;

        ColourSelector* colourSelector = new ColourSelector();
        colourSelector->setName ("background");
        colourSelector->setCurrentColour (colour);	//(TextButton::buttonColourId));
        colourSelector->addChangeListener (this);
        colourSelector->setColour (ColourSelector::backgroundColourId, Colours::transparentBlack);
        colourSelector->setSize (300, 400);

        CallOutBox::launchAsynchronously (colourSelector, getScreenBounds(), nullptr);
	}

	void changeListenerCallback (ChangeBroadcaster *source)
	{
		ColourSelector* cs = dynamic_cast <ColourSelector*> (source);
		colour = cs->getCurrentColour();
		textLabel->setColour(Label::backgroundColourId, colour);
		textLabel->setColour(Label::textColourId, colour.withAlpha(1.0f).contrasting(1.0f));
		textLabel->setText(colour.toDisplayString(true), false);
	}

};


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


class PropertyGroup : public PropertyPanel
{
public:
	PropertyGroup () : PropertyPanel()
    {
		setName ("Properties View");
    }

	PropertyGroup (ValueTree *tree) : PropertyPanel()
	{
		setName ("Properties View");
		if (tree != nullptr) {
			setName((tree->hasProperty(Attributes::name)) ? tree->getProperty(Attributes::name) : "undefined");
			setName((tree->hasProperty(Attributes::objectType)) ? getName() + " : " + tree->getProperty(Attributes::objectType.toString()) : getName());
			Identifier t;
			for (int i = tree->getNumProperties(); --i >= 0;) {
				t = tree->getPropertyName(i);
				Attribute *attrib;
				if ((attrib = Constructor::getInstance()->getAttributeOf(t)) != nullptr) {
					if (attrib->visible) {
						//get propertycomponent object of specified type
						PropertyComponent *comp;
						if (attrib->type == AttributeType::colour) {
							comp = new ColourPropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display);
						} else {
							comp = new TextPropertyComponent(tree->getPropertyAsValue(t, Constructor::getInstance()->getUndoManager()), attrib->display, 96, false);
						}
						//add object to specified group
						if (attrib->group.equalsIgnoreCase("General")) {
							generalGroup.add(comp);
						} else if (attrib->group.equalsIgnoreCase("Bounds")) {
							boundsGroup.add(comp);
						} else if (attrib->group.equalsIgnoreCase("Colours")) {
							coloursGroup.add(comp);
						}
					}
				}
			}
		}

		if (generalGroup.size() > 0) addSection("General", generalGroup);
		if (boundsGroup.size() > 0) addSection("Bounds", boundsGroup);
		if (coloursGroup.size() > 0) addSection("Colours", coloursGroup);

		refreshAll();
	}

private:
	Array<PropertyComponent*> boundsGroup;
	Array<PropertyComponent*> generalGroup;
	Array<PropertyComponent*> coloursGroup;
};

/* This is the old PropertyGroup class we used before switching to PropertyPanel, which has sections.
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
			//AlertWindow::showMessageBox(AlertWindow::NoIcon, "here we go", "...");
			setName((tree->hasProperty(Attributes::name)) ? tree->getProperty(Attributes::name) : "undefined");
			setName((tree->hasProperty(Attributes::objectType)) ? getName() + " : " + tree->getProperty(Attributes::objectType.toString()) : getName());
			Identifier t;
			for (int i = tree->getNumProperties(); --i >= 0;) {
				t = tree->getPropertyName(i);
				Attribute *attrib;
				if ((attrib = Constructor::getInstance()->getAttributeOf(t)) != nullptr) {
					//if (Attributes::isVisibleAsProperty(t)) {
					if (attrib->visible) {
						//AlertWindow::showMessageBox(AlertWindow::NoIcon, "is", "visible");
						if (attrib->type == AttributeType::colour) {
							properties.add (new ColourPropertyComponent(tree->getPropertyAsValue(t, 0), t.toString()));
						} else {
							properties.add (new TextPropertyComponent (tree->getPropertyAsValue(t, 0), t.toString(), 96, false));
						}
					}
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
*/



