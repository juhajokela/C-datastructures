#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "array.h"
#include "string.h"

/*
TODO:
tolower
toupper
isnumber

str_concat -> str_append ?
str_ -> string_ ?
object -> string ?
object.string -> string.data ?
*/

String* str_init(const char* string) {
    String* object = malloc(sizeof(String));
    size_t string_length = strlen(string);
    object->length = string_length + 1;
    object->string = malloc(string_length * sizeof(char));
    strcpy(object->string, string);
    return object;
}

void str_print(String* object) {
    if (!object) {
        puts(NULL);
    } else {
        puts(object->string);
    }
}

void str_concat(String* object, const char* string) {
    size_t string_length = object->length + strlen(string);
    char* pointer = (char*) realloc(
        object->string, string_length * sizeof(char)
    );
    if (pointer) {
        strcat(pointer, string);
        object->string = pointer;
        object->length = string_length;
    } else {
        puts("str_concat: failed to allocate memory.");
    }
}

size_t str_length(String* object) {
    return object->length - 1;
}

bool str_equals(String* object, const char* string) {
    if (!object || !string) return false;
    return strcmp(object->string, string) == 0;
}

Array* str_split(String* object, const char* delimiters) {
  Array* results = array_init();
  char* token;
  while ((token = strsep(&object->string, delimiters))) {
      String* substring = str_init(token);
      array_push(results, substring);
  }
  return results;
}

String* str_copy(String* object) {
    // TODO: optimize!!!
    return str_init(object->string);
}

void str_apply(String* object, int (*func)(int)) {
    for (size_t i = 0; i < object->length; ++i) {
        object->string[i] = func(object->string[i]);
    }
}

void str_tolower(String* object) {
    str_apply(object, tolower);
}

String* str_lower(String* object) {
    String* result = str_copy(object);
    str_tolower(result);
    return result;
}

void str_toupper(String* object) {
    str_apply(object, toupper);
}

String* str_upper(String* object) {
    String* result = str_copy(object);
    str_toupper(result);
    return result;
}

void str_free(String* object) {
    free(object->string);
    free(object);
}
