#include <stdlib.h>
#include <stdio.h>
#include "thread.h"

WorkerThread::~WorkerThread()
{
    if(m_work_buff != NULL)
    {
        free(m_work_buff);
        m_work_buff = NULL;
    }
}

void* WorkerThread::StartRoutine(void* arg)
{
	WorkerThread* pThread = (WorkerThread*)arg;
    
    pThread->Execute();

    exit(0);
	return NULL;
}

