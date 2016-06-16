svr: configParser.o RelationModel.o UserModel.o net.o asynLog.o  main.o MySqlConn.o
	g++ -o svr UserModel.o RelationModel.o MySqlConn.o configParser.o net.o  main.o asynLog.o  -lpthread /usr/lib/libevent.a /usr/lib64/mysql/libmysqlclient.a -ldl

RelationModel.o:../RelationModel.cpp
	g++ -std=c++11 -g -c ../RelationModel.cpp

UserModel.o: ../UserModel.cpp
	g++ -std=c++11 -g -c ../UserModel.cpp

net.o: ../../../../common/net.cpp
	g++ -std=c++11 -g -c ../../../../common/net.cpp

MySqlConn.o: ../../../../common/MySqlConn.cpp
	g++ -std=c++11 -g -c ../../../../common/MySqlConn.cpp

configParser.o: ../../../../common/configParser.cpp
	g++  -std=c++11 -g -c ../../../../common/configParser.cpp

asynLog.o: ../../../../common/asynLog.cpp
	g++  -std=c++11 -g -c ../../../../common/asynLog.cpp

main.o: main.cpp
	g++  -std=c++11 -g -c main.cpp

clean:
	rm -rf *.o
	rm -rf core*
	rm -rf svr
	rm -rf *.log

