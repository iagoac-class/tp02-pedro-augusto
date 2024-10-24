#include <stdio.h>
#include <stdlib.h>
#include <time.h>       
#include "arvores.h"

// Inicializando a raiz da árvore como NULL, (Árvore começa vazia).
struct arvbin *root = NULL;

// Função para criar um novo nó na árvore binária.
struct arvbin *Novo_no(int valor){
    // Alocamos o espaço de uma posição da struct para armazenar o nó, definimos o valor do nó com o parâmetro passado e iniciamos suas subárvores com NULL.
    struct arvbin *tmp = (struct arvbin*)malloc(sizeof(struct arvbin));
    if(!tmp){
        printf("\nErro ao alocar memória para o nó!");
        exit (EXIT_FAILURE);
    }
    
    tmp->valor = valor;
    tmp->esq = tmp->dir = NULL;

    return tmp;
}

// Função para buscar um nó na árvore binária.
struct arvbin *Busca_arvbin(int valor, struct arvbin **pai){
    struct arvbin *tmp = root; // Ponteiro para percorrer a àrvore.
    *pai = NULL; // Ponteiro para indicar o pai do nó encontrado (se ele possuir).

    // Ponteiro para armazenar o nó encontrado.
    struct arvbin *no_encontrado = NULL;
    
    // Busca pelo nó desejado e por seu nó pai.
    while(tmp != NULL){
        *pai = tmp;
        if(tmp->valor > valor){
            tmp = tmp->esq;
        }else if(tmp->valor < valor){
            tmp = tmp->dir;
        }else{
            no_encontrado = tmp;
            tmp = NULL;
        }
    }

    // Retorna o valor encontrado pela busca, sendo ele o valor encontrado ou NULL.
    return no_encontrado;
}

// Função para inserir um nó na árvore binária.
struct arvbin *Inserir_bin(int valor){
    struct arvbin *no_inserir = Novo_no(valor); // Nó a ser inserido na árvore binária.
    
    // Se a raiz for NULL, nó é inserido como raiz diretamente.
    if( root == NULL){
        root = no_inserir;
        return root;
    }

    // Criamos ponteiros para percorrer pela àrvore e encontrar o nó pai correto.
    struct arvbin *pai = NULL;
    struct arvbin *tmp = Busca_arvbin(valor, &pai);

    // Caso seja encontrado um nó válido ao invés da posição de inserção desejada, interrompemos a inserção.
    if(tmp != NULL){
        free(no_inserir); // Liberando o espaço alocado.
        printf("\nNão foi possível realizar a inserção, valor já presente na árvore!");
        return NULL;
    }

    // Inserindo o nó na posição correta.
    if(pai != NULL){
        if(valor < pai->valor){
            pai->esq = no_inserir;
        }else{
            pai->dir = no_inserir;
        }
    }

    return no_inserir;
}

// Função para remover um nó da árvore binária.
struct arvbin *Remover_bin(int valor){
    
    if(root == NULL) return NULL; // Caso a árvores esteja vazia.
    
    // Criamos ponteiros para percorrer pela àrvore e encontrar o nó pai correto.
    struct arvbin *pai = NULL;
    struct arvbin *tmp = Busca_arvbin(valor, &pai);


    if(tmp == NULL) return NULL; // Caso o nó a ser removido não exista.

    // Caso o nó a ser removido não possua filhos.
    if(tmp->esq == NULL && tmp->dir == NULL){
        if(pai == NULL){ // Nó a ser removido é a raiz.
           free(tmp);
           root = NULL; // Árvore ficará vazia.
        }else if(pai->esq == tmp){
            pai->esq = NULL; // Filho esquerdo removido.
        }else{
            pai->dir = NULL; // Filho direito removido.
        }
    }

