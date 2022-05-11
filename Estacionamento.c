#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "Estacionamento.h"

//Aloca espaço para estacionamento
Estacionamento * aloca_estacionamento ()
{
    Estacionamento *estacionamento;

    estacionamento = (Estacionamento *) malloc (sizeof(Estacionamento));

    if (estacionamento == NULL)
    {
        printf("\tErro ao alocar.\n");
    }

    estacionamento->qtd_fileiras = 0;
    estacionamento->qtd_max_carros_por_fileira = 0;
    estacionamento->qtd_max_carros_rua = 0;
    estacionamento->numero_veiculos_total = 0;

    return estacionamento;
}

//Define número de fileiras
//Define número de carros em cada fileira
//Define número de carros na rua
//Inicia contador de carros (dentro do estacionamento) com a qtd máxima de carros por fileira
//Inicia contador de carros na rua com a qtd máxima de carros na rua
Estacionamento *configurar_estacionamento (Estacionamento *estacionamento)
{
    char s[30];
    int i;


    printf("\n\t\t\t--------------TELA DE CONFIGURAÇÃO DO ESTACIONAMENTO--------------\n");

    //tratando tamanho maximo, podendo ser escolhido alterando o valor da constante TAM
    do
    {
        printf("\n\tQuantas fileiras o seu estacionamento tem ? ");

        fflush(stdin);

        gets (s);
        estacionamento->qtd_fileiras = atoi (s);

        if(estacionamento->qtd_fileiras > TAM)
        {
            printf("\n\tA capacidade do estacionamento é para apenas %d fileiras de carro\n", TAM);
        }
    }
    while(estacionamento->qtd_fileiras < 1 || estacionamento->qtd_fileiras > TAM);

    //tratando tamanho maximo, podendo ser escolhido alterando o valor da constante TAM
    do
    {
        printf("\n\tQuantos carros cabem em cada fileira do seu estacionamento? ");

        fflush(stdin);

        gets (s);
        estacionamento->qtd_max_carros_por_fileira = atoi (s);

        if(estacionamento->qtd_max_carros_por_fileira > TAM)
        {
            printf("\n\tA capacidade das fileiras do estacionamento é para apenas %d carros\n", TAM);
        }
    }
    while(estacionamento->qtd_max_carros_por_fileira < 1 || estacionamento->qtd_max_carros_por_fileira > TAM);

    //tratando tamanho maximo, podendo ser escolhido alterando o valor da constante TAM
    printf("\n\tDICA: A quantidade mínima de vagas na rua para o seu estacionamento é de: %d\n", estacionamento->qtd_max_carros_por_fileira - 1);
    do
    {
        printf("\n\tQuantos carros podem ser manobrados na rua? ");

        fflush(stdin);

        gets (s);
        estacionamento->qtd_max_carros_rua = atoi (s);

        if(estacionamento->qtd_max_carros_rua > TAM)
        {
            printf("\n\tA capacidade de veículos que podem ser manobrados na rua é: %d\n", TAM);
        }

        if (estacionamento->qtd_max_carros_rua < estacionamento->qtd_max_carros_por_fileira - 1)
        {
            printf("\n\tA quantidade de vagas mínima para a rua é de %d veículo(s).\n", estacionamento->qtd_max_carros_por_fileira - 1);
        }

    }
    while(estacionamento->qtd_max_carros_rua < estacionamento->qtd_max_carros_por_fileira - 1 || estacionamento->qtd_max_carros_rua > TAM);


    //Inicializando o contador de carros por fileira com a quantidade de vagas dispoíveis
    for (i = 0; i < TAM; i++)
    {
        estacionamento->contador_carros[i] = estacionamento->qtd_max_carros_por_fileira;
    }

    //Inicializando o contador de carros na rua com a quantidade de vagas disponíveis
    estacionamento->contador_carros_rua = estacionamento->qtd_max_carros_rua;


    return estacionamento;
}

