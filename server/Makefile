CXX = g++
CXXFLAGS = -g -Wall -std=c++11
INC_DIR = ../include
OBJ = server.o messenger.o package.o
NAME = server


all: ${OBJ}
	${CXX} ${CXXFLAGS} -I${INC_DIR} main.cpp -o ${NAME} ${OBJ}

server.o: server.cpp server.hpp messenger.o
	${CXX} ${CXXFLAGS} -I${INC_DIR} -c server.cpp

messenger.o: ${INC_DIR}/messenger.cpp ${INC_DIR}/messenger.hpp package.o
	${CXX} ${CXXFLAGS} -c ${INC_DIR}/messenger.cpp

package.o: ${INC_DIR}/package.cpp ${INC_DIR}/package.hpp
	${CXX} ${CXXFLAGS} -c ${INC_DIR}/package.cpp

clean:
		rm -rf *.o server *.gch

clean-out:
		rm -f result/*.txt
