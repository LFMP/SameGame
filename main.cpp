#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define MAX_COL 10 //número máximo de colunas da mesa
#define MAX_LIN 10 //número máximo de linhas da mesa
#define TAM MAX_COL*MAX_LIN //com base no numero de colunas e linhas, define o tamanho máximo da linha estática
#define NORMAL "\033[0m"
#define VERMELHO "\033[1;31m|00|"
#define VERDE "\033[1;32m|00|"
#define AMARELO "\033[1;33m|00|"
#define AZUL "\033[1;34m|00|"
#define ROXO "\033[1;35m|00|"
#define VAZIO "\033[1m     "

//SAME GAME - IMPLEMENTADO COM C/C++ - DESENVOLVIDO PARA LINUX

typedef struct tipo_item{
	int acima, abaixo, dir, esq;
	string cor;
}item;

typedef struct tipo_lista{
	struct tipo_item item[TAM];
}mesa;

int obter_posicao(int coluna, int linha){
	return ((MAX_LIN*(linha+1)) - (MAX_COL - (coluna+1)) - 1);
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

string obter_cor(int atual){ //essa função retorna uma constante que contém uma cor. A chamada é feita com um número aleatório de 0 a 5
	switch(atual){
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
	}
}

void prepara_mesa(mesa* m){ //função usada para preencher a mesa com cores aleatórias e posições da região de um item
	srand(time(NULL));
	for(int i=0; i<TAM; i++){
		m->item[i].cor = obter_cor(rand()%5);
		m->item[i].acima = obter_acima(i);
		m->item[i].abaixo = obter_abaixo(i);
		m->item[i].esq = obter_esq(i);
		m->item[i].dir = obter_dir(i);
	}
}

void mostra_mesa(mesa* m){ //função usada para printar a mesa na tela
	cout << "   ";
	for(int i=0; i<MAX_COL; i++){
		if(i < 10)
			cout << "  0" << i;
		else cout << "  " << i;
	}
	cout << endl;

    for(int linha=0; linha<MAX_LIN; linha++){
        if(linha < 10)
            cout << "0" << linha << "  ";
        else cout << linha << "  ";
        for(int coluna=0; coluna<MAX_COL; coluna++){
            cout << m->item[obter_posicao(coluna, linha)].cor << NORMAL;
        }
        cout << endl;
    }
}

void reorganiza_coluna(mesa* m){ //função utilizada para "puxar" elementos vazios para cima
	int posicao;

	for(int k=0; k<MAX_LIN; k++){
		for(int linha=0; linha<MAX_LIN; linha++){
			for(int coluna=0; coluna<MAX_COL; coluna++){
				posicao = obter_posicao(coluna, linha);
				if(m->item[posicao].cor == VAZIO && obter_acima(posicao) != -1){
					m->item[posicao].cor = m->item[obter_acima(posicao)].cor;
					m->item[obter_acima(posicao)].cor = VAZIO;
				}
			}
		}
	}
}

int main(){
	mesa Jogo;

	prepara_mesa(&Jogo);
	mostra_mesa(&Jogo);
}