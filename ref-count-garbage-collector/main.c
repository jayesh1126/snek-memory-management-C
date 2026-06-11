#include "snekobject.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void test_array_set(void) {
  snek_object_t *foo = new_snek_integer(1);

  snek_object_t *array = new_snek_array(1);
  snek_array_set(array, 0, foo);

  assert(foo->refcount == 2 && "foo is now referenced by array");

  refcount_dec(foo);
  refcount_dec(array);

  printf("test_array_set passed\n");
}

static void test_array_free(void) {
  snek_object_t *foo = new_snek_integer(1);
  snek_object_t *bar = new_snek_integer(2);
  snek_object_t *baz = new_snek_integer(3);

  snek_object_t *array = new_snek_array(2);
  snek_array_set(array, 0, foo);
  snek_array_set(array, 1, bar);

  assert(foo->refcount == 2);
  assert(bar->refcount == 2);
  assert(baz->refcount == 1);

  refcount_dec(foo);
  assert(foo->refcount >= 1); // still referenced by array

  snek_array_set(array, 0, baz); // overwrite foo -> should free foo

  refcount_dec(bar);
  refcount_dec(baz);
  refcount_dec(array);

  printf("test_array_free passed\n");
}

static void test_vector3_refcounting(void) {
  snek_object_t *foo = new_snek_integer(1);
  snek_object_t *bar = new_snek_integer(2);
  snek_object_t *baz = new_snek_integer(3);

  snek_object_t *vec = new_snek_vector3(foo, bar, baz);

  assert(foo->refcount == 2);
  assert(bar->refcount == 2);
  assert(baz->refcount == 2);

  refcount_dec(foo);
  refcount_dec(vec);

  refcount_dec(bar);
  refcount_dec(baz);

  printf("test_vector3_refcounting passed\n");
}

static void test_refcount_basics(void) {
  snek_object_t *obj = new_snek_integer(10);
  assert(obj->refcount == 1);
  free(obj);

  printf("test_refcount_basics passed\n");
}

static void test_inc_dec(void) {
  snek_object_t *obj = new_snek_float(4.2);

  assert(obj->refcount == 1);

  refcount_inc(obj);
  assert(obj->refcount == 2);

  refcount_dec(obj);
  assert(obj->refcount == 1);

  free(obj);

  printf("test_inc_dec passed\n");
}

static void test_string_refcount(void) {
  snek_object_t *obj = new_snek_string("Hello @wagslane!");

  refcount_inc(obj);
  assert(obj->refcount == 2);

  refcount_dec(obj);
  assert(obj->refcount == 1);

  refcount_dec(obj);

  printf("test_string_refcount passed\n");
}

int main(void) {
  test_array_set();
  test_array_free();
  test_vector3_refcounting();
  test_refcount_basics();
  test_inc_dec();
  test_string_refcount();

  printf("ALL TESTS PASSED\n");
  return 0;
}
