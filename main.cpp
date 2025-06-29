#include <iostream>
#include <cstring>

#include <math.h>

using namespace std;
class CentroDistribuicao
{
public:
    double getOrigemX()
    {
        return coordenadaOrigem[0];
    }
    double getOrigemY()
    {
        return coordenadaOrigem[1];
    }
    char *getNomeLocal()
    {
        return nomeLocal;
    }
    void setNovoLocal(const char *novoLocal)
    {
        strncpy(nomeLocal, novoLocal, sizeof(nomeLocal) - 1);
        nomeLocal[sizeof(nomeLocal) - 1] = '\0';
    }
    CentroDistribuicao()
    {
        coordenadaOrigem[0] = 0.0;
        coordenadaOrigem[1] = 0.0;
        strcpy(nomeLocal, "");
    }

    void exibirCentro()
    {
        cout << "Nome local: " << nomeLocal << endl;
        cout << "Coordenada X: " << coordenadaOrigem[0] << " Y: " << coordenadaOrigem[1] << endl;
    }
    void setCoordenadas(double x, double y)
    {
        coordenadaOrigem[0] = x;
        coordenadaOrigem[1] = y;
    }

private:
    double coordenadaOrigem[2];
    char nomeLocal[20];
};

void cadastrarCentro(CentroDistribuicao *centros[], int &quantidade)
{
    if (quantidade >= 100)
    {
        cout << "Limite de centros atingido.\n";
        return;
    }

    char nome[20];
    double x, y;

    cout << "Digite o nome do centro: ";
    cin >> nome;

    cout << "Digite a coordenada X: ";
    cin >> x;

    cout << "Digite a coordenada Y: ";
    cin >> y;

    CentroDistribuicao *novoCentro = new CentroDistribuicao();
    novoCentro->setNovoLocal(nome);

    novoCentro->setCoordenadas(x, y);

    centros[quantidade] = novoCentro;
    quantidade++;

    cout << "Centro cadastrado com sucesso.\n";
}

void listarCentros(CentroDistribuicao *centros[], int quantidade)
{
    if (quantidade == 0)
    {
        cout << "Nenhum centro cadastrado.\n";
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        cout << "Centro [" << i + 1 << "]\n";
        centros[i]->exibirCentro();
    }
}

void excluirCentro(CentroDistribuicao *centros[], int &quantidade)
{

    char nomeProcurado[20];
    cout << "Digite o nome do centro que deseja excluir: ";
    cin >> nomeProcurado;

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(centros[i]->getNomeLocal(), nomeProcurado) == 0)
        {
            delete centros[i];
            for (int j = i; j < quantidade - 1; j++)
            {
                centros[j] = centros[j + 1];
            }
            quantidade--;
            cout << "Centro removido com sucesso.\n";
            return;
        }
    }
    cout << "Centro com nome \"" << nomeProcurado << "\" nao encontrado.\n";
}

void atualizarCentro(CentroDistribuicao *centros[], int quantidade)
{
    char nomeProcurado[20];

    cout << "Digite o nome do centro que deseja atualizar: ";
    cin >> nomeProcurado;

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(centros[i]->getNomeLocal(), nomeProcurado) == 0)
        {
            char novoNome[20];
            cout << "Digite o novo nome do centro: ";
            cin >> novoNome;
            centros[i]->setNovoLocal(novoNome);
            cout << "Centro atualizado com sucesso.\n";
            return;
        }
    }

    cout << "Centro com nome \"" << nomeProcurado << "\" nao encontrado.\n";
}

class Veiculo
{
public:
    CentroDistribuicao *getLocalAtual()
    {
        return localAtual;
    }
    void setLocalAtual(CentroDistribuicao *novoLocal)
    {
        localAtual = novoLocal;
    }
    bool getStatus()
    {
        return status;
    }
    char *getPlaca()
    {
        return placa;
    }
    void setPlacaNova(char *placaNova)
    {
        strncpy(placa, placaNova, sizeof(placa) - 1);
        placa[sizeof(placa) - 1] = '\0';
    }
    char *getModelo()
    {
        return modelo;
    }
    void setModelo(const char *modeloNovo)
    {
        strncpy(modelo, modeloNovo, sizeof(modelo) - 1);
        modelo[sizeof(modelo) - 1] = '\0';
    }
    Veiculo()
    {
        status = false;
        localAtual = nullptr;
        strcpy(placa, "");
        strcpy(modelo, "");
    }

