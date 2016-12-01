#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bemVindo(); 	// prototipo da funcao de boas vindas
void sequencia();	// prototipo da funcao de sequencia
void ajuda();		// prototipo da funcao de ajuda
int main(){


	bemVindo();
	short escolha = 0;
	scanf("%d", &escolha);
	switch(escolha){
		case 1:
			sequencia();
			break;
		case 2:
			ajuda();
			break;
		case 3:
			system("exit");
		default:
			// TODO
			break;
	}

	return 0;
}

/** Funcao de boas vindas e exibicao do menu principal **/
void bemVindo(){
	system("title CONTROLE PORTA PARALELA");
	system("cls");
	printf("Bem-vindo ao controle de porta paralela\n");
	printf("escolha\t\tfuncao\n\n");
	printf("1\t\tIniciar sequencia\n");
	printf("2\t\tAjuda\n");
	printf("3\t\tSair");
}
/** Funcao para exibir ajuda **/
void ajuda(){
	system("cls");
	printf("AJUDA:\n");
	printf("Para criar uma sequencia, basta digitar\n\
 no campo 'TODO' a quantodade de passos.\n\
 no campo 'TODO' digite quantas vezes a sequencia se repetira\n\
 no campo 'TODO' digite intervalo entre cada passo\n");
	printf("E pronto, voce criou uma sequencia!");
	system("cls");
}
/** Funcao para definir a sequencia de LEDs acesos **/
void sequencia(){
}
void atraso(int atraso){
	int x;
	clock_t Ini;  //Criação da variavel relógio
	Ini = clock(); //Inicialização do relógio
	while(((clock() - Ini) / (CLOCKS_PER_SEC / 100)) <= 10){  //Executa o while por 10ms antes de retornar o valor
			x++;
	}
}
