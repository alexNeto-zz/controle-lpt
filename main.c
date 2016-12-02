#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bemVindo(); 	// prototipo da funcao de boas vindas
void menuPrincipal();
void recebeVariaveis(); // prototipo da funcao input sequencia
void sequencia(int quantPassos, int passos[], int atraso);	// prototipo da funcao de sequencia
void ajuda();		// prototipo da funcao de ajuda
void atrasoFuc(int atraso); // prototipo da funcao atraso


int main(){

	bemVindo();
	short escolha = 0;
	while(1){
		menuPrincipal();
		scanf("%d", &escolha);
		switch(escolha){
			case 1:
				recebeVariaveis();
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
	}
	return 0;
}

/** Funcao de boas vindas **/
void bemVindo(){
	system("title CONTROLE PORTA PARALELA"); // Muda o titulo da janela
	system("cls"); // limpa a janela
	printf("Bem-vindo ao controle de porta paralela\n"); // Mensagem de boas vindas
}
/** funcao de exibicao do menu principal **/
void menuPrincipal(){
	printf("escolha\t\tfuncao\n\n"); // Cabecalho do menu Inicial
	/*** Itens do menu ***/
	printf("1\t\tIniciar sequencia\n");
	printf("2\t\tAjuda\n");
	printf("3\t\tSair\n");
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
void recebeVariaveis(){
	int quantPassos = 0; // Variavel que ira receber a quantidade de passos
	printf("Digite a quantidade de passos: "); // Mensagem com informacao para usuario
	scanf("%d", &quantPassos); // Recebe o valor digitado, sem tratamento
	int passos[quantPassos]; // Declara um array de tamanho "quantPassos"
	int i; // Declara um contador
	/*** Loop para zerar todas as posicoes do array ***/
	for(i = 0; i < quantPassos; i++){
		passos[i] = 0;
	}
	/*** Loop para armazenar cada passo ***/
	for(i = 0; i < quantPassos; i++){
			printf("Digite o %dº passo: ");
			scanf("%d", &passos[i]);
	}
	int atraso = 0; // Variavel para receber o tempo entre cada passo
	printf("Digite o intervalo entre cada passo (em ms, e apenas inteiros): ");
	scanf("%d", &atraso);
	sequencia(quantPassos, passos, atraso);
}
/** funcao que faz sequencia **/
void sequencia(int quantPassos, int passos[], int atraso){
	int i;
	for(i = 0; i < quantPassos; i++){
			printf("%d\n", passos[i]);
			atrasoFuc(atraso);
	}

}
/** funcao de atraso **/
void atrasoFuc(int atraso){
	int x; // Define o contador
	clock_t Ini;  //Criacao da variavel relogio
	Ini = clock(); //Inicializacao do relogio
	 //Executa o while por 10ms antes de retornar o valor
	while(((clock() - Ini) / (CLOCKS_PER_SEC / 100)) <= atraso){
			x++;
	}
}
