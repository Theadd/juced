/*
  ==============================================================================

    Constructor.cpp
    Created: 16 Mar 2013 4:58:15pm
    Author:  admin

  ==============================================================================
*/

#include "NewProjectWizard.cpp"
#include "Constructor.h"

// Global static pointer used to ensure a single instance of the class.
ScopedPointer<Constructor> Constructor::m_pInstance = nullptr; 

Constructor* Constructor::getInstance()
{
   if (!m_pInstance) {   // Only allow one instance of class to be generated.
      m_pInstance = new Constructor;
	  m_pInstance->setGridSize(5);
	  m_pInstance->_bigTreeRoot = new BigTree();
	  m_pInstance->setSelectedComponent(nullptr);
	  //customLookAndFeel = new LookAndFeelCustom();
   }

   return m_pInstance;
}

void Constructor::destroy()
{
	Constructor::log("C004 - Constructor::destroy() call");
	m_pInstance = nullptr;
}

Constructor::~Constructor()
{
	Constructor::log("C003 - ~Constructor() call");
	_selectedComponent = nullptr;
	Constructor::log("C103 - 1");
	
	Constructor::log("C103 - 2");
	_selectionBox = nullptr;
	Constructor::log("C103 - 3");
	_bigTreeRoot = nullptr;
	
	Constructor::log("C103 - 5");
	_enumerations.clear();
	Constructor::log("C103 - 6");
	_attributes.clear();
	Constructor::log("C103 - Clear PlaceableComponent OwnedArray");
	if (getBigTreeRoot() != nullptr)
		getBigTreeRoot()->recursive_removeProperty(Attributes::object, 0);
	_placeableComponents.clear(false);
	//if (getBigTreeRoot() != nullptr)
		//delete getBigTreeRoot();
	Constructor::log("C103 - 7");
	undoManager = nullptr;
	Constructor::log("C103 - 4");
	_designer = nullptr;
	Constructor::log("C103 - Done");
}


void Constructor::loadAttributesFromXmlFile(const File &xmlFile)
{
	Constructor::log("C001 - Load attributes from XML file: " + xmlFile.getFullPathName());
	XmlElement *xml = XmlDocument::parse(xmlFile);//->getFirstChildElement();

	//while (xml != nullptr)
	forEachXmlChildElement (*xml, e)
	{
		Attribute *t = new Attribute;
		t->name = e->getStringAttribute("name");
		t->group = e->getStringAttribute("group");
		t->visible = e->getBoolAttribute("visible");
		t->type = e->getStringAttribute("type");
		t->display = e->getStringAttribute("display");
		t->valueType = e->getStringAttribute("valueType");
		t->syntax = e->getStringAttribute("syntax");
		_attributes.add(t);

		//xml = xml->getNextElement();
	}

	delete xml;
}

void Constructor::loadEnumerationsFromXmlFile(const File &xmlFile)
{
	Constructor::log("C002 - Load enumerations from XML file: " + xmlFile.getFullPathName());
	XmlElement *xml = XmlDocument::parse(xmlFile);//->getFirstChildElement();

	//while (xml != nullptr)
	forEachXmlChildElement (*xml, xmlnode)
	{
		_Enumerations *e = new _Enumerations;
		e->name = xmlnode->getStringAttribute("name");
		e->enumerations = new Array< Enumeration* >;

		//XmlElement *child = xmlnode->getFirstChildElement();

		//(while (child != nullptr)
		forEachXmlChildElement (*xmlnode, child)
		{
			Enumeration *t = new Enumeration;
			t->name = child->getStringAttribute("name");
			t->display = child->getStringAttribute("display");
			t->value = child->getIntAttribute("value");
			e->enumerations->add(t);
			//child = child->getNextElement();
		}
		_enumerations.add(*e);
		//child = nullptr;
		//xml = xml->getNextElement();
	}

	delete xml;
}

Choices Constructor::getChoicesOf(Identifier _name)
{
	File xmlFile(_workingDirectory + "choices.xml");

	XmlElement *xml = XmlDocument::parse(xmlFile);
	Choices choices;

	forEachXmlChildElement (*xml, xmlnode)
	{
		//if we are not looking for this choices, skip
		if (!xmlnode->getStringAttribute("name").equalsIgnoreCase(_name.toString())) continue;

		forEachXmlChildElement (*xmlnode, child)
		{
			choices.names.add(child->getStringAttribute("name"));
			choices.display.add(child->getStringAttribute("display"));
			choices.values.add(child->getStringAttribute("value"));
		}
		break;
	}

	delete xml;
	return choices;
}

