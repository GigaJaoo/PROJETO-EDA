/*****************************************************************//**
 * \file   Meios.c
 * \brief  Funções dos Meios de Mobilidade Elétricos.
 * 
 * \author João Pereira - a24254
 * \date   March 2023
 *********************************************************************/

#include "Assinaturas.h"

//Duvidas
 /**
  * Função para armazenar a lista dos meios de mobilidade elétricos em ficheiro de texto.
  *
  * Caso consiga guardar a lista no ficheiro, retorna 1.
  * Caso a lista esteja vazia, retorna 0.
  * Caso não consiga guardar a lista no ficheiro, retorna -1.
  */
int ArmazenarMeios(ListaGestores* head, char fileName[]) {
	if (head == NULL) {
		return 0;
	}
	ListaMeios* aux = head;
	FILE* fMeios;
	fMeios = fopen(fileName, "w");
	if (fMeios == NULL) {
		return (-1);
	}
	while (aux != NULL) {
		fprintf(fMeios, "%d;%d;%d\n", aux->meio->autonomia, aux->meio->geocodigo, (int)aux->meio->tipo);        //duvida de como ficará escrito o tipo de transporte
		aux = aux->nextMeio;
	}
	fclose(fMeios);
	return 1;
}

/**
 * Função para armazenar a lista dos meios de mobilidade elétricos em ficheiro binário.
 *
 * Caso consiga guardar a lista no ficheiro, retorna 1.
 * Caso a lista esteja vazia, retorna 0.
 * Caso não consiga guardar a lista no ficheiro, retorna -1.
 */
int ArmazenarMeiosBin(ListaGestores* head, char fileName[]) {
	if (head == NULL) {
		return 0;
	}
	ListaMeios* aux = head;
	FILE* fMeiosBin;
	fMeiosBin = fopen(fileName, "wb");
	if (fMeiosBin == NULL) {
		return (-1);
	}
	while (aux != NULL) {
		fwrite(&aux->meio, 1, sizeof(MeiosMobElet), fMeiosBin);
		aux = aux->nextMeio;
	}
	fclose(fMeiosBin);
	return 1;
}

//Duvidas
/**
 * Função para ler a lista dos meios de mobilidade elétricos de ficheiro de texto.
 *
 * Caso não consiga ler a lista a partir do ficheiro, retorna 0.
 * Caso consiga ler a lista a partir do ficheiro, retorna a lista lida.
 */
 ListaMeios* LerMeios(char fileName[]) {
 	ListaMeios* head = NULL;
 	FILE* fMeios;
 	fMeios = fopen(fileName, "r");
 	if (fMeios == NULL) {
 		return 0;
 	}
 
 	MeiosMobElet aux;      //Não é apontador aqui
 	int transporte;
 	while (!feof(fMeios)) {
 		fscanf(fMeios, "%d;%d;%d\n", &aux.autonomia, &aux.geocodigo, &transporte);             //utilizar . em vez de -> no fscanf
 		aux.tipo = (TipoTransporte)transporte;
 		head = InserirMeio(head, &aux);
 	}
 	fclose(fMeios);
 
 	return head;
 }

/**
  * Função para ler a lista dos meios de mobilidade elétricos de ficheiro binário.
  *
  * Caso não consiga ler a lista a partir do ficheiro, retorna 0.
  * Caso consiga ler a lista a partir do ficheiro, retorna a lista lida.
  */
ListaMeios* LerMeiosBin(char fileName[]) {
	ListaMeios* head = NULL;
	FILE* fMeiosBin;
	fMeiosBin = fopen(fileName, "rb");
	if (fMeiosBin == NULL) {
		return 0;
	}

	MeiosMobElet aux;          //Nao é apontador aqui
	while (fread(&aux, 1, sizeof(MeiosMobElet), fMeiosBin)) {
		head = InserirMeio(head, &aux);
	}
	fclose(fMeiosBin);

	return head;
}

//Tenho de acrescentar um parametro para me dizer aquilo que aconteceu - um inteiro talvez
/**
 * Função para inserir novos dados de um meio de mobilidade elétrico na lista dos meios de mobilidade elétricos por ordem decresecente de autonomia.
 */
