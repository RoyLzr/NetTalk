#include "../client/ClientSvr.h"
#include "../client/workThread.h"
#include "../client/LineTalkReactor.h"
#include "../client/Parser.h"
#include <memory>

int main()
{

    ClientSvr client;
    Singleton<ConfigParser>::instance()->parser_file("./client.conf");
    Singleton<ConfigParser>::instance()->scan();
    const Section & logSec = Singleton<ConfigParser>::instance()->get("LOG");
    const Section & recSec = Singleton<ConfigParser>::instance()->get("REACTOR");

    std::unique_ptr<WorkerThread> tThread(new ReadLineUserInput(&client, 1024));
    std::shared_ptr<DataParser> svrData(new SvrDataParser());
    std::shared_ptr<DataParser> userData(new UserDataParser());
    std::unique_ptr<IReactor> reactor(new LineTalkReactor(svrData, userData, recSec));

    client.openLog(logSec); 
    client.init(std::move(reactor), std::move(tThread));
    client.run();
    sleep(1000);

    printf("\n\nend !!!\n\n");
}