    void exibirVeiculo()
    {
        cout << "Placa: " << getPlaca() << endl;
        cout << "Modelo: " << getModelo() << endl;
        if (this->status == 0)
        {
            cout << "Status: Livre" << endl;
        }
        else
        {
            cout << "Status: Ocupado" << endl;
        }

        if (localAtual != nullptr)
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
    void iniciarEntrega() { this->status = 1; }
    void finalizarEntrega(CentroDistribuicao *destino)
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

void cadastrarVeiculo(Veiculo *veiculos[], int &quantidade, CentroDistribuicao *centros[], int qtdCentros)
{
    if (quantidade >= 100)
    {
        cout << "Limite de veiculos atingido.\n";
        return;
    }

    if (qtdCentros == 0)
    {
        cout << "Nenhum centro de distribuição cadastrado. Cadastre um centro antes de adicionar veículos.\n";
        return;
    }

    char placa[20], modelo[20];

    cout << "Digite a placa do veiculo: ";
    cin >> placa;

    cout << "Digite o modelo do veiculo: ";
    cin >> modelo;

    cout << "\nCentros de distribuição disponíveis:\n";
    for (int i = 0; i < qtdCentros; i++)
    {
        cout << i + 1 << ". ";
        centros[i]->exibirCentro();
    }

    int opcaoCentro;
    cout << "Escolha o número do centro onde o veículo está: ";
    cin >> opcaoCentro;

    if (opcaoCentro < 1 || opcaoCentro > qtdCentros)
    {
        cout << "Opção inválida. Veículo não cadastrado.\n";
        return;
    }

    veiculos[quantidade] = new Veiculo();
    veiculos[quantidade]->setPlacaNova(placa);
    veiculos[quantidade]->setModelo(modelo);
    veiculos[quantidade]->setLocalAtual(centros[opcaoCentro - 1]);

    quantidade++;

    cout << "Veiculo cadastrado com sucesso.\n";
}

void atualizarVeiculo(Veiculo *veiculos[], int quantidade)
{
    char placaProcurada[20];

    cout << "Digite a placa do veiculo que voce deseja atualizar: ";
    cin >> placaProcurada;
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(veiculos[i]->getPlaca(), placaProcurada) == 0)
        {
            cout << "Nova placa: ";
            char novaPlaca[20];
            cin >> novaPlaca;
            veiculos[i]->setPlacaNova(novaPlaca);
            cout << "Placa atualizada com sucesso.\n";
            return;
        }
    }
    cout << "Veiculo placa " << placaProcurada << " nao encontrado.\n";
}

void excluirVeiculo(Veiculo *veiculos[], int &quantidade)
{
    char placaProcurada[20];

    cout << "Digite a placa do veiculo que voce deseja atualizar: ";
    cin >> placaProcurada;
    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(veiculos[i]->getPlaca(), placaProcurada) == 0)
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

void listarVeiculos(Veiculo *veiculos[], int quantidade)
{
    if (quantidade == 0)
    {
        cout << "Nenhum veiculo cadastrado.\n";
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        veiculos[i]->exibirVeiculo();
    }
}

class Pedido
{
public:
    Pedido()
    {
        coordenadaDestino[0] = 0.0;
        coordenadaDestino[1] = 0.0;
        strcpy(idUnico, "");
        pesoDoItem = 0.0;
    }
    const char *getIdUnico() const
    {
        return idUnico;
    }

    double getDestinoX() const
    {
        return coordenadaDestino[0];
    }

    double getDestinoY() const
    {
        return coordenadaDestino[1];
    }

    double getPeso() const
    {
        return pesoDoItem;
    }

