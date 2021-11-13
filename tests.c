#include <assert.h>
#include <stdio.h>
#include "array.h"
#include "map.h"
#include "string.h"

void test_string() {
    String* string = str_init("test");
    assert(str_equals(string, "test"));
}

void test_array() {

    Array* array_str = array_init();
    array_push(array_str, "test");
    assert(array_get(array_str, 0) == "test");

    Array* array_int = array_init();
    int val = 1;
    array_push(array_int, &val);
    int* _val = array_get(array_int, 0);
    assert(*_val == 1);
}

void test_map() {

    // TODO: free strings

    Map* map = map_init(1000);
    assert(map_get(map, "key") == NULL);
    map_set(map, "key", str_init("value"));
    assert(str_equals(map_get(map, "key"), "value"));
    map_set(map, "key", str_init("walue"));
    assert(str_equals(map_get(map, "key"), "walue"));
    map_delete(map, "key");
    assert(map_get(map, "key") == NULL);

    Map* map_tiny = map_init(1);
    map_set(map_tiny, "key", str_init("value"));
    map_set(map_tiny, "avain", str_init("arvo"));
    assert(str_equals(map_get(map_tiny, "key"), "value"));
    assert(str_equals(map_get(map_tiny, "avain"), "arvo"));
}

void test_str_print() {
    str_print(str_init("Hello, World!"));
}

void test_str_concat() {
    String* string = str_init("Hello,");
    str_concat(string, " ");
    str_concat(string, "World!");
    assert(str_length(string) == 13);
    assert(str_equals(string, "Hello, World!") == true);
    assert(str_equals(string, "Hello,World!") == false);
}

void test_str_split() {
    String* string = str_init("/drive/media/root/directory/subdirectory");
    Array* results = str_split(string, "/");
    assert(array_length(results) == 6);
    assert(str_equals(array_get(results, -1), "subdirectory"));
}

void test_str_lower() {
    assert(str_equals(str_lower(str_init("TesT")), "test"));
}

void test_array_pop() {
    Array* array = array_init();
    array_push(array, "1");
    array_push(array, "2");
    array_push(array, "3");
    array_push(array, "4");
    array_push(array, "5");
    for (int i = 0; i < array_length(array); ++i) {
      puts(array_get(array, i));
    }
    array_pop(array, 2);
    for (int i = 0; i < array_length(array); ++i) {
      puts(array_get(array, i));
    }
}

int main() {

    test_string();
    test_array();
    test_map();

    test_str_print();
    test_str_concat();
    test_str_split();
    test_str_lower();

    test_array_pop();

    return 0;
}
