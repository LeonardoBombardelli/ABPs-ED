#include "header.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* Entrada;
    FILE* Saida;
    char Passagem[5];
    int Numeros[100];
    int i = 0;

    if(argc != 3)
    {
        printf("Esperava 3 argumentos, recebeu %d argumentos", argc);
        return 1;
    }
    else
    {
        Entrada = fopen(argv[1], "r");
        if (Entrada != NULL)
        {
            printf("Erro ao abrir arquivo 1");
            return 1;
        }

        Saida = fopen(argv[2], "w");

        while(!feof(Entrada))
        {
            fgets(Passagem, 5, Entrada);
            Numeros[i] = atoi(Passagem);
            i++;
            printf("%d\n", Numeros[i]);
        }
    }
}

