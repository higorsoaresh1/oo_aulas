#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    int cod_identificador;
    char descricao[50];
    float valorVenda;
    int qtdAtual;
    int situacao;
} Produto;

typedef struct
{
    int cod_compra;
    Data data;
    float valorUnit;
    int quantidade;
    float valorTotal;
} Compra;

typedef struct
{
    int cod_venda;
    Data data;
    float valorUnitVenda;
    int quantidade;
    float valorTotal;

} Venda;

void menu(Produto **prod, int *posicao_prod, Compra **buy, int *posicao_buy, Venda **sell, int *posicao_sell, /*Quebra de linha*/
          int *acoes, Data *dt_inicial, Data *dt_final, int *mem_alocada_prod, int *mem_alocada_buy, int *mem_alocada_sell, Data *d);

void cadastrar_produto(Produto *prod, int *posicao_prod);
void cadastrar_varios(Produto **prod, int *posicao_prod, int *mem_alocada_prod);
void imprimir_relacao(Produto *prod, int *posicao_prod);
void compra(Compra *buy, int *posicao_buy, Produto *prod, int *posicao_prod, Data *d);
void exibir_compras(Data *dt_inicial, Data *dt_final, Compra *buy, int *posicao_buy, Produto *prod, int *posicao_prod, int *acoes);
void venda(Venda *sell, int *posicao_sell, Produto *prod, int *posicao_prod, Data *d);
void exibir_vendas(Data *dt_inicial, Data *dt_final, Venda *sell, int *posicao_sell, Produto *prod, int *posicao_prod, int *acoes);
void historico_prod(Produto *prod, int *posicao_prod, Compra *buy, int *posicao_buy, Venda *sell, int *posicao_sell, int *acoes);
void produtos_esgotados(Produto *prod, int *posicao_prod);
void sobre();
void recebedata(Data *dt);
int comparaData(Data a, Data b);
void imprime_compra(Produto *p, Compra *c);
void imprime_venda(Produto *p, Venda *v);

int main(void)
{
    // Configura a localidade para português do Brasil
    setlocale(LC_ALL, "portuguese_Brazil");

    Produto *prod;
    int posicao_prod = 0;
    int mem_alocada_prod = 2;
    Compra *buy;
    int posicao_buy = 0;
    int mem_alocada_buy = 2;
    Venda *sell;
    int posicao_sell = 0;
    int mem_alocada_sell = 2;
    int acoes = 0;
    Data dt_inicial, dt_final, d;

    prod = calloc(2, sizeof(Produto));

    !prod ? "Erro de alocação! \"prod\"", exit(1) : NULL;

    buy = calloc(2, sizeof(Compra));

    !buy ? "Erro de alocação! \"buy\"", exit(1) : NULL;

    sell = calloc(2, sizeof(Venda));

    !sell ? "Erro de alocação! \"sell\"", exit(1) : NULL;

    menu(&prod, &posicao_prod, &buy, &posicao_buy, &sell, &posicao_sell, &acoes, &dt_inicial, /*Quebra de linha*/
         &dt_final, &mem_alocada_prod, &mem_alocada_buy, &mem_alocada_sell, &d);

    free(prod);
    free(buy);
    free(sell);
    return 0;
}

