#ifndef DATA_H
#define DATA_H

#define ERRO_DIA_INVALIDO -1001;
#define ERRO_MES_INVALIDO -1002;
#define ERRO_ANO_INVALIDO -1003;

typedef struct {
  int dia;
  int mes;
  int ano;
} Data;

int inicializa_data(Data *data, int dia, int mes, int ano);
int compara_data(Data data, Data data_a_ser_comparada);
int mesmo_dia(Data data1, Data data2);
#endif
