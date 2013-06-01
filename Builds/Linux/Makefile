# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := ../../binaries
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := juced
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := ../../binaries
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := juced
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/LookAndFeelCustom_1844cb0b.o \
  $(OBJDIR)/FilePropertyComponent_49968eb5.o \
  $(OBJDIR)/EnumerationPropertyComponent_de55b962.o \
  $(OBJDIR)/TextWithButtonPropertyComponent_3924a22c.o \
  $(OBJDIR)/ColourPropertyComponent_cc568b65.o \
  $(OBJDIR)/Importer_c0bc8037.o \
  $(OBJDIR)/CodeGenerator_b0b491ab.o \
  $(OBJDIR)/PropertyView_4114f33f.o \
  $(OBJDIR)/PropertyGroup_e98fedef.o \
  $(OBJDIR)/Constructor_d51dfc3f.o \
  $(OBJDIR)/PlaceableComponent_6c700b41.o \
  $(OBJDIR)/BigTree_831bcf03.o \
  $(OBJDIR)/SelectionArea_1d9b98fe.o \
  $(OBJDIR)/NewProjectWizard_7d2e3c49.o \
  $(OBJDIR)/Toolbox_d7e134f8.o \
  $(OBJDIR)/juced_ToggleButton_9a7b89ff.o \
  $(OBJDIR)/juced_ImageComponent_d8ecdd3b.o \
  $(OBJDIR)/juced_Viewport_9494f4ff.o \
  $(OBJDIR)/juced_DirectShowComponent_7718928.o \
  $(OBJDIR)/juced_Component_bf4c010e.o \
  $(OBJDIR)/juced_BubbleComponent_c5efeae2.o \
  $(OBJDIR)/juced_ProgressBar_37d6d737.o \
  $(OBJDIR)/juced_ListBox_75c52b5e.o \
  $(OBJDIR)/juced_ComboBox_3f308a36.o \
  $(OBJDIR)/juced_ImageButton_55bd317e.o \
  $(OBJDIR)/juced_Slider_65f5b8ba.o \
  $(OBJDIR)/juced_TextButton_ec77b198.o \
  $(OBJDIR)/juced_Label_9acedd85.o \
  $(OBJDIR)/juced_MainComponent_33b1d5.o \
  $(OBJDIR)/juced_Window_930afc49.o \
  $(OBJDIR)/JUCE_Designer_1c26c51e.o \
  $(OBJDIR)/MainComponent_a6ffb4a5.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_opengl_c7e3506c.o \
  $(OBJDIR)/juce_video_184321c8.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking juced
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning juced
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

strip:
	@echo Stripping juced
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/LookAndFeelCustom_1844cb0b.o: ../../Source/Styles/LookAndFeelCustom.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LookAndFeelCustom.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FilePropertyComponent_49968eb5.o: ../../Source/Designer/Properties/FilePropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FilePropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/EnumerationPropertyComponent_de55b962.o: ../../Source/Designer/Properties/EnumerationPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling EnumerationPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TextWithButtonPropertyComponent_3924a22c.o: ../../Source/Designer/Properties/TextWithButtonPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TextWithButtonPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ColourPropertyComponent_cc568b65.o: ../../Source/Designer/Properties/ColourPropertyComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ColourPropertyComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Importer_c0bc8037.o: ../../Source/Designer/Importer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Importer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CodeGenerator_b0b491ab.o: ../../Source/Designer/CodeGenerator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CodeGenerator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PropertyView_4114f33f.o: ../../Source/Designer/PropertyView.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PropertyView.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PropertyGroup_e98fedef.o: ../../Source/Designer/PropertyGroup.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PropertyGroup.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Constructor_d51dfc3f.o: ../../Source/Designer/Constructor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Constructor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PlaceableComponent_6c700b41.o: ../../Source/Designer/PlaceableComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PlaceableComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BigTree_831bcf03.o: ../../Source/Designer/BigTree.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BigTree.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SelectionArea_1d9b98fe.o: ../../Source/Designer/SelectionArea.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SelectionArea.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NewProjectWizard_7d2e3c49.o: ../../Source/Designer/NewProjectWizard.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NewProjectWizard.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Toolbox_d7e134f8.o: ../../Source/Designer/Toolbox.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Toolbox.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_ToggleButton_9a7b89ff.o: ../../Source/Modules/juced_ToggleButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_ToggleButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_ImageComponent_d8ecdd3b.o: ../../Source/Modules/juced_ImageComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_ImageComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_Viewport_9494f4ff.o: ../../Source/Modules/juced_Viewport.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_Viewport.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_DirectShowComponent_7718928.o: ../../Source/Modules/juced_DirectShowComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_DirectShowComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_Component_bf4c010e.o: ../../Source/Modules/juced_Component.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_Component.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_BubbleComponent_c5efeae2.o: ../../Source/Modules/juced_BubbleComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_BubbleComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_ProgressBar_37d6d737.o: ../../Source/Modules/juced_ProgressBar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_ProgressBar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_ListBox_75c52b5e.o: ../../Source/Modules/juced_ListBox.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_ListBox.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_ComboBox_3f308a36.o: ../../Source/Modules/juced_ComboBox.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_ComboBox.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_ImageButton_55bd317e.o: ../../Source/Modules/juced_ImageButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_ImageButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_Slider_65f5b8ba.o: ../../Source/Modules/juced_Slider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_Slider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_TextButton_ec77b198.o: ../../Source/Modules/juced_TextButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_TextButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_Label_9acedd85.o: ../../Source/Modules/juced_Label.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_Label.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_MainComponent_33b1d5.o: ../../Source/Modules/juced_MainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_MainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juced_Window_930afc49.o: ../../Source/Modules/juced_Window.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juced_Window.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/JUCE_Designer_1c26c51e.o: ../../Source/JUCE_Designer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling JUCE_Designer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainComponent_a6ffb4a5.o: ../../Source/MainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_c7e3506c.o: ../../JuceLibraryCode/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_184321c8.o: ../../JuceLibraryCode/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
