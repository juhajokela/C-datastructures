#ifndef MAP_H
#define MAP_H

typedef struct MapEntry MapEntry;
struct MapEntry {
    char* key;
    void* value;
    MapEntry* next;
};

typedef struct Map {
    MapEntry** data;
    size_t size;
} Map;

Map* map_init();
void map_set(Map* map, char* key, void* value);
void* map_get(Map* map, char* key);
void map_delete(Map* map, char* key);

#endif
