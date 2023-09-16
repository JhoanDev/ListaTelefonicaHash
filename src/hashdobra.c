#include "sistema.c"
#include "hashdobra.h"

int Dobra(char *texto)
{
    char *bin = StringParaBinario(texto);
    int tamanhoDaString = strlen(bin);
    int tamanhoDoSegmento = 5;
    int i = 0;
    char segmento[tamanhoDoSegmento + 1];
    char *resultado = (char *)malloc(5 * sizeof(char));
    if (resultado == NULL)
    {
        printRED("Erro de alocação de memória.");
        exit(1);
    }
    strncpy(segmento, bin + i, tamanhoDoSegmento);
    strncpy(resultado, bin + i + tamanhoDoSegmento, tamanhoDoSegmento);
    resultado = SomaDiferente(segmento, resultado);
    for (i = tamanhoDoSegmento * 2; i < tamanhoDaString; i += tamanhoDoSegmento)
    {
        strncpy(segmento, bin + i, tamanhoDoSegmento);
        resultado = SomaDiferente(resultado, segmento);
    }
    int hash = BinarioParaInteiro(resultado);
    return hash;
}

char *StringParaBinario(const char *texto)
{
    int i, j;
    int pos = 0; // Variável de posição
    // Calcula o tamanho necessário
    int tamanhoBinario = 8 * strlen(texto) + 1;
    char *binario = (char *)malloc(tamanhoBinario);
    if (binario == NULL)
    {
        printRED("Erro de alocação de memória.");
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

char *SomaDiferente(char *dobra, char *naodobra)
{
    int tamanho = 5;
    int i = 0, j = tamanho - 1;
    char *resultado = (char *)malloc((tamanho + 1) * sizeof(char));
    if (resultado == NULL)
    {
        printRED("Erro de alocação de memória.");
        exit(1);
    }
    while (i < tamanho)
    {
        if (dobra[j] != naodobra[i])
            resultado[i] = '1';
        else
            resultado[i] = '0';
        i++;
        j--;
    }
    return resultado;
}


int BinarioParaInteiro(char *binario)
{
    int tamanho = strlen(binario);
    int resultado = 0;

    for (int i = tamanho - 1; i >= 0; i--)
    {
        if (binario[i] == '1')
        {
            resultado += (1 << (tamanho - 1 - i));
        }
    }
    free(binario);
    return resultado;
}

int SondagemLinear(Telefone *agenda, int indice){
    int novoindice = indice;
    int i = 1;
    while (colisao(agenda,novoindice)) {
        novoindice = (indice + i) % 32; // 32 é o tamanho da tabela hash
        i++;
    }
    return novoindice;
}

