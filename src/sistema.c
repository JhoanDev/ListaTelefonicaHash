#include "sistema.h"

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define WHITE "\x1B[0m"

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

char LeOpcao(char menorValor, char maiorValor)
{
    char op;
    char entrada[100];
    char text[50];
    while (1)
    {
        printf("Digite sua opcao: ");
        scanf(" %[^\n]", entrada);
        op = entrada[0];
        if (op >= menorValor && op <= maiorValor && strlen(entrada) == 1)
        {
            LimpaBuffer();
            break;
        }
        else
        {
            sprintf(text, "Opcao invalida. A opcao deve estar entre %c e %c.\n", menorValor, maiorValor);
            printRED(text);
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

int verificaemail(const char email[])
{
    int i, at_count = 0, dot_count = 0;
    int len = strlen(email);
    for (i = 0; i < len; i++)
    {
        if (email[i] == '@')
            at_count++;
        else if (email[i] == '.')
            dot_count++;
    }
    // Verificar se há um único '@' e pelo menos um '.' após o '@'
    if (at_count == 1 && dot_count >= 1)
    {
        // Verificar se termina com ".com"
        if (strcmp(email + len - 4, ".com") == 0)
        {
            return 1;
        }
    }
    return 0;
}

int verificanumerotelefone(const char numero[])
{
    int len = strlen(numero);
    int possuiNove = 0; // Variável para verificar se o número contém o dígito "9"
    // Verificar se o número de telefone tem exatamente 11 dígitos numéricos
    if (len != 11)
    {
        return 0;
    }
    // Verificar se todos os caracteres são dígitos numéricos
    for (int i = 0; i < len; i++)
    {
        if (!isdigit(numero[i]))
            return 0;
        // Verificar se o número contém o dígito "9"
        if (numero[i] == '9')
            possuiNove = 1;
    }
    // Verificar se o número contém pelo menos um "9"
    if (!possuiNove)
    {
        return 0;
    }
    return 1;
}

void formatanumerotelefone(char numero[])
{
    int len = strlen(numero);
    char numeroFormatado[20]; // Usado para armazenar o número formatado temporariamente
    sprintf(numeroFormatado, "(%c%c) %c%c%c%c%c-%c%c%c%c", numero[0], numero[1], numero[2], numero[3], numero[4], numero[5], numero[6], numero[7], numero[8], numero[9], numero[10]);
    // Copiar o número formatado de volta para o número original
    strcpy(numero, numeroFormatado);
}

void menu(void)
{
    printf("Menu:\n");
    printf("========================================\n");
    printf("[1] Criar contato\n");
    printf("[2] Listar contatos\n");
    printf("[3] Buscar contato\n");
    printf("[4] Exportar contatos\n");
    printf("[5] Importar contatos\n");
    printf("[6] Apagar contato\n");
    printf("[7] Editar contato\n");
    printf("[8] Sair\n");
    printf("========================================\n");
}

void printGREEN(char *text)
{
    printf("%s%s%s", GREEN, text, WHITE);
}

void printYELLOW(char *text)
{
    printf("%s%s%s", YELLOW, text, WHITE);
}

void printRED(char *text)
{
    printf("%s%s%s", RED, text, WHITE);
}

