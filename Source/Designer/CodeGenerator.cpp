/*
  ==============================================================================

    CodeGenerator.cpp
    Created: 11 Apr 2013 5:54:23pm
    Author:  admin

  ==============================================================================
*/

#include "Globals.h"
#include "BigTree.h"
#include "Constructor.h"
#include "CodeGenerator.h"


CodeGenerator::CodeGenerator(BigTree *tree)// : _tree(tree)
{
	_tree = *tree;
	Constructor::log("CG001 - CodeGenerator Constructor call");
	_parentCodeGenerator = nullptr;
	refresh();
}

CodeGenerator::CodeGenerator(BigTree tree, CodeGenerator *parentCodeGenerator)// : _tree(tree), _parentCodeGenerator(parentCodeGenerator)
{
	_tree = tree;
	//bTree(tree);
	_parentCodeGenerator = parentCodeGenerator;
	Constructor::log("CG001 - CodeGenerator Constructor child call");
	refresh();
}

void CodeGenerator::getKeywords()
{
	Constructor *constructor = Constructor::getInstance();

	for (int i = _tree.getNumProperties();	--i >= 0;) {
		Attribute *attrib = constructor->getAttributeOf(_tree.getPropertyName(i));
		if (attrib != nullptr && attrib->valueType != ValueType::undefined) {
			_match *m = new _match;
			m->pattern = "%" + _tree.getPropertyName(i).toString() + "%";
			m->value = _tree.getProperty(_tree.getPropertyName(i)).toString();
			_matches.add(m);
			/*_match *m = new _match;
			*m = {"%" + _tree.getPropertyName(i).toString() + "%", _tree.getProperty(_tree.getPropertyName(i))};
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

void CodeGenerator::refresh()
{
	Constructor::log("CG002 - CodeGenerator refresh call");
	_childGenerators.clear();
	_code = "";

	getKeywords();

	Constructor *constructor = Constructor::getInstance();

	bool declareExtended = false;
	if (_tree.hasProperty(Attributes::declareExtended)) {
		declareExtended = _tree.getProperty(Attributes::declareExtended);
		if (declareExtended) {
			_code = getTemplate();
			Constructor::log("CG102 - Template retrieved successfully");
			_code = replaceKeywords(_code);
			Constructor::log("CG102 - Keywords replaced successfully");
			//add attributes if its syntax is specified
			for (int i = _tree.getNumProperties();	--i >= 0;) {
				Attribute *attrib = constructor->getAttributeOf(_tree.getPropertyName(i));
				if (attrib != nullptr && !attrib->syntax.isEmpty()) {
					_definition += replaceKeywords(attrib->syntax) + ";\n";
				}
			}
			//set specific properties
			if (_tree.getProperty(Attributes::lookAndFeel).toString() != "Inherit")
				_definition += "setLookAndFeel(" + _tree.getProperty(Attributes::lookAndFeel).toString() + "::getInstance());\n";
			bool castMouseEvents = _tree.getProperty(Attributes::castMouseEvents);
			if (castMouseEvents)
				_definition += "addMouseListener(this, false);\n";
		}
	}
	if (!declareExtended) {
		//get declaration code
		_declaration = _tree.getProperty(Attributes::className).toString() + " " + _tree.getProperty(Attributes::varName).toString() + ";\n";
		//get definition code adding attributes if its syntax is specified
		for (int i = _tree.getNumProperties();	--i >= 0;) {
			Attribute *attrib = constructor->getAttributeOf(_tree.getPropertyName(i));
			if (attrib != nullptr && !attrib->syntax.isEmpty()) {
				_definition += _tree.getProperty(Attributes::varName).toString() + "." + replaceKeywords(attrib->syntax) + ";\n";
			}
		}
		//set specific properties
		if (_tree.getProperty(Attributes::lookAndFeel).toString() != "Inherit")
			_definition += _tree.getProperty(Attributes::varName).toString() + ".setLookAndFeel(" + _tree.getProperty(Attributes::lookAndFeel).toString() + "::getInstance());\n";
		bool castMouseEvents = _tree.getProperty(Attributes::castMouseEvents);
		if (castMouseEvents)
			_definition +=  _tree.getProperty(Attributes::varName).toString() + ".addMouseListener(this, false);\n";
		//if parent component is a window, this component must be owned by the window
		if (_parentCodeGenerator->isContentOwner()) {
			//if parent window is not an extended DocumentWindow class, set to modify its corresponding object
			if (!_parentCodeGenerator->isDeclaredAsExtended())
				_definition += _parentCodeGenerator->getVarName() + ".";
			//set this component as owned by the parent window
			_definition += "setContentOwned (&" + _tree.getProperty(Attributes::varName).toString() + ", true);\n";
		} else {
			//add and make visible this component into the parent component
			if (!_parentCodeGenerator->isDeclaredAsExtended())
				_definition += _parentCodeGenerator->getVarName() + ".";

			_definition += "addAndMakeVisible(&" + _tree.getProperty(Attributes::varName).toString() + ");\n";
		}
	}

	//refresh childs
	for (int i = _tree.getNumChildren(); --i >= 0;) {
		BigTree cTree(_tree.getChild(i));
		if (cTree.isValid()) {
			_childGenerators.add(new CodeGenerator(cTree, this));
		}
	}

}

String CodeGenerator::getTemplate()
{
	Constructor::log("CG003 - CodeGenerator getTemplate call");
	if (_tree.getProperty(Attributes::objectType).toString().equalsIgnoreCase("Window")) {
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
	jassert (_tree.isValid());
	return _tree.getProperty(Attributes::varName).toString();
}

bool CodeGenerator::isContentOwner()
{
	if (_tree.getProperty(Attributes::objectType).toString().equalsIgnoreCase("Window")) {
		return true;
	} else {
		return false;
	}
}

bool CodeGenerator::isDeclaredAsExtended()
{
	bool declareExtended = false;
	if (_tree.hasProperty(Attributes::declareExtended))
		declareExtended = _tree.getProperty(Attributes::declareExtended);

	return declareExtended;
}