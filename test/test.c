#include <stdio.h>  //funções basicas da linguagem c
#include <stdlib.h> //para fazer alocação dinamica
#include <string.h> //para usar strings
#include <ctype.h>  //manipulação de caracteres

#define MaxNome 100
#define Leitos 25
#define codigohospital 77

typedef union document Document;
typedef struct pacientes Pacientes;
typedef struct listapacientes Listapacientes;
typedef struct hospital Hospital;

union document
{
    char cpf[15];
    char rg[12];
};

struct pacientes
{
    char nome[MaxNome];
    Document documento;
    char enfermidade[50];
    int internado; // sim == 1, nao == 0
    char receita[100];
};

struct listapacientes
{
    Pacientes *pacientes;
    struct listapacientes *next;
    struct listapacientes *prev;
};

struct hospital
{
    int codigo;
    int leitos;
    char localizacao[20];
    char nome[10];
    Listapacientes *lista;
};

Hospital *hospital_cria(void)
{
    Hospital *h = (Hospital *)malloc(sizeof(Hospital));
    h->lista = lista_cria();
    h->lista->next = NULL;
    h->lista->prev = NULL;
    h->leitos = Leitos;
    h->codigo = codigohospital;
    strcpy(h->nome, "HealCare");
    strcpy(h->localizacao, "Cidade: UmariGomes");
    return h;
}

Listapacientes *lista_cria(void)
{
    Listapacientes *l = (Listapacientes *)malloc(sizeof(Listapacientes));
    return l;
}

Pacientes preenche_paciente(void)
{
    Pacientes paciente;
    int i;
    char opcao_documento;

    printf("Digite o nome do paciente: ");
    scanf(" %[^\n]s", paciente.nome);
    // Formatando nome
    int tamanho_do_nome = strlen(paciente.nome);
    paciente.nome[0] = toupper(paciente.nome[0]); // convertendo o primeiro caractere para maiúsculo
    // Percorra os caracteres restantes e convertendo para minúsculo
    for (i = 1; i < tamanho_do_nome; i++)
    {
        paciente.nome[i] = tolower(paciente.nome[i]);
        // Verificando se o caractere anterior é um espaço em branco. Se sim, converte o caractere atual para maiúsculo
        if (paciente.nome[i - 1] == ' ')
        {
            paciente.nome[i] = toupper(paciente.nome[i]);
        }
    }

    printf("Digite a enfermidade do paciente: ");
    scanf(" %[^\n]s", paciente.enfermidade);

    printf("Digite a receita para o paciente: ");
    scanf(" %[^\n]s", paciente.receita);

    printf("Internado? (1-sim) (0-nao): ");
    scanf("%d", &paciente.internado);

    // Pedir para o usuário escolher qual documento cadastrar
    printf("Digite '1' para cadastrar o CPF ou '2' para cadastrar o RG: ");
    scanf(" %c", &opcao_documento);

    // Ler o documento escolhido pelo usuário
    if (opcao_documento == '1')
    {
        printf("Digite o CPF do paciente (XXX.YYY.ZZZ-SS): ");
        scanf(" %[^\n]s", paciente.documento.cpf);
    }
    else if (opcao_documento == '2')
    {
        printf("Digite o RG do paciente (XXX.YYY.ZZZ): ");
        scanf(" %[^\n]s", paciente.documento.rg);
    }
    else
    {
        printf("Opcao invalida.\n");
        exit(1);
    }
    return paciente;
}

void lista_add(Listapacientes *l, Pacientes paciente)
{
    // Encontrar a posição correta para inserir o novo paciente
    Listapacientes *p = l;
    while (p->next != NULL && strcmp(p->next->pacientes->nome, paciente.nome) < 0)
    {
        p = p->next;
    }
    // Criar um novo nó para o novo paciente
    Listapacientes *novo_no = (Listapacientes *)malloc(sizeof(Listapacientes));
    if (novo_no == NULL)
    {
        printf("Erro: memoria insuficiente.\n");
        exit(1);
    }
    novo_no->pacientes = (Pacientes *)malloc(sizeof(Pacientes));
    if (novo_no->pacientes == NULL)
    {
        printf("Erro: memoria insuficiente.\n");
        exit(1);
    }
    *novo_no->pacientes = paciente;

    // Inserir o novo paciente na posição correta
    novo_no->next = p->next;
    novo_no->prev = p;
    if (p->next != NULL)
    {
        p->next->prev = novo_no;
    }
    p->next = novo_no;
    return p;
}

Hospital *cadastra_paciente(Hospital *h, int *qnt)
{
    if ((*qnt) == Leitos)
    {
        printf("Capacidade máxima atingida!\n");
        exit(1);
    }
    // Adicionando o paciente na lista do hospital
    Pacientes p = preenche_paciente();
    lista_add(h->lista, p);
    (*qnt)++;
    (h->leitos)--;
    printf("Paciente cadastrado com sucesso.\n\n");
    return h;
}