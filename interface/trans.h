#ifndef   __TRANS_H_
#define   __TRANS_H_

class Trans
{
    public:
        Trans();
        virtual ~Trans();

        virtual void * Build() = 0;

        virtual void * Send(void * data, int len) = 0;
        
        virtual void * Recv(void * data, int len) = 0;

        virtual void * Bye() = 0;



        virtual void * setIP(const string &);

        virtual void * setTarPort(int );

        virtual void * setOwnPort(int);

};


#endif
