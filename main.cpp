#include <iostream>
#include <string>
#include <limits>

const int MAX_ATIVOS = 100;

struct Ativo {
    std::string ticket;
    int quantidade;
    double precoMedio;
};

void registrarCompra(Ativo ativos[], int &numAtivos) {
    if (numAtivos >= MAX_ATIVOS) {
        std::cout << "Limite de ativos atingido.\n";
        return;
    }

    std::string ticket;
    int quantidade;
    double preco;

    std::cout << "Ticket: ";
    std::cin >> ticket;
    std::cout << "Quantidade: ";
    std::cin >> quantidade;
    std::cout << "Preco: ";
    std::cin >> preco;

    for (int i = 0; i < numAtivos; ++i) {
        if (ativos[i].ticket == ticket) {
            ativos[i].precoMedio = (ativos[i].precoMedio * ativos[i].quantidade + preco * quantidade) / (ativos[i].quantidade + quantidade);
            ativos[i].quantidade += quantidade;
            std::cout << "Compra registrada com sucesso!\n";
            return;
        }
    }

    Ativo novoAtivo = {ticket, quantidade, preco};
    ativos[numAtivos] = novoAtivo;
    numAtivos++;
    std::cout << "Novo ativo registrado com sucesso!\n";
}

void registrarVenda(Ativo ativos[], int numAtivos) {
    std::string ticket;
    int quantidade;
    double preco;

    std::cout << "Ticket: ";
    std::cin >> ticket;
    std::cout << "Quantidade: ";
    std::cin >> quantidade;

    for (int i = 0; i < numAtivos; ++i) {
        if (ativos[i].ticket == ticket) {
            if (ativos[i].quantidade < quantidade) {
                std::cout << "Quantidade insuficiente para venda.\n";
                return;
            }

            ativos[i].quantidade -= quantidade;
            std::cout << "Venda registrada com sucesso!\n";
            return;
        }
    }

    std::cout << "Ativo nao encontrado.\n";
}

int buscarAtivo(Ativo ativos[], int esquerda, int direita, const std::string &ticket) {
    if (direita >= esquerda) {
        int meio = esquerda + (direita - esquerda) / 2;

        if (ativos[meio].ticket == ticket) {
            return meio;
        }

        if (ativos[meio].ticket > ticket) {
            return buscarAtivo(ativos, esquerda, meio - 1, ticket);
        }

        return buscarAtivo(ativos, meio + 1, direita, ticket);
    }

    return -1;
}

void verSaldoAtivo(Ativo ativos[], int numAtivos) {
    std::string ticket;
    std::cout << "Ticket: ";
    std::cin >> ticket;

    int indice = buscarAtivo(ativos, 0, numAtivos - 1, ticket);
    if (indice != -1) {
        std::cout << "Ticket: " << ativos[indice].ticket << ", Quantidade: " << ativos[indice].quantidade << ", Preco Medio: " << ativos[indice].precoMedio << "\n";
    } else {
        std::cout << "Ativo não encontrado.\n";
    }
}

void listarPatrimonio(Ativo ativos[], int numAtivos) {
    for (int i = 0; i < numAtivos; ++i) {
        std::cout << "Ticket: " << ativos[i].ticket << ", Quantidade: " << ativos[i].quantidade << ", Preco Medio: " << ativos[i].precoMedio << "\n";
    }
}

int main() {
    Ativo ativos[MAX_ATIVOS];
    int numAtivos = 0;
    int opcao;

    do {
        std::cout << "===== Menu =====\n";
        std::cout << "1. Registrar Compra\n";
        std::cout << "2. Registrar Venda\n";
        std::cout << "3. Ver Saldo de um Ativo\n";
        std::cout << "4. Listar Patrimonio\n";
        std::cout << "5. Sair\n";
        std::cout << "Selecione uma opcao: ";
        std::cin >> opcao;


        if (std::cin.fail() || opcao < 1 || opcao > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora caracteres inválidos no buffer---pesquisei
            std::cout << "Opção inválida! Tente novamente.\n";
        } else {
            switch (opcao) {
                case 1:
                    registrarCompra(ativos, numAtivos);
                    break;
                case 2:
                    registrarVenda(ativos, numAtivos);
                    break;
                case 3:
                    verSaldoAtivo(ativos, numAtivos);
                    break;
                case 4:
                    listarPatrimonio(ativos, numAtivos);
                    break;
                case 5:
                    std::cout << "Saindo...\n";
                    break;
            }
        }

    } while (opcao != 5);

    return 0;
}
