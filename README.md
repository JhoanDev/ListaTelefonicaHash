# Phone Directory
A program written in C that stores phone numbers in a Hash Table.

To store into table, this program uses double hashing and linear probing to avoid hash collisions.

## Summary
- [Features](#features)
- [Double hashing code](#double-hashing-code)
- [Linear probing code](#linear-probing-code)


## Features

This program offers several intereting functionalities, such as

- creating contact
- displaying all contacts
- searching a contact
- exporting a contact
- importing a contact
- deleting a contact
- editing a contact

## Double hashing code

The following code shows how double hashing was impremented

*double hashing*
```C
int Dobra(char *texto)
{
    char *bin = StringParaBinario(texto);
    int tamanhoDaString = strlen(bin);
    int tamanhoDoSegmento = 5;
    int i = 0;
    char segmento[tamanhoDoSegmento + 1];
    char *resultado = (char *)malloc(5 * sizeof(char));
    if (resultado == NULL)
    {
        printRED("Erro de alocação de memória.");
        exit(1);
    }
    strncpy(segmento, bin + i, tamanhoDoSegmento);
    strncpy(resultado, bin + i + tamanhoDoSegmento, tamanhoDoSegmento);
    resultado = SomaDiferente(segmento, resultado);
    for (i = tamanhoDoSegmento * 2; i < tamanhoDaString; i += tamanhoDoSegmento)
    {
        strncpy(segmento, bin + i, tamanhoDoSegmento);
        resultado = SomaDiferente(resultado, segmento);
    }
    int hash = BinarioParaInteiro(resultado);
    return hash;
}
```
you can see the complete implementation in **./src/hashdrobra/**.

## Linear probing code
The following code shows how linar probing was impremented

```C
int SondagemLinear(Telefone *agenda, int indice)
{
    int novoindice = indice;
    int i = 1;
    while (colisao(agenda, novoindice))
    {
        novoindice = (indice + i) % 32;
        i++;
    }
    return novoindice;
}
```

you can see the complete implementation in **./src/hashdrobra/**.