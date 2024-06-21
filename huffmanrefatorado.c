    // Importações necessárias para a implementação do algoritmo de Huffman

#include "huffmanrefatorado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARACTERES_MAXIMO 256

Frequencia frequencias[CARACTERES_MAXIMO]; // Responsável por guardar a frequencia de caracteres
int qntd_frequencia = 0; // Contador para a quantidade de caracteres

caracteresHuff codigos_huffman[CARACTERES_MAXIMO]; // Resposável por guardar os códigos de huffman para cada caractere
int qntd_codigo = 0; // Contador de códigos huffman

// Requisito 1.
void add(char caractere, int frequencia){ // Informa a frequência do caractere E. Se E já havia sido informado, substitui o valor anterior
    for (int contador = 0; contador < qntd_frequencia; contador++){ // Verifica todos os caracteres já informados para procurar por aquele informado
      if (frequencias[contador].caractere == caractere) { // Se for igual ao caractere já informado, substitui a frequencia anterior pela nova
        frequencias[contador].frequencia = frequencia;
        return; 
      }
  } // Se chegou até aqui é porque não foi encontrado um igual, então adiciona o caractere e a frequencia
  frequencias[qntd_frequencia].caractere = caractere;
  frequencias[qntd_frequencia].frequencia = frequencia;
  qntd_frequencia++;
}

// Requisito 2.
void calc(){
  HuffNode *raiz = construir_arvore_huff(); 
  char codigo[CARACTERES_MAXIMO]; // Vetor para armazenar o código de huffman
  gerar_cod(raiz, codigo, 0); // Gera o código de huffman para cada caractere
  liberar_arvore(raiz);
}

// Requisito 3.
void print() {
    qsort(codigos_huffman, qntd_codigo, sizeof(caracteresHuff), comparar_caracteres);
    for (int contador = 0; contador < qntd_codigo; contador++) {
        printf("[%c] | Frequencia: [%d] | Codificado: [%s]\n",
               codigos_huffman[contador].caractere, frequencias[contador].frequencia,
               codigos_huffman[contador].codigo);
    }
}


// Requisito 4.
char *cod(char *str, float *taxa_compressao_8bits, float *taxa_compressao_min_bits) {
  int contador_bits = 0;
  char *string_codificada = (char *)malloc(CARACTERES_MAXIMO * 8);
  string_codificada[0] = '\0';

  for (int i = 0; str[i] != '\0'; i++) {
    for (int j = 0; j < qntd_codigo; j++) {
      if (str[i] == codigos_huffman[j].caractere) {
        strcat(string_codificada, codigos_huffman[j].codigo);
        contador_bits += strlen(codigos_huffman[j].codigo);
        break;
      }
    }
  }

  int contador_bits_original = strlen(str) * 8;
  int contador_bits_min = 0;
  for (int i = 0; i < qntd_frequencia; i++) {
    contador_bits_min += frequencias[i].frequencia * strlen(codigos_huffman[i].codigo);
  }

  *taxa_compressao_8bits = (float)contador_bits / contador_bits_original * 100;
  *taxa_compressao_min_bits = (float)contador_bits / contador_bits_min * 100;

  return string_codificada;
}


// Requisito 5.
char *dec(char *bits) {
  HuffNode *raiz = construir_arvore_huff();
  HuffNode *atual = raiz;
  char *string_decodificada = (char *)malloc(CARACTERES_MAXIMO);
  int indice = 0;

  for (int i = 0; bits[i] != '\0'; i++) {
    if (bits[i] == '0') {
      atual = atual->esq;
    } else {
      atual = atual->dir;
    }

    if (atual->esq == NULL && atual->dir == NULL) {
      string_decodificada[indice++] = atual->caractere;
      atual = raiz;
    }
  }
  string_decodificada[indice] = '\0';

  liberar_arvore(raiz);
  return string_decodificada;
}


// Requisito 6.
void clear(){
  qntd_frequencia = 0; 
  qntd_codigo = 0; 
}

// Requisito 7.
void exit_program() { 
  liberar_codigos_huff(); 
  clear(); 
  exit(0); 
}

// Funções auxiliares para execução correta do código:

