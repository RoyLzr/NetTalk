#include "../IMProto.h"



int main()
{
    ImPheader_t theader;
    theader.length =5;
    theader.command_id = 10;
    theader.punch_flag = 15;
    char * buf = (char *)malloc(100000);

    char * h = (char *)&theader;
    for(int i = 0; i < sizeof(theader); i++)
        buf[i] = *(h+i);
    for(int i=sizeof(theader); i < 100000; i++)
        buf[i] = '1';
    ImProto * imp = new ImProto();
    int res = imp->InitByHeaderAddBuf(buf, 10000);
    
    printf("%d\n", imp->GetLength());
    std::string *s = imp->GetBuffer();
    printf("%d\n", s->size());  
    std::cout << *s << std::endl;
    return 0;
}