void menu(Produto **prod, int *posicao_prod, Compra **buy, int *posicao_buy, Venda **sell, int *posicao_sell, /*Quebra de linha*/
          int *acoes, Data *dt_inicial, Data *dt_final, int *mem_alocada_prod, int *mem_alocada_buy, int *mem_alocada_sell, Data *d)
{
    int opcao_menu;    // Recebe a opção do menu;
    int sair_menu = 0; // Controle do loop do menu;

    while (sair_menu == 0)
    { // Interface com o usuário do sistema.
        printf("|-------------- SISTEMA DE SUPERMERCADO --------------|");
        printf("\n| 0 - SAIR DO MENU;");
        printf("\n| 1 - CADASTRAR PRODUTO;");
        printf("\n| 2 - CADASTRAR PRODUTOS EM SEQUENCIA;");
        printf("\n| 3 - RELAÇÃO DE PRODUTOS;");
        printf("\n| 4 - COMPRA DE PRODUTOS;");
        printf("\n| 5 - EXIBIR COMPRAS EM PERÍODO;");
        printf("\n| 6 - VENDA DE PRODUTOS;");
        printf("\n| 7 - EXIBIR VENDAS EM PERÍODO;");
        printf("\n| 8 - HISTÓRICO DE UM PRODUTO;");
        printf("\n| 9 - EXIBIR PRODUTOS ESGOTADOS;");
        printf("\n| 10 - SOBRE.");
        printf("\n|-----------------------------------------------------|\n");

        while (1)
        {
            if (scanf("%d", &opcao_menu) != 1)
            {
                printf("Opção inválida, tente novamente!");
                while (getchar() != '\n')
                    ;
                continue;
            }

            if (opcao_menu < 0 || opcao_menu > 10)
            {
                printf("Opção inválida, tente novamente!");
                continue;
            }
            else
                break;
        }

        switch (opcao_menu)
        {
        case 0:
            system("cls");
            sair_menu = 1;

            (*acoes)++;
            break;
        case 1:
            system("cls");

            if (*mem_alocada_prod == *posicao_prod)
            {
                (*mem_alocada_prod) += 2;

                Produto *temp = realloc(*prod, (*mem_alocada_prod) * sizeof(Produto));

                !temp ? "Erro de realocação para Produto!", exit(1) : NULL;

                *prod = temp;
            }

            cadastrar_produto(*prod, posicao_prod);

            (*acoes)++;
            break;
        case 2:
            system("cls");
            cadastrar_varios(prod, posicao_prod, mem_alocada_prod);

            (*acoes)++;
            break;
        case 3:
            system("cls");
            imprimir_relacao(*prod, posicao_prod);

            (*acoes)++;
            break;
        case 4:
            system("cls");

            if (*mem_alocada_buy == *posicao_buy)
            {
                (*mem_alocada_buy) += 2;

                Compra *temp = realloc(*buy, (*mem_alocada_buy) * sizeof(Compra));

                !temp ? "Erro de realocação para Compra!", exit(1) : NULL;

                *buy = temp;
            }

            compra(*buy, posicao_buy, *prod, posicao_prod, d);

            (*acoes)++;
            break;
        case 5:
            system("cls");
            exibir_compras(dt_inicial, dt_final, *buy, posicao_buy, *prod, posicao_prod, acoes);

            (*acoes)++;
            break;
        case 6:
            system("cls");

            if (*mem_alocada_sell == *posicao_sell)
            {
                (*mem_alocada_sell) += 2;

                Venda *temp = realloc(*sell, (*mem_alocada_sell) * sizeof(Venda));

                !temp ? "Erro de realocação para Venda!", exit(1) : NULL;

                *sell = temp;
            }

            venda(*sell, posicao_sell, *prod, posicao_prod, d);

            (*acoes)++;
            break;
        case 7:
            system("cls");
            exibir_vendas(dt_inicial, dt_final, *sell, posicao_sell, *prod, posicao_prod, acoes);

            (*acoes)++;
            break;
        case 8:
            system("cls");
            historico_prod(*prod, posicao_prod, *buy, posicao_buy, *sell, posicao_sell, acoes);

            (*acoes)++;
            break;
        case 9:
            system("cls");
            produtos_esgotados(*prod, posicao_prod);

            (*acoes)++;
            break;
        case 10:
            system("cls");
            sobre();

            (*acoes)++;
            break;
        default:
            system("cls");
            printf("Opção inválida, tente novamente!");
            break;
        }
    }

    printf("Foram realizadas \"%d\" ações pelo usuário", *acoes);
}

