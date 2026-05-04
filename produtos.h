// produtos.h
// Shared structures for product registration system

#ifndef PRODUTOS_H
#define PRODUTOS_H

#define MAX_PRODUTOS 100

typedef struct {
    char nome[100];
    float preco;
    int codigo;
} Produto;

typedef struct {
    Produto produtos[MAX_PRODUTOS];
    int total;
} Cadastro;

#endif // PRODUTOS_H
