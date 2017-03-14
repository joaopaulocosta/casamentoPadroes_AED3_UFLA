//Netbeans Project !!

CASAMENTO DE PADRÕES EM SEQUÊNCIA DE DNA
TRABALHO DE ALGORITIMOS E ESTRUTURA DE DADOS III
 
BACHARELADO EM CIÊNCIA DA COMPUTAÇÃO - UNIVERSIDADE FEDERAL DE LAVRAS [UFLA]


Terceiro Período 

Integrantes:
João Paulo Costa - 10A
 
Jonhy Geraldo - 10A
 
 
 
13/02/2014
 
versão 1.5

 

Sistema Operaciona Utilizado: Windows 7

Instruções de uso do software:

-Pastas :

Pasta1 (Trabalho III):
Trabalho III contém o projeto
main.c
busca.c
busca.h
makefile

Pasta 2 (Documentação Externa):
Documentação Externa contêm a documentação do código desenvolvido pelo programa Doxygen.


-Comandos:

busca_dna <padrão> <arquivo.txt> <algoritmo_de_busca>

EX de entrada: 
	busca_dna gctacgatcgact Lactobacillus_salivarius_UCC118.txt KMP

O algoritmo retornará todas as posições que o padrão foi encontrado no arquivo, retornará também a
quantidade de comparações realizadas pelo algoritmo escolhido.

-Algoritmos disponíveis:
	- KMP - Knuth Morris Pratt, que utiliza préfixos para realizar a busca. 
	- BMH - Boyer-Morre-Horspoll, que utiliza sulfixos para realizar a busca.


OBS1. Para abrir a documentação clique em index.html


