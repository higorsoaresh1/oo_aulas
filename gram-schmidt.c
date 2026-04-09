//[MÉTODO DE ORTONORMALIZAÇÃO DE GRAM-SCHMIDT]
//[DESENVOLVIDOR POR: GUILHERME PARREIRA E HIGOR SOARES]

#include <stdio.h>
#include <math.h>
#include <locale.h>

int normalizar(int n, int c, double w[c], double n_u[][c], int valido[]);
void wn_calc(int n, int l, int c, int matriz[l][c], double matriz_normal[l][c], double cria_w[c], int valido[]);

int main()
{
    setlocale(LC_ALL, "");
    int n = 0; /*Índice do vetor atual analisado.*/
    int i, j;  /*Contadores.*/
    int l, c;  /*l = quantidade de vetores | c = tamanho do vetor.*/

    /*Trecho para obtenção dos vetores*/
    printf("Informe a dimensao dos vetores: ");
    scanf("%d", &c);
    printf("Informe a quantidade de vetores para ortonormalizacao: ");
    scanf("%d", &l);

    int matriz[l][c]; /*Matriz que armazena todos os vetores escolhidos.*/

    printf("\n Preencha os vetores:\n");

    for (i = 0; i < l; i++)
    {
        printf("\n Vetor [%d]\n", i);
        for (j = 0; j < c; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }

    double matriz_normal[l][c]; /*Matriz que armazena todos os resultados da normalização.*/
    double w[c];                /*Vetor que armazena o W para ser normalizado.*/
    int valido[l];              /*Vetor auxiliar para verificação dependência linear*/

    for (i = 0; i < l; i++)
    {
        valido[i] = 0;
    }

    while (n < l)
    {
        wn_calc(n, l, c, matriz, matriz_normal, w, valido);
        normalizar(n, c, w, matriz_normal, valido);
        n++;
    }

    for (i = 0; i < l; i++)
    {
        if (!valido[i])
        { /*Mostra apenas os válidos.*/
            continue;
        }

        printf("\n[%d] = ", i);

        for (j = 0; j < c; j++)
        { /*Imprime os vetores normalizados (resultado).*/
            printf("\t%.2f", matriz_normal[i][j]);
        }
    }

    return 0;
}

int normalizar(int n, int c, double w[c], double n_u[][c], int valido[])
{
    int i, j;
    double soma_mdl = 0;
    double mdl = 0;

    for (i = 0; i < c; i++)
    { /*Soma o quadrado dos números dentro da raiz.*/
        soma_mdl += (w[i] * w[i]);
    }

    mdl = sqrt(soma_mdl); /*Faz a raiz da soma.*/

    if (mdl < 1e-10)
    { /*Etapa que verifica se é LD.*/
        printf("\nO Vetor [%d] LD - Foi descartado.\n", n);
        valido[n] = 0;
        return 0;
    }

    for (i = 0; i < c; i++)
    { /*Armazena na matriz de normalizados, o Wn dividido pelo seu módulo.*/
        n_u[n][i] = ((w[i]) / mdl);
    }

    valido[n] = 1;
    return 1;
}

void wn_calc(int n, int l, int c, int matriz[l][c], double matriz_normal[l][c], double cria_w[c], int valido[])
{
    int i, j;
    int k = n;
    double vet_subtracao[c];

    for (i = 0; i < c; i++)
    { /*Inicializa como 0 pra evitar lixo.*/
        vet_subtracao[i] = 0;
    }

    if (n == 0)
    { /*Para o primeiro vetor, dizemos que W0 = V0.*/
        for (i = 0; i < c; i++)
        {
            cria_w[i] = matriz[n][i];
        }
    }
    else
    {
        while (k > 0)
        {
            if (!valido[k - 1])
            { /*Ignora os vetores inválidos [LD].*/
                k--;
                continue;
            }

            double esc = 0;

            for (i = 0; i < c; i++)
            { /*Gera o escalar resulante do produto escalar entre vetores (V.U).*/
                esc += matriz[n][i] * matriz_normal[k - 1][i];
            }

            for (i = 0; i < c; i++)
            { /*Implicitamente coloca o "-" em evidência e soma todos os termos [(Vn.Un).Un]*/
                vet_subtracao[i] += esc * matriz_normal[k - 1][i];
            }

            k--;
        }

        for (i = 0; i < c; i++)
        { /*Armazena no vetor W, o vetor resultado da subtração de Vn por todos os termos seguintes.*/
            cria_w[i] = (matriz[n][i] - vet_subtracao[i]);
        }
    }
}