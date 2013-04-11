/*
  ==============================================================================

    SelectionArea.cpp
    Created: 3 Mar 2013 2:25:17pm
    Author:  admin

  ==============================================================================
*/

#include "SelectionArea.h"

SelectionArea::SelectionArea() : Component("Selection")
{
	isComponentSelection = false;
	ready = false;
	setListenToChanges(false);
	setAllowTransform(true);
}

SelectionArea::SelectionArea(bool _isComponentSelection) : Component("Selection") {
	isComponentSelection = _isComponentSelection;
	setListenToChanges(_isComponentSelection);
	setBoxSize(6);
	if (isComponentSelection) {
		/*MiniBox *box = new MiniBox("upperLeft");
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
		miniBoxes.add(box);*/

		MiniBox *box = new MiniBox("bottomRight");
		addAndMakeVisible(box);
		box->addMouseListener(this, false);
		box->setMouseCursor(MouseCursor::BottomRightCornerResizeCursor);
		miniBoxes.add(box);
	}
	setAllowTransform(true);
	ready = false;
}

SelectionArea::~SelectionArea()
{
	if (isComponentSelection) {
		for (int i = miniBoxes.size(); --i >= 0;) {
			miniBoxes[i]->removeMouseListener(this);
		}
	}
	miniBoxes.clear(true);
}

void SelectionArea::setSelectionBounds(int x, int y, int width, int height, bool isModX, bool isModY, bool isModWidth, bool isModHeight)
{
	if (_allowTransform) {
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
			miniBoxes[0]->setBounds(getWidth() - _boxSize, getHeight() - _boxSize, _boxSize, _boxSize);
			ready = true;
		}
	}
}

void SelectionArea::setVisible(bool shouldBeVisible)
{
	Component::setVisible(shouldBeVisible);
	ready = shouldBeVisible;
}

bool SelectionArea::isReady()
{
	return ready;
}

void SelectionArea::paint (Graphics& g)
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

void SelectionArea::mouseDrag (const MouseEvent& event)
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

void SelectionArea::setBoxSize(int newSize) {
	_boxSize = newSize;
}

int SelectionArea::getBoxSize() {
	return _boxSize;
}

void SelectionArea::componentMovedOrResized (Component &component, bool wasMoved, bool wasResized)
{
	if (isVisible() && isListeningToChanges()) {
		if (wasMoved || wasResized) {
			Point<int> pos = component.getScreenPosition() - Constructor::getInstance()->getDesigner()->getScreenPosition();

			setSelectionBounds(pos.getX(), pos.getY(), component.getWidth(), component.getHeight());

		}
	}
}

void SelectionArea::setListenToChanges(bool shouldBeListeningToChanges)
{
	_isListeningToChanges = shouldBeListeningToChanges;
}

bool SelectionArea::isListeningToChanges()
{
	return _isListeningToChanges;
}

void SelectionArea::setAllowTransform(bool shouldBeAllowedToTransform)
{
	_allowTransform = shouldBeAllowedToTransform;
	if (isComponentSelection) {
		for (int i = miniBoxes.size(); --i >= 0;) {
			miniBoxes[i]->setVisible(shouldBeAllowedToTransform);
		}
	}
	setListenToChanges(shouldBeAllowedToTransform);
}

//================================================

SelectionArea::MiniBox::MiniBox(String _name) : Component(_name) {
	_boxSize = 6;
	setSize(_boxSize, _boxSize);
}

void SelectionArea::MiniBox::paint (Graphics& g) {
	//setAlpha(0.5f);
	g.fillAll (Colours::black);
	g.setColour(Colours::white);
	g.fillRect(1.0f, 1.0f, (float) (_boxSize - 2), (float) (_boxSize - 2));
}
