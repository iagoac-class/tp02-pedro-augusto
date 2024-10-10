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
    tmp->esq = tmp->dir = 0;

    return tmp;
}

// Função para buscar um nó na árvore binária.
struct arvbin *Busca_arvbin(int valor){
    struct arvbin *tmp = root;
    // Caso root == NULL, a árvore está vazia.
    if(root == NULL){
        return root;
    }

    // Enquanto o valor desejado não for encontrado e o nó não for NULO, continua percorrendo a árvore.
    while(tmp->valor != valor && tmp->valor != NULL){
        if(valor == tmp->valor){
            return tmp;
        }else{
            if(valor > tmp->valor){
                tmp = tmp->dir;
            }else if(valor < tmp->valor){
                tmp = tmp->esq;
            }
        }
    }

    // Caso o valor não seja encontrado na árvore, a função retorna NULL.
    return tmp;
}

// Função para inserir um nó na árvore binária.
struct arvbin *Inserir_bin(int valor){
    // Nó a ser inserido na árvore binária.
    struct arvbin *no_inserir = Novo_no(valor);

    // Posição em que o nó deve ser inserido.
    struct arvbin *pos_inserir = Busca_arvbin(valor);
    
    if(pos_inserir == NULL){
        pos_inserir = no_inserir;
    }

    return no_inserir;
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