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

private:
    double coordenadaOrigem[2];
};
class Pedido
{
public:
    Veiculo AcharVeiculoMaisProximo(Veiculo *veiculos[], int quantidade)
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
            }
        }
        return *veiculoMaisProximo;
    }

private:
    double coordenadaDestino[2];
    CentroDistribuicao *origem;
    Veiculo *veiculoMaisProximo;
    double calcularDistanciaEntreDoisPontos(double x1, double y1, double x2, double y2) { return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); }
    CentroDistribuicao acharCentroDeDistruibuicaoMaisProximo(CentroDistribuicao *centros[], int quantidade)
    {
        double distanciaMinima = 999999.9;
        CentroDistribuicao *centroDeDistruibuicaoMaisProximo = nullptr;
        for (int i = 0; i < quantidade; i++)
        {
            CentroDistribuicao *centro = centros[i];
            double distanciaCalculada = calcularDistanciaEntreDoisPontos(coordenadaDestino[0], coordenadaDestino[1], centro->getOrigemX(), centro->getOrigemY());

            if (distanciaCalculada < distanciaMinima)
            {
                distanciaMinima = distanciaCalculada;
                centroDeDistruibuicaoMaisProximo = centro;
            }
        }
        origem = centroDeDistruibuicaoMaisProximo;
    }
};

int main()
{
    Veiculo veiculos[100];
}