    // Caso o no a ser removido possua apenas um filho.
    else if(tmp->esq == NULL || tmp->dir == NULL){
        struct arvbin *filho = (tmp->esq != NULL) ? tmp->esq : tmp->dir; // Caso tmp->esq != NULL, filho == tmp->esq; caso tmp->esq == NULL, filho == tmp->dir.
        if(pai == NULL){ // Nó a ser removido é a raiz.
            free(tmp);
            root = filho; // Filho assume papel de raiz.
        }else if(pai->esq == tmp){
            pai->esq = filho; // Conecta o pai ao filho restante.
        }else{
            pai->dir = filho; // Conecta o pai ao filho restante.
        }
        free(tmp); // Libera o espaço do nó que foi removido.
    }

    // Caso o nó a ser removido possua dois filhos.
    else{
        // Encontrar o sucessor (menor valor na subárvore direita).       
        struct arvbin *sucessor = tmp->dir;

        // Encontrar o sucessor do nó a ser removido.
        while(sucessor->esq != NULL){
            sucessor = sucessor->esq;
        }

        // Substituindo o nó a ser removido pelo seu sucessor.
        tmp->valor = sucessor->valor;

        // Removendo o sucessor.
        struct arvbin *pai_sucessor = tmp; // Nó que estamos removendo.
        if(pai_sucessor->esq == sucessor){
            pai_sucessor->esq = sucessor->dir; // Conecta o filho no sucessor.
        }else{
            pai_sucessor->dir = sucessor->dir; // Conecta o filho do sucessor.
        }
        free(sucessor); // Libera a memória do sucessor.
    }

    return tmp; // Retorna o nó removido (ou NULL caso não exista).
}

// Função contendo todas as operações que devem ser realizadas na árvore binária.
double arvore_binaria(int instancia_num) {
    clock_t begin = clock();

    // Formatação do nome do arquivo.
    char filename[20];
    snprintf(filename, sizeof(filename), "instancias/%d", instancia_num);

    // Lendo o arquivo de instâncias.
    FILE *arq = fopen(filename, "r");
    if (!arq) {
        printf("\nErro ao abrir o arquivo!");
        return -1.0;
    }

    // Variáveis para operações.
    char op;
    int valor;

    // Lendo o arquivo e realizando operações.
    while (fscanf(arq, " %c %d", &op, &valor) == 2) {
        if (op == 'I') {
            Inserir_bin(valor); // Inserção.
        } else if (op == 'R') {
            Remover_bin(valor); // Remoção.
        }
    }

    fclose(arq); // Fechando o arquivo.

    clock_t end = clock();
    double tempo = (double)(end - begin) / CLOCKS_PER_SEC; // Calcula o tempo decorrido.
    return tempo; // Retorna o tempo.
}

// Inicializando a árvore balanceada como NULL, (começa vazia).
struct Node *root_avl = NULL;

// Função que retorna o máximo entre dois valores inteiros.
int max(int a, int b)
{
    return (a > b)? a : b;
}

// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


// Função para alocar um novo na árvore balanceada.
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;  // O novo nó é concebido primeiramente como folha.
    return(node);
}

// Função que realiza a rotação de um nó para a direita.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Realizando a rotação.
    x->right = y;
    y->left = T2;

    // Atualizando as alturas.
    y->height = max(height(y->left),height(y->right)) + 1;
    x->height = max(height(x->left),height(x->right)) + 1;

    // Retornando a nova raiz.
    return x;
}

// Função que realiza a rotação de um nó para a esquerda.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Realizando a rotação.
    y->left = x;
    x->right = T2;

    // Atualizando as alturas.
    x->height = max(height(x->left),height(x->right)) + 1;
    y->height = max(height(y->left),height(y->right)) + 1;

    // Retornando a nova raiz.
    return y;
}

// Função que obtém o fator de balanceamento de um nó.
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0; // Se o nó não existe, retorna 0.

    return height(N->left) - height(N->right); // Caso exista, retorna o fator de balanceamento, (altura à esquerda - altura à direita).
}

// Função que realiza a inserção de um novo nó na árvore, recursivamente.
struct Node* insert(struct Node* node, int key)
{
    // Primeiramente, realizamos a inserção do mesmo modo que a árvore binária de busca (só que agora, recursivamente).
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    // Agora, atualizamos a altura do nó.
    node->height = 1 + max(height(node->left), height(node->right));