Attribute* Constructor::getAttributeOf(Identifier _name)
{
	for (int i = _attributes.size(); --i >= 0;)
		if (_attributes[i]->name == _name)
			return _attributes[i];

	return nullptr;
}

Array< Enumeration* >* Constructor::getEnumerationsOf(Identifier _name)
{
	for (int i = _enumerations.size(); --i >= 0;)
		if (_enumerations[i].name == _name)
			return _enumerations[i].enumerations;

	return nullptr;
}

UndoManager* Constructor::getUndoManager() {
	if (undoManager == nullptr)
		undoManager = new UndoManager();
	
	return undoManager;
}

void Constructor::setDrawBoundsMod(int x, int y, int width, int height)
{
	_drawBoundsModX = x;
	_drawBoundsModY = y;
	_drawBoundsModWidth = width;
	_drawBoundsModHeight = height;
}

int Constructor::getDrawBoundsModX()
{
	return _drawBoundsModX;
}

int Constructor::getDrawBoundsModY()
{
	return _drawBoundsModY;
}

int Constructor::getDrawBoundsModWidth()
{
	return _drawBoundsModWidth;
}

int Constructor::getDrawBoundsModHeight()
{
	return _drawBoundsModHeight;
}

void Constructor::setGridSize(int newGridSize)
{
	_gridSize = newGridSize;
}

int Constructor::getGridSize()
{
	return _gridSize;
}

Component* Constructor::getSelectedComponent()
{
	return _selectedComponent;
}

void Constructor::setSelectedComponent(Component *selectedComponent)
{
	_selectedComponent = selectedComponent;
}

SelectionArea* Constructor::getSelectionBox()
{
	if (_selectionBox == nullptr) {
		_selectionBox = new SelectionArea(true);
		_selectionBox->setAlwaysOnTop(true);
		_selectionBox->setInterceptsMouseClicks(false, true);
	}

	return _selectionBox;
}

void Constructor::log(String msg)
{
	DBG((msg));
	return;
	/*File logFile(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "designer.log");
	//Create log file if it does not exists
	if (!logFile.exists())
		logFile.create();
	//Apply format
	String::CharPointerType pointer(msg.getCharPointer());
	for (; !pointer.isDigit(); pointer++);
	int logType = (int)(pointer[0]) - 48;
	switch (logType) {
	case 0:
		msg = Time::getCurrentTime().formatted("%M:%S") + ": " + msg;
		break;
	case 1:
		msg = "\t[INFO] " + Time::getCurrentTime().formatted("%M:%S") + ": " + msg;
		break;
	case 2:
		msg = "\t[WARNING] " + Time::getCurrentTime().formatted("%M:%S") + ": " + msg;
		break;
	case 3:
		msg = "\t[ERROR] " + Time::getCurrentTime().formatted("%M:%S") + ": " + msg;
		break;
	}
	//Append msg to log file
	logFile.appendText(msg + "\n");*/
}

void Constructor::setDesigner(Component* juce_designer)
{
	_designer = juce_designer;
}

Component* Constructor::getDesigner()
{
	jassert (_designer != nullptr);
	return _designer;
}

void Constructor::setBigTreeRoot(BigTree *bigTreeRoot)
{
	//_bigTreeRoot = bigTreeRoot;
	if (bigTreeRoot != nullptr) {
		*_bigTreeRoot = BigTree(*bigTreeRoot);
		//Updating root varName (don't call updateRootVarName() here)
		rootVarName = getBigTreeRoot()->getProperty(Attributes::varName).toString();
	} else {
		_bigTreeRoot = new BigTree();
	}
}

BigTree* Constructor::getBigTreeRoot()
{
	if (_bigTreeRoot != nullptr && _bigTreeRoot->isValid())
		return _bigTreeRoot;

	return nullptr;
}

