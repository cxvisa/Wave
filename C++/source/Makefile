MAKEFILE := $(lastword $(MAKEFILE_LIST))

include Makefile.tools
include Makefile.versioninfo

.PHONY: all phony

LIB.SO.VER := $(LIB.SO).$(WAVE_VERSION_MAJOR).$(WAVE_VERSION_MINOR).$(WAVE_VERSION_PATCH)

ALL_DEPS_GOALS := all $(LIB.SO.VER) $(LIB.A)

ALL_DEPS_GOALS += $(LIB.SO)

all: | $(LIB.SO.VER) $(LIB.SO)

WHO_GENERATES_INCLUDES := $(WAVE_RESOURCES) $(EXTRACTION)

SRCS := $(shell find . -name '*.cpp')
OBJS := $(subst ./,,$(SRCS:.cpp=.o))

DYN_OBJS := WaveResourceIds.o
DYN_OBJS += WaveVersion.o

WAVE_RESOURCE_ENUMS := $(WAVE_BUILD_DIR_DYNAMIC_SRC_ARCH_KIND_INDEP)/WaveResourceIds.cpp
WAVE_VERSION        := $(BUILD_DIR_DYNAMIC_SRC)/WaveVersion.cpp

include commonMakefileEnd

clean:
	rm -rf $(HOME)/build/$(PROJECT)
	rm -rf ../resourcegenerator/WaveResourceGenerator.$(OS).$(ARCH)
	rm -rf Resources/resources