ListaMeios* InserirMeio(ListaMeios* head, MeiosMobElet* novoMeio) {
	ListaMeios* aux = (ListaMeios*)malloc(sizeof(ListaMeios));
	aux->nextMeio = NULL;
	aux->meio = novoMeio;

	// Caso a lista de meios seja vazia
	if (head == NULL) {
		head = novoMeio;
		return head;
	}
	else {
		// Inserir por ordem decrescente de autonomia dos meios de mobilidade elétricos
		if (head->meio->autonomia < aux->meio->autonomia) {
			// Para inserir no inicio da lista de meios
			aux->nextMeio = head;
			head = novoMeio;
		}
		else {
			// Para inserir o meio de mobilidade elétrico no meio ou no fim da lista
			ListaMeios* meioAnterior = head;
			ListaMeios* meioAtual = head;

			//Procurar a posição onde vai ser inserido o meio, conforme a ordem da autonomia
			while (meioAtual->meio->autonomia > aux->meio->autonomia) {
				meioAnterior = meioAtual;
				meioAtual = meioAtual->nextMeio;
			}

			aux->nextMeio = meioAtual;
			meioAnterior->nextMeio = aux;
		}
	}
	return head;
}

//Tenho de acrescentar um parametro para me dizer aquilo que aconteceu - um inteiro talvez
//Posso ainda usar as funçoes de verificar a presença para ver se está ou nao na lista e melhorar as funçães de verificarpresença para me dizer onde está
/**
 * Função para remover um determinado meio de mobilidade elétrico da lista de meios de mobilidade elétricos.
 *
 * Caso consiga remover o meio pretendido, retorna a lista sem esse meio.
 * Caso não consiga remover o meio pretendido, retorna a lista sem alterações
 */
ListaMeios* RemoverMeio(ListaMeios* head, MeiosMobElet* meioRemovido) {
	ListaMeios* aux = head;
	ListaMeios* anterior = head;

	// Caso em que o meio removido é o primeiro elemento da lista
	if (ComparaMeios(aux, meioRemovido) == 1) {
		head = aux->nextMeio;
		//aux->nextMeio = NULL;           // Possivelmente, deveria libertar o aux em vez de o colocar a apontar para NULL
		free(aux);
		return head;
	}

	// Caso em que o meio removido está no meio ou no fim da lista.
	aux = aux->nextMeio;
	while (aux != NULL) {
		if (ComparaMeios(aux, meioRemovido) == 1) {
			anterior->nextMeio = aux->nextMeio;
			//aux->nextMeio = NULL;
			free(aux);
		}
		else {
			anterior = anterior->nextMeio;
			aux = aux->nextMeio;
		}
	}
	return head;
}

//Tenho de acrescentar um parametros para me dizer aquilo que aconteceu - um inteiro talvez
/**
 * Função para alterar os dados de um determinado meio de mobilidade elétrico na lista de meios de mobilidade elétricos.
 */
ListaMeios* AlterarMeio(ListaMeios* head, MeiosMobElet* meioAlterar, MeiosMobElet* novoMeio) {
	if (VerificaMeios(head, meioAlterar)) {
		head = RemoverMeio(head, meioAlterar);
		head = InserirMeio(head, novoMeio);
	}
	return head;
}

/**
 * Função que compara dois Meios de Mobilidade Elétricos.
 *
 * Caso os dois Meios sejam iguais em todos os parametros, retorna 1.
 * Caso os dois Meios sejam diferentes em qualquer parametro, retorna 0.
 */
int ComparaMeios(MeiosMobElet* m1, MeiosMobElet* m2) {
	if ((m1->autonomia == m2->autonomia) && (m1->geocodigo == m2->geocodigo) && (m1->tipo == m2->tipo)) {
		return 1;
	}
	else {
		return 0;
	}
}

//Posso melhorar estas funções para me dizerem onde está aquilo que procuro ou criar umas novas que o façam
/**
 * Função que verifica se um determinado Meio está presente na Lista de Meios.
 *
 * Caso o Meio esteja presente na Lista, retorna true.
 * Caso o Meio não esteja presente na Lista, retorna false.
 */
bool VerificaMeios(ListaMeios* head, MeiosMobElet* meio) {
	ListaMeios* aux = head;
	while (aux != NULL) {
		if (ComparaMeios(aux, meio) == 1) {
			return true;
		}
		aux = aux->nextMeio;
	}
	return false;
}

/**
 * Imprime os dados dos Meios de Mobilidade El�tricos numa determinada lista dos mesmos.
 */
int ImprimirMeios(ListaMeios* head) {

}
