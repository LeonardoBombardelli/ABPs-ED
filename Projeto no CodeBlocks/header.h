typedef struct ABP_STRUCT {
    int info;
    struct ABP_STRUCT *esq, *dir;
    int altura;
    int FB;
} ABP,AVL;



void gotoxy(int x, int y);

ABP* InicializaArvore();
ABP* InsereArvore(ABP *Raiz, int num, long int *comparacoes);
void ImprimeNiveis(ABP *Raiz, int Nivel);


// AVL
AVL* InicializaAvl();
void Atualiza_Info(AVL **Raiz);
void Mostra_Infos (AVL *Raiz);
AVL* Rotacao (AVL *Nodo,int *rotacoes,long int *comparacoes);
AVL* rotacao_direita(AVL* Nodo);
AVL* rotacao_esquerda(AVL *Nodo);
AVL* rotacao_dupla_direita (AVL* Nodo);
AVL* rotacao_dupla_esquerda (AVL *Nodo);
AVL* InsereAVL(AVL *a, int x,int *ok, long int *comparacoes, int *rotacoes);
AVL* Caso1 (AVL *a, int *ok, int *rotacoes);
AVL* Caso2 (AVL *a, int *ok, int *rotacoes);
AVL* retorna_maior(AVL **no, long int *comparacoes);
AVL* balance_tree(AVL* root,long int *comparacoes, long int *rotacoes);
AVL* deletion(AVL* root, int val,long int *comparacoes, long int *rotacoes);
AVL* inorder_succ_right_tree(AVL* root,long int *comparacoes, long int *rotacoes);
int get_balance(AVL* root,long int *comparacoes, long int *rotacoes);
AVL* balance_tree(AVL* root,long int *comparacoes, long int *rotacoes);
int get_height(AVL* root,long int *comparacoes, long int *rotacoes);


// FUNCOES QUE AS DUAS USAM

int FatorNodo(ABP* Nodo);
int AlturaNodo(ABP* a);
int conta_nodos(ABP *Raiz);
int AchaNodo(ABP *Nodo, int info, long int *comparacoes);
int the_maior(ABP *nodo, long int *comparacoes);
ABP* RemoveNodo(ABP *raiz, int nodo, long int *comparacoes);
int FatorArvore(ABP *Raiz);

