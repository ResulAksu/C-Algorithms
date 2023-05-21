#include "unionfind.h"
#include <stdio.h>

void uf_init(UFNode* uf, int key) {
    uf->parent = uf; // Konvention: uf hat kein Elter falls uf->parent == uf
    uf->key = key;
    uf->size = 1; // initial enthält Partition genau ein Element
}

UFNode* uf_find(UFNode* x) {
  // hier Code einfügen
    if(x->parent == x){
        return x;
    }
    x->parent = uf_find(x->parent);
    return x->parent;
}

UFNode* uf_union(UFNode* x, UFNode* y) {
   // hier Code einfügen
   UFNode* wurzelx = uf_find(x);
   UFNode* wurzely = uf_find(y);
   if(wurzelx->size > wurzely->size){
       wurzely->parent = wurzelx;
       wurzelx->size = wurzelx->size + wurzely->size;
       return wurzelx;
   }else if(wurzelx->size < wurzely->size){
       wurzelx->parent= wurzely;
       wurzely->size = wurzely->size +wurzelx->size;
       return wurzely;
   }else{
       if(wurzelx->key < wurzely->key){
           wurzelx->parent= wurzely;
           wurzely->size = wurzely->size +wurzelx->size;
           return wurzely;
       }else{
           wurzely->parent=wurzelx;
           wurzelx->size = wurzelx->size + wurzely->size;
           return wurzelx;
       }
   }
}

void uf_print(const UFNode* x) {
    printf("%d: %d", x->key, x->parent->key); // parent ist niemals null
}

void print_all(UFNode uf[], int n) {
    printf(" / ");
    for(int i=0; i < n; ++i){
        uf_print(&uf[i]);
        printf(" / ");
    }
    printf("\n");
}
