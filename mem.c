#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 16

struct Memory {
    struct MemoryEntry *entries;
    size_t size;
    size_t capacity;
};

struct MemoryEntry {
    uint64_t key;
    uint8_t *data;
    size_t data_size;
};

struct Memory new_Memory() {
    struct Memory mem;
    mem.entries = malloc(INITIAL_CAPACITY * sizeof(struct MemoryEntry));
    if (!mem.entries) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    mem.size = 0;
    mem.capacity = INITIAL_CAPACITY;
    return mem;
}

void free_Memory(struct Memory *mem) {
    for (size_t i = 0; i < mem->size; ++i) {
        free(mem->entries[i].data);
    }
    free(mem->entries);
}

void load_data(struct Memory *mem, uint64_t key, const uint8_t *data, size_t data_size) {
    if (mem->size == mem->capacity) {
        size_t new_capacity = mem->capacity * 2;
        struct MemoryEntry *new_entries = realloc(mem->entries, new_capacity * sizeof(struct MemoryEntry));
        if (!new_entries) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        mem->entries = new_entries;
        mem->capacity = new_capacity;
    }

    mem->entries[mem->size].key = key;
    mem->entries[mem->size].data = malloc(data_size);
    if (!mem->entries[mem->size].data) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    mem->entries[mem->size].data_size = data_size;
    memcpy(mem->entries[mem->size].data, data, data_size);
    mem->size++;
}

void *unload_data(struct Memory *mem, uint64_t key, size_t *data_size) {
    for (size_t i = 0; i < mem->size; ++i) {
        if (mem->entries[i].key == key) {
            void *data = mem->entries[i].data;
            *data_size = mem->entries[i].data_size;

            // Shift entries to fill the gap
            for (size_t j = i; j < mem->size - 1; ++j) {
                mem->entries[j] = mem->entries[j + 1];
            }

            mem->size--;
            return data;
        }
    }
    return NULL;
}

const void *find_data(const struct Memory *mem, uint64_t key, size_t *data_size) {
    for (size_t i = 0; i < mem->size; ++i) {
        if (mem->entries[i].key == key) {
            *data_size = mem->entries[i].data_size;
            return mem->entries[i].data;
        }
    }
    return NULL;
}
