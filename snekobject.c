#include "snekobject.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
  if (a == NULL || b == NULL){
    return NULL;
  }

  switch (a->kind) {
    case INTEGER:
        if(b->kind==INTEGER){
          return new_snek_integer(a->data.v_int + b->data.v_int);
	} else if (b->kind==FLOAT) {
          return new_snek_float(a->data.v_int + b->data.v_float);
        } else {
	  return NULL;
	}
        break;
    case FLOAT:
        if(b->kind==INTEGER){
          return new_snek_float(a->data.v_float + b->data.v_int);
        } else if (b->kind==FLOAT) {
          return new_snek_float(a->data.v_float + b->data.v_float);
        } else {
          return NULL;
        }
        break;
    case STRING:
	if(b->kind!=STRING){
          return NULL;
        } else {
          char *temp = calloc(strlen(a->data.v_string) + strlen(b->data.v_string) + 1, sizeof(char));
	  if (temp == NULL){
	    return NULL;
	  }
	  strcat(temp, a->data.v_string);
	  strcat(temp, b->data.v_string);
	  snek_object_t *obj = new_snek_string(temp);
	  free(temp);
	  return obj;
        }
        break;
    case VECTOR3:
	if(b->kind!=VECTOR3){
          return NULL;
        } else {
          snek_object_t *snek_vector = new_snek_vector3(snek_add(a->data.v_vector3.x, b->data.v_vector3.x), snek_add(a->data.v_vector3.y, b->data.v_vector3.y), snek_add(a->data.v_vector3.z, b->data.v_vector3.z));
          return snek_vector;	  
	}
        break;
    case ARRAY:
	if(b->kind!=ARRAY){
          return NULL;
        } else {
	  snek_object_t *arr = new_snek_array(snek_length(a) + snek_length(b));
	  for (int i = 0; i < a->data.v_array.size; i++){
	    snek_array_set(arr, i, snek_array_get(a, i));
	  }
	  for (int j = 0; j < b->data.v_array.size; j++) {
	    snek_array_set(arr, j + a->data.v_array.size, snek_array_get(b, j));
	  }
	  return arr;
        }
        break;
    default:
        return NULL;
  }
}

int snek_length(snek_object_t *obj) {
  if (obj == NULL){
    return -1;
  }

  switch (obj->kind) {
    case INTEGER:
	return 1;
        break;
    case FLOAT:
	return 1;
        break;
    case STRING:
	return strlen(obj->data.v_string);
        break;
    case VECTOR3:
	return 3;
        break;
    case ARRAY:
	return obj->data.v_array.size;
        break;
    default:
	return -1;
  }
}

snek_object_t *snek_array_get(snek_object_t *snek_obj, size_t index) {
  if (snek_obj == NULL) {
    return NULL;
  }

  if (snek_obj->kind != ARRAY) {
    return NULL;
  }

  if (snek_obj->data.v_array.size <= index){
  return NULL;
  }

  return snek_obj->data.v_array.elements[index]; 
}

bool snek_array_set(snek_object_t *snek_obj, size_t index,
                    snek_object_t *value) {
  if (snek_obj == NULL || value == NULL){
    return false;
  }

  if (snek_obj->kind != ARRAY){
    return false;
  }

  if (snek_obj->data.v_array.size <= index){
    return false;
  }

  snek_obj->data.v_array.elements[index] = value;
  return true;
}

snek_object_t *new_snek_array(size_t size){
  
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj==NULL){
    return NULL;
  }

  snek_object_t **elements = calloc(size, sizeof(void*));
  if (elements==NULL){
    free(obj);
    return NULL;
  }

  obj->kind = ARRAY;
  obj->data.v_array.size = size;
  obj->data.v_array.elements = elements;

  return obj;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y,
                                snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj==NULL){
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3.x = x;
  obj->data.v_vector3.y = y;
  obj->data.v_vector3.z = z;

  return obj;
}

snek_object_t *new_snek_string(char *value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj==NULL){
    return NULL;
  }

  char *str_ptr = malloc(strlen(value) + 1);
  if (str_ptr==NULL){
    free(obj);
    return NULL;
  }

  strcpy(str_ptr, value);

  obj->kind = STRING;
  obj->data.v_string = str_ptr;

  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj==NULL){
    return NULL;
  }

  obj->kind = FLOAT;
  obj->data.v_float = value;

  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *snek_object_ptr = malloc(sizeof(snek_object_t));
  if (snek_object_ptr == NULL){
    return NULL;
  }

  snek_object_ptr->kind = INTEGER;
  snek_object_ptr->data.v_int = value;

  return snek_object_ptr;
}