Component* Constructor::createComponent(String selectedToolName, String parentComponentID, Rectangle<int> bounds, String componentID, bool addDependencies)
{
	PlaceableComponent *newComponent = new PlaceableComponent(selectedToolName, parentComponentID, bounds, componentID);
	_placeableComponents.add(newComponent);
	getUndoManager()->perform(newComponent, "Create new " + selectedToolName);
	//getUndoManager()->setCurrentTransactionName("Create new " + selectedToolName);
	if (selectedToolName == "juced_Window" && addDependencies) {
		bounds.setX(0);
		bounds.setY(0);
		bounds.setHeight(bounds.getHeight() - (dynamic_cast<DocumentWindow*> (newComponent->getComponent()))->getTitleBarHeight());
		PlaceableComponent *childComponent = new PlaceableComponent("juced_MainComponent", newComponent->getComponent()->getComponentID(), bounds);
		_placeableComponents.add(childComponent);
		getUndoManager()->perform(childComponent);
		//(dynamic_cast<DocumentWindow*> (newComponent->getComponent()))->setContentOwned(childComponent->getComponent(), true);
	} else if (selectedToolName == "juced_Viewport" && addDependencies) {
		bounds.setX(0);
		bounds.setY(0);
		//bounds.setHeight(bounds.getHeight());
		PlaceableComponent *childComponent = new PlaceableComponent("juced_Component", newComponent->getComponent()->getComponentID(), bounds);
		_placeableComponents.add(childComponent);
		getUndoManager()->perform(childComponent);
	}
	getUndoManager()->beginNewTransaction();
	return newComponent->getComponent();
}

String Constructor::getTemplatesDir()
{
	return File::addTrailingSeparator(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "Templates");
}

LookAndFeel* Constructor::getNamedLookAndFeel(String name)
{
	Constructor::log("C005 - getNamedLookAndFeel(" + name + ")");
	if (name.equalsIgnoreCase("LookAndFeelCustom")) {
		Constructor::log("C105 - Set custom LookAndFeel");
		return static_cast<LookAndFeel*> (&customLookAndFeel);
	} else {
		return nullptr;
	}
}

void Constructor::setWorkingDirectory(String path)
{
	_workingDirectory = path;
}

String Constructor::getWorkingDirectory()
{
	return _workingDirectory;
}

void Constructor::importFromXml(File xmlFile)
{
	Importer importer(xmlFile);
}

void Constructor::resetCurrentState()
{
	log("C10? - resetCurrentState()");
	setSelectedComponent(nullptr);
	//_selectionBox = nullptr;

	//_bigTreeRoot = nullptr;

	//if (getBigTreeRoot() != nullptr)
	//	getBigTreeRoot()->recursive_removeProperty(Attributes::object, 0);
	log("C10? - resetCurrentState() clear placeable components");
	_placeableComponents.clear(false);
	log("C10? - resetCurrentState() delete undoManager");
	undoManager = nullptr;
	if (getBigTreeRoot() != nullptr) {
		Component *rootComponent = dynamic_cast<Component *> (getBigTreeRoot()->getProperty(Attributes::object).getDynamicObject());
		getDesigner()->removeChildComponent(rootComponent);
	}
	setBigTreeRoot(nullptr);
	getSelectionBox()->setVisible(false);
	log("C10? - resetCurrentState() done.");
}

bool Constructor::createNewProject()
{
	NewProjectWizard projectWizard;

	if (projectWizard.show()) {
		projectName = projectWizard.getProjectName();
		projectPath = projectWizard.getProjectPath();
		projectType = projectWizard.getProjectType();
		resourceType = projectWizard.getResourceType();
		selectedTemplate = projectWizard.getTemplate();

		File savePath(projectPath);
		//uncompress project template
		ZipFile templateZip(File(File::addTrailingSeparator(File::addTrailingSeparator(File::getCurrentWorkingDirectory().getFullPathName()) + "Templates") + selectedTemplate + ".zip"));
		templateZip.uncompressTo(savePath, true);
		Constructor::log("D103 - Uncompressed template");
		File generatedCodeFile(File::addTrailingSeparator(savePath.getFullPathName()) + "Source" + File::separatorString + "GeneratedCode.cpp");
		String code(generatedCodeFile.loadFileAsString());
		code = code.replace("%generatedCode%", "");
		generatedCodeFile.replaceWithText(code);
		Constructor::log("D103 - Replaced GeneratedCode.cpp : " + generatedCodeFile.getFullPathName() + " SIZE: " + String(code.length()));

		return true;
	}
	return false;
}

