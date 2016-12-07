#include "header.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define X 40    // ALTERAR O VALOR PARA MUDAR O INICIO DA ARVORE NO EIXO X


//---------------------------------------------------------------------------------//

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

ABP* InsereArvore(ABP *Raiz, int num,long long int *comparacoes)
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


AVL* InsereAVL(AVL *a, int x, int *ok,long long int *comparacoes,long long int*rotacoes)
/*  Retirado do Moodle */
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
    x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL)
    {
        *comparacoes+=1;
        a = (AVL*) malloc(sizeof(AVL));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (x < a->info)
    {
        *comparacoes+=2;
        a->esq = InsereAVL(a->esq,x,ok,comparacoes,rotacoes);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                comparacoes+=1;
                a=Caso1(a,ok,rotacoes, comparacoes);
                break;
            }
        }
    }
    else
    {
        *comparacoes+=1;
        a->dir = InsereAVL(a->dir,x,ok,comparacoes,rotacoes);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                *comparacoes+=1;
                a = Caso2(a,ok,rotacoes, comparacoes);
                break;
            }
        }
    }
    a->altura=AlturaNodoAVL(a);
    return a;
}

int AlturaNodoAVL(AVL *T) //Recebe raiz, retorna altura
{
    int lh,rh;
    if(T==NULL)
        return(0);

    if(T->esq==NULL)
        lh=0;
    else
        lh=1+T->esq->altura;

    if(T->dir==NULL)
        rh=0;
    else
        rh=1+T->dir->altura;

    if(lh>rh)
        return(lh);
    return(rh);
}

