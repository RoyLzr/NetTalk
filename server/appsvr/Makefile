svr: configParser.o appConn.o IM.Base.pb.o IM.Log.pb.o IMProto.o net.o asynLog.o  thread.o appReactor.o main.o
	g++ -o svr configParser.o appConn.o IM.Log.pb.o IM.Base.pb.o IMProto.o net.o thread.o appReactor.o main.o asynLog.o  -lpthread /usr/lib/libevent.a `pkg-config --cflags --libs protobuf`

IM.Base.pb.o:../../proto/IM.Base.pb.cc
	g++ -std=c++11 -g -c ../../proto/IM.Base.pb.cc
IM.Log.pb.o:../../proto/IM.Log.pb.cc
	g++ -std=c++11 -g -c ../../proto/IM.Log.pb.cc

appConn.o:appConn.cpp
	g++ -std=c++11 -g -c appConn.cpp
IMProto.o:../../common/IMProto.cpp
	g++ -std=c++11 -g -c ../../common/IMProto.cpp

thread.o: ../../interface/thread.cpp
	g++  -std=c++11 -g -c ../../interface/thread.cpp

appReactor.o: appReactor.cpp
	g++ -std=c++11 -g -c ./appReactor.cpp

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

