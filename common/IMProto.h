#ifndef _ASYN_LOG_
#define _ASYN_LOG_
#include "net.h"
#include <event.h>
#include "../proto/IM.Base.pb.h"
#include <string>

typedef struct
{
    uint32_t length;
    uint16_t command_id;
    uint16_t punch_flag;
}ImPheader_t;

class ImProto
{
    public:
        ImProto();
        virtual ~ImProto() {}
        
        std::string * GetBuffer() 
        {return &_buf;}

        ImPheader_t * GetHeader() 
        {return &_imHeader;}

        uint32_t GetLength()      
        {return _imHeader.length;}
        
        uint16_t GetCommandID()   
        {return _imHeader.command_id;}  
        
        uint16_t GetPunch()       
        {return _imHeader.punch_flag;}  
        
        void SetLength(uint16_t len)        
        {_imHeader.length = len;}
        
        void SetCommandID(uint16_t command) 
        {_imHeader.command_id = command;}
        
        void SetPunch(uint16_t punch)       
        {_imHeader.punch_flag = punch;}

        static int IsProtoValid(void * buf, int len, int * prolen);

        int InitByHeaderAddBuf(void * buf, int len);


    protected:
        ImPheader_t            _imHeader;
        std::string            _buf;
        static int             _headerlen;
};
















#endif
