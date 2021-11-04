#include "wasi.h"

void *__cxa_allocate_exception(size_t thrown_size)
{
    abort();
}

void __cxa_throw(void *thrown_object, void *tinfo, void (*dest)(void *))
{
    abort();
}

int pthread_attr_init(int a) { printf("pthread_attr_init"); return 0; }
int pthread_create(int a, int b, int c, int d) { printf("pthread_create"); return 0; }
int pthread_attr_destroy(int a) { printf("pthread_attr_destroy"); return 0; }
int pthread_attr_setschedpolicy(int a, int b) { printf("pthread_attr_setschedpolicy"); return 0; }
int pthread_attr_setschedparam(int a, int b) { printf("pthread_attr_setschedparam"); return 0; }
int pthread_join(int a, int b) { printf("pthread_join"); return 0; }
int pthread_mutex_init(int a, int b) { printf("pthread_mutex_init"); return 0; }
int pthread_mutex_destroy(int a) { printf("pthread_mutex_destroy"); return 0; }
int pthread_mutex_lock(int a) { printf("pthread_mutex_lock"); return 0; }
int pthread_mutex_unlock(int a) { printf("pthread_mutex_unlock"); return 0; }
int pthread_cond_init(int a, int b) { printf("pthread_cond_init"); return 0; }
int pthread_cond_destroy(int a) { printf("pthread_cond_destroy"); return 0; }
int pthread_cond_wait(int a, int b) { printf("pthread_cond_wait"); return 0; }
int pthread_cond_signal(int a) { printf("pthread_cond_signal"); return 0; }