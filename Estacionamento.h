
#define TAM 10

typedef struct _veiculo
{
    char *placa;             // Ponteiro responsálvel por apontar para a placa do carro
    struct _veiculo *prox;   // Ponteiro responsável por apontar par próximo carro da pilha
    int tempo_permanencia; // Tempo de permanência do carro em minutos

} Veiculo;


typedef struct _estacionamento
{
    int qtd_fileiras;               // Responsável pelo número de fileiras do estacionamento
    int qtd_max_carros_por_fileira; // Resposável pelo número de carros por fileira
    int qtd_max_carros_rua;         // Resposável pelo número de carros na rua
    int contador_carros[TAM];       // Responsável por controlar a quantidade de carros em cada fileira
    int numero_veiculos_total;      // Responsável pelo número total de veículos no estacionamento
    int contador_carros_rua;        // Responsável por controlar a quantidade de carros na rua
    Veiculo **fileiras;             // Responsável pelas fileiras de veiculos
    Veiculo *fileira_rua;           // Responsável pela fileira na rua


} Estacionamento;

//Aloca espaço para estacionamento
Estacionamento * aloca_estacionamento ();

//Define número de fileiras
//Define número de carros em cada fileira
//Define número de carros na rua
//Inicia contador de carros (dentro do estacionamento) com a qtd máxima de carros por fileira
//Inicia contador de carros na rua com a qtd máxima de carros na rua
Estacionamento *configurar_estacionamento (Estacionamento *estacionamento);

//Cria espaço do estacionamento e da rua. De acordo com qtd de: fileiras, carros em cada fileira e carros na rua
//aloca espaço para as fileiras
//Aloca espaço para a rua
Estacionamento *cria_estacionamento (Estacionamento * estacionamento);

//Aloca espaço para veiculo
//Aloca espaço para placa
//Insere placa
//Insere tempo de pernanência
//Próximo recebe NULL
Veiculo *cria_veiculo ();

//Insere placa
//Veriica placa para saber se tem algum veículo com mesma placa estacionado
//Insere tempo de pernanência
//Próximo recebe NULL
Veiculo *Insere_dados_veiculo (Veiculo * novo_veiculo, Estacionamento *estacionamento);

//Recebe a escolha do dono do veículo se quer estacionar sozinho ou deixar com manobrista
int escolha_manobrista ();

//Informa vagas disponíveis
//Recebe a escolha da fileira
int verifica_fileira (Estacionamento *estacionamento);

//Insere veículo no estacionamento de acordo com a escolha do dono do carro
//Se quiser estacionar sozinho, é perguntado qual fileira deseja estacionar
//Se quiser o manobrista, carro é estacionado na melhor escolha de vaga
Estacionamento *insere_veiculo (Estacionamento *estacionamento);

//Responsável por achar a melhor vaga que tiver disponível para o veículo
//Leva em consideração dois parâmetros: Qual fileira tem mais vagas disponíveis e se o carro já estacionado na fileira tem o tempo de permanência
//maior do que será estacionado
int heuristica_insercao (Estacionamento *estacionamento, Veiculo *novo);

//Pergunta a placa do veículo a ser retirado
char *insere_placa_retirar_veiculo ();

//Faz a varredura no estacionamento para procurar o veículo
//Comparando as placas
//Devolve a fileira onde o veículo está estacionado
int procura_veiculo (Estacionamento *estacionamento, char *placa_retirada);

//Manobrar os veículos para a retirada do veículo que estiver saindo
//Cada veículo manobrado será direcionado para uma outra melhor vaga dentro do estacionamento
//Se estacionamento estiver lotado, os veículos são direcionados para a rua
Estacionamento *manobrar_e_retirar_veiculos (Estacionamento *estacionamento, int aux_retirada_sequenciada);

//Verifica se a rua tem algum veículo estacionado
//Se tiver, volta com os veículos para dentro do estacionamento
//usa a heuristica para achar a melhor vaga para voltar com os veículos
Estacionamento *esvazia_rua (Estacionamento *estacionamento, int aux_retirada_sequenciada);

void imprime_estacionamento (Estacionamento *estacionamento);

