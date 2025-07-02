#include <iostream>
#include <cstring>

#include <math.h>

using namespace std;
class CentroDistribuicao // criação da classe CentroDistribuição, que seria a classe Local sugerida no enunciado do trabalho
{
public:
    double getOrigemX()
    {
        return coordenadaOrigem[0]; // getter para que seja possivel o retorno do atributo private Coordenada origem
    }
    double getOrigemY()
    {
        return coordenadaOrigem[1];
    }
    char *getNomeLocal() //
    {
        return nomeLocal; // getter para que seja possivel retornar para a string armazenada no objeto
    }
    void setNovoLocal(const char *novoLocal) // setter para que seja possivel realizar operaçoes com o atributo desejado
    {
        strncpy(nomeLocal, novoLocal, sizeof(nomeLocal) - 1); // usa strncpy pois estamos usando so as bibliotecas do C
        nomeLocal[sizeof(nomeLocal) - 1] = '\0';
    }
    CentroDistribuicao() // Contrutor sem parametros para os atributos da classe
    {
        coordenadaOrigem[0] = 0.0;
        coordenadaOrigem[1] = 0.0;
        strcpy(nomeLocal, "");
    }

    void exibirCentro() // funcao para que seja exibido as informaçoes da classe
    {
        cout << "Nome local: " << nomeLocal << endl;
        cout << "Coordenada X: " << coordenadaOrigem[0] << " Y: " << coordenadaOrigem[1] << endl;
    }
    void setCoordenadas(double x, double y) // setter para que seja possivel modificar as coordenadas
    {
        coordenadaOrigem[0] = x;
        coordenadaOrigem[1] = y;
    }

private: // atributos privados da classe
    double coordenadaOrigem[2];
    char nomeLocal[20];
};

void cadastrarCentro(CentroDistribuicao *centros[], int &quantidade) // funcao para cadastrar o centro, recebe um vetor de ponteiros para centros, recebe a quantidade atual de centros cadastrados pelo main
{
    if (quantidade >= 100) // um limitador para que o programe nao armazene mais que 100 centros
    {
        cout << "Limite de centros atingido.\n";
        return;
    }

    char nome[20]; // variavel para os nomes terem ate 20 caracteres
    double x, y;

    // interaçoes com o usuario
    cout << "Digite o nome do centro: ";
    cin >> nome;

    // verifica se o nome digitado é apenas numerico
    bool apenasNumeros = true;
    for (int i = 0; nome[i] != '\0'; i++)
    {
        if (!isdigit(nome[i]))
        {
            apenasNumeros = false;
            break;
        }
    }
    if (apenasNumeros)
    {
        cout << "Erro: O nome do centro nao pode ser apenas numeros.\n";
        return;
    }
    

    cout << "Digite a coordenada X: ";
    cin >> x;

    cout << "Digite a coordenada Y: ";
    cin >> y;

    // verifica se ja existe centro com mesmo nome ou coordenadas
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(centros[i]->getNomeLocal(), nome) == 0)
        {
            cout << "Erro: Ja existe um centro com esse nome.\n";
            return;
        }
        if (centros[i]->getOrigemX() == x && centros[i]->getOrigemY() == y)
        {
            cout << "Erro: Ja existe um centro com essas coordenadas.\n";
            return;
        }
    }

    CentroDistribuicao *novoCentro = new CentroDistribuicao(); // cria um novo centro dinamicamente
    novoCentro->setNovoLocal(nome);                            // define o nome do novo centro de distribuição usando o valor digitado pelo usuário

    novoCentro->setCoordenadas(x, y); // Define as coordenadas do novo centro de distribuição usando o valor digitado pelo usuário

    centros[quantidade] = novoCentro; // armazena o ponteiro do novo centro no vetor
    quantidade++;                     // incrementa a quantidade total de centros cadastrados

    cout << "Centro cadastrado com sucesso.\n";
}


void listarCentros(CentroDistribuicao *centros[], int quantidade) // função para listar os centros ja cadastrados, recebe os mesmo parametros tirando o quantidade pois aqui ja nao tera alteraçoes na quantidade existente
{
    if (quantidade == 0) // verificar se a quantidade nao esta vazia
    {
        cout << "Nenhum centro cadastrado.\n";
        return;
    }

    for (int i = 0; i < quantidade; i++) // laço para mostrar todos os centros cadastrados
    {
        cout << "Centro [" << i + 1 << "]\n";
        centros[i]->exibirCentro();
    }
}

