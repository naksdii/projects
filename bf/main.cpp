#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// Função para pular o loop quando a[i] == 0
int next(const string &s, int p)
{
    int nest = 1;
    for (int i = p + 1; i < s.size(); i++)
    {
        if (s.at(i) == '[')
            nest++;
        if (s.at(i) == ']')
            nest--;
        if (nest == 0)
            return i;
    }
    return p; // Caso não encontre o par (erro de sintaxe no script)
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    ifstream file(argv[1]);
    if (!file.is_open())
        return 1;

    string script = "";
    string rawLine;
    string allowed = "+-<>[].,";

    // 1. Lendo e filtrando apenas caracteres válidos
    while (getline(file, rawLine))
    {
        for (char c : rawLine)
        {
            if (allowed.find(c) != string::npos)
            {
                script += c;
            }
        }
    }

    stack<int> NodeLoop;
    int i = 0;
    vector<unsigned char> a(30000, 0); // Padrão: 30.000 células iniciadas em 0

    for (int pos = 0; pos < script.length(); pos++)
    {
        switch (script.at(pos))
        {
        case '+':
            a[i]++;
            break;
        case '-':
            a[i]--;
            break;
        case '>':
            i++;
            break;
        case '<':
            if (i > 0)
                i--;
            break; // Proteção contra índice negativo
        case '.':
            cout << (char)a[i];
            break;

        case ',':
            char input;
            if (cin >> input)
                a[i] = input;
            break;

        case '[':
            if (a[i] == 0)
            {
                // Se for 0, pula para o final do loop
                pos = next(script, pos);
            }
            else
            {
                // Se não for 0, salva a posição para voltar depois
                NodeLoop.push(pos);
            }
            break;

        case ']':
            if (!NodeLoop.empty())
            {
                if (a[i] != 0)
                {
                    // Se não for 0, volta para o '[' salvo na pilha
                    pos = NodeLoop.top();
                }
                else
                {
                    // Se for 0, sai do loop e remove da pilha
                    NodeLoop.pop();
                }
            }
            break;
        }
    }
    cout << endl;
    return 0;
}