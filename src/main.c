#include "./telefone/telefone.c"

int main(void)
{
    char opc, volta;
    Telefone *agenda = (Telefone *)malloc(MAX * sizeof(Telefone));
    if (agenda == NULL)
    {
        printRED("[ERRO]");
        exit(1);
    }
    char *caminho = "../data/";
    int qntcontatos = 0;
    while (opc != OPCAO8)
    {
        menu();
        opc = LeOpcao(OPCAO1, OPCAO8);
        switch (opc)
        {
        case OPCAO1:
            if (qntcontatos == 32)
            {
                printRED("Sua agenda esta cheia!\n\n");
                break;
            }
            printYELLOW("Voce quer mesmo cadastrar um contato? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                Telefone contato = preenchedados();
                cadastra(agenda, contato);
                printGREEN("Contato adicionado com sucesso.\n");
                qntcontatos++;
            }
            else
                break;
            break;
        case OPCAO2:
            if (qntcontatos == 0)
            {
                printRED("Sua agenda esta vazia!\n\n");
                break;
            }
            printYELLOW("Voce quer mesmo listar os contatos? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                listarcontatos(agenda);
            else
                break;
            break;
        case OPCAO3:
            if (qntcontatos == 0)
            {
                printRED("Sua agenda esta vazia!\n\n");
                break;
            }
            printYELLOW("Voce quer mesmo buscar um contato? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                int indice = buscarcontato(agenda);
                if (indice == -1)
                    printRED("Contato nao esta na agenda!\n\n");
                else
                {
                    printGREEN("Contato encontrado!!\n\n");
                    printf("Nome: %s\n", agenda[indice].nome);
                    printf("email: %s\n", agenda[indice].email);
                    printf("Numero: %s\n", agenda[indice].numero);
                }
            }
            else
                break;
            break;
        case OPCAO4:
            printYELLOW("Voce quer mesmo exportar contatos? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                exportarcontatos(agenda, caminho);
            else
                break;
            break;
        case OPCAO5:
            printYELLOW("Voce quer mesmo importar contatos? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                limparagenda(agenda);
                qntcontatos = importarcontatos(agenda, caminho);
            }
            else
                break;
            break;
        case OPCAO6:
            printYELLOW("Voce quer mesmo apagar um contato? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                apagacontato(agenda);
                agenda = reorganizahash(agenda);
            }
            else
                break;
            break;
        case OPCAO7:
            printYELLOW("Voce quer mesmo editar um contato? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                editarcontato(agenda);
            else
                break;
            break;
        case OPCAO8:
            printYELLOW("Voce quer mesmo sair do programa? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                printGREEN("Obrigado por utilizar meu programa!\n");
            else
                opc = 0;
            break;
        default:
            break;
        }
    }
    free(agenda);
    return 0;
}