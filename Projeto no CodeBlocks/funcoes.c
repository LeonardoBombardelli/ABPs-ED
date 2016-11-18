#include "header.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define X 40    // ALTERAR O VALOR PARA MUDAR O INICIO DA ARVORE NO EIXO X


//---------------------------------------------------------------------------------//

void gotoxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD)
    {
        x-1,y-1
    });
}

//==================================================================================//

ABP* InicializaArvore()
{
    return NULL;
}

AVL* InicializaAvl()
{
    return NULL;
}

//---------------------------------------------------------------------------------//

ABP* InsereArvore(ABP *Raiz, int num, double *comparacoes)
{
    if (Raiz == NULL)
    {
        Raiz = (ABP*) malloc(sizeof(ABP));
        Raiz->info = num;
        Raiz->esq = NULL;
        Raiz->dir = NULL;
        Raiz->FB  = 0;
    }
    else if (num < (Raiz->info))
    {
        *comparacoes+=1;
        Raiz->esq = InsereArvore(Raiz->esq, num, comparacoes);
    }
    else
    {
        *comparacoes+=1;
        Raiz->dir = InsereArvore(Raiz->dir, num, comparacoes);
    }
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

int FatorDaArvore(ABP *a)
{
    int balanc;

    if (a)
    {
        balanc=AlturaNodo(a->esq)-AlturaNodo(a->dir);
        if(balanc < 0)
            balanc=balanc*-1;
        return balanc;
    }
    else
        return 0;
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
        Raiz->FB   = 0;
    }
    else if (num < (Raiz->info))
        Raiz->esq = InsereArvoreAVL(Raiz->esq, num);
    else
        Raiz->dir = InsereArvoreAVL(Raiz->dir, num);
    return Raiz;
}

//------------------------------------------------------------------------------//

int AchaNodo(ABP *Nodo, int info, double *comparacoes)
{
    ABP *achou = NULL;

    if(Nodo == NULL)
    {
        return 0;
    }
    else
    {
        *comparacoes+=1;
        if(Nodo->info == info)
        {
            return 1;
        }
        else
        {
            if(info > Nodo->info)
            {
                *comparacoes+=1;
                return achou = AchaNodo(Nodo->dir, info, comparacoes);
            }
            else if(info <= Nodo->info)
            {
                *comparacoes+=1;
                return AchaNodo(Nodo->esq, info, comparacoes);
            }
        }
    }
}

//------------------------------------------------------------------------------//

void Atualiza_Info(AVL **Raiz)
{
    if (Raiz!=NULL)
    {
        if(*Raiz)
        {
            (*Raiz)->FB=FatorNodo(*Raiz);
            Atualiza_Info(&(*Raiz)->dir);
            Atualiza_Info(&(*Raiz)->esq);
        }
    }
}

//-------------------------------------------------------------------------------//

void Mostra_Infos (AVL *Raiz)
{
    printf("\n %d",Raiz->info);
    printf("   Vai se foder Fator: %d\n",Raiz->FB);
}

//---------------------------------------------------------------------------------//

AVL* Rotacao (AVL *Nodo,double *rotacoes,double *comparacoes)
{
    if (Nodo)
    {
        if (Nodo->FB > 1 && FatorNodo(Nodo->esq) > 0)     // ROT SIMP DIR
        {
            *comparacoes+=1;
            *rotacoes+=1;
            Nodo=rotacao_direita(Nodo);
        }
        if (Nodo->FB < -1 && FatorNodo(Nodo->dir) < 0)    // ROT SIMP ESQ
        {
            *comparacoes+=1;
            *rotacoes+=1;
            Nodo=rotacao_esquerda(Nodo);
        }
        if (Nodo->FB > 1 && FatorNodo(Nodo->esq) < 0)     // ROT DUP DIR
        {
            *comparacoes+=1;
            *rotacoes+=1;
            Nodo=rotacao_dupla_direita(Nodo);
        }
        if (Nodo->FB < -1 && FatorNodo(Nodo->dir) > 0)    // ROT DUP ESQ
        {
            *comparacoes+=1;
            *rotacoes+=1;
            Nodo=rotacao_dupla_esquerda(Nodo);
        }
        Nodo->esq=Rotacao(Nodo->esq,rotacoes,comparacoes);
        Nodo->dir=Rotacao(Nodo->dir,rotacoes,comparacoes);
        return Nodo;
    }
    else
        return Nodo;

}

