test:AudioSession.o main.o
	g++ -o test AudioSession.o main.o  ../../lib/jrtplib/libjrtp.a -lasound
AudioSession.o:../../client/AudioSession.cpp
	g++ -g -c ../../client/AudioSession.cpp
main.o:main.cpp
	g++ -g -c main.cpp

clean:
	rm -rf *.o
	rm -rf test
