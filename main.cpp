#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MAX_COL 10 //número máximo de colunas da mesa
#define MAX_LIN 10 //número máximo de linhas da mesa
#define TAM MAX_COL*MAX_LIN //com base no numero de colunas e linhas, define o tamanho máximo da linha estática
#define VERMELHO 4

typedef struct tipo_item{
	int item, acima, abaixo, dir esq;
}item;

typedef struct tipo_lista{
	struct tipo_item item[TAM];
}mesa;

int obter_posicao(int coluna, int linha){
	return ((MAX_LIN*linha) - (MAX_COL-coluna));
}

int obter_acima(int atual){ //retorna qual é a posição "acima" de um elemento
	if(atual >= MAX_COL)
		return atual - MAX_COL;
	else return -1; //caso estivermos na primeira linha
}

int obter_abaixo(int atual){ //retorna qual é a posicão "abaixo" de um elemento
	if(atual >= (TAM - MAX_LIN))
		return -1; //caso estivermos na ultima linha
	else return atual + MAX_COL;
}

int obter_esq(int atual){ //retorna qual é a posição "à esquerda" de um elemento
	if(atual%MAX_COL == 0) //termina em 0, ou seja, coluna 0
		return -1; //caso estivermos na primeira coluna
	else return atual - 1;
}

int obter_dir(int atual){
	if(atual%MAX_COL == 9) //termina em 9, ou seja, coluna 9
		return -1; //caso estivermos na ultima coluna
	else return atual + 1;
}

void prepara_mesa(mesa* m){
	for(int i=0; i<TAM; i++){
		m->item[i].item = VERMELHO;
		m->item[i].acima = obter_acima(i);
		m->item[i].abaixo = obter_abaixo(i);
		m->item[i].esq = obter_esq(i);
		m->item[i].dir = obter_dir(i);
	}
}

void mostra_mesa(mesa* m){
	cout << "  1  2  3  4  5  6  7  8  9" << endl;
	for(int j=0; j<MAX_LIN; j++){
		cout << j << "  ";
		for(int i=0; i<MAX_COL; i++){
			cout << m->item[i].item << " ";
		}
		cout << endl;
	}
}