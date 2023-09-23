#include "../hashdobra/hashdobra.c"

struct telefone
{
    char nome[50];
    char email[50];
    char numero[16];
};

Telefone preenche_dados()
{
    Telefone novo;
    print_yellow("Insira o nome: ");
    scanf(" %[^\n]s", novo.nome);
    corrige_nome(novo.nome);
    print_yellow("Insira o email: ");
    scanf(" %[^\n]s", novo.email);
    while (!verifica_email(novo.email))
    {
        print_red("Por favor insira um email valido, ex:(nomesilva@hotgmail.com)\n");
        print_yellow("Insira o email: ");
        scanf(" %[^\n]s", novo.email);
    }
    print_yellow("Insira o numero de telefone (apenas numeros e incluindo o ddd e o 9): ");
    scanf(" %[^\n]s", novo.numero);
    while (!verifica_numero_telefone(novo.numero))
    {
        print_red("Por favor insira um telefone valido, ex:(84923435465)\n");
        print_yellow("Insira o numero: ");
        scanf(" %[^\n]s", novo.numero);
    }
    formata_numero_telefone(novo.numero);
    return novo;
}

int colisao(Telefone *agenda, int indice)
{
    return verifica_email(agenda[indice].email);
}

int compara(Telefone *agenda, int atual, char email[])
{
    return (strcmp(agenda[atual].email, email) == 0);
}

void cadastra(Telefone *agenda, Telefone contato)
{
    int codigohash = dobra(contato.email);
    if (colisao(agenda, codigohash))
    {
        int novoindice = sondagem_linear(agenda, codigohash);
        agenda[novoindice] = contato;
    }
    else
    {
        agenda[codigohash] = contato;
    }
}

void listar_contatos(Telefone *agenda)
{
    print_green("Lista de Contatos:\n\n");
    int qnt = 1;
    for (int i = 0; i < 32; i++)
    {
        if (verifica_email(agenda[i].email))
        {
            printf("Contato [%d]\n", qnt++);
            printf("Nome: %s\n", agenda[i].nome);
            printf("Email: %s\n", agenda[i].email);
            printf("Número: %s\n", agenda[i].numero);
            printf("\n");
        }
    }
}

int buscar_contato(Telefone *agenda)
{
    char email[50];
    print_yellow("Insira o email do contato que deseja buscar: ");
    scanf(" %[^\n]s", email);
    while (!verifica_email(email))
    {
        print_red("Por favor insira um email valido, ex:(nomesilva@hotgmail.com)\n");
        print_yellow("Insira o email: ");
        scanf(" %[^\n]s", email);
    }
    int hash = dobra(email);
    int indice = sondagem_linear_busca(agenda, hash, email);
    return indice;
}

