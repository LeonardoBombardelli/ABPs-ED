#include "header.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    ABP *arvore = InicializaArvore();
    int opt =1,dado=0,inf=0;

    while(opt)
    {
        printf("\n--------------\n");
        puts("1 - Inserir AVL");
        puts("3 - Contar");
        puts("6 - Fator Balanceamento");
        puts("0 - Sair");
        printf("--------------");
        printf("\n");
        scanf("%d",&opt);
        switch(opt)
        {
        case 1:
            puts("Digite o Numero a ser inserido");
            scanf("%d",&dado);
            arvore=InsereArvore(arvore,dado);break;
        case 3:
            printf("\n Quantia: %d",conta_nodos(arvore));break;
        case 0:
            opt=0;break;
        }
    }
}

