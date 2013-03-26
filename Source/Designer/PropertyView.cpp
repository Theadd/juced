/*
  ==============================================================================

    PropertyView.cpp
    Created: 20 Mar 2013 2:33:37pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"


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
	//ScopedPointer<Component> content;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PropertyView)
};
