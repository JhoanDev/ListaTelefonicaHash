#include "hashdobra.c"
#include "telefone.h"
struct telefone
{
    char nome[50];
    char email[50];
    int numero;
};

Telefone preenchedados(){
    Telefone novo;
    printYELLOW("Insira o nome: ");
    scanf(" %[^\n]s",novo.nome);
    printYELLOW("Insira o email: ");
    scanf(" %[^\n]s",novo.email);
    printYELLOW("Insira o numero de telefone: ");
    scanf(" %d",&novo.numero);
    return novo;
}

void cadastra(Telefone *agenda, Telefone contato){
    int codigohash = Dobra(contato.email);
    printf("Codigo %d\n\n", codigohash);
    agenda[codigohash] = contato;
}