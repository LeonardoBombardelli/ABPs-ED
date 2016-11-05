#include "header.h"
#include <stdio.h>

//---------------------------------------------------------------------------------//


//==================================================================================//

ABP* InicializaArvore()
{
    return NULL;
}

//---------------------------------------------------------------------------------//

ABP* InsereArvore(ABP *Raiz, int num)
{
    if (Raiz == NULL)
    {
        Raiz = (ABP*) malloc(sizeof(ABP));
        Raiz->info = num;
        Raiz->esq = NULL;

    }
    else if (num < (Raiz->info))
        Raiz->esq = InsereArvore(Raiz->esq, num);
    else
        Raiz->dir = InsereArvore(Raiz->dir, num);
    return Raiz;
}

//---------------------------------------------------------------------------------//

void ImprimeNiveis(ABP *Raiz, int Nivel)
{
    int i;
    if (Raiz!= NULL)
    {
        for(i = 0; i <= Nivel; i++)
            printf("=");

        printf(" %d\n",Raiz->info);

        Nivel++;
        ImprimeNiveis(Raiz->esq, Nivel);
        ImprimeNiveis(Raiz->dir, Nivel);
    }
}

//---------------------------------------------------------------------------------//

int FatorNodo(ABP* Nodo)
{
    if(Nodo != NULL)
    {
        return(AlturaNodo(Nodo->esq) - AlturaNodo(Nodo->dir));
    }
    else return 0;
}

//---------------------------------------------------------------------------------//

int AlturaNodo(ABP *a)
{
    int Alt_Esq, Alt_Dir;
    if (a == NULL)
        return 0;
    else
    {
        Alt_Esq = AlturaNodo(a->esq);
        Alt_Dir = AlturaNodo(a->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}

//---------------------------------------------------------------------------------//

int FatorArvore(ABP *Raiz)
{
    int FatEsq, FatDir, FatMid;
    if (Raiz != NULL)
    {
        FatEsq = FatorArvore(Raiz->esq);
        FatDir = FatorArvore(Raiz->dir);
        FatMid = FatorNodo(Raiz);
        if((FatEsq >= FatDir) &&(FatEsq >= FatMid))
            return FatEsq;
        else if ((FatDir >= FatEsq) &&(FatDir >= FatMid))
            return FatDir;
        else return FatMid;
    }
    else return 0;
}

//---------------------------------------------------------------------------------//

int conta_nodos(ABP *Raiz)
{
    if(Raiz)
        return(1+conta_nodos(Raiz->esq)+conta_nodos(Raiz->dir));
    else
        return 0;
}

//---------------------------------------------------------------------------------//
AVL* InsereArvoreAVL(AVL *Raiz, int num)
{
    if (Raiz == NULL)
    {
        Raiz = (ABP*) malloc(sizeof(ABP));
        Raiz->info = num;
        Raiz->esq = NULL;
        Raiz->esq_alt = 0;
        Raiz->dir_alt = 0;
        Raiz->fator   = 0;
    }
    else if (num < (Raiz->info))
    {
        Raiz->esq = InsereArvore(Raiz->esq, num);
        Raiz->esq_alt = AlturaNodo(Raiz->esq)+1;
        Raiz->fator   = FatorNodo(Raiz);
    }
    else
    {
        Raiz->dir = InsereArvore(Raiz->dir, num);
        Raiz->dir_alt = AlturaNodo(Raiz->dir)+1;
        Raiz->fator   = FatorNodo(Raiz);
    }

    return Raiz;
}
