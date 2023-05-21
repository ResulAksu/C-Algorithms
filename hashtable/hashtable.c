#include "hashtable.h"

#include <stdio.h>
#include <stdbool.h>

void init(HashTable *h, int a, int b, int p) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        h->table[i].id = EMPTY;
        h->table[i].x = 0;
        h->table[i].y = 0;
    }

    h->n_collisions = 0;
    h->n_items = 0;
    h->a = a;
    h->b = b;
    h->p = p;
}

unsigned int hash(const HashTable *h, int key) {
    return (h->a * key + h->b) % h->p;
}

bool is_pos_empty(const HashTable *h, unsigned int pos) {
    return h->table[pos].id == EMPTY;
}

unsigned int insert(HashTable *h, Bird b) {
    if (h->n_items == TABLE_SIZE) {
        return TABLE_SIZE;
    }

    unsigned int index = hash(h, b.id) % TABLE_SIZE;
    unsigned int count = 0;

    while (!is_pos_empty(h, index)) {
        index = (index + 1) % TABLE_SIZE;
        count++;
        h->n_collisions++;

        if(count >= TABLE_SIZE){
            return TABLE_SIZE;
        }
    }

    h->table[index].id = b.id;
    h->table[index].x = b.x;
    h->table[index].y = b.y;

    h->n_items++;

    return index;
}

Bird get(const HashTable *h, int key) {
    unsigned int index = hash(h, key) %TABLE_SIZE;

    while (!is_pos_empty(h, index)) {
        if (h->table[index].id == key) {
            return h->table[index];
        }

        index = (index + 1) % TABLE_SIZE;
    }

    Bird dummy;
    dummy.id = -1;
    dummy.x = -1;
    dummy.y = -1;
    return dummy;
}


void print_table(const HashTable *h) {
    printf("#");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("  %03d#", i);
    }
    printf("\n");

    printf("#");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (is_pos_empty(h, i)) {
            printf("%5s#", "");
        } else {
            printf("%5d#", h->table[i].id);
        }
    }
    printf("\n\n");
}
