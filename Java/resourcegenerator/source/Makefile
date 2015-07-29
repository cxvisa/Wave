.PHONY: buildobj buildlib all

all: buildobj buildlib

buildobj:
	javac -Xlint:unchecked -cp $(shell pwd) -d ../build/obj -Werror com/CxWave/WaveResourceGenerator/*.java

buildlib: buildobj
	cd ../build/obj && jar -cvf ../lib/WaveResourceGenerator.jar com

clean:
	rm -rf ../build/obj/*
	rm -rf ../build/lib/*

generateresourceenums:
	java -cp ../build/lib/WaveResourceGenerator.jar com.CxWave.WaveResourceGenerator.WaveResourceGenerator -wavecomponents ../../source/com/CxWave/Wave/Resources/WaveComponents.xml -destination ../../build/DynamicSource -package com.CxWave.Wave.Resources.ResourceEnums

