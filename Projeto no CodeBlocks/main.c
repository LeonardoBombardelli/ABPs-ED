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
    FILE* Removendo;
    FILE* Consultando;
    ABP   *abptree=NULL,*avltree=NULL;
    char acao[40];
    char bug;
    char insere_arquivo[20];
    char consulta_arquivo[20];
    char comando;
    int valor_lido,nodos;
    double comparacoes,rotacoes;
    clock_t time;
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
        while(!feof(Entrada))                       // Repete at� o roteiro acabar
        {
            fscanf(Entrada, "%c",&comando);         // Pega o comando e o lixo que vem ap�s
            fscanf(Entrada, "%c",&bug);
            printf("\n%c\n",comando);
            if (comando == 'I')                     // Se for inserir, vai abrir outro arquivo
            {
                fscanf(Entrada, "%s",&insere_arquivo);  // Pega o nome do arquivo do primeiro arquivo
                fscanf(Entrada, "%c",&bug);             // Pega o lixo
                Inserindo = fopen(insere_arquivo,"r");  // Abre o arquivo que tem os dados
                comparacoes=0;                          // Zera as variaveis e o tempo
                start = clock();
                time = 0;
                rotacoes=0;
                while(!feof(Inserindo))                 // Enquanto n�o acabar vai inserir na �rvore e atualizar seus valores
                {
                    fscanf(Inserindo, "%i",&valor_lido);    // Le os valores desse outro arquivo
                    abptree=InsereArvore(abptree,valor_lido,&comparacoes);
                }
                end = clock();                                 // Termina o tempo e grava no arquivo de sa�da as informa��es
                time = 1000 * (end - start) / CLOCKS_PER_SEC;
                fclose(Inserindo);
                strcpy(acao,"Inserindo dados do arquivo");
            }
            if (comando == 'E')     // Grava as estatisticas
            {
                fprintf(Saida,"*********VERS�O COM ABP***********\n");
                fprintf(Saida,"%s %s\n",acao,insere_arquivo);
                fprintf(Saida,"********ESTAT�STICAS ABP***********\n");
                fprintf(Saida,"Tempo: %ld ms\n",time);
                fprintf(Saida,"Nodos: %d\n",conta_nodos(abptree));
                fprintf(Saida,"Altura: %d\n",AlturaNodo(abptree));
                fprintf(Saida,"Fator: %d\n",FatorArvore(abptree));
                fprintf(Saida,"Compara��es: %.0lf\n",comparacoes);
                fprintf(Saida,"Rota��es: %.0lf\n",rotacoes);
                fprintf(Saida,"----------------------------------\n");
            }
            if (comando == 'R')
            {
                fscanf(Entrada, "%s",&insere_arquivo);  // Pega o nome do arquivo do primeiro arquivo
                fscanf(Entrada, "%c",&bug);             // Pega o lixo
                Removendo = fopen(insere_arquivo,"r");  // Abre o arquivo que tem os dados
                comparacoes=0;                          // Zera as variaveis e o tempo
                start = clock();
                time = 0;
                nodos=0;
                rotacoes=0;
                while(!feof(Removendo))                 // Enquanto n�o acabar vai inserir na �rvore e atualizar seus valores
                {
                    fscanf(Removendo, "%i",&valor_lido);    // Le os valores desse outro arquivo
                    abptree=RemoveNodo(abptree,valor_lido,&comparacoes);
                    nodos+=1;
                }
                end = clock();                                 // Termina o tempo e grava no arquivo de sa�da as informa��es
                time = 1000 * (end - start) / CLOCKS_PER_SEC;
                fclose(Removendo);
                strcpy(acao,"Removendo dados do arquivo");
            }
            if (comando == 'C')
            {
                fscanf(Entrada, "%s",&consulta_arquivo);  // Pega o nome do arquivo do primeiro arquivo
                fscanf(Entrada, "%c",&bug);             // Pega o lixo ap�s
                Consultando = fopen(consulta_arquivo,"r");  // Abre o arquivo que tem os dados
                comparacoes=0;                          // Zera as variaveis e o tempo
                start = clock();
                time = 0;
                nodos=0;
                rotacoes=0;
                while(!feof(Inserindo))                 // Enquanto n�o acabar vai inserir na �rvore e atualizar seus valores
                {
                    fscanf(Inserindo, "%i",&valor_lido);    // Le os valores desse outro arquivo
                    AchaNodo(abptree,valor_lido,&comparacoes);
                }
                end = clock();                                 // Termina o tempo e grava no arquivo de sa�da as informa��es
                time = 1000 * (end - start) / CLOCKS_PER_SEC;
                fclose(Inserindo);
                strcpy(acao,"Consultando dados do arquivo");
            }
        }
        fclose(Entrada);            // Fecho o primeiro arquivo para reseta-lo e come�ar a AVL
        //------------------------------------ AVL --------------------------------------//
        Entrada = fopen(argv[1], "r");
        while(!feof(Entrada))
        {
            fscanf(Entrada, "%c",&comando);         // Pega o comando e o lixo que vem ap�s
            fscanf(Entrada, "%c",&bug);
            printf("\n%c\n",comando);
            if (comando == 'I')                     // Se for inserir, vai abrir outro arquivo
            {
                fscanf(Entrada, "%s",&insere_arquivo);
                fscanf(Entrada, "%c",&bug);
                Inserindo = fopen(insere_arquivo,"r");
                comparacoes=0;
                start = clock();
                time =0;
                rotacoes=0;
                while(!feof(Inserindo))
                {
                    fscanf(Inserindo, "%i",&valor_lido);    // Le os valores desse outro arquivo
                    avltree=InsereArvore(avltree,valor_lido,&comparacoes);
                    Atualiza_Info(&avltree);
                    avltree=Rotacao(avltree,&rotacoes,&comparacoes);
                }
                end = clock();
                time = 1000 * (end - start) / CLOCKS_PER_SEC;
                fclose(Inserindo);
                strcpy(acao,"Inserindo dados do arquivo");
            }
            if (comando == 'E') // IMPRIMI
            {
                fprintf(Saida,"*********VERS�O COM AVL***********\n");
                fprintf(Saida,"%s %s\n",acao,insere_arquivo);
                fprintf(Saida,"********ESTAT�STICAS AVL***********\n");
                fprintf(Saida,"Tempo: %ld ms\n",time);
                fprintf(Saida,"Nodos: %d\n",conta_nodos(avltree));
                fprintf(Saida,"Altura: %d\n",AlturaNodo(avltree));
                fprintf(Saida,"Fator: %d\n",FatorArvore(avltree));
                fprintf(Saida,"Compara��es: %.0lf\n",comparacoes);
                fprintf(Saida,"Rota��es: %.0lf\n",rotacoes);
                fprintf(Saida,"----------------------------------\n");
            }

            if (comando == 'R')
            {
                fscanf(Entrada, "%s",&insere_arquivo);  // Pega o nome do arquivo do primeiro arquivo
                fscanf(Entrada, "%c",&bug);             // Pega o lixo
                Removendo = fopen(insere_arquivo,"r");  // Abre o arquivo que tem os dados
                comparacoes=0;                          // Zera as variaveis e o tempo
                start = clock();
                time = 0;
                nodos=0;
                rotacoes=0;
                while(!feof(Removendo))                 // Enquanto n�o acabar vai inserir na �rvore e atualizar seus valores
                {
                    fscanf(Removendo, "%i",&valor_lido);    // Le os valores desse outro arquivo
                    avltree=RemoveNodo(avltree,valor_lido,&comparacoes);
                    Atualiza_Info(&avltree);
                    avltree=Rotacao(avltree,&rotacoes,&comparacoes);
                }
                end = clock();                                 // Termina o tempo e grava no arquivo de sa�da as informa��es
                time = 1000 * (end - start) / CLOCKS_PER_SEC;
                fclose(Removendo);
                strcpy(acao,"Removendo dados do arquivo");
            }
            if (comando == 'C')
            {
                fscanf(Entrada, "%s",&consulta_arquivo);  // Pega o nome do arquivo do primeiro arquivo
                fscanf(Entrada, "%c",&bug);             // Pega o lixo ap�s
                Consultando = fopen(consulta_arquivo,"r");  // Abre o arquivo que tem os dados
                comparacoes=0;                          // Zera as variaveis e o tempo
                start = clock();
                time = 0;
                nodos=0;
                rotacoes=0;
                while(!feof(Inserindo))                 // Enquanto n�o acabar vai inserir na �rvore e atualizar seus valores
                {
                    fscanf(Inserindo, "%i",&valor_lido);    // Le os valores desse outro arquivo
                    AchaNodo(avltree,valor_lido,&comparacoes);
                }
                end = clock();                                 // Termina o tempo e grava no arquivo de sa�da as informa��es
                time = 1000 * (end - start) / CLOCKS_PER_SEC;
                fclose(Inserindo);
                strcpy(acao,"Consultando dados do arquivo");
            }
        }
    }
    return 0;
}

