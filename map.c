#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

size_t generate_hash(char* key) {
    // TODO: optimize
    size_t hash = 0;
    for (size_t i = 0; i < strlen(key); ++i) {
        hash += key[i];
    }
    return hash;
}

size_t generate_index(Map* map, char* key) {
    size_t hash = generate_hash(key);
    return hash % map->size;
}

bool keys_match(MapEntry* entry, char* key) {
    return strcmp(entry->key, key) == 0;
}

Map* map_init(size_t size) {
    Map* map = malloc(sizeof(Map));
    map->data = calloc(size, sizeof(MapEntry**));
    map->size = size;
    return map;
}

MapEntry* map_entry_create(char* key, void* value) {
    MapEntry* map_entry = malloc(sizeof(MapEntry));
    map_entry->key = malloc((strlen(key) + 1) * sizeof(char));
    strcpy(map_entry->key, key);
    map_entry->value = malloc(sizeof(void*));
    map_entry->value = value;
    map_entry->next = NULL;
    return map_entry;
}

void map_entry_delete(MapEntry* map_entry) {
    free(map_entry->key);
    free(map_entry->value);
    free(map_entry);
}

void map_set(Map* map, char* key, void* value) {
    MapEntry* entry = map_entry_create(key, value);
    size_t index = generate_index(map, key);
    MapEntry* slot = map->data[index];
    if (!slot) {
        map->data[index] = entry;

        return;
    }
    while (true) {
        if (keys_match(slot, key)) {
            slot->value = value;
            break;
        }
        if (!slot->next) {
            slot->next = entry;
            break;
        }
        slot = slot->next;
    }
}

void* map_get(Map* map, char* key) {
    size_t index = generate_index(map, key);
    MapEntry* entry = map->data[index];
    while (entry) {
        if (keys_match(entry, key)) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

void map_delete(Map* map, char* key) {
    size_t index = generate_index(map, key);
    MapEntry* entry = map->data[index];
    if (!entry) {
        return;
    }
    if (keys_match(entry, key)) {
        map->data[index] = entry->next;
        map_entry_delete(entry);
        map->data[index] = NULL;
        return;
    }
    while (true) {
        MapEntry* previous = entry;
        entry = entry->next;
        if (!entry) {
            break;
        }
        if (keys_match(entry, key)) {
            previous->next = entry->next;
            map_entry_delete(entry);
            break;
        }
    }
}

char** map_keys(Map* map) {
    
}


// shallow copy
Map* map_copy(Map* map) {

}
