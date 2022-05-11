#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "Estacionamento.h"

//Aloca espa�o para estacionamento
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

//Define n�mero de fileiras
//Define n�mero de carros em cada fileira
//Define n�mero de carros na rua
//Inicia contador de carros (dentro do estacionamento) com a qtd m�xima de carros por fileira
//Inicia contador de carros na rua com a qtd m�xima de carros na rua
Estacionamento *configurar_estacionamento (Estacionamento *estacionamento)
{
    char s[30];
    int i;


    printf("\n\t\t\t--------------TELA DE CONFIGURA��O DO ESTACIONAMENTO--------------\n");

    //tratando tamanho maximo, podendo ser escolhido alterando o valor da constante TAM
    do
    {
        printf("\n\tQuantas fileiras o seu estacionamento tem ? ");

        fflush(stdin);

        gets (s);
        estacionamento->qtd_fileiras = atoi (s);

        if(estacionamento->qtd_fileiras > TAM)
        {
            printf("\n\tA capacidade do estacionamento � para apenas %d fileiras de carro\n", TAM);
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
            printf("\n\tA capacidade das fileiras do estacionamento � para apenas %d carros\n", TAM);
        }
    }
    while(estacionamento->qtd_max_carros_por_fileira < 1 || estacionamento->qtd_max_carros_por_fileira > TAM);

    //tratando tamanho maximo, podendo ser escolhido alterando o valor da constante TAM
    printf("\n\tDICA: A quantidade m�nima de vagas na rua para o seu estacionamento � de: %d\n", estacionamento->qtd_max_carros_por_fileira - 1);
    do
    {
        printf("\n\tQuantos carros podem ser manobrados na rua? ");

        fflush(stdin);

        gets (s);
        estacionamento->qtd_max_carros_rua = atoi (s);

        if(estacionamento->qtd_max_carros_rua > TAM)
        {
            printf("\n\tA capacidade de ve�culos que podem ser manobrados na rua �: %d\n", TAM);
        }

        if (estacionamento->qtd_max_carros_rua < estacionamento->qtd_max_carros_por_fileira - 1)
        {
            printf("\n\tA quantidade de vagas m�nima para a rua � de %d ve�culo(s).\n", estacionamento->qtd_max_carros_por_fileira - 1);
        }

    }
    while(estacionamento->qtd_max_carros_rua < estacionamento->qtd_max_carros_por_fileira - 1 || estacionamento->qtd_max_carros_rua > TAM);


    //Inicializando o contador de carros por fileira com a quantidade de vagas dispo�veis
    for (i = 0; i < TAM; i++)
    {
        estacionamento->contador_carros[i] = estacionamento->qtd_max_carros_por_fileira;
    }

    //Inicializando o contador de carros na rua com a quantidade de vagas dispon�veis
    estacionamento->contador_carros_rua = estacionamento->qtd_max_carros_rua;


    return estacionamento;
}

//Cria espa�o do estacionamento e da rua. De acordo com qtd de: fileiras, carros em cada fileira e carros na rua
//aloca espa�o para as fileiras
//Aloca espa�o para a rua
Estacionamento *cria_estacionamento (Estacionamento * estacionamento)
{
    int i;

    //Alocando espa�o para as fileiras do estacionamento
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

    //Iniciando contador de ve�culos total do estacionamento em zero
    estacionamento->numero_veiculos_total = 0;


    printf("\n\t\t\t--------------ESTACIONAMENTO CONFIGURADO COM SUCESSO!--------------\n");

    return estacionamento;
}

//Aloca espa�o para veiculo
//Aloca espa�o para placa
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
//Veriica placa para saber se tem algum ve�culo com mesma placa estacionado
//Insere tempo de pernan�ncia
//Pr�ximo recebe NULL
Veiculo *Insere_dados_veiculo (Veiculo * novo_veiculo, Estacionamento *estacionamento)
{
    int i;
    Veiculo *aux;
    int compara_placa = 0; // se no final da verifica��o das placas essa vari�vel for maior que 0, significa que tem uma placa igual no estacionamento

    printf("\n\t---------Informa��es do ve�culo para estacionar---------\n");

    printf("\n\tEntre com a placa do seu ve�culo: ");
    scanf("%s", novo_veiculo->placa);

    //Verifica a placa, se tem algum ve�culo estacionado com mesma placa
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

    //Se contador maior 0, tem algum ve�culo com mesma placa e n�o deixa estacionar
    if (compara_placa > 0)
    {
        printf("\n\tAten��o, a placa do seu ve�culo pode ter sido clonada.\n\tVerifique a placa antes de estacionar.\n");
        novo_veiculo->placa = NULL;
    }
    else
    {
        printf("\n\tEntre com tempo de pernan�ncia em minutos: ");
        scanf("%d", &novo_veiculo->tempo_permanencia);
    }


    return novo_veiculo;
}

