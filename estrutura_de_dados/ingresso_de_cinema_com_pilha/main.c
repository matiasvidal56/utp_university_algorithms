#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa {
    char nome[30];
    int idade;
    struct pessoa *prox;
} Pessoa;

typedef struct ingresso {
    char filme[30];
    float valor;
    struct ingresso *prox;
} Ingresso;

Pessoa *enfileira(Pessoa *tras, char *nome, int idade) {
    /*
	 Aloca um novo espaço na memória, com o tamanho de memória da estrutura (struct) Pessoa
	*/
    Pessoa *novaPessoa = (Pessoa *)malloc(sizeof(Pessoa));
   
    /*
     Define o atributo "nome" da estrutura "novaPessoa"

     Observação: strcpy copia o valor de um endereço de memória para o outro
       strcpy(variavel_de_destino, variavel_a_ser_copiada)
    */
    strcpy(novaPessoa->nome, nome);
    novaPessoa->idade = idade;
    novaPessoa->prox = NULL;
    
    /*
     O valor de trás é sempre o último adicionado a fila! Inicialmente, a isabela é última pesssoa da fila, então associa-se à isabela a próxima pessoa a ser adicionada (novaPessoa). 
    */
    if (tras) {
        tras->prox = novaPessoa;
    }
    
    /*
     Retorna o valor adiciona à fila. 
    */
    return novaPessoa;
}

Pessoa *desenfileira(Pessoa *frente) {
    if (!frente) return NULL;
    
    /*
     Desenfileira o primeiro dado da fila (frente). 

     O próximo valor da fila, que estava no indice (posição) 1 da fila deve ir para o indice (posição) 0. Por isso, o retorno dessa função é a próxima pessoa da fila! Observe que a próxima pessoa da fila, no código main, é colocada na variável "frente."
    */
    Pessoa *proxima = frente->prox;

    /**
     Limpa o endereço de memória da variável "frente"
    */
    free(frente);
    return proxima;
}

/*
Essa função é parecida com a função "enfileira", mas há uma diferença: o valor de "prox" (próximo) é definido com valor o do topo da pilha.
*/
Ingresso *empilha(Ingresso *topo, char *nome, float valor) {
 
    Ingresso *novoIngresso = (Ingresso *)malloc(sizeof(Ingresso));
  
    strcpy(novoIngresso->filme, nome);
    novoIngresso->valor = valor;
    novoIngresso->prox = topo;
    
    return novoIngresso;
}

/*
Essa função é parecida com a função desenfileira (fila), mas o valor removido é o do topo da pilha.
*/
Ingresso *desempilha(Ingresso *topo) {
    if (!topo) return NULL;
    
    Ingresso *proximo = topo->prox;
    free(topo);
    return proximo;
}

/*
Imprime a fila em ordem crescente (o primeiro valor da fila é o primeiro adicionado)
*/
void imprimeFila(Pessoa *frente) {
    Pessoa *atual = frente;
    while (atual) {
        printf("Nome: %s, Idade: %d\n", atual->nome, atual->idade);
        atual = atual->prox;
    }
}

/*
imprime a pilha em ordem descrescente (o primeiro valor da pilha é o último adicionado)
*/
void imprimePilha(Ingresso *topo) {
    Ingresso *atual = topo;
    while (atual) {
        printf("Filme: %s, Valor: %.2f\n", atual->filme, atual->valor);
        atual = atual->prox;
    }
}

void main() {
    Pessoa *frente = NULL, *tras = NULL;
    Ingresso *topo = NULL;
    
    /*
	1° TAREFA: Enfileirar as pessoas na fila. 
	*/

    /*
	Coloca a isabela na última posição que nesse caso é a primeira. 
	*/
    tras = enfileira(tras, "Isabela", 30);

    /*
     Define o valor inicial da fila (variável frente) com valor da variável trás. Lembre-se: o valor inicial e final da fila SÓ É IGUAL QUANDO há uma pessoa na fila.
    */
    if (!frente) frente = tras;  

    /*
     Coloca o bob na última posição da fila, alterando a fila para: 
        ISABELA
        BOB
    */
    tras = enfileira(tras, "Bob", 25);
    
    /*
      Coloca o Charlie na última posição da fila, alterando a fila para: 
        ISABELA
        BOB
        CHARLIE
    */
    tras = enfileira(tras, "Charlie", 20); 

    printf("Fila de Pessoas:\n"); 

    /*
     A função "imprimeFila" irá mostrar o estado atual da fila: 
        ISABELA
        BOB
        CHARLIE
    */
    imprimeFila(frente);    

    /*
      Lembre-se: O primeiro a entrar na fila, é o primeiro a sair! (FIRST IN, FIRST OUT - FIFO) 

      A função irá remover a primeira pessoa adicionada a fila (Isabela). Veja a última alteração da váriavel "frente". 

      Observe que é definido um novo valor à variável "frente", que é o retorno da função "desenfileira", o qual representa a próxima pessoa da fila (BOB)

      A fila agora está assim: 
            BOB
            CHARLIE
    */
    frente = desenfileira(frente); 
    printf("\nFila de Pessoas após desenfileirar:\n");

    /*
      A função "imprimeFila" irá mostrar o estado atual da fila: 
        BOB
        CHARLIE
    */
    imprimeFila(frente); 

    /*
     2° TAREFA: Empilhar os ingressos na pilha.
    */

    /*
     Coloca o filme "Inception" no topo da pilha. 

     O valor da variável "topo" é definido com o último ingresso adicionado a pilha.
    */
    topo = empilha(topo, "Inception", 12.50);

    /*
     Coloca o filme "Matrix" no topo da pilha. 

     "topo" é definido como "Matrix" agora! (pois foi o último filme adicionado)

     O estado da pilha agora é: 
        Matrix
        Inception
    */
    topo = empilha(topo, "Matrix", 10.00);
    

    /*
     Coloca o filme "Avatar" no topo da pilha
     
     O estado da pilha agora é: 
        Avatar
        Matrix
        Inception 
    */
    topo = empilha(topo, "Avatar", 15.00);

    printf("\nPilha de Ingressos:\n");

    /*
     Mostra o estado atual da pilha: 
        Avatar
        Matrix
        Inception
    */
    imprimePilha(topo);

    /*
     Lembre-se: O último valor adicionado a filha é o primeiro a ser removido! (LAST IN, FIRST OUT)
     
     A função "desempilha" irá remover o último ingresso adicionado a pilha (Avatar).
    */
    topo = desempilha(topo);
    printf("\nPilha de Ingressos após desempilhar:\n");

    /*
     Imprime o estado atual da pilha: 
        Matrix
        Inception
    */
    imprimePilha(topo);

    /*
      Para a execução (testing pr) 
    */
    system("pause");
}
