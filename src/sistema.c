#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define N_OPCOES 8

#define OPCAO1 '1'
#define OPCAO2 '2'
#define OPCAO3 '3'
#define OPCAO4 '4'
#define OPCAO5 '5'
#define OPCAO6 '6'
#define OPCAO7 '7'
#define OPCAO8 '8'

void LimpaBuffer(void)
{
    int valorLido;
    do
    {
        valorLido = getchar();
    } while ((valorLido != '\n') && (valorLido != EOF));
}

int LeOpcao(int menorValor, int maiorValor)
{
    int op;
    char entrada[50];
    while (1)
    {
        printf("Digite sua opcao: ");
        scanf(" %[^\n]", entrada);
        op = entrada[0];
        if (op >= menorValor && op <= maiorValor && strlen(entrada) == 1)
        {
            LimpaBuffer();
            Beep(1200, 300);
            break;
        }
        else
        {
            printf("Opcao invalida. A opcao deve estar entre %c e %c. \n", menorValor, maiorValor);
            LimpaBuffer();
        }
    }
    return op;
}

void corrige_nome(char nome[])
{
    int tamanho_do_nome = strlen(nome);
    int i, j;
    char ultimo_caractere = ' ';

    for (i = 0, j = 0; i < tamanho_do_nome; i++)
    {
        if (isalpha(nome[i]) || nome[i] == ' ')
        {
            if (nome[i] == ' ' && ultimo_caractere == ' ')
            {
                continue;
            }
            nome[j] = nome[i];
            j++;
            ultimo_caractere = nome[i];
        }
    }
    nome[j] = '\0';
    nome[0] = toupper(nome[0]);
    for (i = 1; i < j; i++)
    {
        nome[i] = tolower(nome[i]);
        if (nome[i - 1] == ' ')
        {
            nome[i] = toupper(nome[i]);
        }
    }
    tamanho_do_nome = strlen(nome);
    if (j == 1 && nome[tamanho_do_nome] == ' ')
    {
        nome[tamanho_do_nome] = '\0';
    }
}

void menu(void)
{
    
}