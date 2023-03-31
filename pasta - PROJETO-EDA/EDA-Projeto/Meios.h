/*****************************************************************//**
 * \file   Meios.h
 * \brief  Structs e assinaturas das funções dos Meios de Mobilidade Elétricos.
 * 
 * \author João Pereira - a24254
 * \date   March 2023
 *********************************************************************/

#include <string.h>    // strings
#include <stdlib.h>    // malloc
#include <stdio.h>     // NULL
#include <stdbool.h>   // bools

 /**
  * Tipos de transportes elétricos.
  */
typedef enum tipoTransporte {
	trotinete,
	bicicleta,
	motociclo,
	carro,
} TipoTransporte;

/**
 * Estrutura dos meios de mobilidade elétricos.
 */
typedef struct meiosMobilidadeEletricos {
	int autonomia;
	int geocodigo;
	TipoTransporte tipo;
} MeiosMobElet;

/**
 * Estrutura para a criação da lista de meios de mobilidade elétricos.
 */
typedef struct listaMeios {
	MeiosMobElet* meio;
	struct listaMeios* nextMeio;
} ListaMeios;

/**
 * Função para armazenar a lista dos meios de mobilidade el�trica em ficheiro de texto.
 */
int ArmazenarMeios(ListaMeios* head, char fileName[]);

/**
 * Função para armazenar a lista dos meios de mobilidade el�trica em ficheiro binário.
 */
int ArmazenarMeiosBin(ListaMeios* head, char fileName[]);

/**
 * Função para ler a lista dos meios de mobilidade elétricos de ficheiro de texto.
 */
ListaMeios* LerMeios(char fileName[]);

/**
 * Função para ler a lista dos meios de mobilidade elétricos de ficheiro binário.
 */
ListaMeios* LerMeiosBin(char fileName[]);

/**
 * Função para inserir novos dados de um meio de mobilidade elétrico na lista dos meios de mobilidade elétricos.
 */
ListaMeios* InserirMeio(ListaMeios* head, MeiosMobElet* novoMeio);

/**
 * Função para remover um determinado meio de mobilidade elétrico da lista de meios de mobilidade elétricos.
 */
ListaMeios* RemoverMeio(ListaMeios* head, MeiosMobElet* meioRemovido);

/**
 * Função para alterar os dados de um determinado meio de mobilidade elétrico na lista de meios de mobilidade elétricos.
 */
ListaMeios* AlterarMeio(ListaMeios* head, MeiosMobElet* meioAlterar, MeiosMobElet* novoMeio);

/**
 * Função que compara dois Meios de Mobilidade Elétricos.
 */
int ComparaMeios(MeiosMobElet* m1, MeiosMobElet* m2);

/**
 * Função que verifica se um determinado Meio está presente na Lista de Meios.
 */
bool VerificaMeios(ListaMeios* head, MeiosMobElet* meio);

/**
 * Imprime os dados dos Meios de Mobilidade Elétricos numa determinada lista dos mesmos.
 */
int ImprimirMeios(ListaMeios* head);
