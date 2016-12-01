#include <stdio.h>		
#include <stdlib.h>	

/*
*
* Desenvolvedor -- Alexandre Neto
* Equipe -- Alberto Leao
* 			Anderson Cruz
* 			Edilberto Rodrigues
* 			Tiago Soares
*
* Versão 0.1 -- alfa 
* 	adicionado I/O 
*	tarefas basicas com saida no console padrao
*
*/

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

void bemVindo(){
	system("title CONTROLE PORTA PARALELA");
	printf("Bem-vindo ao controle de porta paralela\n");
	printf("escolha\t\tfuncao\n");
	printf("1\t\tIniciar sequencia\n");
	printf("2\t\tAjuda\n");
	printf("3\t\tSair");
}
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
void sequencia(){
}
