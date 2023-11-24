#include <stdio.h>
#include <stdlib.h>

#include "Evento.h"
#include "Horario.h"
#include "Lista.h"

void remover_evento(Lista *lista) {
  int opcaoRemover;
  printf("Escolha a opcao de remocao:\n");
  printf("1. Remover todos os eventos de uma data\n");
  printf("2. Remover um evento por data e hora inicial\n");
  printf("Escolha uma opcao: ");
  scanf("%d", &opcaoRemover);

  if (opcaoRemover == 0) {
    Data data;
    printf("Informe a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
    remover_eventos_por_data(lista, data);
    printf("Eventos removidos com sucesso!\n");
  } else if (opcaoRemover == 1) {
    Data data;
    Horario hora;
    printf("Informe a data (DD MM AAAA): ");
    scanf("%d %d %d", &data.dia, &data.mes, &data.ano);
    printf("Informe a hora de inicio (HH MM): ");
    scanf("%d %d", &hora.hora, &hora.minuto);
    remover_eventos_por_data_hora(lista, data, hora);
  } else {
    printf("Opcao invalida.\n");
  }
}

int main(int argc, char const *argv[]) {
  Lista *lista = malloc(sizeof(Lista));
  int result = le_arquivo("entrada.txt", lista);

  if (result == 0) // Arquivo nâo existe
    inicializa_lista(lista, sizeof(Evento));

  int opcao;

  do {
    printf("\nMenu:\n");
    printf("1. Cadastrar novo evento\n");
    printf("2. Mostrar todos os eventos\n");
    printf("3. Mostrar eventos por data\n");
    printf("4. Mostrar eventos por descricao\n");
    printf("5. Remover evento\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1: {
      criar_novo_evento(lista);
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
      mostrar_todos_os_eventos_da_data(*lista, data);
      break;
    }
    case 4: {
      char descricao[50];
      printf("Informe a descrição: ");
      scanf(" %[^\n]", descricao);
      mostrar_todos_os_eventos_por_descricao(*lista, descricao);
      break;
    }
    case 5: {
      remover_evento(lista);
      break;
    }
    case 6:
      break;
    default:
      printf("Opção inválida.\n");
      break;
    }
  } while (opcao != 6);

  // Se o professor leu até aqui, saiba que esse código foi escrito com a ajuda
  // de algumas cervejas

  return 0;
}
