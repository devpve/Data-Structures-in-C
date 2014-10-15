/******************************************************************************
 *  >>>> Estrutura de Dados 
 *  >>>> Turma "A" 
 *  >>>> Trabalho 2
 *  >>>> Aluno: Paulo Victor Gonçalves Farias
 *  >>>> Matrícula: 13/0144754 
 *  >>>> UnB - Junho/2014
 *  >>>> Professor: José Carlos Loureiro Ralha
 *
 *
 *  >>>> Nome do Programa: trabalho2
 *  >>>> Objetivo: Praticar estruturas hierárquicas (Árvores binárias)
 *
 *  >>>> Conteúdo do arquivo Trabalho2.zip
 *  
 *      > Na pasta codigos:
 *
 *  	   main.c - arquivo principal que contém cópia deste texto como comentário.
 *         fila.c - arquivo fonte .c com as rotinas de fila
 *         fila.h - arquivo header com o cabeçalho das rotinas de fila e a struct fila
 *         arvore.c - varquivo fonte .c com as rotinas de árvore
 *         arvore.h - arquivo fonte .h com o cabeçalho das rotinas de árvore
 *         funcoes.c - arquivo fonte .c com algumas funções usadas
 *         funcoes.h - arquivo fonte .h com o cabeçalho das funções usadas
 *         makefile.linux - usado para facilitar na compilação do programa descrita abaixo
 *
 *       > Na pasta exemplos:
 *          
 *          Exemplo 1 e 2 - Cada pasta contém um exemplo de uso do programa Trabalho2,
 *          a partir de uma árvore temos os percorrimentos, após o uso destes no programa
 *          temos o arquivo de saída com o resultado do programa.
 *
 *  	> readme.txt - arquivo explicativo.
 *
 * >>>> Sobre o programa:
 *
 *
 *  Padrão: O programa, escrito em c, está em conformidade e usa apenas as bibliotecas
 *          disponíveis no padrão ISO C99
 *
 *  Argumentos: O programa receberá o nome de dois arquivos
 *
 *  Saída: O programa escreve no terminal corrente os percorrimentos Preordem, DFS
 *  Posordem, BFS da árvore reconstruída dos arquivos. 
 *         
 *
 *  Abordagem do problema: Primeiramente utilizaremos uma fila para armazenar todos os 
 *                         valores que estiverem no arquivo contendo o percorrimento
 *                         préordem. Utilizaremos um vetor de inteiros para armezanar
 *						   todos os valores que estiverem no arquivo contendo o percorrimento
 *						   DFS (Depth-First-Search) que fez uma busca em profundidade na
 *						   árvore original.
 *
 *						   Após ler os arquivos teremos uma fila e um vetor com os caminhamento DFS
 *						   Retiramos o primeiro elemento da fila do percorrimento Preordem, pois 
 *                         ele representa a raiz da árvore. Chamamos a função árvore com os parâmetros
 *                         (elemento, NULL), no caso NULL pois o segundo argumento representa o pai, como
 *                         a raiz é o primeiro elemento não tem pai.
 *                         
 *                         Chamamos a função árvore reconstroi e atribuimos ela a árvore binária. A função
 *                         árvore reconstroi dividirá o vetor DFS procurando pela raiz e tomará este elemento
 *                         como seu pivô, semelhante ao quickSort, faremos isso para as outras duas metades
 *                         do vetor enquanto houver elementos na fila Preordem. Construindo assim a subárvore
 * 						   esquerda e direita.
 *               
 *                         Após a reconstrução da árvore faremos os percorrimentos préordem, pósordem utilizando
 *                         o campo pai. E o DFS usando os campos NULL a direita das folhas. Costurando a árvore.
 *                    
 *                         Por último faremos o caminhamento BFS (breadth-first-search) caminhamento em largura
 *						   na árvore como pedido.
 *                         
 *                        
 *  Limitações: Consideramos que a árvore estará ordenada.
 *              Consideramos que a árvore é de inteiros.
 *				Consideramos que não há elementos repetidos na árvore.          
 *              Consideramos que a árvore é binária.
 * 
 *                 
 * >>> Comandos utilizados para compilação:
 *    
 *  gcc -Wall -c fila.c
 *	gcc -Wall -c arvore.c
 *	gcc -Wall -c BFSfila.c
 *  gcc -Wall -c funcoes.c
 *	gcc -Wall -c cliente.c
 *	gcc fila.o arvore.o BFSfila.o funcoes.o cliente.o -o trabalho2    
 *
 *
 * >>> Como executar: 
 *
 *          >>> make
 *          >>> ./trabalho2
 *
 * Foram feitos testes no sistema Linux Ubuntu(64 bits), sendo
 * que a versão entregue compilou nos sistema sem warnings.
 * 
 * versão do gcc no Linux Ubuntu: (Ubuntu 4.4.3-4ubuntu 5.1)
 *
 *
 * >>> Referência bibliográfica;
 * 
 * Função de reconstrução da árvore levemente baseada no QuickSort apresentado em 
 * http://pt.wikipedia.org/wiki/Quicksort#C
 * Imagem exemplo1 
 * http://videos.web-03.net/artigos/Higor_Medeiros/ArvoreBinaria/ArvoreBinaria1.jpg
 * Imagem exemplo2 
 * http://www.ricbit.com/uploaded_images/grafico3-767233.jpg
 *
 *
 * Acessados em 05/06/2014.
 *
 ******************************************************************************/
