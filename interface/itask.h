#ifndef  _ITASK_H_
#define  _ITASK_H_



class Itask
{
    public:
        virtual ~Itask()  {};
        Itask() {};
        virtual void run() = 0;
};




#endif
