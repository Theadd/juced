/*
  ==============================================================================

    Toolbox.cpp
    Created: 2 Mar 2013 9:53:47pm
    Author:  admin

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"

class Toolbox   : public Component,
				  public MouseListener
{
public:
    //==============================================================================
	Toolbox(int _itemsPerRow, int _itemSize, int _itemPadding) : Component()
	{
		itemSize = _itemSize;
		itemsPerRow = _itemsPerRow;
		itemPadding = _itemPadding;
		setBounds(0, 0, itemsPerRow * itemSize, itemSize);
		//tooltipWindow = new TooltipWindow(this);
		//tooltipWindow->setBounds(0, 0, 10, 10);
	};

	void setBounds (int x, int y, int width, int height) {
		width = (width < (itemSize * itemsPerRow)) ? itemSize * itemsPerRow : width;
		height = (height < (itemSize * ((tools.size() + 1) / itemsPerRow))) ? itemSize * ((tools.size() + 1) / itemsPerRow) : height;
		//tooltipWindow->setBounds(getX(), getY(), width, height);
		//tooltipWindow->setBounds(0, 0, width - 1, height - 1);
		Component::setBounds(x, y, width, height);
		
	}

	void loadTooltips () {
		//tooltipWindow = new TooltipWindow(this);
		//tooltipWindow->setBounds(0, 0, 10, 10);
	}

	void addItem (const String& name, const String& toolTip, const char* image, int imageSize)
    {
		ImageButton *imageButton = new ImageButton(name);
		if (toolTip.isNotEmpty()) imageButton->setTooltip(toolTip);
		imageButton->setImages (false, true, true,
                          ImageCache::getFromMemory (image, imageSize), 0.6000f, Colour((uint8) 0, (uint8) 0, (uint8) 0, 0.0f),
                          Image(), 1.0000f, Colour((uint8) 0, (uint8) 0, (uint8) 0, 0.0f),
                          Image(), 1.0000f, Colour((uint8) 150, (uint8) 150, (uint8) 150, 0.3f));
        addAndMakeVisible(imageButton);
		int itemCount = tools.size() + 1;
		int y = ((itemCount - 1) / itemsPerRow) * itemSize;
		int x = (((itemCount - 1) % itemsPerRow)) * itemSize;
		imageButton->setBounds(x + itemPadding, y + itemPadding, itemSize - 2 * itemPadding, itemSize - 2 * itemPadding);
		imageButton->addMouseListener(this, false);
		tools.add(imageButton);

		//Adapt toolbox height to show all tools in it
		if (getHeight() < y + itemSize) {
			setBounds(getX(), getY(), getWidth(), y + itemSize);
		}
    }

	void paint (Graphics& g)
	{
		//g.fillAll(Colours::grey);
	}

	String* getSelectedToolName () {
		return selectedToolName;
	}

	void deselectTool () {
		String *pString = new String("");
		selectedToolName = pString;
	}

	void mouseUp (const MouseEvent &event) {
		
		if (event.mouseWasClicked()) {
			for (int i = 0; i < tools.size(); i++) {
				if (tools[i]->getScreenBounds().contains(event.getMouseDownScreenPosition())) {
					selectedToolName = new String(tools[i]->getName());
				}
			}
		}
	}


private:
	OwnedArray<ImageButton> tools;
	ScopedPointer<TooltipWindow> tooltipWindow;
	ScopedPointer<String> selectedToolName;
	int itemSize, itemPadding, itemsPerRow;
};
