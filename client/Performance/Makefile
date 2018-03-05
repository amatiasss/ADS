CXX 			= g++
CC				= gcc
CXXFLAGS 	= -std=c++11
LIB 			= -lpthread -ldl
OBJ 			= ltDriver.o ltQuery.o sqlite3.o
NAME 			= psqlite


all: sqlite3.o ltDriver.o ltQuery.o
	${CXX} ${CXXFLAGS} Performance.cpp ${OBJ} -o ${NAME} ${LIB}

ltDriver.o: ltDriver.cpp
	${CXX} ${CXXFLAGS} -o $@ -c $^

ltQuery.o: ltQuery.cpp
	${CXX} ${CXXFLAGS} -o $@ -c $^

sqlite: sqlite3.c shell.c
	${CC} -o $@ $^ ${LIB}

sqlite3.o: sqlite3.c
	${CC} -o $@ -c $^
