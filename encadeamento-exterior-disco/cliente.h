#ifndef CLIENTE_H
#define CLIENTE_H

#define LIBERADO 0
#define OCUPADO 1

#define TAM_NOME 100

#include <stdio.h>

typedef struct Cliente {
	int cod;
	char nome[TAM_NOME];
	int prox;
	int ocupado;
} TCliente;

// Imprime cliente
void imprime_cliente(TCliente *cliente);

// Cria cliente. Lembrar de usar free(cliente)
TCliente *cliente(int cod, char *nome, int prox, int status);

// Salva cliente no arquivo out, na posicao atual do cursor
void salva_cliente(TCliente *cliente, FILE *out);

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
TCliente *le_cliente(FILE *in);

// Compara dois clientes
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_cliente(TCliente *c1, TCliente *c2);

// Retorna tamanho do cliente em bytes
int tamanho_cliente();

#endif