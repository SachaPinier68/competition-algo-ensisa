#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *A;

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);
int compare(const void *a, const void *b){
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x > y) return -1;
    if (x < y) return 1;
    return 0;
}


int main()
{
    int n = parse_int(ltrim(rtrim(readline())));
    A = malloc(n * sizeof(int));
    long long k=0;   

    for (int n_itr = 0; n_itr < n; n_itr++) {
        int x = parse_int(ltrim(rtrim(readline())));
        A[n_itr]=x;
        k+=x;
    }
    qsort(A, n, sizeof(int), compare);
    long long sum=0;
    int i=0;
    while (2*sum <= k){  
        sum += A[i];
        i++;
    }
    printf("%i\n",i);
    for(int p=0;p<i;p++){
        printf("%i\n",A[p]);
    }
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}