    void setIdUnico(const char *novoId)
    {
        strncpy(idUnico, novoId, sizeof(idUnico) - 1);
        idUnico[sizeof(idUnico) - 1] = '\0';
    }

    void setDestino(double x, double y)
    {
        coordenadaDestino[0] = x;
        coordenadaDestino[1] = y;
    }
    void setDestinoCentro(CentroDistribuicao *centro)
    {
        destino = centro;
        setDestino(centro->getOrigemX(), centro->getOrigemY());
    }

    void setPeso(double novoPeso)
    {
        pesoDoItem = novoPeso;
    }
    CentroDistribuicao *getOrigem() const
    {
        return origem;
    }
    CentroDistribuicao *getDestinoCentro() const { return destino; }

    void setOrigem(CentroDistribuicao *novoCentro)
    {
        origem = novoCentro;
    }

    Veiculo *AcharVeiculoMaisProximo(Veiculo *veiculos[], int quantidade)
    {
        double distanciaMinima = 999999.9;
        Veiculo *veiculoMaisProximo = nullptr;

        for (int i = 0; i < quantidade; i++)
        {
            Veiculo *veiculo = veiculos[i];

            // Ignora veículos ocupados
            if (!veiculo->getStatus())
            {
                CentroDistribuicao *localVeiculo = veiculo->getLocalAtual();

                // Verifica se o local atual está definido
                if (localVeiculo == nullptr)
                    continue;

                double distanciaCalculada = calcularDistanciaEntreDoisPontos(
                    coordenadaDestino[0], coordenadaDestino[1],
                    localVeiculo->getOrigemX(), localVeiculo->getOrigemY());

                if (distanciaCalculada < distanciaMinima)
                {
                    distanciaMinima = distanciaCalculada;
                    veiculoMaisProximo = veiculo;
                    this->veiculoMaisProximo = veiculo;
                }
            }
        }

        return veiculoMaisProximo;
    }
    Veiculo *getVeiculoMaisProximo()
    {
        return veiculoMaisProximo;
    }
    void exibirPedido()
    {
        cout << "-------------------------------\n";
        cout << "ID do Pedido: " << getIdUnico() << endl;

        if (origem != nullptr)
        {
            cout << "Origem: " << origem->getNomeLocal()
                 << " (" << origem->getOrigemX()
                 << ", " << origem->getOrigemY() << ")\n";
        }

        if (destino != nullptr)
        {
            cout << "Destino: " << destino->getNomeLocal()
                 << " (" << getDestinoX()
                 << ", " << getDestinoY() << ")\n";
        }

        cout << "Peso: " << getPeso() << " kg\n";
        cout << "-------------------------------\n";
    }