void excluirCentro(CentroDistribuicao *centros[], int &quantidade) // funcao para excluir o centro desejado
{

    char nomeProcurado[20];
    cout << "Digite o nome do centro que deseja excluir: ";
    cin >> nomeProcurado;

    for (int i = 0; i < quantidade; i++) // loop para realizar a operacao de excluir
    {
        if (strcmp(centros[i]->getNomeLocal(), nomeProcurado) == 0) // compara se o nome digitado pelo usuario é existente
        {
            delete centros[i]; // deletar centro
            for (int j = i; j < quantidade - 1; j++)
            {
                centros[j] = centros[j + 1]; // apos remover o centro na posição i, move os centros seguintes uma posição para trás
            }
            quantidade--; // decrementa a quantidade
            cout << "Centro removido com sucesso.\n";
            return;
        }
    }
    cout << "Centro com nome \"" << nomeProcurado << "\" nao encontrado.\n"; // se nao atender ao if, exibe essa mensagem
}

void atualizarCentro(CentroDistribuicao *centros[], int quantidade) // funcao para atualizar o centro
{
    char nomeProcurado[20];

    cout << "Digite o nome do centro que deseja atualizar: ";
    cin >> nomeProcurado;

    for (int i = 0; i < quantidade; i++) // loop para realizar a operacao de atualizar
    {
        if (strcmp(centros[i]->getNomeLocal(), nomeProcurado) == 0) // compara se o nome digitado pelo usuario é existente
        {
            char novoNome[20];
            cout << "Digite o novo nome do centro: ";
            cin >> novoNome;
            centros[i]->setNovoLocal(novoNome);
            cout << "Centro atualizado com sucesso.\n";
            return;
        }
    }

    cout << "Centro com nome \"" << nomeProcurado << "\" nao encontrado.\n"; // se nao atender ao if, exibe essa mensagem
}

class Veiculo // criação da classe veiculo
{
public:
    CentroDistribuicao *getLocalAtual() // retorna um ponteiro para o centro de distribuição atual onde o veículo está localizado
    {
        return localAtual;
    }
    void setLocalAtual(CentroDistribuicao *novoLocal) // define o centro de distribuição atual do veículo
    {
        localAtual = novoLocal;
    }
    bool getStatus() // retorna o status do veiculo
    {
        return status;
    }
    char *getPlaca() // retorna a placa do veiculo
    {
        return placa;
    }
    void setPlacaNova(char *placaNova) // define a nova placa do veiculo
    {
        strncpy(placa, placaNova, sizeof(placa) - 1);
        placa[sizeof(placa) - 1] = '\0';
    }
    char *getModelo() // retorna o modelo do veiculo
    {
        return modelo;
    }
    void setModelo(const char *modeloNovo) // define o novo modelo do veiculo
    {
        strncpy(modelo, modeloNovo, sizeof(modelo) - 1);
        modelo[sizeof(modelo) - 1] = '\0';
    }
    Veiculo() // construtor da classe
    {
        status = false;
        localAtual = nullptr;
        strcpy(placa, "");
        strcpy(modelo, "");
    }

    void exibirVeiculo() // função para exibir as informaçoes do veiculo
    {
        cout << "Placa: " << getPlaca() << endl;
        cout << "Modelo: " << getModelo() << endl;
        if (this->status == 0) // verificar se o veiculo esta ocupado
        {
            cout << "Status: Livre" << endl;
        }
        else
        {
            cout << "Status: Ocupado" << endl;
        }

        if (localAtual != nullptr) // funcao para mostrar a localizaçao atual
        {
            cout << "Localizacao: " << localAtual->getNomeLocal()
                 << " (" << localAtual->getOrigemX()
                 << ", " << localAtual->getOrigemY() << ")" << endl;
        }
        else
        {
            cout << "Localizacao: N/A\n";
        }
    }
    void iniciarEntrega() { this->status = 1; }        // funcao de iniciar entrega, se o usuario acionar ela, o status do veiculo que esta em uso altera para 1
    void finalizarEntrega(CentroDistribuicao *destino) // funcao para finalizar, que quando interagida o status atualiza para false e seta o local que o veiculo esta para o destino da entrega, como foi solicitado
    {
        this->status = false;
        this->setLocalAtual(destino);
    }

private:
    CentroDistribuicao *localAtual;
    bool status;
    char placa[20];
    char modelo[20];
};

