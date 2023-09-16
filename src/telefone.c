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

void cadastra(Telefone *agenda)
{
    Telefone contato = preenchedados();
    int codigohash = Dobra(contato.email);
    printf("Codigo %d\n\n", codigohash);
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