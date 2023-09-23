#ifndef HASH_H
#define HASH_H

// Módulo: Hash dobra
#include "../telefone/telefone.h"

// Transforma a string em binaria
char *string_para_binario(const char *texto);

// faz a soma "dobrando" o primeiro termo
char *soma_diferente(char *dobra, char *naodobra);

// função hash da dobra
int dobra(char *bin);

// transforma o numero em binario para inteiro
int binario_para_inteiro(char *binario);

// Algoritmo para tratamento de colisões
int sondagem_linear(Telefone *agenda, int indice);

// Algoritmo para buscar na tabela hash
int sondagem_linear_busca(Telefone *agenda, int indice, char email[]);

#endif // HASH_H