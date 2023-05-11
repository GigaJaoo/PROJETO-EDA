/*****************************************************************//**
 * \file   Grafo.h
 * \brief  Estrutura dos Grafos
 * 
 * \author João Pereira - a24254
 * \date   May 2023
 *********************************************************************/

#define T 30

#include <string.h>    // strings
#include <stdlib.h>    // malloc
#include <stdio.h>     // NULL
#include <stdbool.h>   // bools

/**
 * Estrutura dos Vertices do Grafo.
 */
typedef struct vertice{
	int codigo;
	char cidade[T];
	bool visitado;
	Vertice* next;
	Adjacente* adj;
}Vertice;

/**
 * Estrutura dos Vertices do Grafo para serem guardados em ficheiro binario.
 */
typedef struct verticeFile{
	int codigo;
	char cidade[T];
}VerticeFile;

/**
 * Estrutura dos Adjacentes dos Vertices no Grafo.
 */
typedef struct adjacente {
	int codigo;
	int peso;
	Adjacente* nextAdj;
}Adjacente;

/**
 * Estrutura dos Adjacentes dos Vertices para serem guardados em ficheiro binario.
 */
typedef struct adjacenteFile {
	int codigoOrigem;
	int codigoDestino;
	int peso;
}AdjacenteFile;

/**
 * Função para guardar a lista de Vértices de um Grafo.
 */
int GuardarGrafoBin(Vertice* g, char* fileName);

/**
 * Função para guardar a lista de Adjacencias de um Vértice de um Grafo.
 */
int GuardarAdjsBin(Adjacente* h, char fileName, int codigoOrigem);