bool Constructor::openProject()
{
	File path;
	FileChooser myChooser ("Please select a project directory", File::getSpecialLocation (File::userHomeDirectory), "*.*");
	if (myChooser.browseForDirectory()) {
		path = myChooser.getResult().getFullPathName();
	} else return false;

	projectPath = path.getFullPathName();
	selectedTemplate = "Empty";
	resetCurrentState();

	File designsFolder(File::addTrailingSeparator(path.getFullPathName()) + ".juced" + File::separatorString + "designs" + File::separatorString);
	Array<File> designs;
	designsFolder.findChildFiles(designs, 6, false, "*.xml");
	if (designs.size() > 0) {
		importFromXml(designs.getFirst());
	}
	return true;
}

void Constructor::quickSave ()
{
	Constructor::log("QUICK SAVE!");
	if (getBigTreeRoot() != nullptr) {
		XmlElement *obj_xml = getBigTreeRoot()->createXml();

		//Create xml file from XmlElement
		File file = File(File::addTrailingSeparator(File::addTrailingSeparator(File::addTrailingSeparator(projectPath) + ".juced") + "designs") + getBigTreeRoot()->getProperty(Attributes::varName) + ".xml");
		file.create();
		obj_xml->writeToFile(file, "");

		delete obj_xml;

		//Generate code
		CodeGenerator codeGenerator(Constructor::getInstance()->getBigTreeRoot());
		String generatedCodeString = codeGenerator.getCode();
		File generatedCodeFile(File::addTrailingSeparator(projectPath) + "Source" + File::separatorString + "GeneratedCode.cpp");
		File templateCodeFile(File(_workingDirectory).getChildFile("Templates" + File::separatorString + selectedTemplate + File::separatorString + "Source" + File::separatorString + "GeneratedCode.cpp"));
		//templateCodeFile.copyFileTo(generatedCodeFile);
		log(templateCodeFile.getFullPathName());
		String code(templateCodeFile.loadFileAsString());
		code = code.replace("%generatedCode%", generatedCodeString);
		generatedCodeFile.replaceWithText(code);
		//main.cpp
		File mainFile(File::addTrailingSeparator(projectPath) + "Source" + File::separatorString + "Main.cpp");
		File templateMainFile(File(_workingDirectory).getChildFile("Templates" + File::separatorString + selectedTemplate + File::separatorString + "Source" + File::separatorString + "Main.cpp"));
		String mainFileCode(templateMainFile.loadFileAsString());
		mainFileCode = mainFileCode.replace("%varName%", codeGenerator.getVarName());
		mainFile.replaceWithText(mainFileCode);

		system(String("AStyle.exe -n --style=allman " + generatedCodeFile.getFullPathName()).getCharPointer());//File::addTrailingSeparator(savePath.getFullPathName()) + "Source" + File::separatorString + "GeneratedCode.cpp").getCharPointer());
		

	}
}

void Constructor::updateRootVarName ()
{
	if (rootVarName != getBigTreeRoot()->getProperty(Attributes::varName).toString()) {
		File file = File(File::addTrailingSeparator(File::addTrailingSeparator(File::addTrailingSeparator(projectPath) + ".juced") + "designs") + rootVarName + ".xml");
		if (file.existsAsFile()) {
			file.deleteFile();
			quickSave();
		}

		rootVarName = getBigTreeRoot()->getProperty(Attributes::varName).toString();
	}
}

String Constructor::setResourceFile(String path)
{
	if (File::isAbsolutePath(path)) {
		File resourceFile(path);
		if (resourceFile.existsAsFile()) {
			File destinationFile(File::addTrailingSeparator(projectPath) + "Source" + File::separatorString + "BinaryData" + File::separatorString + resourceFile.getFileName());
			if (resourceFile.copyFileTo(destinationFile)) {
				return destinationFile.getFileName();
			} else {
				return String::empty;
			}
		} else {
			return String::empty;
		}
	} else {
		return String::empty;
	}
}

String Constructor::getResourceFilePath(String filename)
{
	File resourceFile(File::addTrailingSeparator(projectPath) + "Source" + File::separatorString + "BinaryData" + File::separatorString + filename);
	if (resourceFile.existsAsFile()) {
		return resourceFile.getFullPathName();
	} else {
		return String::empty;
	}
}

ApplicationCommandManager* Constructor::getCommandManager()
{
	return &commandManager;
}