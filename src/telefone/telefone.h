#ifndef TELEFONE_H
#define TELEFONE_H

// TAD: telefone
typedef struct telefone Telefone;

// função para preencher um contato
Telefone preenche_dados();

// verifica se ha colisão
int colisao(Telefone *agenda, int indice);

// compara emails
int compara(Telefone *agenda, int atual, char email[]);

// cadastrar um novo contato na agenda
void cadastra(Telefone *agenda, Telefone contato);

// listar contatos da lista telefonica
void listar_contatos(Telefone *agenda);

// buscar contato
int buscar_contato(Telefone *agenda);

// importar contatos
int importar_contatos(Telefone *agenda, char *caminho);

// exportar contatos
void exportar_contatos(Telefone *agenda, char *caminho);

// gerar contatos
void gera_contatos(char *caminho);

// apaga um contato da tabela
void apaga_contato(Telefone *agenda);

// reorganiza a tabela apos exclusao, ou edição do email.
void reorganiza_hash(Telefone *agenda);

// limpa agenda
void limpar_agenda(Telefone *agenda);

// edita um contato
void editar_contato(Telefone *agenda);

#endif // TELEFONE_H