HuffNode *criar_node(char caractere, int frequencia) { 
    HuffNode *node = (HuffNode *)malloc(sizeof(HuffNode)); // Aloca memória para o novo nó
    node->caractere = caractere; // Define o caractere do nó
    node->frequencia = frequencia; // Define a frequência do nó
    node->esq = NULL; // Define o filho esquerdo como nulo
    node->dir = NULL; // Define o filho direito como nulo
    return node; 
}

int comparar_nodes(const void *a, const void *b) {
  const HuffNode *nodeA = *(const HuffNode **)a;
  const HuffNode *nodeB = *(const HuffNode **)b;
  // Primeiro comparar pela frequência
  if (nodeA->frequencia != nodeB->frequencia) {
    return nodeA->frequencia - nodeB->frequencia;
  }
  // Se as frequências forem iguais, usar a ordem alfabética
  return nodeA->caractere - nodeB->caractere;
}

HuffNode *construir_arvore_huff(){ 
    int n = qntd_frequencia;

    // cria uma lista de nós para cada caractere com sua frequência
    HuffNode **nodes = (HuffNode **)malloc(n * sizeof(HuffNode *)); 
    for (int i = 0; i < n; i++){
        nodes[i] = criar_node(frequencias[i].caractere, frequencias[i].frequencia);
    }

    // ordena os nós pela frequência
    qsort(nodes, n, sizeof(HuffNode *), comparar_nodes);

    // junta os nós para formar a árvore de Huffman
    while (n > 1){
        // pega os nós com as menores frequências
        HuffNode *esq = nodes[0]; 
        HuffNode *dir = nodes[1];

        // cria um novo nó pai com a soma das frequências dos dois nós
        HuffNode *pai = criar_node('\0', esq->frequencia + dir->frequencia);
        pai->esq = esq;
        pai->dir = dir;

        // remove os dois nós da lista e adiciona um novo nó
        memmove(&nodes[0], &nodes[2], (n - 2) * sizeof(HuffNode *));
        nodes[n - 2] = pai;
        n--;

        // reordena a lista de nós
        qsort(nodes, n, sizeof(HuffNode *), comparar_nodes);
    }

    HuffNode *raiz = nodes[0];
    free(nodes);
    return raiz;
} 

char *duplicar_string(const char *s) {
    char *d = malloc(strlen(s) + 1); // +1 para o terminador nulo
    if (d == NULL) return NULL;      // tratamento de erro
    strcpy(d, s);                    // copia a string
    return d;
}

void gerar_cod(HuffNode *raiz, char *codigo, int tamanho) {
    // Verifica se o nó atual é uma folha
    if (raiz->esq == NULL && raiz->dir == NULL) {
        // Nó folha encontrado, atribui o código ao caractere correspondente
        codigo[tamanho] = '\0'; // Termina o código com '\0' para formar uma string válida
        codigos_huffman[qntd_codigo].caractere = raiz->caractere;
        codigos_huffman[qntd_codigo].codigo = duplicar_string(codigo);
        qntd_codigo++;
        return;
    }

    // Se não for uma folha, continua recursivamente para os filhos
    // Filho esquerdo: adiciona '0' ao código e chama recursivamente
    codigo[tamanho] = '0';
    gerar_cod(raiz->esq, codigo, tamanho + 1);

    // Filho direito: adiciona '1' ao código e chama recursivamente
    codigo[tamanho] = '1';
    gerar_cod(raiz->dir, codigo, tamanho + 1);
}

int comparar_caracteres(const void *a, const void *b) {
    caracteresHuff *ca = (caracteresHuff *)a;
    caracteresHuff *cb = (caracteresHuff *)b;
    return ca->caractere - cb->caractere;
}

void liberar_codigos_huff() { 
    for (int contador = 0; contador < qntd_codigo; contador++) {
        free(codigos_huffman[contador].codigo); 
    }
}

void liberar_arvore(HuffNode *raiz) {
    if (raiz == NULL) { 
      return;
    }
    liberar_arvore(raiz->esq); // Percorre para a subárvore esquerda (Recursão) se existir
    liberar_arvore(raiz->dir); // Percorre para a subárvore direita (Recursão) se existir
    free(raiz); // Libera a memória alocada para o nó atual
}

