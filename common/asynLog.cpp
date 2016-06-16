#include "asynLog.h"


queue<std::unique_ptr<char[]>> Log :: log_buffer;
pthread_cond_t Log:: log_cond;
pthread_mutex_t Log :: log_mutex;
char Log :: buffer[LOG_MAXLINE];
int Log :: STATUS = LOG_INIT;
FILE * Log :: fp; 
int Log :: LEVEL = LOG_DEBUG;
const string Log :: str_prefix[4] = {"[DEBUG]   ", 
                                     "[NOTICE]  ",
                                     "[WARN]    ", 
                                     "[ERROR]   "};


int 
Log :: init(const char * name)
{
    //size_t path_len;
    FILE * fp;
    pthread_t write_t;    
    
    pthread_mutex_init(&log_mutex, NULL);
    pthread_cond_init(&log_cond, NULL);
    
     
    fp = fopen(name, "w+");
    if(fp != NULL)
        set_file(fp);
    else
        return -1;

    if (pthread_create(&write_t, NULL, write_log, NULL) != 0) 
    {
        return -1;
    }
    STATUS = LOG_RUN;
    return 0; 
}

void *
Log :: write_log(void *)
{
    while(STATUS == LOG_RUN)
    {
        pthread_mutex_lock(&log_mutex);
        
        while(log_buffer.empty() && STATUS == LOG_RUN)
        {
            pthread_cond_wait(&log_cond, &log_mutex);    
        }
        if(STATUS != LOG_RUN)
            return NULL;
       
        std::unique_ptr<char[]> content = std::move(log_buffer.front()); 
        log_buffer.pop();
 
        pthread_mutex_unlock(&log_mutex);
        fprintf(fp, "%s\n", content.get());
    //#ifndef WORK
        fflush(fp);
    //#endif
    }
    fflush(fp); 
    return NULL;
}

int
Log :: DEBUG(const char * fmt, ...)
{
    if (LEVEL <= LOG_DEBUG)
    {   
        va_list args;
        va_start(args, fmt);
        produce_log(LOG_DEBUG, fmt, args);
        va_end(args);

    }
    return 1; 
}
int
Log :: ERROR(const char * fmt, ...)
{
    if (LEVEL <= LOG_ERROR)
    {   
        va_list args;
        va_start(args, fmt);
        produce_log(LOG_ERROR, fmt, args);
        va_end(args);
     
    }
    return 1; 
}

int
Log :: NOTICE(const char * fmt, ...)
{
    if (LEVEL <= LOG_NOTICE)
    {   
        va_list args;
        va_start(args, fmt);
        produce_log(LOG_NOTICE, fmt, args);
        va_end(args);

    }
    return 1; 
}


int
Log :: WARN(const char * fmt, ...)
{
    if (LEVEL <= LOG_WARN)
    {   
        va_list args;
        va_start(args, fmt);
        produce_log(LOG_WARN, fmt, args);
        va_end(args);
     
    }
    return 1; 
}

int 
add_prefix(char * dest, const string &add)
{
    int n = 0;
    while(add[n] != '\0')
    {
        *dest = add[n];
        dest++;
        n++;
    }
    return n;
}

char *
ctime(char * t_time, size_t n)
{
    time_t tt;
    struct tm vtm;

    time(&tt);
    localtime_r(&tt, &vtm);
    snprintf(t_time, n, "%02d-%02d %02d:%02d:%02d",
             vtm.tm_mon + 1, vtm.tm_mday, vtm.tm_hour,
             vtm.tm_min, vtm.tm_sec);
    return t_time;
}

void
Log :: produce_log(int event, const char * fmt, va_list args)
{
    std::unique_ptr<char[]> tmp(new char[LOG_MAXLINE]);
    switch(event)
    {
        case LOG_DEBUG:
            add_prefix(tmp.get(), str_prefix[LOG_DEBUG]);
            break;
        case LOG_NOTICE:
            add_prefix(tmp.get(), str_prefix[LOG_NOTICE]);
            break;
        case LOG_WARN:
            add_prefix(tmp.get(), str_prefix[LOG_WARN]);
            break;
        case LOG_ERROR:
            add_prefix(tmp.get(), str_prefix[LOG_ERROR]);
            break;
    }

    char * valPtr = tmp.get();
    ctime(&valPtr[9], 20);
    valPtr[23] = ' '; 
    valPtr[24] = ' '; 
    vsprintf(&valPtr[25], fmt, args);

    pthread_mutex_lock(&log_mutex);
    log_buffer.push(std::move(tmp));
    if(log_buffer.size() == 1)
        pthread_cond_signal(&log_cond);
    else
        pthread_cond_broadcast(&log_cond);
    pthread_mutex_unlock(&log_mutex);
}
