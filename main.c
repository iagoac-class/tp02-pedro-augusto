#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       
#include "arvores.h"

/*TODO:
- Fazer implementação da Árvore AVL em arvores.c e arvores.h
- Fazer uma função para desalocar a memória após uso do programa

*ISSUES:
- Erro de segmentação quando executamos a instância 1. (Provavelmente acontece pela falta de uma função que desaloque memória após o uso).

*/


/*
double arvore_balanceada(int instancia_num) {
    double tempo = 0;
    clock_t begin = clock();

    
    clock_t end = clock();
    // calcula o tempo decorrido encontrando a diferença (end - begin) e
    // dividindo a diferença por CLOCKS_PER_SEC para converter em segundos
    tempo += (double)(end - begin) / CLOCKS_PER_SEC;
    return (tempo);
}
*/


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
    
    double tempo_n_balanceada = arvore_binaria(instancia_num);
  //  double tempo_balanceada = arvore_balanceada(instancia_num);

    

    
    printf("%f\n", tempo_n_balanceada);

    return (1);
}