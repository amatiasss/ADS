CXX = g++
CXXFLAGS = -g -Wall -std=c++11
LIB = -lm

main: main.cpp
	${CXX} ${CXXFLAGS} main.cpp -o test_ ${LIB}

rand: random_in.cpp
	${CXX} ${CXXFLAGS} random_in.cpp -o rand

sleep: sleep.cpp
	${CXX} ${CXXFLAGS} sleep.cpp -o sleep

clean:
		rm -rf rand sleep test_

clean-out:
		rm -f result/*.txt
