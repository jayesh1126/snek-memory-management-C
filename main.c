#include "snekobject.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  /* test_integer_add */
  snek_object_t *one = new_snek_integer(1);
  snek_object_t *three = new_snek_integer(3);
  snek_object_t *four = snek_add(one, three);

  assert(four != NULL);
  assert(four->kind == INTEGER);
  assert(four->data.v_int == 4);

  free(one);
  free(three);
  free(four);

  printf("test_integer_add passed\n");

  /* test_float_add */
  snek_object_t *f1 = new_snek_float(1.5);
  snek_object_t *f2 = new_snek_float(3.5);
  snek_object_t *f5 = snek_add(f1, f2);

  assert(f5 != NULL);
  assert(f5->kind == FLOAT);
  assert(f5->data.v_float == (1.5f + 3.5f));

  free(f1);
  free(f2);
  free(f5);

  printf("test_float_add passed\n");

  /* test_string_add */
  snek_object_t *hello = new_snek_string("hello");
  snek_object_t *world = new_snek_string(", world");
  snek_object_t *greeting = snek_add(hello, world);

  assert(greeting != NULL);
  assert(greeting->kind == STRING);
  assert(strcmp(greeting->data.v_string, "hello, world") == 0);

  free(hello->data.v_string);
  free(hello);
  free(world->data.v_string);
  free(world);
  free(greeting->data.v_string);
  free(greeting);

  printf("test_string_add passed\n");

  /* test_string_add_self */
  snek_object_t *rep = new_snek_string("(repeated)");
  snek_object_t *rep_res = snek_add(rep, rep);

  assert(rep_res != NULL);
  assert(rep_res->kind == STRING);
  assert(strcmp(rep_res->data.v_string, "(repeated)(repeated)") == 0);

  free(rep->data.v_string);
  free(rep);
  free(rep_res->data.v_string);
  free(rep_res);

  printf("test_string_add_self passed\n");

  /* test_vector3_add */
  snek_object_t *onef = new_snek_float(1.0);
  snek_object_t *twof = new_snek_float(2.0);
  snek_object_t *threef = new_snek_float(3.0);
  snek_object_t *fourf = new_snek_float(4.0);
  snek_object_t *fivef = new_snek_float(5.0);
  snek_object_t *sixf = new_snek_float(6.0);

  snek_object_t *v1 = new_snek_vector3(onef, twof, threef);
  snek_object_t *v2 = new_snek_vector3(fourf, fivef, sixf);
  snek_object_t *vsum = snek_add(v1, v2);

  assert(vsum != NULL);
  assert(vsum->kind == VECTOR3);

  assert(vsum->data.v_vector3.x->data.v_float == 5.0f);
  assert(vsum->data.v_vector3.y->data.v_float == 7.0f);
  assert(vsum->data.v_vector3.z->data.v_float == 9.0f);

  free(v1->data.v_vector3.x);
  free(v1->data.v_vector3.y);
  free(v1->data.v_vector3.z);
  free(v1);

  free(v2->data.v_vector3.x);
  free(v2->data.v_vector3.y);
  free(v2->data.v_vector3.z);
  free(v2);

  free(vsum->data.v_vector3.x);
  free(vsum->data.v_vector3.y);
  free(vsum->data.v_vector3.z);
  free(vsum);

  printf("test_vector3_add passed\n");

  /* test_array_add */
  snek_object_t *i = new_snek_integer(1);
  snek_object_t *arr1 = new_snek_array(2);
  assert(snek_array_set(arr1, 0, i));
  assert(snek_array_set(arr1, 1, i));

  snek_object_t *hi = new_snek_string("hi");
  snek_object_t *arr2 = new_snek_array(3);
  assert(snek_array_set(arr2, 0, hi));
  assert(snek_array_set(arr2, 1, hi));
  assert(snek_array_set(arr2, 2, hi));

  snek_object_t *arr_sum = snek_add(arr1, arr2);

  assert(arr_sum != NULL);
  assert(arr_sum->kind == ARRAY);
  assert(arr_sum->data.v_array.size == 5);

  snek_object_t *first = snek_array_get(arr_sum, 0);
  assert(first->data.v_int == 1);

  snek_object_t *second = snek_array_get(arr_sum, 1);
  assert(second->data.v_int == 1);

  snek_object_t *third = snek_array_get(arr_sum, 2);
  assert(strcmp(third->data.v_string, "hi") == 0);

  snek_object_t *fourth = snek_array_get(arr_sum, 3);
  assert(strcmp(fourth->data.v_string, "hi") == 0);

  snek_object_t *fifth = snek_array_get(arr_sum, 4);
  assert(strcmp(fifth->data.v_string, "hi") == 0);

  free(i);
  free(arr1->data.v_array.elements);
  free(arr1);

  free(hi->data.v_string);
  free(hi);
  free(arr2->data.v_array.elements);
  free(arr2);
  free(arr_sum->data.v_array.elements);
  free(arr_sum);

  printf("test_array_add passed\n");

  /* test_array_add_empty_left */
  snek_object_t *empty = new_snek_array(0);
  snek_object_t *hi2 = new_snek_string("hi");
  snek_object_t *arr3 = new_snek_array(2);
  assert(snek_array_set(arr3, 0, hi2));
  assert(snek_array_set(arr3, 1, hi2));

  snek_object_t *arr_empty_sum = snek_add(empty, arr3);

  assert(arr_empty_sum != NULL);
  assert(arr_empty_sum->kind == ARRAY);
  assert(arr_empty_sum->data.v_array.size == 2);

  snek_object_t *a = snek_array_get(arr_empty_sum, 0);
  snek_object_t *b = snek_array_get(arr_empty_sum, 1);

  assert(strcmp(a->data.v_string, "hi") == 0);
  assert(strcmp(b->data.v_string, "hi") == 0);

  free(empty->data.v_array.elements);
  free(empty);

  free(hi2->data.v_string);
  free(hi2);
  free(arr3->data.v_array.elements);
  free(arr3);
  free(arr_empty_sum->data.v_array.elements);
  free(arr_empty_sum);

  printf("test_array_add_empty_left passed\n");

  printf("ALL TESTS PASSED\n");
  return 0;
}
