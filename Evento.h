#ifndef EVENTO_H
#define EVENTO_H

#include "Data.h"
#include "Horario.h"

typedef struct {
  Data *data;
  Horario *hora_inicial;
  Horario *hora_final;
  char *descricao;
  char *local;
} Evento;

int novo_evento(Evento *evento, Data *data, Horario *hora_ini,
                Horario *hora_fim, char *descricao, char *local);

void mostrar_evento(void *evento);

int compara_data(Evento *evento);

#endif
