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

ABP* InsereArvore(ABP *Raiz, int num, long int *comparacoes)
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

AVL* InsereAVL(AVL *a, int x, int *ok, long int *comparacoes, int *rotacoes)
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
                a=Caso1(a,ok,rotacoes);
                break;
            }
        }
    }
    else
    {
        comparacoes+=1;
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
                comparacoes+=1;
                a = Caso2(a,ok,rotacoes);
                break;
            }
        }
    }
    a->altura=AlturaNodoAVL(a);
    return a;
}
int AlturaNodoAVL(AVL *T)
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
AVL* Caso1 (AVL *a, int *ok, int *rotacoes)
{
    AVL *ptu;
    ptu = a->esq;
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

AVL* Caso2 (AVL *a, int *ok, int *rotacoes)
{
    AVL *ptu;
    ptu = a->dir;
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
AVL* retorna_maior(AVL **no, long int *comparacoes)
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

AVL* verifica_avl(AVL *no,long int *comparacoes,int *rotacoes)
{
    if (no!=NULL)
    {
        *comparacoes+=2;
        if ( (AlturaNodo(no->dir) - AlturaNodo(no->esq))==-2)
        {
            *comparacoes+=1;
            if ( (AlturaNodo(no->esq->dir) - AlturaNodo(no->esq->esq) )==-1)
            {
                *rotacoes+=1;
                no=rotacao_direita(no);
            }
            else
            {
                *rotacoes+=2;
                no=rotacao_dupla_direita(no);
            }
        }
        else if ( (AlturaNodo(no->dir) - AlturaNodo(no->esq))==2)
        {
            *comparacoes+=2;
            if((AlturaNodo(no->dir->dir)-AlturaNodo(no->dir->esq))==1)
            {
                *rotacoes+=1;
                no=rotacao_esquerda(no);
            }
            else
            {
                *rotacoes+=2;
                no=rotacao_dupla_esquerda(no);
            }
        }
        *comparacoes+=2;
        if(no->esq!=NULL)
            no->esq=verifica_avl(no->esq,comparacoes,rotacoes);
        *comparacoes+=1;
        if(no->dir!=NULL)
            no->dir=verifica_avl(no->dir,comparacoes,rotacoes);
    }
    return no;
}
AVL* inorder_succ_right_tree(AVL* root,long int *comparacoes, long int *rotacoes)
{
    AVL* temp = root->dir;
    while(temp->esq)
    {
        *comparacoes+=1;
        temp = temp->esq;
    }
    *comparacoes+=1;
    return temp;
}
AVL* deletion(AVL* root, int val,long int *comparacoes, long int *rotacoes)
{
    //normal deletion
    AVL* temp;
    *comparacoes+=1;
    if(!root)
        return NULL;
    *comparacoes+=1;
    if(root->info > val)
    {
        root->esq = deletion(root->esq, val,comparacoes,rotacoes);
    }
    else if(root->info < val)
    {
        *comparacoes+=1;
        root->dir = deletion(root->dir, val,comparacoes,rotacoes);
    }
    else
    {
        *comparacoes+=1;
        *comparacoes+=1;
        if(root->esq == NULL || root->dir == NULL)
        {
            *comparacoes+=1;
            if(root->esq)
                temp = root->esq;
            else if(root->dir)
            {
                *comparacoes+=1;
                temp = root->dir;
            }
            else
            {
                *comparacoes+=1;
                *comparacoes+=1;
                temp = NULL;
            }
            root = NULL;
            free(root);
            return temp;
        }
        else
        {
            temp = inorder_succ_right_tree(root,comparacoes,rotacoes);
            root->info = temp->info;
            root->dir = deletion(root->dir,temp->info,comparacoes,rotacoes);
        }
    }
    *comparacoes+=1;
    if(root)
    {
        //update height
        root->altura = max(get_height(root->esq,comparacoes,rotacoes), get_height(root->dir,comparacoes,rotacoes)) + 1;
        int balance = get_balance(root,comparacoes,rotacoes);
        *comparacoes+=1;
        if(balance > 1 || balance < -1)
            root = balance_tree(root,comparacoes,rotacoes);
    }
    return root;
}
int get_balance(AVL* root,long int *comparacoes, long int *rotacoes)
{
    *comparacoes+=1;
    if(!root)
        return 0;
    return (get_height(root->esq,comparacoes,rotacoes) - get_height(root->dir,comparacoes,rotacoes));
}
int get_height(AVL* root,long int *comparacoes, long int *rotacoes)
{
    *comparacoes+=1;
    if(!root)
        return 0;
    else
        return root->altura;
}
AVL* balance_tree(AVL* root,long int *comparacoes, long int *rotacoes)
{
    AVL* x, *y;
    int lheight,rheight;
    lheight = get_height(root->esq,comparacoes,rotacoes);
    rheight = get_height(root->dir,comparacoes,rotacoes);
    *comparacoes+=1;
    if(lheight >= rheight)
        x = root->esq;
    else
        x = root->dir;
    lheight = get_height(x->esq,comparacoes,rotacoes);
    rheight = get_height(x->dir,comparacoes,rotacoes);
    *comparacoes+=1;
    if(x == root->esq)
    {
        *comparacoes+=1;
        if(lheight >= rheight)
        {
            y = x->esq;
        }
        else
            y = x->dir;
    }
    *comparacoes+=1;
    if(x == root->dir)
    {
        *comparacoes+=1;
        if(lheight > rheight)
        {
            y = x->esq;
        }
        else
            y = x->dir;
    }
    //left-left case
    *comparacoes+=1;
    if(root->esq == x && x->esq == y)
    {
        *rotacoes+=1;
        root = rotacao_direita(root);
    }
    //right-right case
    else if(x == root->dir && x->dir == y)
    {
        *comparacoes+=1;
        *rotacoes+=1;
        root = rotacao_esquerda(root);
    }
    //left-right case
    else if(x == root->esq && y == x->dir)
    {
        *comparacoes+=1;
        *comparacoes+=1;
        *rotacoes+=1;
        *rotacoes+=1;
        root->esq = rotacao_esquerda(root->esq);
        root = rotacao_direita(root);
    }
    //right-left case
    else if(x == root->dir && y == x->esq)
    {
        *comparacoes+=1;
        *comparacoes+=1;
        *comparacoes+=1;
        *rotacoes+=1;
        *rotacoes+=1;
        root->dir = rotacao_direita(root->dir);
        root = rotacao_esquerda(root);
    }
    return root;
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
        return (AlturaNodo(Nodo->esq) - AlturaNodo(Nodo->dir));
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

int AchaNodo(ABP *Nodo, int info, long int *comparacoes)
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

AVL* Rotacao (AVL *Nodo,int *rotacoes,long int *comparacoes)
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

ABP* RemoveNodo(ABP *raiz, int nodo, long int *comparacoes)
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

int the_maior(ABP *nodo, long int *comparacoes)
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

