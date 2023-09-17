#ifndef SISTEMA_H
#define SISTEMA_H

// Módulo: funções para tratativas e falhas
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Lê e descarta caracteres encontrados na entrada
void LimpaBuffer(void);

// Lê e valida a opção digitada pelo usuário
char LeOpcao(char menorValor, char maiorValor);

// corrige o nome
void corrige_nome(char nome[]);

// Exibe o menu
void menu(void);

// Imprime em verde
void printGREEN(char *text);

// Imprime em amarelo
void printYELLOW(char *text);

// Imprime em vermelho
void printRED(char *text);

// verificação do numero
int verificanumerotelefone(const char numero[]);

// verificação do email
int verificaemail(const char email[]);

// formatação do numero
void formatanumerotelefone(char numero[]);

#endif // SISTEMA_H