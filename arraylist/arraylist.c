#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Initiale Kapazität der Arrayliste */
const int initial_capacity = 11;

int _resize(ArrayList *l, int new_capacity);

/* Konstruktur; initialisiert l als leere Liste
 * mit einem Array der Größe initial_capacity.*/
void al_init(ArrayList *l) {
    l->arr = (int *)malloc(initial_capacity * sizeof(int));
    l->size = 0;
    l->capacity = initial_capacity;
}

/* Destruktor; gibt sämtlichen von der Arrayliste
 * dynamisch allokierten Speicher wieder frei */
void al_destroy(ArrayList *l) {
    if (l->arr != NULL) {
        free(l->arr);
        l->arr = NULL;
    }
    l->size = 0;
    l->capacity = initial_capacity;
}

/* Hängt den Schlüssel key an das Ende der
 * Arrayliste an. Wenn die aktuelle Kapazität
 * der Arrayliste nicht ausreicht, wird die Kapazität
 * der Arrayliste verdoppelt. */
int al_append(ArrayList *l, int key) {
    if (l->size >= l->capacity) {
        if (!_resize(l, 2*l->capacity)) {
            return 0;
        }
    }
    l->arr[l->size] = key;
    l->size++;
    return 1;

}

/* Fügt den Schlüssel key an Position pos ein.
 * Schiebt dazu die Elemente l->arr[pos,...,l->size-1]
 * um eine Position nach rechts. Wenn die aktuelle
 * Kapazität der Arrayliste nicht ausreicht,
 * wird die Kapazität der Arrayliste verdoppelt.
 *
 * Wenn pos == l->size ist die Funktion äquivalent
 * zu al_append. Es muss 0 <= pos <= l->size gelten.
 */
int al_insert(ArrayList *l, int pos, int key) {
    if(pos < 0 || pos > l->size){
        return 0;
    }
    if (l->size >= l->capacity) {
        int cap = 2* l->capacity;
        if (!_resize(l, cap)) {
            return 0;
        }
    }
    for (int i = l->size; i > pos; i--) {
        l->arr[i] = l->arr[i - 1];
    }
    l->arr[pos] = key;
    l->size++;
    return 1;
}

/* Löscht den Schlüssel an Position pos und
 * schiebt die Elemente l->arr[pos+1,...,l->size-1]
 * um eine Position nach links. Falls nach der
 * Operation die Kapazität mehr als dreimal so groß
 * wie die Anzahl der Elemente in der Liste ist,
 * wird die Kapazität der Liste halbiert.
 * Die Kapazität der Liste wird niemals unter 11
 * reduziert. Es muss 0 <= pos < l->size gelten.
 */
void al_delete(ArrayList *l, int pos) {
    if (pos < 0 || pos >= l->size) {
        return;
    }
    for (int i = pos; i < l->size - 1; i++) {
        l->arr[i] = l->arr[i + 1];
    }
    l->size--;
    if (l->capacity > 3 * l->size && l->capacity > initial_capacity) {
        int cap = l->capacity / 2 < initial_capacity ? initial_capacity : l->capacity/2;
        _resize(l, cap);
    }
}

/* Hilfsfunktion: Ändert die Kapazität der Liste
 * auf new_capacity; new_capacity kann größer
 * oder kleiner als die aktuelle Kapazität sein.
 *
 * Die Kapazität der Liste soll immer mindestens
 * 11 sein; daher soll die Funktion nichts tun,
 * wenn new_capacity < 11 ist.
 */
int _resize(ArrayList *l, int new_capacity) {
    if (new_capacity < 11) {
        return 0;
    }

    int *new_arr = (int *) realloc(l->arr, new_capacity * sizeof(int));
    if (new_arr == NULL) {
        return 0;
    }
    l->arr = new_arr;
    l->capacity = new_capacity;
    return 1;
}

/* Gibt die Liste in die Datei f aus
 * Verändern Sie diese Funktion bitte nicht :)
 */
void al_print(FILE *f, const ArrayList *l) {
    fprintf(f, "[ ");
    for (int i = 0; i < l->size; ++i) {
        fprintf(f, "%3d ", l->arr[i]);
    }
    for (int i = l->size; i < l->capacity; ++i) {
        fprintf(f, "%3s ", "");
    }
    fprintf(f, " ][ size: %3d capacity: %3d ]\n", l->size, l->capacity);
}