void cadastrar_produto(Produto *prod, int *posicao_prod)
{
    int i;

    printf("| Cadastre o Produto |");
    printf("\n| Código: ");

    while (1)
    {
        int cod_repedito = 0;

        if (scanf("%d", &(prod + *posicao_prod)->cod_identificador) != 1)
        {
            printf("Opção inválida, tente novamente!");
            while (getchar() != '\n')
                ;
            continue;
        }

        for (i = 0; i < *posicao_prod; i++)
        {
            if ((prod + *posicao_prod)->cod_identificador == (prod + i)->cod_identificador)
            {
                cod_repedito = 1;
                break;
            }
        }

        if (cod_repedito)
        {
            printf("\nCódigo repetido, tente novamente!");
            printf("\n\n| Código: ");
            continue;
        }
        break;
    }

    printf("| Descrição : ");
    scanf(" %49[^\n]", (prod + *posicao_prod)->descricao);
    while (getchar() != '\n')
        ;
    printf("\n");

    (prod + *posicao_prod)->valorVenda = 0;
    (prod + *posicao_prod)->qtdAtual = 0;
    (prod + *posicao_prod)->situacao = 0;

    (*posicao_prod)++;
}

void cadastrar_varios(Produto **prod, int *posicao_prod, int *mem_alocada_prod)
{
    int opcao;

    printf("| Cadastro em sequência dos produtos |\n");
    do
    {
        if (*mem_alocada_prod == *posicao_prod)
        {
            (*mem_alocada_prod) += 2;
            Produto *temp = realloc(*prod, (*mem_alocada_prod) * sizeof(Produto));

            !temp ? "Erro de realocação para Produto!", exit(1) : NULL;

            *prod = temp;
        }

        cadastrar_produto(*prod, posicao_prod);

        printf("Digite \"1\" para continuar ou \"0\" para encerrar: ");

        while (1)
        {
            if (scanf("%d", &opcao) != 1)
            {
                printf("Opção inválida, tente novamente!");
                while (getchar() != '\n')
                    ;
                continue;
            }
            if (opcao < 0 || opcao > 1)
            {
                printf("Opção inválida, tente novamente!");
                continue;
            }
            break;
        }
        system("cls");
    } while (opcao != 0);
}

void imprimir_relacao(Produto *prod, int *posicao_prod)
{
    int i;

    printf("| RELAÇÃO DE PRODUTOS CADASTRADOS |");
    for (i = 0; i < *posicao_prod; i++)
    {
        printf("\n| Código: %d", (prod + i)->cod_identificador);
        printf("\n| Descrição: %s\n", (prod + i)->descricao);

        if ((prod + i)->situacao == 1)
        {
            printf("| Quantidade em estoque: %d", (prod + i)->qtdAtual);
            printf("\n| Valor Unitário de venda: %.2f\n", (prod + i)->valorVenda);
        }
        else if ((prod + i)->situacao == 2)
        {
            printf("| Produto esgotado!\n");
        }
        else
            printf("| Produto inativo!\n");
    }

    printf("\n");
}

