typedef struct ABP_STRUCT {
    int info;
    struct ABP_STRUCT *esq, *dir;
    int FB;
} ABP,AVL;



void gotoxy(int x, int y);

ABP* InicializaArvore();
ABP* InsereArvore(ABP *Raiz, int num, int *comparacoes);
void ImprimeNiveis(ABP *Raiz, int Nivel);


// AVL
AVL* InicializaAvl();
AVL* InsereArvoreAVL(AVL *Raiz, int num);
void Atualiza_Info(AVL **Raiz);
void Mostra_Infos (AVL *Raiz);
AVL* Rotacao (AVL *Nodo,int *rotacoes);
AVL* rotacao_direita(AVL* Nodo);
AVL* rotacao_esquerda(AVL *Nodo);
AVL* rotacao_dupla_direita (AVL* Nodo);
AVL* rotacao_dupla_esquerda (AVL *Nodo);

// FUNCOES QUE AS DUAS USAM

int FatorNodo(ABP* Nodo);
int AlturaNodo(ABP* a);
int conta_nodos(ABP *Raiz);
int FatorDaArvore(ABP *a);
int AchaNodo(ABP *Nodo, int info);
ABP* MontaInterseccao (ABP *um, ABP *dois, ABP **montado);
ABP* Intersecao (ABP *um, ABP *dois, int info);
// AUXILIAR

void imprimir_desenhando(AVL *node,int contadorX,int contadorY, char ch);
void printTreeInfo(AVL node);
