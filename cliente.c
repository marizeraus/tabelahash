#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <string.h>
#include <stdlib.h>

#include "cliente.h"


void imprime_cliente(TCliente *cliente)
{
	printf("%d, %s, %d, %s\n", cliente->cod, cliente->nome, cliente->prox,
		(cliente->ocupado? "OCUPADO" : "LIBERADO"));
}

TCliente *cliente(int cod, char *nome, int prox, int flag)
{
	TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));
	if (cliente) memset(cliente, 0, sizeof(TCliente));
	cliente->cod = cod;
	strcpy(cliente->nome, nome);
	cliente->prox = prox;
	cliente->ocupado = flag;
	return cliente;
}

void salva_cliente(TCliente *cliente, FILE *out)
{
	fwrite(&cliente->cod, sizeof(int), 1, out);
	fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
	fwrite(&cliente->prox, sizeof(int), 1, out);
	fwrite(&cliente->ocupado, sizeof(int), 1, out);
}

TCliente *le_cliente(FILE *in)
{
	TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));
	if (0 >= fread(&cliente->cod, sizeof(int), 1, in)) {
		free(cliente);
		return NULL;
	}
	fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
	fread(&cliente->prox, sizeof(int), 1, in);
	fread(&cliente->ocupado, sizeof(int), 1, in);
	return cliente;
}

int cmp_cliente(TCliente *c1, TCliente *c2)
{
	if (c1 == NULL) {
		return (c2 == NULL);
	}
	if (c1->cod != c2->cod) {
		return 0;
	}
	if (strcmp(c1->nome, c2->nome) != 0) {
		return 0;
	}
	if (c1->prox != c2->prox) {
		return 0;
	}
	if (c1->ocupado != c2->ocupado) {
		return 0;
	}
	return 1;
}

int tamanho_cliente()
{
	return sizeof(int) + // cod_cliente
		sizeof(char) * TAM_NOME + // nome
		sizeof(int) + // prox
		sizeof(int); //flag
}