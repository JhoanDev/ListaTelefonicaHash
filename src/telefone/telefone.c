#include "../hashdobra/hashdobra.c"

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
    return verificaemail(agenda[indice].email);
}

int compara(Telefone *agenda, int atual, char email[])
{
    return (strcmp(agenda[atual].email, email) == 0);
}

void cadastra(Telefone *agenda, Telefone contato)
{
    int codigohash = Dobra(contato.email);
    if (colisao(agenda, codigohash))
    {
        int novoindice = SondagemLinear(agenda, codigohash);
        agenda[novoindice] = contato;
    }
    else
    {
        agenda[codigohash] = contato;
    }
}

void listarcontatos(Telefone *agenda)
{
    printGREEN("Lista de Contatos:\n\n");
    int qnt = 1;
    for (int i = 0; i < 32; i++)
    {
        if (verificaemail(agenda[i].email))
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
    int hash = Dobra(email);
    int indice = SondagemLinearBusca(agenda, hash, email);
    return indice;
}

int importarcontatos(Telefone *agenda, char *caminho)
{
    printYELLOW("Insira o nome do arquivo a ser importado: ");
    char nomearq[20];
    scanf(" %[^\n]s", nomearq);
    char nomecomtxt[100];
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
    printGREEN("Contatos importados com sucesso.\n");
    fclose(importa);
    return i;
}

void exportarcontatos(Telefone *agenda, char *caminho)
{
    printYELLOW("Insira o nome que deseja em seu arquivo: ");
    char nomearq[20];
    scanf(" %[^\n]s", nomearq);
    char nomecomtxt[100];
    sprintf(nomecomtxt, "%s%s.txt", caminho, nomearq);

    FILE *exporta = fopen(nomecomtxt, "w");
    if (exporta == NULL)
    {
        printRED("Erro ao criar o arquivo.");
        exit(1);
    }

    for (int i = 0; i < 32; i++)
    { // Supondo que sua tabela hash tenha 100 elementos
        if (verificaemail(agenda[i].email))
        {
            fprintf(exporta, "Nome: %s\n", agenda[i].nome);
            fprintf(exporta, "Email: %s\n", agenda[i].email);
            fprintf(exporta, "Número: %s\n", agenda[i].numero);
            fprintf(exporta, "\n");
        }
    }

    fclose(exporta);
}

void geracontatos(char *caminho)
{
    printYELLOW("Insira o nome que deseja em seu arquivo: ");
    char nomearq[20];
    scanf(" %[^\n]s", nomearq);
    char nomecomtxt[100];
    sprintf(nomecomtxt, "%s%s.txt", caminho, nomearq);
    FILE *exporta = fopen(nomecomtxt, "w");
    if (exporta == NULL)
    {
        printRED("Erro ao criar o arquivo.");
        exit(1);
    }
    for (int i = 1; i <= 32; i++)
    {
        fprintf(exporta, "Nome: Contato %d\n", i);
        fprintf(exporta, "Email: contato%d@gmail.com\n", i);
        fprintf(exporta, "Número: (%d) %d%d%d%d%d-%d%d%d%d\n",
                (i % 10) + 1,
                (i % 10), (i % 10), (i % 10), (i % 10), (i % 10),
                (i % 10), (i % 10), (i % 10), (i % 10));

        fprintf(exporta, "\n");
    }
    fclose(exporta);
}
void apagacontato(Telefone *agenda)
{
    printYELLOW("Insira o email do contato que deseja apagar: ");
    char email[50];
    scanf(" %[^\n]s", email);
    while (!verificaemail(email))
    {
        printRED("Por favor insira um email valido, ex:(nomesilva@hotgmail.com)\n");
        printYELLOW("Insira o email: ");
        scanf(" %[^\n]s", email);
    }
    int indice = SondagemLinearBusca(agenda, Dobra(email), email);
    if (indice != -1)
    {
        strcpy(agenda[indice].nome, "");
        strcpy(agenda[indice].email, "");
        strcpy(agenda[indice].numero, "");
        printGREEN("Contato apagado com sucesso.\n");
    }
    else
    {
        printRED("Contato não encontrado na agenda.\n");
    }
}

void reorganizahash(Telefone *agenda)
{
    Telefone *novaAgenda = (Telefone *)malloc(MAX * sizeof(Telefone));
    if (novaAgenda == NULL)
    {
        printRED("Erro de alocação de memória.");
        exit(1);
    }
    for (int i = 0; i < MAX; i++)
    {
        if (verificaemail(agenda[i].email))
        {
            int codigohash = Dobra(agenda[i].email);
            int novoindice = SondagemLinear(novaAgenda, codigohash);
            novaAgenda[novoindice] = agenda[i];
        }
    }
    agenda = novaAgenda;
    free(novaAgenda);
}

void limparagenda(Telefone *agenda)
{
    for (int i = 0; i < 32; i++)
    {
        strcpy(agenda[i].nome, "");
        strcpy(agenda[i].email, "");
        strcpy(agenda[i].numero, "");
    }
    printGREEN("Agenda limpa com sucesso(pronto para a importação).\n");
}

void editarcontato(Telefone *agenda)
{
    char email[50];
    printYELLOW("Insira o email do contato que deseja editar: ");
    scanf(" %[^\n]s", email);
    
    // Verificar se o email é válido
    while (!verificaemail(email))
    {
        printRED("Por favor insira um email válido, ex:(nomesilva@hotgmail.com)\n");
        printYELLOW("Insira o email: ");
        scanf(" %[^\n]s", email);
    }
    
    int indice = SondagemLinearBusca(agenda, Dobra(email), email);
    if (indice != -1)
    {
        printf("Contato Encontrado:\n");
        printf("Nome: %s\n", agenda[indice].nome);
        printf("Email: %s\n", agenda[indice].email);
        printf("Número: %s\n", agenda[indice].numero);
        printYELLOW("\nQual campo deseja editar?\n");
        printYELLOW("1. Nome\n");
        printYELLOW("2. Email\n");
        printYELLOW("3. Número de Telefone\n");
        printYELLOW("4. Editar todos os campos\n");
        char opcao;
        opcao = LeOpcao(OPCAO1,OPCAO4);
        switch (opcao)
        {
            case OPCAO1:
                printYELLOW("Editar Nome: ");
                scanf(" %[^\n]s", agenda[indice].nome);
                corrige_nome(agenda[indice].nome);
                break;
            case OPCAO2:
                printYELLOW("Editar Email: ");
                scanf(" %[^\n]s", agenda[indice].email);
                while (!verificaemail(agenda[indice].email))
                {
                    printRED("Por favor insira um email válido, ex:(nomesilva@hotgmail.com)\n");
                    printYELLOW("Editar Email: ");
                    scanf(" %[^\n]s", agenda[indice].email);
                }
                reorganizahash(agenda); //reoganizando pois mudou a chave (email);
                break;
            case OPCAO3:
                printYELLOW("Editar Número de Telefone (apenas números e incluindo o DDD e o 9): ");
                scanf(" %[^\n]s", agenda[indice].numero);
                while (!verificanumerotelefone(agenda[indice].numero))
                {
                    printRED("Por favor insira um número de telefone válido, ex:(84923435465)\n");
                    printYELLOW("Editar Número: ");
                    scanf(" %[^\n]s", agenda[indice].numero);
                }
                formatanumerotelefone(agenda[indice].numero);
                break;
            case OPCAO4:
                printYELLOW("Editar Nome: ");
                scanf(" %[^\n]s", agenda[indice].nome);
                corrige_nome(agenda[indice].nome);
                
                printYELLOW("Editar Email: ");
                scanf(" %[^\n]s", agenda[indice].email);
                while (!verificaemail(agenda[indice].email))
                {
                    printRED("Por favor insira um email válido, ex:(nomesilva@hotgmail.com)\n");
                    printYELLOW("Editar Email: ");
                    scanf(" %[^\n]s", agenda[indice].email);
                }
                
                printYELLOW("Editar Número de Telefone (apenas números e incluindo o DDD e o 9): ");
                scanf(" %[^\n]s", agenda[indice].numero);
                while (!verificanumerotelefone(agenda[indice].numero))
                {
                    printRED("Por favor insira um número de telefone válido, ex:(84923435465)\n");
                    printYELLOW("Editar Número: ");
                    scanf(" %[^\n]s", agenda[indice].numero);
                }
                formatanumerotelefone(agenda[indice].numero);
                reorganizahash(agenda); //reoganizando pois mudou a chave (email);
                break;
            default:
                printRED("Opção inválida.\n");
                break;
        }
        printGREEN("Contato editado com sucesso.\n");
    }
    else
    {
        printRED("Contato não encontrado na agenda.\n");
    }
}
