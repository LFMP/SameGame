#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MAX_COL 10 //número máximo de colunas da mesa
#define MAX_LIN 10 //número máximo de linhas da mesa
#define TAM MAX_COL*MAX_LIN //com base no numero de colunas e linhas, define o tamanho máximo da linha estática
#define NORMAL "\033[0m"
#define VERMELHO "\033[1;31m|000|"
#define VERDE "\033[1;32m|000|"
#define AMARELO "\033[1;33m|000|"
#define AZUL "\033[1;34m|000|"
#define ROXO "\033[1;35m|000|"
#define VAZIO "\033[1m     "

typedef struct tipo_item{
	int acima, abaixo, dir, esq;
	string atual;
}item;

typedef struct tipo_lista{
	struct tipo_item item[TAM];
}mesa;

int obter_posicao(int coluna, int linha){
	return ((MAX_LIN*(linha+1)) - (MAX_COL - (coluna+1) - 1));
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
	if(atual%MAX_COL == 0) //se atual está na primeira coluna
		return -1; //caso estivermos na primeira coluna
	else return atual - 1;
}

int obter_dir(int atual){
	if(atual%MAX_COL == MAX_COL-1) //se atual está na última coluna
		return -1; //caso estivermos na ultima coluna
	else return atual + 1;
}

string obter_cor(int atual){
	//atual = rand()%6;
	switch(atual%6){
		case 0:
			return VERMELHO;
		break;

		case 1:
			return VERDE;
		break;

		case 2:
			return AMARELO;
		break;

		case 3:
			return AZUL;
		break;

		case 4:
			return ROXO;
		break;

		default:
			return VERMELHO;
		break;
	}
}

void prepara_mesa(mesa* m){
	srand(time(NULL));
	for(int i=0; i<TAM; i++){
		m->item[i].atual = obter_cor(i);
		m->item[i].acima = obter_acima(i);
		m->item[i].abaixo = obter_abaixo(i);
		m->item[i].esq = obter_esq(i);
		m->item[i].dir = obter_dir(i);
	}
}

void mostra_mesa(mesa* m){
	cout << "     0    1    2    3    4    5    6    7    8    9" << endl;
	for(int j=0; j<MAX_LIN; j++){
		cout << j << "  ";
		for(int i=0; i<MAX_COL; i++){
			cout << m->item[i].atual << NORMAL;
		}
		cout << endl;
	}
}

int main(){
	mesa Jogo;

	prepara_mesa(&Jogo);
	mostra_mesa(&Jogo);
}