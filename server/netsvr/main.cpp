#include "netReactor.h"

int main()
{
    Singleton<ConfigParser>::instance()->parser_file("./svr.conf");
    Singleton<ConfigParser>::instance()->scan();
    const Section & NetSec = Singleton<ConfigParser>::instance()->get("NetSvr");
    
    Log::init("./run.log");
    Log::set_level(1);
    Log::NOTICE("LOG INIT SUCCES");
    
    NetReactor svr(NetSec);
    svr.init();
    svr.run();

    return 0;
}
