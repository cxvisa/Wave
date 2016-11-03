MAKEFILE := $(lastword $(MAKEFILE_LIST))

include Makefile.tools
include Makefile.versioninfo

.PHONY: all phony

LIB.SO.VER := $(LIB.SO).$(WAVE_VERSION_MAJOR).$(WAVE_VERSION_MINOR).$(WAVE_VERSION_PATCH)

ALL_DEPS_GOALS := all $(LIB.SO.VER) $(LIB.A) sdk internalsdk

ALL_DEPS_GOALS += $(LIB.SO)

ALL_DEPS_GOALS += buildversion buildresources


# LIB.SO is the libWave.so file - defined in Makefile.tools
all: | $(LIB.SO.VER) $(LIB.SO)

################################################################################
# here put goals that dynamically generate include files for use of our .cpp files
################################################################################
WHO_GENERATES_INCLUDES := $(WAVE_RESOURCES) $(EXTRACTION)


################################################################################
# compute pre-existing (static) sources
#
# objects OBJS are relative to $(BUILD_DIR_OBJ)
################################################################################
SRCS := $(shell find . -name '*.cpp')
OBJS := $(subst ./,,$(SRCS:.cpp=.o))

DYN_OBJS := WaveResourceIds.o
DYN_OBJS += WaveVersion.o

# second expansion pass for prerequsites is needed to resolve things like $$(@D)
# these directory targets are recognized by /. suffix, 
# and are existence-only (order-only)  prerequisites for their targets
.SECONDEXPANSION:

# the strange variable name $(@D)/.
# is to avoid parallelism bugs in the recursive makes
# see the manual for explanation
$(BUILD_DIR_DYNAMIC_SRC)/WaveVersion.cpp: phony | $$($$(@D)/.)
	$(MAKE) -C Version -f Makefile.version $(@D)/.=


$(WAVE_BUILD_DIR_DYNAMIC_SRC_ARCH_KIND_INDEP)/WaveResourceIds.cpp: | \
	 $(WAVE_RESOURCES) ;

include commonMakefileEnd

clean:
	rm -rf $(HOME)/build/$(PROJECT)
	rm -rf ../resourcegenerator/WaveResourceGenerator.$(OS).$(ARCH)
	rm -rf Resources/resources

