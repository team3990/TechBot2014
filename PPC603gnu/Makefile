# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_build main_all post_build

_clean ::
	@echo "make: removing targets and objects of `pwd`"

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

FLEXIBLE_BUILD := 1

BUILD_SPEC = PPC603gnu
DEBUG_MODE = 1
ifeq ($(DEBUG_MODE),1)
MODE_DIR := Debug
else
MODE_DIR := NonDebug
endif
OBJ_DIR := .
WS_ROOT_DIR := C:/WindRiver/workspace
PRJ_ROOT_DIR := $(WS_ROOT_DIR)/TechForKids2014



#Global Build Macros
PROJECT_TYPE = DKM
DEFINES = 
EXPAND_DBG = 0


#BuildSpec specific Build Macros
VX_CPU_FAMILY = ppc
CPU = PPC603
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
LIBPATH = 
LIBS = 

IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 

IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 

IDE_DEFINES = 



#BuildTool flags
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
DEBUGFLAGS_C++-Compiler = -g
DEBUGFLAGS_Linker = -g
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
DEBUGFLAGS_Partial-Image-Linker = 
DEBUGFLAGS_Librarian = 
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif


#Project Targets
PROJECT_TARGETS = TechForKids2014/$(MODE_DIR)/TechForKids2014.out \
	 TechForKids2014_partialImage/$(MODE_DIR)/TechForKids2014_partialImage.o


#Rules

# TechForKids2014
ifeq ($(DEBUG_MODE),1)
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
TechForKids2014/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
TechForKids2014/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
TechForKids2014/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
TechForKids2014/$(MODE_DIR)/% : IDE_DEFINES = 
TechForKids2014/$(MODE_DIR)/% : PROJECT_TYPE = DKM
TechForKids2014/$(MODE_DIR)/% : DEFINES = 
TechForKids2014/$(MODE_DIR)/% : EXPAND_DBG = 0
TechForKids2014/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
TechForKids2014/$(MODE_DIR)/% : CPU = PPC603
TechForKids2014/$(MODE_DIR)/% : TOOL_FAMILY = gnu
TechForKids2014/$(MODE_DIR)/% : TOOL = gnu
TechForKids2014/$(MODE_DIR)/% : TOOL_PATH = 
TechForKids2014/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
TechForKids2014/$(MODE_DIR)/% : LIBPATH = 
TechForKids2014/$(MODE_DIR)/% : LIBS = 
TechForKids2014/$(MODE_DIR)/% : OBJ_DIR := TechForKids2014/$(MODE_DIR)

OBJECTS_TechForKids2014 = TechForKids2014_partialImage/$(MODE_DIR)/TechForKids2014_partialImage.o

TechForKids2014/$(MODE_DIR)/TechForKids2014.out : $(OBJECTS_TechForKids2014)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@";rm -f "$@";nmppc $(OBJECTS_TechForKids2014) $(IDE_LIBRARIES) | tclsh $(WIND_BASE)/host/resource/hutils/tcl/munch.tcl -c ppc > $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Linker) $(CC_ARCH_SPEC) -fdollars-in-identifiers -Wall $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES)  -o $(OBJ_DIR)/ctdt.o -c $(OBJ_DIR)/ctdt.c; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X -T $(WIND_BASE)/target/h/tool/gnu/ldscripts/link.OUT -o "$@" $(OBJ_DIR)/ctdt.o $(OBJECTS_TechForKids2014) $(IDE_LIBRARIES) $(LIBPATH) $(LIBS)  $(ADDED_LIBPATH) $(ADDED_LIBS) && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

TechForKids2014/$(MODE_DIR)/TechForKids2014_compile_file : $(FILE) ;

_clean :: TechForKids2014/$(MODE_DIR)/TechForKids2014_clean

TechForKids2014/$(MODE_DIR)/TechForKids2014_clean : 
	$(TRACE_FLAG)if [ -d "TechForKids2014" ]; then cd "TechForKids2014"; rm -rf $(MODE_DIR); fi


