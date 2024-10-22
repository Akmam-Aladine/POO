#include <iostream>
#include <cmath>

using namespace std;
double sinTaylor(double x) {
    double term = x; // Premier terme de la série
    double sum = term; // Somme initiale
    int n = 1; // Compteur pour les termes

    // Continue à ajouter des termes jusqu'à ce que la précision soit atteinte
    while (abs(term) >= 0.0001) {
        term *= -x * x / ((2 * n) * (2 * n + 1)); // Calcul du terme suivant
        sum += term; // Ajout du terme à la somme
        n++; // Incrémenter le compteur
    }

    return sum;
}

int main() {
    double x;

    cout << "Entrez la valeur de x en radians: ";
    cin >> x;

    double result = sinTaylor(x);
    cout << "sin(" << x << ") ≈ " << result << endl;

    return 0;
}