    void atualizarPedido(Pedido *pedidos[], int quantidade)
    {
        char idProcurado[20];

        cout << "Digite o ID do pedido que deseja atualizar: ";
        cin >> idProcurado;

        for (int i = 0; i < quantidade; i++)
        {
            if (strcmp(pedidos[i]->getIdUnico(), idProcurado) == 0)
            {
                double novoPeso, novoX, novoY;
                cout << "Digite o novo peso do item: ";
                cin >> novoPeso;

                cout << "Digite as novas coordenadas de destino (X e Y): ";
                cin >> novoX >> novoY;

                pedidos[i]->setPeso(novoPeso);
                pedidos[i]->setDestino(novoX, novoY);

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
    CentroDistribuicao *origem;
    CentroDistribuicao *destino;
    Veiculo *veiculoMaisProximo;
    double calcularDistanciaEntreDoisPontos(double x1, double y1, double x2, double y2) { return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); }
    void acharCentroDeDistribuicaoMaisProximo(CentroDistribuicao *centros[], int quantidade)
    {
        double distanciaMinima = 999999.9;
        CentroDistribuicao *centroDeDistribuicaoMaisProximo = nullptr;
        for (int i = 0; i < quantidade; i++)
        {
            CentroDistribuicao *centro = centros[i];
            double distanciaCalculada = calcularDistanciaEntreDoisPontos(coordenadaDestino[0], coordenadaDestino[1], centro->getOrigemX(), centro->getOrigemY());

            if (distanciaCalculada < distanciaMinima)
            {
                distanciaMinima = distanciaCalculada;
                centroDeDistribuicaoMaisProximo = centro;
            }
        }
        origem = centroDeDistribuicaoMaisProximo;
    }
};

void criarPedido(Pedido *pedidos[], int &quantidade, CentroDistribuicao *centros[], int qtdCentros)
{
    if (quantidade >= 100)
    {
        cout << "Limite de pedidos atingido.\n";
        return;
    }
    if (qtdCentros == 0)
    {
        cout << "Nenhum centro cadastrado. Cadastre um centro primeiro.\n";
        return;
    }

    Pedido *novoPedido = new Pedido();

    char id[20];
    double peso;

    cout << "Digite o ID do pedido: ";
    cin >> id;

    // Escolher centro de origem
    cout << "\nCentros de distribuição disponíveis:\n";
    for (int i = 0; i < qtdCentros; i++)
    {
        cout << i + 1 << ". ";
        centros[i]->exibirCentro();
    }

    int opcaoOrigem;
    cout << "Escolha o número do centro de ORIGEM: ";
    cin >> opcaoOrigem;

    if (opcaoOrigem < 1 || opcaoOrigem > qtdCentros)
    {
        cout << "Opção inválida. Pedido cancelado.\n";
        delete novoPedido;
        return;
    }

    CentroDistribuicao *centroOrigem = centros[opcaoOrigem - 1];
    novoPedido->setOrigem(centroOrigem);

    // Escolher centro de destino
    int opcaoDestino;
    cout << "Escolha o número do centro de DESTINO: ";
    cin >> opcaoDestino;

    if (opcaoDestino < 1 || opcaoDestino > qtdCentros)
    {
        cout << "Opção inválida. Pedido cancelado.\n";
        delete novoPedido;
        return;
    }

    CentroDistribuicao *centroDestino = centros[opcaoDestino - 1];

    if (centroOrigem == centroDestino)

    {
        cout << "Origem e destino não podem ser o mesmo centro.\n";
        delete novoPedido;
        return;
    }

    novoPedido->setDestinoCentro(centroDestino);

    cout << "Digite o peso do item: ";
    cin >> peso;

    novoPedido->setIdUnico(id);
    novoPedido->setPeso(peso);

    pedidos[quantidade] = novoPedido;
    quantidade++;

    cout << "Pedido criado com sucesso.\n";
}

void excluirPedido(Pedido *pedidos[], int &quantidade)
{
    if (quantidade == 0)
    {
        cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    char idProcurado[20];
    cout << "Digite o ID do pedido que deseja excluir: ";
    cin >> idProcurado;

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(pedidos[i]->getIdUnico(), idProcurado) == 0)
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

    cout << "Pedido com ID \"" << idProcurado << "\" nao encontrado.\n";
}

void listarPedido(Pedido *pedidos[], int quantidade)
{
    if (quantidade == 0)
    {
        cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    for (int i = 0; i < quantidade; i++)
    {
        cout << "Pedido [" << i + 1 << "]\n";
        pedidos[i]->exibirPedido();
    }
}
void simularEntrega(Pedido *pedidos[], int qtdPedidos, Veiculo *veiculos[], int qtdVeiculos)
{
    if (qtdPedidos == 0)
    {
        cout << "Nenhum pedido cadastrado!" << endl;
        return;
    }

    char id[20];
    cout << "Digite o id do pedido a ser simulado: ";
    cin >> id;

    Pedido *pedidoSelecionado = nullptr;
    for (int i = 0; i < qtdPedidos; i++)
    {
        if (strcmp(pedidos[i]->getIdUnico(), id) == 0)
        {
            pedidoSelecionado = pedidos[i];
            break;
        }
    }

    if (pedidoSelecionado == nullptr)
    {
        cout << "Nenhum pedido encontrado.\n";
        return;
    }

    Veiculo *veiculo = pedidoSelecionado->AcharVeiculoMaisProximo(veiculos, qtdVeiculos);

    if (veiculo == nullptr)
    {
        cout << "Nenhum veiculo disponível encontrado.\n";
        return;
    }

    cout << "Simulação realizada com sucesso." << endl;
    cout << "Veículo mais próximo: " << veiculo->getPlaca() << " no centro " << veiculo->getLocalAtual()->getNomeLocal() << endl;
    cout << "Destino do pedido: " << pedidoSelecionado->getDestinoCentro()->getNomeLocal() << endl;
}

void iniciarEntregaManual(Pedido *pedidos[], int qtdPedidos, Veiculo *veiculos[], int qtdVeiculos)
{
    if (qtdPedidos == 0)
    {
        cout << "Nenhum pedido cadastrado.\n";
        return;
    }

    char id[20];
    cout << "Digite o ID do pedido que deseja entregar: ";
    cin >> id;

    Pedido *pedidoSelecionado = nullptr;
    for (int i = 0; i < qtdPedidos; i++)
    {
        if (strcmp(pedidos[i]->getIdUnico(), id) == 0)
        {
            pedidoSelecionado = pedidos[i];
            break;
        }
    }

    if (pedidoSelecionado == nullptr)
    {
        cout << "Pedido não encontrado.\n";
        return;
    }

    Veiculo *veiculo = pedidoSelecionado->AcharVeiculoMaisProximo(veiculos, qtdVeiculos);

    if (veiculo == nullptr)
    {
        cout << "Nenhum veículo disponível para realizar a entrega.\n";
        return;
    }

    veiculo->iniciarEntrega();
    cout << "Entrega iniciada com sucesso!\n";
    cout << "Veículo " << veiculo->getPlaca() << " realizará a entrega para o destino: "
         << pedidoSelecionado->getDestinoCentro()->getNomeLocal() << endl;
}

void finalizarEntregaManual(Pedido *pedidos[], int qtdPedidos, Veiculo *veiculos[], int qtdVeiculos)
{
    if (qtdPedidos == 0)
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
        if (strcmp(pedidos[i]->getIdUnico(), id) == 0)
        {
            pedidoSelecionado = pedidos[i];
            break;
        }
    }

    if (pedidoSelecionado == nullptr)
    {
        cout << "Pedido não encontrado.\n";
        return;
    }

    Veiculo *veiculo = pedidoSelecionado->getVeiculoMaisProximo();

    if (veiculo == nullptr || !veiculo->getStatus())
    {
        cout << "Veículo não encontrado ou não está em entrega.\n";
        return;
    }

    veiculo->finalizarEntrega(pedidoSelecionado->getDestinoCentro());

    cout << "Entrega finalizada com sucesso.\n";
    cout << "Veículo " << veiculo->getPlaca() << " agora está disponível no centro "
         << pedidoSelecionado->getDestinoCentro()->getNomeLocal() << endl;
}
void fazerBackup(Veiculo *veiculos[], int qtdVeiculos, CentroDistribuicao *centros[], int qtdCentros, Pedido *pedidos[], int qtdPedidos)
{
    // Backup dos centros
    FILE *arqCentro = fopen("centros.bin", "wb");
    fwrite(&qtdCentros, sizeof(int), 1, arqCentro);
    for (int i = 0; i < qtdCentros; i++)
    {
        fwrite(centros[i], sizeof(CentroDistribuicao), 1, arqCentro);
    }
    fclose(arqCentro);

    // Backup dos veículos
    FILE *arqVeiculo = fopen("veiculos.bin", "wb");
    fwrite(&qtdVeiculos, sizeof(int), 1, arqVeiculo);
    for (int i = 0; i < qtdVeiculos; i++)
    {
        fwrite(veiculos[i], sizeof(Veiculo), 1, arqVeiculo);

        // Salvar o índice do centro onde o veículo está
        for (int j = 0; j < qtdCentros; j++)
        {
            if (veiculos[i]->getLocalAtual() == centros[j])
            {
                fwrite(&j, sizeof(int), 1, arqVeiculo);
                break;
            }
        }
    }
    fclose(arqVeiculo);

    // Backup dos pedidos
    FILE *arqPedido = fopen("pedidos.bin", "wb");
    fwrite(&qtdPedidos, sizeof(int), 1, arqPedido);
    for (int i = 0; i < qtdPedidos; i++)
    {
        fwrite(pedidos[i], sizeof(Pedido), 1, arqPedido);

        int origemIndex = -1, destinoIndex = -1;
        for (int j = 0; j < qtdCentros; j++)
        {
            if (pedidos[i]->getOrigem() == centros[j])
                origemIndex = j;
            if (pedidos[i]->getDestinoCentro() == centros[j])
                destinoIndex = j;
        }
        fwrite(&origemIndex, sizeof(int), 1, arqPedido);
        fwrite(&destinoIndex, sizeof(int), 1, arqPedido);
    }
    fclose(arqPedido);

    cout << "Backup concluído com sucesso!\n";
}
void restaurarBackup(Veiculo *veiculos[], int &qtdVeiculos, CentroDistribuicao *centros[], int &qtdCentros, Pedido *pedidos[], int &qtdPedidos)
{
    // Restaurar centros
    FILE *arqCentro = fopen("centros.bin", "rb");
    if (!arqCentro)
    {
        cout << "Arquivo de centros não encontrado.\n";
        return;
    }

    fread(&qtdCentros, sizeof(int), 1, arqCentro);
    for (int i = 0; i < qtdCentros; i++)
    {
        centros[i] = new CentroDistribuicao();
        fread(centros[i], sizeof(CentroDistribuicao), 1, arqCentro);
    }
    fclose(arqCentro);

    // Restaurar veículos
    FILE *arqVeiculo = fopen("veiculos.bin", "rb");
    fread(&qtdVeiculos, sizeof(int), 1, arqVeiculo);
    for (int i = 0; i < qtdVeiculos; i++)
    {
        veiculos[i] = new Veiculo();
        fread(veiculos[i], sizeof(Veiculo), 1, arqVeiculo);

        int centroIndex;
        fread(&centroIndex, sizeof(int), 1, arqVeiculo);
        if (centroIndex >= 0 && centroIndex < qtdCentros)
        {
            veiculos[i]->setLocalAtual(centros[centroIndex]);
        }
    }
    fclose(arqVeiculo);

    // Restaurar pedidos
    FILE *arqPedido = fopen("pedidos.bin", "rb");
    fread(&qtdPedidos, sizeof(int), 1, arqPedido);
    for (int i = 0; i < qtdPedidos; i++)
    {
        pedidos[i] = new Pedido();
        fread(pedidos[i], sizeof(Pedido), 1, arqPedido);

        int origemIndex, destinoIndex;
        fread(&origemIndex, sizeof(int), 1, arqPedido);
        fread(&destinoIndex, sizeof(int), 1, arqPedido);

        if (origemIndex >= 0 && origemIndex < qtdCentros)
            pedidos[i]->setOrigem(centros[origemIndex]);
        if (destinoIndex >= 0 && destinoIndex < qtdCentros)
            pedidos[i]->setDestinoCentro(centros[destinoIndex]);
    }
    fclose(arqPedido);

    cout << "Backup restaurado com sucesso!\n";
}

int main()
{
    Veiculo *veiculos[100];
    CentroDistribuicao *centros[100];
    Pedido *pedidos[100];
    int qtdVeiculos = 0, qtdCentros = 0, qtdPedidos = 0;
    restaurarBackup(veiculos, qtdVeiculos, centros, qtdCentros, pedidos, qtdPedidos);

    int opcao;
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

    for (int i = 0; i < qtdVeiculos; i++)
        delete veiculos[i];
    for (int i = 0; i < qtdCentros; i++)
        delete centros[i];
    for (int i = 0; i < qtdPedidos; i++)
        delete pedidos[i];

    return 0;
}
