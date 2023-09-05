#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int dado;

  // Inicializamos a função rand com um valor aleatório.
  srand(time(NULL));

  // Geramos um número aleatório entre 0 e 5.
  dado = rand() % 6;

  // Imprimimos o resultado.
  printf("O número sorteado foi: %d\n", dado + 1);

  return 0;
}
