class %varName% : public %className%
{
public:

    %varName%() : %className%()
	{
		%definitions%
	}
	
	void mouseUp (const MouseEvent& event)
	{
		if (event.eventComponent == this)
			%className%::mouseUp(event);
	}

	void mouseDrag (const MouseEvent& event)
	{
		if (event.eventComponent == this)
			%className%::mouseDrag(event);
	}

	void mouseDoubleClick (const MouseEvent& event)
	{
		if (event.eventComponent == this)
			%className%::mouseDoubleClick(event);
	}

private:
	%declarations%
};


