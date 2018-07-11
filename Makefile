
NAME = iStorage

ROOTINCL = `${ROOTSYS}/bin/root-config --cflags`

# default: ${BIN}/${NAME}.so
default: ${NAME}

clean:
	@echo -n " clean:            "
	rm -f *.o *.gch *.dict.* *.so

${NAME}.dict.cc: ${NAME}.cc ${NAME}.linkdef.h
	@echo -n " ${NAME}.dict.cc: "
	rootcint -f ${NAME}.dict.cc -c -g ${ROOTINCL} ${NAME}.cc ${NAME}.linkdef.h

${NAME}.dict.o: ${NAME}.dict.cc
	@echo -n " ${NAME}.dict.o:  "
	g++ -fPIC -c -g -o ${NAME}.dict.o ${ROOTINCL} ${NAME}.dict.cc

${NAME}.o: ${NAME}.cc ${NAME}.hh
	@echo -n " ${NAME}.o:       "
	g++ -fPIC -c -g -o ${NAME}.o ${ROOTINCL} ${NAME}.cc

${NAME}: clean ${NAME}.o ${NAME}.dict.o
	@echo -n " ${NAME}.so:      "
	g++ -fPIC -shared ${ROOTINCL} -o ${NAME}.so ${NAME}.dict.o ${NAME}.o
	@echo -n " clean:            "
	rm -f *.o *.gch *.dict.*
