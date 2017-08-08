package main

import (
	"os"
	"os/signal"
	"syscall"
)

/*
extern int waveMain (int argc, char **argv);
extern void waveProcessAlarmSignal ();
*/
// #cgo CXXFLAGS: -I ../../../../C++/source
// #cgo LDFLAGS: -L /usr/local/lib -L ../../../../C++/build/Wave/Linux/x86_64/debug/lib -Wl,-R${SRCDIR}/../../../../C++/build/Wave/Linux/x86_64/debug/lib -lstdc++ -lWave -lgrpc++ -lgrpc -lprotobuf -lxerces-c -lxalan-c -lxalanMsg -lcurl -lssl -lidn -lpq -lcrypto -lpam -luuid -lpthread -lmagic -lrt -liberty -lz
// #include <stdio.h>
// #include <stdlib.h>
import "C"
import "unsafe"

func main() {
	goArguments := os.Args
	argv := []*C.char{}

	for _, goArgument := range goArguments {
	    argv = append(argv, C.CString(goArgument))
	}

	alarmChannel := make(chan os.Signal, 100000)
	signal.Notify(alarmChannel, syscall.SIGALRM)

	go processAlarmSignals(alarmChannel)

	C.waveMain(1, (**C.char)(unsafe.Pointer(&argv[0])))
}

func processAlarmSignals(alarmChannel chan os.Signal) {
    for {
        _ = <- alarmChannel
        C.waveProcessAlarmSignal();
    }
}
