#include "./telefone/telefone.c"

int main(void)
{
    char opc, volta;
    Telefone *agenda = (Telefone *)malloc(MAX * sizeof(Telefone));
    if (agenda == NULL)
    {
        print_red("[ERRO]");
        exit(1);
    }
    char *caminho = "../data/";
    int qntcontatos = 0;
    while (opc != OPCAO8)
    {
        menu();
        opc = le_opcao(OPCAO1, OPCAO8);
        switch (opc)
        {
        case OPCAO1:
            if (qntcontatos == 32)
            {
                print_red("Sua agenda esta cheia!\n\n");
                break;
            }
            print_yellow("Voce quer mesmo cadastrar um contato? 1-(Sim) 2-(Nao)\n");
            volta = le_opcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                Telefone contato = preenche_dados();
                cadastra(agenda, contato);
                print_green("Contato adicionado com sucesso.\n");
                qntcontatos++;
            }
            else
                break;
            break;
        case OPCAO2:
            if (qntcontatos == 0)
            {
                print_red("Sua agenda esta vazia!\n\n");
                break;
            }
            print_yellow("Voce quer mesmo listar os contatos? 1-(Sim) 2-(Nao)\n");
            volta = le_opcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                listar_contatos(agenda);
            else
                break;
            break;
        case OPCAO3:
            if (qntcontatos == 0)
            {
                print_red("Sua agenda esta vazia!\n\n");
                break;
            }
            print_yellow("Voce quer mesmo buscar um contato? 1-(Sim) 2-(Nao)\n");
            volta = le_opcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                int indice = buscar_contato(agenda);
                if (indice == -1)
                    print_red("Contato nao esta na agenda!\n\n");
                else
                {
                    print_green("Contato encontrado!!\n\n");
                    printf("Nome: %s\n", agenda[indice].nome);
                    printf("email: %s\n", agenda[indice].email);
                    printf("Numero: %s\n", agenda[indice].numero);
                }
            }
            else
                break;
            break;
        case OPCAO4:
            print_yellow("Voce quer mesmo exportar contatos? 1-(Sim) 2-(Nao)\n");
            volta = le_opcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                exportar_contatos(agenda, caminho);
            else
                break;
            break;
        case OPCAO5:
            print_yellow("Voce quer mesmo importar contatos? 1-(Sim) 2-(Nao)\n");
            volta = le_opcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                limpar_agenda(agenda);
                qntcontatos = importar_contatos(agenda, caminho);
            }
            else
                break;
            break;
        case OPCAO6:
            print_yellow("Voce quer mesmo apagar um contato? 1-(Sim) 2-(Nao)\n");
            volta = le_opcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                apaga_contato(agenda);
                qntcontatos -= 1;
                reorganiza_hash(agenda);
            }
            else
                break;
            break;
        case OPCAO7:
            print_yellow("Voce quer mesmo editar um contato? 1-(Sim) 2-(Nao)\n");
            volta = le_opcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                editar_contato(agenda);
            else
                break;
            break;
        case OPCAO8:
            print_yellow("Voce quer mesmo sair do programa? 1-(Sim) 2-(Nao)\n");
            volta = le_opcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                print_green("Obrigado por utilizar meu programa!\n");
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