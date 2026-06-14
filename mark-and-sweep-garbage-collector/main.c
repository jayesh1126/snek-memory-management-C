#include "sneknew.h"
#include "snekobject.h"
#include "vm.h"

#include <assert.h>
#include <stdio.h>

static void test_simple(void) {
    vm_t *vm = vm_new();
    frame_t *f1 = vm_new_frame(vm);

    snek_object_t *s =
        new_snek_string(vm, "I wish I knew how to read.");

    frame_reference_object(f1, s);

    vm_collect_garbage(vm);

    /*
     * Object is still referenced by frame.
     */
    assert(vm->objects->count == 1);

    frame_free(vm_frame_pop(vm));

    vm_collect_garbage(vm);

    /*
     * Object should now be collected.
     */
    assert(vm->objects->count == 0);

    vm_free(vm);

    printf("test_simple passed\n");
}

static void test_full(void) {
    vm_t *vm = vm_new();

    frame_t *f1 = vm_new_frame(vm);
    frame_t *f2 = vm_new_frame(vm);
    frame_t *f3 = vm_new_frame(vm);

    snek_object_t *s1 =
        new_snek_string(vm, "This string is going into frame 1");
    frame_reference_object(f1, s1);

    snek_object_t *s2 =
        new_snek_string(vm, "This string is going into frame 2");
    frame_reference_object(f2, s2);

    snek_object_t *s3 =
        new_snek_string(vm, "This string is going into frame 3");
    frame_reference_object(f3, s3);

    snek_object_t *i1 = new_snek_integer(vm, 69);
    snek_object_t *i2 = new_snek_integer(vm, 420);
    snek_object_t *i3 = new_snek_integer(vm, 1337);

    snek_object_t *v =
        new_snek_vector3(vm, i1, i2, i3);

    frame_reference_object(f2, v);
    frame_reference_object(f3, v);

    assert(vm->objects->count == 7);

    /*
     * Remove frame 3.
     * s3 should become unreachable.
     * vector is still referenced by frame 2.
     */
    frame_free(vm_frame_pop(vm));

    vm_collect_garbage(vm);

    assert(vm->objects->count == 6);

    /*
     * Remove remaining frames.
     */
    frame_free(vm_frame_pop(vm));
    frame_free(vm_frame_pop(vm));

    vm_collect_garbage(vm);

    assert(vm->objects->count == 0);

    vm_free(vm);

    printf("test_full passed\n");
}

int main(void) {
    test_simple();
    test_full();

    printf("ALL TESTS PASSED\n");
    return 0;
}
