/*
  ==============================================================================

    BigTree.cpp
    Created: 11 Mar 2013 8:38:49am
    Author:  admin

  ==============================================================================
*/



#include "BigTree.h"

BigTree::BigTree() : ValueTree()
{

}

BigTree::BigTree(const ValueTree &other) : ValueTree(other)
{

}

BigTree::BigTree(DynamicObject *object, var _type) : ValueTree(_type.toString()) {
	getDynamicObjectProperties(object);
	addListener(this);
}

BigTree::BigTree(DynamicObject *object) : ValueTree(Modules::Unknown.toString())
{
	getDynamicObjectProperties(object);
	addListener(this);
}

BigTree::~BigTree()
{
	//removeAllProperties(0);
}

void BigTree::valueTreePropertyChanged (ValueTree &treeWhosePropertyHasChanged, const Identifier &property)
{
	//Deal with changes on this ValueTree only, not their childs.
	if (treeWhosePropertyHasChanged == *this) {

		jassert (this->hasProperty(Attributes::objectType));	//Object requires: setProperty(Ids::objectType, "object named type")

		//If editing design root component's varName, update saved design file using new varName
		if (property == Attributes::varName) {
			if (getProperty(Attributes::ID) == Constructor::getInstance()->getBigTreeRoot()->getProperty(Attributes::ID)) {
				Constructor::getInstance()->updateRootVarName();
			}
		}
		/*avoid crashing if size < 0
		if (property == Attributes::height) {
			int tempHeight = getProperty(Attributes::height);
			if (tempHeight <= 0) setProperty(Attributes::height, 1, 0);
			return;
		} else if (property == Attributes::width) {
			int tempWidth = getProperty(Attributes::width);
			if (tempWidth <= 0) setProperty(Attributes::width, 1, 0);
			return;
		}*/

		//[WRONG STATEMENT] since Windows don't inherit from Component class we deal with it separately
		if (this->getProperty(Attributes::objectType) == Modules::Window) {
			juced_Window *obj = (juced_Window *)this->getProperty(Attributes::object).getDynamicObject();
			if (property == Attributes::height) {
				int height = treeWhosePropertyHasChanged.getProperty(property);
				obj->setSize(obj->getWidth(), height);
			} else if (property == Attributes::width) {
				int width = treeWhosePropertyHasChanged.getProperty(property);
				obj->setSize(width, obj->getHeight());
			} else if (property == Attributes::x) {
				int x = treeWhosePropertyHasChanged.getProperty(property);
				obj->setTopLeftPosition(x, obj->getY());
			} else if (property == Attributes::y) {
				int y = treeWhosePropertyHasChanged.getProperty(property);
				obj->setTopLeftPosition(obj->getX(), y);
			} else if (property == Attributes::name) {
				obj->setName(treeWhosePropertyHasChanged.getProperty(property).toString());
			} else if (property == Attributes::titleBarHeight) {
				int height = treeWhosePropertyHasChanged.getProperty(property);
				obj->setTitleBarHeight(height);
			} else if (property == Attributes::titleBarTextCentered) {
				bool centered = treeWhosePropertyHasChanged.getProperty(property);
				obj->setTitleBarTextCentred(centered);
			} else if (property == Attributes::titleBarButtons) {
				int buttons = treeWhosePropertyHasChanged.getProperty(property);
				bool buttonsOnLeft = treeWhosePropertyHasChanged.getProperty(Attributes::titleBarButtonsOnLeft);
				obj->setTitleBarButtonsRequired(buttons, buttonsOnLeft);
			} else if (property == Attributes::titleBarButtonsOnLeft) {
				int buttons = treeWhosePropertyHasChanged.getProperty(Attributes::titleBarButtons);
				bool buttonsOnLeft = treeWhosePropertyHasChanged.getProperty(property);
				obj->setTitleBarButtonsRequired(buttons, buttonsOnLeft);
			} else if (property == Attributes::backgroundColour) {
				Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
				obj->setColour(DocumentWindow::backgroundColourId, newColour);
			} else if (property == Attributes::lookAndFeel) {
				obj->setLookAndFeel(Constructor::getInstance()->getNamedLookAndFeel(treeWhosePropertyHasChanged.getProperty(property).toString()));
			} else if (property == Attributes::usingNativeTitleBar) {
				bool usingNativeTitleBar = treeWhosePropertyHasChanged.getProperty(property);
				obj->setUsingNativeTitleBar(usingNativeTitleBar);
			}
		} else {
			//deal with other type of components since its not a window
			bool propertyChanged = true;
			if (this->getProperty(Attributes::objectType) == Modules::Label) {
				//deal with Label specific properties
				juced_Label *cObject = (juced_Label *)this->getProperty(Attributes::object).getDynamicObject();
				if (property == Attributes::text) {
					cObject->setText(treeWhosePropertyHasChanged.getProperty(property).toString(), false);
				} else if (property == Attributes::backgroundColour) {
					Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
					cObject->setColour(Label::backgroundColourId, newColour);
				} else if (property == Attributes::textColour) {
					Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
					cObject->setColour(Label::textColourId, newColour);
				} else if (property == Attributes::editable) {
					bool editable = getProperty(property);
					cObject->setEditable(editable);
				} else if (property == Attributes::showEditor) {
					bool showEditor = getProperty(property);
					if (showEditor) {
						cObject->showEditor();
					} else {
						cObject->hideEditor(false);
					}
				} else {
					propertyChanged = false;
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::TextButton) {
				//deal with TextButton specific properties
				juced_TextButton *cObject = (juced_TextButton *)this->getProperty(Attributes::object).getDynamicObject();
				if (property == Attributes::buttonText) {
					cObject->setButtonText(treeWhosePropertyHasChanged.getProperty(property).toString());
				} else if (property == Attributes::buttonColour) {
					Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
					cObject->setColour(TextButton::buttonColourId, newColour);
				} else if (property == Attributes::buttonOnColour) {
					Colour newColour = Colour::fromString(treeWhosePropertyHasChanged.getProperty(property).toString());
					cObject->setColour(TextButton::buttonOnColourId, newColour);
				} else if (property == Attributes::connectedEdges) {
					int value = treeWhosePropertyHasChanged.getProperty(property);
					cObject->setConnectedEdges(value);
				} else {
					propertyChanged = false;
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::Slider) {
				//deal with Slider specific properties
				juced_Slider *cObject = (juced_Slider *)this->getProperty(Attributes::object).getDynamicObject();
				bool updateTextBoxStyle = false;
				if (property == Attributes::sliderStyle) {
					if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("Rotary")) {
						cObject->setSliderStyle(Slider::Rotary);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("LinearHorizontal")) {
						cObject->setSliderStyle(Slider::LinearHorizontal);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("LinearVertical")) {
						cObject->setSliderStyle(Slider::LinearVertical);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("LinearBar")) {
						cObject->setSliderStyle(Slider::LinearBar);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("LinearBarVertical")) {
						cObject->setSliderStyle(Slider::LinearBarVertical);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("RotaryHorizontalDrag")) {
						cObject->setSliderStyle(Slider::RotaryHorizontalDrag);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("RotaryVerticalDrag")) {
						cObject->setSliderStyle(Slider::RotaryVerticalDrag);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("RotaryHorizontalVerticalDrag")) {
						cObject->setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("IncDecButtons")) {
						cObject->setSliderStyle(Slider::IncDecButtons);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("TwoValueHorizontal")) {
						cObject->setSliderStyle(Slider::TwoValueHorizontal);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("TwoValueVertical")) {
						cObject->setSliderStyle(Slider::TwoValueVertical);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("ThreeValueHorizontal")) {
						cObject->setSliderStyle(Slider::ThreeValueHorizontal);
					} else if (treeWhosePropertyHasChanged.getProperty(property).toString().equalsIgnoreCase("ThreeValueVertical")) {
						cObject->setSliderStyle(Slider::ThreeValueVertical);
					}
					
				} else if (property == Attributes::textEntryBoxPosition) {
					updateTextBoxStyle = true;
				} else if (property == Attributes::textEntryBoxWidth) {
					updateTextBoxStyle = true;
				} else if (property == Attributes::textEntryBoxHeight) {
					updateTextBoxStyle = true;
				} else if (property == Attributes::textBoxReadOnly) {
					updateTextBoxStyle = true;
				} else if (property == Attributes::minimum) {
					double minimum = getProperty(Attributes::minimum);
					double maximum = getProperty(Attributes::maximum);
					double interval = getProperty(Attributes::interval);
					cObject->setRange(minimum, maximum, interval);
				} else if (property == Attributes::maximum) {
					double minimum = getProperty(Attributes::minimum);
					double maximum = getProperty(Attributes::maximum);
					double interval = getProperty(Attributes::interval);
					cObject->setRange(minimum, maximum, interval);
				} else if (property == Attributes::interval) {
					double minimum = getProperty(Attributes::minimum);
					double maximum = getProperty(Attributes::maximum);
					double interval = getProperty(Attributes::interval);
					cObject->setRange(minimum, maximum, interval);
				} else if (property == Attributes::value) {
					double value = getProperty(Attributes::value);
					cObject->setValue(value);
				} else {
					propertyChanged = false;
				}
				if (updateTextBoxStyle) {
					int textBoxWidth = getProperty(Attributes::textEntryBoxWidth);
					int textBoxHeight = getProperty(Attributes::textEntryBoxHeight);
					bool readOnly = getProperty(Attributes::textBoxReadOnly);
					String textBoxPosition = getProperty(Attributes::textEntryBoxPosition);
					if (textBoxPosition.equalsIgnoreCase("NoTextBox")) {
						cObject->setTextBoxStyle (Slider::NoTextBox, readOnly, textBoxWidth, textBoxHeight);
					} else if (textBoxPosition.equalsIgnoreCase("TextBoxLeft")) {
						cObject->setTextBoxStyle (Slider::TextBoxLeft, readOnly, textBoxWidth, textBoxHeight);
					} else if (textBoxPosition.equalsIgnoreCase("TextBoxRight")) {
						cObject->setTextBoxStyle (Slider::TextBoxRight, readOnly, textBoxWidth, textBoxHeight);
					} else if (textBoxPosition.equalsIgnoreCase("TextBoxAbove")) {
						cObject->setTextBoxStyle (Slider::TextBoxAbove, readOnly, textBoxWidth, textBoxHeight);
					} else if (textBoxPosition.equalsIgnoreCase("TextBoxBelow")) {
						cObject->setTextBoxStyle (Slider::TextBoxBelow, readOnly, textBoxWidth, textBoxHeight);
					}
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::ImageButton) {
				//deal with TextButton specific properties
				juced_ImageButton *cObject = (juced_ImageButton *)this->getProperty(Attributes::object).getDynamicObject();
				bool updateImage = false;
				if (property == Attributes::normalImage) {
					updateImage = true;
				} else if (property == Attributes::overImage) {
					updateImage = true;
				} else if (property == Attributes::downImage) {
					updateImage = true;
				} else {
					propertyChanged = false;
				}
				if (updateImage) {
					Image normalImage = (File::isAbsolutePath(Constructor::getInstance()->getResourceFilePath(getProperty(Attributes::normalImage).toString()))) ? ImageFileFormat::loadFrom(File(Constructor::getInstance()->getResourceFilePath(getProperty(Attributes::normalImage).toString()))) : Image();
					Image overImage = (File::isAbsolutePath(Constructor::getInstance()->getResourceFilePath(getProperty(Attributes::overImage).toString()))) ? ImageFileFormat::loadFrom(File(Constructor::getInstance()->getResourceFilePath(getProperty(Attributes::overImage).toString()))) : Image();
					Image downImage = (File::isAbsolutePath(Constructor::getInstance()->getResourceFilePath(getProperty(Attributes::downImage).toString()))) ? ImageFileFormat::loadFrom(File(Constructor::getInstance()->getResourceFilePath(getProperty(Attributes::downImage).toString()))) : Image();
					cObject->setImages (false, true, true,
                          normalImage,
						  0.6000f, Colour((uint8) 0, (uint8) 0, (uint8) 0, 0.0f),
                          overImage,
						  1.0000f, Colour((uint8) 0, (uint8) 0, (uint8) 0, 0.0f),
                          downImage,
						  1.0000f, Colour((uint8) 150, (uint8) 150, (uint8) 150, 0.3f));
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::Component) {
				//deal with Component specific properties (obviously is empty)
				propertyChanged = false;
			} else if (this->getProperty(Attributes::objectType) == Modules::ComboBox) {
				//deal with ComboBox specific properties
				juced_ComboBox *cObject = dynamic_cast<juced_ComboBox *> (this->getProperty(Attributes::object).getDynamicObject());
				if (property == Attributes::itemList) {
					String strList = treeWhosePropertyHasChanged.getProperty(property);
					StringArray itemList;
					itemList.addLines(strList);
					cObject->addItemList(itemList, 1);
				} else if (property == Attributes::text) {
					cObject->setText(treeWhosePropertyHasChanged.getProperty(property).toString(), false);
				} else {
					propertyChanged = false;
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::ListBox) {
				//deal with ListBox specific properties
				juced_ListBox *cObject = dynamic_cast<juced_ListBox *> (this->getProperty(Attributes::object).getDynamicObject());
				//if (property == Attributes::itemList) {
				//	String strList = treeWhosePropertyHasChanged.getProperty(property);
				//	StringArray itemList;
				//	itemList.addLines(strList);
				//	cObject->addItemList(itemList, 1);
				//if (property == Attributes::text) {
					//cObject->setText(treeWhosePropertyHasChanged.getProperty(property).toString(), false);
				//} else {
					propertyChanged = false;
				//}
			} else if (this->getProperty(Attributes::objectType) == Modules::DirectShowComponent) {
				//deal with DirectShowComponent specific properties
				juced_DirectShowComponent *cObject = dynamic_cast<juced_DirectShowComponent *> (this->getProperty(Attributes::object).getDynamicObject());
				if (property == Attributes::movie) {
					String movieSource = treeWhosePropertyHasChanged.getProperty(property);
					//cObject->loadMovie(movieSource);
				} else {
					propertyChanged = false;
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::Viewport) {
				//deal with DirectShowComponent specific properties
				juced_Viewport *cObject = dynamic_cast<juced_Viewport *> (this->getProperty(Attributes::object).getDynamicObject());
				if (property == Attributes::scrollBarThickness) {
					int thickness = treeWhosePropertyHasChanged.getProperty(property);
					cObject->setScrollBarThickness(thickness);
				} else {
					propertyChanged = false;
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::ImageComponent) {
				//deal with DirectShowComponent specific properties
				juced_ImageComponent *cObject = dynamic_cast<juced_ImageComponent *> (this->getProperty(Attributes::object).getDynamicObject());
				if (property == Attributes::image) {
					String filePath = Constructor::getInstance()->getResourceFilePath(getProperty(property).toString());
					Image resourceImage = (filePath.isNotEmpty()) ? ImageFileFormat::loadFrom(File(filePath)) : Image();

					cObject->setImage(resourceImage);
				} else {
					propertyChanged = false;
				}
			} else if (this->getProperty(Attributes::objectType) == Modules::ToggleButton) {
				//deal with DirectShowComponent specific properties
				//juced_ToggleButton *cObject = dynamic_cast<juced_ToggleButton *> (this->getProperty(Attributes::object).getDynamicObject());
				
				propertyChanged = false;

			}
                 
			//[CUSTOM MODULES HERE]
			if (!propertyChanged) {
				//deal with common component properties
				Component *obj = dynamic_cast<Component *> (this->getProperty(Attributes::object).getDynamicObject());
				if (property == Attributes::x) {
					int value = treeWhosePropertyHasChanged.getProperty(property);
					obj->setBounds(value, obj->getY(), obj->getWidth(), obj->getHeight());
				} else if (property == Attributes::y) {
					int value = treeWhosePropertyHasChanged.getProperty(property);
					obj->setBounds(obj->getX(), value, obj->getWidth(), obj->getHeight());
				} else if (property == Attributes::width) {
					int value = treeWhosePropertyHasChanged.getProperty(property);
					obj->setBounds(obj->getX(), obj->getY(), value, obj->getHeight());
				} else if (property == Attributes::height) {
					int value = treeWhosePropertyHasChanged.getProperty(property);
					obj->setBounds(obj->getX(), obj->getY(), obj->getWidth(), value);
				} else if (property == Attributes::name) {
					obj->setName(treeWhosePropertyHasChanged.getProperty(property).toString());
				} else if (property == Attributes::lookAndFeel) {
					obj->setLookAndFeel(Constructor::getInstance()->getNamedLookAndFeel(treeWhosePropertyHasChanged.getProperty(property).toString()));
				}
			}
		}
		//Set current transaction description of UndoManager and start a new one
		Attribute *t = Constructor::getInstance()->getAttributeOf(property);
		Constructor::getInstance()->getUndoManager()->setCurrentTransactionName("Set " + t->display + " on " + getProperty(Attributes::name).toString());
		Constructor::getInstance()->getUndoManager()->beginNewTransaction();
	}
}

void BigTree::valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded)
{
	if (parentTree == childWhichHasBeenAdded) {}	//useless - to avoid warnings
}

void BigTree::valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved)
{
	if (parentTree == childWhichHasBeenRemoved) {}	//useless - to avoid warnings
}


void BigTree::valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved)
{
	if (*this == parentTreeWhoseChildrenHaveMoved) {}	//useless - to avoid warnings
}

void BigTree::valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged)
{
	if (*this == treeWhoseParentHasChanged) {}	//useless - to avoid warnings
}

void BigTree::valueTreeRedirected (ValueTree& treeWhichHasBeenChanged)
{
	if (*this == treeWhichHasBeenChanged) {}	//useless - to avoid warnings
}
	
BigTree BigTree::getChildWithProperty(const Identifier &propertyName, const var &propertyValue, bool recursive)
{
	//checking root node first
	if (hasProperty(propertyName))
		if (getProperty(propertyName) == propertyValue)
			return *this;

	BigTree bTree(ValueTree::getChildWithProperty(propertyName, propertyValue));
	if (bTree.isValid()) {
		return bTree;
	} else if (!recursive) {
		return (BigTree());
	}

	for (int i = getNumChildren(); --i >= 0;) {
		BigTree cTree(getChild(i).getChildWithProperty(propertyName, propertyValue, recursive));
		if (cTree.isValid()) {
			return cTree;
		}
	}
	return (BigTree());
}

/*
ValueTree getChildWithProperty (const Identifier& propertyName, const var& propertyValue) const
{
    for (int i = 0; i < children.size(); ++i)
    {
        SharedObject* const s = children.getObjectPointerUnchecked (i);
        if (s->getProperty (propertyName) == propertyValue)
            return ValueTree (s);
    }

    return ValueTree::invalid;
}*/

BigTree BigTree::getChild(int index) const
{
	return BigTree(ValueTree::getChild(index));
}

void BigTree::recursive_removeProperty(Identifier name, UndoManager *undoManager)
{

	removeProperty(name, undoManager);
	for (int i = getNumChildren(); --i >= 0;) {
		getChild(i).recursive_removeProperty(name, undoManager);
	}
}

void BigTree::recursive_setFilePathAsRelative(UndoManager *undoManager)
{
	DBG(("BigTree::recursive_setFilePathAsRelative()"));
	for (int i = 0; i < getNumProperties(); ++i) {
		Identifier p = getPropertyName(i);
		DBG(("parsing property: " + p.toString()));
		Attribute *attrib = Constructor::getInstance()->getAttributeOf(p);
		if (attrib != nullptr  && attrib->type == AttributeType::file) {
			String pValue = getPropertyAsValue(p, undoManager).toString();
			if (File(pValue).exists()) {
				File temp(pValue);
				String relativePath = temp.getRelativePathFrom(File(Constructor::getInstance()->getWorkingDirectory()));
				//if (pValue.contains(stringToReplace)) {
				//	setProperty(p, pValue.replace(stringToReplace, stringToInsertInstead, false), undoManager);
				//}
				if (relativePath != String::empty)
					setProperty(p, relativePath, undoManager);
			}
		}
	}
	for (int i = getNumChildren(); --i >= 0;) {
		getChild(i).recursive_setFilePathAsRelative(undoManager);
	}
}

XmlElement* BigTree::createXml()
{

	BigTree *printableTree = new BigTree(createCopy());
	printableTree->recursive_removeProperty(Attributes::object, 0);
	//printableTree->recursive_setFilePathAsRelative(0);
	ValueTree *vTree = (ValueTree *) printableTree;
	return vTree->createXml();
}

void BigTree::getDynamicObjectProperties(DynamicObject *object) {
	setProperty(Attributes::object, var(object), 0);

	NamedValueSet values = object->getProperties();
	for (int i = values.size(); --i >= 0;) {
		setProperty(values.getName(i), values.getValueAt(i), 0);
	}
		
}

void BigTree::setDynamicObject(DynamicObject *object)
{
	getDynamicObjectProperties(object);
}
