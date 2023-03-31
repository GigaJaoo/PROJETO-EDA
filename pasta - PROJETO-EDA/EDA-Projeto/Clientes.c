/*****************************************************************//**
 * \file   Clientes.c
 * \brief  Funções dos Clientes.
 * 
 * \author João Pereira - a24254
 * \date   March 2023
 *********************************************************************/

#include "Assinaturas.h"

//Duvidas
 /**
  * Função para armazenar a lista de clientes em ficheiro de texto.
  *
  * Caso consiga guardar a lista no ficheiro, retorna 1.
  * Caso a lista esteja vazia, retorna 0.
  * Caso não consiga guardar a lista no ficheiro, retorna -1.
  */
int ArmazenarClientes(ListaClientes* head, char fileName[]) {
	if (head == NULL) {
		return 0;
	}
	ListaClientes* aux = head;
	FILE* fClientes;
	fClientes = fopen(fileName, "w");
	if (fClientes == NULL) {
		return (-1);
	}
	while (aux != NULL) {
		fprintf(fClientes, "%d;%d;%f;%s;%s\n", aux->cliente->nif, aux->cliente->idade, aux->cliente->saldo, aux->cliente, aux->cliente->nome, aux->cliente->morada);
		aux = aux->nextCliente;
	}
	fclose(fClientes);
	return 1;
}

/**
 * Função para armazenar a lista de clientes em ficheiro binário.
 *
 * Caso consiga guardar a lista no ficheiro, retorna 1.
 * Caso a lista esteja vazia, retorna 0.
 * Caso não consiga guardar a lista no ficheiro, retorna -1.
 */
int ArmazenarClientesBin(ListaClientes* head, char fileName[]) {
	if (head == NULL) {
		return 0;
	}
	ListaClientes* aux = head;
	FILE* fClientesBin;
	fClientesBin = fopen(fileName, "wb");
	if (fClientesBin == NULL) {
		return (-1);
	}
	while (aux != NULL) {
		fwrite(&aux->cliente, 1, sizeof(Cliente), fClientesBin);
		aux = aux->nextCliente;
	}
	fclose(fClientesBin);
	return 1;
}

//Duvidas
/**
 * Função para ler a lista de clientes de ficheiro de texto.
 *
 * Caso não consiga ler a lista a partir do ficheiro, retorna 0.
 * Caso consiga ler a lista a partir do ficheiro, retorna a lista lida.
 */
 //ListaClientes* LerClientes(char fileName[]) {
 //	ListaClientes* head = NULL;
 //	FILE* fClientes;
 //	fClientes = fopen(fileName, "r");
 //	if (fClientes == NULL) {
 //		return 0;
 //	}
 //
 //	Cliente aux;              //Não é apontador
 // 
 //	while(!feof(fClientes)){
 //		fscanf(fClientes, "%d;%d;%f;[^;];%s\n", &aux.nif, &aux.idade, &aux.saldo, aux.nome, aux.morada);                //Nas strings não precisa de &
 //		head = InserirClientes(head, &aux);                              //no fscanf utilizar . em vez de ->
 //	}
 //	fclose(fClientes);
 //
 //	return head;
 //}

/**
  * Função para ler a lista de clientes de ficheiro binário.
  *
  * Caso não consiga ler a lista a partir do ficheiro, retorna 0.
  * Caso consiga ler a lista a partir do ficheiro, retorna a lista lida.
  */
ListaClientes* LerClientesBin(char fileName[]) {
	ListaClientes* head = NULL;
	FILE* fClientesBin;
	fClientesBin = fopen(fileName, "rb");
	if (fClientesBin == NULL) {
		return 0;
	}

	Cliente aux;
	while (fread(&aux, 1, sizeof(Cliente), fClientesBin)) {
		head = InserirClientes(head, &aux);
	}
	fclose(fClientesBin);

	return head;
}

//Tenho de acrescentar um parametro para me dizer aquilo que aconteceu - um inteiro talvez
/**
 * Função para inserir novos dados de um cliente na lista dos clientes por ordem crescente de NIF.
 */