//Cria espaço do estacionamento e da rua. De acordo com qtd de: fileiras, carros em cada fileira e carros na rua
//aloca espaço para as fileiras
//Aloca espaço para a rua
Estacionamento *cria_estacionamento (Estacionamento * estacionamento)
{
    int i;

    //Alocando espaço para as fileiras do estacionamento
    estacionamento->fileiras = (Veiculo **) malloc (estacionamento->qtd_fileiras * sizeof(Veiculo *));

    if (estacionamento->fileiras == NULL)
    {
        printf("\n\tErro ao alocar.\n");
    }

    //Apontando as pilhas do estacionamento para NULL (Vazias)
    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {
        estacionamento->fileiras[i] = NULL;
    }

    //Apontando a pilha da rua para NULL (Vazia)
    estacionamento->fileira_rua = NULL;

    //Iniciando contador de veículos total do estacionamento em zero
    estacionamento->numero_veiculos_total = 0;


    printf("\n\t\t\t--------------ESTACIONAMENTO CONFIGURADO COM SUCESSO!--------------\n");

    return estacionamento;
}

//Aloca espaço para veiculo
//Aloca espaço para placa
Veiculo *cria_veiculo ()
{
    Veiculo *novo_veiculo;

    novo_veiculo = (Veiculo *) malloc(sizeof(Veiculo));

    if (novo_veiculo == NULL)
    {
        printf("\n\tErro ao alocar.\n");
    }

    novo_veiculo->placa = (char *) malloc (sizeof(char));

    if (novo_veiculo->placa == NULL)
    {
        printf("\n\tErro ao alocar.\n");
    }

    novo_veiculo->prox = NULL;

    return novo_veiculo;
}

//Insere placa
//Veriica placa para saber se tem algum veículo com mesma placa estacionado
//Insere tempo de pernanência
//Próximo recebe NULL
Veiculo *Insere_dados_veiculo (Veiculo * novo_veiculo, Estacionamento *estacionamento)
{
    int i;
    Veiculo *aux;
    int compara_placa = 0; // se no final da verificação das placas essa variável for maior que 0, significa que tem uma placa igual no estacionamento

    printf("\n\t---------Informações do veículo para estacionar---------\n");

    printf("\n\tEntre com a placa do seu veículo: ");
    scanf("%s", novo_veiculo->placa);

    //Verifica a placa, se tem algum veículo estacionado com mesma placa
    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {
        aux = estacionamento->fileiras[i];

        while (aux != NULL)
        {
            //se tiver alguma placa igual contador incrementa
            if ( strcmp(aux->placa, novo_veiculo->placa) == 0 )
            {
                compara_placa++;
            }

            aux = aux->prox;
        }
    }

    //Se contador maior 0, tem algum veículo com mesma placa e não deixa estacionar
    if (compara_placa > 0)
    {
        printf("\n\tAtenção, a placa do seu veículo pode ter sido clonada.\n\tVerifique a placa antes de estacionar.\n");
        novo_veiculo->placa = NULL;
    }
    else
    {
        printf("\n\tEntre com tempo de pernanência em minutos: ");
        scanf("%d", &novo_veiculo->tempo_permanencia);
    }


    return novo_veiculo;
}

//Recebe a escolha do dono do veículo se quer estacionar sozinho ou deixar com manobrista
int escolha_manobrista ()
{
    int escolha;
    char s[30];

    printf("\n\tDeseja estacionar sozinho ou prefere deixar com manobrista?\n");
    printf("\n\tManobrista irá estacionar na vaga recomendada!\n");
    printf("\t[1] Estacionar sozinho\n");
    printf("\t[2] Deixar com manobrista\n");

    do
    {
        printf("\tEscolha: ");

        fflush(stdin);

        gets (s);
        escolha = atoi (s);

    }
    while (escolha < 1 || escolha > 2);


    return escolha;
}

