/*****************************************************************//**
 * \file   Clientes.h
 * \brief  Structs e assinaturas das funções dos Clientes.
 * 
 * \author João Pereira - a24254
 * \date   March 2023
 *********************************************************************/

#define NOME 50
#define MORADA 100

#include <string.h>    // strings
#include <stdlib.h>    // malloc
#include <stdio.h>     // NULL
#include <stdbool.h>   // bools

 /**
  * Estrutura dos Clientes.
  */
typedef struct cliente {
	int nif;
	int idade;
	float saldo;
	char nome[NOME];
	char morada[MORADA];
} Cliente;

/**
 * Estrutura para a criação da lista de Clientes.
 */
typedef struct listaClientes {
	Cliente* cliente;
	struct listaClientes* nextCliente;
} ListaClientes;

/**
 * Função para armazenar a lista de clientes em ficheiro de texto.
 */
int ArmazenarClientes(ListaClientes* head, char filename[]);

/**
 * Função para armazenar a lista de clientes em ficheiro binário.
 */
int ArmazenarClientesBin(ListaClientes* head, char fileName[]);

/**
 * Função para ler a lista de clientes de ficheiro de texto.
 */
ListaClientes* LerClientes(char fileName[]);

/**
 * Função para ler a lista de clientes de ficheiro binário.
 */
ListaClientes* LerClientesBin(char fileName[]);

/**
 * Função para inserir novos dados de um cliente na lista dos clientes.
 */
ListaClientes* InserirClientes(ListaClientes* head, Cliente* novoCliente);

/**
 * Função para remover um determinado cliente da lista de clientes.
 */
ListaClientes* RemoverClientes(ListaClientes* head, Cliente* clienteRemovido);

/**
 * Função para alterar os dados de um determinado cliente na lista de clientes.
 */
ListaClientes* AlterarClientes(ListaClientes* head, Cliente* clienteAlterar, Cliente* novoCliente);

/**
 * Função que compara dois Clientes.
 */
int ComparaClientes(Cliente* c1, Cliente* c2);

/**
 * Função que verifica se um determinado Cliente está presente na Lista de Clientes.
 */
bool VerificaClientes(ListaClientes* head, Cliente* cliente);

/**
 * Imprime os dados dos Clientes presentes numa determinada lista dos mesmos.
 */
int ImprimirClientes(ListaClientes* head);
