# Algoritmo de Huffman

## Integrantes da equipe:
- Alan Andrade Vasconi de Souza - SC3038319
- Felipe Santos Lourenço - SC303867X
- Fernando Castro - SC3037495

## Visão Geral

O Algoritmo de Huffman é um método de compressão de dados sem perdas amplamente utilizado em várias aplicações, como compressão de arquivos e codificação de dados. Este projeto implementa o Algoritmo de Huffman em C, fornecendo uma maneira eficiente de codificar e decodificar dados.

## Descrição do Trabalho

Neste trabalho, foi implementado um programa que utiliza o Algoritmo de Huffman para a definição de uma codificação mínima. O programa permite as seguintes operações:

- *add E freq*: Informa a frequência do caractere E. Se E já havia sido informado, substitui o valor anterior.
- *calc*: Calcula os códigos Huffman dos caracteres informados até o momento.
- *print*: Imprime a tabela de códigos Huffman calculados.
- *cod str*: Apresenta a sequência de 0’s e 1’s da codificação de str. Informa também as taxas de compactação em relação à codificação com 8 bits e com o número mínimo de bits para representar todos os caracteres.
- *dec bits*: Apresenta a sequência decodificada correspondente a bits.
- *clear*: Zera a tabela de frequência.
- *exit*: Sai do programa.

## Estrutura do Projeto

- Makefile: Script para compilar o projeto de forma simplificada.
- README.md: Documento que você está lendo, descrevendo o projeto e suas instruções.
- huffmanrefatorado.c: Implementação das funções principais do Algoritmo de Huffman.
- huffmanrefatorado.h: Cabeçalho contendo as definições das funções e estruturas usadas no algoritmo.
- main.c: Programa principal que demonstra o uso das funções do Algoritmo de Huffman.

## Funcionalidades

- *Compressão de Dados*: Converte dados de entrada em um formato compactado usando o Algoritmo de Huffman.
- *Descompressão de Dados*: Restaura os dados compactados ao seu estado original.
- *Facilidade de Uso*: Interface clara e modularização do código para fácil compreensão e extensão.

## Como Compilar

Para compilar o projeto, você precisa ter o make instalado. Em seguida, execute o seguinte comando no terminal:

sh
make


Isso gerará um executável chamado huffman na raiz do projeto.

## Como Executar

Após a compilação, você pode executar o programa com o seguinte comando:

sh
./huffman


## Exemplos de Uso

### Exemplo de Utilização do Programa

1. Adicionar caracteres e suas frequências:
    sh
    ->add A 3
    ->add C 2
    ->add B 1
    ->add D 1
    

2. Calcular os códigos Huffman:
    sh
    ->calc
    

3. Imprimir a tabela de códigos Huffman:
    sh
    ->print
    
    Saída esperada:
    
    A com frequencia 3 codificado como 0
    B com frequencia 1 codificado como 100
    C com frequencia 2 codificado como 11
    D com frequencia 1 codificado como 101
    

4. Codificar uma string:
    sh
    ->cod ABACCDA
    
    Saída esperada:
    
    0100011111010 23.21% 92.86%
    

5. Decodificar uma sequência de bits:
    sh
    ->dec 0100011111010
    
    Saída esperada:
    
    ABACCDA
    

6. Sair do programa:
    sh
    ->exit
    

## Agradecimentos

Este projeto foi desenvolvido como parte de um estudo sobre algoritmos de compressão de dados. Agradecimentos especiais a todos que contribuíram com seu tempo e conhecimento.
