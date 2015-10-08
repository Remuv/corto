/* cx_method.c
 *
 * This file contains the implementation for the generated interface.
 *
 * Don't mess with the begin and end tags, since these will ensure that modified
 * code in interface functions isn't replaced when code is re-generated.
 */

#include "cx.h"

/* ::corto::lang::method::bind() */
cx_int16 _cx_method_bind(cx_method this) {
/* $begin(::corto::lang::method::bind) */
    
    /* Bind function */
    if (cx_function_bind(cx_function(this))) {
        goto error;
    }

    return 0;
error:
    return -1;
/* $end */
}

/* ::corto::lang::method::init() */
cx_int16 _cx_method_init(cx_method this) {
/* $begin(::corto::lang::method::init) */
    cx_object parent;
    
    /* Locate parent class object */
    parent = cx_parentof(this);

    /* Parent of method must be an interface type */
    if (cx_class_instanceof(cx_interface_o, parent)) {
        if (cx_interface_bindMethod(cx_interface(parent), this)) {
            goto error;
        }
    }

    return cx_function_init(cx_function(this));
error:
    return -1;
/* $end */
}