void compra(Compra *buy, int *posicao_buy, Produto *prod, int *posicao_prod, Data *d)
{
    int i;
    int verifica_cod = 0;
    int atualizar = 0;
    float taxa;

    printf("| Compra de Produto |");

    do
    {
        printf("\n| Informe o Código do produto: ");
        scanf("%d", &(buy + *posicao_buy)->cod_compra);
        while (getchar() != '\n')
            ;

        for (i = 0; i < *posicao_prod; i++)
        {
            if ((prod + i)->cod_identificador == (buy + *posicao_buy)->cod_compra)
            {
                printf("| Descrição: %s\n", (prod + i)->descricao);
                printf("| Data da compra: \n");

                recebedata(d);

                (buy + *posicao_buy)->data.dia = d->dia;
                (buy + *posicao_buy)->data.mes = d->mes;
                (buy + *posicao_buy)->data.ano = d->ano;

                printf("| Valor unitário: R$ ");
                scanf("%f", &(buy + *posicao_buy)->valorUnit);
                printf("| Quantidade: ");

                while (1)
                {
                    if (scanf("%d", &(buy + *posicao_buy)->quantidade) != 1)
                    {
                        printf("\nOpção inválida, tente novamente!");
                        while (getchar() != '\n')
                            ;
                        continue;
                    }
                    else if ((buy + *posicao_buy)->quantidade <= 0)
                    {
                        printf("\nCompra cancelada!\n\n");
                        return;
                    }
                    else
                    {
                        break;
                    }
                }

                if ((prod + i)->situacao == 0)
                {
                    printf("\nQual taxa quer aplicar em cima desse produto (%)? ");
                    scanf("%f", &taxa);

                    (prod + i)->valorVenda = ((buy + *posicao_buy)->valorUnit + (taxa / 100 * (buy + i)->valorUnit));

                    printf("\n| Preço unitário final: R$ %.2f", (prod + i)->valorVenda);

                    printf("\n");
                }
                else
                {
                    printf("\nAtualizar o valor de venda? (1)-Sim ou (0)-Não.");
                    while (1)
                    {
                        if (scanf("%d", &atualizar) != 1)
                        {
                            printf("Opção inválida, tente novamente!");
                            while (getchar() != '\n')
                                ;
                            continue;
                        }
                        else if (atualizar < 0 || atualizar > 1)
                        {
                            printf("Opção inválida, tente novamente!");
                            continue;
                        }
                        else if (atualizar == 0)
                        {
                            atualizar = 0;
                            system("cls");
                            break;
                        }
                        else
                        {
                            printf("\nQual taxa quer aplicar em cima desse produto? ");
                            scanf("%f", &taxa);

                            (prod + i)->valorVenda = ((buy + *posicao_buy)->valorUnit + (taxa / 100 * (buy + i)->valorUnit));

                            printf("\n| Preço unitário final: R$ %.2f", (prod + i)->valorVenda);

                            printf("\n");
                            break;
                        }
                    }
                }

                (buy + *posicao_buy)->valorTotal = (buy + *posicao_buy)->quantidade * (buy + *posicao_buy)->valorUnit;
                printf("| Preço total da compra: R$ %.2f\n\n", (buy + *posicao_buy)->valorTotal);

                (prod + i)->qtdAtual += (buy + *posicao_buy)->quantidade;
                (prod + i)->situacao = 1;
                verifica_cod = 1;
                break;
            }
        }
        !verifica_cod ? "\nCódigo não encontrado no sistema, tente novamente!\n" : NULL;

    } while (!verifica_cod);

    (*posicao_buy)++;
}

