export SUB_DIRS := $(shell find . -type d)
export ALL_JAVA_SOURCES = $(shell find . -name "*.java")
export ALL_JAVA_CLASSES = $(patsubst %.java,../build/obj/%.class,$(ALL_JAVA_SOURCES))

export WAVEJARFILE = ../../build/lib/libWave-1.5.jar
export CLASSPATH = $(WAVEJARFILE)

export JVM_MEMORY_OPTIONS = -Xmx100m -Xss228k -XX:MaxMetaspaceSize=50m

export JARFILE = ../build/lib/libSpectrum-1.5.jar

export LD_LIBRARY_PATH += .

.PHONY: all build package classes $(WAVEJARFILE)

build: $(WAVEJARFILE) classes
	for i in $(SUB_DIRS); \
	do \
	    echo $$i; \
	done;

LIST_OF_CLASSES_TO_BE_UPDATED :=

classes: $(ALL_JAVA_CLASSES) $(WAVEJARFILE)
	if [ ! -z "$(LIST_OF_CLASSES_TO_BE_UPDATED)" ] ; then \
		javac -Xlint:unchecked -cp $(CLASSPATH) -sourcepath $(shell pwd) -d ../build/obj -Werror -g $(LIST_OF_CLASSES_TO_BE_UPDATED) && \
		cd ../build/obj && jar -cvmf ../../source/MANIFEST.MF ../../source/$(JARFILE) `find . -name "*.class"`; \
	fi

$(ALL_JAVA_CLASSES) : ../build/obj/%.class : %.java
	$(eval LIST_OF_CLASSES_TO_BE_UPDATED+=$$<)

$(WAVEJARFILE):
	gmake -C ../../source

clean:
	rm -rf ../build/obj/* ../build/lib/* ../build/DynamicSource/*

cleanall: clean
	gmake -C ../../source clean

runspectrum:
	#java -cp ../../build/lib/libSpectrum-1.5.jar:../../../build/lib/libWave-1.5.jar com.CxWave.Wave.Spectrum ../..
	java -Duser.dir=`pwd` -Dfile.encoding=UTF-8 $(JVM_MEMORY_OPTIONS) -jar ../../build/lib/libSpectrum-1.5.jar ../.. SpectrumConfiguration.xml

hspectrum:
	#java -cp ../../build/lib/libSpectrum-1.5.jar:../../../build/lib/libWave-1.5.jar com.CxWave.Wave.Spectrum ../..
	javah  ../../build/obj/

jdbspectrum:
	jdb -Duser.dir=`pwd` -Dfile.encoding=UTF-8 $(JVM_MEMORY_OPTIONS) -sourcepath ../../source:../../../source -classpath ../../build/obj:../../../build/obj com.CxWave.Wave.Spectrum ../.. SpectrumConfiguration.xml

debugspectrum:
	java -agentlib:jdwp=transport=dt_socket,address=3333,server=y,suspend=y -Duser.dir=`pwd` -Dfile.encoding=UTF-8 $(JVM_MEMORY_OPTIONS) -jar ../../build/lib/libSpectrum-1.5.jar ../.. SpectrumConfiguration.xml
