#include "workThread.h"

void ReadLineUserInput::Start()
{
    WorkerThread::SetBuff(buffSize);
    m_status = THREADRUN;
    (void)pthread_create(&m_thread_id, NULL, StartRoutine, this); 
    
}

int ReadLineUserInput::readLineOnce()
{
    int readSize = -1;

    if((readSize = read_to_ms(STDIN_FILENO,
                              m_work_buff,
                              m_work_len,
                              2000))<0)
    {
        if(errno == ETIMEDOUT)
            return 0;
        return -1;
    }
    client->extUserInput(m_work_buff, readSize);
    return 0;
}

void ReadLineUserInput::Execute()
{
    while(true)
    {
        if(isStop())
            break;
        if(readLineOnce()<0)
        {
            printf("user input read once error \n");
            std::cout << strerror(errno) << std::endl;
        }
    }
}
