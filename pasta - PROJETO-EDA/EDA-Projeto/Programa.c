/*****************************************************************//**
 * \file   Programa.c
 * \brief  Programa Principal
 *
 * \author João Pereira - a24254
 * \date   March 2023
 *********************************************************************/

#include "Assinaturas.h"

int main() {

	// Inicializa��o das Listas de Clientes, Gestores e Meios.
	ListaClientes* inicioClientes = NULL;
	ListaGestores* inicioGestores = NULL;
	ListaMeios* inicioMeios = NULL;

	// Coleta as listas dos dados dos Clientes, Gestores e Meios a partir dos ficheiros bin�rios no inicio do programa.
	//inicioClientes = LerClientesBin("DadosBinClientes.bin");
	//inicioGestores = LerGestoresBin("DadosBinGestores.bin");
	//inicioMeios = LerMeiosBin("DadosBinMeios.bin");

	//Cliente c1, c2, c3, c4;

	Cliente c1 = { 51, 19, 34.5f, "Joao", "Rua da Ambrosia" };
	Cliente c2 = { 28, 45, 0.4f, "Abel", "Avenida dos Astros" };
	Cliente c3 = { 180, 23, 473, "Vitor", "Riacho dos Caniscos" };
	Cliente c4 = { 11, 47, 126.7f, "Lima", "Casa de Esposende" };

	/*c1.nif = 51;
	c1.idade = 19;
	c1.saldo = 34.5f;
	strcpy("Joao", c1.nome);
	strcpy("Rua da Ambrosia", c1.morada);

	c2.nif = 28;
	c2.idade = 45;
	c2.saldo = 0.4f;
	strcpy("Abel", c2.nome);
	strcpy("Avenida dos Astros", c2.morada);

	c3.nif = 180;
	c3.idade = 23;
	c3.saldo = 473;
	strcpy("Vitor", c3.nome);
	strcpy("Riacho dos Caniscos", c3.morada);

	c4.nif = 12;
	c4.idade = 47;
	c4.saldo = 126.7f;
	strcpy("Lima", c4.nome);
	strcpy("Casa de Esposende", c4.morada);*/

	inicioClientes = InserirClientes(inicioClientes, &c1);
	inicioClientes = InserirClientes(inicioClientes, &c2);
	inicioClientes = InserirClientes(inicioClientes, &c3);
	inicioClientes = InserirClientes(inicioClientes, &c4);

	printf("\nForam imprimidos %d clientes.\n", ImprimirClientes(inicioClientes));

	// No final do programa, grava as listas de Clientes, Gestores e Meios em ficheiros bin�rios.
	ArmazenarClientesBin(inicioClientes, "DadosBinClientes.bin");
	//ArmazenarGestoresBin(inicioGestores, "DadosBinGestores.bin");
	//ArmazenarMeiosBin(inicioMeios, "DadosBinMeios.bin");

	// Armazena também em ficheiros de texto
	ArmazenarClientes(inicioClientes, "DadosClientes.txt");
}