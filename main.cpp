#include <iostream>
#include <cmath>
#include <iomanip> // Para std::setw e std::setprecision

using namespace std;

double f1(double x) {
    return x * x - 3;
}

double f2(double x) {
    return x * x * x - 10;
}

double bissecao(double (*f)(double), double a, double b, double tol, int interrupcao) {
    double fa = f(a);
    double fb = f(b);

    if (fa * fb >= 0) {
        cerr << "Erro: f(a) e f(b) devem ter sinais opostos." << endl;
        return NAN;
    }

    double c, fc;
    int iteracoes = 0;
    double E_ideal = (b - a) / 2.0;

    // Cabeçalho da tabela
    cout << fixed << setprecision(6);
    cout << setw(4) << "N" << setw(12) << "A" << setw(12) << "B" << setw(12) << "x_ns" 
         << setw(12) << "f(x_ns)" << setw(12) << "f(A)" << setw(12) << "f(B)" 
         << setw(16) << "f(A)*f(x_ns)" << setw(16) << "f(B)*f(x_ns)" << setw(12) << "E_ideal" 
         << setw(12) << "E" << endl;

    while ((b - a) / 2.0 > tol) {
        c = (a + b) / 2.0;
        fc = f(c);
        E_ideal = (b - a) / 2.0;

        // Imprime os valores das variáveis em cada iteração
        cout << setw(4) << iteracoes + 1 << setw(12) << a << setw(12) << b << setw(12) << c 
             << setw(12) << fc << setw(12) << fa << setw(12) << fb 
             << setw(16) << fa * fc << setw(16) << fb * fc << setw(12) << E_ideal 
             << setw(12) << fabs(fc) << endl;

        if (fabs(fc) < tol) {
            break;
        }

        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }

        iteracoes++;

        if (iteracoes == interrupcao) {
            cout << "Limite de iteracoes." << endl;
            return c;  // Retorna o valor aproximado encontrado até agora
        }
    }

    cout << "Raiz encontrada em " << iteracoes << " iteracoes." << endl;
    return (a + b) / 2.0;
}

int main() {
    double a1 = 1.0;  // Valor inicial de a para f1(x)
    double b1 = 2.0;  // Valor inicial de b para f1(x)
    double tol = 0.01;
    int interrupcao = 100;  // Limite de iterações

    double raiz1 = bissecao(f1, a1, b1, tol, interrupcao);
    if (!isnan(raiz1)) {
        cout << "A raiz aproximada de f1(x): " << raiz1 << endl;
    }

    double a2 = 2.0;  // Valor inicial de a para f2(x)
    double b2 = 3.0;  // Valor inicial de b para f2(x)
    cout << "\n\n\n" << endl;
    double raiz2 = bissecao(f2, a2, b2, tol, interrupcao);
    if (!isnan(raiz2)) {
        cout << "A raiz aproximada de f2(x): " << raiz2 << endl;
    }

    return 0;
}
