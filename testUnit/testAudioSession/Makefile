test:AudioSession.o AudioThread.o thread.o main.o
	g++ -o test AudioThread.o AudioSession.o thread.o main.o  ../../lib/jrtplib/libjrtp.a -lasound -lpthread
AudioSession.o:../../client/AudioSession.cpp
	g++ -g -c ../../client/AudioSession.cpp

thread.o:../../interface/thread.cpp
	g++ -g -c ../../interface/thread.cpp

AudioThread.o:../../client/AudioThread.cpp
	g++ -g -c ../../client/AudioThread.cpp
main.o:main.cpp
	g++ -g -c main.cpp

clean:
	rm -rf *.o
	rm -rf test
