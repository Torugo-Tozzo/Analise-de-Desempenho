#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define OCUPACAO(x) x
#define E_N(x) 
#define E_W(x) 
#define ERRO_LITTLE(x) 
#define VALORES_FINAIS(x) 

typedef struct
{
    double media_chegada;
    double media_servico;
    double tempo_simulacao;
} parametros;

typedef struct
{
    unsigned long int no_eventos;
    double tempo_anterior;
    double soma_areas;
} little;

void inicia_little(little *l)
{
    l->no_eventos = 0;
    l->tempo_anterior = 0.0;
    l->soma_areas = 0.0;
}

double uniforme()
{
    double u = rand() / ((double)RAND_MAX + 1);
    // limitando entre (0,1]
    u = 1.0 - u;
    return (u);
}

double min(double d1, double d2)
{
    if (d1 < d2)
    {
        return d1;
    }
    return d2;
}

double min_array(double *arr, int arr_size)
{
    int i;
    double min = arr[0];
    for (i = 1; i < 3; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    return min;
}

double max(double d1, double d2)
{
    if (d1 > d2)
    {
        return d1;
    }
    return d2;
}


int main()
{
    int semente = time(NULL);
    srand(semente);
     // le valores parametrizados
    parametros params;
    //le_parametros(&params);
    // variaveis de controle da simulacao
    double tempo_simulacao = 864000;
    double tempo_decorrido = 0.0;

    double intervalo_medio_chegada = 0.1;
    double tempo_medio_servico;
    double porc_ocupacao;
    double tempo_chegada = (-1.0 / (1.0 / intervalo_medio_chegada)) * log(uniforme());;
    double tempo_servico;

    double soma_tempo_servico = 0.0;

    unsigned long int fila = 0;
    unsigned long int max_fila = 0;
    double e_n_final = 0.0;
    double e_w_final = 0.0;
    double lambda;

    /**
    Little
    */
    little e_n;
    little e_w_chegada;
    little e_w_saida;

    inicia_little(&e_n);
    inicia_little(&e_w_chegada);
    inicia_little(&e_w_saida);
    /**
    Little -- fim
    */

    printf("Ocupação desejada (entre 0 e 1): ");
    scanf("%lF", &porc_ocupacao);
    tempo_medio_servico = intervalo_medio_chegada * porc_ocupacao;
    printf("\n%.2lF%%,0", porc_ocupacao * 100);

    tempo_chegada = (-1.0 / (1.0 / intervalo_medio_chegada)) * log(uniforme());
    double coleta_dados = 10.00;
    while (tempo_decorrido <= tempo_simulacao)
    {
        double eventos[3] = {tempo_chegada, tempo_servico, coleta_dados};
        tempo_decorrido = !fila ? min(tempo_chegada, coleta_dados) : min_array(eventos, 3);

        // coleta de dados
        if (tempo_decorrido == coleta_dados)
        {
            // printf("%lF,", coleta_dados * 100);
            e_n.soma_areas += (tempo_decorrido - e_n.tempo_anterior) * e_n.no_eventos;
            e_w_chegada.soma_areas += (tempo_decorrido - e_w_chegada.tempo_anterior) * e_w_chegada.no_eventos;
            e_w_saida.soma_areas += (tempo_decorrido - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;

            e_w_saida.tempo_anterior = tempo_decorrido;
            e_n.tempo_anterior = tempo_decorrido;
            e_w_chegada.tempo_anterior = tempo_decorrido;

            e_n_final = e_n.soma_areas / tempo_decorrido;
            e_w_final = (e_w_chegada.soma_areas - e_w_saida.soma_areas) / (double)e_w_chegada.no_eventos;
            lambda = e_w_chegada.no_eventos / tempo_decorrido;

            E_N(printf(",%lF", e_n_final););
            E_W(printf(",%lF", e_w_final););
            ERRO_LITTLE(printf(",%.20lF", fabs(e_n_final - lambda * e_w_final)););
            OCUPACAO(printf(",%lF", soma_tempo_servico / max(coleta_dados, tempo_servico)););
            coleta_dados += 10.00;
        }
        // chegada
        else if (tempo_decorrido == tempo_chegada)
        {
            // printf("Chegada em %lF.\n", tempo_decorrido);
            if (!fila)
            {
                tempo_servico = tempo_decorrido + (-1.0 / (1.0 / tempo_medio_servico)) * log(uniforme());
                soma_tempo_servico += tempo_servico - tempo_decorrido;
            }
            fila++;
            max_fila = fila > max_fila ? fila : max_fila;

            tempo_chegada = tempo_decorrido + (-1.0 / (1.0 / intervalo_medio_chegada)) * log(uniforme());

            // little
            e_n.soma_areas +=
                (tempo_decorrido - e_n.tempo_anterior) * e_n.no_eventos;
            e_n.tempo_anterior = tempo_decorrido;
            e_n.no_eventos++;

            e_w_chegada.soma_areas +=
                (tempo_decorrido - e_w_chegada.tempo_anterior) * e_w_chegada.no_eventos;
            e_w_chegada.tempo_anterior = tempo_decorrido;
            e_w_chegada.no_eventos++;
        }

        // saida
        else
        {
            fila--;
            if (fila)
            {
                tempo_servico = tempo_servico + (-1.0 / (1.0 / tempo_medio_servico)) * log(uniforme());
                soma_tempo_servico += tempo_servico - tempo_decorrido;
            }
            // little
            e_n.soma_areas +=
                (tempo_decorrido - e_n.tempo_anterior) * e_n.no_eventos;
            e_n.tempo_anterior = tempo_decorrido;
            e_n.no_eventos--;

            e_w_saida.soma_areas +=
                (tempo_decorrido - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;
            e_w_saida.tempo_anterior = tempo_decorrido;
            e_w_saida.no_eventos++;
        }
    }
    e_w_chegada.soma_areas += (tempo_decorrido - e_w_chegada.tempo_anterior) * e_w_chegada.no_eventos;
    e_w_saida.soma_areas += (tempo_decorrido - e_w_saida.tempo_anterior) * e_w_saida.no_eventos;

    e_n_final = e_n.soma_areas / tempo_decorrido;
    e_w_final = (e_w_chegada.soma_areas - e_w_saida.soma_areas) / e_w_chegada.no_eventos;
    lambda = e_w_chegada.no_eventos / tempo_decorrido;

    VALORES_FINAIS(
        printf("E[N]: %lF\n", e_n_final);
        printf("E[W]: %lF\n", e_w_final);
        printf("lambda: %lF\n\n", lambda);
        printf("Erro de Little: %.20lF\n\n", fabs(e_n_final - lambda * e_w_final));
        printf("Ocupacao: %lF.\n", soma_tempo_servico / max(tempo_decorrido, tempo_servico));
        printf("Max fila: %ld.\n", max_fila);)
    return 0;
}