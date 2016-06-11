#include "IMProto.h"
int ImProto::_headerlen = sizeof(ImPheader_t);

ImProto::ImProto()
{
    _imHeader.length = 0;
    _imHeader.command_id = 0;
    _imHeader.punch_flag = 0;
    _imHeader.user_id = 0;
    _headerlen = sizeof(ImPheader_t);
}

int ImProto::IsProtoValid(void *buf,
                           int  len,
                           int  *plen)
{
    if(len < _headerlen)
        return 0;
    int buflen = ((ImPheader_t *)buf)->length;

    if(len < buflen)
        return 0;
    if(buflen <= 0)
        return -1;
    *plen = buflen;
    return 1;
}

int ImProto::InitByHeaderAddBuf(void * buf, int len)
{
    int buflen;
    int res;
    if((res=IsProtoValid(buf, len, &buflen))<=0)
    {
        return res;
    }

    ImPheader_t * head = (ImPheader_t *)buf;
    _imHeader.length = head->length;
    _imHeader.command_id = head->command_id;
    _imHeader.punch_flag = head->punch_flag; 
    _imHeader.user_id = head->user_id; 
    
    buf = (void *)((char *)buf + _headerlen);

    /*
    printf("%d  %d  %d", _imHeader.length, 
                         _imHeader.command_id, 
                         _imHeader.punch_flag);
    */

    if(buflen > 0)
        _buf.assign((char *)buf, buflen);
    
    return 1;    
} 