void exibir_compras(Data *dt_inicial, Data *dt_final, Compra *buy, int *posicao_buy, Produto *prod, int *posicao_prod, int *acoes)
{
    int i, k;
    int opcao_menu;
    int sair_menu = 0;

    do
    {
        printf("|---- PESQUISA DE COMPRAS REALIZADAS POR DATA ----|");
        printf("\n| 0 - RETORNAR AO MENU ANTERIOR;");
        printf("\n| 1 - TODAS AS COMPRAS REALIZADAS;");
        printf("\n| 2 - TODAS A PARTIR DA DATA;");
        printf("\n| 3 - TODAS ANTES DA DATA;");
        printf("\n| 4 - ENTRE AS DATAS.");
        printf("\n|-------------------------------------------------|\n");

        while (1)
        {
            if (scanf("%d", &opcao_menu) != 1)
            {
                printf("Opção inválida, tente novamente!");
                while (getchar() != '\n')
                    ;
                continue;
            }

            if (opcao_menu < 0 || opcao_menu > 4)
            {
                printf("Opção inválida, tente novamente!");
                continue;
            }
            else
                break;
        }

        switch (opcao_menu)
        {
        case 0:
            system("cls");
            sair_menu++;

            (*acoes)++;
            break;
        case 1:
            system("cls");

            printf("| TODO O PERÍODO |\n\n");
            for (i = 0; i < *posicao_buy; i++)
            {
                for (k = 0; k < *posicao_prod; k++)
                {
                    (prod + k)->cod_identificador == (buy + i)->cod_compra ? imprime_compra((prod + k), (buy + i)) : NULL;
                }
                printf("\n");
            }

            (*acoes)++;
            break;
        case 2:
            system("cls");

            printf("| Informe a data inicial:\n");
            recebedata(dt_inicial);

            system("cls");
            printf("| TODAS A PARTIR DA DATA: %d/%d/%d |\n\n", dt_inicial->dia, dt_inicial->mes, dt_inicial->ano);

            for (i = 0; i < *posicao_buy; i++)
            { // Data registrada > Data pesquisada
                if (!comparaData((buy + i)->data, *dt_inicial))
                {
                    for (k = 0; k < *posicao_prod; k++)
                    {
                        (prod + k)->cod_identificador == (buy + i)->cod_compra ? imprime_compra((prod + k), (buy + i)) : NULL;
                    }
                }
                printf("\n");
            }

            (*acoes)++;
            break;
        case 3:
            system("cls");

            printf("| Informe a data final:\n");
            recebedata(dt_final);

            system("cls");
            printf("| TODAS ATÉ A DATA: %d/%d/%d |\n\n", dt_final->dia, dt_final->mes, dt_final->ano);
            for (i = 0; i < *posicao_buy; i++)
            { // Data registrada < Data pesquisada.
                if (comparaData((buy + i)->data, *dt_final))
                {
                    for (k = 0; k < *posicao_prod; k++)
                    {
                        (prod + k)->cod_identificador == (buy + i)->cod_compra ? imprime_compra((prod + k), (buy + i)) : NULL;
                    }
                }
                printf("\n");
            }

            (*acoes)++;
            break;
        case 4:
            system("cls");

            printf("| Informe a data inicial:\n");
            recebedata(dt_inicial);

            printf("\n| Informe a data final:\n");
            recebedata(dt_final);

            system("cls");
            printf("| PERÍODO DE %d/%d/%d ATÉ %d/%d/%d|\n\n", dt_inicial->dia, dt_inicial->mes, dt_inicial->ano, dt_final->dia, dt_final->mes, dt_final->ano);

            for (i = 0; i < *posicao_buy; i++)
            {
                if (!comparaData((buy + i)->data, *dt_inicial))
                {
                    if (comparaData((buy + i)->data, *dt_final))
                    {
                        for (k = 0; k < *posicao_prod; k++)
                        {
                            (prod + k)->cod_identificador == (buy + i)->cod_compra ? imprime_compra((prod + k), (buy + i)) : NULL;
                        }
                    }
                }
                printf("\n");
            }

            (*acoes)++;
            break;
        default:
            system("cls");
            printf("Opção inválida, tente novamente!");
            break;
        }
    } while (!sair_menu);
}

void venda(Venda *sell, int *posicao_sell, Produto *prod, int *posicao_prod, Data *d)
{
    int i;
    int verifica_cod = 0;
    float taxa;

    printf("| Venda de Produto |");
    do
    {
        printf("\n| Informe o Código do produto: ");
        scanf("%d", &(sell + *posicao_sell)->cod_venda);
        while (getchar() != '\n')
            ;

        for (i = 0; i < *posicao_prod; i++)
        {
            if ((prod + i)->cod_identificador == (sell + *posicao_sell)->cod_venda)
            {
                if ((prod + i)->situacao == 1)
                {
                    printf("| Descrição: %s", (prod + i)->descricao);
                    printf("\n| Data da venda: \n");

                    recebedata(d);

                    (sell + *posicao_sell)->data.dia = d->dia;
                    (sell + *posicao_sell)->data.mes = d->mes;
                    (sell + *posicao_sell)->data.ano = d->ano;

                    (sell + *posicao_sell)->valorUnitVenda = (prod + i)->valorVenda;
                    printf("| Preço unitário de venda: R$ %.2f\n\n", (sell + *posicao_sell)->valorUnitVenda);

                    printf("| Quantidade: ");

                    while (1)
                    {
                        if (scanf("%d", &(sell + *posicao_sell)->quantidade) != 1)
                        {
                            printf("\nOpção inválida, tente novamente!");
                            while (getchar() != '\n')
                                ;
                            continue;
                        }
                        else if ((sell + *posicao_sell)->quantidade > (prod + i)->qtdAtual)
                        {
                            printf("\nEstoque insuficiente!");
                            continue;
                        }
                        else if ((sell + *posicao_sell)->quantidade <= 0)
                        {
                            printf("\nValor inexistente!");
                            continue;
                        }
                        else
                        {
                            if ((prod + i)->qtdAtual - (sell + *posicao_sell)->quantidade == 0)
                            {
                                (prod + i)->situacao = 2;
                            }

                            (sell + *posicao_sell)->valorTotal = (sell + *posicao_sell)->quantidade * (sell + *posicao_sell)->valorUnitVenda;
                            printf("| Preço total da venda: R$ %.2f\n\n", (sell + *posicao_sell)->valorTotal);

                            (prod + i)->qtdAtual -= (sell + *posicao_sell)->quantidade;

                            break;
                        }
                    }
                }
                else if ((prod + i)->situacao == 2)
                {
                    printf("\nProduto esgotado!\n\n");
                }
                else
                {
                    printf("\nProduto inativo!\n\n");
                }
                verifica_cod = 1;
                break;
            }
        }
        !verifica_cod ? "\nCódigo não encontrado no sistema, tente novamente!\n" : NULL;

    } while (!verifica_cod);

    (*posicao_sell)++;
}

