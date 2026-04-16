#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    using namespace std;
    vector<pair<string, int>> alunos;
    int index = 1;
    int choice;
    pair<string, int> temp;

    cout << "Bem-vindo ao sistema de cadastro de alunos!" << endl;
    while (true) {
        cout << "Escolha uma opção:" << endl;
        cout << "0. Sair." << endl;
        cout << "1. Cadastrar aluno." << endl;
        cout << "2. Listar os alunos." << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Qual seu nome?" << endl;
                cin >> temp.first;

                temp.first.erase(
                    remove(temp.first.begin(), temp.first.end(), '\n'),
                    temp.first.end());
                if (temp.first.length() < 3) {
                    cout << "Nome muito curto. Tente novamente." << endl;
                    break;
                }
                if (temp.first.length() > 50) {
                    cout << "Nome muito longo. tente novamente." << endl;
                    break;
                }

                if (temp.first.find(' ') != string::npos) {
                    cout << "Nome não pode conter espaços. Tente novamente."
                         << endl;
                    break;
                }
                temp.second = index;
                index++;
                alunos.push_back(temp);
                break;

            case 2:
                for (auto& aluno : alunos) {
                    cout << "Aluno: " << aluno.first
                         << ", Matrícula: " << aluno.second << endl;
                }
                break;

            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    }
}