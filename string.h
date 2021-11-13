#ifndef STRING_H
#define STRING_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct String {
    char* string;
    size_t length;
} String;

String* str_init(const char* string);
void str_print(String* object);
void str_concat(String* object, const char* string);
size_t str_length(String* object);
bool str_equals(String* object, const char* string);
Array* str_split(String* object, const char* delimiters);

String* str_lower(String* object);

#endif
