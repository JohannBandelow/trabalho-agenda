#include "Evento.h"
#include "Data.h"
#include "Horario.h"
#include <stdio.h>
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

int compara_data(void *daLista, void *aInserir) {
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
