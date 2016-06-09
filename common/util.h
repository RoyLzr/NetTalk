#ifndef _UTIL_
#define _UTIL_

class Uncopyable
{
    protected:
        Uncopyable() {}
        ~Uncopyable() {}

    private:
        Uncopyable(const Uncopyable &);
        Uncopyable & operator=(const Uncopyable &);
};

#endif
