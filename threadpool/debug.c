//
//  debug.c
//  Para
//
//  Created by Eric on 2018/12/18.
//  Copyright © 2018 Eric. All rights reserved.
//

#include "debug.h"
#include <stdlib.h>

void panic_spin(char* filename, int line, const char* func, const char* condition) {
    printf("\n------- error -------\n");
    printf("filename: %s \n", filename);
    printf("line: %d \n", line);
    printf("function: %s \n", func);
    printf("condition: %s \n", condition);
    //    while(1);
    exit(-1);
}
