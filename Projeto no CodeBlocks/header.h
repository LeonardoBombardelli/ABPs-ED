typedef struct ABP_STRUCT {
    int info;
    struct ABP_STRUCT *esq, *dir;
} ABP;

typedef struct AVL_STRUCT {
    int info;
    struct AVL_STRUCT *esq, *dir;
    int esq_alt,dir_alt,FB;
}AVL;

void gotoxy(int x, int y);

ABP* InicializaArvore();
ABP* InsereArvore(ABP *Raiz, int num);
void ImprimeNiveis(ABP *Raiz, int Nivel);


// AVL
AVL* InicializaAvl();
AVL* InsereArvoreAVL(AVL *Raiz, int num);
void Atualiza_Info(AVL **Raiz);
void Mostra_Infos (AVL *Raiz);
AVL* Rotacao (AVL *Nodo);
AVL* rotacao_direita(AVL* Nodo);
AVL* rotacao_esquerda(AVL *Nodo);
AVL* rotacao_dupla_direita (AVL* Nodo);
AVL* rotacao_dupla_esquerda (AVL *Nodo);

// FUNCOES QUE AS DUAS USAM

int FatorNodo(ABP* Nodo);
int AlturaNodo(ABP* a);
int conta_nodos(ABP *Raiz);
int FatorDaArvore(ABP *a);
ABP* AchaNodo(ABP *Nodo, int info);

// AUXILIAR

void imprimir_desenhando(AVL *node,int contadorX,int contadorY, char ch);
void printTreeInfo(AVL node);
