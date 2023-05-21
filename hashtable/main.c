#include "hashtable.h"

#include <stdio.h>

int main(void) {
    int n_birds, n_queries;
    if(scanf("%d %d", &n_birds, &n_queries) != 2) {
        printf("Fehler: Zeile der Form <n> <m> erwartet.");
        return 1;
    }

    int a, b, p;
    if(scanf("%d %d %d", &a, &b, &p) != 3) {
        printf("Fehler: Zeile der Form <a> <b> <p> erwartet.");
        return 2;
    }

    // Hier fehlt Code:
    /* hier Hashtable deklarieren */
    HashTable h;
    /* hier Hashtable initialisieren */
    init(&h,a,b,p);
    for(int i=0; i < n_birds; ++i) {
        Bird bird;
        if(scanf("%d %d %d", &bird.id, &bird.x, &bird.y) != 3) {
            printf("Fehler: Konnte Vogel %d nicht lesen.\n", i+1);
            return 3;
        }
        if(insert(&h,bird) == TABLE_SIZE) {
            printf("Fehler: Hashtabelle voll\n");
            return 4;
        }
        print_table(&h);
    }

    for(int i=0; i < n_queries; ++i) {
        int query;
        if(scanf("%d", &query) != 1) {
            printf("Fehler: Konnte Query %d nicht lesen.\n", i+1);
            return 4;
        }
        Bird bird = get(&h, query);
        if(bird.id == -1) {
            printf("Vogel %d nicht beobachtet.\n", query);
        }
        else {
            printf("Vogel %d bei (%d, %d) beobachtet.\n", query, bird.x, bird.y);
        }
    }

    printf("%d Kollisionen beim Einfügen.\n", h.n_collisions);

    return 0;
}
