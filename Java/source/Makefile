.PHONY: all build package classes doc generateresourceenums


export PROJECT_NAME := Wave
export PROJECT_VERSION := 1.5
export SUB_DIRS := $(shell find . -type d)
export ALL_JAVA_SOURCES = $(shell find . -name "*.java")
export ALL_JAVA_CLASSES = $(patsubst %.java,../build/obj/%.class,$(ALL_JAVA_SOURCES))
export BUILD_DIR = ../build
export BUILD_DIR_DYNAMIC = $(BUILD_DIR)/DynamicSource
export DOCS_DIR = ../docs

export JARFILE = ../build/lib/lib$(PROJECT_NAME)-$(PROJECT_VERSION).jar

all: build

classes : generateresourceenums
$(JARFILE) : generateresourceenums

buildresourceenums : generateresourceenums
	gmake -C com/CxWave/Wave/Resources -f Makefile.build

generateresourceenums:
	gmake -C com/CxWave/Wave/Resources -f Makefile.resources


build: buildresourceenums classes $(JARFILE)
	for i in $(SUB_DIRS); \
	do \
	    echo $$i; \
	done;

LIST_OF_CLASSES_TO_BE_UPDATED :=

classes: $(ALL_JAVA_CLASSES)
	if [ ! -z "$(LIST_OF_CLASSES_TO_BE_UPDATED)" ] ; then \
		for i in $(LIST_OF_CLASSES_TO_BE_UPDATED); \
		do \
			echo $$i; \
		done; \
		javac -Xlint:unchecked -cp $(shell pwd):../build/DynamicSource -d ../build/obj -Werror $(LIST_OF_CLASSES_TO_BE_UPDATED) && \
		cd ../build/obj && jar -cvf ../../source/$(JARFILE) `find . -name "*.class"`; \
	fi

$(ALL_JAVA_CLASSES) : ../build/obj/%.class : %.java
	$(eval LIST_OF_CLASSES_TO_BE_UPDATED += $$<)

$(JARFILE):

doc: $(ALL_JAVA_SOURCES)
	find . -name "*.java" > $(BUILD_DIR_DYNAMIC)/allJavaSourceFiles && rm -rf $(DOCS_DIR) && javadoc -d $(DOCS_DIR) @$(BUILD_DIR_DYNAMIC)/allJavaSourceFiles

clean:
	rm -rf ../build/obj/* ../build/lib/* ../build/DynamicSource/* ../build/DynamicSource/._*

