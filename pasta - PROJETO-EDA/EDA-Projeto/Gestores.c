/*****************************************************************//**
 * \file   Gestores.c
 * \brief  Funções dos Gestores.
 * 
 * \author João Pereira - a24254
 * \date   March 2023
 *********************************************************************/

#include "Assinaturas.h"

//Duvidas
 /**
  * Função para armazenar a lista de gestores em ficheiro de texto.
  *
  * Caso consiga guardar a lista no ficheiro, retorna 1.
  * Caso a lista esteja vazia, retorna 0.
  * Caso não consiga guardar a lista no ficheiro, retorna -1.
  */
int ArmazenarGestores(ListaGestores* head, char fileName[]) {
	if (head == NULL) {
		return 0;
	}
	ListaGestores* aux = head;
	FILE* fGestores;
	fGestores = fopen(fileName, "w");
	if (fGestores == NULL) {
		return (-1);
	}
	while (aux != NULL) {
		fprintf(fGestores, "%d;%d;%s\n", aux->gestor->nif, aux->gestor->idade, aux->gestor->nome);
		aux = aux->nextGestor;
	}
	fclose(fGestores);
	return 1;
}

/**
 * Função para armazenar a lista de gestores em ficheiro binário.
 *
 * Caso consiga guardar a lista no ficheiro, retorna 1.
 * Caso a lista esteja vazia, retorna 0.
 * Caso não consiga guardar a lista no ficheiro, retorna -1.
 */
int ArmazenarGestoresBin(ListaGestores* head, char fileName[]) {
	if (head == NULL) {
		return 0;
	}
	ListaGestores* aux = head;
	FILE* fGestoresBin;
	fGestoresBin = fopen(fileName, "wb");
	if (fGestoresBin == NULL) {
		return (-1);
	}
	while (aux != NULL) {
		fwrite(&aux->gestor, 1, sizeof(Gestor), fGestoresBin);
		aux = aux->nextGestor;
	}
	fclose(fGestoresBin);
	return 1;
}

//Duvidas
/**
 * Função para ler a lista de gestores de ficheiro de texto.
 *
 * Caso não consiga ler a lista a partir do ficheiro, retorna 0.
 * Caso consiga ler a lista a partir do ficheiro, retorna a lista lida.
 */
 ListaGestores* LerGestores(char fileName[]) {
 	ListaGestores* head = NULL;
 	FILE* fGestores;
 	fGestores = fopen(fileName, "r");
 	if (fGestores == NULL) {
 		return 0;
 	}
 
 	Gestor aux;              //Não é apontador aqui
 	while (!feof(fGestores)) {
 		fscanf(fGestores, "%d;%d;%s\n", &aux->nif, &aux->idade, aux->nome);           //nas strings nao precisa do &
 		head = InserirGestores(head, &aux);                                           //mudar as -> para . n fscanf
 	}
 	fclose(fGestores);
 
 	return head;
 }

/**
  * Função para ler a lista de gestores de ficheiro binário.
  *
  * Caso não consiga ler a lista a partir do ficheiro, retorna 0.
  * Caso consiga ler a lista a partir do ficheiro, retorna a lista lida.
  */
ListaGestores* LerGestoresBin(char fileName[]) {
	ListaGestores* head = NULL;
	FILE* fGestoresBin;
	fGestoresBin = fopen(fileName, "rb");
	if (fGestoresBin == NULL) {
		return 0;
	}

	Gestor aux;           //Não é apontador
	while (fread(&aux, 1, sizeof(Gestor), fGestoresBin)) {
		head = InserirGestores(head, &aux);
	}
	fclose(fGestoresBin);

	return head;
}

//Tenho de acrescentar um parametro para me dizer aquilo que aconteceu - um inteiro talvez
/**
 * Função para inserir novos dados de um gestor na lista dos gestores por ordem crescente de NIF.
 */
