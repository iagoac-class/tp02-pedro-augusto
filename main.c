#include <stdio.h>
#include <stdlib.h>
#include "arvores.h"

int main(int argc, char* argv[]) {
    // Verifica se um argumento foi passado
    if (argc < 2) {
        printf("Por favor, forneça um número de instância como argumento.\n");
        return 1;
    }

    ///////////////////////////////////////////////////////////
    /////////////////// Leitor de instâncias //////////////////
    ///////////////// Não deve ser modificado /////////////////
    ///////////////////////////////////////////////////////////
    int instancia_num = atoi(argv[1]);
    if (instancia_num <= 0 || instancia_num > 10) {
        printf("Para executar o código, digite ./arvores x\n \nonde x é um número entre 1 e 10 que simboliza a instância utilizada\n");
        exit(0);
    }
    
    double tempo_n_balanceada = arvore_binaria(instancia_num);
    double tempo_balanceada = arvore_balanceada(instancia_num);

    // Exibe os tempos de cada árvore.
    printf("Tempo da árvore não balanceada: %f\n", tempo_n_balanceada);
    printf("Tempo da árvore balanceada: %f\n", tempo_balanceada);

    return 0;
}
