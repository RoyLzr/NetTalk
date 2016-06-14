svr: configParser.o netConn.o IMProto.o net.o asynLog.o  thread.o netReactor.o main.o
	g++ -o svr configParser.o netConn.o IMProto.o net.o thread.o netReactor.o main.o asynLog.o  -lpthread /usr/lib/libevent.a


netConn.o:netConn.cpp
	g++ -std=c++11 -g -c netConn.cpp
IMProto.o:../../common/IMProto.cpp
	g++ -std=c++11 -g -c ../../common/IMProto.cpp

thread.o: ../../interface/thread.cpp
	g++  -std=c++11 -g -c ../../interface/thread.cpp

netReactor.o: netReactor.cpp
	g++ -std=c++11 -g -c ./netReactor.cpp

net.o: ../../common/net.cpp
	g++ -std=c++11 -g -c ../../common/net.cpp

configParser.o: ../../common/configParser.cpp
	g++  -std=c++11 -g -c ../../common/configParser.cpp

asynLog.o: ../../common/asynLog.cpp
	g++  -std=c++11 -g -c ../../common/asynLog.cpp

main.o: main.cpp
	g++  -std=c++11 -g -c main.cpp

clean:
	rm -rf *.o
	rm -rf core*
	rm -rf svr
	rm -rf *.log

