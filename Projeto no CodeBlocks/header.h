typedef struct ABP_STRUCT {
    int info;
    struct ABP_STRUCT *esq, *dir;
    int FB;
} ABP;

ABP* InicializaArvore();
ABP* InsereArvore(ABP *Raiz, int num);
void ImprimeNiveis(ABP *Raiz, int Nivel);
int FatorNodo(ABP* Nodo);
int AlturaNodo(ABP* a);

