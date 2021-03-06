/* $CORTO_GENERATED
 *
 * AutoResumeSink.c
 *
 * Only code written between the begin and end tags will be preserved
 * when the file is regenerated.
 */

#include <include/test.h>

corto_void _test_AutoResumeSink_onDeclare(
    test_AutoResumeSink this,
    corto_eventMask event,
    corto_object object,
    corto_observer observer)
{
/* $begin(test/AutoResumeSink/onDeclare) */

    this->declared ++;

/* $end */
}

corto_void _test_AutoResumeSink_onDefine(
    test_AutoResumeSink this,
    corto_eventMask event,
    corto_object object,
    corto_observer observer)
{
/* $begin(test/AutoResumeSink/onDefine) */

    this->defined ++;

/* $end */
}

corto_void _test_AutoResumeSink_onDelete(
    test_AutoResumeSink this,
    corto_eventMask event,
    corto_object object,
    corto_observer observer)
{
/* $begin(test/AutoResumeSink/onDelete) */

    this->deleted ++;

/* $end */
}

corto_void _test_AutoResumeSink_onResume(
    test_AutoResumeSink this,
    corto_eventMask event,
    corto_object object,
    corto_observer observer)
{
/* $begin(test/AutoResumeSink/onResume) */

    this->resumed ++;

/* $end */
}

corto_void _test_AutoResumeSink_onSuspend(
    test_AutoResumeSink this,
    corto_eventMask event,
    corto_object object,
    corto_observer observer)
{
/* $begin(test/AutoResumeSink/onSuspend) */

      this->suspended ++;

/* $end */
}

corto_void _test_AutoResumeSink_onUpdate(
    test_AutoResumeSink this,
    corto_eventMask event,
    corto_object object,
    corto_observer observer)
{
/* $begin(test/AutoResumeSink/onUpdate) */

    this->updated ++;

/* $end */
}

corto_void _test_AutoResumeSink_setup(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/setup) */
    /* Register sink mount */
    corto_voidCreateChild_auto(root_o, mount);
    test_AutoResumeSinkMountCreateChild_auto(root_o, sinkMount, mount, "test/Foo", "{10, 20}");

    CORTO_DEBUG_ENABLED = 1;

    /* Setup observers */
    corto_observer_observe(test_ResumeSink_onDeclare_o, this, mount);
    corto_observer_observe(test_ResumeSink_onDefine_o, this, mount);
    corto_observer_observe(test_ResumeSink_onDelete_o, this, mount);
    corto_observer_observe(test_ResumeSink_onUpdate_o, this, mount);
    corto_observer_observe(test_ResumeSink_onResume_o, this, mount);
    corto_observer_observe(test_ResumeSink_onSuspend_o, this, mount);

/* $end */
}

corto_void _test_AutoResumeSink_tc_define(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_define) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object mount = corto_resolve(root_o, "mount");
    test_assert(mount != NULL);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = test_FooCreateChild(mount, "x", 0, 0);
    test_assert(o != NULL);
    test_assert(corto_parentof(o) == mount);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));

    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 0);

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 0);

    /* Foo constructor modifies members */
    test_assertint(o->x, 20);
    test_assertint(o->y, 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);

    /* No define notification should have been generated. An object was inserted into
     * the store, but since it was a suspended object, its lifecycle didn't
     * change. */
    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 1);

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 1);

    corto_release(mount);
    corto_release(sinkMount);

/* $end */
}

corto_void _test_AutoResumeSink_tc_defineNested1(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_defineNested1) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object parent = corto_resolve(root_o, "mount/x");
    test_assert(parent != NULL);

    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 0);

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = test_FooCreateChild(parent, "a", 0, 0);
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 0);

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 0);

    /* Foo constructor modifies members */
    test_assertint(o->x, 20);
    test_assertint(o->y, 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(parent);

    /* No define notification should have been generated. An object was inserted into
     * the store, but since it was a suspended object, its lifecycle didn't
     * change. */
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 2);

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 2);

    corto_release(sinkMount);