void exibir_vendas(Data *dt_inicial, Data *dt_final, Venda *sell, int *posicao_sell, Produto *prod, int *posicao_prod, int *acoes)
{
    int i, k;
    int opcao_menu;
    int sair_menu = 0;

    do
    {
        printf("|---- PESQUISA DE VENDAS REALIZADAS POR DATA ----|");
        printf("\n| 0 - RETORNAR AO MENU ANTERIOR;");
        printf("\n| 1 - TODAS AS VENDAS REALIZADAS;");
        printf("\n| 2 - TODAS A PARTIR DA DATA;");
        printf("\n| 3 - TODAS ANTES DA DATA;");
        printf("\n| 4 - ENTRE AS DATAS.");
        printf("\n|-------------------------------------------------|\n");

        while (1)
        {
            if (scanf("%d", &opcao_menu) != 1)
            {
                printf("Opção inválida, tente novamente!");
                while (getchar() != '\n')
                    ;
                continue;
            }

            if (opcao_menu < 0 || opcao_menu > 4)
            {
                printf("Opção inválida, tente novamente!");
                continue;
            }
            else
                break;
        }

        switch (opcao_menu)
        {
        case 0:
            system("cls");
            sair_menu++;

            (*acoes)++;
            break;
        case 1:
            system("cls");

            printf("| TODO O PERÍODO |\n\n");
            for (i = 0; i < *posicao_sell; i++)
            {
                for (k = 0; k < *posicao_prod; k++)
                {
                    (prod + k)->cod_identificador == (sell + i)->cod_venda ? imprime_venda((prod + k), (sell + i)) : NULL;
                }
                printf("\n");
            }

            (*acoes)++;
            break;
        case 2:
            system("cls");

            printf("| Informe a data inicial:\n");
            recebedata(dt_inicial);

            system("cls");
            printf("| TODAS A PARTIR DA DATA: %d/%d/%d |\n\n", dt_inicial->dia, dt_inicial->mes, dt_inicial->ano);
            for (i = 0; i < *posicao_sell; i++)
            {
                if (!comparaData((sell + i)->data, *dt_inicial))
                {
                    for (k = 0; k < *posicao_prod; k++)
                    {
                        (prod + k)->cod_identificador == (sell + i)->cod_venda ? imprime_venda((prod + k), (sell + i)) : NULL;
                    }
                }
                printf("\n");
            }

            (*acoes)++;
            break;
        case 3:
            system("cls");

            printf("| Informe a data final:\n");
            recebedata(dt_final);

            system("cls");
            printf("| TODAS ATÉ A DATA: %d/%d/%d |\n\n", dt_final->dia, dt_final->mes, dt_final->ano);
            for (i = 0; i < *posicao_sell; i++)
            {
                if (comparaData((sell + i)->data, *dt_final))
                {
                    for (k = 0; k < *posicao_prod; k++)
                    {
                        (prod + k)->cod_identificador == (sell + i)->cod_venda ? imprime_venda((prod + k), (sell + i)) : NULL;
                    }
                }
                printf("\n");
            }

            (*acoes)++;
            break;
        case 4:
            system("cls");

            printf("| Informe a data inicial:\n");
            recebedata(dt_inicial);

            printf("\n| Informe a data final:\n");
            recebedata(dt_final);

            system("cls");
            printf("| PERÍODO DE %d/%d/%d ATÉ %d/%d/%d|\n\n", dt_inicial->dia, dt_inicial->mes, dt_inicial->ano,
                   dt_final->dia, dt_final->mes, dt_final->ano);

            for (i = 0; i < *posicao_sell; i++)
            {
                if (!comparaData((sell + i)->data, *dt_inicial))
                {
                    if (comparaData((sell + i)->data, *dt_final))
                    {
                        for (k = 0; k < *posicao_prod; k++)
                        {
                            (prod + k)->cod_identificador == (sell + i)->cod_venda ? imprime_venda((prod + k), (sell + i)) : NULL;
                        }
                    }
                }
                printf("\n");
            }

            (*acoes)++;
            break;
        default:
            system("cls");
            printf("Opção inválida, tente novamente!");
            break;
        }
    } while (!sair_menu);
}

