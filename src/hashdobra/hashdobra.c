#include "hashdobra.h"
#include "../system/sistema.c"

int dobra(char *texto)
{
    char *bin = string_para_binario(texto);
    int tamanhoDaString = strlen(bin);
    int tamanhoDoSegmento = 5;
    int i = 0;
    char segmento[tamanhoDoSegmento + 1];
    char *resultado = (char *)malloc(5 * sizeof(char));
    if (resultado == NULL)
    {
        print_red("Erro de alocação de memória.");
        exit(1);
    }
    strncpy(segmento, bin + i, tamanhoDoSegmento);
    strncpy(resultado, bin + i + tamanhoDoSegmento, tamanhoDoSegmento);
    resultado = soma_diferente(segmento, resultado);
    for (i = tamanhoDoSegmento * 2; i < tamanhoDaString; i += tamanhoDoSegmento)
    {
        strncpy(segmento, bin + i, tamanhoDoSegmento);
        resultado = soma_diferente(resultado, segmento);
    }
    int hash = binario_para_inteiro(resultado);
    return hash;
}

char *string_para_binario(const char *texto)
{
    int i, j;
    int pos = 0;
    int tamanhoBinario = 8 * strlen(texto) + 1;
    char *binario = (char *)malloc(tamanhoBinario);
    if (binario == NULL)
    {
        print_red("Erro de alocação de memória.");
        exit(1);
    }
    for (i = 0; texto[i] != '\0'; i++)
    {
        char caractere = texto[i];
        for (j = 7; j >= 0; j--)
        {
            binario[pos++] = (caractere & (1 << j)) ? '1' : '0';
        }
    }
    binario[pos] = '\0';
    int diferenca = strlen(binario) % 5;
    if (diferenca != 0)
    {
        int novoTamanho = strlen(binario) + (5 - diferenca);
        char *novoBinario = (char *)malloc((novoTamanho + 1) * sizeof(char));
        if (novoBinario == NULL)
        {
            print_red("Erro de alocação de memória.");
            exit(1);
        }
        for (i = 0; i < 5 - diferenca; i++)
        {
            novoBinario[i] = '0';
        }
        for (i = 5 - diferenca; i < novoTamanho; i++)
        {
            novoBinario[i] = binario[i - (5 - diferenca)];
        }
        novoBinario[novoTamanho] = '\0';
        free(binario);
        binario = novoBinario;
    }
    return binario;
}

char *soma_diferente(char *dobra, char *naodobra)
{
    int tamanho = 5;
    int i = 0, j = tamanho - 1;
    char *resultado = (char *)malloc((tamanho + 1) * sizeof(char));
    if (resultado == NULL)
    {
        print_red("Erro de alocação de memória.");
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

int binario_para_inteiro(char *binario)
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

int sondagem_linear(Telefone *agenda, int indice)
{
    int novoindice = indice;
    int i = 1;
    while (colisao(agenda, novoindice))
    {
        novoindice = (indice + i) % 32;
        i++;
    }
    return novoindice;
}

int sondagem_linear_busca(Telefone *agenda, int indice, char email[])
{
    int indicebuscado = indice;
    int i = 1;
    while (!compara(agenda, indicebuscado, email))
    {
        indicebuscado = (indice + i) % 32;
        if (i >= 32)
            return -1;
        i++;
    }
    return indicebuscado;
}
