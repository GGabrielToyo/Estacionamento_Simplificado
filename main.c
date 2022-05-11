#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "Estacionamento.h"

int menu (int num_veiculos_total, int qtd_fileiras, int qtd_carros_por_filera)
{
    int escolha;
    char s[30];

    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\tEstacionamento Simplificado\n");
    printf("\t\t\tOBS: Entre apenas com NÚMEROS por favor.\n");
    printf("\t\t\tPara uma melhor experiência, utilize o programa em TELA CHEIA\n");

    if (qtd_fileiras != 0)
    {
        if (num_veiculos_total == qtd_fileiras * qtd_carros_por_filera)
        {
            printf("\t\t\t#### ESTACIONAMENTO LOTADO ####\n");
        }
    }

    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("\t\t\tMENU:\n");
    printf("\t\t\t[1] Configurar estacionamento\n");
    printf("\t\t\t[2] Mostrar estacionamento\n");
    printf("\t\t\t[3] Inserir veículo\n");
    printf("\t\t\t[4] Retirar veículo (Retirada simples)\n");
    printf("\t\t\t[5] Retirar veículo (Retirada sequênciada)\n");
    printf("\t\t\t[6] Sair\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    do
    {
        printf("\t\tEscolha: ");
        fflush(stdin);
        gets (s);
        escolha = atoi (s);

    }
    while (escolha < 1 || escolha > 6);


    return escolha;
}

void imprime_estacionamento (Estacionamento *estacionamento)
{
    Veiculo * aux;
    int i;
    int j;
    int cont;

    printf("\n\n\n");

    for (i = 0; i < estacionamento->qtd_fileiras; i ++)
    {
        printf("\n ----------------------------------------------------------------------------------------------------FILEIRA %d-----------------------------------------------------------------------------------------------------\n\n", i + 1);

        if (estacionamento->fileiras[i] == NULL)
        {

            j = 0; //j vai até o num max de carros por fileira

            //Do while para mostrar as vagas disponíveis
            do
            {
                printf(" Vaga Disponível  ");
                j++;

            }
            while (j < estacionamento->qtd_max_carros_por_fileira);

            printf("\n");
        }
        else
        {
            cont = 0;

            aux = estacionamento->fileiras[i];


            //Se for diferente de zero, quer dizer que tem vaga disponível (As vagas vazias sempre serão no topo da pilha)
            if (estacionamento->contador_carros[i] != 0)
            {
                // as fileiras que não estão vazias mas tem vagas disponiveis. Essas vagas disponiveis são contadas pelo cont
                do
                {
                    printf(" Vaga Disponível  ");
                    cont++;

                }
                while (cont < estacionamento->contador_carros[i]);

            }

            //Em cada fileira, dps de preencher as vagas disponíveis (se houver) printa os veículos estacopnados
            while (aux != NULL)
            {
                if ( strcmp(aux->placa, "DICA") == 0 )
                {
                    printf(" *%s*  ", aux->placa);
                }
                else
                {
                    printf(" Placa: %s Tempo: %d min  ", aux->placa, aux->tempo_permanencia);
                }

                aux = aux->prox;
            }

        }
    }

    printf("\n ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

    printf("\n\n");

    printf("\n ------------------------------------------------------------------------------------------------------RUA---------------------------------------------------------------------------------------------------------\n\n");

    // A rua segue a mesma lógica das fileiras para a impressão correta das vagas disponíveis e eventualmente dos veículos
    if (estacionamento->fileira_rua == NULL)
    {
        j = 0;

        do
        {
            printf(" Vaga Disponível  ");
            j++;

        }
        while (j < estacionamento->qtd_max_carros_rua);
    }
    else
    {
        aux = estacionamento->fileira_rua;

        //Se for diferente de zero, quer dizer que tem vaga disponível (As vagas vazias sempre serão no topo da pilha)
        if (estacionamento->contador_carros_rua != 0)
        {
            do
            {
                printf(" Vaga Disponível  ");
                cont++;

            }
            while (cont < estacionamento->contador_carros_rua);

        }

        while (aux != NULL)
        {


            printf(" Placa: %s Tempo: %d min ", aux->placa, aux->tempo_permanencia);

            aux = aux->prox;
        }
    }

    printf("\n ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

}

int main()
{
    setlocale(LC_ALL,"");

    int escolha;                     //Receber a escolha do menu
    Estacionamento * estacionamento;
    char flag = '0';
    int aux_retirada_sequenciada; //Na opção 5 (retirada sequenciada) recebe 1 para a função executar passo a passo ou na opção 4 recebe 0 faz todo processo

    estacionamento = aloca_estacionamento ();

    do
    {
        escolha = menu (estacionamento->numero_veiculos_total, estacionamento->qtd_fileiras, estacionamento->qtd_max_carros_por_fileira);

        switch (escolha)
        {
        //Configura estacionamento
        case 1:
            system("cls");
            estacionamento = configurar_estacionamento (estacionamento);
            estacionamento = cria_estacionamento (estacionamento);

            system("pause");
            system("cls");
            break;

        //Mostrar estacionamento
        case 2:
            system("cls");

            if (estacionamento->qtd_fileiras != 0)
            {
                imprime_estacionamento(estacionamento);
            }
            else
            {
                printf("\n\tPrimeiro configure estacionamento!\n");
            }

            system("pause");
            system("cls");
            break;

        //Inserir veículo
        case 3:
            system("cls");
            if (estacionamento->qtd_fileiras != 0)
            {

                if (estacionamento->numero_veiculos_total == estacionamento->qtd_fileiras * estacionamento->qtd_max_carros_por_fileira)
                {
                    printf("\n\tEstacionamento Lotado!\n\n");
                }
                else
                {
                    insere_veiculo(estacionamento);
                }

            }
            else
            {
                printf("\tPara inserir veículos configure o estacionamento!\n\n");
            }

            system("pause");
            system("cls");
            break;

        //Retirar veículo (Retirada Simples)
        case 4:
            //Serve para a função saber se executa direto ou passo a passo
            aux_retirada_sequenciada = 0;

            system ("cls");

            if (estacionamento->qtd_fileiras == 0)
            {
                printf("\n\tPrimeiro configure o estacionamento e insira veículos!\n\n");
            }
            else if (estacionamento->numero_veiculos_total == 0)
            {
                printf("\n\tEstacionamento Vazio!\n\n");
            }
            else
            {
                estacionamento = manobrar_e_retirar_veiculos(estacionamento, aux_retirada_sequenciada);
            }

            system ("pause");
            system ("cls");
            break;

        //Retirar veículo (Retirada sequênciada)
        case 5:
            //Serve para a função saber se executa direto ou passo a passo
            aux_retirada_sequenciada = 1;

            system ("cls");

            if (estacionamento->qtd_fileiras == 0)
            {
                printf("\n\tPrimeiro configure o estacionamento e insira veículos!\n\n");
            }
            else if (estacionamento->numero_veiculos_total == 0)
            {
                printf("\n\tEstacionamento Vazio!\n\n");
            }
            else if (estacionamento->numero_veiculos_total != 0)
            {
                estacionamento = manobrar_e_retirar_veiculos (estacionamento, aux_retirada_sequenciada);
            }

            system ("pause");
            system ("cls");
            break;

        case 6:
            printf("\tEncerrando...\n");
            exit(0);
            break;
        }

    }
    while (flag == '0');

    return 0;
}