void historico_prod(Produto *prod, int *posicao_prod, Compra *buy, int *posicao_buy, Venda *sell, int *posicao_sell, int *acoes)
{
    int i;
    int opcao_menu;
    int sair_menu = 0;
    int verifica_cod = 0;
    int pesquisa_cod;
    int somatorio_compra;
    int somatorio_venda;
    int prot_conta = 0;

    printf("| HISTÓRICO DO PRODUTO |");

    do
    {
        printf("\n| Informe o Código do produto: ");
        scanf("%d", &pesquisa_cod);
        while (getchar() != '\n')
            ;

        for (i = 0; i < *posicao_prod; i++)
        {
            if ((prod + i)->cod_identificador == pesquisa_cod)
            {
                system("cls");
                while (sair_menu == 0)
                {
                    printf("|---------- HISTÓRICO DO PRODUTO ----------|");
                    printf("\n| 0 - RETORNAR AO MENU ANTERIOR;");
                    printf("\n| 1 - INFORMAÇÕES DO PRODUTO;");
                    printf("\n| 2 - LISTAR COMPRAS E VENDAS;");
                    printf("\n| 3 - RECALCULAR UNIDADES.");
                    printf("\n|------------------------------------------|\n");

                    while (1)
                    {
                        if (scanf("%d", &opcao_menu) != 1)
                        {
                            printf("Opção inválida, tente novamente!");
                            while (getchar() != '\n')
                                ;
                            continue;
                        }

                        if (opcao_menu < 0 || opcao_menu > 4)
                        {
                            printf("Opção inválida, tente novamente!");
                            continue;
                        }
                        else
                            break;
                    }

                    switch (opcao_menu)
                    {
                    case 0:
                        system("cls");
                        sair_menu++;

                        (*acoes)++;
                        break;
                    case 1:
                        system("cls");

                        for (i = 0; i < *posicao_buy; i++)
                        {
                            printf("Indice: %d | Qtd: %d\n", i, (buy + i)->quantidade);
                        }
                        for (i = 0; i < *posicao_sell; i++)
                        {
                            printf("Indice: %d | Qtd: %d\n", i, (sell + i)->quantidade);
                        }

                        for (i = 0; i < *posicao_buy; i++)
                        {
                            if (pesquisa_cod == (buy + i)->cod_compra)
                            {
                                printf("| INFORMAÇÕES DO PRODUTO |");
                                printf("\n| Código: %d", (prod + i)->cod_identificador);
                                printf("\n| Descrição: %s", (prod + i)->descricao);
                                printf("\n| Situação: %s\n\n", (prod + i)->situacao == 1 ? "Em estoque!" : (prod + i)->situacao == 2 ? "Esgotado!"
                                                                                                                                     : "Inativo!");
                                break;
                            }
                        }

                        (*acoes)++;
                        break;
                    case 2:
                        system("cls");

                        printf("| COMPRAS |\n");
                        for (i = 0; i < *posicao_buy; i++)
                        {
                            pesquisa_cod == (buy + i)->cod_compra ? "\n", imprime_compra((prod + i), (buy + i)) : NULL;
                        }
                        printf("\n| VENDAS |\n");
                        for (i = 0; i < *posicao_sell; i++)
                        {
                            pesquisa_cod == (sell + i)->cod_venda ? "\n", imprime_venda((prod + i), (sell + i)) : NULL;
                        }

                        (*acoes)++;
                        break;
                    case 3:
                        system("cls");

                        if (!prot_conta)
                        {
                            for (i = 0; i < *posicao_buy; i++)
                            {
                                somatorio_compra += (buy + i)->quantidade;
                            }

                            for (i = 0; i < *posicao_sell; i++)
                            {
                                somatorio_venda += (sell + i)->quantidade;
                            }
                        }

                        (somatorio_compra - somatorio_venda) > (prod + *posicao_prod)->qtdAtual ? "Produto sobrando!" : (somatorio_compra - somatorio_venda) == (prod + *posicao_prod)->qtdAtual ? "Estoque correto!"
                                                                                                                                                                                                 : "Produtos faltando";

                        printf("\nAuditoria de unidades: %d | Quantidade em estoque: %d\n\n", (somatorio_compra - somatorio_venda), (prod + *posicao_prod - 1)->qtdAtual);

                        prot_conta = 1;
                        (*acoes)++;
                        break;
                    default:
                        system("cls");
                        printf("Opção inválida, tente novamente!");
                        break;
                    }
                }
                verifica_cod = 1;
            }
        }
        sair_menu = 0;
        !verifica_cod ? "\nCódigo não encontrado no sistema, tente novamente!\n" : NULL;

    } while (!verifica_cod);
}

