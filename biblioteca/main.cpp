#include <iostream>
#include <string>
#include <vector>
class livro;
struct pessoa;
int MenuPrincipal();
void AdicionarLivro(uint &id);
void Devolucao(std::vector<pessoa> &pessoas, std::vector<livro> &livros);
void Emprestimo(std::vector<pessoa> &pessoas, std::vector<livro> &livros);
void ClearInput();

class livro {
  public:
    pessoa *leitor;
    std::string nomeDoLivro;
    std::string nomeDoAutor;
    int ano;
    uint id;
    livro(std::string nomeDoLivro, std::string nomeDoAutor, int ano, uint id) {
        this->nomeDoLivro = nomeDoLivro;
        this->nomeDoAutor = nomeDoAutor;
        this->ano = ano;
        this->id = id;
    };
    void devolucao();
};
struct pessoa {
    std::string nome;
    uint cpf;
    livro *livroEmprestado;
};
// main
int main() {
    std::vector<livro> livros;
    std::vector<pessoa> pessoas;
    uint index;
    uint escolha;
    while (true) {
        escolha = MenuPrincipal();
        switch (escolha) {
        case 1:
            AdicionarLivro(index);
            break;
        case 2:
            Emprestimo(pessoas, livros);
            break;
        case 3:
            Devolucao(pessoas, livros);
            break;
        case 4:
            break;
        default:
            std::cout << "ocorreu um erro";
        }
    }
}
// functions
void ClearInput() {
    using namespace std;
    cin.ignore();
    return;
}
int MenuPrincipal() {
    int c = 0;
    using std::cin;
    using std::cout;
    using std::endl;
    cout << "MENU" << endl;
    while (true) {
        cout << endl;
        cout << "1. Adicionar livro" << endl;
        cout << "2. Empréstimo" << endl;
        cout << "3. Devolução" << endl;
        cout << "4. Adicionar cliente" << endl;
        cout << ">>";
        cin >> c;
        if (c > 0 || 4 >= c) {
            break;
        }
        cout << "tente novamente";
    }
    return c;
}
void AdicionarLivro(uint &id) {
    std::string nome;
    std::string autor;
    int ano;

    std::cout << "Nome do livro: ";
    ClearInput();
    std::getline(std::cin, nome);

    std::cout << "Autor do livro; ";
    ClearInput();
    std::getline(std::cin, autor);

    std::cout << "Ano do livro: ";
    ClearInput();
    std::cin >> ano;

    livro temp(nome, autor, ano, id);
    id++;
    return;
}
void Emprestimo(std::vector<pessoa> &pessoas, std::vector<livro> &livros) {
    uint id;
    int cpf;
    pessoa *cliente = nullptr;
    std::cout << "cpf do leitor" << std::endl;
    ClearInput();
    std::cin >> cpf;
    std::cout << "id do livro" << std::endl;
    ClearInput();
    std::cout << ">>";
    std::cin >> id;
    for (auto &p : pessoas) {
        if (p.cpf != cpf) {
            continue;
        }
        cliente = &p;
        break;
    }
    if (cliente == nullptr) {
        std::cout << "cliente não encontrado" << std::endl;
        return;
    }
    if (cliente->livroEmprestado != nullptr) {
        std::cout << "já possui livro" << std::endl;
        return;
    }
    for (auto &l : livros) {
        if (l.id == id) {
            l.leitor = cliente;
            cliente->livroEmprestado = &l;
            return;
        }
    }
    std::cout << "nn deu certo" << std::endl;
    return;
}
void Devolucao(std::vector<pessoa> &pessoas, std::vector<livro> &livros) {
    int cpf;
    pessoa *cliente = nullptr;
    std::cout << "cpf do retornante: ";
    std::cin >> cpf;

    for (auto &p : pessoas) {
        if (p.cpf != cpf) {
            continue;
        }
        cliente = &p;
        break;
    }
    if (cliente == nullptr) {
        std::cout << "não achou o cliente" << std::endl;
        return;
    }
    if (!(cliente->livroEmprestado)) {
        std::cout << "nn tem livro" << std::endl;
        return;
    }
    cliente->livroEmprestado->devolucao();
}
void livro::devolucao() {
    if (leitor != nullptr) {
        leitor->livroEmprestado = nullptr;
        leitor = nullptr;
    }
}