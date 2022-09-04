//
//  condition.h
//  Para
//
//  Created by Eric on 2018/12/18.
//  Copyright © 2018 Eric. All rights reserved.
//

#ifndef condition_h
#define condition_h

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

__BEGIN_DECLS

typedef struct condition {
    pthread_mutex_t p_mutex;
    pthread_cond_t p_cond;
} condition_t;

int cond_init(condition_t*); //initial Mutex and Condition variable
int cond_destroy(condition_t*); // deallocate Mutex and Condition variable

int cond_lock(condition_t*); // acquire Mutex lock
int cond_unlock(condition_t*); //// release Mutex lock

int cond_wait(condition_t*); // wait for a condition
int condition_timedwait(condition_t*, const struct timespec *); // wait for a condition for a specified time

int cond_signal(condition_t*); // send signal to a waiting thread
int cond_broadcast(condition_t*); // send signal to all waiting thread

__END_DECLS

#endif /* condition_h */
