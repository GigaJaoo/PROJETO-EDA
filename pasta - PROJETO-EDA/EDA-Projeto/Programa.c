/*****************************************************************//**
 * \file   Programa.c
 * \brief  Programa Principal
 *
 * \author João Pereira - a24254
 * \date   March 2023
 *********************************************************************/

#include "Assinaturas.h"

int main() {

	// Inicialização das Listas de Clientes, Gestores e Meios.
	ListaClientes* inicioClientes = NULL;
	ListaGestores* inicioGestores = NULL;
	ListaMeios* inicioMeios = NULL;

	Cliente c1 = { 51, 19, 34.5f, "Joao", "Rua da Ambrosia" };
	Cliente c2 = { 28, 45, 0.4f, "Abel", "Avenida dos Astros" };
	Cliente c3 = { 180, 23, 473, "Vitor", "Riacho dos Caniscos" };
	Cliente c4 = { 11, 47, 126.7f, "Lima", "Casa de Esposende" };

	inicioClientes = InserirClientes(inicioClientes, &c1);
	inicioClientes = InserirClientes(inicioClientes, &c2);
	inicioClientes = InserirClientes(inicioClientes, &c3);
	inicioClientes = InserirClientes(inicioClientes, &c4);

	printf("\nForam imprimidos %d clientes.\n", ImprimirClientes(inicioClientes));

	// No final do programa, grava as listas de Clientes, Gestores e Meios em ficheiros bin�rios.
	ArmazenarClientesBin(inicioClientes, "DadosBinClientes.bin");

	// Armazena também em ficheiros de texto
	ArmazenarClientes(inicioClientes, "DadosClientes.txt");
}