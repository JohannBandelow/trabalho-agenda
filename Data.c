#include "Data.h"
#include <stdio.h>

int inicializa_data(Data *data, int dia, int mes, int ano) {
  if (dia > 31 || dia < 1) {
    printf("Dia inválido!\n");
    return ERRO_DIA_INVALIDO;
  }

  if (ano < 0) {
    printf("Ano inválido!\n");
    return ERRO_ANO_INVALIDO;
  }

  if (mes < 1 || mes > 12) {
    printf("Mes inválido!\n");
    return ERRO_MES_INVALIDO;
  }

  data->dia = dia;
  data->mes = mes;
  data->ano = ano;

  return 0;
}

int mesmo_dia(Data data1, Data data2) {
  return (data1.ano == data2.ano) && (data1.mes == data2.mes) &&
         (data1.dia == data2.dia);
}

int comparada_data(Data data, Data data_a_ser_comparada) {
  int retorno = 0;
  if (data.ano == data_a_ser_comparada.ano &&
      data.mes == data_a_ser_comparada.mes &&
      data.dia == data_a_ser_comparada.dia)
    return 1;
  return retorno;
}
