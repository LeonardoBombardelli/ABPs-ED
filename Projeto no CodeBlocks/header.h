typedef struct ABP_STRUCT {
    int info;
    struct ABP_STRUCT *esq, *dir;
} ABP;

typedef struct AVL_STRUCT {
    int info;
    struct AVL_STRUCT *esq, *dir;
    int esq_alt,dir_alt,fator;
}AVL;

ABP* InicializaArvore();
ABP* InsereArvore(ABP *Raiz, int num);
void ImprimeNiveis(ABP *Raiz, int Nivel);
int FatorNodo(ABP* Nodo);
int AlturaNodo(ABP* a);
int conta_nodos(ABP *Raiz);

// AVL
AVL* InicializaAvl();
AVL* InsereArvoreAVL(AVL *Raiz, int num);
void Atualiza_Info(AVL **Raiz);
void Mostra_Infos (AVL *Raiz);
int AlturaNodoAVL(AVL *a);
int FatorNodoAVL(AVL* Nodo);
