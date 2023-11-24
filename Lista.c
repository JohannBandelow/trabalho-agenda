#include "Lista.h"
#include "Data.h"
#include "Evento.h"
#include "Horario.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Privado------------------------

Elemento *aloca_elemento(void *info, int tam) {
  Elemento *p = malloc(sizeof(Elemento));
  if (p == NULL)
    return NULL; // Erro, falta de mem�ria!
  p->info = malloc(tam);
  if (p->info == NULL) {
    free(p);
    return NULL; // Erro, falta de mem�ria!
  }
  memcpy(p->info, info, tam);
  return p; // Sucesso!
}

//-------------------------------

int le_arquivo(char *nome_arquivo, Lista *p) {
  FILE *f = fopen(nome_arquivo, "rt");
  if (f == NULL)
    return 0; // Retorna 0 caso n�o abra o arquivo

  int quantidadeEventos = 0;
  fscanf(f, "%d", &quantidadeEventos);

  inicializa_lista(p, sizeof(Evento));
  int i;
  // Lê os eventos do arquivo
  for (i = 0; i < quantidadeEventos; i++) {
    int dia, mes, ano, hora_ini, min_ini, hora_fim, min_fim;
    char *descricao = malloc(sizeof(char) * 50);
    char *local = malloc(sizeof(char) * 50);

    fscanf(f, "%d/%d/%d %d:%d %d:%d %49[^,], %49[^\n]", &dia, &mes, &ano,
           &hora_ini, &min_ini, &hora_fim, &min_fim, descricao, local);

    Data *data = malloc(sizeof(Data));
    inicializa_data(data, dia, mes, ano);

    Horario *horario_ini = malloc(sizeof(Horario));
    inicializa_hora(horario_ini, hora_ini, min_ini);

    Horario *horario_fim = malloc(sizeof(Horario));
    inicializa_hora(horario_fim, hora_fim, min_fim);

    Evento evento;

    novo_evento(&evento, data, horario_ini, horario_fim, descricao, local);

    insere_fim(p, &evento);
  }

  fclose(f);

  return 1;
}

int salva_no_arquivo(char *nome_arquivo, Lista *lista) {
  FILE *arquivo = fopen(nome_arquivo, "w");

  if (arquivo == NULL)
    return -1;

  Elemento *atual = lista->cabeca;

  fprintf(arquivo, "%d\n", lista->qtd);

  while (atual != NULL) {
    Evento *evento = (Evento *)atual->info;

    fprintf(arquivo, "%d/%d/%d %d:%d %d:%d %s, %s\n", evento->data->dia,
            evento->data->mes, evento->data->ano, evento->hora_inicial->hora,
            evento->hora_inicial->minuto, evento->hora_final->hora,
            evento->hora_final->minuto, evento->descricao, evento->local);

    atual = atual->proximo;
  }

  fclose(arquivo);

  return 0;
}

void mostrar_todos_os_eventos_da_data(Lista l, Data dia) {
  int i = 0;
  Elemento *aux = l.cabeca;
  while (aux != NULL) {
    Evento *evento = aux->info;
    if (compara_data(*evento->data, dia)) {
      i++;
      printf("\nEvento %d\n", i);
      mostrar_evento(evento);
      printf("\n-------------------------------");
    }
    aux = aux->proximo;
  }
  if (i == 0)
    printf("Nao ha eventos nesta data!");
}

int remover_eventos_por_data(Lista *lista, Data data) {
  int i = 0;
  Elemento *aux = lista->cabeca;
  Evento *evento = malloc(sizeof(Evento));
  Elemento *prox;

  while (aux != NULL) {
    evento = (Evento *)aux->info;
    prox = aux->proximo;

    if (compara_data(*evento->data, data)) {
      void *removido = malloc(sizeof(Evento));
      remove_pos(lista, removido, i);
      aux = prox;
    } else {
      // Se o elemento não for removido, apenas avança para o próximo
      i++;
      aux = aux->proximo;
    }
  }

  if (i == 0)
    printf("Nao ha eventos nesta data!");

  return 0;
}

int remover_eventos_por_data_hora(Lista *lista, Data data, Horario horario) {
  int i = 0;
  Elemento *aux = lista->cabeca;
  Evento *e = malloc(sizeof(Evento));
  Elemento *prox;

  while (aux != NULL) {
    e = (Evento *)aux->info;
    prox = aux->proximo;

    if (compara_data(*e->data, data) &&
        hora_dentro_de_escopo(horario, *e->hora_inicial, *e->hora_final)) {

      void *removido = malloc(sizeof(Evento));
      remove_pos(lista, removido, i);

      return 0; // Só vai apagar um tem mesmo
    } else {
      // Se o elemento não for removido, apenas avança para o próximo
      i++;
      aux = aux->proximo;
    }
  }

  if (i == 0)
    printf("Nao ha eventos nesta data!");

  return 0;
}

void inicializa_lista(Lista *p, int t) {
  p->tamInfo = t;
  p->cabeca = NULL;
  p->qtd = 0;
}

int lista_vazia(Lista l) { return l.cabeca == NULL; }

int insere_inicio(Lista *p, void *info) {
  Elemento *novo = aloca_elemento(info, p->tamInfo);
  if (novo == NULL)
    return 0; // Erro, falta de mem�ria!

  novo->proximo = p->cabeca;
  p->cabeca = novo;
  p->qtd++;
  return 1; // Sucesso!
}

