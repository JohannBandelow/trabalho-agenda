#include <stdio.h>
#include <stdlib.h>

#include "Evento.h"
#include "Horario.h"
#include "Lista.h"

/*
 * TODO:
 * 1 -> Johann
 * 2 -> Feito
 * 3 -> Erick
 * 4 ->
 * 5 ->
 * 6 ->
 *
 * */

void removerEvento() {
  int opcaoRemover;
  printf("Escolha a opção de remoção:\n");
  printf("1. Remover todos os eventos de uma data\n");
  printf("2. Remover um evento por data e hora inicial\n");
  printf("Escolha uma opção: ");
  scanf("%d", &opcaoRemover);

  if (opcaoRemover == 0) {
    Data data;
    printf("Informe a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
    // removerEventosPorData(&lista, data);
    printf("Eventos removidos com sucesso!\n");
  } else if (opcaoRemover == 1) {
    Data data;
    Horario hora;
    printf("Informe a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
    printf("Informe a hora de início (HH MM): ");
    scanf("%d %d", &hora.hora, &hora.minuto);
    // removerEventoPorDataHora(&lista, data, hora);
  } else {
    printf("Opção inválida.\n");
  }
}

void cadastrarNovoEvento() {
  Evento novoEvento;
  Data data;
  Horario hora_ini;
  Horario hora_fim;
  printf("Informe a data (DD MM AAAA): ");
  scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
  printf("Informe a hora de início (HH MM): ");
  scanf("%d %d", &hora_ini.hora, &hora_ini.minuto);
  printf("Informe a hora de fim (HH MM): ");
  scanf("%d %d", &hora_fim.hora, &hora_fim.minuto);

  novoEvento.data = &data;
  novoEvento.hora_final = &hora_fim;
  novoEvento.hora_inicial = &hora_ini;

  printf("Informe a descrição (até 50 caracteres): ");
  scanf(" %[^\n]", novoEvento.descricao);
  printf("Informe o local (até 50 caracteres): ");
  scanf(" %[^\n]", novoEvento.local);

  // inserirEvento(&lista, novoEvento);
}

int main(int argc, char const *argv[]) {
  Lista *lista = malloc(sizeof(Lista) + sizeof(Evento));
  int result = le_arquivo("entrada.txt", lista);

  mostra_lista(*lista, &mostrar_evento);

  if (result == 0) { // Arquivo nâo existe
    inicializa_lista(lista, sizeof(Evento));
    printf("Arquivo não encontrado");
  }

  int opcao;

  do {
    printf("\nMenu:\n");
    printf("1. Cadastrar novo evento\n");
    printf("2. Mostrar todos os eventos\n");
    printf("3. Mostrar eventos por data\n");
    printf("4. Mostrar eventos por descrição\n");
    printf("5. Remover evento\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      cadastrarNovoEvento();
      printf("Evento cadastrado com sucesso!\n");
      break;
    }
    case 2:
      mostra_lista(*lista, mostrar_evento);
      break;
    case 3: {
      Data data;
      printf("Informe a data (DD MM AAAA): ");
      scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
      // mostrarEventosPorData(lista, data);
      break;
    }
    case 4: {
      char descricao[50];
      printf("Informe a descrição: ");
      scanf(" %[^\n]", descricao);
      // mostrarEventosPorDescricao(lista, descricao);
      break;
    }
    case 5: {
      removerEvento();
      break;
    }
    case 6:
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }
  } while (opcao != 6);

  return 0;
}