//Informa vagas disponíveis
//Recebe a escolha da fileira
int verifica_fileira (Estacionamento *estacionamento)
{
    int escolha_fileira;
    char s[30];
    int i;

    printf("\n\t---------Fileiras com vagas disponíveis---------\n");

    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {
        if (estacionamento->contador_carros[i] != 0)
        {
            printf("\n\tFileira %d tem %d vagas disponíveis\n", i + 1, estacionamento->contador_carros[i]);
        }
    }

    do
    {
        //Pergunta a fileira que deseja estacionar
        printf("\n\tEntre com a fileira que deseja estacionar:\n");
        do
        {
            printf("\tEscolha: ");

            fflush(stdin);

            gets (s);
            escolha_fileira = atoi (s);

        }
        while (escolha_fileira < 1 || escolha_fileira > estacionamento->qtd_fileiras);

        if (estacionamento->contador_carros[escolha_fileira - 1] == 0)
        {
            printf("\n\tFileira sem vagas disponíveis.\n\tEscolha outra fileira.\n");
        }

    }
    while (estacionamento->contador_carros[escolha_fileira - 1] == 0);


    return escolha_fileira;
}

//Insere veículo no estacionamento de acordo com a escolha do dono do carro
//Se quiser estacionar sozinho, é perguntado qual fileira deseja estacionar
//Se quiser o manobrista, carro é estacionado na melhor escolha de vaga
Estacionamento *insere_veiculo (Estacionamento *estacionamento)
{
    Veiculo *novo_veiculo;//Veículo que será estacionado
    Veiculo * veiculo_aux;//Veículo de demonstração para a melhor opção de vaga
    int fileira_com_maior_num_vagas = 0;//Melhor opção de fileira do estacionamento
    int decisao_estacionar;//Decisão sobre estacionar sozinho ou deixar com manobrista
    int fileira_escolhida;

    //Veículo a ser estacionado
    novo_veiculo = cria_veiculo();
    novo_veiculo = Insere_dados_veiculo(novo_veiculo, estacionamento);

    //Só será NULL quando uma placa repetida for inserida
    if (novo_veiculo->placa == NULL)
    {
        return estacionamento;
    }

    //Buscca a melhor opção para o veículo ser estacionado
    fileira_com_maior_num_vagas = heuristica_insercao(estacionamento, novo_veiculo);

    //---------------------------------------//

    //Veículo auxiliar para mostrar a sugestão de vaga
    veiculo_aux = cria_veiculo();
    veiculo_aux->placa = "DICA";//Palavra para mostrar de forma diferenciada a sugestão de vaga
    veiculo_aux->tempo_permanencia = 0;

    //Faz a inserção do veículo auxiliar como forma de demonstração para sugestão de melhor vaga
    //Decrementa o contador de carro para a impressão sair correta
    if (estacionamento->fileiras[fileira_com_maior_num_vagas] == NULL)

    {
        estacionamento->fileiras[fileira_com_maior_num_vagas] = veiculo_aux;
        //atualiza número de vagas disponíveis na fileira
        estacionamento->contador_carros[fileira_com_maior_num_vagas]--;
    }
    else
    {
        veiculo_aux->prox = estacionamento->fileiras[fileira_com_maior_num_vagas];
        estacionamento->fileiras[fileira_com_maior_num_vagas] = veiculo_aux;
        //atualiza número de vagas disponíveis na fileira
        estacionamento->contador_carros[fileira_com_maior_num_vagas]--;
    }

    printf("\n\t--------SUGESTÃO DE VAGA PARA O SEU VEÍCULO--------\n\n");

    imprime_estacionamento(estacionamento);

    //Pergunta se quer estacionar sozinho ou com manobrista
    decisao_estacionar = escolha_manobrista();

    switch (decisao_estacionar)
    {
    case 1:
        //Se dono do veíclo recusar a sugestão volto com estacionamento do jeito que estava antes
        estacionamento->fileiras[fileira_com_maior_num_vagas] = estacionamento->fileiras[fileira_com_maior_num_vagas]->prox;

        //Voltando com a  quantidade de vagas disponíveis na fileira
        estacionamento->contador_carros[fileira_com_maior_num_vagas]++;

        //Libero espaço do carro de demosntração
        free (veiculo_aux);

        fileira_escolhida = verifica_fileira(estacionamento);

        if (estacionamento->fileiras[fileira_escolhida - 1] == NULL)
        {
            estacionamento->fileiras[fileira_escolhida - 1] = novo_veiculo;
            //atualiza número de vagas disponíveis na fileira
            estacionamento->contador_carros[fileira_escolhida - 1]--;
        }
        else
        {
            novo_veiculo->prox = estacionamento->fileiras[fileira_escolhida - 1];
            estacionamento->fileiras[fileira_escolhida - 1] = novo_veiculo;
            //atualiza número de vagas disponíveis na fileira
            estacionamento->contador_carros[fileira_escolhida - 1]--;
        }

        break;

    case 2:

        printf("\n\tOlá, sou seu manobrista. Seu veículo está em boas mãos!\n");

        //Volto com estacionamento do jeito que estava para estacionar o carro na vaga escolhida pelo programa
        estacionamento->fileiras[fileira_com_maior_num_vagas] = estacionamento->fileiras[fileira_com_maior_num_vagas]->prox;

        //Libero espaço do carro de demosntração
        free(veiculo_aux);

        if (estacionamento->fileiras[fileira_com_maior_num_vagas] == NULL)
        {
            estacionamento->fileiras[fileira_com_maior_num_vagas] = novo_veiculo;
        }
        else
        {
            novo_veiculo->prox = estacionamento->fileiras[fileira_com_maior_num_vagas];
            estacionamento->fileiras[fileira_com_maior_num_vagas] = novo_veiculo;
        }


        break;

    }

    printf("\n\tCarro estacionado com sucesso\n\n");

    //Incrementa o contador de veículos do estacionamento
    estacionamento->numero_veiculos_total++;


    return estacionamento;
}

