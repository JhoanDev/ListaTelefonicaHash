#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para converter uma string em uma sequência binária e retornar a string binária
char *stringParaBinario(const char *texto) {
    int i, j;
    int pos = 0; // Variável de posição na string binária

    // Calcula o tamanho necessário da string binária
    int tamanhoBinario = 8 * strlen(texto) + 1;

    // Aloca memória dinamicamente para a string binária
    char *binario = (char *)malloc(tamanhoBinario);

    if (binario == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(1);
    }

    for (i = 0; texto[i] != '\0'; i++) {
        // Para cada caractere na string
        char caractere = texto[i];
        // Converte o caractere em seu valor binário usando operações de bits
        for (j = 7; j >= 0; j--) {
            // Testa o j-ésimo bit do caractere e coloca '0' ou '1' na string binária
            binario[pos++] = (caractere & (1 << j)) ? '1' : '0';
        }
    }
    binario[pos] = '\0'; // Adiciona o caractere nulo ao final da string binária

    return binario;
}

// Função para dobrar a string binária de acordo com a lógica especificada
char *dobrarStringBinaria(const char *binario) {
    int tamanho = strlen(binario);
    int novoTamanho = (tamanho / 5 + (tamanho % 5 != 0)) * 5; // Ajusta o tamanho para ser múltiplo de 5
    char *resultado = (char *)malloc(novoTamanho + 1); // +1 para o caractere nulo
    if (resultado == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(1);
    }

    int i, j;
    char temp[6] = "00000"; // Inicializa um grupo de zeros
    for (i = 0; i < novoTamanho; i += 5) {
        for (j = 0; j < 5; j++) {
            temp[j] = (i + j < tamanho) ? binario[i + j] : '0';
        }
        if (i > 0) {
            for (j = 0; j < 5; j++) {
                temp[j] = (temp[j] == binario[i + j]) ? '0' : '1';
            }
        }
        resultado[i / 5] = temp[0];
    }
    resultado[i / 5] = '\0'; // Adiciona o caractere nulo ao final

    return resultado;
}

int main() {
    const char *texto = "asdasd";
    char *binario = stringParaBinario(texto);
    char *resultado = dobrarStringBinaria(binario);

    // Imprime o resultado
    printf("String Binária: %s\n", binario);
    printf("Resultado: %s\n", resultado);

    // Libera a memória alocada
    free(binario);
    free(resultado);

    return 0;
}
