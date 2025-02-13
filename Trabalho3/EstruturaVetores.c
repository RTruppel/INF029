#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EstruturaVetores.h"

Principal vetorPrincipal[TAM];

/*
Abre arquivo
caso vazio, fecha e inicia a aplicaçãovazia
caso tenha algo separo as informações por variável.
indice
tamanho
qtd
elementos na estrturua auxiliar

depois utilizo as funções existentes para preencher a aplicação.

*/

void lerArquivo() {
    FILE *input = fopen("estrutura.txt", "r");

    if (input == NULL) {
        // Se o arquivo não existir, cria um novo e encerra a função
        input = fopen("estrutura.txt", "w");
        if (input == NULL) {
            printf("Erro ao criar o arquivo.\n");
            return;
        }
        fclose(input);
        printf("Arquivo criado com sucesso.\n");
        return;
    }

    char linha[1001];
    while (fgets(linha, 1001, input) != NULL) {
        int vetor[100]; // Vetor para armazenar os números lidos
        char numero[100]; // Buffer para armazenar cada número como string
        int j = 0; // Índice para o buffer 'numero'
        int h = 0; // Índice para o vetor 'vetor'
        int posicao = -1, tamanho = -1;

        for (int x = 0; x < strlen(linha); x++) {
            if (linha[x] != ';') {
                numero[j] = linha[x];
                j++;
            } else {
                numero[j] = '\0'; // Finaliza a string
                vetor[h] = atoi(numero); // Converte para inteiro
                h++;
                j = 0; // Reinicia o índice do buffer 'numero'
            }
        }

        // Processa os números lidos
        for (int x = 0; x < h; x++) {
            if (x == 0) {
                posicao = vetor[x];
            } else if (x == 1) {
                tamanho = vetor[x];
                criarEstruturaAuxiliar(posicao, tamanho);
            } else {
                inserirNumeroEmEstrutura(vetor[x], posicao);
            }
        }
    }

    fclose(input);
}


/*  **** ESTÁVEL ****  */

void dobrar(int *x){
    *x = *x * 2;
}

// Objetivo: inicializa o programa. deve ser chamado no inicio do programa 
void inicializar(){
    int i;

    for (i = 0; i < TAM; i++){
        vetorPrincipal[i].auxiliar = NULL;
        vetorPrincipal[i].qtd = 0;
        vetorPrincipal[i].tamanho = 0;
    }

    // lerArquivo();
} 