//Responsável por achar a melhor vaga que tiver disponível para o veículo
//Leva em consideração dois parâmetros: Qual fileira tem mais vagas disponíveis e se o carro já estacionado na fileira tem o tempo de permanência
//maior do que será estacionado
int heuristica_insercao (Estacionamento *estacionamento, Veiculo *novo)
{
    int i;
    int aux_contador_vagas = 0; // vai guardar a qtd de qual fileira tem mais vagas disponíveis (se não achar nos primeiros parâmetros)
    int fileira_com_maior_num_vagas = 0;//vai guardar a posição da fileira com maior num de vagas disponiveis
    int num; //Número randômico para escolher uma opção entre um conjunto de melhores vagas
    int vet_melhor_vaga[TAM]; //Cada indice desse vetor, corresponde a uma fileira do estacionamento. Se a fileira na posição i for NULL esse vetor na i recebe
    // 1, se não recebe 0. Depois percorre as fileiras novamente para saber das fileiras que não são NULL se o tempo de pernamencia
    // do veículo atual é maior a do que será estacionado, se for, esse vetor anteriormente com 0 na posição i recebe 1. No final cada indice que tiver
    // 1 estará representando uma boa opção de vaga

    //Zerando cada posição do vetor para fazer as buscas
    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {
        vet_melhor_vaga[i] = 0;
    }

    //Primeira busca que vai ser feita é por fileiras vazias. Se a fileira for vazia o vetor melhor vaga no mesmo indice vai receber 1, que significa
    //que é uma boa opção de vaga
    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {

        //Se a fileira estiver vazia, o vetor de mellhor vaga recebe 1
        if (estacionamento->fileiras[i] == NULL)
        {
            vet_melhor_vaga[i] = 1;
        }
    }

    //Segunda busca que vai ser feita verifica se as fileiras que ja tem algum veículo parado, o tempo desse veículo que já está la é maior do que o novo
    //veículo.
    //A questão do tempo pensada foi de um veículo 1 qualquer parar atras de um veículo 2 qualquer cujo tempo seja maior para dar tempo do veículo 1 sair sem acabar o tempo
    //do veículo 2 evitando manobras desnecessárias
    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {

        // No indice do vetor que estiver 0, ele vai verificar se o tempo de permanencia do veiculo estacionado é maior do que a do novo
        if (vet_melhor_vaga[i] == 0)
        {
            //Verifica se a fileira tem vagas disponíveis
            if (estacionamento->contador_carros[i] > 0)
            {
                if (estacionamento->fileiras[i]->tempo_permanencia >= novo->tempo_permanencia)
                {
                    vet_melhor_vaga[i] = 1;
                }
                //Se o tempo não atender o requisito, aux incrementa
                else
                {
                    aux_contador_vagas++;
                }

            }

            //Se a fileira não atendeu os parametros anteriores ela fica com 0, aqui faz uma contagem de quantas fileiras disponiveis para estacionar
            //foram encontradas. No final se essa contagem chegar até o num de fileiras total do estacionamento, significa que nenhuma fileira foi encontrada
            // que atendesse os parametros anteriores.
            else
            {
                aux_contador_vagas++;
            }

        }

    }
    //Se o num do aux for == a qtd de fileiras, outro parametro é usado para encontrar uma melhor vaga
    if (aux_contador_vagas == estacionamento->qtd_fileiras)
    {
        //Aqui o aux é utilizado para guardar a qtd de vagas disponiveis em cada fileira
        aux_contador_vagas = 0;

        //Vai buscar a fileira com maior num de vagas disponíveis
        for (i = 0; i < estacionamento->qtd_fileiras; i++)
        {
            if (estacionamento->contador_carros[i] > aux_contador_vagas)
            {
                aux_contador_vagas = estacionamento->contador_carros[i];

                fileira_com_maior_num_vagas = i;
            }
        }

        //Essa posição do vetor recebe 1 e vai ser a vaga onde será a sugestão de melhor vaga
        vet_melhor_vaga[fileira_com_maior_num_vagas] = 1;

    }


    srand(time(NULL));
    //vai sortear uma posição dentre as melhores vagas disponíveis
    do
    {
        num = rand() % TAM;

    }
    while (vet_melhor_vaga[num] != 1);//sorteia até achar um num cujo indice do vetor tenha o 1 (que corresponde a uma boa opção de fileira)

    return num;
}

