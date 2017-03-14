/* Author: João Paulo Costa
 * Author: Jonhy Geraldo. */

#include <stdio.h>
#include <stdlib.h>
#include "busca.h"

/**********************************************************************************************/

/**Função responsável pela leitura do arquivo texto. É criado um vetor dinâmico do tipo char
 * para armazenar todos os caracteres relevantes, descartando o cabeçálho e caracteres desnecessários
 * como o caracter espaço
 * @param  file  nome do arquivo que contenha o dna a ser processado.
 * @param  contCaracteres  ponteiro que retornará a quantidade de caracteres lidos no cabeçalho.
 * @param  contCaracteresFita  ponteiro que retornará a quantidade de caracteres relevantes lidos,
 * ou seja o tamanho do vetor de char, que será alocado dinâmicamente.
 * @return  retorna o endereço do vetor de caracteres referentes ao dna que será processados.*/
char * criarFita(char file[100],long *contCaracteres, long *contCaracteresFita){
	FILE *arquivo = fopen(file,"r");
	long i = 0; /* iterador */
	char *fita;
	if (arquivo != NULL){
		while(!feof(arquivo)){
			char linha[100];
			fgets(linha,100,arquivo);
			if(linha[0] > 50){		/*linhas do cabeçalho começam com um letra maiuscula, está condição so aceita linhas do cabeçalho */
				while(linha[i] != '\0') {
					*contCaracteres += 1;;
					i++;
				}
			}
			else{	/*está condição não aceita linhas que começem com letras */
				while(linha[i] != '\0'){
					if(linha[i] >= 97 && linha[i] <= 122){
						*contCaracteresFita += 1;	/*contando os caracteres relevantes para a busca */
					}
					i++;
				}
			}
			i = 0;
		}
		int j = 0, i=0;
		fita = (char *) malloc(*contCaracteresFita * sizeof(char)); /* alocação dinâmica para a fita de caracteres relevantes */
		fclose(arquivo);
		arquivo = fopen(file,"r+b");
		fseek(arquivo,*contCaracteres,0);
		while(!feof(arquivo)){
			char linha[100];
			fgets(linha,100,arquivo);
			while(linha[i] != '\0'){
				if(linha[i] >= 97 && linha[i] <= 122){
					fita[j] = linha[i]; /* salvando os caracteres na fita */
					j++;
				}
				i++;
			}
			i=0;
		}
	}
	fclose(arquivo);
	return fita;
}

/**********************************************************************************************/

/** Função que copia o padrão que será utilizado na busca, para um vetor dinâmico, primeiramente o 
 * padrão é inserido em um vetor de caracteres do tamanho 100, esta função aloca um novo vetor 
 * que receberá o padrão.
 * @param  padraoAux vetor de tamanho 100 que recebe o padrao.
 * @param tamPadrao  ponteiro que armazenará o tamanho do vetor que será alocado.
 * @return  endereço do vetor de char que foi alocado dinâmicamente, e que contêm o padrão*/
char * ajustarPadrao(char padraoAux[100],int *tamPadrao){
	int j = 0;
	*tamPadrao = 0;
	/*ajustando o tamanho do padrão */
	while(padraoAux[*tamPadrao] != '\0') 
		*tamPadrao += 1;
	char * padrao =(char *) malloc(*tamPadrao*sizeof(char));
	for(; j< *tamPadrao; j++)
		padrao[j] = padraoAux[j];
	return padrao;
}

/**********************************************************************************************/

/** Função que cria o vetor dinâmico pi que será utilizado para a busca do algoritmo KMP. O vetor pi
 * é criado processando o vetor referente ao padrao buscado. É procurado dentro do padrão, prefixos, que
 * podem ser utilizados para dar saltos maiores na hora da busca.
 * @param padrao  ponteiro que receberá o vetor referente ao padrão que será buscado.
 * @param tamPadrao  variável que receberá o tamanho do vetor padrao.
 * @return  endereço referente ao vetor de inteiros pi, utilizado no algoritmo KMP. */