int importar_contatos(Telefone *agenda, char *caminho)
{
    print_yellow("Insira o nome do arquivo a ser importado: ");
    char nomearq[20];
    scanf(" %[^\n]s", nomearq);
    char nomecomtxt[100];
    sprintf(nomecomtxt, "%s%s.txt", caminho, nomearq);
    FILE *importa = fopen(nomecomtxt, "r");
    if (importa == NULL)
    {
        print_red("Erro ao abrir o arquivo para importação.");
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
    print_green("Contatos importados com sucesso.\n");
    fclose(importa);
    return i;
}

void exportar_contatos(Telefone *agenda, char *caminho)
{
    print_yellow("Insira o nome que deseja em seu arquivo: ");
    char nomearq[20];
    scanf(" %[^\n]s", nomearq);
    char nomecomtxt[100];
    sprintf(nomecomtxt, "%s%s.txt", caminho, nomearq);
    FILE *exporta = fopen(nomecomtxt, "w");
    if (exporta == NULL)
    {
        print_red("Erro ao criar o arquivo.");
        exit(1);
    }

    for (int i = 0; i < 32; i++)
    {
        if (verifica_email(agenda[i].email))
        {
            fprintf(exporta, "Nome: %s\n", agenda[i].nome);
            fprintf(exporta, "Email: %s\n", agenda[i].email);
            fprintf(exporta, "Número: %s\n", agenda[i].numero);
            fprintf(exporta, "\n");
        }
    }
    fclose(exporta);
}

void gera_contatos(char *caminho)
{
    print_yellow("Insira o nome que deseja em seu arquivo: ");
    char nomearq[20];
    scanf(" %[^\n]s", nomearq);
    char nomecomtxt[100];
    sprintf(nomecomtxt, "%s%s.txt", caminho, nomearq);
    FILE *exporta = fopen(nomecomtxt, "w");
    if (exporta == NULL)
    {
        print_red("Erro ao criar o arquivo.");
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
void apaga_contato(Telefone *agenda)
{
    print_yellow("Insira o email do contato que deseja apagar: ");
    char email[50];
    scanf(" %[^\n]s", email);
    while (!verifica_email(email))
    {
        print_red("Por favor insira um email valido, ex:(nomesilva@hotgmail.com)\n");
        print_yellow("Insira o email: ");
        scanf(" %[^\n]s", email);
    }
    int indice = sondagem_linear_busca(agenda, dobra(email), email);
    if (indice != -1)
    {
        strcpy(agenda[indice].nome, "");
        strcpy(agenda[indice].email, "");
        strcpy(agenda[indice].numero, "");
        print_green("Contato apagado com sucesso.\n");
    }
    else
    {
        print_red("Contato não encontrado na agenda.\n");
    }
}

void reorganiza_hash(Telefone *agenda)
{
    Telefone *novaAgenda = (Telefone *)malloc(MAX * sizeof(Telefone));
    if (novaAgenda == NULL)
    {
        print_red("Erro de alocação de memória.");
        exit(1);
    }
    for (int i = 0; i < MAX; i++)
    {
        if (verifica_email(agenda[i].email))
        {
            int codigohash = dobra(agenda[i].email);
            int novoindice = sondagem_linear(novaAgenda, codigohash);
            novaAgenda[novoindice] = agenda[i];
        }
    }
    agenda = novaAgenda;
    free(novaAgenda);
}

void limpar_agenda(Telefone *agenda)
{
    for (int i = 0; i < 32; i++)
    {
        strcpy(agenda[i].nome, "");
        strcpy(agenda[i].email, "");
        strcpy(agenda[i].numero, "");
    }
    print_green("Agenda limpa com sucesso(pronto para a importação).\n");
}

void editar_contato(Telefone *agenda)
{
    char email[50];
    print_yellow("Insira o email do contato que deseja editar: ");
    scanf(" %[^\n]s", email);
    // Verificar se o email é válido
    while (!verifica_email(email))
    {
        print_red("Por favor insira um email válido, ex:(nomesilva@hotgmail.com)\n");
        print_yellow("Insira o email: ");
        scanf(" %[^\n]s", email);
    }
    int indice = sondagem_linear_busca(agenda, dobra(email), email);
    if (indice != -1)
    {
        printf("Contato Encontrado:\n");
        printf("Nome: %s\n", agenda[indice].nome);
        printf("Email: %s\n", agenda[indice].email);
        printf("Número: %s\n", agenda[indice].numero);
        print_yellow("\nQual campo deseja editar?\n");
        print_yellow("1. Nome\n");
        print_yellow("2. Email\n");
        print_yellow("3. Número de Telefone\n");
        print_yellow("4. Editar todos os campos\n");
        char opcao;
        opcao = le_opcao(OPCAO1, OPCAO4);
        switch (opcao)
        {
        case OPCAO1:
            print_yellow("Editar Nome: ");
            scanf(" %[^\n]s", agenda[indice].nome);
            corrige_nome(agenda[indice].nome);
            break;
        case OPCAO2:
            print_yellow("Editar Email: ");
            scanf(" %[^\n]s", agenda[indice].email);
            while (!verifica_email(agenda[indice].email))
            {
                print_red("Por favor insira um email válido, ex:(nomesilva@hotgmail.com)\n");
                print_yellow("Editar Email: ");
                scanf(" %[^\n]s", agenda[indice].email);
            }
            reorganiza_hash(agenda); // reoganizando pois mudou a chave (email);
            break;
        case OPCAO3:
            print_yellow("Editar Número de Telefone (apenas números e incluindo o DDD e o 9): ");
            scanf(" %[^\n]s", agenda[indice].numero);
            while (!verifica_numero_telefone(agenda[indice].numero))
            {
                print_red("Por favor insira um número de telefone válido, ex:(84923435465)\n");
                print_yellow("Editar Número: ");
                scanf(" %[^\n]s", agenda[indice].numero);
            }
            formata_numero_telefone(agenda[indice].numero);
            break;
        case OPCAO4:
            print_yellow("Editar Nome: ");
            scanf(" %[^\n]s", agenda[indice].nome);
            corrige_nome(agenda[indice].nome);

            print_yellow("Editar Email: ");
            scanf(" %[^\n]s", agenda[indice].email);
            while (!verifica_email(agenda[indice].email))
            {
                print_red("Por favor insira um email válido, ex:(nomesilva@hotgmail.com)\n");
                print_yellow("Editar Email: ");
                scanf(" %[^\n]s", agenda[indice].email);
            }

            print_yellow("Editar Número de Telefone (apenas números e incluindo o DDD e o 9): ");
            scanf(" %[^\n]s", agenda[indice].numero);
            while (!verifica_numero_telefone(agenda[indice].numero))
            {
                print_red("Por favor insira um número de telefone válido, ex:(84923435465)\n");
                print_yellow("Editar Número: ");
                scanf(" %[^\n]s", agenda[indice].numero);
            }
            formata_numero_telefone(agenda[indice].numero);
            reorganiza_hash(agenda); // reoganizando pois mudou a chave (email);
            break;
        default:
            print_red("Opção inválida.\n");
            break;
        }
        print_green("Contato editado com sucesso.\n");
    }
    else
    {
        print_red("Contato não encontrado na agenda.\n");
    }
}