//Pergunta a placa do veículo a ser retirado
char *insere_placa_retirar_veiculo ()
{
    char *placa_retirada;

    placa_retirada = (char *) malloc (sizeof(char));


    printf("\n\tEntre com a placa do seu veículo :");
    scanf("%s", placa_retirada);


    return placa_retirada;
}

//Faz a varredura no estacionamento para procurar o veículo
//Comparando as placas
//Devolve a fileira onde o veículo está estacionado
int procura_veiculo (Estacionamento *estacionamento, char *placa_retirada)
{
    int fileira = -1;
    int i;
    Veiculo *aux;

    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {
        aux = estacionamento->fileiras[i];

        if (aux != NULL)
        {
            //Correndo as fileiras para encontrar o veículo
            while (aux != NULL)
            {
                //Se a placa for igual recebe a fileira e retorna
                if ( strcmp(aux->placa, placa_retirada) == 0)
                {
                    fileira = i;

                    return fileira;
                }

                aux = aux->prox;
            }
        }

    }

    printf("\n\tVeículo não encontrado\n\tVerifique a placa e tente novamente.\n");

    return fileira;
}

//Manobrar os veículos para a retirada do veículo que estiver saindo
//Cada veículo manobrado será direcionado para uma outra melhor vaga dentro do estacionamento
//Se estacionamento estiver lotado, os veículos são direcionados para a rua
Estacionamento *manobrar_e_retirar_veiculos (Estacionamento *estacionamento, int aux_retirada_sequenciada)
{
    int i;
    int fileira;
    int fileira_inserir_carro_manobrado;
    int fileira_maior_num_vagas = 0;
    char *placa_retirada;
    Veiculo *aux;
    Veiculo *aux_retirado;
    Veiculo *veiculo_copia;

    printf("\n\t---------Informações para retirar o veículo---------\n");

    //Recebe a placa do veículo a ser retirado
    placa_retirada = insere_placa_retirar_veiculo();

    //Busca a fileira onde o veículo está
    fileira = procura_veiculo(estacionamento, placa_retirada);

    //Se fileira for -1, não achou o veículo no estacionamento. Logo, não existe veículo com essa placa estacionado.
    //retorna estacionamento
    if (fileira == -1)
    {
        return estacionamento;
    }

    //Aux para buscar veículo na fileira
    aux = estacionamento->fileiras[fileira];

    //Enquanto não achar veículo com placa correspondente, faz todo o processo de manobrar, achar outra melhor vaga para veículo até achar a placa do
    //veículo que será retirado
    while ( strcmp (aux->placa, placa_retirada) != 0 )
    {
        //Cria uma copia do veículo para manobrar, essa copia será inserida na nova fileira
        veiculo_copia = cria_veiculo ();

        //Copia a placa e tempo de permanência para veículo copia
        strcpy(veiculo_copia->placa, aux->placa);
        veiculo_copia->tempo_permanencia = aux->tempo_permanencia;

        //Guarda o anterior para liberar espaço alocado
        aux_retirado = aux;

        //aux vai para próximo veículo da fileira
        aux = aux->prox;

        //Libera espaço alocado
        free (aux_retirado);

        //atualiza a fileira
        estacionamento->fileiras[fileira] = aux;

        //Incrementa contador de vagas disponíveis da fileira que veículo saiu (manobrado)
        estacionamento->contador_carros[fileira]++;

        //Verifica se estacionamento está lotado
        //Se estiver lotado, insere os veículos necessários na rua
        if (estacionamento->numero_veiculos_total == estacionamento->qtd_fileiras * estacionamento->qtd_max_carros_por_fileira || estacionamento->qtd_fileiras == 1)
        {
            //testa se a rua está vazia
            if (estacionamento->fileira_rua == NULL)
            {
                estacionamento->fileira_rua = veiculo_copia;

                estacionamento->contador_carros_rua--;

            }
            else
            {
                veiculo_copia->prox = estacionamento->fileira_rua;
                estacionamento->fileira_rua = veiculo_copia;

                estacionamento->contador_carros_rua--;

            }

        }

        //Se estacionamento não estiver lotado, faz as manobras dentro mesmo
        else
        {

            //Procura a melhor vaga para veículo manobrado, sem ser a fileira original dele
            do
            {
                fileira_inserir_carro_manobrado = heuristica_insercao(estacionamento, veiculo_copia);

                //Quando a huristica acha a melhor vaga que seja na fileira que está saindo os carros
                if (fileira_inserir_carro_manobrado == fileira)
                {
                    for (i = 0; i < estacionamento->qtd_fileiras; i++)
                    {
                        //Esse if vazio serve para pular a fileira aonde os veículos estão saindo
                        if (i != fileira)
                        {
                            if (estacionamento->contador_carros[i] > fileira_maior_num_vagas)
                            {
                                fileira_maior_num_vagas = estacionamento->contador_carros[i];

                                fileira_inserir_carro_manobrado = i;
                            }
                        }
                    }
                }

            }
            while (fileira_inserir_carro_manobrado == fileira);


            //Se a fileira for NULL (Fileira vazia)
            if (estacionamento->fileiras[fileira_inserir_carro_manobrado] == NULL)
            {

                estacionamento->fileiras[fileira_inserir_carro_manobrado] = veiculo_copia;

                //Decrementa o contador de vagas disponiveis na fileira
                estacionamento->contador_carros[fileira_inserir_carro_manobrado]--;

            }
            else
            {

                veiculo_copia->prox = estacionamento->fileiras[fileira_inserir_carro_manobrado];
                estacionamento->fileiras[fileira_inserir_carro_manobrado] = veiculo_copia;

                //Decrementa o contador de vagas disponiveis na fileira
                estacionamento->contador_carros[fileira_inserir_carro_manobrado]--;

            }

        }

        //Quando a chamada da função vier com aux_retirada_sequencialda == 1, faz passo a passo printando na tela
        if (aux_retirada_sequenciada == 1)
        {
            system ("cls");

            imprime_estacionamento (estacionamento);

            system ("pause");
            system ("cls");
        }

    }

    //Aqui aux já é o veículo a ser excluido, então um outro aux recebe ele
    aux_retirado = aux;

    //Aux recebe seu prox, podendo ser outro veículo ou, se for o ultimo da fileira recebe NULL indicando fileira vazia
    aux = aux->prox;

    //Atualiza a fileira que teve seu veículo retirado
    estacionamento->fileiras[fileira] = aux;

    //Atualiza o num de vagas disponíveis da fileira
    estacionamento->contador_carros[fileira]++;

    //Atualiza num de veículos total do estacionamento
    estacionamento->numero_veiculos_total--;

    //Libera espaço alocado para veículo retirado
    free (aux_retirado);

    imprime_estacionamento (estacionamento);

    system ("pause");


    //Se a rua não estiver vazia, chama função para esvaziar a rua
    if (estacionamento->fileira_rua != NULL)
    {
        estacionamento = esvazia_rua (estacionamento, aux_retirada_sequenciada);
    }
    else
    {
        system ("cls");
    }

    printf("\n\tObrigado e volte sempre!\n\n");

    return estacionamento;
}

