/*
  ==============================================================================

    CodeGenerator.h
    Created: 11 Apr 2013 5:54:23pm
    Author:  admin

  ==============================================================================
*/

#ifndef __CODEGENERATOR_H_200599A5__
#define __CODEGENERATOR_H_200599A5__

#include "Globals.h"
#include "BigTree.h"
#include "Constructor.h"

class BigTree;

class CodeGenerator
{
public:

	CodeGenerator();

	CodeGenerator(BigTree *tree);

	CodeGenerator(BigTree tree, CodeGenerator *parentCodeGenerator);

	//~CodeGenerator();

	String getCode();

	String getDefinitions();

	String getDeclarations();

	void refresh();

	String getTemplate();

	String getVarName();

	bool isContentOwner();

	bool isDeclaredAsExtended();

private:
	friend class BigTree;
	//BigTree *_tree;
	BigTree* _tree;
	String _code;
	String _definition;
	String _declaration;
	CodeGenerator *_parentCodeGenerator;

	struct _match
	{
		String pattern;
		String value;
	};

	OwnedArray<_match> _matches;

	void getKeywords();

	String replaceKeywords(String code);

	void setSpecificProperty(Identifier prop, String appliedTo = String::empty);

	OwnedArray<CodeGenerator> _childGenerators;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeGenerator)
};



#endif  // __CODEGENERATOR_H_200599A5__
