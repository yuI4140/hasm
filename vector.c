#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10
typedef struct {
    void **data;
    size_t size;
    size_t capacity;
} Vector;

Vector* new_vector() {
    Vector *vec = (Vector*)malloc(sizeof(Vector));
    if (!vec) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    vec->data = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
    if (!vec->data) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
    return vec;
}

void init_vector(Vector *vec) {
    vec->data = (void**)malloc(INITIAL_CAPACITY * sizeof(void*));
    if (!vec->data) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
}

void push(Vector *vec, void *element) {
    if (vec->size >= vec->capacity) {
        vec->capacity *= 2;
        vec->data = (void**)realloc(vec->data, vec->capacity * sizeof(void*));
        if (!vec->data) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
    }
    vec->data[vec->size++] = element;
}

void* pop(Vector *vec) {
    if (vec->size == 0) {
        fprintf(stderr, "Vector is empty\n");
        return NULL;
    }
    return vec->data[--vec->size];
}

void remove_element(Vector *vec, size_t index) {
    if (index >= vec->size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    for (size_t i = index; i < vec->size - 1; ++i) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->size--;
}

void* find(Vector *vec, void *element) {
    for (size_t i = 0; i < vec->size; ++i) {
        if (vec->data[i] == element) {
            return vec->data[i];
        }
    }
    return NULL;
}

char* to_str(Vector *vec) {
    size_t total_length = 0;
    for (size_t i = 0; i < vec->size; ++i) {
        total_length += strlen((char*)vec->data[i]);
    }
    char *str = (char*)malloc((total_length + vec->size + 1) * sizeof(char)); // +1 for null terminator
    if (!str) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(str, "");
    for (size_t i = 0; i < vec->size; ++i) {
        strcat(str, (char*)vec->data[i]);
        if (i < vec->size - 1) {
            strcat(str, ",");
        }
    }
    return str;
}

void resize(Vector *vec, size_t new_capacity) {
    vec->capacity = new_capacity;
    vec->data = (void**)realloc(vec->data, new_capacity * sizeof(void*));
    if (!vec->data) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    if (vec->size > new_capacity) {
        vec->size = new_capacity;
    }
}

size_t get_len(Vector *vec) {
    return vec->size;
}

void free_vector(Vector *vec) {
    free(vec->data);
    free(vec);
}
