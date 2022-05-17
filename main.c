#include "./headers/principal.h"
#include "./headers/auxiliar.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  lista l;
  inicializa_lista(&l);

  clean();

  while (1) {
    menu(&l);
  }

return 0;
}