/* $end */
}

corto_void _test_AutoResumeSink_tc_defineNested2(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_defineNested2) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object parent = corto_resolve(root_o, "mount/x/a");
    test_assert(parent != NULL);

    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 0);

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = test_FooCreateChild(parent, "k", 0, 0);
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(this->declared, 3);
    test_assertint(this->defined, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 3);
    test_assertint(this->suspended, 0);

    test_assertint(*test_constructCalled_o, 3);
    test_assertint(*test_destructCalled_o, 0);

    /* Foo constructor modifies members */
    test_assertint(o->x, 20);
    test_assertint(o->y, 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(parent);

    /* No define notification should have been generated. An object was inserted into
     * the store, but since it was a suspended object, its lifecycle didn't
     * change. */
    test_assertint(this->declared, 3);
    test_assertint(this->defined, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->resumed, 3);
    test_assertint(this->suspended, 3);

    test_assertint(*test_constructCalled_o, 3);
    test_assertint(*test_destructCalled_o, 3);

    corto_release(sinkMount);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolve(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolve) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = corto_resolve(root_o, "mount/x");
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 0);

    /* Foo constructor modifies members */
    test_assertint(o->x, 20);
    test_assertint(o->y, 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(sinkMount);

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 1);
    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 1);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveFromMount(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveFromMount) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    corto_object mount = corto_resolve(root_o, "mount");
    test_assert(mount != NULL);

    test_Foo o = corto_resolve(mount, "x");
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 0);

    /* Foo constructor modifies members */
    test_assert(o->x == 20);
    test_assert(o->y == 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(sinkMount);
    corto_release(mount);

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 1);
    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 1);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNested1(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNested1) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = corto_resolve(root_o, "mount/x/a");
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 0);

    /* Foo constructor modifies members */
    test_assert(o->x == 20);
    test_assert(o->y == 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(sinkMount);

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 2);
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 2);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNested1FromMount(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNested1FromMount) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    corto_object mount = corto_resolve(root_o, "mount");
    test_assert(mount != NULL);

    test_Foo o = corto_resolve(mount, "x/a");
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 0);

    /* Foo constructor modifies values */
    test_assert(o->x == 20);
    test_assert(o->y == 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(sinkMount);
    corto_release(mount);

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 2);
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 2);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNested1FromObjectFromMount(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNested1FromObjectFromMount) */

    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    corto_object mount = corto_resolve(root_o, "mount");
    test_assert(mount != NULL);

    corto_object x = corto_resolve(mount, "x");
    test_assert(x != NULL);

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 0);

    test_Foo o = corto_resolve(x, "a");
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 0);

    test_assert(o->x == 20);
    test_assert(o->y == 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(x);
    corto_release(sinkMount);
    corto_release(mount);

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 2);
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 2);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNested1NotExist(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNested1NotExist) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = corto_resolve(root_o, "mount/x/notexists");
    test_assert(o == NULL);

    /* x is resumed and suspended */
    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 1);
    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 1);

    corto_release(sinkMount);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNested2(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNested2) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = corto_resolve(root_o, "mount/x/a/k");
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(*test_constructCalled_o, 3);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 3);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 3);
    test_assertint(this->suspended, 0);

    /* Foo constructor modifies members */
    test_assert(o->x == 20);
    test_assert(o->y == 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(sinkMount);

    test_assertint(*test_constructCalled_o, 3);
    test_assertint(*test_destructCalled_o, 3);
    test_assertint(this->declared, 3);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 3);
    test_assertint(this->suspended, 3);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNested2FromMount(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNested2FromMount) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    corto_object mount = corto_resolve(root_o, "mount");
    test_assert(mount != NULL);

    test_Foo o = corto_resolve(mount, "x/a/k");
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(*test_constructCalled_o, 3);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 3);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 3);
    test_assertint(this->suspended, 0);

    /* Foo constructor modifies members */
    test_assert(o->x == 20);
    test_assert(o->y == 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(sinkMount);
    corto_release(mount);

    test_assertint(*test_constructCalled_o, 3);
    test_assertint(*test_destructCalled_o, 3);
    test_assertint(this->declared, 3);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 3);
    test_assertint(this->suspended, 3);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNested2FromObjectFromMount(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNested2FromObjectFromMount) */

    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    corto_object mount = corto_resolve(root_o, "mount");
    test_assert(mount != NULL);

    corto_object x = corto_resolve(mount, "x");
    test_assert(x != NULL);

    test_assertint(*test_constructCalled_o, 1);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 1);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 1);
    test_assertint(this->suspended, 0);

    corto_object a = corto_resolve(x, "a");
    test_assert(a != NULL);

    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 0);

    test_Foo o = corto_resolve(a, "k");
    test_assert(o != NULL);
    test_assert(corto_typeof(o) == corto_type(test_Foo_o));
    test_assert(corto_ownerof(o) == sinkMount);
    test_assert(corto_checkState(o, CORTO_DEFINED | CORTO_DECLARED));
    test_assert(corto_checkAttr(o, CORTO_ATTR_PERSISTENT));

    test_assertint(*test_constructCalled_o, 3);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 3);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 3);
    test_assertint(this->suspended, 0);

    /* Foo constructor modifies members */
    test_assert(o->x == 20);
    test_assert(o->y == 40);

    /* This should remove o from the store and "suspend" it to the sink */
    corto_release(o);
    corto_release(a);
    corto_release(x);
    corto_release(sinkMount);
    corto_release(mount);

    test_assertint(*test_constructCalled_o, 3);
    test_assertint(*test_destructCalled_o, 3);
    test_assertint(this->declared, 3);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 3);
    test_assertint(this->suspended, 3);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNested2NotExist(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNested2NotExist) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = corto_resolve(root_o, "mount/x/a/notexists");
    test_assert(o == NULL);

    /* x is resumed and suspended */
    test_assertint(*test_constructCalled_o, 2);
    test_assertint(*test_destructCalled_o, 2);
    test_assertint(this->declared, 2);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 2);
    test_assertint(this->suspended, 2);

    corto_release(sinkMount);