//------------------------ROTAÇÕES----------------------------------------------------//

AVL* rotacao_direita(AVL* Nodo)
{
    AVL *aux;
    aux = Nodo->esq;
    Nodo->esq = aux->dir;
    aux->dir = Nodo;
    Nodo->FB = 0;
    Nodo = aux;
    return Nodo;
}

AVL* rotacao_esquerda(AVL *Nodo)
{
    AVL *aux;
    aux = Nodo->dir;
    Nodo->dir = aux->esq;
    aux->esq = Nodo;
    Nodo->FB = 0;
    Nodo = aux;
    return Nodo;
}

AVL* rotacao_dupla_direita (AVL* Nodo)
{
    AVL *aux, *aux2;
    aux = Nodo->esq;
    aux2 = aux->dir;
    aux->dir = aux2->esq;
    aux2->esq = aux;
    Nodo->esq = aux2->dir;
    aux2->dir = Nodo;
    if (aux2->FB == 1) Nodo->FB = -1;
    else Nodo->FB = 0;
    if (aux2->FB == -1) aux->FB = 1;
    else aux->FB = 0;
    Nodo = aux2;
    return Nodo;
}

AVL* rotacao_dupla_esquerda (AVL *Nodo)
{
    AVL *aux, *aux2;
    aux = Nodo->dir;
    aux2 = aux->esq;
    aux->esq = aux2->dir;
    aux2->dir = aux;
    Nodo->dir = aux2->esq;
    aux2->esq = Nodo;
    if (aux2->FB == -1) Nodo->FB = 1;
    else Nodo->FB = 0;
    if (aux2->FB == 1) aux->FB = -1;
    else aux->FB = 0;
    Nodo = aux2;
    return Nodo;
}

// ------------------------- AUXILIAR --------------------------------//

void imprimir_desenhando(AVL *node,int contadorX,int contadorY, char ch)
{
    if (ch==' ' && node)
    {
        gotoxy(X+contadorX,contadorY);
        printTreeInfo(*node);
        imprimir_desenhando(node->dir,6,contadorY+2,'\\');
        imprimir_desenhando(node->esq,-6,contadorY+2,'/');
    }
    else if(node)
    {
        if(ch=='/')
            gotoxy(X+contadorX+1,contadorY-1);
        else
        {
            gotoxy(X+contadorX,contadorY-1);
        }
        printf("%c",ch);
        gotoxy(X+contadorX,contadorY);
        printTreeInfo(*node);
        imprimir_desenhando(node->dir,contadorX+2,contadorY+2,'\\');
        imprimir_desenhando(node->esq,contadorX-2,contadorY+2,'/');
    }
}

//-------------------------------------------------------------------------//

void printTreeInfo(AVL node)
{
    printf("%d ", node.info);
}

//--------------------------------------------------------------------------//

/*int Intersecao (ABP *um, ABP *dois, int info)
{
    if(AchaNodo(um,info)&&AchaNodo(dois,info))
        return 1;
    else
        return 0;
}

ABP* MontaInterseccao (ABP *um, ABP *dois, ABP **montado)
{

    if(um==NULL)
        return *montado;
    *montado=MontaInterseccao(um->dir,dois,montado);
    *montado=MontaInterseccao(um->esq,dois,montado);
    if(Intersecao(um,dois,um->info))
    {
        *montado=InsereArvore(*montado,um->info);
    }

    return *montado;

}
*/
