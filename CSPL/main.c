/** Bibliotecas necess�rias **/
#include <stdio.h>      // printf() e scanf()
#include <stdlib.h>     // system()
#include <time.h>       // Usar o relogio
#include <windows.h>    // Importar o inpout32.dll
/** Configura��o da porta paralela **/
// Cria um "tipo de v�riavel" chamada PtrInp
typedef short _stdcall (*PtrInp)(short EndPorta); // Para entrada de dados via LPT
// Cria um "tipo de v�riavel" chamada PtrOut
typedef void _stdcall (*PtrOut)(short EndPorta, short valor); // Para saida de dados via LPT

HINSTANCE hLib;     //Inst�ncia para a DLL inpout32.dll.
PtrInp inportb;     //Inst�ncia para a fun��o Imp32().
PtrOut outportb;    //Inst�ncia para a fun��o Out32().

/** Prot�tipos das fun��es **/
void bemVindo(); 	               // prototipo da funcao de boas vindas
void menuPrincipal();              // Prototipo da funcao de menu inicial
void recebeVariaveis();            // prototipo da funcao input sequencia
void sequencia(int quantPassos,
               int passos[],
               int atraso,
               int repeticao);	   // prototipo da funcao de sequencia
void atrasoFuc(int atraso);        // prototipo da funcao atraso
int carregaLib();
/** E aqui que o programa comeca a executar **/
int main(){
    // chama a funcao de boas-vindas
	bemVindo();
	// chama a funcao que vai carregas o inpout32.dll
	// caso de algum erro, a funcao retornara -1
	// se tudo der certo retornara 0
	if(carregaLib() == -1) return -1;
	// declara uma variavel do tipo short
	// (short � um inteiro pequeno)
	// escolha sera usada para armazenar
	// o item do menu seleciuonado pelo usuario
	short escolha = 0;
	// loop para repetir o codigo emquanto necessario
	while(1){
        // apaga todos os LEDs da porta paralela
		outportb(0x378, 0);
		// apaga todo conteudo da janela
		system("cls");
		// chama a funcao menuPrincipal
		menuPrincipal();
		// armazena o valor digitado na variavel escolha
		scanf("%d", &escolha);
		// caso o primeiro item seja celecionado
		// sera chamada a funcao recebeVariaveis
		// com o parametro 0
		if(escolha == 1) recebeVariaveis(0);
		// se o segundo item for selecionado
		// o parametro sera 1
		else if(escolha == 2) recebeVariaveis(1);
		// caso a terceira opcao seja escolhida
		// saira do looping e executara a linha
		// system("exit"); que fechara a janela
		else if(escolha == 3) break;
		// se for escolhido qualquer outra coisa
		// aparecera a mensagem abaixo, que ficara
		// visivel por 50 ms
		else{
			printf("Escolha invalida");
			atrasoFuc(50);
		}
	}
	system("exit");

	return 0;
}
/** Funcao de boas vindas **/
void bemVindo(){
	system("title CONTROLE PORTA PARALELA"); // Muda o titulo da janela
	printf("Bem-vindo ao controle de porta paralela\n"); // Mensagem de boas vindas
	int i;
	// loop para aparecer uma barra de carregando
	// formada por iguais
	// ==========================================
	for(i = 0; i < 39; i++){
		printf("=");
		atrasoFuc(5);
	}
	// limpa todo o conteudo da janela
	system("cls");
}
/** funcao que carrega input32.dll **/
int carregaLib(){

   //Carrega a DLL na mem�ria.
   hLib = LoadLibrary("inpout32.dll");

   if(hLib == NULL) //Verifica se houve erro.
   {
      printf("Erro. O arquivo inpout32.dll n�o foi encontrado.\n");
      getch();
      return -1;
   }

   //Obt�m o endere�o da fun��o Inp32 contida na DLL.
   inportb = (PtrInp) GetProcAddress(hLib, "Inp32");

   if(inportb == NULL) //Verifica se houve erro.
   {
      printf("Erro. A fun��o Inp32 n�o foi encontrada.\n");
      getch();
      return -1;
   }

   //Obt�m o endere�o da fun��o Out32 contida na DLL.
   outportb = (PtrOut) GetProcAddress(hLib, "Out32");

   if(outportb == NULL) //Verifica se houve erro.
   {
       printf("Erro. A fun��o Out32 n�o foi encontrada.\n");
       getch();
       return -1;
   }
}
/** funcao de exibicao do menu principal **/
void menuPrincipal(){
	printf("escolha\t\tfuncao\n\n"); // Cabecalho do menu Inicial
	/*** Itens do menu ***/
	printf("1\t\tIniciar sequencia em decimal\n");
	printf("2\t\tIniciar sequencia em binario\n");
	printf("3\t\tSair\n");
}
/** Funcao para definir a sequencia de LEDs acesos **/
void recebeVariaveis(int binario){ // o parametro int binario sera usado para verificar se
                                   // precisa de convercao ou nao
	system("cls");  // limpa todo conteudo da janela
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
	if(binario == 0) // verifica parametro binario
		for(i = 0; i < quantPassos; i++){
			do{
			printf("Digite o %d passo (menor  que 255): ", i + 1);
			scanf("%d", &passos[i]);
		}while(passos[i] > 255);
	}
	else
		for(i = 0; i < quantPassos; i++){
			printf("Digite o %d passo (8 bits): ", i);
			int valorBinario;
			scanf("%d", &valorBinario);
			// chama a funcao quem converte de binario para decimal
			// e amarzena na lista passos, na posicao i
			passos[i] = converteParaDecimal(valorBinario);
		}
	int atraso = 0; // Variavel para receber o tempo entre cada passo
	printf("Digite o intervalo entre cada passo (em ms, e apenas inteiros): ");
	scanf("%d", &atraso);
	int repeticao = 0;
	printf("Digite quantas vezes a sequencia se repetira: ");
	scanf("%d", &repeticao);
	sequencia(quantPassos, passos, atraso, repeticao);
}
/** funcao que converte de binario para decimal **/
int converteParaDecimal(int valorBinario){
	int valorDecimal = 0;
	int potencia = 1;
	// representacao em codigo da formula
	// (D * 2 ^ P) + (D * 2 ^ P-1) + ... + (D * 2 ^ P-n)
	while(valorBinario > 0){
		valorDecimal += valorBinario % 10 * potencia;
		valorBinario /= 10;
		potencia *= 2;
	}
	// retorna o valor convertido
	return valorDecimal;
}
/** funcao que faz sequencia **/
void sequencia(int quantPassos, int passos[], int atraso, int repeticao){
	// variaveis para contador
	int i, j;
	// limpa todo conteudo da janela
	system("cls");
	// for para a quantidade de vezes que se deseja
	// repetir a sequencia
	for(i = 0; i < repeticao; i++){
		printf("Sequencia em progresso");
		// loop para percorrer a lista passos
		// e ligar os LEDs de acordo com o valor
		// de cada posicao
		for(j = 0; j < quantPassos; j++){
			if(j % 3 == 0) printf("."); // so para mostrar algun status no console
			outportb(0x378, passos[j]); // imprime na porta LPT
			atrasoFuc(atraso);          // chama a funcao atrado com o atraso digitado
		}
		system("cls"); //  apaga todo o conteudo da janela
	}
}
/** funcao de atraso **/
void atrasoFuc(int atraso){
	int x; // Define o contador
	clock_t Ini;  //Criacao da variavel relogio
	Ini = clock(); //Inicializacao do relogio
	 //Executa o while por "atraso" antes de retornar o valor
	while(((clock() - Ini) / (CLOCKS_PER_SEC / 100)) <= atraso){
		x++;
	}
}