//Recebe a escolha do dono do ve�culo se quer estacionar sozinho ou deixar com manobrista
int escolha_manobrista ()
{
    int escolha;
    char s[30];

    printf("\n\tDeseja estacionar sozinho ou prefere deixar com manobrista?\n");
    printf("\n\tManobrista ir� estacionar na vaga recomendada!\n");
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

//Informa vagas dispon�veis
//Recebe a escolha da fileira
int verifica_fileira (Estacionamento *estacionamento)
{
    int escolha_fileira;
    char s[30];
    int i;

    printf("\n\t---------Fileiras com vagas dispon�veis---------\n");

    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {
        if (estacionamento->contador_carros[i] != 0)
        {
            printf("\n\tFileira %d tem %d vagas dispon�veis\n", i + 1, estacionamento->contador_carros[i]);
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
            printf("\n\tFileira sem vagas dispon�veis.\n\tEscolha outra fileira.\n");
        }

    }
    while (estacionamento->contador_carros[escolha_fileira - 1] == 0);


    return escolha_fileira;
}

//Insere ve�culo no estacionamento de acordo com a escolha do dono do carro
//Se quiser estacionar sozinho, � perguntado qual fileira deseja estacionar
//Se quiser o manobrista, carro � estacionado na melhor escolha de vaga
Estacionamento *insere_veiculo (Estacionamento *estacionamento)
{
    Veiculo *novo_veiculo;//Ve�culo que ser� estacionado
    Veiculo * veiculo_aux;//Ve�culo de demonstra��o para a melhor op��o de vaga
    int fileira_com_maior_num_vagas = 0;//Melhor op��o de fileira do estacionamento
    int decisao_estacionar;//Decis�o sobre estacionar sozinho ou deixar com manobrista
    int fileira_escolhida;

    //Ve�culo a ser estacionado
    novo_veiculo = cria_veiculo();
    novo_veiculo = Insere_dados_veiculo(novo_veiculo, estacionamento);

    //S� ser� NULL quando uma placa repetida for inserida
    if (novo_veiculo->placa == NULL)
    {
        return estacionamento;
    }

    //Buscca a melhor op��o para o ve�culo ser estacionado
    fileira_com_maior_num_vagas = heuristica_insercao(estacionamento, novo_veiculo);

    //---------------------------------------//

    //Ve�culo auxiliar para mostrar a sugest�o de vaga
    veiculo_aux = cria_veiculo();
    veiculo_aux->placa = "DICA";//Palavra para mostrar de forma diferenciada a sugest�o de vaga
    veiculo_aux->tempo_permanencia = 0;

    //Faz a inser��o do ve�culo auxiliar como forma de demonstra��o para sugest�o de melhor vaga
    //Decrementa o contador de carro para a impress�o sair correta
    if (estacionamento->fileiras[fileira_com_maior_num_vagas] == NULL)

    {
        estacionamento->fileiras[fileira_com_maior_num_vagas] = veiculo_aux;
        //atualiza n�mero de vagas dispon�veis na fileira
        estacionamento->contador_carros[fileira_com_maior_num_vagas]--;
    }
    else
    {
        veiculo_aux->prox = estacionamento->fileiras[fileira_com_maior_num_vagas];
        estacionamento->fileiras[fileira_com_maior_num_vagas] = veiculo_aux;
        //atualiza n�mero de vagas dispon�veis na fileira
        estacionamento->contador_carros[fileira_com_maior_num_vagas]--;
    }

    printf("\n\t--------SUGEST�O DE VAGA PARA O SEU VE�CULO--------\n\n");

    imprime_estacionamento(estacionamento);

    //Pergunta se quer estacionar sozinho ou com manobrista
    decisao_estacionar = escolha_manobrista();

    switch (decisao_estacionar)
    {
    case 1:
        //Se dono do ve�clo recusar a sugest�o volto com estacionamento do jeito que estava antes
        estacionamento->fileiras[fileira_com_maior_num_vagas] = estacionamento->fileiras[fileira_com_maior_num_vagas]->prox;

        //Voltando com a  quantidade de vagas dispon�veis na fileira
        estacionamento->contador_carros[fileira_com_maior_num_vagas]++;

        //Libero espa�o do carro de demosntra��o
        free (veiculo_aux);

        fileira_escolhida = verifica_fileira(estacionamento);

        if (estacionamento->fileiras[fileira_escolhida - 1] == NULL)
        {
            estacionamento->fileiras[fileira_escolhida - 1] = novo_veiculo;
            //atualiza n�mero de vagas dispon�veis na fileira
            estacionamento->contador_carros[fileira_escolhida - 1]--;
        }
        else
        {
            novo_veiculo->prox = estacionamento->fileiras[fileira_escolhida - 1];
            estacionamento->fileiras[fileira_escolhida - 1] = novo_veiculo;
            //atualiza n�mero de vagas dispon�veis na fileira
            estacionamento->contador_carros[fileira_escolhida - 1]--;
        }

        break;

    case 2:

        printf("\n\tOl�, sou seu manobrista. Seu ve�culo est� em boas m�os!\n");

        //Volto com estacionamento do jeito que estava para estacionar o carro na vaga escolhida pelo programa
        estacionamento->fileiras[fileira_com_maior_num_vagas] = estacionamento->fileiras[fileira_com_maior_num_vagas]->prox;

        //Libero espa�o do carro de demosntra��o
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

    //Incrementa o contador de ve�culos do estacionamento
    estacionamento->numero_veiculos_total++;


    return estacionamento;
}

//Respons�vel por achar a melhor vaga que tiver dispon�vel para o ve�culo
//Leva em considera��o dois par�metros: Qual fileira tem mais vagas dispon�veis e se o carro j� estacionado na fileira tem o tempo de perman�ncia
//maior do que ser� estacionado
int heuristica_insercao (Estacionamento *estacionamento, Veiculo *novo)
{
    int i;
    int aux_contador_vagas = 0; // vai guardar a qtd de qual fileira tem mais vagas dispon�veis (se n�o achar nos primeiros par�metros)
    int fileira_com_maior_num_vagas = 0;//vai guardar a posi��o da fileira com maior num de vagas disponiveis
    int num; //N�mero rand�mico para escolher uma op��o entre um conjunto de melhores vagas
    int vet_melhor_vaga[TAM]; //Cada indice desse vetor, corresponde a uma fileira do estacionamento. Se a fileira na posi��o i for NULL esse vetor na i recebe
    // 1, se n�o recebe 0. Depois percorre as fileiras novamente para saber das fileiras que n�o s�o NULL se o tempo de pernamencia
    // do ve�culo atual � maior a do que ser� estacionado, se for, esse vetor anteriormente com 0 na posi��o i recebe 1. No final cada indice que tiver
    // 1 estar� representando uma boa op��o de vaga

    //Zerando cada posi��o do vetor para fazer as buscas
    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {
        vet_melhor_vaga[i] = 0;
    }

    //Primeira busca que vai ser feita � por fileiras vazias. Se a fileira for vazia o vetor melhor vaga no mesmo indice vai receber 1, que significa
    //que � uma boa op��o de vaga
    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {

        //Se a fileira estiver vazia, o vetor de mellhor vaga recebe 1
        if (estacionamento->fileiras[i] == NULL)
        {
            vet_melhor_vaga[i] = 1;
        }
    }

    //Segunda busca que vai ser feita verifica se as fileiras que ja tem algum ve�culo parado, o tempo desse ve�culo que j� est� la � maior do que o novo
    //ve�culo.
    //A quest�o do tempo pensada foi de um ve�culo 1 qualquer parar atras de um ve�culo 2 qualquer cujo tempo seja maior para dar tempo do ve�culo 1 sair sem acabar o tempo
    //do ve�culo 2 evitando manobras desnecess�rias
    for (i = 0; i < estacionamento->qtd_fileiras; i++)
    {

        // No indice do vetor que estiver 0, ele vai verificar se o tempo de permanencia do veiculo estacionado � maior do que a do novo
        if (vet_melhor_vaga[i] == 0)
        {
            //Verifica se a fileira tem vagas dispon�veis
            if (estacionamento->contador_carros[i] > 0)
            {
                if (estacionamento->fileiras[i]->tempo_permanencia >= novo->tempo_permanencia)
                {
                    vet_melhor_vaga[i] = 1;
                }
                //Se o tempo n�o atender o requisito, aux incrementa
                else
                {
                    aux_contador_vagas++;
                }

            }

            //Se a fileira n�o atendeu os parametros anteriores ela fica com 0, aqui faz uma contagem de quantas fileiras disponiveis para estacionar
            //foram encontradas. No final se essa contagem chegar at� o num de fileiras total do estacionamento, significa que nenhuma fileira foi encontrada
            // que atendesse os parametros anteriores.
            else
            {
                aux_contador_vagas++;
            }

        }

    }
    //Se o num do aux for == a qtd de fileiras, outro parametro � usado para encontrar uma melhor vaga
    if (aux_contador_vagas == estacionamento->qtd_fileiras)
    {
        //Aqui o aux � utilizado para guardar a qtd de vagas disponiveis em cada fileira
        aux_contador_vagas = 0;

        //Vai buscar a fileira com maior num de vagas dispon�veis
        for (i = 0; i < estacionamento->qtd_fileiras; i++)
        {
            if (estacionamento->contador_carros[i] > aux_contador_vagas)
            {
                aux_contador_vagas = estacionamento->contador_carros[i];

                fileira_com_maior_num_vagas = i;
            }
        }

        //Essa posi��o do vetor recebe 1 e vai ser a vaga onde ser� a sugest�o de melhor vaga
        vet_melhor_vaga[fileira_com_maior_num_vagas] = 1;

    }


    srand(time(NULL));
    //vai sortear uma posi��o dentre as melhores vagas dispon�veis
    do
    {
        num = rand() % TAM;

    }
    while (vet_melhor_vaga[num] != 1);//sorteia at� achar um num cujo indice do vetor tenha o 1 (que corresponde a uma boa op��o de fileira)

    return num;
}

//Pergunta a placa do ve�culo a ser retirado
char *insere_placa_retirar_veiculo ()
{
    char *placa_retirada;

    placa_retirada = (char *) malloc (sizeof(char));


    printf("\n\tEntre com a placa do seu ve�culo :");
    scanf("%s", placa_retirada);


    return placa_retirada;
}

//Faz a varredura no estacionamento para procurar o ve�culo
//Comparando as placas
//Devolve a fileira onde o ve�culo est� estacionado
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
            //Correndo as fileiras para encontrar o ve�culo
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

    printf("\n\tVe�culo n�o encontrado\n\tVerifique a placa e tente novamente.\n");

    return fileira;
}

//Manobrar os ve�culos para a retirada do ve�culo que estiver saindo
//Cada ve�culo manobrado ser� direcionado para uma outra melhor vaga dentro do estacionamento
//Se estacionamento estiver lotado, os ve�culos s�o direcionados para a rua
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

    printf("\n\t---------Informa��es para retirar o ve�culo---------\n");

    //Recebe a placa do ve�culo a ser retirado
    placa_retirada = insere_placa_retirar_veiculo();

    //Busca a fileira onde o ve�culo est�
    fileira = procura_veiculo(estacionamento, placa_retirada);

    //Se fileira for -1, n�o achou o ve�culo no estacionamento. Logo, n�o existe ve�culo com essa placa estacionado.
    //retorna estacionamento
    if (fileira == -1)
    {
        return estacionamento;
    }

    //Aux para buscar ve�culo na fileira
    aux = estacionamento->fileiras[fileira];

    //Enquanto n�o achar ve�culo com placa correspondente, faz todo o processo de manobrar, achar outra melhor vaga para ve�culo at� achar a placa do
    //ve�culo que ser� retirado
    while ( strcmp (aux->placa, placa_retirada) != 0 )
    {
        //Cria uma copia do ve�culo para manobrar, essa copia ser� inserida na nova fileira
        veiculo_copia = cria_veiculo ();

        //Copia a placa e tempo de perman�ncia para ve�culo copia
        strcpy(veiculo_copia->placa, aux->placa);
        veiculo_copia->tempo_permanencia = aux->tempo_permanencia;

        //Guarda o anterior para liberar espa�o alocado
        aux_retirado = aux;

        //aux vai para pr�ximo ve�culo da fileira
        aux = aux->prox;

        //Libera espa�o alocado
        free (aux_retirado);

        //atualiza a fileira
        estacionamento->fileiras[fileira] = aux;

        //Incrementa contador de vagas dispon�veis da fileira que ve�culo saiu (manobrado)
        estacionamento->contador_carros[fileira]++;

        //Verifica se estacionamento est� lotado
        //Se estiver lotado, insere os ve�culos necess�rios na rua
        if (estacionamento->numero_veiculos_total == estacionamento->qtd_fileiras * estacionamento->qtd_max_carros_por_fileira || estacionamento->qtd_fileiras == 1)
        {
            //testa se a rua est� vazia
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

        //Se estacionamento n�o estiver lotado, faz as manobras dentro mesmo
        else
        {

            //Procura a melhor vaga para ve�culo manobrado, sem ser a fileira original dele
            do
            {
                fileira_inserir_carro_manobrado = heuristica_insercao(estacionamento, veiculo_copia);

                //Quando a huristica acha a melhor vaga que seja na fileira que est� saindo os carros
                if (fileira_inserir_carro_manobrado == fileira)
                {
                    for (i = 0; i < estacionamento->qtd_fileiras; i++)
                    {
                        //Esse if vazio serve para pular a fileira aonde os ve�culos est�o saindo
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

        //Quando a chamada da fun��o vier com aux_retirada_sequencialda == 1, faz passo a passo printando na tela
        if (aux_retirada_sequenciada == 1)
        {
            system ("cls");

            imprime_estacionamento (estacionamento);

            system ("pause");
            system ("cls");
        }

    }

    //Aqui aux j� � o ve�culo a ser excluido, ent�o um outro aux recebe ele
    aux_retirado = aux;

    //Aux recebe seu prox, podendo ser outro ve�culo ou, se for o ultimo da fileira recebe NULL indicando fileira vazia
    aux = aux->prox;

    //Atualiza a fileira que teve seu ve�culo retirado
    estacionamento->fileiras[fileira] = aux;

    //Atualiza o num de vagas dispon�veis da fileira
    estacionamento->contador_carros[fileira]++;

    //Atualiza num de ve�culos total do estacionamento
    estacionamento->numero_veiculos_total--;

    //Libera espa�o alocado para ve�culo retirado
    free (aux_retirado);

    imprime_estacionamento (estacionamento);

    system ("pause");


    //Se a rua n�o estiver vazia, chama fun��o para esvaziar a rua
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

//Verifica se a rua tem algum ve�culo estacionado
//Se tiver, volta com os ve�culos para dentro do estacionamento
//usa a heuristica para achar a melhor vaga para voltar com os ve�culos
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

            //Cria uma copia do ve�culo para devolver para dentro do estacionamento
            veiculo_copia = cria_veiculo ();

            //Copia a placa e tempo de perman�ncia para ve�culo auxiliar
            strcpy(veiculo_copia->placa, aux->placa);
            veiculo_copia->tempo_permanencia = aux->tempo_permanencia;

            //Guarda o anterior para liberar espa�o alocado
            aux_retirado = aux;

            //aux vai para pr�ximo ve�culo da fileira
            aux = aux->prox;

            //Atualiza contador de ve�culos da rua
            estacionamento->contador_carros_rua++;

            //Atualiza a fileira da rua
            estacionamento->fileira_rua = aux;

            //Libera espa�o alocado
            free (aux_retirado);

            //Procura melhor fileira para devolver o ve�culo
            fileira_inserir_carro = heuristica_insercao (estacionamento, veiculo_copia);


            if (estacionamento->fileiras[fileira_inserir_carro] == NULL)
            {
                estacionamento->fileiras[fileira_inserir_carro] = veiculo_copia;

                //Decrementa a qtd de vagas dispon�veis para essa fileira
                estacionamento->contador_carros[fileira_inserir_carro]--;
            }
            else
            {
                veiculo_copia->prox = estacionamento->fileiras[fileira_inserir_carro];
                estacionamento->fileiras[fileira_inserir_carro] = veiculo_copia;

                //Decrementa a qtd de vagas dispon�veis para essa fileira
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
