#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

// Função para criar um novo nó na árvore binária.
struct arvbin *Novo_no(int valor){
    // Alocamos o espaço de uma posição da struct para armazenar o nó, definimos o valor do nó com o parâmetro passado e iniciamos suas subárvores com NULL.
    struct arvbin *tmp = (struct arvbin*)malloc(sizeof(struct arvbin));
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
    struct arvbin *tmp = root;
    struct arvbin *pai = NULL;
    tmp = Busca_arvbin(valor, &pai);

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

double arvore_binaria(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}

double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}


int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = -1;
    instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    // Iniciando a raiz da árvore como NULL. (Árvore começa vazia).
    root = NULL;

    double tempo_n_balanceada = arvore_binaria(instancia_num);
    double tempo_balanceada = arvore_balanceada(instancia_num);

    

    
    printf("%f\n%f\n", tempo_n_balanceada, tempo_balanceada);

    return (1);
}