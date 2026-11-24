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

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);



struct maillon {
    int lieu;
    struct maillon *suivant;
};

int n, m;
struct maillon **voisins;   
int *dist;                 
int *file;


void ajouter_voisin(int x, int y)
{
    struct maillon *nouveau = malloc(sizeof(struct maillon));
    nouveau->lieu = y;
    nouveau->suivant = voisins[x];
    voisins[x] = nouveau;
}

void parcoursBFS(int depart)
{
    int debut = 0;
    int fin = 0;

    dist[depart] = 0;
    file[fin] = depart;
    fin++;

    while (debut < fin) {
        int x = file[debut];
        debut++;
        for (struct maillon *p = voisins[x]; p != NULL; p = p->suivant) {
            int voisin = p->lieu;
            if (dist[voisin] == -1) {
                dist[voisin] = dist[x] + 1;
                file[fin] = voisin;
                fin++;
            }
        }
    }
}

int main()
{
    char** first_multiple_input = split_string(rtrim(readline()));

    n = parse_int(*(first_multiple_input + 0));

    m = parse_int(*(first_multiple_input + 1));

    voisins = malloc((n + 1) * sizeof(struct maillon *));
    dist    = malloc((n + 1) * sizeof(int));
    file    = malloc((n + 1) * sizeof(int));
    for (int x = 1; x <= n; x++) voisins[x] = NULL;   

    for (int m_itr = 0; m_itr < m; m_itr++) {
        char** second_multiple_input = split_string(rtrim(readline()));
        int u = parse_int(*(second_multiple_input + 0));
        int v = parse_int(*(second_multiple_input + 1));
        ajouter_voisin(u, v); 
        ajouter_voisin(v, u);
        free(second_multiple_input);
    }

    char** third_multiple_input = split_string(rtrim(readline()));

    int A = parse_int(*(third_multiple_input + 0));

    int B = parse_int(*(third_multiple_input + 1));

    /* ===== Tache 1 : compter les royaumes ===== */
    for (int x = 1; x <= n; x++) dist[x] = -1;

    int royaumes = 0;
    for (int x = 1; x <= n; x++) {
        if (dist[x] == -1) {
            royaumes++;
            parcoursBFS(x);
        }
    }

    /* ===== Tache 2 : plus court chemin de A a B ===== */
    for (int x = 1; x <= n; x++) dist[x] = -1;
    parcoursBFS(A);

    printf("%d\n", royaumes);
    printf("%d\n", dist[B]);

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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
