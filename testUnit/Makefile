test: configParser.o net.o asynLog.o thread.o ClientSvr.o workThread.o LineTalkReactor.o main.o
	g++ -o test configParser.o net.o main.o asynLog.o thread.o ClientSvr.o workThread.o LineTalkReactor.o -lpthread

net.o: ../common/net.cpp
	g++ -std=c++11 -g -c ../common/net.cpp

configParser.o: ../common/configParser.cpp
	g++  -std=c++11 -g -c ../common/configParser.cpp

asynLog.o: ../common/asynLog.cpp
	g++  -std=c++11 -g -c ../common/asynLog.cpp

main.o: main.cpp
	g++  -std=c++11 -g -c main.cpp

thread.o: ../interface/thread.cpp
	g++  -std=c++11 -g -c ../interface/thread.cpp

ClientSvr.o: ../client/ClientSvr.cpp
	g++  -std=c++11 -g -c ../client/ClientSvr.cpp

workThread.o: ../client/workThread.cpp
	g++  -std=c++11 -g -c ../client/workThread.cpp

LineTalkReactor.o: ../client/LineTalkReactor.cpp
	g++  -std=c++11 -g -c ../client/LineTalkReactor.cpp

clean:
	rm -rf *.o
	rm -rf core*
	rm -rf test

