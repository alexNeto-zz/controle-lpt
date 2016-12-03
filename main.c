#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void bemVindo(); 	// prototipo da funcao de boas vindas
void menuPrincipal();
void recebeVariaveis(); // prototipo da funcao input sequencia
void sequencia(int quantPassos, int passos[], int atraso, int repeticao);	// prototipo da funcao de sequencia
void atrasoFuc(int atraso); // prototipo da funcao atraso
int carregaLib();

int main(){
	bemVindo();
	if(carregaLib() == -1) return -1;
	short escolha = 0;
	while(1){
		system("cls");
		menuPrincipal();
		scanf("%d", &escolha);
		if(escolha == 1) recebeVariaveis();
		else if(escolha = 2) break;
		else printf("Escolha invalida");
	}
	system("exit");
	
	return 0;
}

/** Funcao de boas vindas **/
void bemVindo(){
	system("title CONTROLE PORTA PARALELA"); // Muda o titulo da janela
	printf("Bem-vindo ao controle de porta paralela\n"); // Mensagem de boas vindas
	int i;
	for(i = 0; i < 39; i++){
		printf("=");
		atrasoFuc(5);
	}
	system("cls");
}
int carregaLib(){
	typedef short _stdcall (*PtrInp)(short EndPorta);
	typedef void _stdcall (*PtrOut)(short EndPorta, short valor);
	HINSTANCE hLib; //Instância para a DLL inpout32.dll.
   	PtrInp inportb;     //Instância para a função Imp32(). 
   	PtrOut outportb;  //Instância para a função Out32().

   //Carrega a DLL na memória.
   hLib = LoadLibrary("inpout32.dll");

   if(hLib == NULL) //Verifica se houve erro.
   {
      printf("Erro. O arquivo inpout32.dll não foi encontrado.\n");
      getch();
      return -1;
   }

   //Obtém o endereço da função Inp32 contida na DLL.
   inportb = (PtrInp) GetProcAddress(hLib, "Inp32");

   if(inportb == NULL) //Verifica se houve erro.
   {
      printf("Erro. A função Inp32 não foi encontrada.\n");
      getch();
      return -1;
   }

   //Obtém o endereço da função Out32 contida na DLL.
   outportb = (PtrOut) GetProcAddress(hLib, "Out32");

   if(outportb == NULL) //Verifica se houve erro.
   {
       printf("Erro. A função Out32 não foi encontrada.\n");
       getch();
       return -1;
   }
}
/** funcao de exibicao do menu principal **/
void menuPrincipal(){
	printf("escolha\t\tfuncao\n\n"); // Cabecalho do menu Inicial
	/*** Itens do menu ***/
	printf("1\t\tIniciar sequencia\n");
	printf("2\t\tSair\n");
}
/** Funcao para definir a sequencia de LEDs acesos **/
void recebeVariaveis(){
	system("cls");
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
			printf("Digite o %dº passo: ", i);
			scanf("%d", &passos[i]);
	}
	int atraso = 0; // Variavel para receber o tempo entre cada passo
	printf("Digite o intervalo entre cada passo (em ms, e apenas inteiros): ");
	scanf("%d", &atraso);
	int repeticao = 0;
	printf("Digite quantas vezes a sequencia se repetira: ");
	scanf("%d", &repeticao);
	sequencia(quantPassos, passos, atraso, repeticao);
}
/** funcao que faz sequencia **/
void sequencia(int quantPassos, int passos[], int atraso, int repeticao){
	int i, j;
	for(i = 0; i < repeticao; i++)
		for(j = 0; j < quantPassos; j++){
			outportb(0x378, passos[j]);
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
