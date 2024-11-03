#include <iostream>
#include <cstdlib>
using namespace std;

class Fichier {
private:
    char* pointeur;  // Pointeur vers la mémoire allouée
    int longueur;    // Longueur en nombre d'octets

public:
    // Constructeur
    Fichier(int _longueur) : longueur(_longueur) {
        pointeur = new char[longueur];  // Alloue de la mémoire
    }

    // Destructeur
    ~Fichier() {
        delete[] pointeur;  // Libère la mémoire allouée
    }

    // Méthode pour créer l'espace mémoire
    void Creation() {
        // L'espace mémoire est déjà alloué dans le constructeur
    }

    // Méthode pour remplir arbitrairement l'espace mémoire
    void Remplit() {
        for (int i = 0; i < longueur; i++) {
            pointeur[i] = rand() % 256;  // Remplit avec des valeurs aléatoires (de 0 à 255)
        }
    }

    // Méthode pour afficher la zone mémoire pointée par P
    void Affiche() {
        cout << "Contenu du fichier : ";
        for (int i = 0; i < longueur; i++) {
            cout << static_cast<int>(pointeur[i]) << " ";
        }
        cout << endl;
    }
};

int main() {
    // Instanciation de la classe Fichier
    Fichier* monFichier = new Fichier(10);

    // Appel des méthodes
    monFichier->Creation();
    monFichier->Remplit();
    monFichier->Affiche();

    // Libération de la mémoire et appel du destructeur
    delete monFichier;

    return 0;
}
