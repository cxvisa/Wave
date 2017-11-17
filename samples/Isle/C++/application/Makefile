ISLE_HOME := $(shell dirname `pwd`)

include ../source/Makefile.versioninfo
include ../source/Makefile.tools

# the -I and -iquote options are specified only here
CXXFLAGS += \
	-I $(SRC_ROOT) \
	-I $(WAVE_BUILD_DIR_DYNAMIC_SRC_ARCH_KIND_INDEP) \
	-I $(WAVE_HOME)/build/Wave/$(OS)/$(DYNAMIC_SRC) -I $(WAVE_HOME)/source \
	-I $(POSTGRESQL_INCLUDE_DIR) \
	-I $(OPENVSWITCH_INCLUDE_DIR) \
	-I $(WAVEOSS_INCLUDE_DIR) \
	-I $(XERCESC_INCLUDE_DIR) \
	-I $(XALANC_INCLUDE_DIR)

LIB.SO.VER := $(LIB.SO).$(VERSION_FULL)
ISLE_LIB := $(LIB.SO)
WAVE_LIB := $(WAVE_HOME)/build/Wave/$(OS)/$(ARCH)/$(BUILD_TYPE)/lib/libWave.so

LDFLAGS += -L $(WAVE_HOME)/build/Wave/$(OS)/$(ARCH)/$(BUILD_TYPE)/lib -Wl,-R$(WAVE_HOME)/build/Wave/$(OS)/$(ARCH)/$(BUILD_TYPE)/lib
LDFLAGS += -L $(BUILD_DIR_LIB) -Wl,-R$(BUILD_DIR_LIB)
LIBFILES := -lWave $(LIBFILES)

################################################################################
# common dependencies for all programs
#
# extractions are libraries not built by us but extracted - they are listed in commonMakefileEnd
#
# notice we need both the .so library file, the links, and the file linked to
# if both are there, then in fact make checks the same timestamp for both, so .so is redundant
# but if only .so is present, then we don't care about it's timestamp, only existence
# thus  .so are order-only prerequisites
################################################################################
COMMON_DEPENDENCIES := $(WAVE_LIB) $(MKFS) $(ISLE_LIB)

PROGRAMS := \
	Island.$(OS_ARCH_XT) \
	IslandClient.$(OS_ARCH_XT)


.PHONY: all clean phony
all: $(PROGRAMS)

Island.$(OS_ARCH_XT): Island.cpp
IslandClient.$(OS_ARCH_XT): IslandClient.cpp $(WAVE_HOME)/application/WaveCliReplyThread.cpp

include $(WAVE_HOME)/source/commonMakefileEnd

clean:
	rm -rf *.$(OS_ARCH_XT)

wave_clean:
	$(MAKE) -C $(WAVE_HOME)/source clean