/* $end */
}

corto_void _test_AutoResumeSink_tc_resolveNotExist(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/tc_resolveNotExist) */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_object sinkMount = corto_resolve(root_o, "sinkMount");
    test_assert(sinkMount != NULL);

    test_Foo o = corto_resolve(root_o, "mount/notexists");
    test_assert(o == NULL);

    /* x is resumed and suspended */
    test_assertint(*test_constructCalled_o, 0);
    test_assertint(*test_destructCalled_o, 0);
    test_assertint(this->declared, 0);
    test_assertint(this->defined, 0);
    test_assertint(this->deleted, 0);
    test_assertint(this->updated, 0);
    test_assertint(this->resumed, 0);
    test_assertint(this->suspended, 0);

    corto_release(sinkMount);

/* $end */
}

corto_void _test_AutoResumeSink_teardown(
    test_AutoResumeSink this)
{
/* $begin(test/AutoResumeSink/teardown) */
    corto_object mount = corto_resolve(NULL, "mount");
    corto_observer_unobserve(test_ResumeSink_onDeclare_o, this, mount);
    corto_observer_unobserve(test_ResumeSink_onDefine_o, this, mount);
    corto_observer_unobserve(test_ResumeSink_onDelete_o, this, mount);
    corto_observer_unobserve(test_ResumeSink_onUpdate_o, this, mount);
    corto_observer_unobserve(test_ResumeSink_onResume_o, this, mount);
    corto_observer_unobserve(test_ResumeSink_onSuspend_o, this, mount);
    corto_release(mount);
/* $end */
}
