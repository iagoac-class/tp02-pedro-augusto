#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    
    // Criamos ponteiros para percorrer pela àrvore e encontrar o nó pai correto.
    struct arvbin *pai = NULL;
    struct arvbin *tmp = Busca_arvbin(valor, &pai);

    if(root == NULL) return NULL; // Caso a árvores esteja vazia.

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
    double tempo = 0;
    clock_t begin = clock();

    // Operando o Arquivo de Instâncias.
    char filename[20]; // Variável para armazenar o nome do arquivo.
    snprintf(filename, sizeof(filename), "instancias/%d", instancia_num); // Formatando a string conforme a instância passada e armazenando em filename.
    
    // Lendo o arquivo de instâncias.
    FILE *arq = fopen(filename, "r");
    if(!arq){
        printf("\nErro ao abrir o arquivo!");
        return -1;
    }

    // Variáveis para armazenar as operações que serão realizadas.
    char op;
    int valor;

    // Lendo o arquivo linha por linha e realizando as operações.
    while (fscanf(arq, " %c %d", &op, &valor) == 2) {
        if (op == 'I') {
            Inserir_bin(valor); // Realiza a inserção.
        } else if (op == 'R') {
            Remover_bin(valor); // Realiza a remoção.
        }
    }

    fclose(arq); // Fechando o arquivo após a leitura  
    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    // Operando o Arquivo de Instâncias.
    char filename[20]; // Variável para armazenar o nome do arquivo.
    snprintf(filename, sizeof(filename), "instancias/%d", instancia_num); // Formatando a string conforme a instância passada e armazenando em filename.
    
    // Lendo o arquivo de instâncias.
    FILE *arq = fopen(filename, "r");
    if(!arq){
        printf("\nErro ao abrir o arquivo!");
        return -1;
    }

    // Variáveis para armazenar as operações que serão realizadas.
    char op;
    int valor;

    // Lendo o arquivo linha por linha e realizando as operações.
    while (fscanf(arq, " %c %d", &op, &valor) == 2) {
        if (op == 'I') {
            Inserir_bin(valor); // Realiza a inserção.
        } else if (op == 'R') {
            Remover_bin(valor); // Realiza a remoção.
        }
    }

    fclose(arq); // Fechando o arquivo após a leitura  
    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}