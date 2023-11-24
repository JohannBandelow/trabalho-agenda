#ifndef HORARIO_H
#define HORARIO_H

#define ERRO_HORA_INVALIDA -1001;
#define ERRO_MINUTO_INVALIDO -1002;

typedef struct {
  int hora;
  int minuto;
} Horario;

int inicializa_hora(Horario *h, int hora, int minuto);
int conflita_hora(Horario h1_ini, Horario h1_fim, Horario h2_ini,
                  Horario h2_fim);

#endif
