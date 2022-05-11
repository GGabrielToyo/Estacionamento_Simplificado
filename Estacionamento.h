
#define TAM 10

typedef struct _veiculo
{
    char *placa;             // Ponteiro respons�lvel por apontar para a placa do carro
    struct _veiculo *prox;   // Ponteiro respons�vel por apontar par pr�ximo carro da pilha
    int tempo_permanencia; // Tempo de perman�ncia do carro em minutos

} Veiculo;


typedef struct _estacionamento
{
    int qtd_fileiras;               // Respons�vel pelo n�mero de fileiras do estacionamento
    int qtd_max_carros_por_fileira; // Respos�vel pelo n�mero de carros por fileira
    int qtd_max_carros_rua;         // Respos�vel pelo n�mero de carros na rua
    int contador_carros[TAM];       // Respons�vel por controlar a quantidade de carros em cada fileira
    int numero_veiculos_total;      // Respons�vel pelo n�mero total de ve�culos no estacionamento
    int contador_carros_rua;        // Respons�vel por controlar a quantidade de carros na rua
    Veiculo **fileiras;             // Respons�vel pelas fileiras de veiculos
    Veiculo *fileira_rua;           // Respons�vel pela fileira na rua


} Estacionamento;

//Aloca espa�o para estacionamento
Estacionamento * aloca_estacionamento ();

//Define n�mero de fileiras
//Define n�mero de carros em cada fileira
//Define n�mero de carros na rua
//Inicia contador de carros (dentro do estacionamento) com a qtd m�xima de carros por fileira
//Inicia contador de carros na rua com a qtd m�xima de carros na rua
Estacionamento *configurar_estacionamento (Estacionamento *estacionamento);

//Cria espa�o do estacionamento e da rua. De acordo com qtd de: fileiras, carros em cada fileira e carros na rua
//aloca espa�o para as fileiras
//Aloca espa�o para a rua
Estacionamento *cria_estacionamento (Estacionamento * estacionamento);

//Aloca espa�o para veiculo
//Aloca espa�o para placa
//Insere placa
//Insere tempo de pernan�ncia
//Pr�ximo recebe NULL
Veiculo *cria_veiculo ();

//Insere placa
//Veriica placa para saber se tem algum ve�culo com mesma placa estacionado
//Insere tempo de pernan�ncia
//Pr�ximo recebe NULL
Veiculo *Insere_dados_veiculo (Veiculo * novo_veiculo, Estacionamento *estacionamento);

//Recebe a escolha do dono do ve�culo se quer estacionar sozinho ou deixar com manobrista
int escolha_manobrista ();

//Informa vagas dispon�veis
//Recebe a escolha da fileira
int verifica_fileira (Estacionamento *estacionamento);

//Insere ve�culo no estacionamento de acordo com a escolha do dono do carro
//Se quiser estacionar sozinho, � perguntado qual fileira deseja estacionar
//Se quiser o manobrista, carro � estacionado na melhor escolha de vaga
Estacionamento *insere_veiculo (Estacionamento *estacionamento);

//Respons�vel por achar a melhor vaga que tiver dispon�vel para o ve�culo
//Leva em considera��o dois par�metros: Qual fileira tem mais vagas dispon�veis e se o carro j� estacionado na fileira tem o tempo de perman�ncia
//maior do que ser� estacionado
int heuristica_insercao (Estacionamento *estacionamento, Veiculo *novo);

//Pergunta a placa do ve�culo a ser retirado
char *insere_placa_retirar_veiculo ();

//Faz a varredura no estacionamento para procurar o ve�culo
//Comparando as placas
//Devolve a fileira onde o ve�culo est� estacionado
int procura_veiculo (Estacionamento *estacionamento, char *placa_retirada);

//Manobrar os ve�culos para a retirada do ve�culo que estiver saindo
//Cada ve�culo manobrado ser� direcionado para uma outra melhor vaga dentro do estacionamento
//Se estacionamento estiver lotado, os ve�culos s�o direcionados para a rua
Estacionamento *manobrar_e_retirar_veiculos (Estacionamento *estacionamento, int aux_retirada_sequenciada);

//Verifica se a rua tem algum ve�culo estacionado
//Se tiver, volta com os ve�culos para dentro do estacionamento
//usa a heuristica para achar a melhor vaga para voltar com os ve�culos
Estacionamento *esvazia_rua (Estacionamento *estacionamento, int aux_retirada_sequenciada);

void imprime_estacionamento (Estacionamento *estacionamento);