void cadastrarVeiculo(Veiculo *veiculos[], int &quantidade, CentroDistribuicao *centros[], int qtdCentros) // funcao para cadastrar o veiculo
{
    if (quantidade >= 100) // limitador de veiculo
    {
        cout << "Limite de veiculos atingido.\n";
        return;
    }

    if (qtdCentros == 0) // verificar se os centros estao vazios caso o usuario chame sem um centro
    {
        cout << "Nenhum centro de distribuicao cadastrado. Cadastre um centro antes de adicionar veiculos.\n";
        return;
    }

    char placa[20], modelo[20];

    cout << "Digite a placa do veiculo: ";
    cin >> placa;

    cout << "Digite o modelo do veiculo: ";
    cin >> modelo;

    cout << "\nCentros de distribuicao disponiveis:\n";
    for (int i = 0; i < qtdCentros; i++) // loop para exibir os centros existentes
    {
        cout << i + 1 << ". ";
        centros[i]->exibirCentro();
    }

    int opcaoCentro;
    cout << "Escolha o numero do centro onde o veiculo esta: ";
    cin >> opcaoCentro;

    if (opcaoCentro < 1 || opcaoCentro > qtdCentros) // verificar se a opcao digitada pelo o usuario é valida
    {
        cout << "Opcao invalida. Veiculo nao cadastrado.\n";
        return;
    }

    // armazenar as novas informaçoes dentro de vetor de veiculos
    veiculos[quantidade] = new Veiculo();
    veiculos[quantidade]->setPlacaNova(placa);
    veiculos[quantidade]->setModelo(modelo);
    veiculos[quantidade]->setLocalAtual(centros[opcaoCentro - 1]);

    quantidade++; // incrementar a quantidade de veiculos

    cout << "Veiculo cadastrado com sucesso.\n";
}

void atualizarVeiculo(Veiculo *veiculos[], int quantidade) // funcao para atualizar os veiculos
{
    char placaProcurada[20];

    cout << "Digite a placa do veiculo que voce deseja atualizar: ";
    cin >> placaProcurada;
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(veiculos[i]->getPlaca(), placaProcurada) == 0) // caso a placa digitada seja existente entra nesse if
        {
            cout << "Nova placa: ";
            char novaPlaca[20];
            cin >> novaPlaca;
            veiculos[i]->setPlacaNova(novaPlaca);
            cout << "Placa atualizada com sucesso.\n";
            return;
        }
    }
    cout << "Veiculo placa " << placaProcurada << " nao encontrado.\n"; // senao cai para essa mensagem
}

void excluirVeiculo(Veiculo *veiculos[], int &quantidade) // funcao para excluir um veiculo
{
    char placaProcurada[20];

    cout << "Digite a placa do veiculo que voce deseja atualizar: ";
    cin >> placaProcurada;
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(veiculos[i]->getPlaca(), placaProcurada) == 0) // caso a placa digitada seja existente entra nesse if
        {
            delete veiculos[i];
            for (int j = i; j < quantidade - 1; j++)
            {
                veiculos[j] = veiculos[j + 1];
            }
            quantidade--;
            cout << "Veiculo removido com sucesso.\n";
            return;
        }
    }
    cout << "Veiculo nao encontrado.\n";
}

void listarVeiculos(Veiculo *veiculos[], int quantidade) // funcao para listar os veiculos
{
    if (quantidade == 0) // se quantidade for igual a 0 imprime a mensagem
    {
        cout << "Nenhum veiculo cadastrado.\n";
        return;
    }

    for (int i = 0; i < quantidade; i++) // senao exibe todos veiculos
    {
        veiculos[i]->exibirVeiculo();
    }
}

class Pedido // criação da classe pedido
{
public:
    Pedido() // construtor
    {
        coordenadaDestino[0] = 0.0;
        coordenadaDestino[1] = 0.0;
        strcpy(idUnico, "");
        pesoDoItem = 0.0;
    }
    const char *getIdUnico() const // retornar o id unico
    {
        return idUnico;
    }

    double getDestinoX() const // retornar as coordenadas de destino
    {
        return coordenadaDestino[0];
    }

    double getDestinoY() const
    {
        return coordenadaDestino[1];
    }

    double getPeso() const // retornar o peso do item
    {
        return pesoDoItem;
    }

    void setIdUnico(const char *novoId) // definir um novo id
    {
        strncpy(idUnico, novoId, sizeof(idUnico) - 1);
        idUnico[sizeof(idUnico) - 1] = '\0';
    }

    void setDestino(double x, double y) // definir um destino
    {
        coordenadaDestino[0] = x;
        coordenadaDestino[1] = y;
    }
    void setDestinoCentro(CentroDistribuicao *centro) // definir um centro
    {
        destino = centro;
        setDestino(centro->getOrigemX(), centro->getOrigemY());
    }

    void setPeso(double novoPeso) // definir um novo peso
    {
        pesoDoItem = novoPeso;
    }
    CentroDistribuicao *getOrigem() const // retornar a origem do centro
    {
        return origem;
    }
    CentroDistribuicao *getDestinoCentro() const { return destino; } // retornar o destino do centro

    void setOrigem(CentroDistribuicao *novoCentro) // definir um novo centro
    {
        origem = novoCentro;
    }

