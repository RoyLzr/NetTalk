#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../common/lock.h"

using namespace std;

class WorkerThread 
{
    public:
    enum
    {
        THREADNONE,
        THREADINIT,
        THREADRUN,
        THREADSTOP,
    };

    public:
	    WorkerThread() : m_work_buff(NULL),
                         m_work_len(0),
                         m_status(THREADNONE),
                         m_lock(),
                         m_thread_id(0)
        {};

	    virtual ~WorkerThread();

	    static void* StartRoutine(void* arg);

	    virtual void Start() = 0;
	    virtual void Execute() = 0;
        
        void * GetWorkerBuff()
        {
            return m_work_buff;
        }
        
        int GetThreadId()
        {
            return m_thread_id;
        }
        
        int GetWorkerLen()
        {
            return m_work_len;
        }

        int GetStatus()
        {
            return m_status;
        }

        int Stop()
        {
            AutoLock<MLock> l(m_lock);
            m_status = THREADSTOP;
        }

        bool isStop()
        {
            AutoLock<MLock> l(m_lock);
            if(m_status == THREADSTOP)
                return true;
            return false;
        }

        int SetBuff(int size)
        {
            if(m_work_buff != NULL)
                return m_work_len;
            if(size <= 0)
                return size;
            m_work_buff = malloc(size);
            memset(m_work_buff, '\0', size);
            if(m_work_buff != NULL)
               m_work_len = size; 
            return size;
        }

    protected:

	    pthread_t		m_thread_id;
        void *          m_work_buff;
        int             m_work_len;
        int             m_status;
        MLock           m_lock;
};

#endif
