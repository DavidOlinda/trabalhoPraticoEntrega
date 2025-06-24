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
    void cadastrarVeiculo()
    {
        cout << "Digite a placa do veiculo: " << endl;
        cin.ignore();
        cin.getline(placa, 20);
        cout << "Digite o modelo do veiculo: " << endl;
        cin.getline(modelo, 20);
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

    void cadastrarCentro()
    {
        cout << "Digite o nome do local: " << endl;
        cin.ignore();
        cin.getline(nomeLocal, 20);
        cout << "Digite a coordenada X: " << endl;
        cin >> coordenadaOrigem[0];
        cout << "Digite a coordenada Y: " << endl;
        cin >> coordenadaOrigem[1];
    }
    void exibirCentro()
    {
        cout << "Nome local: " << nomeLocal << endl;
        cout << "Coordenada X: " << coordenadaOrigem[0] << " Y: " << coordenadaOrigem[1] << endl;
    }

private:
    double coordenadaOrigem[2];
    char nomeLocal[20];
};
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
                this->veiculoMaisProximo = veiculo; // <-- atualiza o atributo da classe
            }
        }
        return veiculosMaisProximo;
    }
    void criarPedido()
    {
        cout << "Digite o id: " << endl;
        cin.getline(idUnico, 20);
        cin.ignore();
        cout << "Digite as coordenadas de destino (X E Y): " << endl;
        cin >> coordenadaDestino[0];
        cin >> coordenadaDestino[1];
        cout << "Digite o peso do item: " << endl;
        cin >> pesoDoItem;
    }
    void exibirPedido()
    {
        cout << "Id: " << getIdUnico() << endl;
        cout << "Coordenadas: X: " << getDestinoX() << " Y: " << getDestinoY() << endl;
        cout << "Peso: " << getPeso() << endl;
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

int main()
{
    Veiculo veiculos[100];
}