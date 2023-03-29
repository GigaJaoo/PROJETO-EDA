/*****************************************************************//**
 * \file   Gestores.h
 * \brief  Structs e assinaturas das funções dos Gestores.
 * 
 * \author João Pereira - a24254
 * \date   March 2023
 *********************************************************************/

#define NOME 50

#include <string.h>    // strings
#include <stdlib.h>    // malloc
#include <stdio.h>     // NULL
#include <stdbool.h>   // bools

 /**
  * Estrutura dos Gestores.
  */
typedef struct gestor {
	int nif;
	int idade;
	char nome[NOME];
} Gestor;

/**
 * Estrutura para a criação da lista de Gestores.
 */
typedef struct listaGestores {
	Gestor* gestor;
	struct listaGestores* nextGestor;
} ListaGestores;

/**
 * Função para armazenar a lista de gestores em ficheiro de texto.
 */
int ArmazenarGestores(ListaGestores* head, char fileName[]);

/**
 * Função para armazenar a lista de gestores em ficheiro binário.
 */
int ArmazenarGestoresBin(ListaGestores* head, char fileName[]);

/**
 * Função para ler a lista de gestores de ficheiro de texto.
 */
ListaGestores* LerGestores(char fileName[]);

/**
 * Função para ler a lista de gestores de ficheiro binário.
 */
ListaGestores* LerGestoresBin(char fileName[]);

/**
 * Função para inserir novos dados de um gestor na lista dos gestores.
 */
ListaGestores* InserirGestores(ListaGestores* head, Gestor* novoGestor);

/**
 * Função para remover um determinado gestor da lista de gestores.
 */
ListaGestores* RemoverGestores(ListaGestores* head, Gestor* gestorRemovido);

/**
 * Função para alterar os dados de um determinado gestor na lista de gestores.
 */
ListaGestores* AlterarGestores(ListaGestores* head, Gestor* gestorAlterar, Gestor* novoGestor);

/**
 * Fun~ção que compara dois Gestores.
 */
int ComparaGestores(Gestor* g1, Gestor* g2);

/**
 * Função que verifica se um determinado Gestor está presente na Lista de Gestores.
 */
bool VerificaGestores(ListaGestores* head, Gestor* gestor);

/**
 * Imprime os dados dos Gestores presentes numa determinada lista dos mesmos.
 */
int ImprimirGestores(ListaGestores* head);