int remove_inicio(Lista *p, void *info) {
  if (lista_vazia(*p))
    return ERRO_LISTA_VAZIA;

  Elemento *aux = p->cabeca;
  memcpy(info, aux->info, p->tamInfo);
  p->cabeca = aux->proximo;
  free(aux->info);
  free(aux);
  p->qtd--;
  return 1; // Sucesso!
}

int insere_fim(Lista *p, void *info) {
  if (lista_vazia(*p))
    return insere_inicio(p, info);

  Elemento *aux = p->cabeca;
  while (aux->proximo != NULL)
    aux = aux->proximo;

  Elemento *novo = aloca_elemento(info, p->tamInfo);
  if (novo == NULL)
    return 0; // Erro, falta de mem�ria!

  aux->proximo = novo;
  novo->proximo = NULL;
  p->qtd++;
  return 1; // Sucesso!
}

int remove_fim(Lista *p, void *info) {
  if (lista_vazia(*p))
    return ERRO_LISTA_VAZIA;
  if (p->qtd == 1)
    return remove_inicio(p, info);
  Elemento *aux = p->cabeca;
  while (aux->proximo->proximo != NULL)
    aux = aux->proximo;
  Elemento *ultimo = aux->proximo;
  memcpy(info, ultimo->info, p->tamInfo);
  free(ultimo->info);
  free(ultimo);
  aux->proximo = NULL;
  p->qtd--;
  return 1; // Sucesso!
}

int insere_pos(Lista *p, void *info, int pos) {
  if (pos < 0 || pos > p->qtd)
    return ERRO_POS_INVALIDA;

  if (pos == 0)
    return insere_inicio(p, info);

  Elemento *aux = p->cabeca;
  int cont;
  for (cont = 0; cont < pos - 1; cont++)
    aux = aux->proximo; // Vai at� elemento em pos-1

  Elemento *novo = aloca_elemento(info, p->tamInfo);
  if (novo == NULL)
    return 0; // Erro, falta de mem�ria!

  novo->proximo = aux->proximo;
  aux->proximo = novo;
  p->qtd++;
  return 1; // Sucesso!
}

int remove_pos(Lista *p, void *info, int pos) {
  if (lista_vazia(*p))
    return ERRO_LISTA_VAZIA;

  if (pos < 0 || pos >= p->qtd)
    return ERRO_POS_INVALIDA;

  if (pos == 0)
    return remove_inicio(p, info);

  Elemento *aux = p->cabeca;
  int cont;
  for (cont = 0; cont < pos - 1; cont++)
    aux = aux->proximo; // Vai at� pos-1

  Elemento *x = aux->proximo;
  aux->proximo = x->proximo;
  memcpy(info, x->info, p->tamInfo);
  free(x->info);
  free(x);
  p->qtd--;
  return 1; // Sucesso!
}

int le_valor(Lista l, void *info, int pos) {
  if (lista_vazia(l))
    return ERRO_LISTA_VAZIA;

  if (pos < 0 || pos >= l.qtd)
    return ERRO_POS_INVALIDA;

  Elemento *aux = l.cabeca;
  int cont;
  for (cont = 0; cont < pos; cont++)
    aux = aux->proximo; // Vai at� elemento em pos

  memcpy(info, aux->info, l.tamInfo);
  return 1; // Sucesso!
}

int modifica_valor(Lista l, void *info, int pos) {
  if (lista_vazia(l))
    return ERRO_LISTA_VAZIA;

  if (pos < 0 || pos >= l.qtd)
    return ERRO_POS_INVALIDA;

  Elemento *aux = l.cabeca;
  int cont;
  for (cont = 0; cont < pos; cont++)
    aux = aux->proximo; // Vai at� elemento em pos

  memcpy(aux->info, info, l.tamInfo);
  return 1; // Sucesso!
}

void mostra_lista(Lista l, void (*mostra)(void *)) {

  if (lista_vazia(l)) {
    printf("Lista vazia!\n");
  } else {
    printf("Dados da lista (%d elementos):\n", l.qtd);
    Elemento *p = l.cabeca;
    int cont = 0; // cont � o �ndice do elemento dentro da lista.
    while (p != NULL) {
      printf("[%d] ", cont);
      mostra(p->info); // Invoca��o por callback
      p = p->proximo;
      cont++;
    }
  }
  printf("--------------------------------\n");
}

int conta_elementos(Lista l) {
  int cont = 0;
  Elemento *p = l.cabeca;
  while (p != NULL) {
    cont++;
    p = p->proximo;
  }
  return cont;
}

void limpa_lista(Lista *l) {
  Elemento *p = l->cabeca;
  while (p != NULL) {
    Elemento *prox = p->proximo;
    free(p->info);
    free(p);
    p = prox;
  }
  l->cabeca = NULL;
  l->qtd = 0;
}

int insere_ordem(Lista *p, void *info, int (*compara)(void *, void *)) {
  Elemento *aux = p->cabeca;
  int cont = 0;
  while (aux != NULL && compara(info, aux->info) > 0) {
    aux = aux->proximo;
    cont++;
  }
  return insere_pos(p, info, cont);
}
