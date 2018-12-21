//
//  condition.c
//  Para
//
//  Created by Eric on 2018/12/18.
//  Copyright © 2018 Eric. All rights reserved.
//

#include "condition.h"
#include "debug.h"

int cond_init(condition_t* cond) {
    int ret = pthread_mutex_init(&cond->p_mutex, 0);
    ASSERT(0 == ret);
    ret = pthread_cond_init(&cond->p_cond, 0);
    ASSERT(0 == ret);
    return ret;
}

int cond_destroy(condition_t* cond) {
    int ret;
    ret = pthread_mutex_destroy(&cond->p_mutex);
    ASSERT(0 == ret);
    ret = pthread_cond_destroy(&cond->p_cond);
    ASSERT(0 == ret);
    return ret;
}

int cond_lock(condition_t* cond) {
    return pthread_mutex_lock(&cond->p_mutex);
}

int cond_unlock(condition_t* cond) {
    return pthread_mutex_unlock(&cond->p_mutex);
}

int cond_wait(condition_t* cond) {
    return pthread_cond_wait(&cond->p_cond, &cond->p_mutex);
}

int condition_timedwait(condition_t* cond, const struct timespec *ts) {
    return pthread_cond_timedwait(&cond->p_cond, &cond->p_mutex, ts);
}

int cond_signal(condition_t* cond) {
    return pthread_cond_signal(&cond->p_cond);
}

int cond_broadcast(condition_t* cond) {
    return pthread_cond_broadcast(&cond->p_cond);
}
