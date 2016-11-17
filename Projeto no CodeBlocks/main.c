#include "header.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
int main(int argc, char *argv[])
{
    FILE* Entrada;
    FILE* Saida;
    FILE* Inserindo;
    ABP   *abptree=NULL,*avltree=NULL;
    char bug;
    char insere_arquivo[20];
    char comando;
    int valor_lido,rotacoes,nodos;
    int comparacoes;
    float time;
    clock_t  start;
    clock_t  end;

    printf("Comecando \n");
    if(argc != 3)
    {
        printf("Esperava 3 argumentos, recebeu %d argumentos", argc);
        return 1;
    }
    else
    {
        Entrada = fopen(argv[1], "r");
        if (Entrada == NULL)
        {
            printf("Erro ao abrir arquivo 1");
            return 1;
        }

        Saida = fopen(argv[2], "w");
        while(!feof(Entrada))                       // Repete até o roteiro acabar
        {
            fscanf(Entrada, "%c",&comando);         // Pega o comando e o lixo que vem após
            fscanf(Entrada, "%c",&bug);
            printf("\n%c\n",comando);
            if (comando == 'I')                     // Se for inserir, vai abrir outro arquivo
            {
                fscanf(Entrada, "%s",&insere_arquivo);  // Pega o nome do arquivo do primeiro arquivo
                fscanf(Entrada, "%c",&bug);             // Pega o lixo
                Inserindo = fopen(insere_arquivo,"r");  // Abre o arquivo que tem os dados
                comparacoes=0;                          // Zera as variaveis, arvores e o tempo
                start = clock();
                time = 0;
                nodos=0;
                abptree=NULL;
                while(!feof(Inserindo))                 // Enquanto não acabar vai inserir na árvore e atualizar seus valores
                {
                    fscanf(Inserindo, "%i",&valor_lido);    // Le os valores desse outro arquivo
                    printf("\n%d",valor_lido);
                    abptree=InsereArvore(abptree,valor_lido,&comparacoes);
                    nodos+=1;
                }
            end = clock();                                 // Termina o tempo e grava no arquivo de saída as informações
            time = (float)(end - start) / CLOCKS_PER_SEC;
            fclose(Inserindo);
            fprintf(Saida,"*********VERSÃO COM ABP***********\n");
            fprintf(Saida,"Inserindo dados do arquivo %s\n",insere_arquivo);
            fprintf(Saida,"********ESTATÍSTICAS ABP***********\n");
            fprintf(Saida,"Tempo: %f ms\n",time);
            fprintf(Saida,"Nodos: %d\n",nodos);
            fprintf(Saida,"Altura: %d\n",AlturaNodo(abptree));
            fprintf(Saida,"Fator: %d\n",FatorArvore(abptree));
            fprintf(Saida,"Comparações: %d\n",comparacoes);
            fprintf(Saida,"Rotações: 0\n");
            fprintf(Saida,"----------------------------------\n");
            }
            if (comando == 'E')
            {
                printf("\nESTATISTICAS BONITAS\n");
            }
            if (comando == 'R')
            {
                printf("\nESTOU REMOVENDO\n");
            }
        }
        fclose(Entrada);            // Fecho o primeiro arquivo para reseta-lo e começar a AVL
        //------------------------------------ AVL --------------------------------------//
        Entrada = fopen(argv[1], "r");
        while(!feof(Entrada))
        {
            fscanf(Entrada, "%c",&comando);         // Pega o comando e o lixo que vem após
            fscanf(Entrada, "%c",&bug);
            printf("\n%c\n",comando);
            if (comando == 'I')                     // Se for inserir, vai abrir outro arquivo
            {
                fscanf(Entrada, "%s",&insere_arquivo);
                puts(insere_arquivo);
                fscanf(Entrada, "%c",&bug);
                Inserindo = fopen(insere_arquivo,"r");
                comparacoes=0;
                start = clock();
                time =0;
                nodos=0;
                rotacoes=0;
                avltree=NULL;
                while(!feof(Inserindo))
                {
                    fscanf(Inserindo, "%i",&valor_lido);    // Le os valores desse outro arquivo
                    printf("\n%d",valor_lido);
                    avltree=InsereArvore(avltree,valor_lido,&comparacoes);
                    Atualiza_Info(&avltree);
                    Rotacao(avltree,&rotacoes);
                    nodos+=1;
                }

            end = clock();
            time = (float)(end - start) / CLOCKS_PER_SEC;
            fclose(Inserindo);
            fprintf(Saida,"*********VERSÃO COM AVL***********\n");
            fprintf(Saida,"Inserindo dados do arquivo %s\n",insere_arquivo);
            fprintf(Saida,"********ESTATÍSTICAS AVL***********\n");
            fprintf(Saida,"Tempo: %f ms\n",time);
            fprintf(Saida,"Nodos: %d\n",nodos);
            fprintf(Saida,"Altura: %d\n",AlturaNodo(avltree));
            fprintf(Saida,"Fator: %d\n",FatorArvore(avltree));
            fprintf(Saida,"Comparações: %d\n",comparacoes);
            fprintf(Saida,"Rotações: %d\n",rotacoes);
            fprintf(Saida,"----------------------------------\n");
            }
            if (comando == 'E')
            {
                printf("\nESTATISTICAS BONITAS\n");
            }
            if (comando == 'R')
            {
                printf("\nESTOU REMOVENDO\n");
            }
        }
    }
    return 0;
}

