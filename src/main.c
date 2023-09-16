#include "telefone.c"

#define MAX 32

int main(void)
{
    char opc, volta;
    Telefone *agenda = (Telefone*) malloc(MAX * sizeof(Telefone));
    Telefone aux;
    if (agenda == NULL)
    {
        printRED("[ERRO]");
        exit(1);
    }
    while (opc != OPCAO8)
    {
        menu();
        opc = LeOpcao(OPCAO1, OPCAO8);
        switch (opc)
        {
        case OPCAO1:
            printYELLOW("Voce quer mesmo cadastrar um contato? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
                cadastra(agenda);
            else
                break;
            break;
        case OPCAO2:
            printYELLOW("Voce quer mesmo listar os contatos? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
            }
            else

                break;

            break;
        case OPCAO3:
            printYELLOW("Voce quer mesmo buscar um contato? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
            }
            else
                break;
            break;
        case OPCAO4:
            printYELLOW("Voce quer mesmo exportar contatos? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
            }
            else
                break;

            break;
        case OPCAO5:
            printYELLOW("Voce quer mesmo importar contatos? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
            }
            else
            {
                break;
            }
            break;
        case OPCAO6:
            printYELLOW("Voce quer mesmo apagar um contato? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
            }
            else
            {
                break;
            }
            break;
        case OPCAO7:
            printYELLOW("Voce quer mesmo editar um paciente? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
            }
            else
            {
                break;
            }
            break;
        case OPCAO8:
            printYELLOW("Voce quer mesmo sair do programa? 1-(Sim) 2-(Nao)\n");
            volta = LeOpcao(OPCAO1, OPCAO2);
            if (volta == OPCAO1)
            {
                printGREEN("Obrigado por utilizar meu programa!\n");
            }
            else
                opc = 0;
            break;
            break;
        default:
            break;
        }
    }
    return 0;
}
