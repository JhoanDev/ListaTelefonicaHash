#ifndef TELEFONE_H
#define TELEFONE_H

// TAD: telefone
typedef struct telefone Telefone;

// função para preencher um contato
Telefone preenchedados();

// cadastrar um novo contato na agenda
void cadastra(Telefone *agenda);

// verifica se ha colisão
int colisao(Telefone *agenda, int indice);

// compara emails
int compara(Telefone *agenda, int atual, int buscado);

#endif // TELEFONE_H