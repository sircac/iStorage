
ROOTINCL = `${ROOTSYS}/bin/root-config --cflags`

# default: ${BIN}/pex.so
default: iStorage

clean:
	rm -f *.o *dict.* *.so


iStoragedict.cc: iStorage.cc iStorage.linkdef.h
	rootcint -f iStoragedict.cc -c -g ${ROOTINCL} iStorage.cc iStorage.linkdef.h

iStoragedict.o: iStoragedict.cc
	g++ -fPIC -c -g -o iStoragedict.o ${ROOTINCL} iStoragedict.cc

iStorage.o: iStorage.cc iStorage.hh
	g++ -fPIC -c -g -o iStorage.o ${ROOTINCL} iStorage.cc

iStorage: clean iStorage.o iStoragedict.o
	g++ -fPIC -shared ${ROOTINCL} -o iStorage.so iStoragedict.o iStorage.o
	rm -f *.o *dict.*
