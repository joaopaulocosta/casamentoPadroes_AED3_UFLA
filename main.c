/** \mainpage Inicio
 * 
 * CASAMENTO DE PADRÕES
 * 
 * \par TRABALHO III DE ALGORITIMOS E ESTRUTURA DE DADOS III
 * BACHARELADO EM CIÊNCIA DA COMPUTAÇÃO - UNIVERSIDADE FEDERAL DE LAVRAS [UFLA]
 * 
 * \par Resumo
 * O projeto tem como objetivo realizar uma busca por padrões em um arquivo texto
 * que contém algum código de dna.
 * 
 * \par Professor
 * Prof. André Pimenta
 * 
 * \author João Paulo Costa.
 * \author Jonhy Geraldo.
 
 * \date 11 de Fevereiro de 2014, 18:20
 * 
 * Versão 1.5
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "busca.h"


int main(int argc, char** argv) {
    char comando[9];
	scanf("%s",comando); /* lendo o primeiro comando */
	if(strcmp(comando,"busca_dna") == 0){
		char padraoAux[100];
		scanf("%s",padraoAux); /* lendo o padrão a ser buscado */
		int tamPadrao;
		char * padrao = ajustarPadrao(padraoAux,&tamPadrao); 
		char file[100];
		scanf("%s",file); /*lendo o nome do arquivo */
		long tamFita = 0,tamCabec = 0;
		char *fita = criarFita( file, &tamCabec,&tamFita);
		char metodo[3];
		scanf("%s",metodo); /* lendo o algoritmo a ser utilizado na busca */
		if(metodo[0] =='K' && metodo[1] == 'M' && metodo[2] == 'P')
			KMP(fita,padrao,tamPadrao,tamFita,tamCabec);
		else if(metodo[0] =='B' && metodo[1] == 'M' && metodo[2] == 'H')
			BMH(fita,padrao,tamPadrao,tamFita,tamCabec);
		free(padrao);
	}
    return (EXIT_SUCCESS);
}

