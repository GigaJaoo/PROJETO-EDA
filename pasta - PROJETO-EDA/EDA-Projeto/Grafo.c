/*****************************************************************//**
 * \file   Grafo.c
 * \brief  Implementação das Funções dos Grafos
 * 
 * \author João Pereira - a24254
 * \date   May 2023
 *********************************************************************/

#include "Assinaturas.h"

 /**
  * Função para guardar a lista de Vértices de um Grafo.
  * 
  * Caso o Grafo seja nulo, retorna -1.
  * Caso não consiga abrir o ficheiro, retorna 0.
  * Caso consiga guardar a lista dos Vértices do Grafo com sucesso, retorna 1.
  */
int GuardarGrafoBin(Vertice* g, char* fileName){
	if (g == NULL) {
		return -1;
	}
	Vertice* aux = g;
	VerticeFile* v;
	FILE* fileGrafoBin;
	fileGrafoBin = fopen(fileName, "wb");
	if (fileGrafoBin == NULL) {
		return 0;
	}
	while (aux != NULL) {
		strcpy(v->cidade, aux->cidade);
		v->codigo = aux->codigo;
		fwrite(v, 1, sizeof(VerticeFile), fileGrafoBin);
		GuardarAdjsBin(aux->adj, strcat("Adj", fileName), v->codigo);
	}
	fclose(fileGrafoBin);
	return 1;
}

/**
 * Função para guardar a lista de Adjacencias de um Vértice de um Grafo.
 * 
 * Caso a lista seja nula, retorna -1.
 * Caso não consiga abrir o ficheiro, retorna 0.
 * Caso consiga guardar a lista das Adjacencias com sucesso, retorna 1.
 */
int GuardarAdjsBin(Adjacente* h, char fileName, int codigoOrigem){
	if (h == NULL) {
		return -1;
	}
	Adjacente* aux = h;
	AdjacenteFile* a;
	FILE* fileAdjBin;
	fileAdjBin = fopen(fileName, "wb");
	if (fileAdjBin == NULL) {
		return 0;
	}
	while (aux != NULL) {
		a->codigoOrigem = codigoOrigem;
		a->codigoDestino = aux->codigo;
		a->peso = aux->peso;
		fwrite(a, 1, sizeof(AdjacenteFile), fileAdjBin);
	}
	fclose(fileAdjBin);
	return 1;
}
