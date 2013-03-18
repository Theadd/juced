/*
  ==============================================================================

    SelectionArea.cpp
    Created: 3 Mar 2013 2:25:17pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"

class SelectionArea : public Component
{
public:
    //==============================================================================
	SelectionArea() : Component()
	{
		isComponentSelection = false;
		ready = false;
	}

	SelectionArea(bool _isComponentSelection) : Component() {
		isComponentSelection = _isComponentSelection;
		setBoxSize(6);
		if (isComponentSelection) {
			MiniBox *box = new MiniBox("upperLeft");
			addAndMakeVisible(box);
			box->addMouseListener(this, false);
			box->setMouseCursor(MouseCursor::TopLeftCornerResizeCursor);
			miniBoxes.add(box);

			box = new MiniBox("upperRight");
			addAndMakeVisible(box);
			box->addMouseListener(this, false);
			box->setMouseCursor(MouseCursor::TopRightCornerResizeCursor);
			miniBoxes.add(box);

			box = new MiniBox("bottomLeft");
			addAndMakeVisible(box);
			box->addMouseListener(this, false);
			box->setMouseCursor(MouseCursor::BottomLeftCornerResizeCursor);
			miniBoxes.add(box);

			box = new MiniBox("bottomRight");
			addAndMakeVisible(box);
			box->addMouseListener(this, false);
			box->setMouseCursor(MouseCursor::BottomRightCornerResizeCursor);
			miniBoxes.add(box);
		}
		ready = false;
	}

	~SelectionArea()
	{
		if (isComponentSelection) {
			for (int i = miniBoxes.size(); --i >= 0;) {
				miniBoxes[i]->removeMouseListener(this);
			}
		}
	}

	void setSelectionBounds(int x, int y, int width, int height) {
		//ready = false;
		setBounds(x - _boxSize, y - _boxSize, width + (_boxSize*2), height + (_boxSize*2));

		miniBoxes[0]->setBounds(0, 0, _boxSize, _boxSize);
		miniBoxes[1]->setBounds(width + _boxSize, 0, _boxSize, _boxSize);
		miniBoxes[2]->setBounds(0, height + _boxSize, _boxSize, _boxSize);
		miniBoxes[3]->setBounds(width + _boxSize,height + _boxSize, _boxSize, _boxSize);
		ready = true;
	}

	void setVisible(bool shouldBeVisible)
	{
		Component::setVisible(shouldBeVisible);
		ready = shouldBeVisible;
	}

	bool isReady()
	{
		return ready;
	}

	void paint (Graphics& g)
	{
		if (!isComponentSelection) {
			g.fillAll (Colours::grey);
			setAlpha(0.3f);
		} else {
			g.fillAll (Colours::grey);
			setAlpha(0.2f);
		}
	}

	void mouseDrag (const MouseEvent& event)
	{
		if (event.originalComponent->getName().equalsIgnoreCase("bottomRight")) {
			Point<int> size = event.getScreenPosition() - this->getScreenPosition();
			setSelectionBounds(getX() + _boxSize, getY() + _boxSize, size.getX() - _boxSize, size.getY() - _boxSize); 
		} else if (event.originalComponent->getName().equalsIgnoreCase("bottomLeft")) {
			Point<int> size = event.getScreenPosition() - this->getScreenPosition();
			setSelectionBounds(getX() + _boxSize + size.getX(), getY() + _boxSize, getWidth() - (_boxSize * 2) - size.getX(), size.getY() - (_boxSize * 2));
		}
	}

	void setBoxSize(int newSize) {
		_boxSize = newSize;
	}

	int getBoxSize() {
		return _boxSize;
	}

private:
	ScopedPointer<Component> selectedComponent;
	int _boxSize;
	bool isComponentSelection;
	bool ready;

	class MiniBox : public Component
	{
	public:
		int _boxSize;
		MiniBox(String _name) : Component(_name) {
			_boxSize = 6;
			setSize(_boxSize, _boxSize);
		}

		void paint (Graphics& g) {
			g.fillAll (Colours::black);
		}
	};

	OwnedArray<MiniBox> miniBoxes;
};