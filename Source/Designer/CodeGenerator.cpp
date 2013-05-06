/*
  ==============================================================================

    CodeGenerator.cpp
    Created: 11 Apr 2013 5:54:23pm
    Author:  admin

  ==============================================================================
*/


#include "CodeGenerator.h"


CodeGenerator::CodeGenerator(BigTree *tree)// : _tree(tree)
{
	//_tree = *tree;
	_tree = new BigTree();
	*_tree = BigTree(*tree);
	Constructor::log("CG001 - CodeGenerator Constructor call");
	_parentCodeGenerator = nullptr;
	refresh();
}

CodeGenerator::CodeGenerator(BigTree tree, CodeGenerator *parentCodeGenerator)// : _tree(tree), _parentCodeGenerator(parentCodeGenerator)
{
	//_tree = tree;
	_tree = new BigTree();
	*_tree = tree;
	//bTree(tree);
	_parentCodeGenerator = parentCodeGenerator;
	Constructor::log("CG001 - CodeGenerator Constructor child call");
	refresh();
}

void CodeGenerator::getKeywords()
{
	Constructor *constructor = Constructor::getInstance();

	for (int i = _tree->getNumProperties();	--i >= 0;) {
		Attribute *attrib = constructor->getAttributeOf(_tree->getPropertyName(i));
		if (attrib != nullptr && attrib->valueType != ValueType::undefined) {
			if (attrib->type == AttributeType::file) {
				//If its an existing file, copy it to BinaryData folder
				//Source\BinaryData
				String filename = _tree->getProperty(_tree->getPropertyName(i)).toString();
				if (File::isAbsolutePath(filename)) {
					File resourceFile(filename);
					File destinationFile(File::addTrailingSeparator(constructor->projectPath) + "Source" + File::separatorString + "BinaryData" + File::separatorString + resourceFile.getFileName());
					//TODO: check if resourceFile and destinationFile have different content to update destinationFile
					if (!destinationFile.existsAsFile()) {
						resourceFile.copyFileTo(destinationFile);
					}
				}
			}
			_match *m = new _match;
			m->pattern = "%" + _tree->getPropertyName(i).toString() + "%";
			m->value = _tree->getProperty(_tree->getPropertyName(i)).toString();
			_matches.add(m);
			/*_match *m = new _match;
			*m = {"%" + _tree->getPropertyName(i).toString() + "%", _tree->getProperty(_tree->getPropertyName(i))};
			_matches.add(m);*/
		}
	}
}

String CodeGenerator::replaceKeywords(String code)
{
	for (int i = _matches.size(); --i >= 0;)
		code = code.replace(_matches.getUnchecked(i)->pattern, _matches.getUnchecked(i)->value);

	return code;
}

void CodeGenerator::setSpecificProperty(Identifier prop, String appliedTo)
{
	Attribute *attrib = Constructor::getInstance()->getAttributeOf(prop);
	String value = replaceKeywords("%" + attrib->name.toString() + "%");
	/*	prop = Property identifier
		value = Property value as string
		attrib = pointer to Attribute struct containing attribute.xml fields for specified property
	*/
	if (prop == Attributes::itemList) {
		StringArray itemList;
		itemList.addLines(value);
		for (int i = 0; i < itemList.size(); ++i) {
			_definition += appliedTo + "addItem(\"" + itemList[i] + "\", " + String(i + 1) + ");\n";
		}
	} else if (prop == Attributes::lookAndFeel) {
		if (value != "Inherit") {
			_definition += appliedTo + "setLookAndFeel(" + _tree->getProperty(Attributes::lookAndFeel).toString() + "::getInstance());\n";
		}
	} else if (prop == Attributes::castMouseEvents) {
		bool castMouseEvents = _tree->getProperty(Attributes::castMouseEvents);
		if (castMouseEvents) {
			_definition += appliedTo + "addMouseListener(this, false);\n";
		}
	} else if (prop == Attributes::showEditor) {
		bool showEditor = _tree->getProperty(Attributes::showEditor);
		if (showEditor) {
			_definition += appliedTo + "showEditor();\n";
		}
	} else if (prop == Attributes::normalImage) {
		String normalImage = (File::isAbsolutePath(value)) ? "ImageFileFormat::loadFrom(File::getCurrentWorkingDirectory().getChildFile(\"../../Source/BinaryData/" + File(value).getFileName() + "\"))" : "Image()";
		String overImage = (File::isAbsolutePath(_tree->getProperty(Attributes::overImage))) ? "ImageFileFormat::loadFrom(File::getCurrentWorkingDirectory().getChildFile(\"../../Source/BinaryData/" + File(_tree->getProperty(Attributes::overImage)).getFileName() + "\"))" : "Image()";
		String downImage = (File::isAbsolutePath(_tree->getProperty(Attributes::downImage))) ? "ImageFileFormat::loadFrom(File::getCurrentWorkingDirectory().getChildFile(\"../../Source/BinaryData/" + File(_tree->getProperty(Attributes::downImage)).getFileName() + "\"))" : "Image()";
		_definition += appliedTo + "setImages (false, true, true, " + normalImage + ", 0.6000f, Colour((uint8) 0, (uint8) 0, (uint8) 0, 0.0f), " + overImage + ", 1.0000f, Colour((uint8) 0, (uint8) 0, (uint8) 0, 0.0f), " + downImage + ", 1.0000f, Colour((uint8) 150, (uint8) 150, (uint8) 150, 0.3f));\n";
	}
	
	
}