void produtos_esgotados(Produto *prod, int *posicao_prod)
{
    int i;

    printf("| PRODUTOS ESGOTADOS |\n");
    for (i = 0; i < *posicao_prod; i++)
    {
        if ((prod + i)->situacao == 2)
        {
            printf("\n| Código: %d", (prod + i)->cod_identificador);
            printf("\n| Descrição: %s", (prod + i)->descricao);
            printf("\n| Quantidade: %d", (prod + i)->qtdAtual);
        }
    }
    printf("\n\n");
}

void sobre()
{
    printf("| SISTEMA DE SUPERMERCADO |;");
    printf("\n| Engenharia de Controle e Automação;");
    printf("\n| Algorítmo e Estrutura de Dados;");
    printf("\n| Desenvolvido por: Gabriel Henrique e Higor Soares Pereira;");
    printf("\n| Última alteração: 25/11/2025");
    printf("\n\n");
}

void recebedata(Data *d)
{
    printf("| Dia (dd): ");
    scanf("%d", &d->dia);
    printf("| Mês: (mm): ");
    scanf("%d", &d->mes);
    printf("| Ano: (aaaa): ");
    scanf("%d", &d->ano);
}

int comparaData(Data a, Data b)
{
    // Tipo a: Data registrada.
    // Tipo b: Data pesquisada.

    if (a.ano < b.ano)
        return 1;
    if (a.ano > b.ano)
        return 0;

    if (a.mes < b.mes)
        return 1;
    if (a.mes > b.mes)
        return 0;

    if (a.dia <= b.dia)
        return 1;

    return 0;
}

void imprime_compra(Produto *p, Compra *c)
{
    printf("| Código: %d", c->cod_compra);
    printf("\n| Descrição: %s", p->descricao);
    printf("\n| Data: %d/%d/%d", c->data.dia, c->data.mes, c->data.ano);
    printf("\n| Quantidade: %d", c->quantidade);
    printf("\n| Valor unitário: %.2f", c->valorUnit);
    printf("\n| Valor total: %.2f\n", c->valorTotal);
}

void imprime_venda(Produto *p, Venda *v)
{
    printf("| Código: %d", v->cod_venda);
    printf("\n| Descrição: %s", p->descricao);
    printf("\n| Data: %d/%d/%d", v->data.dia, v->data.mes, v->data.ano);
    printf("\n| Quantidade: %d", v->quantidade);
    printf("\n| Valor unitário: %.2f", v->valorUnitVenda);
    printf("\n| Valor total: %.2f\n", v->valorTotal);
}