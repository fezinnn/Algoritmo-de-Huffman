#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffmanrefatorado.h"

int main() {
    char command[50];
    char character;
    int frequency;
    char str[100];
    char bits[100];
    float compression_rate_8bits, compression_rate_min_bits;

    while (1) {
        printf("-> ");
        if (scanf("%s", command) != 1) {
            fprintf(stderr, "Erro ao ler o comando\n");
            continue;
        }

        int cmd = 0;
        if (strcmp(command, "add") == 0) {
            cmd = 1;
        } else if (strcmp(command, "calc") == 0) {
            cmd = 2;
        } else if (strcmp(command, "print") == 0) {
            cmd = 3;
        } else if (strcmp(command, "cod") == 0) {
            cmd = 4;
        } else if (strcmp(command, "dec") == 0) {
            cmd = 5;
        } else if (strcmp(command, "clear") == 0) {
            cmd = 6;
        } else if (strcmp(command, "exit") == 0) {
            cmd = 7;
        }

        switch (cmd) {
            case 1:
                if (scanf(" %c %d", &character, &frequency) != 2) {
                    fprintf(stderr, "Erro ao ler o caractere e a frequência\n");
                    continue;
                }
                add(character, frequency);
                break;
            
            case 2:
                calc();
                break;

            case 3:
                print();
                break;

            case 4:
                if (scanf("%s", str) != 1) {
                    fprintf(stderr, "Erro ao ler a string\n");
                    continue;
                }
                {
                    char* encoded_str = cod(str, &compression_rate_8bits, &compression_rate_min_bits);
                    printf("%s %.2f%% %.2f%%\n", encoded_str, compression_rate_8bits, compression_rate_min_bits);
                    free(encoded_str);
                }
                break;

            case 5:
                if (scanf("%s", bits) != 1) {
                    fprintf(stderr, "Erro ao ler os bits\n");
                    continue;
                }
                {
                    char* decoded_str = dec(bits);
                    printf("%s\n", decoded_str);
                    free(decoded_str);
                }
                break;

            case 6:
                clear();
                break;

            case 7:
                return 0;
            
            default:
                fprintf(stderr, "Comando inválido\n");
                break;
        }
    }

    return 0;
}
