/* $CORTO_GENERATED
 *
 * routerimpl.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/core/core.h>

/* $header(corto/core/routerimpl/construct) */
int corto_routerimpl_countArgs(corto_object o, void *userData) {
    if (corto_instanceof(corto_route_o, o)) {
        if (corto_routerimpl(userData)->maxArgs < corto_function(o)->parameters.length) {
            corto_routerimpl(userData)->maxArgs = corto_function(o)->parameters.length;
        }
    }
    return 1;
}
/* $end */
corto_int16 _corto_routerimpl_construct(
    corto_routerimpl this)
{
/* $begin(corto/core/routerimpl/construct) */
    corto_scopeWalk(this, corto_routerimpl_countArgs, this);
    return corto_class_construct(this);
/* $end */
}

corto_void _corto_routerimpl_destruct(
    corto_routerimpl this)
{
/* $begin(corto/core/routerimpl/destruct) */

    CORTO_UNUSED(this);

/* $end */
}

corto_route _corto_routerimpl_findRoute_v(
    corto_routerimpl this,
    corto_object instance,
    corto_stringseq pattern,
    corto_any param,
    corto_any *routerData)
{
/* $begin(corto/core/routerimpl/findRoute) */
    corto_route result = NULL;
    corto_router routerBase = corto_router(corto_typeof(this));
    corto_interface interfaceType = corto_interface(corto_typeof(instance));
    corto_int32 maxMatched = -1;

    CORTO_UNUSED(instance);

    /* Walk routes */
    corto_int32 i;
    for (i = 0; i < interfaceType->methods.length; i++) {
        corto_object o = interfaceType->methods.buffer[i];
        if (corto_instanceof(corto_route_o, o)) {
            corto_int32 matched = corto_routerimpl_matchRoute(
                this, corto_route(o), pattern, param, routerData);
            if (matched > maxMatched) {
                result = corto_route(o);

                /* If request is not split up in multiple elements, there will
                 * be only one matching route. */
                if (!routerBase->elementSeparator) {
                    break;
                }
            }
        }
    }

    return result;

/* $end */
}

corto_int32 _corto_routerimpl_matchRoute_v(
    corto_routerimpl this,
    corto_route route,
    corto_stringseq pattern,
    corto_any param,
    corto_any *routerData)
{
/* $begin(corto/core/routerimpl/matchRoute) */
    corto_int32 result = -1;

    CORTO_UNUSED(this);
    CORTO_UNUSED(param);
    CORTO_UNUSED(routerData);

    if (route->elements.length == pattern.length) {
        result = 0;
        corto_int32 i;
        for (i = 0; i < pattern.length; i++) {
            char *expr = route->elements.buffer[i];
            if (expr[0] != '$') {
                if (strcmp(expr, pattern.buffer[i])) {
                    goto nomatch;
                } else {
                    result ++;
                }
            }
        }
    }

    return result;
nomatch:
    return -1;
/* $end */
}
