#include "Horario.h"
#include <stdio.h>

int inicializa_hora(Horario *h, int hora, int minuto) {

  if (hora > 24 || hora < 0) {
    printf("Hora inválida!\n");
    return ERRO_HORA_INVALIDA;
  }

  if (minuto > 60 || minuto < 0) {
    printf("Minuto inválido!\n");
    return ERRO_MINUTO_INVALIDO;
  }

  if (hora > 23 && minuto > 0)
    hora = 0; // Corrigido hora para formatar corretamente

  h->hora = hora;
  h->minuto = minuto;

  return 0;
}

int conflita_hora(Horario h1_ini, Horario h1_fim, Horario h2_ini,
                  Horario h2_fim) {

  int min_h1_ini = (h1_ini.hora * 60) + h1_ini.minuto;
  int min_h1_fim = (h1_fim.hora * 60) + h1_fim.minuto;
  int min_h2_ini = (h2_ini.hora * 60) + h2_ini.minuto;
  int min_h2_fim = (h2_fim.hora * 60) + h2_fim.minuto;

  if (min_h2_ini < min_h1_ini &&
      min_h2_fim <
          min_h1_ini) { // A hora do evento é anterior ao evento comparado
    return 0;
  }

  if (min_h2_ini > min_h1_fim) { // A hora está depois do evento comparado
    return 0;
  }

  return 1;
}
