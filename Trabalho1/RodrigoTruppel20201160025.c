// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: 
//  email: 
//  Matrícula: 
//  Semestre: 

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "RodrigoTruppel20201160025.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i; 

  for (i = 0; data[i] != '/'; i++){
    sDia[i] = data[i];	
  }
  if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
    sDia[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }  


  int j = i + 1; //anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++){
    sMes[i] = data[j];
    i++;
  }

  if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
    sMes[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }


  j = j + 1; //anda 1 cada para pular a barra
  i = 0;

  for(; data[j] != '\0'; j++){
    sAno[i] = data[j];
    i++;
  }

  if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
    sAno[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

  dq.valido = 1;

  return dq;
}
/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int datavalida = 0;
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Quebrar a string data em strings sDia, sMes, sAno
    DataQuebrada date = quebraData(data);

    if (date.iAno < 100 && date.iAno > 0)
    {
        date.iAno += 2000;
    }

    if (date.iAno >= 1900 && date.iAno <= 2024)
    {
        if (date.iMes >= 1 && date.iMes <= 12)
        {
            if ((date.iAno % 4 == 0 && date.iAno % 100 != 0) || (date.iAno % 400 == 0))
            {
                meses[1] = 29; // Ano bissexto
            }

            if (date.iDia >= 0 && date.iDia <= meses[date.iMes - 1])
            {
                return 1; // Data válida
            }
        }
    }

    return 0; // Data inválida
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
  dma.qtdAnos = 0;
  dma.qtdMeses = 0;
  dma.qtdDias = 0;
 int i; int resultado;
   DataQuebrada inicial, finall;
 int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int cont = 0;
    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final não é menor que a data inicial
      inicial = quebraData(datainicial);
      finall = quebraData(datafinal);


      if (inicial.iAno < 100 && inicial.iAno > 0)
    {
        inicial.iAno += 2000;
    }
      if (finall.iAno < 100 && finall.iAno > 0)
    {
        finall.iAno += 2000;
    }

      if ((inicial.iAno % 4 == 0 && inicial.iAno % 100 != 0) || (inicial.iAno % 400 == 0))
            {
                meses[1] = 29; // Ano bissexto
            }

      int inicialSoma = inicial.iAno * 365;
      int finalSoma = finall.iAno * 365;
      for(i=inicial.iMes-2;i>=0;i--){
        inicialSoma = inicialSoma + meses[i];
      }
       if ((finall.iAno % 4 == 0 && finall.iAno % 100 != 0) || (finall.iAno % 400 == 0))
            {
                meses[1] = 29;
              cont = 1;// Ano bissexto
            }
      for(i=finall.iMes-2;i>=0;i--){
        finalSoma = finalSoma + meses[i];
      }
      finalSoma = finalSoma + finall.iDia;
      inicialSoma = inicialSoma + inicial.iDia;
        if(inicialSoma>finalSoma){
        dma.retorno = 4;
        return dma;
        }
        //calcule a distancia entre as datas
      int resultado = 0 ;
      resultado = finalSoma - inicialSoma;

      while(resultado>=365){
        dma.qtdAnos++;
        if(meses[1] == 29 && cont != 1){
          resultado = resultado -366;
          meses[1] = 28;
        }
        else
           resultado = resultado - 365;
      }
      while(resultado>=meses[inicial.iMes-1]){
        dma.qtdMeses++;
        resultado = resultado - meses[inicial.iMes-1];
        if(meses[1] )
        inicial.iMes++;
      }
      dma.qtdDias = resultado;

      //se tudo der certo
      dma.retorno = 1;
      return dma;

    }

}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0; int i;
     if(isCaseSensitive == 1){

         for(i=0;texto[i] != '\0';i++){
         if(c == texto[i])
            qtdOcorrencias++;
         }

     }
     else{
       if( c>=97 && c<=122){
          for(i=0;texto[i] != '\0';i++){
         if(c == texto[i] || (c-32) == texto[i])
            qtdOcorrencias++;
         }
       }
         else{
          for(i=0;texto[i] != '\0';i++){
         if(c == texto[i] || (c+32) == texto[i])
            qtdOcorrencias++;
         }  
       }

     }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
 int qtdOcorrencias = 0;
    int i=0;
    int j=0;
    int acento=0,correcao_posicao=0;;
    int n =0;
    int iposicoes=0;

  while(strBusca[n]!='\0')
    {
      n+=1;
    }

    while(strTexto[i]!='\0')
    {
      j=0;
      if(strTexto[i]<0)
      {
        acento++;
      }
      for(j=0; strBusca[j] == strTexto[i+j];j++){
        if(strTexto[i+j]<0)
          acento++;
      }

      correcao_posicao =acento/2;

      if(j==n)
      {
        posicoes[iposicoes]=i+1-correcao_posicao;
        posicoes[iposicoes+1]=i+j-correcao_posicao;
        iposicoes+=2;
        qtdOcorrencias++;
        i=i+j-1;
      }

      i++;
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
 int numTeste = num;
 int i; int divisor =1 ;int divisao = 1; int contador_algarismos = 0; int *n; int inverter;
 while(divisao != 0){
  divisao = numTeste/10;
  numTeste = divisao;
  contador_algarismos++;
 }
  n = malloc(contador_algarismos * sizeof(int));
  for(i=1;i<contador_algarismos;i++){
    divisor = divisor * 10;  
  }
  inverter = divisor;
  for(i=0;i<contador_algarismos;i++){
    n[i] = num/divisor;
    num = num%divisor;
   divisor = divisor/10;  
  }
  num = 0;
  for(i=(contador_algarismos- 1);i>=0;i--){
    num = num + n[i]*inverter;
    inverter = inverter/10; 
  }
  free(n);
    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
   int *nBusca; int *nBase; int numTesteBusca; int numTesteBase; int divisorBusca = 1; int divisorBase = 1; int qtdOcorrencias = 0; int contAlgarismosBusca = 0; int contAlgarismosBase = 0; int divisaoBusca = 1; int divisaoBase = 1; int i;
numTesteBusca = numerobusca; int cont =0; int j;
numTesteBase = numerobase;
 while(divisaoBusca != 0){
  divisaoBusca = numTesteBusca/10;
  numTesteBusca = divisaoBusca;
  contAlgarismosBusca++;
 }
   nBusca = malloc(contAlgarismosBusca * sizeof(int));
  for(i=1;i<contAlgarismosBusca;i++){
    divisorBusca = divisorBusca * 10;  
  }
  for(i=0;i<contAlgarismosBusca;i++){
    nBusca[i] = numerobusca/divisorBusca;
    numerobusca = numerobusca%divisorBusca;
   divisorBusca = divisorBusca/10;  
  }

  while(divisaoBase != 0){
  divisaoBase = numTesteBase/10;
  numTesteBase = divisaoBase;
  contAlgarismosBase++;
 }
   nBase = malloc(contAlgarismosBase * sizeof(int));
  for(i=1;i<contAlgarismosBase;i++){
    divisorBase = divisorBase * 10;  
  }
  for(i=0;i<contAlgarismosBase;i++){
    nBase[i] = numerobase/divisorBase;
    numerobase = numerobase%divisorBase;
   divisorBase = divisorBase/10;  
  }

  int achou = 0;
  for(i=0;i<contAlgarismosBase;i++){
      if(nBusca[0] == nBase[i]){
          achou = 1;
        for(j=0;j<contAlgarismosBusca;j++){
            if(nBusca[j] == nBase[j+i]){
                cont++;
            }
        }  
      }
     if(cont == contAlgarismosBusca){
       qtdOcorrencias++;
     }
     if(achou ==1){
        i=i + j -1; 
        achou =0;
     }  

      cont = 0;
  }

  free(nBase);
  free(nBusca);  
  return qtdOcorrencias;
}
