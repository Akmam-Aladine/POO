#include <iostream>
using namespace std;

void incrementer(int* a) {
    if (a !=0) { // Vérifie que le pointeur n'est pas nul
        (*a)++; // Incrémente la a à l'adresse pointée
    }
}

int main() {

    int n;
    cout<<"entrez la valeur que tu souhaite incrementer:";
    cin>>n;
    cout << "Avant l'incrémentation on a : " << n <<endl;
    incrementer(&n); // Appelle la fonction en passant l'adresse de 'nombre'
    cout << "Après incrémentation on obtient : " << n<< endl; // Affiche 6
    return 0;
}