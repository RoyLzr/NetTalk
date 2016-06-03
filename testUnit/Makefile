test: configParser.o IMProto.o net.o asynLog.o thread.o ClientSvr.o workThread.o LineTalkReactor.o ClientCmd.o AudioThread.o AudioSession.o main.o
	g++ -o test configParser.o IMProto.o net.o main.o asynLog.o thread.o ClientSvr.o workThread.o LineTalkReactor.o ClientCmd.o AudioThread.o AudioSession.o  ../lib/jrtplib/libjrtp.a -lpthread -lasound

IMProto.o:../common/IMProto.cpp
	g++ -std=c++11 -g -c ../common/IMProto.cpp

ClientCmd.o:../client/ClientCmd.cpp
	g++ -std=c++11 -g -c ../client/ClientCmd.cpp

AudioThread.o:../client/AudioThread.cpp
	g++ -std=c++11 -g -c ../client/AudioThread.cpp

AudioSession.o:../client/AudioSession.cpp
	g++ -std=c++11 -g -c ../client/AudioSession.cpp

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