    Veiculo *AcharVeiculoMaisProximo(Veiculo *veiculos[], int quantidade) // funcao para calcular qual veiculo esta mais proximo de um centro
    {
        double distanciaMinima = 999999.9;
        Veiculo *veiculoMaisProximo = nullptr;

        for (int i = 0; i < quantidade; i++)
        {
            Veiculo *veiculo = veiculos[i];

            // ignora veículos ocupados
            if (!veiculo->getStatus())
            {
                CentroDistribuicao *localVeiculo = veiculo->getLocalAtual();

                // verifica se o local atual está definido
                if (localVeiculo == nullptr)
                    continue;

                double distanciaCalculada = calcularDistanciaEntreDoisPontos( // Calcula a distância entre o destino do pedido e a posição atual do veículo
                    coordenadaDestino[0], coordenadaDestino[1], // coordenadas do destino do pedido
                    localVeiculo->getOrigemX(), localVeiculo->getOrigemY()); // coordenadas de onde o veiculo esta 

                if (distanciaCalculada < distanciaMinima) // se a distância calculada for menor que a menor distância encontrada 
                {
                    distanciaMinima = distanciaCalculada; // atualiza a menor distância
                    veiculoMaisProximo = veiculo; // guarda o ponteiro para o veículo mais próximo
                    this->veiculoMaisProximo = veiculo; // associa o veículo ao pedido para uso posterior
                }
            }
        }

        return veiculoMaisProximo; // retorno do resultado
    }
    Veiculo *getVeiculoMaisProximo()
    {
        return veiculoMaisProximo; // retorna o veiculo mais proximo
    }
    void exibirPedido() // funcao para exibir o pedido 
    {
        cout << "-------------------------------\n";
        cout << "ID do Pedido: " << getIdUnico() << endl;

        if (origem != nullptr) // se origem nao for vazio 
        {
            cout << "Origem: " << origem->getNomeLocal()
                 << " (" << origem->getOrigemX()
                 << ", " << origem->getOrigemY() << ")\n";
        }

        if (destino != nullptr)  // se destino nao for vazio 
        {
            cout << "Destino: " << destino->getNomeLocal()
                 << " (" << getDestinoX()
                 << ", " << getDestinoY() << ")\n";
        }

        cout << "Peso: " << getPeso() << " kg\n";
        cout << "-------------------------------\n";
    }

    void atualizarPedido(Pedido *pedidos[], int quantidade) // funcao para atualizar o pedido 
    {
        char idProcurado[20];

        cout << "Digite o ID do pedido que deseja atualizar: ";
        cin >> idProcurado;

        for (int i = 0; i < quantidade; i++)
        {
            if (strcmp(pedidos[i]->getIdUnico(), idProcurado) == 0) // confere se o id digitado é existente 
            {
                double novoPeso, novoX, novoY;
                cout << "Digite o novo peso do item: ";
                cin >> novoPeso;

                cout << "Digite as novas coordenadas de destino (X e Y): ";
                cin >> novoX >> novoY;

                pedidos[i]->setPeso(novoPeso); // defini um novo peso 
                pedidos[i]->setDestino(novoX, novoY); // defini um novo destino

                cout << "Pedido atualizado com sucesso.\n";
                return;
            }
        }

        cout << "Pedido com ID \"" << idProcurado << "\" nao encontrado.\n";
    }

private:
    double coordenadaDestino[2];
    char idUnico[20];
    double pesoDoItem;
    CentroDistribuicao *origem; // ponteiro para o centro de distribuição de origem do pedido
    CentroDistribuicao *destino; // ponteiro para o centro de distribuição de destino do pedido
    Veiculo *veiculoMaisProximo; // ponteiro para o veículo mais próximo, atribuído após simulação
    double calcularDistanciaEntreDoisPontos(double x1, double y1, double x2, double y2) { return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); } // funcao que usa a distancia euclidiana para calcular 
    void acharCentroDeDistribuicaoMaisProximo(CentroDistribuicao *centros[], int quantidade) // funcao para achar o centroMaisProximo
    {
        double distanciaMinima = 999999.9; // usa-se um valor alto para garantir que qualquer distância real será menor
        CentroDistribuicao *centroDeDistribuicaoMaisProximo = nullptr; // ponteiro que vai armazenar o centro de distribuição mais próximo.
// começa com nullptr (nenhum centro selecionado ainda)
        for (int i = 0; i < quantidade; i++) // loop que percorre todos os centros disponiveis
        {
            CentroDistribuicao *centro = centros[i]; // ponteiro para o centro de distribuição atual do vetor
            double distanciaCalculada = calcularDistanciaEntreDoisPontos(coordenadaDestino[0], coordenadaDestino[1], centro->getOrigemX(), centro->getOrigemY()); // calcula as distancias com as coordenadas de destino e usa origem para obter os centros atuais

            if (distanciaCalculada < distanciaMinima) // se a distancia calculada for menor que a menor distância conhecida até agora,
    // atualiza a menor distância e armazena este centro como o mais próximo  
            {
                distanciaMinima = distanciaCalculada;
                centroDeDistribuicaoMaisProximo = centro;
            }
        }
        origem = centroDeDistribuicaoMaisProximo; // define origem com o resultado do calculo 
    }
};