int * criarPi( char *padrao, int tamPadrao){
	int *pi = (int *) malloc(tamPadrao*sizeof(int));
	int l = 0,cont = 0,j;
	pi[0] = 0;
	for(j = 1; j < tamPadrao ; j++){
		if(padrao[j] == padrao[l]){
			cont++;
			l++;
			pi[j] = cont;
		}
		else{ 
			cont = 0;
			l = 0;
			if(padrao[j] == padrao[l]){
				cont++;
				l++;
				pi[j] = cont;
			}
			else
				pi[j] = cont;
		}
	}
	return pi;
}

/**********************************************************************************************/

/** Função que realiza o algoritmo de casamento de padrões KMP, desenvolvidos por
 * Knuth, Morris e Pratt. Basicamente o algortimo em questão, observa características
 * do padrão, características que podem ser usadas para dar saltos maiores que 1, no texto
 * de busca. Quando é detectado o casamento de padrão, é impresso na saída a posição no texto
 * referente ao casamento. ao final é impresso o número de comparações necessárias para a busca.
 * @param fita  ponteiro que receberá o vetor de caracteres referente ao dna, onde será
 * buscado o padrão.
 * @param  padrao ponteiro que receberá o vetor de caracteres referente ao padrão.
 * @param tamPadrao  variável responsável por armazenar o tamanho do vetor padrão.
 * @param tamFita  variável responsável por armazenar o tamanho do vetor fita.
 * @param tamCabec  variável que receberá o tamanho do cabeçalho do arquivo onde está
 * armazenado o dna.*/
void KMP(char * fita,char *padrao,int tamPadrao,long tamFita,long tamCabec){
	long i,comparacoes = 0;
	int l, q=0, *pi = criarPi(padrao,tamPadrao);
	for(i = 0; i< tamFita; i++){
		while(q > 0 && padrao[q] != fita[i]){
			q = pi[q-1];
			comparacoes++;
		}
		if(padrao[q] == fita[i]){
			q++;
		}
		if(q == tamPadrao-1 && padrao[q] == fita[i+1]){
			/* calculando a posição do padrão encontrado, no arquivo txt*/
                        long div = (i-(tamPadrao-2))/60;
			long total = div * 81;
			long res = (i-(tamPadrao-2))%60;
			total += 5+ res + res/10; 
			printf("%ld\n", tamCabec+ total);
			q = pi[q];
		}
	}
	free(pi);
	printf("Comparações: %ld\n",comparacoes);
}

/**********************************************************************************************/

/** Função que realiza o algoritmo de casamento de padrões BMH, desenvolvidos por Boyer, Moore
 * e Horspool. Primeiramente o padrão é processado a procura de sulfixos, depois é realizado uma busca
 * sequencial no padrão através de comparações realizadas da direita para a esquerda, caso haja uma 
 * desigualdade o algortimo calcula um salto a ser realizado no texto.  
 * @param - char * fita - ponteiro que receberá o vetor de caracteres referente ao dna, onde será
 * buscado o padrão.
 * @param padrao  ponteiro que receberá o vetor de caracteres referente ao padrão.
 * @param tamPadrao  variável responsável por armazenar o tamanho do vetor padrão.
 * @param tamFita  variável responsável por armazenar o tamanho do vetor fita.
 * @param tamCabec  variável que receberá o tamanho do cabeçalho do arquivo onde está
 * armazenado o dna.*/
void BMH(char * fita,char *padrao,int tamPadrao,long tamFita,long tamCabec){
	long i,j,k,comparacoes = 0;
	int tabela[150];
	/*criando tabela de saltos */
	for(i = 0; i< 150; i++)
		tabela[i] = tamPadrao;
	for(j=1; j< tamPadrao; j++)
		tabela[padrao[j-1]] = tamPadrao-j;
	i = tamPadrao;
	
	/*percorrendo a fita */
	while(i < tamFita){
		k = i;
		j = tamPadrao;
		while(fita[k-1] == padrao[j-1] && j>0){
			k--;
			j--;
			comparacoes++;
		}
		if(j==0){
                        /* calculando a posição do padrão encontrado, no arquivo txt*/
			long div = (i-(tamPadrao))/60;
			long total = div * 81;
			long res = (i-(tamPadrao))%60;
			total += 5+ res + res/10; 
			printf("%ld\n", tamCabec+ total);
		}
		i += tabela[fita[i-1]];
	}
	printf("Comparações: %ld\n",comparacoes);
}
