#include "Horario.h"

int inicializa_hora(Horario *h, int hora, int minuto) {

    if (hora > 24 || hora < 0)
        return ERRO_HORA_INVALIDA;

    if (minuto > 60 || minuto < 0)
        return ERRO_MINUTO_INVALIDO;

    if (hora > 23 && minuto > 0)
        hora = 0; //Corrigido hora para formatar corretamente

    h->hora = hora;
    h->minuto = minuto;
}