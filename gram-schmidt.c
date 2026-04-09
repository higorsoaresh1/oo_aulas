#include <stdio.h>
#include <math.h>

int n = 0;
void normalizar(int n, int c, double w[c], double n_u[][c]);
void wn_calc(int l, int c, int matriz[l][c], double matriz_normal[l][c], double cria_w[c]);

int main()
{
    int i, j;
    int l, c;

    printf("Informe a dimensão dos vetores: \n");
    scanf("%d", &l);
    printf("Informe a quantidade de vetores para ortonormalização: \n");
    scanf("%d", &c);

    int matriz[l][c];

    printf("\n\n Preencha os vetores:\n");

    for (i = 0; i < l; i++)
    {
        printf("\n Vetor [%d]\n", i);
        for (j = 0; j < c; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }

    double matriz_normal[l][c];
    double w[c];

    while (n < l)
    {
        wn_calc(l, c, matriz, matriz_normal, w);
        normalizar(n, c, w, matriz_normal);
        n++;
    }

    for (i = 0; i < l; i++)
    {
        printf("\n[%d]", i);
        for (j = 0; j < c; j++)
        {
            printf("\t%.2f", matriz_normal[i][j]);
        }
    }

    return 0;
}

void normalizar(int n, int c, double w[c], double n_u[][c])
{
    int i, j;
    double soma_mdl = 0;
    double mdl = 0;

    for (i = 0; i < c; i++)
    {
        soma_mdl += (w[i] * w[i]);
    }
    printf("\nSoma: %.2f\n", soma_mdl);

    mdl = sqrt(soma_mdl);

    for (i = 0; i < c; i++)
    {
        n_u[n][i] = ((w[i]) / mdl);
    }
    printf("\nN: ");
    for (i = 0; i < c; i++)
    {
        printf("\t%.2f", n_u[n][i]);
    }
    printf("\n");
}

void wn_calc(int l, int c, int matriz[l][c], double matriz_normal[l][c], double cria_w[c])
{
    int i, j;
    double vet_subtracao[c];
    int k = n;

    for (i = 0; i < c; i++)
    {
        vet_subtracao[i] = 0;
    }

    if (n == 0)
    {
        for (i = 0; i < c; i++)
        {
            cria_w[i] = matriz[n][i];
        }
        printf("\nW: ");
        for (i = 0; i < c; i++)
        {
            printf("\t%.2f", cria_w[i]);
        }
    }
    else
    {

        while (k > 0)
        {
            double esc = 0;

            for (i = 0; i < c; i++)
            {
                esc += (matriz[n][i] * matriz_normal[k - 1][i]);
            }

            for (i = 0; i < c; i++)
            {
                vet_subtracao[i] += (esc * matriz_normal[k - 1][i]);
            }

            k--;
        }

        for (i = 0; i < c; i++)
        {
            cria_w[i] = (matriz[n][i] - vet_subtracao[i]);
        }
    }

    for (i = 0; i < l; i++)
    {
        printf("\n[%d]", i);
        for (j = 0; j < c; j++)
        {
            printf("\t%.2f", matriz_normal[i][j]);
        }
    }
}
