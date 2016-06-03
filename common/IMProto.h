#ifndef __IMPROTO_H__
#define __IMPROTO_H__

#include "net.h"
#include <event.h>
#include "../proto/IM.Base.pb.h"
#include <string>

typedef struct
{
    uint32_t length;
    uint16_t command_id;
    uint16_t punch_flag;
    uint32_t user_id;
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
        
        uint16_t GetUserID()   
        {return _imHeader.user_id;}  
        
        uint16_t GetPunch()       
        {return _imHeader.punch_flag;}  
        
        void SetLength(uint16_t len)        
        {_imHeader.length = len;}
        
        void SetCommandID(uint16_t command) 
        {_imHeader.command_id = command;}
        
        void SetUserID(uint16_t user) 
        {_imHeader.user_id = user;}
        
        void SetPunch(uint16_t punch)       
        {_imHeader.punch_flag = punch;}

        static int IsProtoValid(void * buf, int len, int * prolen);

        int InitByHeaderAddBuf(void * buf, int len);


    protected:
        ImPheader_t            _imHeader;
        std::string            _buf;
    public:
        static int             _headerlen;
};

#endif
