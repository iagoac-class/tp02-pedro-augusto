#ifndef _H_ARVORES
#define _H_ARVORES

// Struct necessária para implementação da árvore binária de busca.
struct arvbin{
    int valor;
    struct arvbin *esq, *dir;
};

// Ponteiro para armazenar a raiz da árvore binária, utilizamos extern para que ela seja definida em arvores.c e referenciada globalmente, evitar erro de linkagem.
extern struct arvbin *root; 

// Incorporando todas as chamadas de funções da árvore binária de busca no arquivo .h e implementando em arvores.c .
double arvore_binaria(int instancia_num);

// Todas as operações necessárias para o funcionamento de uma árvore binária de busca.
struct arvbin *Novo_no(int valor);
struct arvbin *Busca_arvbin(int valor, struct arvbin **pai);
struct arvbin *Inserir_bin(int valor);
struct arvbin *Remover_bin(int valor);


// Struct necessária para implementação da árvore AVL.
struct Node{
    int key;
    struct Node *left, *right;
    int height;
};

// Ponteiro para armazenar a raiz da árvore balanceada.
extern struct Node *root_avl;

// Incorporando todas as chamadas de funções da árvore balanceada (AVL) no arquivo .h e implementando em arvores.c .
double arvore_balanceada(int instancia_num);

// Todas as operações necessárias para o funcionamento de uma árvore balanceada (AVL).
int max(int a, int b);
int height(struct Node *N);
struct Node* newNode(int key);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* node, int key);
struct Node * minValueNode(struct Node* node);
struct Node* deleteNode(struct Node* root_avl, int key);

#endif // _H_ARVORES