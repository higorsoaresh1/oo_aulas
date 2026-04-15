#include <stdio.h>

// Desenvolvido por Higor Soares Pereira e Johnny Alves Pereira.

// Declaração dos protótipos das funções.
void recebeNumeros(int numeros[], int registra_num[], int quant_num);                         // Função que recebe os números do mmc;
int divideAlguem(int numeros[], int quant_num, int primo);                                    // Função que faz a divisão no mmc;
int proximoPrimo(int numeros[], int quant_num, int primo);                                    // Função que gera os números primos;
int verificaMMC(int numeros[], int quant_num);                                                // Função que verifica se o mmc terminou;
int registra_divisores(int registra_primo[], int cont_divisao, int primo, int posicao_primo); // Função que registra os divisores que foram usados.

int main()
{
    int quant_num = 0;     // Variável que recebe a quantidade de números do mmc;
    int primo = 2;         // Variável primo que armazena o número primo divisor;
    int acabou_MMC = 0;    // Variável que condiciona o fim do mmc (0 ou 1);
    int posicao_primo = 0; // Variável parâmetro da posição do divisor no vetor.

    printf("Calcule o MMC!\n\n");
    printf("Quer fazer MMC de quantos números?");
    scanf("%d", &quant_num); // Usuário insere a quantidade de números que serão calculados;

    int numeros[quant_num];      // Vetor que armazena os números que serão calculados o mmc;
    int registra_num[quant_num]; // Vetor que armazena os números do mmc (Esses não serão modificados);

    recebeNumeros(numeros, registra_num, quant_num); // Chama a função que recebe os números que serão calculados;
    int i = 0;                                       // Incremento inicializado.
    int cont_divisao = 1;                            // Contador que registra a quantidade de divisões realizadas;
    int registra_primo[cont_divisao];                // Vetor que armazena os primos que dividiram algum número.

    while (acabou_MMC != 1) // Enquanto acabou_MMC retornar 0, o loop permanece.
    {
        if (divideAlguem(numeros, quant_num, primo) == 0) // Se o retorno da divideAlguem == 0, entra no if.
        {
            primo = proximoPrimo(numeros, quant_num, primo); // Variável primo recebe o retorno da proximoPrimo.
        }
        else // Se o retorno da divideAlguem == 1, entra no else.
        {
            // Com esse if, eu garanto que quando o loop for acontecendo inúmeras vezes, eu vou fazer esse "for" somente 1 vez,
            // que é p/ escrever a primeira linha do mmc, que contem os números iniciais.

            if ((cont_divisao - 1) == 0) // Se contador - 1 == 0, entra no if (Esse -1 é pra voltar essa variável p/ 0 inicialmente).
            {
                for (i = 0; i < quant_num; i++) // Enquanto i for menor que o tam. do vetor (Ex: vetor tem tam. 4, mas vai de 0 a 3 em indices), acontece o loop.
                {
                    printf("%d  ", registra_num[i]); // Escreve todos os indices o vetor registra_num, que contem os números iniciais.
                }
            }

            printf("|  %d\n", primo);                                                               // Escreve o primo que divide algum número, no formato do mmc.
            posicao_primo = registra_divisores(registra_primo, cont_divisao, primo, posicao_primo); // Chama a função que registra o primo que fez a divisão.

            for (i = 0; i < quant_num; i++)
            {
                printf("%d  ", numeros[i]); // Escreve o números do mmc já divididos.
            }
            cont_divisao++; // Incrementa +1 se alguma divisão foi feita.
        }

        acabou_MMC = verificaMMC(numeros, quant_num); // Chama a função que verifica se o mmc terminou.
    }

    int resultado = 1; // Variável resultado inicializada em 1.
    for (int i = 0; i < posicao_primo; i++)
    {
        resultado = resultado * registra_primo[i]; // Faz a multiplicação entre os divisores armazenados, 1 a 1.
    }
    printf("\n\nMMC = %d.", resultado); // Mostra o resultado do mmc.
    return 0;
}

void recebeNumeros(int numeros[], int registra_num[], int quant_num) // Função responsável por obter os números do mmc.
{
    printf("Digite os números:\n");

    for (int i = 0; i < quant_num; i++)
    {
        scanf("%d", &numeros[i]); // Usuário insere os números do mmc.

        registra_num[i] = numeros[i]; // Armazena em registra_num[] os mesmos números que numeros[] recebe.
    }
    printf("\n");
}

int divideAlguem(int numeros[], int quant_num, int primo) // Função responsável por fazer a divisão do mmc.
{
    int divide = 0; // Variável que indica se o número primo dividiu algum número (0 ou 1).

    for (int i = 0; i < quant_num; i++)
    {
        if (numeros[i] % primo == 0) // Se algum número dividido pelo primo da resto 0, entra no if.
        {
            numeros[i] = (numeros[i] / primo); // Faz a divisão do(s) número(s) que resulta resto 0;
            divide = 1;                        // Indica que dividiu alguem.
        }
    }

    return divide; // Retorna o indicador de divisão.
}

int proximoPrimo(int numeros[], int quant_num, int primo) // Função responsável por gerar o próximo número primo (2 em diante).
{
    int resultado_primo = (primo + 1); // Inicializa o resultado que recebe o valor do primo + 1.

    while (1) // Loop infinito.
    {
        int contador = 0; // Contador de divisões feitas inicializado;
        int divisor = 1;  // Divisor inicializado em 1.

        while (divisor <= resultado_primo) // Enquanto o divisor for menor ou igual ao resultado_primo, o loop acontece.
        {
            if ((resultado_primo % divisor) == 0) // Se a divisão do resultado_primo pelo primo der resto 0, entra no if.
            {
                contador++; // Incrementa 1 nas divisões foram feitas no número.
            }
            divisor++; // Incrementa 1 no divisor.
        }

        if (contador > 2) // Se o contador registrou mais que 2 divisões, o número número não é primo.
        {
            resultado_primo = (resultado_primo + 1); // Soma +1 em resultado_primo p/ verificar o próximo número.
        }
        else // Caso contrário, o número é primo (fez apenas 2 divisões).
        {
            primo = resultado_primo; // Primo recebe o valor de resultado_primo.
            break;
        }
    }
    return primo; // Retorna o valor do número primo.
}

int verificaMMC(int numeros[], int quant_num) // Função responsável por verificar se o mmc foi finalizado (Ex: restou só 1 1 1).
{
    int acabou_MMC = 1; // Inicializa acabou_MMC como 1 (finalizado);

    for (int i = 0; i < quant_num; i++)
    {
        if (numeros[i] != 1) // Se no vetor numeros[] algum número for diferente de 1, entra no if.
        {
            acabou_MMC = 0; // acabou_MMC recebe 0, que significa que ainda tem número a ser dividido.
        }
    }
    return acabou_MMC; // Retorna o valor que condiciona se o mmc acabou ou não (0 ou 1).
}

int registra_divisores(int registra_primo[], int cont_divisao, int primo, int posicao_primo) // Função responsável por armazenar os primos que dividiram algum número.
{                                                                                            // Chamada estratégicamente na hora que o primo dividiu alguém, logo o primo tem o valor certo.

    registra_primo[posicao_primo] = primo; // Vetor registra_primo recebe o valor do primo;
    posicao_primo++;                       // Incrementa 1 em posicao_primo, que aumenta o tamanho do vetor, e garante que o próx. número será armazenado no espaço seguinte.

    return posicao_primo;
}