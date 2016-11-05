#include "header.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main(int argc, char *argv[])
{
    AVL *arvore = InicializaAvl();
    int opt =1,dado=0,inf=0,arv=0;

    puts("1 - ABP");
    puts("2 - AVL");
    printf("Insira o Numero: ");
    scanf("%d",&arv);

    if (arv==2)
    {
        while(opt)
        {
            printf("\n--------------\n");
            puts("1 - Inserir AVL");
            puts("2 - Contar");
            puts("3 - Imprimir por niveis");
            puts("4 - Imprime Arvore com Conio");
            puts("5 - Fator");
            puts("0 - Sair");
            printf("--------------");
            printf("\n");
            scanf("%d",&opt);
            switch(opt)
            {
            case 1:
                puts("Digite o Numero a ser inserido");
                scanf("%d",&dado);
                arvore=InsereArvore(arvore,dado);
                Atualiza_Info(&arvore);
                arvore=Rotacao(arvore);
                break;
            case 2:
                printf("\n Quantia: %d",conta_nodos(arvore));
                break;
            case 3:
                ImprimeNiveis(arvore, 0);
                break;
            case 4:
                system("cls");
                imprimir_desenhando(arvore,1,1,' ');
                break;
            case 5:
                printf("\nFator da arvore: %d",FatorDaArvore(arvore));
                break;
            case 0:
                opt=0;
                break;
            }
        }
    }
    else if (arv==1)
    {
        while(opt)
        {
            printf("\n--------------\n");
            puts("1 - Inserir ABP");
            puts("2 - Contar");
            puts("3 - Imprimir por niveis");
            puts("4 - Imprime Arvore com Conio");
            puts("5 - Fator");
            puts("0 - Sair");
            printf("--------------");
            printf("\n");
            scanf("%d",&opt);
            switch(opt)
            {
            case 1:
                puts("Digite o Numero a ser inserido");
                scanf("%d",&dado);
                arvore=InsereArvore(arvore,dado);
                Atualiza_Info(&arvore);
                break;
            case 2:
                printf("\n Quantia: %d",conta_nodos(arvore));
                break;
            case 3:
                ImprimeNiveis(arvore, 0);
                break;
            case 4:
                system("cls");
                imprimir_desenhando(arvore,1,1,' ');
                break;
            case 5:
                printf("\nFator da arvore: %d",FatorDaArvore(arvore));
                break;
            case 0:
                opt=0;
                break;
            }
        }
    }
    return 0;
}

