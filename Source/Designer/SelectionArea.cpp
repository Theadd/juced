/*
  ==============================================================================

    SelectionArea.cpp
    Created: 3 Mar 2013 2:25:17pm
    Author:  admin

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

class SelectionArea : public Component
{
public:
    //==============================================================================
	SelectionArea() : Component()
	{
		isComponentSelection = false;
	}

	SelectionArea(bool _isComponentSelection) : Component() {
		isComponentSelection = _isComponentSelection;
	}

	void setSelectionBounds(int x, int y, int width, int height) {
		setBounds(x - 5, y - 5, width + 10, height + 10);
		MiniBox *box;
		box = new MiniBox("upperLeft");
		addAndMakeVisible(box);
		box->setBounds(0, 0, 5, 5);
		miniBoxes.add(box);

		box = new MiniBox("upperRight");
		addAndMakeVisible(box);
		box->setBounds(x + width, 0, 5, 5);
		miniBoxes.add(box);

		box = new MiniBox("bottomLeft");
		addAndMakeVisible(box);
		box->setBounds(0, y + height, 5, 5);
		miniBoxes.add(box);

		box = new MiniBox("bottomRight");
		addAndMakeVisible(box);
		box->setBounds(x + width, y + height, 5, 5);
		miniBoxes.add(box);
	}

	void paint (Graphics& g)
	{
		if (!isComponentSelection) {
			g.fillAll (Colours::white);
			setAlpha(0.3f);
		}
	}

private:
	ScopedPointer<Component> selectedComponent;
	bool isComponentSelection;

	class MiniBox : public Component
	{
	public:
		String name;

		MiniBox(String _name) : Component() {
			setSize(5, 5);
			name = _name;
		}

		String getName() {
			return name;
		}

		void paint (Graphics& g) {
			g.fillAll (Colours::black);
		}
	};

	OwnedArray<MiniBox> miniBoxes;
};