#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

double uniform() {
    double u = rand() / ((double) RAND_MAX + 1);
    //LIMITA ENTRE 0 E 1
    u = 1.0 - u;
    return (u);
}

int main(){

    //E[x] = 1/L
    //e[x] = 5
    // l = 1/5
    //l = 0.2

    double l;
    printf("informe o tempo medio em segundos");
    scanf("%lF", &l);
    l = 1.0/l;

    //variaveis do calculo da media final
    double soma = 0.0;
    double qtd_numeros_gerados = 1000000;

    int semente = time(NULL);
    srand(semente);

    int i;
    for(i = 0;i < qtd_numeros_gerados; i++){
        double valor = (-1.0/l)*log(uniforme());
        getchar();
        soma += valor;
    }
    printf("media %lF\n", (soma/qtd_numeros_gerados));

    return 0;
}