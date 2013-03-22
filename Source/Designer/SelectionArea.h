/*
  ==============================================================================

    SelectionArea.h
    Created: 21 Mar 2013 8:57:35pm
    Author:  admin

  ==============================================================================
*/

#ifndef __SELECTIONAREA_H_179C59B8__
#define __SELECTIONAREA_H_179C59B8__


#include "Globals.h"
#include "Constructor.h"

class SelectionArea : public Component,
					  public ComponentListener
{
public:
    //==============================================================================
	SelectionArea();

	SelectionArea(bool _isComponentSelection);

	~SelectionArea();

	void setSelectionBounds(int x, int y, int width, int height, bool isModX = false, bool isModY = false, bool isModWidth = false, bool isModHeight = false);

	void setVisible(bool shouldBeVisible);

	bool isReady();

	void paint (Graphics& g);

	void mouseDrag (const MouseEvent& event);

	void setBoxSize(int newSize);

	int getBoxSize();

	void componentMovedOrResized (Component &component, bool wasMoved, bool wasResized);

private:
	ScopedPointer<Component> selectedComponent;
	int _boxSize;
	bool isComponentSelection;
	bool ready;

	class MiniBox : public Component
	{
	public:
		int _boxSize;
		MiniBox(String _name);

		void paint (Graphics& g);
	};

	OwnedArray<MiniBox> miniBoxes;
};



#endif  // __SELECTIONAREA_H_179C59B8__