void criarPedido(Pedido *pedidos[], int &quantidade, CentroDistribuicao *centros[], int qtdCentros) // funcao para criar pedido
{
    if (quantidade >= 100) //limitador de pedidos
    {
        cout << "Limite de pedidos atingido.\n";
        return;
    }
    if (qtdCentros == 0) // verificador de centros cadastrados ou nao
    {
        cout << "Nenhum centro cadastrado. Cadastre um centro primeiro.\n";
        return;
    }

    Pedido *novoPedido = new Pedido(); // cria dinamicamente um novo pedido 

    char id[20];
    double peso;

    cout << "Digite o ID do pedido: ";
    cin >> id;

    // escolher centro de origem
    cout << "\nCentros de distribuicao disponiveis:\n";
    for (int i = 0; i < qtdCentros; i++)
    {
        cout << i + 1 << ". ";
        centros[i]->exibirCentro();
    }

    int opcaoOrigem;
    cout << "Escolha o numero do centro de ORIGEM: ";
    cin >> opcaoOrigem;

    if (opcaoOrigem < 1 || opcaoOrigem > qtdCentros) // verifica se as opcoes digitadas sao validas
    {
        cout << "Opcao invalida. Pedido cancelado.\n";
        delete novoPedido;
        return;
    }

    CentroDistribuicao *centroOrigem = centros[opcaoOrigem - 1]; // centroOrigem recebe o ponteiro para o centro de distribuição escolhido pelo usuário
    novoPedido->setOrigem(centroOrigem); // define esse centro como a origem do novo pedido 

    // escolher centro de destino
    int opcaoDestino;
    cout << "Escolha o numero do centro de DESTINO: ";
    cin >> opcaoDestino;

    if (opcaoDestino < 1 || opcaoDestino > qtdCentros) // verificar a opcao é valida ou nao
    {
        cout << "Opcao invalida. Pedido cancelado.\n";
        delete novoPedido;
        return;
    }

    CentroDistribuicao *centroDestino = centros[opcaoDestino - 1]; // centroDestino recebe o ponteiro para o centro de distribuição escolhido pelo usuário

    if (centroOrigem == centroDestino) // verifica se origem é igual ao destino

    {
        cout << "Origem e destino nao podem ser o mesmo centro.\n";
        delete novoPedido;
        return;
    }

    novoPedido->setDestinoCentro(centroDestino); // define o destino para esse pedido 

    cout << "Digite o peso do item: ";
    cin >> peso;

    novoPedido->setIdUnico(id); // define o id para o pedido 
    novoPedido->setPeso(peso); // define o peso para o pedido 

    pedidos[quantidade] = novoPedido; // armazena dentro do vetor o novo pedido 
    quantidade++; // incrementa a quantidade 

    cout << "Pedido criado com sucesso.\n";
}

void excluirPedido(Pedido *pedidos[], int &quantidade) // funcao para excluir um pedido
{
    if (quantidade == 0) // verificar a quantidade 
    {
        cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    char idProcurado[20];
    cout << "Digite o ID do pedido que deseja excluir: ";
    cin >> idProcurado;

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(pedidos[i]->getIdUnico(), idProcurado) == 0) // verifica se o pedido é existente, se sim entra dentro do if
        {
            delete pedidos[i];

            for (int j = i; j < quantidade - 1; j++)
            {
                pedidos[j] = pedidos[j + 1];
            }

            quantidade--;
            cout << "Pedido removido com sucesso.\n";
            return;
        }
    }

    cout << "Pedido com ID \"" << idProcurado << "\" nao encontrado.\n"; // senao apresenta essa mensagem 
}