    // Checamos o fator de balanceamento do nó.
    int balance = getBalance(node);

    // Caso o nó esteja desbalanceado, existem 4 casos possíveis:

    // Caso Esquerda Esquerda.
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso Direita Direita.
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso Esquerda Direita.
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso Direita Esquerda.
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Retorna o nó da árvore com o menor valor.
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;

    // Percorre a árvore de cima pra baixo a fim de encontrar o nó mais a esquerda possível.
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Função recursiva para realizar a remoção de um nó da árvore.
struct Node* deleteNode(struct Node* root_avl, int key)
{
    // Primeiramente, realizamos a remoção tradicional da árvore desbalanceada (de modo recursivo).
    if (root_avl == NULL) return root_avl;
    
    // Se o nó procurado está à esquerda.
    if (key < root_avl->key) root_avl->left = deleteNode(root_avl->left, key);

    // Se o nó procurado está à direita.
    else if( key > root_avl->key) root_avl->right = deleteNode(root_avl->right, key);

    
    else
    {
        // Nó com somente um filho ou sem filhos. 
        if( (root_avl->left == NULL) || (root_avl->right == NULL)){

            struct Node *temp = root_avl->left ? root_avl->left : root_avl->right;

            // Nó sem filhos.
            if (temp == NULL)
            {
                temp = root_avl;
                root_avl = NULL;
            }else{ // Nó com somente um filho.
                *root_avl = *temp; 
                free(temp);
            }
        }
        else
        {
            // Nó com 2 filhos, procuramos pelo sucessor, menor valor da subárvore direita.
            struct Node* temp = minValueNode(root_avl->right);

            // Passa o valor do sucessor para esse nó.
            root_avl->key = temp->key;

            // Remova o sucessor.
            root_avl->right = deleteNode(root_avl->right, temp->key);
        }
    }

    // Se a árvore não possui nós, vazia.
    if (root_avl == NULL)
      return root_avl;

    // Agora, atualizamos a altura do nó atual.
    root_avl->height = 1 + max(height(root_avl->left),height(root_avl->right));

    // Obtendo o fator de balanceamento do nó.
    int balance = getBalance(root_avl);

    // Caso o nó esteja desbalanceado, temos 4 casos:

    // Caso Esquerda Esquerda.
    if (balance > 1 && getBalance(root_avl->left) >= 0)
        return rightRotate(root_avl);

    // Caso Esquerda Direita.
    if (balance > 1 && getBalance(root_avl->left) < 0)
    {
        root_avl->left =  leftRotate(root_avl->left);
        return rightRotate(root_avl);
    }

    // Caso Direita Direita.
    if (balance < -1 && getBalance(root_avl->right) <= 0)
        return leftRotate(root_avl);

    // Caso Direita Esquerda.
    if (balance < -1 && getBalance(root_avl->right) > 0)
    {
        root_avl->right = rightRotate(root_avl->right);
        return leftRotate(root_avl);
    }

    return root_avl;
}

// Função contendo todas as operações que devem ser realizadas na árvore balanceada (AVL).
double arvore_balanceada(int instancia_num) {
    clock_t begin = clock();

    // Formatação do nome do arquivo.
    char filename[20];
    snprintf(filename, sizeof(filename), "instancias/%d", instancia_num);

    // Lendo o arquivo de instâncias.
    FILE *arq = fopen(filename, "r");
    if (!arq) {
        printf("\nErro ao abrir o arquivo!");
        return -1.0; 
    }

    // Variáveis para operações.
    char op;
    int valor;

    // Lendo o arquivo e realizando operações.
    while (fscanf(arq, " %c %d", &op, &valor) == 2) {
        if (op == 'I') {
            insert(root_avl, valor); // Inserção.
        } else if (op == 'R') {
            deleteNode(root_avl, valor); // Remoção.
        }
    }

    fclose(arq); // Fechando o arquivo.

    clock_t end = clock();
    double tempo = (double)(end - begin) / CLOCKS_PER_SEC; // Calcula o tempo decorrido.
    return tempo; // Retorna o tempo.
}