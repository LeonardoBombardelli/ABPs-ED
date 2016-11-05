#include "header.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main(int argc, char *argv[])
{
    AVL *arvore = InicializaAvl();
    int opt =1,dado=0,inf=0;

    while(opt)
    {
        printf("\n--------------\n");
        puts("1 - Inserir AVL");
        puts("2 - Contar");
        puts("3 - Imprimir por niveis");
        puts("4 - Fator Balanceamento");
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
            arvore=Rotacao(arvore);break;
            Atualiza_Info(&arvore);
        case 2:
            printf("\n Quantia: %d",conta_nodos(arvore));break;
        case 3:
            ImprimeNiveis(arvore, 0);break;
        case 4:
            printf("\n%d",FatorArvore(arvore));break;
        case 5:
            system("cls");
            imprimir_desenhando(arvore,1,1,' ');break;
        case 0:
            opt=0;break;
        }
    }
}