ListaClientes* InserirClientes(ListaClientes* head, Cliente* novoCliente) {
	/*ListaClientes* aux = (ListaClientes*)malloc(sizeof(ListaClientes));
	aux->nextCliente = NULL;
	aux.cliente = novoCliente;

	// Caso a Lista de Clientes seja vazia
	if (head == NULL) {
		head = novoCliente;
		return head;
	}
	else {
		// Inserir por ordem crescente de NIF dos Clientes
		if (head->cliente->nif > aux->cliente->nif) {
			// Para inserir no incio da Lista de Clientes
			aux->nextCliente = head;
			head = novoCliente;
		}
		else {
			// Para inserir o Cliente no meio ou no fim da Lista
			ListaClientes* clienteAnterior = head;
			ListaClientes* clienteAtual = head;

			// Procurar a posi��o onde vai ser inserido o Cliente, conforme a ordem dos NIFs
			while (clienteAtual->cliente->nif < aux->cliente->nif) {
				clienteAnterior = clienteAtual;
				clienteAtual = clienteAtual->nextCliente;
			}

			aux->nextCliente = clienteAtual;
			clienteAnterior->nextCliente = aux;

		}
	}
	return head;*/

	ListaClientes* novo = (ListaClientes*)malloc(sizeof(ListaClientes));
	novo->cliente = novoCliente;
	novo->nextCliente = NULL;

	ListaClientes* aux = head;
	ListaClientes* anterior = head;

	//Caso a lista seja vazia
	if (head == NULL) {
		head = novo;
		return head;
	}
	else {
		//Inserir por ordem crescente dos NIFs
		//Inserir no inicio
		if (head->cliente->nif > novo->cliente->nif) {
			novo->nextCliente = head;
			head = novo;
			return head;
		}
		else {
			//Inserir no meio ou no fim
			aux = aux->nextCliente;
			while (aux != NULL) {
				if (aux->cliente->nif > novo->cliente->nif) {
					novo->nextCliente = aux;
					anterior->nextCliente = novo;
				}
				anterior = aux;
				aux = aux->nextCliente;
			}
			anterior->nextCliente = novo;
		}
	}
	return head;
}

//Tenho de acrescentar um parametro para me dizer aquilo que aconteceu - um inteiro talvez
//Posso ainda usar as funçoes de verificar a presença para ver se está ou nao na lista e melhorar as funçães de verificarpresença para me dizer onde está
/**
 * Função para remover um determinado cliente da lista de clientes.
 *
 * Caso consiga remover o cliente pretendido, retorna a lista sem esse cliente.
 * Caso não consiga remover o cliente pretendido, retorna a lista sem alterações.
 */
ListaClientes* RemoverClientes(ListaClientes* head, Cliente* clienteRemovido) {
	ListaClientes* aux = head;
	ListaClientes* anterior = head;

	// Caso em que o cliente removido é o primeiro elemento da lista.
	if (ComparaClientes(aux, clienteRemovido) == 1) {
		head = aux->nextCliente;
		//aux->nextCliente = NULL;             // Possivelmente, deveria libertar o aux em vez de o colocar a apontar para NULL
		free(aux);
		return head;
	}

	// Caso em que o cliente removido está no meio ou no fim da lista.
	aux = aux->nextCliente;
	while (aux != NULL) {
		if (ComparaClientes(aux, clienteRemovido) == 1) {
			anterior->nextCliente = aux->nextCliente;
			aux->nextCliente = NULL;
		}
		else {
			anterior = anterior->nextCliente;
			aux = aux->nextCliente;
		}
	}
	return head;
}

//Tenho de acrescentar um parametros para me dizer aquilo que aconteceu - um inteiro talvez
/**
 * Função para alterar os dados de um determinado cliente na lista de clientes.
 *
 */
ListaClientes* AlterarClientes(ListaClientes* head, Cliente* clienteAlterar, Cliente* novoCliente) {
	if (VerificaClientes(head, clienteAlterar)) {
		head = RemoverClientes(head, clienteAlterar);
		head = InserirClientes(head, novoCliente);
	}
	return head;
}

/**
 * Função que compara dois Clientes.
 *
 * Caso os dois Clientes sejam iguais em todos os parametros, retorna 1.
 * Caso os dois Clientes sejam diferentes em qualquer parametro, retorna 0.
 */
int ComparaClientes(Cliente* c1, Cliente* c2) {
	if ((c1->nif == c2->nif) && (c1->idade == c2->idade) && (c1->saldo == c2->saldo) && (c1->nome == c2->nome) && (c1->morada == c2->morada)) {
		return 1;
	}
	else {
		return 0;
	}
}

//Posso melhorar estas funções para me dizerem onde está aquilo que procuro ou criar umas novas que o façam
/**
 * Função que verifica se um determinado Cliente está presente na Lista de Clientes.
 *
 * Caso o Cliente esteja presente na Lista, retorna true.
 * Caso o Cliente não esteja presente na Lista, retorna false.
 */
bool VerificaClientes(ListaClientes* head, Cliente* cliente) {
	ListaClientes* aux = head;
	while (aux != NULL) {
		if (ComparaClientes(aux, cliente) == 1) {
			return true;
		}
		aux = aux->nextCliente;
	}
	return false;
}

/**
 * Imprime os dados dos Clientes presentes numa determinada lista dos mesmos.
 */
int ImprimirClientes(ListaClientes* head) {
	int i;
	ListaClientes* aux = head;
	for (i = 0; aux != NULL; i++) {
		printf("\n");
		printf("Cliente %d:\n", i + 1);
		printf("NIF: %d\n", aux->cliente->nif);
		printf("Idade: %d\n", aux->cliente->idade);
		printf("Saldo: %f\n", aux->cliente->saldo);
		printf("Nome: %s\n", aux->cliente->nome);
		printf("Morada: %s\n", aux->cliente->morada);

		aux = aux->nextCliente;
	}
	return i;
}
