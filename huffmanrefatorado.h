#ifndef HUFFMANREFATORADO_H
#define HUFFMANREFATORADO_H

typedef struct HuffNode {
  char caractere;      // Faz o armazenamento do caractere relacionado ao nó
  int frequencia; // Armazena a devida frequencia do caractere
  struct HuffNode *esq, *dir; // Ponteiros para os filhos esquerda e direita
} HuffNode;

typedef struct caracteresHuff {
  char caractere; // Armazena o devido caractere associado ao código de Huffman
  char *codigo;   // Armazena o código do huff como uma string
} caracteresHuff;

typedef struct Frequencia {
  int frequencia; // Armazena a devida frequencia do caractere
  char caractere;      // Armazena o devido caractere
} Frequencia;

// Funções de criação e destruição de árvores
HuffNode *criar_node(char caractere, int frequencia); // Cria um novo nó
HuffNode *construir_arvore_huff(); // Constrói a árvore de Huffman

void gerar_cod(HuffNode *raiz, char *codigo, int tamanho); // Gera o código de huffman para cada caractere
void liberar_codigos_huff();
void liberar_arvore(HuffNode *raiz); // Libera a memória alocada para a árvore
int comparar_caracteres(const void *a, const void *b);

// Funções para manipulação do algoritmo de Huffman necessárias, de acordo com o
// documento de requisitos:
void add(char caractere, int frequencia);
void calc();
void print();
char *cod(char *str, float *taxa_compressao_8bits,
          float *taxa_compressao_min_bits);
char *dec(char *bits);
void clear();
void exit_program();

#endif
