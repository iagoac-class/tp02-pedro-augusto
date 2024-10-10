#ifndef _H_ARVORES
#define _H_ARVORES

// Implementar qualquer struct que for necessária aqui
struct arvbin{
    int valor;
    struct arvbin *esq, *dir;
}*root; // Ponteiro para armazenar a raiz da árvore.

double arvore_binaria(int instancia_num);
double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES