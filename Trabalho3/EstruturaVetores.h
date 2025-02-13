#define SUCESSO -1
#define SEM_ESPACO -2
#define SEM_ESTRUTURA_AUXILIAR -3
#define JA_TEM_ESTRUTURA_AUXILIAR -4
#define POSICAO_INVALIDA -5
#define SEM_ESPACO_DE_MEMORIA -6
#define TAMANHO_INVALIDO -7
#define ESTRUTURA_AUXILIAR_VAZIA -8
#define NUMERO_INEXISTENTE -9
#define NOVO_TAMANHO_INVALIDO -10
#define TODAS_ESTRUTURAS_AUXILIARES_VAZIAS -11
#define ERRO_ABRIR_ARQUIVO -12
#define ESTRUTURA_VAZIA -13
#define TAM 10
#define TAM_LINHA 100

// Estrutura Principal
typedef struct principal{
	int *auxiliar; // VAI APONTAR PARA A ESTRUTURA AUXILIAR
	int tamanho; // TAMANHO DA ESTRUTURA AUXILIAR
	int qtd; // ELE VAI CONTAR A QUANTIDADE DE ELEMENTOS no VETOR
}Principal;

// Estrutura Auxiliar
typedef struct no{
	int conteudo;
	struct no *prox;
}No;

int criarEstruturaAuxiliar(int tamanho, int posicao);
int inserirNumeroEmEstrutura(int valor, int posicao);
int excluirNumeroDoFinaldaEstrutura(int posicao);
int excluirNumeroEspecificoDeEstrutura(int valor, int posicao);
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int modificarTamanhoEstruturaAuxiliar(int posicao, int PrincipalvoTamanho);
int getQuantidadeElementosEstruturaAuxiliar(int posicao);
No* montarListaEncadeadaComCabecote();
void getDadosListaEncadeadaComCabecote(No* inicio, int vetorAux[]);
void destruirListaEncadeadaComCabecote(No** inicio);

void inicializar();
void finalizar();
void dobrar(int *x);

int salvaEstrutura();
int gravaNoArquivo(int indice, int tamanho, int qtd, int elementos[]);
