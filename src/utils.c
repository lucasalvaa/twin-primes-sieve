#include "utils.h"

void *secure_malloc (size_t bytes) {
    void *p = malloc(bytes);
    if (p == NULL) {
        fprintf(stderr, "malloc failed while requesting %zu bytes\n", bytes);
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return p;
}

void *secure_realloc (void *p, size_t bytes) {
    void *q = realloc(p, bytes);
    if (q == NULL) {
        fprintf(stderr, "realloc failed while requesting %zu bytes\n", bytes);
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    return q;
}

FILE *secure_fopen (const char *filename, char *mode) {
    FILE *fp = fopen(filename, mode);
    if (fp == NULL) {
        fprintf(stderr, "fopen failed while opening file \"%s\" in mode \"%s\"\n", filename, mode);
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    return fp;
}