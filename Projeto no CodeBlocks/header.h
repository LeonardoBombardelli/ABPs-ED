typedef struct ABP_STRUCT {
    int info;
    struct ABP_STRUCT *esq, *dir;
    int FB;
} ABP,AVL;



void gotoxy(int x, int y);

ABP* InicializaArvore();
ABP* InsereArvore(ABP *Raiz, int num, double *comparacoes);
void ImprimeNiveis(ABP *Raiz, int Nivel);


// AVL
AVL* InicializaAvl();
void Atualiza_Info(AVL **Raiz);
void Mostra_Infos (AVL *Raiz);
AVL* Rotacao (AVL *Nodo,double *rotacoes,double *comparacoes);
AVL* rotacao_direita(AVL* Nodo);
AVL* rotacao_esquerda(AVL *Nodo);
AVL* rotacao_dupla_direita (AVL* Nodo);
AVL* rotacao_dupla_esquerda (AVL *Nodo);
AVL* InsereAVL(AVL *a, int x, int *ok, double *comparacoes, int *rotacoes);
AVL* Caso1 (AVL *a, int *ok, int *rotacoes);
AVL* Caso2 (AVL *a, int *ok, int *rotacoes);
AVL* retorna_maior(AVL **no, double *comparacoes);
AVL* exclui(AVL *no, int x, double *comparacoes,int *rotacoes);
AVL* verifica_avl(AVL *no,double *comparacoes,int *rotacoes);

// FUNCOES QUE AS DUAS USAM

int FatorNodo(ABP* Nodo);
int AlturaNodo(ABP* a);
int conta_nodos(ABP *Raiz);
int AchaNodo(ABP *Nodo, int info, double *comparacoes);
int the_maior(ABP *nodo, double *comparacoes);
ABP* RemoveNodo(ABP *raiz, int nodo, double *comparacoes);
int FatorArvore(ABP *Raiz);

