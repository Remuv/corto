/* testjson__load.c
 *
 * This file is generated. Only insert code in appropriate places.
 */

#include "testjson.h"

/* $header() */
/* $end */

/* This function is the entrypoint for the library and * loads definitions of the 'testjson' scope */
int cortexmain(int argc, char* argv[]) {
    CX_UNUSED(argc);
    CX_UNUSED(argv);
    
    int result = testjson_load();
    
    /* $begin(cortexmain) */
    /* $end */

    return result;
}

