test.o: rtpAudio.o
	g++ -o test rtpAudio.o ../jrtplib/libjrtp.a -lasound
rtpAudio.o: ./rtpAudio.cpp
	g++ -g -c rtpAudio.cpp


clean:
	rm -rf *.o
	rm -rf test	
