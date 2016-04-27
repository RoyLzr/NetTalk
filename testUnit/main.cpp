#include "../client/ClientSvr.h"
#include "../client/workThread.h"
#include "../client/LineTalkReactor.h"
#include "../client/Parser.h"




int main()
{

    ClientSvr client;
    Singleton<ConfigParser>::instance()->parser_file("./client.conf");
    Singleton<ConfigParser>::instance()->scan();
    const Section & logSec = Singleton<ConfigParser>::instance()->get("LOG");
    const Section & recSec = Singleton<ConfigParser>::instance()->get("REACTOR");

    ReadLineUserInput * tThread = new ReadLineUserInput(&client, 1024);
    SvrDataParser * svrData = new SvrDataParser();
    UserDataParser * userData = new UserDataParser();
    LineTalkReactor   * reactor   = new LineTalkReactor(svrData, userData, recSec);

    client.openLog(logSec); 
    client.init(reactor, tThread);
    client.run();
    sleep(1000);

}
