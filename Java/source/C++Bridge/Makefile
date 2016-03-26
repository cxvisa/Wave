all: ../../build/lib/libWaveJavaToC++Bridge.so

../../build/lib/libWaveJavaToC++Bridge.so: com_CxWave_Wave_Framework_Utils_AAA_PamUtils.cpp com_CxWave_Wave_Framework_Utils_AAA_PamUtils.h
	g++ -O3 -I /usr/lib/jvm/java/include -I /usr/lib/jvm/java/include/linux -I ../../../C++/source -I ../../../C++/build/Wave/Linux/DynamicSource -c -fPIC com_CxWave_Wave_Framework_Utils_AAA_PamUtils.cpp
	g++ -I /usr/lib/jvm/java/include -I /usr/lib/jvm/java/include/linux -L ../../../C++/build/Wave/Linux/x86_64/optimized/lib -fPIC -shared -Wl,-soname,libWaveJavaToC++Bridge.so  com_CxWave_Wave_Framework_Utils_AAA_PamUtils.o -o ../../build/lib/libWaveJavaToC++Bridge.so -lpam -lWave
