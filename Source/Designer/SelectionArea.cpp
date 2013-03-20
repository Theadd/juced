/*
  ==============================================================================

    SelectionArea.cpp
    Created: 3 Mar 2013 2:25:17pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "Constructor.h"

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
			box->setVisible(false);
			box->setMouseCursor(MouseCursor::TopLeftCornerResizeCursor);
			miniBoxes.add(box);

			box = new MiniBox("upperRight");
			addAndMakeVisible(box);
			box->addMouseListener(this, false);
			box->setVisible(false);
			box->setMouseCursor(MouseCursor::TopRightCornerResizeCursor);
			miniBoxes.add(box);

			box = new MiniBox("bottomLeft");
			addAndMakeVisible(box);
			box->addMouseListener(this, false);
			box->setVisible(false);
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

	void setSelectionBounds(int x, int y, int width, int height, bool isModX = false, bool isModY = false, bool isModWidth = false, bool isModHeight = false) {

		int gridSize = Constructor::getInstance()->getGridSize();

		int modX = (isModX) ? x % gridSize : 0;
		int modY = (isModY) ? y % gridSize : 0;
		int modWidth = (isModWidth) ? (x - modX + width) % gridSize : 0;
		int modHeight = (isModHeight) ? (y - modY + height) % gridSize : 0;
		Constructor::getInstance()->setDrawBoundsMod(modX, modY, modWidth, modHeight);

		if (!isComponentSelection) {
			setBounds(x - modX, y - modY, width - modWidth, height - modHeight);
		} else {
			setBounds(x - _boxSize - modX, y - _boxSize - modY, width + (_boxSize*2) - modWidth, height + (_boxSize*2) - modHeight);

			/*miniBoxes[0]->setBounds(0, 0, _boxSize, _boxSize);
			miniBoxes[1]->setBounds(width + _boxSize, 0, _boxSize, _boxSize);
			miniBoxes[2]->setBounds(0, height + _boxSize, _boxSize, _boxSize);*/
			miniBoxes[3]->setBounds(getWidth() - _boxSize, getHeight() - _boxSize, _boxSize, _boxSize);
			ready = true;
		}
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
			g.fillAll (Colours::lightblue);
			setAlpha(0.3f);
		} else {
			g.setColour(Colours::black);
			setAlpha(0.4f);
			g.drawHorizontalLine((_boxSize - 2), (float)(_boxSize - 2), ((float) getWidth()) - (float)(_boxSize - 2));
			g.drawVerticalLine((_boxSize - 2), (float)(_boxSize - 2), ((float) getHeight()) - (float)(_boxSize - 2));
			g.drawHorizontalLine(getHeight() - _boxSize + 1, (float)(_boxSize - 2), ((float) getWidth()) - (float)(_boxSize - 2));
			g.drawVerticalLine(getWidth() - _boxSize + 1, (float)(_boxSize - 2), ((float) getHeight()) - (float)(_boxSize - 2));
		}
	}

	void mouseDrag (const MouseEvent& event)
	{
		bool ctrlKeyDown = event.mods.isCtrlDown();

		if (event.originalComponent->getName().equalsIgnoreCase("bottomRight")) {
			Point<int> size = event.getScreenPosition() - this->getScreenPosition();
			setSelectionBounds(getX() + _boxSize, getY() + _boxSize, size.getX() - _boxSize, size.getY() - _boxSize, false, false, !ctrlKeyDown, !ctrlKeyDown); 
		
		}/* else if (event.originalComponent->getName().equalsIgnoreCase("bottomLeft")) {
			Point<int> size = event.getScreenPosition() - this->getScreenPosition();
			setSelectionBounds(getX() + _boxSize + size.getX(), getY() + _boxSize, getWidth() - (_boxSize * 2) - size.getX(), size.getY() - (_boxSize * 2), !ctrlKeyDown, false, false, !ctrlKeyDown);
		
		}*/
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
			//setAlpha(0.5f);
			g.fillAll (Colours::black);
			g.setColour(Colours::white);
			g.fillRect(1.0f, 1.0f, (float) (_boxSize - 2), (float) (_boxSize - 2));
		}
	};

	OwnedArray<MiniBox> miniBoxes;
};