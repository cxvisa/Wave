export SUB_DIRS := $(shell find . -type d)
export ALL_JAVA_SOURCES = $(shell find . -name "*.java")
export ALL_JAVA_CLASSES = $(patsubst %.java,../build/obj/%.class,$(ALL_JAVA_SOURCES))

export WAVEJARFILE = ../../build/lib/libWave-1.5.jar
export CLASSPATH = $(WAVEJARFILE)

export JARFILE = ../build/lib/libSpectrum-1.5.jar

.PHONY: all build package classes $(WAVEJARFILE)

build: $(WAVEJARFILE) classes
	for i in $(SUB_DIRS); \
	do \
	    echo $$i; \
	done;

LIST_OF_CLASSES_TO_BE_UPDATED :=

classes: $(ALL_JAVA_CLASSES) $(WAVEJARFILE)
	if [ ! -z "$(LIST_OF_CLASSES_TO_BE_UPDATED)" ] ; then \
		javac -Xlint:unchecked -cp $(CLASSPATH) -sourcepath $(shell pwd) -d ../build/obj -Werror $(LIST_OF_CLASSES_TO_BE_UPDATED) && \
		cd ../build/obj && jar -cvmf ../../source/MANIFEST.MF ../../source/$(JARFILE) `find . -name "*.class"`; \
	fi

$(ALL_JAVA_CLASSES) : ../build/obj/%.class : %.java
	$(eval LIST_OF_CLASSES_TO_BE_UPDATED+=$$<)

$(WAVEJARFILE):
	gmake -C ../../source

clean:
	rm -rf ../build/obj/* ../build/lib/* ../build/DynamicSource/*

runspectrum:
	#java -cp ../build/lib/libSpectrum-1.5.jar:../../build/lib/libWave-1.5.jar com.CxWave.Wave.Spectrum ..
	java -Duser.dir=`pwd` -Dfile.encoding=UTF-8 -XX:ThreadStackSize=1024k -jar ../build/lib/libSpectrum-1.5.jar ..
