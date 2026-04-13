#include <iostream>
int main() {
        double num[3];
        char op;
        while (true) {
                std::cout << std::endl << "digite seus numeros: ";
                std::cin >> num[1];
                std::cout << std::endl << "operador  (+,-,*,/,q): ";
                std::cin >> op;
                if (op == 'q') {
                        break;
                }
                std::cout << std::endl << "digite seu numero: ";
                std::cin >> num[2];
                if (op == '+') {
                        std::cout << num[1] + num[2];
                } else if (op == '-') {
                        std::cout << num[1] - num[2];
                } else if (op == '*') {
                        std::cout << num[1] * num[2];
                } else if (op == '/') {
                        if (num[2] != 0) {
                                std::cout << num[1] / num[2];
                        } else {
                                std::cout << "num 2 n pode ser 0";
                        }
                } else {
                        std::cout << "operador inválido";
                }
        }
        std::cout << std::endl;
}