void listarPedido(Pedido *pedidos[], int quantidade) // funcao para listar pedido
{
    if (quantidade == 0) // verifica a quantidade
    {
        cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    for (int i = 0; i < quantidade; i++) //loop para exibir os pedidos
    {
        cout << "Pedido [" << i + 1 << "]\n";
        pedidos[i]->exibirPedido();
    }
}
void simularEntrega(Pedido *pedidos[], int qtdPedidos, Veiculo *veiculos[], int qtdVeiculos) // funcao para simular a entrega
{
    if (qtdPedidos == 0) // verifica a quantidade de pedidos
    {
        cout << "Nenhum pedido cadastrado!" << endl; 
        return;
    }

    char id[20];
    cout << "Digite o id do pedido a ser simulado: ";
    cin >> id;

    Pedido *pedidoSelecionado = nullptr; // comeca com o pedidoSelecionado vazio 
    for (int i = 0; i < qtdPedidos; i++)
    {
        if (strcmp(pedidos[i]->getIdUnico(), id) == 0) // compara se o digitado é existente
        {
            pedidoSelecionado = pedidos[i]; // atualiza o pedido selecinada para o pedido[i]
            break;
        }
    }

    if (pedidoSelecionado == nullptr) // caso pedido ficar vazio ainda
    {
        cout << "Nenhum pedido encontrado.\n";
        return;
    }

    Veiculo *veiculo = pedidoSelecionado->AcharVeiculoMaisProximo(veiculos, qtdVeiculos); // ponteiro veiculo e vai armazenar a referência do veículo mais próximo 

    if (veiculo == nullptr) // se tiver vazio entra no if
    {
        cout << "Nenhum veiculo disponivel encontrado.\n";
        return;
    }

    cout << "Simulacaoo realizada com sucesso." << endl;
    cout << "Veiculo mais próximo: " << veiculo->getPlaca() << " no centro " << veiculo->getLocalAtual()->getNomeLocal() << endl;
    cout << "Destino do pedido: " << pedidoSelecionado->getDestinoCentro()->getNomeLocal() << endl;
}

void iniciarEntregaManual(Pedido *pedidos[], int qtdPedidos, Veiculo *veiculos[], int qtdVeiculos) // funcao de iniciar entrega
{
    if (qtdPedidos == 0) // verificador de pedidos
    {
        cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    char id[20];
    cout << "Digite o ID do pedido que deseja entregar: ";
    cin >> id;

    Pedido *pedidoSelecionado = nullptr;
    for (int i = 0; i < qtdPedidos; i++) // compara para ver se o pedido selecionado é existente 
    {
        if (strcmp(pedidos[i]->getIdUnico(), id) == 0)
        {
            pedidoSelecionado = pedidos[i];
            break;
        }
    }

    if (pedidoSelecionado == nullptr)
    {
        cout << "Pedido nao encontrado.\n";
        return;
    }

    Veiculo *veiculo = pedidoSelecionado->AcharVeiculoMaisProximo(veiculos, qtdVeiculos); // vai armazenar a referência do veículo mais próximo.

    if (veiculo == nullptr)
    {
        cout << "Nenhum veiculo disponivel para realizar a entrega.\n";
        return;
    }

    veiculo->iniciarEntrega();
    cout << "Entrega iniciada com sucesso!\n";
    cout << "Veiculo " << veiculo->getPlaca() << " realizara a entrega para o destino: "
         << pedidoSelecionado->getDestinoCentro()->getNomeLocal() << endl;
}

void finalizarEntregaManual(Pedido *pedidos[], int qtdPedidos, Veiculo *veiculos[], int qtdVeiculos) // funcao para finalizar a entrega
{
    if (qtdPedidos == 0) // verificar os pedidos
    {
        cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    char id[20];
    cout << "Digite o ID do pedido entregue: ";

    cin >> id;

    Pedido *pedidoSelecionado = nullptr;
    for (int i = 0; i < qtdPedidos; i++)
    {
        if (strcmp(pedidos[i]->getIdUnico(), id) == 0) // compara para ver se o id selecionado é existente 
        {
            pedidoSelecionado = pedidos[i]; 
            break;
        }
    }

    if (pedidoSelecionado == nullptr)
    {
        cout << "Pedido nao encontrado.\n";
        return;
    }

    Veiculo *veiculo = pedidoSelecionado->getVeiculoMaisProximo(); // vai armazenar a referência do veículo mais próximo.

    if (veiculo == nullptr || !veiculo->getStatus())
    {
        cout << "Veiculo nao encontrado ou nao esta em entrega.\n";
        return;
    }

    veiculo->finalizarEntrega(pedidoSelecionado->getDestinoCentro()); // chama a funcao finalizar entrega assim que acaba

    cout << "Entrega finalizada com sucesso.\n";
    cout << "Veiculo " << veiculo->getPlaca() << " agora esta disponivel no centro "
         << pedidoSelecionado->getDestinoCentro()->getNomeLocal() << endl;
}
void fazerBackup(Veiculo *veiculos[], int qtdVeiculos, CentroDistribuicao *centros[], int qtdCentros, Pedido *pedidos[], int qtdPedidos)
{
    // backup dos centros
    FILE *arqCentro = fopen("centros.bin", "wb"); // cria e escreve dentro do arquivo centros.bin
    fwrite(&qtdCentros, sizeof(int), 1, arqCentro); // escreve no arquivo binário arqCentro a quantidade total de centros de distribuição (qtdCentros)
    for (int i = 0; i < qtdCentros; i++)
    {
        fwrite(centros[i], sizeof(CentroDistribuicao), 1, arqCentro); // escreve e salva, um por um, todos os centros de distribuição no arquivo binário arqCentro.
    }
    fclose(arqCentro); // fecha o arqCentro

    // backup dos veículos
    FILE *arqVeiculo = fopen("veiculos.bin", "wb"); // cria e escreve o arquivo veiculos bin no modo escrita 
    fwrite(&qtdVeiculos, sizeof(int), 1, arqVeiculo); // escreve no arquivo binário arqVeiculo a quantidade total de veiculos
    for (int i = 0; i < qtdVeiculos; i++)
    {
        fwrite(veiculos[i], sizeof(Veiculo), 1, arqVeiculo); // escreve e salva, um por um, todos os veiculos no arqVeiculo

        // salvar o índice do centro onde o veículo está
        for (int j = 0; j < qtdCentros; j++)
        {
            if (veiculos[i]->getLocalAtual() == centros[j])
            {
                fwrite(&j, sizeof(int), 1, arqVeiculo);
                break;
            }
        }
    }
    fclose(arqVeiculo); // fecha o arqVeiculo

    // backup dos pedidos
    FILE *arqPedido = fopen("pedidos.bin", "wb");  // cria e escreve dentro do arquivo pedidos.bin
    fwrite(&qtdPedidos, sizeof(int), 1, arqPedido); // escreve e salva no arquivo binário a quantidade total de pedidos
    for (int i = 0; i < qtdPedidos; i++)
    {
        fwrite(pedidos[i], sizeof(Pedido), 1, arqPedido); // escreve e salva, um por um, todos os veiculos no arqVeiculo

        int origemIndex = -1, destinoIndex = -1; // inicializa os índices de origem e destino como -1
        for (int j = 0; j < qtdCentros; j++)
        {
            if (pedidos[i]->getOrigem() == centros[j])  // compara o ponteiro do centro de origem do pedido com cada centro no vetor
    // se for igual, armazena o índice correspondente
                origemIndex = j;
            if (pedidos[i]->getDestinoCentro() == centros[j]) // faz o mesmo para o centro de destino do pedido
                destinoIndex = j;
        }
        fwrite(&origemIndex, sizeof(int), 1, arqPedido); // escreve o índice do centro de origem no arquivo binário
        fwrite(&destinoIndex, sizeof(int), 1, arqPedido);  // escreve o índice do centro de destino no arquivo binário
    }
    fclose(arqPedido);

    cout << "Backup concluido com sucesso!\n";
}
void restaurarBackup(Veiculo *veiculos[], int &qtdVeiculos, CentroDistribuicao *centros[], int &qtdCentros, Pedido *pedidos[], int &qtdPedidos) // cria a funcao para restaurar backup
{
    // restaurar centros
    FILE *arqCentro = fopen("centros.bin", "rb"); // abre para leitura o centros.bin
    if (!arqCentro) // se arquivo nao existe 
    {
        cout << "Arquivo de centros nao encontrado.\n";
        return;
    }

    fread(&qtdCentros, sizeof(int), 1, arqCentro); // le a quantidade centros que existem um por um
    for (int i = 0; i < qtdCentros; i++)
    {
        centros[i] = new CentroDistribuicao(); // aloca dinamicamente memória para um novo objeto CentroDistribuicao
        fread(centros[i], sizeof(CentroDistribuicao), 1, arqCentro); // le os dados binários salvos no arquivo diretamente para o objeto recém-alocado
    }
    fclose(arqCentro); // fecha o arquivo

    // restaurar veículos
    FILE *arqVeiculo = fopen("veiculos.bin", "rb"); // abre para leitura o veiculos.bin
    fread(&qtdVeiculos, sizeof(int), 1, arqVeiculo); // le a quantidade de veiculos que existem um por um
    for (int i = 0; i < qtdVeiculos; i++)
    {
        veiculos[i] = new Veiculo(); // aloca dinamicamente memória para um novo objeto
        fread(veiculos[i], sizeof(Veiculo), 1, arqVeiculo); // le os dados binários salvos no arquivo diretamente para o objeto 

        int centroIndex;
        fread(&centroIndex, sizeof(int), 1, arqVeiculo); // lê do arquivo o índice do centro de distribuição associado ao veículo
        if (centroIndex >= 0 && centroIndex < qtdCentros) // verifica se o índice lido é válido
        {
            veiculos[i]->setLocalAtual(centros[centroIndex]);   // associa o ponteiro do centro correspondente ao veículo.
        }
    }
    fclose(arqVeiculo); // fecha o arq veiculo

    // restaurar pedidos
    FILE *arqPedido = fopen("pedidos.bin", "rb"); // abre para leitura o pedidos.bin
    fread(&qtdPedidos, sizeof(int), 1, arqPedido);  // le a quantidade de veiculos que existem um por um
    for (int i = 0; i < qtdPedidos; i++)
    { 
        pedidos[i] = new Pedido();// aloca dinamicamente memória para um novo objeto
        fread(pedidos[i], sizeof(Pedido), 1, arqPedido);// le os dados binários salvos no arquivo diretamente para o objeto

        int origemIndex, destinoIndex;
        fread(&origemIndex, sizeof(int), 1, arqPedido);// lê do arquivo o índice  associado ao pedido
        fread(&destinoIndex, sizeof(int), 1, arqPedido);// lê do arquivo o índice  associado ao pedido

        if (origemIndex >= 0 && origemIndex < qtdCentros) // verifica se o índice lido é válido
            pedidos[i]->setOrigem(centros[origemIndex]);  // associa o ponteiro do centro correspondente ao pedido.
        if (destinoIndex >= 0 && destinoIndex < qtdCentros)
            pedidos[i]->setDestinoCentro(centros[destinoIndex]); // associa o ponteiro do centro correspondente ao pedido.
    }
    fclose(arqPedido); // fecha 

    cout << "Backup restaurado com sucesso!\n";
}

int main()
{
    Veiculo *veiculos[100]; // cria um vetor de ponteiros com o tipo veiculo
    CentroDistribuicao *centros[100]; // cria um vetor de ponteiros com o tipo centro
    Pedido *pedidos[100]; // cria um vetor de ponteiros com o tipo pedido
    int qtdVeiculos = 0, qtdCentros = 0, qtdPedidos = 0; // inicializa as variaveis com 0 para nao terem lixos
    restaurarBackup(veiculos, qtdVeiculos, centros, qtdCentros, pedidos, qtdPedidos); // ja chama a funcao restaurar backup no inicio caso ja existir informaçoes ja dentro dele, ja conseguem ser usadas

    int opcao;
    // MENU
    do
    {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Cadastrar Veiculo" << endl;
        cout << "2. Atualizar Veiculo" << endl;
        cout << "3. Excluir Veiculo" << endl;
        cout << "4. Listar Veiculos" << endl;
        cout << "5. Cadastrar Centro" << endl;
        cout << "6. Atualizar Centro" << endl;
        cout << "7. Excluir Centro" << endl;
        cout << "8. Listar Centros" << endl;
        cout << "9. Criar Pedido" << endl;
        cout << "10. Atualizar Pedido" << endl;
        cout << "11. Excluir Pedido" << endl;
        cout << "12. Listar Pedidos" << endl;
        cout << "13. Simular Entrega" << endl;
        cout << "14. Iniciar Entrega Manualmente" << endl;
        cout << "15. Finalizar Entrega Manualmente" << endl;

        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        // opcoes do menu
        switch (opcao)
        {
        case 1:
            cadastrarVeiculo(veiculos, qtdVeiculos, centros, qtdCentros);
            break;
        case 2:
            atualizarVeiculo(veiculos, qtdVeiculos);
            break;
        case 3:
            excluirVeiculo(veiculos, qtdVeiculos);
            break;
        case 4:
            listarVeiculos(veiculos, qtdVeiculos);
            break;
        case 5:
            cadastrarCentro(centros, qtdCentros);
            break;
        case 6:
            atualizarCentro(centros, qtdCentros);
            break;
        case 7:
            excluirCentro(centros, qtdCentros);
            break;
        case 8:
            listarCentros(centros, qtdCentros);
            break;
        case 9:
            criarPedido(pedidos, qtdPedidos, centros, qtdCentros);
            break;
        case 10:
        {
            Pedido p;
            p.atualizarPedido(pedidos, qtdPedidos);
            break;
        }
        case 11:
            excluirPedido(pedidos, qtdPedidos);
            break;
        case 12:
            listarPedido(pedidos, qtdPedidos);
            break;
        case 13:
            simularEntrega(pedidos, qtdPedidos, veiculos, qtdVeiculos);
            break;
        case 14:
            iniciarEntregaManual(pedidos, qtdPedidos, veiculos, qtdVeiculos);
            break;

        case 15:
            finalizarEntregaManual(pedidos, qtdPedidos, veiculos, qtdVeiculos);
            break;

        case 0:
            cout << "Encerrando programa...\n";
            fazerBackup(veiculos, qtdVeiculos, centros, qtdCentros, pedidos, qtdPedidos);

            break;
        default:
            cout << "Opcao invalida.\n";
        }
    } while (opcao != 0);

    // liberação das memorias
    for (int i = 0; i < qtdVeiculos; i++)
        delete veiculos[i];
    for (int i = 0; i < qtdCentros; i++)
        delete centros[i];
    for (int i = 0; i < qtdPedidos; i++)
        delete pedidos[i];

    return 0;
}