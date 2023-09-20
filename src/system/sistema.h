#ifndef SISTEMA_H
#define SISTEMA_H

// Módulo: funções para tratativas e falhas
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Lê e descarta caracteres encontrados na entrada
void limpa_buffer(void);

// Lê e valida a opção digitada pelo usuário
char le_opcao(char menorValor, char maiorValor);

// corrige o nome
void corrige_nome(char nome[]);

// Exibe o menu
void menu(void);

// Imprime em verde
void print_green(char *text);

// Imprime em amarelo
void print_yellow(char *text);

// Imprime em vermelho
void print_red(char *text);

// verificação do numero
int verifica_numero_telefone(const char numero[]);

// verificação do email
int verifica_email(const char email[]);

// formatação do numero
void formata_numero_telefone(char numero[]);

#endif // SISTEMA_H