/* $CORTO_GENERATED
 *
 * binary.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <corto/lang/lang.h>

corto_int16 _corto_binary_init(
    corto_binary this)
{
/* $begin(corto/lang/binary/init) */
    corto_primitive(this)->kind = CORTO_BINARY;
    return corto_primitive_init((corto_primitive)this);
/* $end */
}
