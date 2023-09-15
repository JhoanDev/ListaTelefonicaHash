#include "sistema.c"
#include "telefone.h"

struct telefone
{
    char nome[50];
    char email[50];
    int numero;
};


char *stringParaBinario(const char *texto)
{
    int i, j;
    int pos = 0; // Variável de posição 
    // Calcula o tamanho necessário
    int tamanhoBinario = 8 * strlen(texto) + 1;
    char *binario = (char *)malloc(tamanhoBinario);
    if (binario == NULL)
    {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(1);
    }
    for (i = 0; texto[i] != '\0'; i++)
    {
        // Para cada caractere na string
        char caractere = texto[i];
        // Converte o caractere em seu valor binário usando operações de bits
        for (j = 7; j >= 0; j--)
        {
            // Testa o j-ésimo bit do caractere e coloca '0' ou '1' na string binária
            binario[pos++] = (caractere & (1 << j)) ? '1' : '0';
        }
    }
    binario[pos] = '\0'; // Adiciona o caractere nulo ao final da string binária
    int diferenca = strlen(binario) % 5;
    if (diferenca != 0)
    {
        // Crie uma nova string com zeros à esquerda
        int novoTamanho = strlen(binario) + (5 - diferenca);
        char *novoBinario = (char *)malloc((novoTamanho + 1) * sizeof(char));
        if (novoBinario == NULL)
        {
            fprintf(stderr, "Erro de alocação de memória.\n");
            exit(1);
        }
        // Preencha com zeros à esquerda
        for (i = 0; i < 5 - diferenca; i++)
        {
            novoBinario[i] = '0';
        }
        // Copie os dígitos binários originais
        for (i = 5 - diferenca; i < novoTamanho; i++)
        {
            novoBinario[i] = binario[i - (5 - diferenca)];
        }
        novoBinario[novoTamanho] = '\0'; // Adicione o caractere nulo

        free(binario);         // Libere a memória da string binária original
        binario = novoBinario; // Atualize o ponteiro com a nova string
    }
    return binario;
}
