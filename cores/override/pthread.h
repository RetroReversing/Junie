typedef int pthread_t;
typedef int pthread_mutex_t;
typedef int pthread_cond_t;
typedef int pthread_attr_t;

#define SCHED_RR 0

struct sched_param 
{
    int sched_priority;
};
