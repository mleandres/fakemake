CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror -MMD
EXEC = fakemake
OBJECTS = main.o makefile.o target.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
