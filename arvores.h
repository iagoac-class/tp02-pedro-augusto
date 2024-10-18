#ifndef _H_ARVORES
#define _H_ARVORES

// Structs necessárias para realizar o programa.
struct arvbin{
    int valor;
    struct arvbin *esq, *dir;
};

// Ponteiro para armazenar a raiz da árvore binária, utilizamos extern para que ela seja definida em arvores.c e referenciada globalmente, evitar erro de linkagem.
extern struct arvbin *root; 

// Incorporando todas as chamadas de funções da árvore binári de busca no arquivo .h e implementando em arvores.c .
double arvore_binaria(int instancia_num);

// Todas as operações necessárias para o funcionamento de uma árvore binária de busca.
struct arvbin *Novo_no(int valor);
struct arvbin *Busca_arvbin(int valor, struct arvbin **pai);
struct arvbin *Inserir_bin(int valor);
struct arvbin *Remover_bin(int valor);


double arvore_balanceada(int instancia_num);

#endif // _H_ARVORES