AVL* Caso1 (AVL *a, int *ok,long long int *rotacoes,long long int *comparacoes)
/*  Retirado do Moodle */
{
    AVL *ptu;
    ptu = a->esq;
    *comparacoes+=1;
    if (ptu->FB == 1)
    {
        *rotacoes+=1;
        a = rotacao_direita(a);
    }
    else
    {
        *rotacoes+=2;
        a = rotacao_dupla_direita(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

AVL* Caso2 (AVL *a, int *ok,long long int *rotacoes,long long int *comparacoes)
/*  Retirado do Moodle */
{
    AVL *ptu;
    ptu = a->dir;
    *comparacoes+=1;
    if (ptu->FB == -1)
    {
        *rotacoes+=1;
        a=rotacao_esquerda(a);
    }
    else
    {
        *rotacoes+=2;
        a=rotacao_dupla_esquerda(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}
AVL* retorna_maior(AVL **no,long long int *comparacoes)
{
    AVL *aux;
    aux = *no;
    *comparacoes+=1;
    if (aux->dir==NULL)
    {
        *no=(*no)->esq;
        return aux;
    }
    else
        return retorna_maior(&(*no)->dir,comparacoes);
}


/*
Funcoes para remocao de nodos de AVLs foram baseadas nas funcoes do site http://www.edufyme.com/code/?id=34173cb38f07f89ddbebc2ac9128303f
*/
AVL* Pega_Arvore_Direita(AVL* Raiz,long long int *comparacoes,long long int *rotacoes)
{
    AVL* temp = Raiz->dir;
    while(temp->esq)
    {
        *comparacoes+=1;
        temp = temp->esq;
    }
    *comparacoes+=1;
    return temp;
}

AVL* RemoveAVL(AVL* Raiz, int val,long long int *comparacoes,long long int *rotacoes)
{
    AVL* temp;
    *comparacoes+=1;
    if(!Raiz)
        return NULL;
    *comparacoes+=1;
    if(Raiz->info > val)
    {
        Raiz->esq = RemoveAVL(Raiz->esq, val,comparacoes,rotacoes);
    }
    else if(Raiz->info < val)
    {
        *comparacoes+=1;
        Raiz->dir = RemoveAVL(Raiz->dir, val,comparacoes,rotacoes);
    }
    else
        //Se chegou aqui, val = Raiz->info
    {
        *comparacoes+=1;
        *comparacoes+=1;
        if(Raiz->esq == NULL || Raiz->dir == NULL)
        {
            //Se um dos nodos forem vazios, apenas deslocamos seu nodo filho para sua posicao
            *comparacoes+=1;
            if(Raiz->esq)
                temp = Raiz->esq;
            else if(Raiz->dir)
            {
                *comparacoes+=1;
                temp = Raiz->dir;
            }
            else    //Se ambos forem vazios, nodo a ser eliminado = nodo folha
            {
                *comparacoes+=1;
                *comparacoes+=1;
                temp = NULL;
            }
            Raiz = NULL;
            free(Raiz);
            return temp;
        }
        else    //So entra aqui se nodo a ser removido tem 2 nodos filhos
        {
            temp = Pega_Arvore_Direita(Raiz,comparacoes,rotacoes);
            Raiz->info = temp->info; //Pega o menor nodo do filho direito e coloca no lugar da raiz
            Raiz->dir = RemoveAVL(Raiz->dir,temp->info,comparacoes,rotacoes); //Remove menor (certamente e nodo folha/1 filho)
        }
    }
    *comparacoes+=1;
    if(Raiz)    //Balanceia arvore de novo
    {
        Raiz->altura = max(Pega_Altura(Raiz->esq,comparacoes,rotacoes), Pega_Altura(Raiz->dir,comparacoes,rotacoes)) + 1;
        int balance = Pega_Balanceamento(Raiz,comparacoes,rotacoes);
        *comparacoes+=1;
        if(balance > 1 || balance < -1)
        {
            Raiz = Balanceamento_Arvore(Raiz,comparacoes,rotacoes);
        }
    }
    return Raiz;
}

int Pega_Balanceamento(AVL* Raiz,long long int *comparacoes,long long int*rotacoes)
{
    *comparacoes+=1;
    if(!Raiz)
        return 0;
    return (Pega_Altura(Raiz->esq,comparacoes,rotacoes) - Pega_Altura(Raiz->dir,comparacoes,rotacoes));
}

int Pega_Altura(AVL* Raiz,long long int *comparacoes,long long int *rotacoes)
{
    *comparacoes+=1;
    if(!Raiz)
        return 0;
    else
        return Raiz->altura;
}

AVL* Balanceamento_Arvore(AVL* Raiz,long long int *comparacoes,long long int *rotacoes)
{
    AVL* x, *y;
    int AlturaEsq,AlturaDir;
    AlturaEsq = Pega_Altura(Raiz->esq,comparacoes,rotacoes);
    AlturaDir = Pega_Altura(Raiz->dir,comparacoes,rotacoes);
    *comparacoes+=1;
    if(AlturaEsq >= AlturaDir)
        x = Raiz->esq;
    else
        x = Raiz->dir;
    AlturaEsq = Pega_Altura(x->esq,comparacoes,rotacoes);
    AlturaDir = Pega_Altura(x->dir,comparacoes,rotacoes);
    *comparacoes+=1;
    if(x == Raiz->esq)
    {
        *comparacoes+=1;
        if(AlturaEsq >= AlturaDir)
        {
            y = x->esq;
        }
        else
            y = x->dir;
    }
    *comparacoes+=1;
    if(x == Raiz->dir)
    {
        *comparacoes+=1;
        if(AlturaEsq > AlturaDir)
        {
            y = x->esq;
        }
        else
            y = x->dir;
    }

    *comparacoes+=1;
    if(Raiz->esq == x && x->esq == y)
    {
        *rotacoes+=1;
        Raiz = rotacao_direita(Raiz);
    }

    else if(x == Raiz->dir && x->dir == y)
    {
        *comparacoes+=1;
        *rotacoes+=1;
        Raiz = rotacao_esquerda(Raiz);
    }

    else if(x == Raiz->esq && y == x->dir)
    {
        *comparacoes+=1;
        *comparacoes+=1;
        *rotacoes+=1;
        *rotacoes+=1;
        Raiz->esq = rotacao_esquerda(Raiz->esq);
        Raiz = rotacao_direita(Raiz);
    }

    else if(x == Raiz->dir && y == x->esq)
    {
        *comparacoes+=1;
        *comparacoes+=1;
        *comparacoes+=1;
        *rotacoes+=1;
        *rotacoes+=1;
        Raiz->dir = rotacao_direita(Raiz->dir);
        Raiz = rotacao_esquerda(Raiz);
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
        return abs((AlturaNodo(Nodo->esq) - AlturaNodo(Nodo->dir)));
    }
    else
        return 0;
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

//------------------------------------------------------------------------------//

int AchaNodo(ABP *Nodo, int info,long long int *comparacoes)
{
    while(Nodo != NULL)
    {
        *comparacoes+=2;
        if(Nodo->info == info)
            return 1;
        else
        {
            *comparacoes+=1;
            if(Nodo->info > info)
                Nodo = Nodo->esq;
            else
                Nodo = Nodo->dir;
        }
    }
    return 0;
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
}

//---------------------------------------------------------------------------------//

AVL* Rotacao (AVL *Nodo,int *rotacoes,long long int *comparacoes)
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
            *rotacoes+=2;
            Nodo=rotacao_dupla_direita(Nodo);
        }
        if (Nodo->FB < -1 && FatorNodo(Nodo->dir) > 0)    // ROT DUP ESQ
        {
            *comparacoes+=1;
            *rotacoes+=2;
            Nodo=rotacao_dupla_esquerda(Nodo);
        }
        Nodo->esq=Rotacao(Nodo->esq,rotacoes,comparacoes);
        Nodo->dir=Rotacao(Nodo->dir,rotacoes,comparacoes);
        return Nodo;
    }
    else
        return Nodo;

}

//---------------------------------------------------------------------------------//

ABP* RemoveNodo(ABP *raiz, int nodo,long long int *comparacoes)
{
    ABP *aux;
    ABP *anterior;

    aux = raiz;
    anterior=NULL;
    while ( (aux !=  NULL ) && (aux->info != nodo) )
    {
        *comparacoes+=3;
        anterior = aux;
        if (aux->info < nodo)
            aux = aux->dir;
        else
            aux = aux->esq;
    }
    *comparacoes+=3;
    if (aux != NULL)
    {
        *comparacoes+=1;
        if (aux->info == nodo)
        {
            *comparacoes+=1;
            if ((aux->esq == NULL) && (aux->dir == NULL)) // Ve se o nodo removido nao eh folha
            {
                *comparacoes+=2;
                // Ve se não é raiz
                if (anterior)
                {
                    *comparacoes+=1;
                    // Testa se o anterior é esq ou direita e zera o pai
                    if (anterior->info > aux->info)
                        anterior->esq = NULL;
                    else
                        anterior->dir = NULL;
                    free(aux);
                }
                else
                    raiz = NULL;
            }
            // COMO NAO EH FOLHA SEGUE O BAILE
            else
            {
                *comparacoes+=2;
                if ( (aux->dir == NULL ) || (aux->esq == NULL) )
                {
                    *comparacoes+=2;
                    if (aux->dir == NULL) // DA DIREITA EH NULL VERIFICA SE A ESQ TEM ALGO
                    {
                        *comparacoes+=1;
                        if (anterior)
                        {
                            *comparacoes+=1;
                            if (anterior->info < aux->info)
                            {
                                anterior->dir = aux->esq;
                                free(aux);
                            }
                            else
                            {
                                anterior->esq = aux->esq;
                                free(aux);
                            }
                        }
                        else // EH RAIZ
                        {
                            raiz = raiz->esq;
                        }
                    }
                    else
                    {
                        *comparacoes+=1;
                        if (anterior)
                        {
                            *comparacoes+=1;
                            if (anterior->info < aux->info)
                            {
                                anterior->dir = aux->dir;
                                free(aux);
                            }
                            else
                            {
                                anterior->esq = aux->dir;
                                free(aux);
                            }
                        }
                        else // Eh RAIZ
                        {
                            raiz = raiz->dir;
                        }
                    }
                }
                else // NODO TEM DUAS SUB
                {
                    aux->info = the_maior(aux->esq, comparacoes);
                    aux->esq = RemoveNodo(aux->esq, aux->info, comparacoes);
                }
            }
        }
    }
    return raiz;
}

int the_maior(ABP *nodo,long long int *comparacoes)
{
    int max;

    while(nodo->dir)
    {
        *comparacoes+=1;
        nodo=nodo->dir;
    }
    *comparacoes+=1;
    max=nodo->info;
    return max;
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