int posicaoInvalida(int posicao){
    if (posicao < 1 || posicao > TAM)
        return 1;
    else
        return 0;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'
*/
int criarEstruturaAuxiliar(int tamanho, int posicao){
  
  if (tamanho < 1 )
    return TAMANHO_INVALIDO;

  if (posicaoInvalida(posicao))
    return POSICAO_INVALIDA;
    
  posicao -= 1; // o vetor vai de 0 - 9

  if (vetorPrincipal[posicao].auxiliar != NULL)
    return JA_TEM_ESTRUTURA_AUXILIAR;
  
  vetorPrincipal[posicao].auxiliar = (int*)malloc(tamanho*sizeof(int)); // AUXILIAR É UM PONTEIRO DO TIPO INTEIRO

  if (vetorPrincipal[posicao].auxiliar == NULL)
      return SEM_ESPACO_DE_MEMORIA;

  vetorPrincipal[posicao].tamanho = tamanho;
  
  return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
RertoPrincipal (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    // 12445
CONSTANTES
    JÁ TEM 
*/
int inserirNumeroEmEstrutura(int valor, int posicao){

    if (posicaoInvalida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;

    if (vetorPrincipal[posicao].auxiliar == NULL )
        return SEM_ESTRUTURA_AUXILIAR;
    
    int qtd = vetorPrincipal[posicao].qtd;

    if (qtd >= vetorPrincipal[posicao].tamanho)
      return SEM_ESPACO;

    vetorPrincipal[posicao].auxiliar[qtd] = valor;
    vetorPrincipal[posicao].qtd ++; // ELE CONSEGUIU COLOCAR O VALOR NA ESTRUTURA

    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar Principal final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma 
[3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica
*/
int excluirNumeroDoFinaldaEstrutura(int posicao){
    
    if (posicaoInvalida(posicao) == 1)
        return POSICAO_INVALIDA;

    posicao -= 1;

    if (vetorPrincipal[posicao].auxiliar == NULL)
        return SEM_ESTRUTURA_AUXILIAR;
  
    if (vetorPrincipal[posicao].qtd == 0) // DEPOIS TENHO QUE VERIFICAR SE EXISTE OUTRA FORMA
        return ESTRUTURA_AUXILIAR_VAZIA;

    vetorPrincipal[posicao].qtd --; // EXCLUSÃO LÓGICA
  
  return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve 
ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
*/
int excluirNumeroEspecificoDeEstrutura(int valor, int posicao){

    int i, j;
    int existe = 0;
    int aux;

    if (posicaoInvalida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;

    if (vetorPrincipal[posicao].auxiliar == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    int qtd = vetorPrincipal[posicao].qtd;

    if (qtd == 1 && vetorPrincipal[posicao].auxiliar[0] == valor)
      existe = 1;

    else
      for (i = 0; i < qtd-1; i++)
        // Se for encontrado, ele vai ser colocado no final do vetor
        if (vetorPrincipal[posicao].auxiliar[i] == valor){
          aux = vetorPrincipal[posicao].auxiliar[i];
          vetorPrincipal[posicao].auxiliar[i] = vetorPrincipal[posicao].auxiliar[i+1];
          vetorPrincipal[posicao].auxiliar[i+1] = aux;

          existe = 1;
        }
    
    if (existe == 0)
        return NUMERO_INEXISTENTE;
    else
      vetorPrincipal[posicao].qtd --;
    
    return SUCESSO;
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux
*/

// PEGA DADOS DO AUXILIAR E COLOCA EM OUTRO VETOR
void getDadosAux(int posicao, int vetorAux[], int n){ 

    int i;
    for (i = 0; i < n; i++)
        vetorAux[i] = vetorPrincipal[posicao].auxiliar[i];
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){

    if (posicaoInvalida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;

    if (vetorPrincipal[posicao].auxiliar == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    int qtd = vetorPrincipal[posicao].qtd;

    getDadosAux(posicao,vetorAux, qtd);

    return SUCESSO;

}


/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux
*/

// Algoritmo de Ordenação Simples
void bubble(int vet[], int n){ 
    int i, j, aux;

    for (i = n -1; i > 0; i--)
        for (j = 0; j < i; j++)
            if(vet[j] > vet[j + 1]){
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){

    if (posicaoInvalida(posicao))
        return POSICAO_INVALIDA;

    posicao -= 1;

    if (vetorPrincipal[posicao].auxiliar == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    int qtd = vetorPrincipal[posicao].qtd;

    getDadosAux(posicao, vetorAux, qtd); // PEGO OS DADOS

    bubble(vetorAux, qtd); // Ordeno O VETOR

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux
*/

//VERIFICA SE TODAS AS ESTRUTURAS AUXILIARES ESTÃO VAZIAS
int todasEstruturasAuxiliaresVazias(){ 

    int vazia = 0;
    int i;

    for (i = 0; i < TAM; i++)
        if (vetorPrincipal[i].qtd == 0)
            vazia++;
    
    if (vazia == TAM)
        return 1;

    return 0;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){

    if (todasEstruturasAuxiliaresVazias())
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    int i, j;
    int qtd;
    int k = 0;

    for (i = 0; i < TAM; i++){

        if (vetorPrincipal[i].auxiliar != NULL){
            qtd = vetorPrincipal[i].qtd;
        
            for (j = 0; j < qtd; j++, k++)
                 vetorAux[k] = vetorPrincipal[i].auxiliar[j];
        }
    }

    return SUCESSO;
}

// CONTA A QUANTIDADE DE ÍNDICES PREENCHIDOS
int getContadorTodasEstruturaAuxiiares(){ 

    int i,j;
    int contador = 0;

    for (i = 0; i < TAM; i++)
        if (vetorPrincipal[i].auxiliar != NULL)
            contador += vetorPrincipal[i].qtd;

    return contador;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

RertoPrincipal (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){

    if (todasEstruturasAuxiliaresVazias() == 1)
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;

    getDadosDeTodasEstruturasAuxiliares(vetorAux);

    int n = getContadorTodasEstruturaAuxiiares();

    bubble(vetorAux, n);

    return SUCESSO;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o Principalvo tamanho 'PrincipalvoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e Principalvo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

RertoPrincipal (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - Principalvo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do Principalvo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){

    if (posicaoInvalida(posicao))
        return POSICAO_INVALIDA;
    
    posicao -= 1;

    if (vetorPrincipal[posicao].auxiliar == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    novoTamanho += vetorPrincipal[posicao].tamanho;

    if (novoTamanho < 1)
        return NOVO_TAMANHO_INVALIDO;

    vetorPrincipal[posicao].auxiliar = (int*)realloc(vetorPrincipal[posicao].auxiliar, novoTamanho * sizeof(int));

    if (vetorPrincipal[posicao].auxiliar == NULL)
        return SEM_ESPACO_DE_MEMORIA;

    vetorPrincipal[posicao].tamanho = novoTamanho;

    int qtd = vetorPrincipal[posicao].qtd;

    if (qtd > novoTamanho)
        vetorPrincipal[posicao].qtd = novoTamanho;
    else
        vetorPrincipal[posicao].qtd = qtd;
    
    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

RetorPrincipal (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao){

    if (posicaoInvalida(posicao))
        return POSICAO_INVALIDA;
    
    posicao -= 1;

    if (vetorPrincipal[posicao].auxiliar == NULL)
        return SEM_ESTRUTURA_AUXILIAR;

    if (vetorPrincipal[posicao].qtd == 0)
        return ESTRUTURA_AUXILIAR_VAZIA;

    int qtd = vetorPrincipal[posicao].qtd;

    return qtd;

}


//Insere o novo valor no final da lista
int inserirNaLista(No *inicio, int valor){

    if (inicio == NULL) // Nao existe lista
        return 0;

    No *novo = (No*)malloc(sizeof(No)); // Alocando memória para novo

    if (novo == NULL) // Não conseguiu alocar memória
        return 0;

    novo->conteudo = valor;
    novo->prox = NULL;

    if (inicio->prox == NULL){ //Lista vazia, nsira no início
        inicio->prox = novo;
        return 1;
    }

    No *ultimo = inicio->prox;

    while (ultimo->prox != NULL)
        ultimo = ultimo->prox;

    ultimo->prox = novo;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

RetorPrincipal (Principal*)
    NULL, caso não tenha nenhum número nas listas
    Principal*, ponteiro para o início da lista com cabeçote
*/
No* montarListaEncadeadaComCabecote(){

    No *inicio = (No*)malloc(sizeof(No)); // Alocando memória para inicio

    if (inicio == NULL) // Não consegui alocar
        return NULL;

    inicio->prox = NULL; // início só vai servir para apontar para o próximo
   
    if (todasEstruturasAuxiliaresVazias()) // Se todas as estruturas auxiliares estiverem vazias, retorne NULL
        return NULL;
   
    int i, j;
    int qtd;

    for (i = 0; i < TAM; i++)
        if (vetorPrincipal[i].auxiliar != NULL){ // Se a estrutura auxiliar não estiver vazia, execute
            qtd = vetorPrincipal[i].qtd; // qtd vai estar sempre mudando o seu valor, pois ele depende de cada posicao da estrutura auxliar
            for (j = 0; j < qtd; j++)
                inserirNaLista(inicio, vetorPrincipal[i].auxiliar[j]);
        }
            
    return inicio;
}





/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
RetorPrincipal void
*/
void getDadosListaEncadeadaComCabecote(No* inicio, int vetorAux[]){

    No *atual = inicio->prox;
    int i = 0;

    while (atual != NULL){
        vetorAux[i] = atual->conteudo; // Atribuindo o conteudo de atual para o vetorAux   
        atual = atual->prox; // Atual passa a ser o próximo
        i++; // I passa a ocupar a próximo posicao
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
*/
void destruirListaEncadeadaComCabecote(No** inicio){
   
    if (inicio == NULL) // Lista não existe
        return;

    No *atual = (*inicio)->prox;

    while (*inicio != NULL){

        atual = (*inicio)->prox;

        free(*inicio);

        *inicio = atual;
    }

    *inicio = NULL;
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/
void finalizar(){
    int i;

    // Salva a estrutura no arquivo.
    salvaEstrutura();
    for(i = 0; i < TAM; i++)
        free(vetorPrincipal[i].auxiliar);
}

/*
        Salvar - Raciocínio

Percorro a estrutura principal
os que forem diferentes de Null eu armazeno o indice da estrutura princiapl
depois armazeno o tamanho da estrutura auxiliar desse indice
depois armazeno a quantidade de elementos preenchidos dessa estrutura auxiliar
depois percorro a estrutura auxiliar e pego todos os seus elementos.
abro o arquivo, 
imprimo:
indicePrincipal;tamanhoAuxiliar;qtdAuxiliar;elementoAux1;elementoAux2;elementoAux3;

*/
int salvaEstrutura() {
    int i;
    int n = 10;
    int indicePrincipal, tamanho, qtd;

    int retorno = SUCESSO;

    // Apaga o já existente e cria um novo arquivo;
    FILE *output = fopen("estrutura.txt", "w");
    fclose(output);

    // Vai percorrer a estrutura principal
    for(i = 0; i < n; i++) {
        // Quando achar uma estrutura que existe, ele vai armazenar os seus dados
        if(vetorPrincipal[i].auxiliar != NULL) {
            indicePrincipal = i+1; // +1    por quê o índice inicia no 0
            tamanho = vetorPrincipal[i].tamanho;
            qtd = vetorPrincipal[i].qtd;

            int elementosAux[qtd];
            // Pega os dados Presentes na estrutura auxiliar e armazena no vetor.
            retorno = getDadosEstruturaAuxiliar(indicePrincipal, elementosAux);

            if(retorno != SUCESSO) {
                return retorno;
            }
            // Grava no arquivo
            retorno = gravaNoArquivo(indicePrincipal, tamanho, qtd, elementosAux);

            if(retorno != SUCESSO) {
                return retorno;
            }
        }
    }

    return retorno;
}

int gravaNoArquivo(int indice, int tamanho, int qtd, int elementos[]) {
    
    // Vai escrever no final do arquivo estrutura.txt
    FILE *output = fopen("estrutura.txt", "a");
    int i;

    if(output == NULL) {
        return ERRO_ABRIR_ARQUIVO;
    }

    // Imprime no Arquivo as Propriedades
    fprintf(output, "%d;", indice);
    fprintf(output, "%d;", tamanho);
    fprintf(output, "%d;", qtd);
        
    // Imprime no Arquivo os Elementos da Estrutura Auxiliar    
    for(i = 0; i < qtd; i++){
        fprintf(output, "%d;", elementos[i]);
    }

    // Imprime o \n no final da linha
    fprintf(output,"\n");
    fclose(output);

    return SUCESSO;

}
