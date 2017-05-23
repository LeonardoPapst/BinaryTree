#include <stdio.h>
#include <stdlib.h>

typedef struct tNo No;

struct tNo {
    No* pai, *direito, *esquerdo;
    int chave;
};

typedef struct {
    No* raiz;
    int quantidade;
} Arvore;

void inicializa(Arvore* a) {
    a->quantidade = 0;
    a->raiz = NULL;
}

int insere(Arvore* arv, int valor) {
	No *novo = malloc(sizeof(No));
	novo->esquerdo = NULL;
	novo->direito = NULL;
	novo->pai = NULL;
	novo->chave = valor;

	No *pai = NULL;
	No *filho = arv->raiz;
	
	while(filho!=NULL){
		pai = filho;
		if(valor < filho->chave){
			filho = filho->esquerdo;
		}
		else{
			filho = filho->direito;
		}
	}
	novo->pai = pai;
	
	if(pai!=NULL){
		if(valor < pai->chave){
			pai->esquerdo = novo;
		}
		else{
			pai->direito = novo;
		}
	}
	else
	{
		arv->raiz=novo;
	}
	arv->quantidade = arv->quantidade+1;
}

No* busca(Arvore*arv, int chave) {
	No *ptrAtual = arv->raiz;

	while(chave!=ptrAtual->chave){
		if(chave<ptrAtual->chave){
			ptrAtual = ptrAtual->esquerdo;
		}
		else
		{
			ptrAtual = ptrAtual->direito;
		}
		if(ptrAtual==NULL)
			return NULL;
	}
	if(chave==ptrAtual->chave){
    	printf("O valor %d foi encontrado\n\n", ptrAtual->chave);
    	return ptrAtual;
    }
	else
	    printf("Nao foi encontrado o dado buscado\n\n");
	return NULL;
}

int remover(Arvore* arv, int chave) {
	No *ptrAtual = busca(arv,chave);
	No *ptrAux;
	//Primeiro caso, sem nenhum filho
	if(ptrAtual->esquerdo == NULL && ptrAtual->direito == NULL){
        if(ptrAtual->pai->direito == NULL)
            ptrAtual->pai->esquerdo = NULL;
        else
			ptrAtual->pai->direito = NULL;
	}
	//Segundo caso, com 1 filho
	else if(ptrAtual->esquerdo == NULL || ptrAtual->direito == NULL){
		
		if(ptrAtual->esquerdo == NULL){	
			
			ptrAtual->direito->pai = ptrAtual->pai;
	
			if(ptrAtual->direito->chave < ptrAtual->pai->chave)
				ptrAtual->pai->esquerdo = ptrAtual->direito;
			else
				ptrAtual->pai->direito = ptrAtual->direito;

		}else{

			ptrAtual->esquerdo->pai = ptrAtual->pai;
			
			if(ptrAtual->esquerdo->chave < ptrAtual->pai->chave)
				ptrAtual->pai->esquerdo = ptrAtual->esquerdo;
			else
				ptrAtual->pai->direito = ptrAtual->esquerdo;
		}
	}
	//Terceiro caso, com 2 filhos
	else{
		ptrAux=ptrAtual->direito;
		while(ptrAux!=NULL){
			ptrAux = ptrAux->esquerdo;
			if(ptrAux->esquerdo==NULL)
				break;
		}
	
		if(ptrAux->chave<ptrAtual->pai->chave)
			ptrAtual->pai->esquerdo = ptrAux;
		else
			ptrAtual->pai->direito = ptrAux;
			
		if(ptrAux->chave<ptrAux->pai->chave){
			if(ptrAux->direito){
				ptrAux->direito->pai=ptrAux->pai;
				if(ptrAux->esquerdo)
					ptrAux->esquerdo->pai = ptrAux->direito;
			}else
				ptrAux->esquerdo->pai = ptrAux->pai;
		}else
			ptrAux->pai->direito=NULL;
			
	}
	free(ptrAtual);
	arv->quantidade = arv->quantidade-1;
	return 0;
}

void preOrder(No* no) {
    printf(" %d \n", no->chave);
    if (no->esquerdo)
        preOrder(no->esquerdo);
    if (no->direito)
        preOrder(no->direito);
}

void inOrder(No* no) {
 
    if (no->esquerdo)
        inOrder(no->esquerdo);
        
    printf(" %d \n", no->chave);
    
    if (no->direito)
        inOrder(no->direito);
}

int main(int argc, char *argv[]) {

    Arvore a;
    inicializa(&a);
	insere(&a, 10);
	insere(&a, 1);
	insere(&a, 15);
	insere(&a, 12);
	insere(&a, 5);
	insere(&a, 8);
	
	preOrder(a.raiz);
	puts("--------------------------------------------------");
	inOrder(a.raiz);
	puts("--------------------------------------------------");
			
	remover(&a, 15);

	preOrder(a.raiz);
	puts("--------------------------------------------------");
	inOrder(a.raiz);
	puts("--------------------------------------------------");

    system("pause");
    return 0;
}
