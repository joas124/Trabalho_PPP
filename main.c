#include "./headers/principal.h"
#include "./headers/auxiliar.h"
#include "./headers/alunos.h"
#include <stdio.h>

int main() {
  lista l;
  if (!inicializa_lista(&l)) {
    printf("Erro ao inicializar a lista\n");
    return 0;
  }

  clean();

  while (menu(&l));

  return 0;
}
