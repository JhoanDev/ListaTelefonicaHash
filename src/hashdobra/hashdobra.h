#ifndef HASH_H
#define HASH_H

// Módulo: Hash dobra
#include "../telefone/telefone.h"

// Transforma a string em binaria
char *StringParaBinario(const char *texto);

// faz a soma "dobrando" o primeiro termo
char *SomaDiferente(char *dobra, char *naodobra);

// função hash da dobra
int Dobra(char *bin);

// transforma o numero em binario para inteiro
int BinarioParaInteiro(char *binario);

// Algoritmo para tratamento de colisões
int SondagemLinear(Telefone *agenda, int indice);

// Algoritmo para buscar na tabela hash
int SondagemLinearBusca(Telefone *agenda, int indice);

#endif // HASH_H