void CodeGenerator::refresh()
{
	Constructor::log("CG002 - CodeGenerator refresh call");
	_childGenerators.clear();
	_code = "";

	getKeywords();
	Constructor *constructor = Constructor::getInstance();

	bool declareExtended = false;
	if (_tree->hasProperty(Attributes::declareExtended)) {
		declareExtended = _tree->getProperty(Attributes::declareExtended);
	}
	String appliedTo = "";
	if (declareExtended) {
		//get respective template and replace its keywords
		_code = getTemplate();
		_code = replaceKeywords(_code);
	} else {
		_declaration = _tree->getProperty(Attributes::className).toString() + " " + _tree->getProperty(Attributes::varName).toString() + ";\n";
		appliedTo = _tree->getProperty(Attributes::varName).toString() + ".";
	}
	//get definition code adding attributes if its syntax is specified
	for (int i = _tree->getNumProperties();	--i >= 0;) {
		Attribute *attrib = constructor->getAttributeOf(_tree->getPropertyName(i));
		if (attrib != nullptr && !attrib->syntax.isEmpty()) {
			if  (attrib->syntax == "#") {
				setSpecificProperty(attrib->name, appliedTo);
			} else {
				_definition += appliedTo + replaceKeywords(attrib->syntax) + ";\n";
			}
		}
	}

	if (!declareExtended) {
		//if parent component is a window, this component must be owned by the window
		if (_parentCodeGenerator->isContentOwner()) {
			//if parent window is not an extended DocumentWindow class, set to modify its corresponding object
			if (!_parentCodeGenerator->isDeclaredAsExtended()) {
				_definition += _parentCodeGenerator->getVarName() + ".";
			}
			//set this component as owned by the parent window
			_definition += "setContentOwned (&" + _tree->getProperty(Attributes::varName).toString() + ", false);\n";
		} else {
			//add and make visible this component into the parent component
			if (!_parentCodeGenerator->isDeclaredAsExtended()) {
				_definition += _parentCodeGenerator->getVarName() + ".";
			}
			_definition += "addAndMakeVisible(&" + _tree->getProperty(Attributes::varName).toString() + ");\n";
		}
	}

	//refresh childs
	for (int i = _tree->getNumChildren(); --i >= 0;) {
		BigTree cTree(_tree->getChild(i));
		if (cTree.isValid()) {
			_childGenerators.add(new CodeGenerator(cTree, this));
		}
	}

}

String CodeGenerator::getTemplate()
{
	Constructor::log("CG003 - CodeGenerator getTemplate call");
	if (_tree->getProperty(Attributes::objectType).toString().equalsIgnoreCase("Window")) {
		return File( Constructor::getInstance()->getTemplatesDir() + "DocumentWindow_extends.tpl").loadFileAsString();
	} else {
		return File( Constructor::getInstance()->getTemplatesDir() + "Default_extends.tpl").loadFileAsString();
	}

}

String CodeGenerator::getCode()
{
	Constructor::log("CG004 - CodeGenerator getCode() call for object " + getVarName());
	String childCode = "";
	for (int i = _childGenerators.size(); --i >= 0;) {
		childCode += _childGenerators.getUnchecked(i)->getCode();
	}
	if (isDeclaredAsExtended()) {
		Constructor::log("CG104 - getDefinitions for " + getVarName());
		_code = _code.replace("%definitions%", getDefinitions());
		Constructor::log("CG104 - getDeclarations for " + getVarName());
		_code = _code.replace("%declarations%", getDeclarations());
		Constructor::log("CG104 - done");
	}
	return childCode + _code;
}

String CodeGenerator::getDefinitions()
{
	String childDefinitions = String::empty;
	for (int i = _childGenerators.size(); --i >= 0;) {
		if (!_childGenerators.getUnchecked(i)->isDeclaredAsExtended()) {
			childDefinitions += _childGenerators.getUnchecked(i)->getDefinitions();
		} else {
			if (!isDeclaredAsExtended())
				childDefinitions += getVarName() + ".";

			if (isContentOwner()) {
				childDefinitions += "setContentOwned (&" + _childGenerators.getUnchecked(i)->getVarName().toLowerCase() + ", true);\n";
			} else {
				childDefinitions += "addAndMakeVisible(&" + _childGenerators.getUnchecked(i)->getVarName().toLowerCase() + ");\n";
			}
		}
	}

	return _definition + childDefinitions;
}

String CodeGenerator::getDeclarations()
{
	String childDeclarations = String::empty;
	for (int i = _childGenerators.size(); --i >= 0;)
		if (!_childGenerators.getUnchecked(i)->isDeclaredAsExtended()) {
			childDeclarations += _childGenerators.getUnchecked(i)->getDeclarations();
		} else {
			childDeclarations += _childGenerators.getUnchecked(i)->getVarName() + " " + _childGenerators.getUnchecked(i)->getVarName().toLowerCase() + ";";
		}

	return _declaration + childDeclarations;
}

String CodeGenerator::getVarName()
{
	jassert (_tree->isValid());
	return _tree->getProperty(Attributes::varName).toString();
}

bool CodeGenerator::isContentOwner()
{
	if (_tree->getProperty(Attributes::objectType).toString().equalsIgnoreCase("Window")) {
		return true;
	} else {
		return false;
	}
}

bool CodeGenerator::isDeclaredAsExtended()
{
	bool declareExtended = false;
	if (_tree->hasProperty(Attributes::declareExtended))
		declareExtended = _tree->getProperty(Attributes::declareExtended);

	return declareExtended;
}