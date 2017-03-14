/* 
 * File:   busca.h
 * 
 * Author: João Paulo Costa
 * Author: Jonhy Geraldo.
 * 
 * Created on 11 de Fevereiro de 2014, 16:35
 */

#ifndef BUSCA_H
#define	BUSCA_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* BUSCA_H */

/*Funções*/


char * criarFita(char file[100],long *contCaracteres, long *contCaracteresFita);
char * ajustarPadrao(char padraoAux[100],int *tamPadrao);
int * criarPi( char *padrao, int tamPadrao);
void KMP(char * fita,char *padrao,int tamPadrao,long tamFita,long tamCabec);
void BMH(char * fita,char *padrao,int tamPadrao,long tamFita,long tamCabec);