#include "../client/ClientSvr.h"
#include "../client/workThread.h"




int main()
{

    ClientSvr client;
    ReadLineUserInput * tThread = new ReadLineUserInput(&client, 1024);
    client.init(NULL, tThread);
    client.run();
    sleep(1000);

}
