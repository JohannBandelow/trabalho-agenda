#include "Data.h"

int inicializa_data(Data *data, int dia, int mes, int ano) {
  if (dia > 31 || dia < 1)
    return ERRO_DIA_INVALIDO;

  if (ano < 0)
    return ERRO_ANO_INVALIDO;

  if (mes < 1 || mes > 12)
    return ERRO_MES_INVALIDO;

  data->dia = dia;
  data->mes = mes;
  data->ano = ano;

  return 0;
}
