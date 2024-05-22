#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct arvore {
  int info;
  struct arvore *esq;
  struct arvore *dir;
} arvore;

// lê a árvore do arquivo
arvore *lerArvore(FILE *arq) {
  char c;
  int num;

  fscanf(arq, "%c", &c);
  fscanf(arq, "%d", &num);

  if (num == -1) {
    fscanf(arq, "%c", &c);
    return NULL;
  } else {
    arvore *a = (arvore *)malloc(sizeof(arvore));
    a->info = num;
    a->esq = lerArvore(arq);
    a->dir = lerArvore(arq);
    fscanf(arq, "%c", &c);
    return a;
  }
}

// limpa a árvore da memória

void freearvore(arvore *a) {
  if (a != NULL) {
    freearvore(a->esq);
    freearvore(a->dir);
    free(a);
  }
}

// imprime em pré ordem
void preOrdem(arvore *a) {
  if (a != NULL) {
    printf("%d ", a->info);
    preOrdem(a->esq);
    preOrdem(a->dir);
  }
}

// imprime em ordem
void emOrdem(arvore *a) {
  if (a != NULL) {
    emOrdem(a->esq);
    printf("%d ", a->info);
    emOrdem(a->dir);
  }
}

// imprime em pós ordem
void posOrdem(arvore *a) {
  if (a != NULL) {
    posOrdem(a->esq);
    posOrdem(a->dir);
    printf("%d ", a->info);
  }
}

// imprime nós de um certo nível (usado para imprimir em largura)
void imprimirNosDeUmNivel(arvore *a, int cont, int n) {
  if (a != NULL) {

    if (cont == n) {
      printf("%d ", a->info);
    } else {
      imprimirNosDeUmNivel(a->esq, cont + 1, n);
      imprimirNosDeUmNivel(a->dir, cont + 1, n);
    }
  }
}

// acha a altura da árvore (usado para imprimir em largura)
int altura(arvore *a) {

  if (a == NULL)
    return 0;
  else {
    int he = altura(a->esq);
    int hd = altura(a->dir);

    if (he > hd) {
      return he + 1;
    } else {
      return hd + 1;
    }
  }
}

// imprime em largura
void largura(arvore *a, int h, int cont) {
  if (a != NULL) {

    imprimirNosDeUmNivel(a, 0, cont);

    if (cont < h) {
      largura(a, h, cont + 1);
    }
  }
}

// verifica se um certo elemendo existe na árvore
int existeABB(arvore *a, int x) {
  if (a != NULL) {
    if (a->info == x)
      return 1;
    else if (x < a->info)
      return existeABB(a->esq, x);
    else if (x > a->info)
      ;
    return existeABB(a->dir, x);
  }
  return 0;
}

// imprime o nível de um certo nó
void nivelDoNoABB(arvore *a, int x, int cont) {
  if (a != NULL) {
    if (a->info == x) {
      printf("%d", cont);
    }

    else if (a->info > x)
      nivelDoNoABB(a->esq, x, cont + 1);
    else if (a->info < x)
      nivelDoNoABB(a->dir, x, cont + 1);
  }
}

// imprime os nós folhas que são menores que um certo valor
void imprimirNosFolhaMenores(arvore *a, int x) {
  if (a != NULL) {
    if (a->info < x) {
      if (a->dir == NULL && a->esq == NULL) {
        printf("%d ", a->info);
      } else {
        imprimirNosFolhaMenores(a->esq, x);
        imprimirNosFolhaMenores(a->dir, x);
      }
    } else {
      imprimirNosFolhaMenores(a->esq, x);
    }
  }
}

// insere um elemendo na árvore
arvore *inserirNo(arvore *a, int x) {
  if (a == NULL) {
    a = malloc(sizeof(arvore));
    a->info = x;
    a->dir = NULL;
    a->esq = NULL;
  } else if (x <= a->info) {
    a->esq = inserirNo(a->esq, x);
  } else {
    a->dir = inserirNo(a->dir, x);
  }
  return a;
}

// Remove um elemendo na árvore
arvore *removerNo(arvore *a, int x) {
  if (a != NULL) {
    if (a->info == x) {
      if (a->esq == NULL && a->dir == NULL) {
        free(a);
        return NULL;
      } else if (a->esq == NULL) {
        arvore *aux = a->dir;
        free(a);
        return aux;
      } else if (a->dir == NULL) {
        arvore *aux = a->esq;
        free(a);
        return aux;
      } else {
        arvore *aux = a->esq;
        while (aux->dir != NULL) {
          aux = aux->dir;
        }
        a->info = aux->info;
        a->esq = removerNo(a->esq, aux->info);
      }
    } else if (x < a->info) {
      a->esq = removerNo(a->esq, x);
    } else {
      a->dir = removerNo(a->dir, x);
    }
    return a;
  }
}
