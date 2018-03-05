CXX 			= g++
CXXFLAGS 	= -g -Wall -std=c++11
INC_DIR 	= ../include
OBJ 			= client.o messenger.o package.o
NAME 			= client
PCT 			= prog sleep


all: ${OBJ} prog.ex sleep.ex
	${CXX} ${CXXFLAGS} -I${INC_DIR} main.cpp -o ${NAME} ${OBJ}

client.o: client.cpp client.hpp messenger.o
	${CXX} ${CXXFLAGS} -I${INC_DIR} -c client.cpp

messenger.o: ${INC_DIR}/messenger.cpp ${INC_DIR}/messenger.hpp package.o
	${CXX} ${CXXFLAGS} -c ${INC_DIR}/messenger.cpp

package.o: ${INC_DIR}/package.cpp ${INC_DIR}/package.hpp
	${CXX} ${CXXFLAGS} -c ${INC_DIR}/package.cpp

clean:
	rm -rf *.o ${NAME} *.gch ${EXEC}

prog.ex:	pct.cpp
	${CXX} pct.cpp -o prog

sleep.ex: sleep.cpp
	${CXX} ${CXXFLAGS} sleep.cpp -o sleep

psqlite.ex:
	${CXX} ${CXXFLAGS} Performance/Performance.cpp Performance/ltDriver.* Performance/ltQuery.* Performance/sqlite3.h  -o psqlite
