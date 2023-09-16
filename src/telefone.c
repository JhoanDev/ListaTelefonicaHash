#include "hashdobra.c"
struct telefone
{
    char nome[50];
    char email[50];
    char numero[16];
};

Telefone preenchedados()
{
    Telefone novo;
    printYELLOW("Insira o nome: ");
    scanf(" %[^\n]s", novo.nome);
    corrige_nome(novo.nome);
    printYELLOW("Insira o email: ");
    scanf(" %[^\n]s", novo.email);
    while (!verificaemail(novo.email))
    {
        printRED("Por favor insira um email valido, ex:(nomesilva@hotgmail.com)\n");
        printYELLOW("Insira o email: ");
        scanf(" %[^\n]s", novo.email);
    }
    printYELLOW("Insira o numero de telefone (apenas numeros e incluindo o ddd e o 9): ");
    scanf(" %[^\n]s", novo.numero);
    while (!verificanumerotelefone(novo.numero))
    {
        printRED("Por favor insira um telefone valido, ex:(84923435465)\n");
        printYELLOW("Insira o numero: ");
        scanf(" %[^\n]s", novo.numero);
    }
    formatanumerotelefone(novo.numero);
    return novo;
}

int colisao(Telefone *agenda, int indice)
{
    return agenda[indice].nome[0] != '\0'; // Se o nome não estiver vazio, o índice está ocupado
}

int compara(Telefone *agenda, int atual, int buscado)
{
    return strcmp(agenda[atual].email, agenda[buscado].email) == 0;
}

void cadastra(Telefone *agenda, Telefone contato)
{
    int codigohash = Dobra(contato.email);
    printf("\n");
    if (colisao(agenda, codigohash))
    {
        int novoindice = SondagemLinear(agenda, codigohash);
        agenda[novoindice] = contato;
        printGREEN("Contato adicionado com sucesso.\n");
    }
    else
    {
        agenda[codigohash] = contato;
        printGREEN("Contato adicionado com sucesso.\n");
    }
}

void listarcontatos(Telefone *agenda)
{
    printGREEN("Lista de Contatos:\n\n");
    int qnt = 1;
    for (int i = 0; i < 32; i++)
    {
        if (agenda[i].nome[0] != '\0')
        {
            printf("Contato [%d]\n", qnt++);
            printf("Nome: %s\n", agenda[i].nome);
            printf("Email: %s\n", agenda[i].email);
            printf("Número: %s\n", agenda[i].numero);
            printf("\n");
        }
    }
}

int buscarcontato(Telefone *agenda)
{
    char email[50];
    printYELLOW("Insira o email do contato que deseja buscar: ");
    scanf(" %[^\n]s", email);
    while (!verificaemail(email))
    {
        printRED("Por favor insira um email valido, ex:(nomesilva@hotgmail.com)\n");
        printYELLOW("Insira o email: ");
        scanf(" %[^\n]s", email);
    }
    int indice = SondagemLinearBusca(agenda, Dobra(email));
    return indice;
}

int importarcontatos(Telefone *agenda, char *caminho)
{
    printYELLOW("Insira o nome do arquivo a ser importado: ");
    char nomearq[20];
    scanf(" %[^\n]s", nomearq);

    // Crie o nome do arquivo completo com caminho e extensão
    char nomecomtxt[100]; // Tamanho suficiente para acomodar o nome e a extensão .txt
    sprintf(nomecomtxt, "%s%s.txt", caminho, nomearq);

    FILE *importa = fopen(nomecomtxt, "r");
    if (importa == NULL)
    {
        printRED("Erro ao abrir o arquivo para importação.");
        return 0;
    }
    char linha[100];
    int i = 0;
    Telefone contato;
    while (fgets(linha, 100, importa) != NULL)
    {
        sscanf(linha, "Nome: %[^\n]", contato.nome);
        fgets(linha, 100, importa);
        sscanf(linha, "Email: %[^\n]", contato.email);
        fgets(linha, 100, importa);
        sscanf(linha, "Número: %[^\n]", contato.numero);
        fgets(linha, 100, importa);
        cadastra(agenda, contato);
        i++;
    }
    fclose(importa);
    return i;
}

void exportarcontatos(Telefone *agenda, char *caminho)
{
    printYELLOW("Insira o nome que deseja em seu arquivo: ");
    char nomearq[20];
    scanf(" %[^\n]s", nomearq);
    // Adicione a extensão .txt ao nome do arquivo
    char nomecomtxt[100]; // Tamanho suficiente para acomodar o nome e a extensão .txt
    sprintf(nomecomtxt, "%s%s.txt", caminho, nomearq);

    FILE *exporta = fopen(nomecomtxt, "w");
    if (exporta == NULL)
    {
        printRED("Erro ao criar o arquivo.");
        exit(1);
    }

    // Agora você pode usar o arquivo 'exporta' para escrever os contatos
    // Certifique-se de escrever os contatos na forma desejada no arquivo

    // Por exemplo:
    for (int i = 0; i < 32; i++)
    { // Supondo que sua tabela hash tenha 100 elementos
        if (agenda[i].nome[0] != '\0')
        {
            fprintf(exporta, "Nome: %s\n", agenda[i].nome);
            fprintf(exporta, "Email: %s\n", agenda[i].email);
            fprintf(exporta, "Número: %s\n", agenda[i].numero);
            fprintf(exporta, "\n");
        }
    }

    fclose(exporta);
}
