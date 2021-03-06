/*
util.h
random utilities
*/

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *content;
    size_t size;
} FileReadResult;

/**
 * Takes a file pointer and reads the full contents of the file.
 * The caller is responsible for cleaning up the file pointer and buffer.
 */
FileReadResult util_read_file_contents(FILE *fp) {
    // get the file size
    fseek(fp, 0, SEEK_END);
    size_t size = ftell(fp);
    rewind(fp);

    // allocate buffer with file size and nullterm
    char *buffer = malloc((size + 1) * sizeof(*buffer));

    fread(buffer, size, 1, fp); // read chunk to buffer
    buffer[size] = '\0';        // add null terminator

    FileReadResult res = {.content = buffer, .size = size};
    return res;
}

bool streq(const char *s1, const char *s2) { return strcmp(s1, s2) == 0; }

// https://stackoverflow.com/questions/21133701/is-there-any-function-in-the-c-language-which-can-convert_base-base-of-decimal-number/21134322#21134322
int convert_dec_to(int val, int base) {
    if (val == 0 || base == 10)
        return val;
    return (val % base) + 10 * convert_dec_to(val / base, base);
}

void util_getln(char *buf, int n) { fgets(buf, n, stdin); }

// https://stackoverflow.com/questions/3408706/hexadecimal-string-to-byte-array-in-c/35452093#35452093
uint8_t *datahex(char *str) {

    if (str == NULL)
        return NULL;

    size_t slength = strlen(str);
    if ((slength % 2) != 0) // must be even
        return NULL;

    size_t dlength = slength / 2;

    uint8_t *data = malloc(dlength);
    memset(data, 0, dlength);

    size_t index = 0;
    while (index < slength) {
        char c = str[index];
        int value = 0;
        if (c >= '0' && c <= '9')
            value = (c - '0');
        else if (c >= 'A' && c <= 'F')
            value = (10 + (c - 'A'));
        else if (c >= 'a' && c <= 'f')
            value = (10 + (c - 'a'));
        else {
            free(data);
            return NULL;
        }

        data[(index / 2)] += value << (((index + 1) % 2) * 4);

        index++;
    }

    return data;
}

void reverse_bytes(uint8_t *start, int size) {
    uint8_t *lo = start;
    uint8_t *hi = start + size - 1;
    uint8_t swap;
    while (lo < hi) {
        swap = *lo;
        *lo++ = *hi;
        *hi-- = swap;
    }
}

char *util_strmk(size_t size) {
    char *str = malloc(size);
    str[0] = '\0';
    return str;
}

char* util_strdup(const char* str) {
    size_t len = strlen(str);
    char* dst = malloc(len + 1);
    strcpy(dst, str);
    return dst;
}
