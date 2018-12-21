//
//  debug.h
//  Para
//
//  Created by Eric on 2018/12/18.
//  Copyright © 2018 Eric. All rights reserved.
//

#ifndef debug_h
#define debug_h

#include <stdio.h>

void panic_spin(char* filename, int line, const char* func, const char* condition);

#define PANIC(...) panic_spin(__FILE__, __LINE__, __func__, __VA_ARGS__)

#ifdef NDEBUG
    #define ASSERT(CONDITION) ((void)0)
    #define PRINT(...) ((void)0)
#else
    #define ASSERT(CONDITION) if (!(CONDITION)) PANIC(#CONDITION);
    #define PRINT(...) printf(__VA_ARGS__)
#endif /* NDEBUG */



#endif /* debug_h */


