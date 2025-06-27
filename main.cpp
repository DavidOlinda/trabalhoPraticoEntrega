#include <iostream>
#include <cstring>

#include <math.h>

using namespace std;
class Veiculo
{
public:
    double getPosicaoAtualVeiculoX()
    {
        return coordenadaAtual[0];
    }
    double getPosicaoAtualVeiculoY()
    {
        return coordenadaAtual[1];
    }

    void setPosicaoVeiculo(double posicaoX, double posicaoY)
    {
        coordenadaAtual[0] = posicaoX;
        coordenadaAtual[1] = posicaoY;
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
        coordenadaAtual[0] = 0.0;
        coordenadaAtual[1] = 0.0;
        strcpy(placa, "");
        strcpy(modelo, "");
    }

    void exibirVeiculo()
    {
        cout << "Placa: " << getPlaca() << endl;
        cout << "Modelo: " << getModelo() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Localizacao: X: " << getPosicaoAtualVeiculoX()
             << " Y: " << getPosicaoAtualVeiculoY() << endl;
    }
    void iniciarEntrega() { this->status = 1; }
    void finalizarEntrega(double coordenadaDestino[2])
    {
        this->status = 0;
        this->coordenadaAtual[0] = coordenadaDestino[0];
        this->coordenadaAtual[1] = coordenadaDestino[1];
    }

private:
    double coordenadaAtual[2];
    bool status;
    char placa[20];
    char modelo[20];
};

void cadastrarVeiculo(Veiculo *veiculos[], int &quantidade)
{
    double coordenadaX, coordenadaY;
    if (quantidade >= 100)
    {
        cout << "Limite de veiculos atingido.\n";
        return;
    }

    char placa[20], modelo[20];

    cout << "Digite a placa do veiculo: ";

    cin >> placa;

    cout << "Digite o modelo do veiculo: ";
    cin >> modelo;

    cout << "Digite as coordenadas de onde o veiculo esta saindo: ";
    cin >> coordenadaX;
    cin >> coordenadaY;

    veiculos[quantidade] = new Veiculo();
    veiculos[quantidade]->setPlacaNova(placa);
    veiculos[quantidade]->setModelo(modelo);
    veiculos[quantidade]->setPosicaoVeiculo(coordenadaX, coordenadaY);
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
            cin.getline(novaPlaca, 20);
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
    cin.ignore();
    cin.getline(nome, 20);

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
    cin.ignore();
    cin.getline(nomeProcurado, 20);

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
    cin.ignore();
    cin.getline(nomeProcurado, 20);

    for (int i = 0; i < quantidade; i++)
    {
        if (strcmp(centros[i]->getNomeLocal(), nomeProcurado) == 0)
        {
            char novoNome[20];
            cout << "Digite o novo nome do centro: ";
            cin.getline(novoNome, 20);
            centros[i]->setNovoLocal(novoNome);
            cout << "Centro atualizado com sucesso.\n";
            return;
        }
    }

    cout << "Centro com nome \"" << nomeProcurado << "\" nao encontrado.\n";
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

    void setPeso(double novoPeso)
    {
        pesoDoItem = novoPeso;
    }
    CentroDistribuicao *getOrigem() const
    {
        return origem;
    }

    void setOrigem(CentroDistribuicao *novoCentro)
    {
        origem = novoCentro;
    }

    Veiculo *AcharVeiculoMaisProximo(Veiculo *veiculos[], int quantidade)
    {
        double distanciaMinima = 999999.9;
        Veiculo *veiculosMaisProximo = nullptr;

        for (int i = 0; i < quantidade; i++)
        {
            Veiculo *veiculo = veiculos[i];
            double distanciaCalculada = calcularDistanciaEntreDoisPontos(coordenadaDestino[0], coordenadaDestino[1], veiculo->getPosicaoAtualVeiculoX(), veiculo->getPosicaoAtualVeiculoY());

            if (distanciaCalculada < distanciaMinima)
            {
                distanciaMinima = distanciaCalculada;
                veiculosMaisProximo = veiculo;
                this->veiculoMaisProximo = veiculo;
            }
        }
        return veiculosMaisProximo;
    }

    void exibirPedido()
    {
        if (origem != nullptr)
        {
            cout << "Origem: " << origem->getNomeLocal() << endl;
        }
        cout << "Id: " << getIdUnico() << endl;
        cout << "Coordenadas: X: " << getDestinoX() << " Y: " << getDestinoY() << endl;
        cout << "Peso: " << getPeso() << endl;
    }

    void atualizarPedido(Pedido *pedidos[], int quantidade)
    {
        char idProcurado[20];

        cout << "Digite o ID do pedido que deseja atualizar: ";
        cin.ignore();
        cin.getline(idProcurado, 20);

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
    double x, y, peso;

    cout << "Digite o ID do pedido: ";
    cin.ignore();
    cin.getline(id, 20);

    cout << "\nCentros de distribuição disponíveis:\n";
    for (int i = 0; i < qtdCentros; i++)
    {
        cout << i + 1 << ". ";
        centros[i]->exibirCentro();
    }

    int opcao;
    cout << "Escolha o número do centro de origem: ";
    cin >> opcao;

    if (opcao < 1 || opcao > qtdCentros)
    {
        cout << "Opção inválida. Pedido cancelado.\n";
        delete novoPedido;
        return;
    }

    CentroDistribuicao *centroOrigem = centros[opcao - 1];
    novoPedido->setOrigem(centroOrigem);

    cout << "Digite as coordenadas de destino (X e Y): ";
    cin >> x >> y;

    cout << "Digite o peso do item: ";
    cin >> peso;

    novoPedido->setIdUnico(id);
    novoPedido->setDestino(x, y);
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
    cin.ignore();
    cin.getline(idProcurado, 20);

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

int main()
{
    Veiculo *veiculos[100];
    CentroDistribuicao *centros[100];
    Pedido *pedidos[100];
    int qtdVeiculos = 0, qtdCentros = 0, qtdPedidos = 0;

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
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao)
        {
        case 1:
            cadastrarVeiculo(veiculos, qtdVeiculos);
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
        case 0:
            cout << "Encerrando programa...\n";
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
