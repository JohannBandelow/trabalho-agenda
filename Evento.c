#include "Evento.h"
#include "Data.h"
#include "Horario.h"
#include "Lista.h"
#include "Utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int novo_evento(Evento *evento, Data *data, Horario *hora_ini,
                Horario *hora_fim, char *descricao, char *local) {
  evento->data = data;
  evento->hora_final = hora_fim;
  evento->hora_inicial = hora_ini;
  evento->descricao = descricao;
  evento->local = local;

  return 1;
}

int validar_conflitos_data(Lista *lista, Evento *evento) {
  if (!lista_vazia(*lista)) {
    Elemento *p = lista->cabeca;
    int cont = 0;
    while (p != NULL) {
      Evento *e = (Evento *)p->info;

      if (mesmo_dia(*evento->data, *e->data)) {
        if (conflita_hora(*e->hora_inicial, *e->hora_final,
                          *evento->hora_inicial, *evento->hora_final)) {
          print_line_separator();
          printf("Há um conflito de hora com o evento:\n");
          mostrar_evento(e);
          print_line_separator();
          return 0;
        }
      }
      p = p->proximo;
      cont++;
    }
  }

  return 1;
}

void criar_novo_evento(Lista *lista) {
  Evento *novoEvento = malloc(sizeof(Evento));
  Data *data = malloc(sizeof(Data));
  Horario *hora_ini = malloc(sizeof(Horario));
  Horario *hora_fim = malloc(sizeof(Horario));
  int erro;
  int valid = 0;

  print_line_separator();
  printf("Criando novo evento:\n");

  while (!valid) {
    int dia, mes, ano;
    printf("Informe a data (DD MM AAAA): ");
    scanf("%d %d %d", &dia, &mes, &ano);
    erro = inicializa_data(data, dia, mes, ano);
    if (erro != 0) {
      continue;
    }

    novoEvento->data = data;

    int hora, minuto;
    printf("Informe a hora de início (HH MM): ");
    scanf("%d %d", &hora, &minuto);
    erro = inicializa_hora(hora_ini, hora, minuto);
    if (erro != 0) {
      continue;
    }

    novoEvento->hora_inicial = hora_ini;

    printf("Informe a hora de fim (HH MM): ");
    scanf("%d %d", &hora, &minuto);
    erro = inicializa_hora(hora_fim, hora, minuto);
    if (erro != 0) {
      continue;
    }

    novoEvento->hora_final = hora_fim;

    char *local = malloc(sizeof(char) * 50);
    char *descricao = malloc(sizeof(char) * 50);
    printf("Informe a descrição (até 50 caracteres): ");
    scanf(" %[^\n]", descricao);
    printf("Informe o local (até 50 caracteres): ");
    scanf(" %[^\n]", local);

    novoEvento->local = local;
    if (strlen(local) > 50) {
      printf("Tamanho maior que 50 caracteres para o campo local!");
      continue;
    }

    novoEvento->descricao = descricao;
    if (strlen(descricao) > 50) {
      printf("Tamanho maior que 50 caracteres para o campo descricao!");
      continue;
    }

    valid = validar_conflitos_data(lista, novoEvento);

    if (!valid) {
      int opc;
      printf("Deseja cadastrar outro evento? 1-Sim 2-Não\n");
      scanf("%d", &opc);
      if (opc == 2) {
        printf("Cancelado registro de evento!");
        print_line_separator();
        return;
      }
    }
  }

  limpa_buffer();
  insere_ordem(lista, novoEvento, compara_data_ordem);
  printf("Evento cadastrado com sucesso!\n");
}

void mostrar_evento(void *evento) {
  Evento *castEvent = (Evento *)evento;

  printf("Descrição: ");
  printf("%s", castEvent->descricao);
  printf("\n");
  printf("Data: %d/%d/%d \n", castEvent->data->dia, castEvent->data->mes,
         castEvent->data->ano);
  printf("Hora Inicio: %d:%d \n", castEvent->hora_inicial->hora,
         castEvent->hora_inicial->minuto);
  printf("Hora Fim: %d:%d \n", castEvent->hora_final->hora,
         castEvent->hora_final->minuto);
  printf("Local: ");
  printf("%s", castEvent->local);
  printf("\n");
}

long long data_para_timestamp(Data data, Horario horario) {
  struct tm tm_data = {0};

  tm_data.tm_year = data.ano - 1900;
  tm_data.tm_mon = data.mes - 1;
  tm_data.tm_mday = data.dia;
  tm_data.tm_hour = horario.hora;
  tm_data.tm_min = horario.minuto;

  time_t unix_timestamp = mktime(&tm_data);
  return (long long)unix_timestamp * 1000;
}

int compara_data_ordem(void *daLista, void *aInserir) {
  Evento *eventoLista = (Evento *)daLista;
  Evento *eventoInserir = (Evento *)aInserir;

  long long timestampEventoDaLista =
      data_para_timestamp(*eventoLista->data, *eventoLista->hora_inicial);
  long long timestampEventoAInserir =
      data_para_timestamp(*eventoInserir->data, *eventoInserir->hora_inicial);

  if (timestampEventoDaLista > timestampEventoAInserir)
    return 1; // Insere depois de receber 1

  if (timestampEventoDaLista < timestampEventoAInserir)
    return -1;

  return 0; // as duas datas são iguais
}