//Verifica se a rua tem algum veículo estacionado
//Se tiver, volta com os veículos para dentro do estacionamento
//usa a heuristica para achar a melhor vaga para voltar com os veículos
Estacionamento *esvazia_rua (Estacionamento *estacionamento, int aux_retirada_sequenciada)
{
    Veiculo *aux;
    Veiculo *veiculo_copia;
    Veiculo *aux_retirado;
    int fileira_inserir_carro;

    if (estacionamento->fileira_rua != NULL)
    {
        aux = estacionamento->fileira_rua;

        while (aux != NULL)
        {

            //Cria uma copia do veículo para devolver para dentro do estacionamento
            veiculo_copia = cria_veiculo ();

            //Copia a placa e tempo de permanência para veículo auxiliar
            strcpy(veiculo_copia->placa, aux->placa);
            veiculo_copia->tempo_permanencia = aux->tempo_permanencia;

            //Guarda o anterior para liberar espaço alocado
            aux_retirado = aux;

            //aux vai para próximo veículo da fileira
            aux = aux->prox;

            //Atualiza contador de veículos da rua
            estacionamento->contador_carros_rua++;

            //Atualiza a fileira da rua
            estacionamento->fileira_rua = aux;

            //Libera espaço alocado
            free (aux_retirado);

            //Procura melhor fileira para devolver o veículo
            fileira_inserir_carro = heuristica_insercao (estacionamento, veiculo_copia);


            if (estacionamento->fileiras[fileira_inserir_carro] == NULL)
            {
                estacionamento->fileiras[fileira_inserir_carro] = veiculo_copia;

                //Decrementa a qtd de vagas disponíveis para essa fileira
                estacionamento->contador_carros[fileira_inserir_carro]--;
            }
            else
            {
                veiculo_copia->prox = estacionamento->fileiras[fileira_inserir_carro];
                estacionamento->fileiras[fileira_inserir_carro] = veiculo_copia;

                //Decrementa a qtd de vagas disponíveis para essa fileira
                estacionamento->contador_carros[fileira_inserir_carro]--;
            }

            if (aux_retirada_sequenciada == 1)
            {
                system ("cls");

                imprime_estacionamento(estacionamento);

                system ("pause");
                system ("cls");
            }

        }

        //Atualiza fileira da rua
        estacionamento->fileira_rua = aux;

    }

    return estacionamento;
}