ListaGestores* InserirGestores(ListaGestores* head, Gestor* novoGestor) {
	ListaGestores* aux = (ListaGestores*)malloc(sizeof(ListaGestores));
	aux->nextGestor = NULL;
	aux->gestor = novoGestor;

	//Caso a lista de gestores seja vazia
	if (head == NULL) {
		head = novoGestor;
		return head;
	}
	else {
		// Inserir por ordem crescente de NIF dos Gestores
		if (head->gestor->nif > aux->gestor->nif) {
			// Para inserir no incio da Lista de Clientes
			aux->nextGestor = head;
			head = novoGestor;
		}
		else {
			// Para inserir o Gestor no meio ou no fim da Lista
			ListaGestores* gestorAnterior = head;
			ListaGestores* gestorAtual = head;

			// Procurar a posição onde vai ser inserido o Gestor, conforme a ordem dos NIFs
			while (gestorAtual->gestor->nif < aux->gestor->nif) {
				gestorAnterior = gestorAtual;
				gestorAtual = gestorAtual->nextGestor;
			}

			aux->nextGestor = gestorAtual;
			gestorAnterior->nextGestor = aux;

		}
	}
	return head;
}

//Tenho de acrescentar um parametro para me dizer aquilo que aconteceu - um inteiro talvez
//Posso ainda usar as funçoes de verificar a presença para ver se está ou nao na lista e melhorar as funçães de verificarpresença para me dizer onde está
/**
 * Função para remover um determinado gestor da lista de gestores.
 *
 * Caso consiga remover o gestor pretendido, retorna a lista sem esse gestor.
 * Caso não consiga remover o gestor pretendido, retorna a lista sem alterações.
 */
ListaGestores* RemoverGestores(ListaGestores* head, Gestor* gestorRemovido, bool*res) {
	ListaGestores* aux = head;
	ListaGestores* anterior = head;
	if (head == NULL) {
		res = false;
		return NULL;
	}

	// Caso em que o gestor removido é o primeiro elemento da lista.
	if (ComparaGestores(aux, gestorRemovido) == 1) {
		head = aux->nextGestor;
		//aux->nextGestor = NULL;            // Possivelmente, deveria libertar o aux em vez de o colocar a apontar para NULL
		free(aux);
		res = true;
		return head;
	}

	// Caso em que o gestor removido está no meio ou no fim da lista.
	aux = aux->nextGestor;
	while (aux != NULL) {
		if (ComparaGestores(aux, gestorRemovido) == 1) {
			anterior->nextGestor = aux->nextGestor;
			//aux->nextGestor = NULL;
			res = true;
			free(aux);
			return head;
		}
		else {
			anterior = anterior->nextGestor;
			aux = aux->nextGestor;
		}
	}
	res = false;
	return head;

}

//Tenho de acrescentar um parametros para me dizer aquilo que aconteceu - um inteiro talvez
/**
 * Função para alterar os dados de um determinado gestor na lista de gestores.
 */
ListaGestores* AlterarGestores(ListaGestores* head, Gestor* gestorAlterar, Gestor* novoGestor) {
	if (VerificaGestores(head, gestorAlterar)) {
		head = RemoverGestores(head, gestorAlterar);
		head = InserirGestores(head, novoGestor);
	}
	return head;

}

/**
 * Função que compara dois Gestores.
 *
 * Caso os dois Gestores sejam iguais em todos os parametros, retorna 1.
 * Caso os dois Gestores sejam diferentes em qualquer parametro, retorna 0.
 */
int ComparaGestores(Gestor* g1, Gestor* g2) {
	if ((g1->nif == g2->nif) && (g1->idade == g2->idade) && (g1->nome == g2->nome)) {
		return 1;
	}
	else {
		return 0;
	}
}

//Posso melhorar estas funções para me dizerem onde está aquilo que procuro ou criar umas novas que o façam
/**
 * Função que verifica se um determinado Gestor está presente na Lista de Gestores.
 *
 * Caso o Gestor esteja presente na Lista, retorna true.
 * Caso o Gestor não esteja presente na Lista, retorna false.
 */
bool VerificaGestores(ListaGestores* head, Gestor* gestor) {
	ListaGestores* aux = head;
	while (aux != NULL) {
		if (ComparaGestores(aux, gestor) == 1) {
			return true;
		}
		aux = aux->nextGestor;
	}
	return false;
}

/**
 * Imprime os dados dos Gestores presentes numa determinada lista dos mesmos.
 */
int ImprimirGestores(ListaGestores* head) {

}