# TechForKids2014_partialImage
ifeq ($(DEBUG_MODE),1)
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -g
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -g
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -g
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -g
else
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Linker = -O2 -fstrength-reduce -fno-builtin
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Partial-Image-Linker = 
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Librarian = 
TechForKids2014_partialImage/$(MODE_DIR)/% : DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
TechForKids2014_partialImage/$(MODE_DIR)/% : IDE_INCLUDES = -I$(WIND_BASE)/target/h/WPILib -I$(WIND_BASE)/target/h -I$(WIND_BASE)/target/h/wrn/coreip 
TechForKids2014_partialImage/$(MODE_DIR)/% : IDE_LIBRARIES = $(WIND_BASE)/target/lib/WPILib.a 
TechForKids2014_partialImage/$(MODE_DIR)/% : IDE_DEFINES = 
TechForKids2014_partialImage/$(MODE_DIR)/% : PROJECT_TYPE = DKM
TechForKids2014_partialImage/$(MODE_DIR)/% : DEFINES = 
TechForKids2014_partialImage/$(MODE_DIR)/% : EXPAND_DBG = 0
TechForKids2014_partialImage/$(MODE_DIR)/% : VX_CPU_FAMILY = ppc
TechForKids2014_partialImage/$(MODE_DIR)/% : CPU = PPC603
TechForKids2014_partialImage/$(MODE_DIR)/% : TOOL_FAMILY = gnu
TechForKids2014_partialImage/$(MODE_DIR)/% : TOOL = gnu
TechForKids2014_partialImage/$(MODE_DIR)/% : TOOL_PATH = 
TechForKids2014_partialImage/$(MODE_DIR)/% : CC_ARCH_SPEC = -mcpu=603 -mstrict-align -mno-implicit-fp -mlongcall
TechForKids2014_partialImage/$(MODE_DIR)/% : LIBPATH = 
TechForKids2014_partialImage/$(MODE_DIR)/% : LIBS = 
TechForKids2014_partialImage/$(MODE_DIR)/% : OBJ_DIR := TechForKids2014_partialImage/$(MODE_DIR)

TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Catcher.o : $(PRJ_ROOT_DIR)/Catcher.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/DrivingBase.o : $(PRJ_ROOT_DIR)/DrivingBase.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/GamepadXbox.o : $(PRJ_ROOT_DIR)/GamepadXbox.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/IRS.o : $(PRJ_ROOT_DIR)/IRS.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/JoystickAttack3.o : $(PRJ_ROOT_DIR)/JoystickAttack3.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Launcher.o : $(PRJ_ROOT_DIR)/Launcher.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/PIDRotation.o : $(PRJ_ROOT_DIR)/PIDRotation.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Picker.o : $(PRJ_ROOT_DIR)/Picker.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/TechBot3.o : $(PRJ_ROOT_DIR)/TechBot3.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/VisualTracking.o : $(PRJ_ROOT_DIR)/VisualTracking.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/t4kBinaryImage.o : $(PRJ_ROOT_DIR)/t4kBinaryImage.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/t4kHSLImage.o : $(PRJ_ROOT_DIR)/t4kHSLImage.cpp $(FORCE_FILE_BUILD)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -Wall  -MD -MP -mlongcall $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_WRS_KERNEL   $(DEFINES) -o "$@" -c "$<"


OBJECTS_TechForKids2014_partialImage = TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Catcher.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/DrivingBase.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/GamepadXbox.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/IRS.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/JoystickAttack3.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Launcher.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/PIDRotation.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Picker.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/TechBot3.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/VisualTracking.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/t4kBinaryImage.o \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/t4kHSLImage.o

TechForKids2014_partialImage/$(MODE_DIR)/TechForKids2014_partialImage.o : $(OBJECTS_TechForKids2014_partialImage)
	$(TRACE_FLAG)if [ ! -d "`dirname "$@"`" ]; then mkdir -p "`dirname "$@"`"; fi;echo "building $@"; $(TOOL_PATH)ccppc -r -nostdlib -Wl,-X  -o "$@" $(OBJECTS_TechForKids2014_partialImage) $(LIBPATH) $(LIBS) $(ADDED_LIBPATH) $(ADDED_LIBS)  && if [ "$(EXPAND_DBG)" = "1" ]; then plink "$@";fi

TechForKids2014_partialImage/$(MODE_DIR)/TechForKids2014_partialImage_compile_file : $(FILE) ;

_clean :: TechForKids2014_partialImage/$(MODE_DIR)/TechForKids2014_partialImage_clean

TechForKids2014_partialImage/$(MODE_DIR)/TechForKids2014_partialImage_clean : 
	$(TRACE_FLAG)if [ -d "TechForKids2014_partialImage" ]; then cd "TechForKids2014_partialImage"; rm -rf $(MODE_DIR); fi

force : 

DEP_FILES := TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Catcher.d TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/DrivingBase.d TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/GamepadXbox.d \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/IRS.d TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/JoystickAttack3.d TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Launcher.d \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/PIDRotation.d TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/Picker.d TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/TechBot3.d \
	 TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/VisualTracking.d TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/t4kBinaryImage.d TechForKids2014_partialImage/$(MODE_DIR)/Objects/TechForKids2014/t4kHSLImage.d
-include $(DEP_FILES)



-include $(PRJ_ROOT_DIR)/*.makefile

-include *.makefile

main_all : external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""
