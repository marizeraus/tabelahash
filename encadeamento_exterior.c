#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>

#include "encadeamento_exterior.h"
#include "compartimento_hash.h"
#include "cliente.h"

int hash(int c, int m){
    return c%m;
}


void cria_hash(char *nome_arquivo_hash, int m)
{
    // Cria uma tabela hash vazia de tamanho tam, e salva no arquivo nome_arquivo_hash
    // Compartimento que nao tem lista encadeada associada deve ter valor igual a -1
    // nome_arquivo_hash: nome do arquivo hash a ser criado
    // m: tamanho da tabela hash a ser criada
    FILE *f = fopen(nome_arquivo_hash, "wb");
    TCompartimento *t;
    t = compartimento_hash(-1);
    for(int i=0; i<m; i++){
        salva_compartimento(t,f);
    }
    fclose(f);
}

int busca(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m)
{
	int pos, pont;
	pos = hash(cod_cli, m);
	FILE *file_hash = fopen(nome_arquivo_hash, "rb");
	FILE *dados = fopen(nome_arquivo_dados, "rb");
	fseek(file_hash, pos*tamanho_compartimento(), SEEK_SET);
	TCompartimento *t;
	t=le_compartimento(file_hash);

	int pont_cli;
    TCliente *cliente;
    pont = t->prox;
	do{
	fseek(dados, pont*tamanho_cliente(), SEEK_SET);
    cliente = le_cliente(dados);
    if (cliente->cod==cod_cli && cliente->ocupado==1){
        return pont;
    }
    else{
        if (cliente->prox!=-1){
            pont = cliente->prox;
        }
    }
	}while(cliente->prox!=-1);
    return -1;
    }



int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int num_registros, int m)
{
	if(busca(cod_cli, nome_arquivo_hash, nome_arquivo_dados, m)==-1){
	    int pos = hash(cod_cli, m);
	    TCliente *cliente1 = cliente(cod_cli, nome_cli, -1, OCUPADO);
	    FILE *arqhash = fopen(nome_arquivo_hash, "rb+");
	    fseek(arqhash, pos*tamanho_compartimento(), SEEK_SET);
	    TCompartimento *comp;
	    comp = le_compartimento(arqhash);
        FILE *arqdados = fopen(nome_arquivo_dados, "rb+");
        int cont=0;
        imprime_compartimento(comp);
        if(comp->prox==-1){
            fseek(arqdados, 0, SEEK_END);
            int pos2 = ftell(arqdados)/tamanho_cliente();
            salva_cliente(cliente1, arqdados);
            comp->prox=pos2;
            rewind(arqhash);
            fseek(arqhash, pos*tamanho_compartimento(), SEEK_SET);
            salva_compartimento(comp, arqhash);
            return pos2;
        }
        while(!feof(arqdados)){
            le_cliente(arqdados);
            cont++;
        }
        salva_cliente(cliente1, arqdados);
        if (comp->prox==-1){

	    }


	}
    return -1;
}

int exclui(int cod_cli, char *nome_arquivo_hash, char *nome_arquivo_dados, int m)
{
    int pont = busca(cod_cli, nome_arquivo_hash, nome_arquivo_dados, m);
	if(pont!=-1) {
        FILE *f = fopen(nome_arquivo_dados, "rb+");
        fseek(f, pont * tamanho_cliente(), SEEK_SET);
        TCliente *t = le_cliente(f);
        rewind(f);
        t->ocupado = 0;
        fseek(f, pont * tamanho_cliente(), SEEK_SET);
        salva_cliente(t, f);
        rewind(f);
        return pont;
    }
    return -1;
}

