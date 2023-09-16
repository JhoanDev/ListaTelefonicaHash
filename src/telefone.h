#ifndef TELEFONE_H
#define TELEFONE_H

// TAD: telefone
typedef struct telefone Telefone;

// função para preencher um contato
Telefone preenchedados();

// verifica se ha colisão
int colisao(Telefone *agenda, int indice);

// compara emails
int compara(Telefone *agenda, int atual, int buscado);

// cadastrar um novo contato na agenda
void cadastra(Telefone *agenda,Telefone contato);

// listar contatos da lista telefonica
void listarcontatos(Telefone *agenda);

// buscar contato
int buscarcontato(Telefone *agenda);

// importar contatos
int importarcontatos(Telefone *agenda, char *caminho);

//exportar contatos
void exportarcontatos(Telefone *agenda, char *caminho);

// gerar contatos
void geracontatos(char *caminho);

#endif // TELEFONE_H